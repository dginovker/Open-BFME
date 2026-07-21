#!/usr/bin/env python3
"""Land the drift report's `exact-ambiguous` functions: byte-identical template copies
locate.py refuses (unique-placement rule), disambiguated here by their string anchor.

Safety: only rows whose function carries a ??_C@ string DIR32 are emitted — the build's
verify_string_refs gate then PROVES the copy assignment (a wrong copy references the
wrong string content and fails the build loudly). Copies with no string reference stay
unassigned: byte-identical + anchorless means no evidence says which address is whose.

Usage: python3 tools/land_ambiguous.py [--report reverse/zh_sweep/drift_report.csv]
"""
import argparse
import csv
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from locate import object_functions

ROOT = build.ROOT


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--report", default="reverse/zh_sweep/drift_report.csv")
    ap.add_argument("--src-dir", default="Code")
    args = ap.parse_args()

    ghidra = {}
    with (ROOT / "reverse" / "ghidra_functions.csv").open(newline="") as fh:
        for row in csv.DictReader(fh):
            ghidra[int(row["rva"], 16)] = int(row["size"])
    matched = {r["name"] for r in build.load_all_function_rows()}

    todo = []
    with (ROOT / args.report).open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["class"] == "exact-ambiguous" or (
                row["aligned_pct"] == "100" and row["first_diff"] == "-1" and row["candidate_rva"]
            ):
                todo.append(row)

    by_source = {}
    for row in todo:
        by_source.setdefault(row["source"], []).append(row)

    emitted_total = 0
    for cpp_name, rows in sorted(by_source.items()):
        # drift report stores bare basenames (often lowercased); resolve under Code/
        src = ROOT / args.src_dir / cpp_name
        if not src.exists():
            want = Path(cpp_name).name.lower()
            hits = [h for h in (ROOT / args.src_dir).rglob("*.cpp") if h.name.lower() == want]
            src = hits[0] if hits else src
        if not src.exists():
            print(f"{cpp_name}: missing source — skipped")
            continue
        # ensure object exists via compile
        try:
            obj = build.obj_path(src)
            build.compile_source(src, obj)
        except (SystemExit, Exception) as e:
            # compile_source raises SystemExit (not Exception) on a bad compile;
            # catch both so one broken sweep source doesn't abort the whole batch.
            print(f"{cpp_name}: compile failed — skipped ({e})")
            continue
        if not obj.exists():
            print(f"{cpp_name}: missing obj — skipped")
            continue
        rel_src = str(src.relative_to(ROOT)).replace("\\", "/")
        has_string = {}
        sizes = {}
        for name, span, relocs in object_functions(obj):
            has_string[name] = any(rt == 0x0006 and sym.startswith("??_C@")
                                   for _, rt, sym in relocs)
            sizes[name] = len(span.rstrip(b"\xcc"))
        new_rows = []
        for row in rows:
            name = row["function"]
            if name in matched:
                continue
            if not has_string.get(name):
                print(f"  SKIP {name[:60]}: no string anchor — copy assignment unprovable")
                continue
            rva = int(row["candidate_rva"], 16)
            size = ghidra.get(rva, sizes.get(name, 0))
            new_rows.append(f"{name},,0x{rva:08X},{size},{rel_src},matched,"
                            f"exact-ambiguous copy; assignment proven by verify_string_refs")
        if not new_rows:
            continue
        with build.FUNCTIONS.open("a", encoding="utf-8", newline="") as fh:
            for line in new_rows:
                fh.write(line + "\n")
        verify = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"),
                                 rel_src],
                                cwd=ROOT, capture_output=True, text=True, timeout=420)
        if verify.returncode != 0:
            # revert this file's additions — fail loudly, land nothing unproven
            text = build.FUNCTIONS.read_text().splitlines(keepends=True)
            keep = [l for l in text if not any(l.startswith(r.split(",")[0] + ",") and
                                               f",{rel_src}," in l for r in new_rows)]
            build.FUNCTIONS.write_text("".join(keep))
            print(f"{cpp_name}: byte-verify REJECTED the assignment — reverted "
                  f"({(verify.stdout.strip().splitlines() or ['?'])[-1]})")
            continue
        emitted_total += len(new_rows)
        print(f"{cpp_name}: +{len(new_rows)} exact-ambiguous landed "
              f"({(verify.stdout.strip().splitlines() or [''])[-1]})")
    print(f"\ntotal landed: {emitted_total}")


if __name__ == "__main__":
    main()
