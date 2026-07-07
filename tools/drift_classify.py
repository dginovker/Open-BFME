#!/usr/bin/env python3
"""Near-miss drift classifier: turn 'unlocated' (drifted) functions into a ranked,
categorized worklist.

For every unmatched function a tracked source emits (the present-unmatched tail),
find the best CANDIDATE placement in the binary (voted by anchors that survive
drift: known-callee call sites, verified string references, rare byte runs), then
score and classify the difference at instruction level (objdump):

  immediate-only   same code shape, only literals differ (changed constant/offset)
                   -> the mechanical queue: fix the value in source, rebuild, land
  register-swap    same shape+literals, different registers -> MSVC-regalloc wall;
                   do NOT attempt in C++ (proven on the whales); asm-candidate only
  imm+reg          both of the above
  structural       instruction shapes differ -> real logic drift, medium task
  absent           no plausible placement -> BFME removed it; prune from worklists

The report is ADVISORY ONLY: candidates are heuristic votes, and nothing lands
without tools/build.py byte-verification + the full gate suite. A wrong candidate
costs an agent a look, never a bad match.

Usage:
  python3 tools/drift_classify.py [--src src/zh] [--limit N] [--min-size 24]
Report: reverse/zh_sweep/drift_report.csv (function,source,...,class,hint)
"""
import argparse
import csv
import re
import struct
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from locate import object_functions

ROOT = build.ROOT
SCRATCH = ROOT / "build" / "drift"
REPORT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"
IMAGE_BASE = 0x400000

CLASS_ORDER = {"immediate-only": 0, "imm+reg": 1, "structural": 2,
               "register-swap": 3, "absent": 4, "no-anchors": 5, "no-obj": 6}


def load_world():
    exe = build.EXE.read_bytes()
    pe = build.pe_sections(exe)
    text = next(s for s in pe if s["name"] == ".text")
    ghidra = {}
    with (ROOT / "reverse" / "ghidra_functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            ghidra[int(row["rva"], 16)] = int(row["size"])
    matched_names, matched_rvas = set(), set()
    for row in build.load_all_function_rows():
        matched_names.add(row["name"])
        matched_rvas.add(int(row["target_rva"], 16))
    return exe, pe, text, ghidra, matched_names, matched_rvas, build.load_symbol_map()


def prescan_call_sites(exe, text):
    """One pass over .text: every e8 rel32 -> callee_rva -> [call-site rvas]."""
    sites = defaultdict(list)
    base, lo, hi = text["rva"], text["raw_pointer"], text["raw_pointer"] + text["size"]
    off = exe.find(b"\xe8", lo, hi - 5)
    while off != -1:
        rva = base + (off - lo)
        callee = rva + 5 + struct.unpack_from("<i", exe, off + 1)[0]
        if 0 < callee < 0x1400000:
            sites[callee].append(rva)
        off = exe.find(b"\xe8", off + 1, hi - 5)
    return sites


def offset_to_rva(pe, off):
    for s in pe:
        if s["raw_pointer"] <= off < s["raw_pointer"] + s["size"]:
            return s["rva"] + (off - s["raw_pointer"])
    return None


def find_candidates(exe, pe, text, body, relocs, symbol_map, call_sites, matched_rvas, obj_path):
    """Vote for candidate start RVAs using drift-surviving anchors."""
    votes = Counter()
    size = len(body)
    holes = sorted(off for off, rt, _ in relocs if rt in (0x0006, 0x0014) and off < size)

    for off, rtype, sym in relocs:
        if off >= size:
            continue
        if rtype == 0x0014 and sym in symbol_map:            # known callee anchor
            for addr in symbol_map[sym]:
                for site in call_sites.get(addr, ()):
                    votes[site - off] += 5
        elif rtype == 0x0006 and sym.startswith("??_C@"):    # verified-string anchor
            try:
                content = build.read_object_symbol_bytes(obj_path, sym)[0].rstrip(b"\x00")
            except ValueError:
                continue
            if len(content) < 6:
                continue
            spos = exe.find(content)
            while spos != -1:
                rva = offset_to_rva(pe, spos)
                if rva:
                    needle = struct.pack("<I", IMAGE_BASE + rva)
                    tpos = exe.find(needle, text["raw_pointer"], text["raw_pointer"] + text["size"])
                    while tpos != -1:
                        votes[text["rva"] + tpos - text["raw_pointer"] - off] += 5
                        tpos = exe.find(needle, tpos + 1, text["raw_pointer"] + text["size"])
                spos = exe.find(content, spos + 1)

    prev = 0                                                  # rare-byte-run anchors
    segments = []
    for hole in holes + [size]:
        if hole - prev >= 8:
            segments.append((prev, hole))
        prev = max(prev, (hole + 4) if hole < size else hole)
    for start, end in sorted(segments, key=lambda s: s[0] - s[1])[:6]:
        needle = bytes(body[start:end])
        weight = min(4, max(1, (end - start) // 10))
        hits = 0
        pos = exe.find(needle, text["raw_pointer"], text["raw_pointer"] + text["size"])
        while pos != -1 and hits < 300:
            votes[text["rva"] + pos - text["raw_pointer"] - start] += weight
            hits += 1
            pos = exe.find(needle, pos + 1, text["raw_pointer"] + text["size"])

    ranked = [(v, rva) for rva, v in votes.items()
              if rva not in matched_rvas and text["rva"] <= rva < text["rva"] + text["size"]]
    ranked.sort(reverse=True)
    return ranked[:3]


def disasm(data):
    """objdump a raw i386 blob -> [(mnemonic, normalized-operands, raw-operands)]."""
    tmp = SCRATCH / "blob.bin"
    tmp.write_bytes(data)
    out = subprocess.run(["objdump", "-b", "binary", "-m", "i386", "-M", "intel", "-D",
                          str(tmp)], capture_output=True, text=True).stdout
    instrs = []
    for line in out.splitlines():
        m = re.match(r"\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s*(\S+)\s*(.*)", line)
        if m:
            mnem, ops = m.group(1), m.group(2).strip()
            instrs.append((mnem, re.sub(r"0x[0-9a-f]+|\b\d+\b", "#", ops), ops))
    return instrs


def mask(data, holes, size):
    out = bytearray(data[:size])
    for hole in holes:
        for i in range(hole, min(hole + 4, size)):
            out[i] = 0
    return bytes(out)


def classify(exe, pe, body, relocs, cand_rva, ghidra):
    size = len(body)
    tsize = ghidra.get(cand_rva, size)
    holes = [off for off, rt, _ in relocs if rt in (0x0006, 0x0014) and off < size]
    toff = build.rva_to_file_offset(pe, cand_rva)
    target = exe[toff : toff + tsize]

    cmp_masked = mask(body, holes, min(size, tsize))
    tgt_masked = mask(target, holes, min(size, tsize))
    same = sum(1 for a, b in zip(cmp_masked, tgt_masked) if a == b)
    pct = same * 100 // max(len(cmp_masked), 1)
    first = next((i for i, (a, b) in enumerate(zip(cmp_masked, tgt_masked)) if a != b), -1)

    ci = disasm(mask(body, holes, size))
    ti = disasm(mask(target, holes, tsize))
    if not ci or not ti:
        return pct, first, "structural", "disasm failed"

    if len(ci) == len(ti):
        imm = reg = shape = 0
        example = ""
        for (cm, cn, cr), (tm, tn, tr) in zip(ci, ti):
            if cm != tm:
                shape += 1
            elif cn == tn and cr != tr:
                imm += 1
                if not example:
                    example = f"{cm} {cr} vs {tr}"
            elif cn != tn:
                reg_only = re.sub(r"\be[a-z]{2}\b|\b[abcd][lh]\b", "R", cn) == \
                           re.sub(r"\be[a-z]{2}\b|\b[abcd][lh]\b", "R", tn)
                if reg_only:
                    reg += 1
                    if not example:
                        example = f"{cm} {cr} vs {tr}"
                else:
                    shape += 1
        if shape == 0 and reg == 0 and imm > 0:
            return pct, first, "immediate-only", f"{imm} literal(s): {example}"
        if shape == 0 and reg > 0 and imm == 0:
            return pct, first, "register-swap", f"{reg} instr(s): {example}"
        if shape == 0:
            return pct, first, "imm+reg", f"{imm} imm / {reg} reg: {example}"
    import difflib
    ratio = difflib.SequenceMatcher(None, [i[0] for i in ci], [i[0] for i in ti]).ratio()
    hint = f"shape ratio {ratio:.0%}, sizes {size}->{tsize}"
    return pct, first, "structural", hint


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--src", default="src/zh")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--min-size", type=int, default=24)
    args = ap.parse_args()

    SCRATCH.mkdir(parents=True, exist_ok=True)
    exe, pe, text, ghidra, matched_names, matched_rvas, symbol_map = load_world()
    print("prescanning call sites...", flush=True)
    call_sites = prescan_call_sites(exe, text)

    rows = []
    seen = {}   # name -> row index (inline COMDATs appear in every TU; report once)
    sources = sorted((ROOT / args.src).glob("*.cpp"))
    for src in sources:
        obj = build.BUILD_DIR / (src.stem + ".obj")
        if not obj.exists():
            rows.append((src.name, "?", 0, "", 0, "no-obj", -1, "run build.py first", 0))
            continue
        for name, span, relocs in object_functions(obj):
            if name in matched_names:
                continue
            if name in seen:
                continue
            seen[name] = True
            body = span.rstrip(b"\xcc")
            if len(body) < args.min_size:
                continue
            cands = find_candidates(exe, pe, text, body, relocs, symbol_map,
                                    call_sites, matched_rvas, obj)
            if not cands or cands[0][0] < 5:
                top = cands[0][0] if cands else 0
                klass = "absent" if top or len(body) >= 48 else "no-anchors"
                hint = "no plausible placement" if klass == "absent" else \
                       "too small/reloc-dense to anchor; needs manual look"
                rows.append((name, src.name, len(body), "", 0, klass, -1, hint, top))
                continue
            votes, rva = cands[0]
            pct, first, klass, hint = classify(exe, pe, body, relocs, rva, ghidra)
            rows.append((name, src.name, len(body), f"0x{rva:08X}", pct, klass, first, hint, votes))
            if args.limit and len(rows) >= args.limit:
                break
        if args.limit and len(rows) >= args.limit:
            break

    rows.sort(key=lambda r: (CLASS_ORDER.get(r[5], 9), -r[4]))
    REPORT.parent.mkdir(parents=True, exist_ok=True)
    with REPORT.open("w", newline="") as fh:
        w = csv.writer(fh)
        w.writerow(["function", "source", "size", "candidate_rva", "aligned_pct",
                    "class", "first_diff", "hint", "votes"])
        w.writerows(rows)

    by_class = Counter(r[5] for r in rows)
    print(f"\n{len(rows)} drifted functions classified -> {REPORT.relative_to(ROOT)}")
    for klass, n in sorted(by_class.items(), key=lambda kv: CLASS_ORDER.get(kv[0], 9)):
        print(f"  {klass:15s} {n}")
    print("\ntop of the mechanical queue (immediate-only, highest alignment):")
    for r in rows[:8]:
        if r[5] == "immediate-only":
            print(f"  {r[4]:3d}%  {r[0][:52]}  @{r[3]}  {r[7][:40]}")


if __name__ == "__main__":
    main()
