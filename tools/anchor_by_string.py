#!/usr/bin/env python3
"""Anchor callee-gated functions via their string-literal references.

masked-scan locate can only place a function that has a unique reloc-free byte
run or an already-known callee. Many functions have neither but DO reference a
distinctive string constant. reverse/string_xrefs.tsv maps each string to the
list of .text addresses that reference it. If our compiled function references
string S at byte-offset O, and the retail binary references S at exactly one
address A, then the retail function starts at A - O (modulo the operand-vs-
instruction convention, which we sweep). We emit that as a candidate row; the
byte comparison in build.py is the final judge, so a wrong guess simply fails.

Usage: anchor_by_string.py <source.cpp> [--emit]

Validated end-to-end: for matched functions that reference a unique string, the
recorded xref address equals the known function start (10/10 across ini/ffactory/
rawfile/crc/md5/mapper). ~1889 not-yet-matched function starts are addressable
this way. CAVEAT: `/DNDEBUG` strips WWASSERT so its *condition* strings never
reach the object — and retail stripped them too (they are absent from
string_xrefs.tsv), so they cannot anchor anything. The strings that DO anchor are
runtime strings (paths, format strings, .tga/.w3d/shader names, container labels
like `MeshMatDescClass::MaterialArray`). Those live mostly in the game-logic and
W3DDevice layers, so the highest-yield use is when a game/device .cpp is brought
up: run this first to pin its string-referencing functions, then let locate's
fixpoint cascade to their callees.
"""
import argparse, sys, csv, struct
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build, harvest

ROOT = Path(__file__).resolve().parents[1]


def load_string_xrefs():
    m = {}
    for line in (ROOT / "reverse" / "string_xrefs.tsv").read_text(errors="replace").splitlines():
        parts = line.split("\t")
        if len(parts) != 2:
            continue
        text, addrs = parts
        try:
            m[text] = [int(a, 16) for a in addrs.split(",") if a]
        except ValueError:
            pass
    return m


def object_string_symbols(obj_data):
    """Return {symbol_name: decoded_string} for .rdata string constants in the obj."""
    symbols = build.read_object_symbols(obj_data)
    section_count = build.u16(obj_data, 2)
    sections = []
    for i in range(section_count):
        off = 20 + i * 40
        sections.append({
            "name": obj_data[off:off + 8].rstrip(b"\0").decode("ascii", "replace"),
            "raw_size": build.u32(obj_data, off + 16),
            "raw_pointer": build.u32(obj_data, off + 20),
        })
    out = {}
    for s in symbols:
        if s["section"] <= 0:
            continue
        sec = sections[s["section"] - 1]
        if not sec["name"].startswith(".rdata") and not sec["name"].startswith(".data"):
            continue
        start = sec["raw_pointer"] + s["value"]
        raw = obj_data[start:sec["raw_pointer"] + sec["raw_size"]]
        end = raw.find(b"\0")
        if end <= 0:
            continue
        try:
            out[s["name"]] = raw[:end].decode("ascii")
        except UnicodeDecodeError:
            continue
    return out


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source")
    parser.add_argument("--emit", action="store_true")
    parser.add_argument("-I", dest="includes", action="append", default=[])
    args = parser.parse_args()
    emit = args.emit
    src = Path(args.source)

    obj = harvest.compile_obj(src if src.is_absolute() else ROOT / src, args.includes)
    obj_data = obj.read_bytes()
    strmap = object_string_symbols(obj_data)
    xrefs = load_string_xrefs()

    have = {r["name"] for r in csv.DictReader((ROOT / "reverse" / "functions.csv").open())}
    matched = {r["name"] for r in csv.DictReader((ROOT / "reverse" / "functions.csv").open()) if r["status"] == "matched"}

    candidates = {}  # name -> (rva, size, evidence)
    for sym in build.read_object_symbols(obj_data):
        name = sym["name"]
        if sym["section"] <= 0 or not name.startswith("?") or name in matched:
            continue
        try:
            body, relocs = build.read_object_symbol_bytes(obj, name)
        except ValueError:
            continue
        size = len(body.rstrip(b"\xcc"))
        if size < 8:
            continue
        # string_xrefs.tsv lists the *containing function's* start address for each
        # reference (validated: A == known start, 10/10). A string referenced from
        # exactly one function names that function's start directly (unique-string
        # anchor). When no single string is unique, the INTERSECTION of the address
        # sets of two or more strings this function references can still be a single
        # address — multi-string intersection anchoring, which reaches functions the
        # unique-string pass misses.
        votes = {}          # address -> how many unique strings vote for it
        ref_sets = []       # per-string candidate address sets (any multiplicity)
        for off, rtype, target in relocs:
            if rtype != 0x0006 or target not in strmap:  # DIR32 to a string
                continue
            text = strmap[target]
            if len(text) < 6 or text not in xrefs:
                continue
            addrs = xrefs[text]
            ref_sets.append(set(addrs))
            if len(addrs) == 1:
                votes.setdefault(addrs[0], 0)
                votes[addrs[0]] += 1
        if votes:
            best = max(votes, key=votes.get)
            if 0x1000 <= best < 0xd00000:
                candidates[name] = (best, size, votes[best], "unique")
            continue
        # no unique string — try intersecting the address sets of 2+ shared strings
        if len(ref_sets) >= 2:
            inter = set.intersection(*ref_sets)
            if len(inter) == 1:
                best = next(iter(inter))
                if 0x1000 <= best < 0xd00000:
                    candidates[name] = (best, size, len(ref_sets), "intersect")

    if not candidates:
        print(f"{src.name}: no string anchors found")
        return

    print(f"{src.name}: {len(candidates)} string-anchor candidate(s)")
    for name, (rva, size, v, kind) in sorted(candidates.items(), key=lambda x: -x[1][2]):
        flag = " (in-csv)" if name in have else ""
        print(f"  0x{rva:06x} size~{size} {kind}={v} {name.split('@@')[0][:50]}{flag}")

    if emit:
        # Preserve every existing ledger byte: historical rows contain mixed
        # line endings, so decoding and rewriting creates unrelated churn.
        ledger = ROOT / "reverse" / "functions.csv"
        raw = ledger.read_bytes()
        newline = "\r\n" if b"\r\n" in raw else "\n"
        additions = []
        for name, (rva, size, v, kind) in candidates.items():
            if name in have:
                continue
            additions.append(f"{name},,0x{rva:08X},{size},{src.as_posix()},matched,string-anchored ({kind})")
        if additions:
            ledger.write_bytes(raw + (newline.join(additions) + newline).encode("utf-8"))
        print(f"emitted {len(additions)} candidate row(s) — run build.py to verify")


if __name__ == "__main__":
    main()
