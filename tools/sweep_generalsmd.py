#!/usr/bin/env python3
"""Batch-sweep GeneralsMD (Zero Hour) reference sources against the BFME binary.

BFME provably forks from ZH (reverse/zh_provenance/FINDINGS.md), so every reference
.cpp is a candidate: compile it against the reference's own engine headers (only the
Windows/SDK walls are shimmed — reference/shims/sweep/), then fingerprint-locate every
emitted function in the binary via tools/locate.py (unique masked placement + callee
validation; no export entry needed).

This converts porting from file-at-a-time archaeology into a pipeline: the report ranks
files by located functions (the winners to land), and aggregates compile blockers by
missing header/error so the shim can be grown where it pays.

Usage:
  python3 tools/sweep_generalsmd.py --area GameEngine/Source --limit 40
  python3 tools/sweep_generalsmd.py --files Snow ParabolicEase ObjectStatusTypes
  python3 tools/sweep_generalsmd.py --area GameEngine/Source        # full run
Report: reverse/zh_sweep/report.csv (appended incrementally, resumable via --skip-done)
"""
import argparse
import csv
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
SHIMS = ROOT / "reference" / "shims" / "sweep"
SCRATCH = ROOT / "build" / "zh_sweep"
REPORT = ROOT / "reverse" / "zh_sweep" / "report.csv"

# every sweep compile sees: shims first (PreRTS.h/windows.h shadowing), then the real engine tree
INCLUDE_DIRS = [
    SHIMS,
    REF / "GameEngine" / "Include",
    REF / "GameEngine" / "Source",
    REF / "Libraries" / "Include",
    REF / "Libraries" / "Source",
    REF / "Libraries" / "Source" / "WWVegas",
    REF / "Libraries" / "Source" / "WWVegas" / "WWLib",
    REF / "GameEngineDevice" / "Include",
    REF / "Libraries" / "Source" / "WWVegas" / "WW3D2",
    REF / "Libraries" / "Source" / "WWVegas" / "WWMath",
    REF / "Libraries" / "Source" / "WWVegas" / "WWDebug",
    REF / "Libraries" / "Source" / "WWVegas" / "WWSaveLoad",
]

HEAD = "// cl: /DNDEBUG /MD /EHsc\n// stlport\n#define Matrix4x4 Matrix4  // BFME renamed it\n"


def candidates(area, names):
    ported = {p.stem.lower() for p in ROOT.glob("src/**/*.cpp")}
    if names:
        out = []
        for name in names:
            hits = sorted(REF.rglob(f"{name}.cpp"))
            if not hits:
                print(f"  no reference file named {name}.cpp")
            out += hits
        return out
    return [p for p in sorted((REF / area).rglob("*.cpp")) if p.stem.lower() not in ported]


def sweep_one(ref_cpp):
    """Copy with recipe head into scratch, locate, and classify the outcome."""
    work = SCRATCH / (ref_cpp.stem.lower() + ".cpp")
    work.write_text(HEAD + ref_cpp.read_text(errors="replace"))
    cmd = [sys.executable, str(ROOT / "tools" / "locate.py"), str(work.relative_to(ROOT))]
    for inc in INCLUDE_DIRS:
        cmd += ["-I", str(inc)]
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=420)
    out = proc.stdout + proc.stderr

    summary = re.search(r"(\d+) located, (\d+) ambiguous, (\d+) unlocated", out)
    if summary:
        located, ambiguous, unlocated = map(int, summary.groups())
        rows = re.findall(r"^  (\?[^,]+,.*,matched,)$", out, re.M)
        return {"status": "ok", "located": located, "ambiguous": ambiguous,
                "unlocated": unlocated, "rows": rows, "blocker": ""}
    missing = re.search(r"Cannot open include file: '([^']+)'", out)
    if missing:
        return {"status": "missing-header", "located": 0, "ambiguous": 0, "unlocated": 0,
                "rows": [], "blocker": missing.group(1)}
    error = re.search(r"error (C\d+)\s*:\s*([^\r\n]{0,90})", out)
    if error:
        return {"status": "compile-error", "located": 0, "ambiguous": 0, "unlocated": 0,
                "rows": [], "blocker": f"{error.group(1)} {error.group(2)}"}
    return {"status": "unknown", "located": 0, "ambiguous": 0, "unlocated": 0,
            "rows": [], "blocker": out.strip()[-120:]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--area", default="GameEngine/Source")
    parser.add_argument("--files", nargs="*", help="sweep only these basenames")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--skip-done", action="store_true",
                        help="skip files already present in the report")
    args = parser.parse_args()

    SCRATCH.mkdir(parents=True, exist_ok=True)
    REPORT.parent.mkdir(parents=True, exist_ok=True)

    done = set()
    if args.skip_done and REPORT.exists():
        with REPORT.open(newline="") as handle:
            done = {row["file"] for row in csv.DictReader(handle)}

    todo = candidates(args.area, args.files)
    if args.limit:
        todo = todo[: args.limit]

    new_report = not REPORT.exists()
    blockers = Counter()
    winners = []
    with REPORT.open("a", newline="") as handle:
        writer = csv.writer(handle)
        if new_report:
            writer.writerow(["file", "status", "located", "ambiguous", "unlocated", "blocker"])
        for index, ref_cpp in enumerate(todo, 1):
            rel = str(ref_cpp.relative_to(REF))
            if rel in done:
                continue
            try:
                result = sweep_one(ref_cpp)
            except subprocess.TimeoutExpired:
                result = {"status": "timeout", "located": 0, "ambiguous": 0,
                          "unlocated": 0, "rows": [], "blocker": ""}
            writer.writerow([rel, result["status"], result["located"],
                             result["ambiguous"], result["unlocated"], result["blocker"]])
            handle.flush()
            if result["status"] in ("missing-header", "compile-error"):
                blockers[result["blocker"].split()[0]] += 1
            if result["located"]:
                winners.append((result["located"], rel))
                print(f"[{index}/{len(todo)}] {rel}: {result['located']} LOCATED"
                      + (f", {result['unlocated']} unlocated" if result["unlocated"] else ""))
            else:
                print(f"[{index}/{len(todo)}] {rel}: {result['status']}"
                      + (f" ({result['blocker']})" if result["blocker"] else ""))

    print("\n=== sweep summary ===")
    for located, rel in sorted(winners, reverse=True):
        print(f"  WINNER {located:3d}  {rel}")
    if blockers:
        print("top blockers (grow the shim here):")
        for blocker, count in blockers.most_common(12):
            print(f"  {count:4d}  {blocker}")


if __name__ == "__main__":
    main()
