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
Report: reverse/zh_sweep/report.csv (appended incrementally, resumable via --skip-done).
The landable column counts located functions big enough for land_zh's locate --emit;
report.meta records the git HEAD the report reflects.
"""
import argparse
import csv
import json
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from locate import MIN_SIZE_DEFAULT

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
SHIMS = ROOT / "reference" / "shims" / "sweep"
SCRATCH = ROOT / "build" / "zh_sweep"
REPORT = ROOT / "reverse" / "zh_sweep" / "report.csv"
META = ROOT / "reverse" / "zh_sweep" / "report.meta"
REPORT_FIELDS = ["file", "status", "located", "ambiguous", "unlocated", "blocker", "landable"]

# every sweep compile sees: shims first (PreRTS.h/windows.h shadowing), then the real engine tree
INCLUDE_DIRS = [
    SHIMS,
    REF / "GameEngine" / "Include",
    REF / "GameEngine" / "Include" / "GameNetwork",
    REF / "GameEngine" / "Source",
    REF / "Libraries" / "Include",
    REF / "Libraries" / "Source",
    REF / "Libraries" / "Source" / "debug",
    REF / "Libraries" / "Source" / "Compression",
    REF / "Libraries" / "Source" / "WWVegas",
    REF / "Libraries" / "Source" / "WWVegas" / "WWLib",
    REF / "GameEngineDevice" / "Include",
    REF / "Libraries" / "Source" / "WWVegas" / "WW3D2",
    REF / "Libraries" / "Source" / "WWVegas" / "WWMath",
    REF / "Libraries" / "Source" / "WWVegas" / "WWDebug",
    REF / "Libraries" / "Source" / "WWVegas" / "WWSaveLoad",
    REF / "Main",
]

HEAD = "// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc\n// stlport\n#define Matrix4x4 Matrix4  // BFME renamed it\n#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves\n"


def candidates(area, names):
    legacy_ported = {p.stem.casefold() for p in ROOT.glob("src/**/*.cpp")}
    code_root = ROOT / "Code"
    landed_paths = {
        p.relative_to(code_root).as_posix().casefold()
        for p in code_root.rglob("*.cpp")
    }
    if names:
        out = []
        for name in names:
            # accept both Foo and Foo.cpp — agents paste either form
            stem = name[:-4] if name.lower().endswith(".cpp") else name
            hits = sorted(REF.rglob(f"{stem}.cpp"))
            if not hits:
                print(f"  no reference file named {stem}.cpp")
            out += hits
        return out
    return [
        p
        for p in sorted((REF / area).rglob("*.cpp"))
        if p.stem.casefold() not in legacy_ported
        and p.relative_to(REF).as_posix().casefold() not in landed_paths
        and not p.name.startswith(".sweep_")
    ]


def sweep_one(ref_cpp):
    """Copy with recipe head beside the original (so quoted sibling includes
    resolve exactly as the real compile did), locate, and classify."""
    work = ref_cpp.parent / (".sweep_" + ref_cpp.name)
    work.write_text(HEAD + ref_cpp.read_text(errors="replace"))
    try:
        cmd = [sys.executable, str(ROOT / "tools" / "locate.py"), str(work.relative_to(ROOT))]
        for inc in INCLUDE_DIRS:
            cmd += ["-I", str(inc)]
        proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=420)
        out = proc.stdout + proc.stderr
    finally:
        work.unlink(missing_ok=True)

    summary = re.search(r"(\d+) located, (\d+) ambiguous, (\d+) unlocated", out)
    if summary:
        located, ambiguous, unlocated = map(int, summary.groups())
        # located rows at or above land_zh's locate --emit threshold actually land
        sizes = re.findall(r"^  \S+,[^,]*,0x[0-9A-Fa-f]+,(\d+),\S+,matched,$", out, re.M)
        landable = sum(1 for size in sizes if int(size) >= MIN_SIZE_DEFAULT)
        return {"status": "ok", "located": located, "ambiguous": ambiguous,
                "unlocated": unlocated, "landable": landable, "blocker": ""}
    missing = re.search(r"Cannot open include file: '([^']+)'", out)
    if missing:
        return {"status": "missing-header", "located": 0, "ambiguous": 0, "unlocated": 0,
                "landable": 0, "blocker": missing.group(1)}
    error = re.search(r"error (C\d+)\s*:\s*([^\r\n]{0,90})", out)
    if error:
        return {"status": "compile-error", "located": 0, "ambiguous": 0, "unlocated": 0,
                "landable": 0, "blocker": f"{error.group(1)} {error.group(2)}"}
    return {"status": "unknown", "located": 0, "ambiguous": 0, "unlocated": 0,
            "landable": 0, "blocker": out.strip()[-120:]}


def upgrade_report_header():
    """Reports written before the landable column exist in the wild; rewrite them
    in place (landable empty on old rows = unknown) so appends stay aligned."""
    if not REPORT.exists():
        return
    with REPORT.open(newline="") as handle:
        rows = list(csv.reader(handle))
    if not rows or "landable" in rows[0]:
        return
    if rows[0] != REPORT_FIELDS[:-1]:
        raise SystemExit(f"{REPORT}: unexpected header {rows[0]}, refusing to rewrite")
    with REPORT.open("w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(REPORT_FIELDS)
        writer.writerows(row + [""] for row in rows[1:])


def write_meta():
    ref = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, check=True,
                         capture_output=True, text=True).stdout.strip()
    META.write_text(json.dumps({"ref": ref}) + "\n")
    print(f"wrote {META.relative_to(ROOT)} (ref {ref[:12]})")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--area", default="GameEngine/Source")
    parser.add_argument("--files", nargs="*", help="sweep only these basenames (.cpp optional)")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--skip-done", action="store_true",
                        help="skip files already present in the report")
    args = parser.parse_args()

    SCRATCH.mkdir(parents=True, exist_ok=True)
    REPORT.parent.mkdir(parents=True, exist_ok=True)
    upgrade_report_header()

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
            writer.writerow(REPORT_FIELDS)
        for index, ref_cpp in enumerate(todo, 1):
            rel = str(ref_cpp.relative_to(REF))
            if rel in done:
                continue
            try:
                result = sweep_one(ref_cpp)
            except subprocess.TimeoutExpired:
                result = {"status": "timeout", "located": 0, "ambiguous": 0,
                          "unlocated": 0, "landable": 0, "blocker": ""}
            writer.writerow([rel, result["status"], result["located"], result["ambiguous"],
                             result["unlocated"], result["blocker"], result["landable"]])
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
    # lets downstream tools (e.g. next_work.py) tell what HEAD the report reflects
    write_meta()


if __name__ == "__main__":
    main()
