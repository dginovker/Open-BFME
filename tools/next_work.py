#!/usr/bin/env python3
"""Answer "what should I work on right now": print only VALIDATED candidates, ranked,
each with the exact command that lands it. No network, no compiling — runs in seconds.

Sections, in priority order:
  0. Ledger health   tools/check_csv.py — a corrupt ledger aborts everything (exit 2)
  1. Sweep winners   report.csv files with landable functions not yet in src/zh/
                     -> python3 tools/land_zh.py <Basename>
  2. Drift quick wins  immediate-only / imm+reg literal fixes from drift_report.csv
  3. Shim unblocking  top compile blockers by count — grow reference/shims/sweep/
  4. Rest of the ladder (pointer commands only, nothing computed)

Parallel agents: export AGENT_SLOT=1..AGENT_POOL (pool defaults to 7) and sections
1-2 show only this agent's deterministic slice (zlib.crc32 of the item key mod pool).
Pass --any when your slot runs dry. --json emits every section machine-readable
(full lists; --limit shapes only the text output).

Usage:
  python3 tools/next_work.py [--limit 10] [--json] [--any]

Exit codes: 0 ok, 1 missing/bad inputs, 2 ledger corrupt.
"""
import argparse
import csv
import json
import os
import subprocess
import sys
import zlib
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
REPORT = ROOT / "reverse" / "zh_sweep" / "report.csv"
META = ROOT / "reverse" / "zh_sweep" / "report.meta"
DRIFT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
ATTEMPTS = ROOT / "reverse" / "re_attempts.log"

POINTERS = [
    ("python3 tools/land_ambiguous.py",
     "land string-anchored exact-ambiguous drift copies"),
    ("python3 tools/list_naked_candidates.py src --limit 20",
     "rank naked-asm functions worth decompiling to C++"),
]

FIX_INSTRUCTIONS = """\
LEDGER CORRUPT — fix this before doing anything else:
  1. python3 tools/dedup_csv.py
  2. byte-verify any remaining conflicting claims: python3 tools/build.py <source>
     for each claimant — the row that fails verification is the wrong one; delete it
  3. re-run: python3 tools/check_csv.py"""


def check_ledger():
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "check_csv.py")],
                          cwd=ROOT, capture_output=True, text=True)
    if proc.returncode != 0:
        sys.stderr.write(proc.stdout + proc.stderr)
        print(FIX_INSTRUCTIONS, file=sys.stderr)
        raise SystemExit(2)
    return proc.stdout.strip()


def sweep_staleness():
    """report.meta records the sha the sweep ran at. Advisory only — never blocks."""
    if not META.exists():
        return None
    try:
        ref = json.loads(META.read_text())["ref"]
    except (ValueError, KeyError) as exc:
        return f"report.meta is unreadable ({exc}) — cannot judge sweep staleness"
    known = subprocess.run(["git", "-C", str(ROOT), "rev-parse", "--verify", "--quiet",
                            f"{ref}^{{commit}}"], capture_output=True)
    if known.returncode != 0:
        return f"sweep ran at {ref}, unknown in this clone — staleness unknown"
    ancestor = subprocess.run(["git", "-C", str(ROOT), "merge-base", "--is-ancestor",
                               ref, "HEAD"], capture_output=True)
    behind = subprocess.run(["git", "-C", str(ROOT), "rev-list", "--count",
                             f"{ref}..HEAD"], capture_output=True, text=True).stdout.strip()
    if ancestor.returncode == 0:
        return f"sweep ran at {ref}, {behind} commit(s) behind HEAD"
    return (f"sweep ran at {ref}, which is NOT an ancestor of HEAD — results may not "
            f"reflect this branch; re-sweep: python3 tools/sweep_generalsmd.py")


def read_csv(path, regen):
    if not path.exists():
        raise SystemExit(f"{path.relative_to(ROOT)} is missing — regenerate it: {regen}")
    with path.open(newline="") as fh:
        reader = csv.DictReader(fh)
        rows, header_dups = [], 0
        for row in reader:
            if row[reader.fieldnames[0]] == reader.fieldnames[0]:
                header_dups += 1  # union-merge damage: a second header line mid-file
                continue
            rows.append(row)
    if header_dups:
        print(f"warning: {path.relative_to(ROOT)} contains {header_dups} repeated "
              f"header line(s) (bad merge) — ignored", file=sys.stderr)
    return reader.fieldnames, rows


def to_int(value, base, what):
    try:
        return int(value, base) if base != 10 else int(value)
    except ValueError:
        raise SystemExit(f"{what}: bad value {value!r} — regenerate the report")


def sweep_winners(mine):
    """report.csv is appended incrementally across re-sweeps: the LAST row per file
    is the current truth (663 files carry stale earlier rows)."""
    fields, rows = read_csv(REPORT, "python3 tools/sweep_generalsmd.py --area GameEngine/Source")
    has_landable = "landable" in fields
    last = {}
    for row in rows:
        last[row["file"]] = row
    legacy_ported = {p.stem.casefold() for p in (ROOT / "src" / "zh").glob("*.cpp")}
    code_root = ROOT / "Code"
    landed_paths = {
        p.relative_to(code_root).as_posix().casefold()
        for p in code_root.rglob("*.cpp")
    }
    out = []
    for file, row in last.items():
        if row["status"] != "ok":
            continue
        score = (to_int(row["landable"], 10, f"report.csv landable for {file}")
                 if has_landable and row.get("landable", "") != ""
                 else to_int(row["located"], 10, f"report.csv located for {file}"))
        if (score < 1
                or Path(file).stem.casefold() in legacy_ported
                or file.casefold() in landed_paths
                or not mine(file)):
            continue
        if not (REF / file).exists():
            print(f"warning: report.csv names a missing reference file, skipped: {file}",
                  file=sys.stderr)
            continue
        out.append({"file": file, "landable": score, "located": int(row["located"]),
                    "ambiguous": int(row["ambiguous"]), "unlocated": int(row["unlocated"]),
                    "command": f"python3 tools/land_zh.py {Path(file).stem}"})
    out.sort(key=lambda c: (-c["landable"], c["file"]))
    return out, last


def drift_quick_wins(mine):
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    claimed = set()
    with FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                claimed.add(int(row["target_rva"], 16))  # check_csv validated these
    last = {}
    for row in rows:
        if row["class"] in ("immediate-only", "imm+reg"):
            last[row["function"]] = row
    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        if rva in claimed or not mine(name):
            continue
        rel = resolve_drift_source(row["source"])
        if rel is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        out.append({"function": name, "source": rel,
                    "class": row["class"], "aligned_pct": int(row["aligned_pct"]),
                    "candidate_rva": row["candidate_rva"], "hint": row["hint"],
                    "command": f"python3 tools/build.py {rel}"})
    out.sort(key=lambda c: (-c["aligned_pct"], c["function"]))
    return out


def read_attempts():
    """reverse/re_attempts.log (TSV: function, outcome, note — tools/log_attempt.py).
    Returns {function: {"n": count, "dead": bool, "last": note}}."""
    out = {}
    if not ATTEMPTS.exists():
        return out
    for line in ATTEMPTS.read_text(encoding="utf-8").splitlines():
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        entry = out.setdefault(parts[0], {"n": 0, "dead": False, "last": ""})
        entry["n"] += 1
        if parts[1] == "dead":
            entry["dead"] = True
        if len(parts) > 2:
            entry["last"] = parts[2]
    return out


def resolve_drift_source(basename):
    """drift_report source column is a bare basename; landed files live under
    Code/ (official tree layout); a few remainders sit under src/."""
    hits = sorted(ROOT.glob(f"Code/**/{basename}")) + sorted(ROOT.glob(f"src/**/{basename}"))
    return hits[0].relative_to(ROOT).as_posix() if hits else None


def structural_candidates(mine, claimed, claimed_names, attempts, big=False):
    """The manual-RE tier: drifted functions whose source exists but whose code
    shape differs (class structural / register-swap). Workflow: docs/structural.md."""
    _, rows = read_csv(DRIFT, "python3 tools/drift_classify.py")
    last = {}
    for row in rows:
        if row["class"] in ("structural", "register-swap"):
            last[row["function"]] = row
    out = []
    for name, row in last.items():
        rva = to_int(row["candidate_rva"], 16, f"drift_report.csv candidate_rva for {name}")
        # candidate_rva is an alignment vote and can be shifted a few bytes from
        # the real start, so a matched function may not hit the rva filter —
        # the name filter catches those stale rows (proven live: insertTee...)
        if rva in claimed or name in claimed_names or not mine(name):
            continue
        att = attempts.get(name, {"n": 0, "dead": False, "last": ""})
        if att["dead"] or att["n"] >= 3:
            continue
        source = resolve_drift_source(row["source"])
        if source is None:
            print(f"warning: drift_report.csv row for {name} names a missing source "
                  f"{row['source']} — stale report, skipped", file=sys.stderr)
            continue
        out.append({"function": name, "source": source, "class": row["class"],
                    "aligned_pct": int(row["aligned_pct"]), "size": int(row["size"]),
                    "candidate_rva": row["candidate_rva"], "hint": row["hint"],
                    "attempts": att["n"], "last_attempt": att["last"],
                    "command": (f"python3 tools/explain_mismatch.py '{name}' "
                                f"--rva {row['candidate_rva']} --size {row['size']} "
                                f"--source {source}")})
    if big:
        # byte-yield mode: biggest functions first (still gated by alignment)
        out.sort(key=lambda c: (-c["size"], -c["aligned_pct"], c["function"]))
    else:
        # highest alignment first (closest to matching), small before big at equal alignment
        out.sort(key=lambda c: (-c["aligned_pct"], c["size"], c["function"]))
    return out


def shim_blockers(last_report_rows):
    counts, examples = Counter(), {}
    for row in last_report_rows.values():
        if row["blocker"]:
            counts[row["blocker"]] += 1
            examples.setdefault(row["blocker"], []).append(Path(row["file"]).name)
    return [{"blocker": blocker, "files": n, "examples": examples[blocker][:3]}
            for blocker, n in counts.most_common(8)]


def partition_env():
    slot_s = os.environ.get("AGENT_SLOT")
    if slot_s is None:
        return None, None
    pool_s = os.environ.get("AGENT_POOL", "7")
    try:
        slot, pool = int(slot_s), int(pool_s)
    except ValueError:
        raise SystemExit(f"AGENT_SLOT/AGENT_POOL must be integers "
                         f"(got AGENT_SLOT={slot_s!r}, AGENT_POOL={pool_s!r})")
    if pool < 1 or not 1 <= slot <= pool:
        raise SystemExit(f"need 1 <= AGENT_SLOT <= AGENT_POOL (got slot={slot}, pool={pool})")
    return slot, pool


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, default=10,
                    help="max items printed per section (text output only; default 10)")
    ap.add_argument("--json", action="store_true",
                    help="machine-readable dump of all sections (full lists, no --limit)")
    ap.add_argument("--any", action="store_true",
                    help="ignore AGENT_SLOT partitioning (when your slot runs dry)")
    ap.add_argument("--tier", choices=("harvest", "structural"),
                    help="show only that tier's sections (structural agents pass "
                         "--tier structural for a deeper list)")
    ap.add_argument("--big", action="store_true",
                    help="sort structural candidates by size (byte yield) instead of alignment")
    args = ap.parse_args()

    ledger = check_ledger()  # exit 2 happens in there; nothing below matters if red
    slot, pool = partition_env()
    filtered = slot is not None and not args.any
    mine = (lambda key: zlib.crc32(key.encode("utf-8")) % pool == slot - 1) if filtered \
        else (lambda key: True)

    staleness = sweep_staleness()
    winners, last_report = sweep_winners(mine)
    drifts = drift_quick_wins(mine)
    claimed, claimed_names = set(), set()
    with FUNCTIONS.open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["target_rva"]:
                claimed.add(int(row["target_rva"], 16))
                claimed_names.add(row["name"])
    structural = structural_candidates(mine, claimed, claimed_names, read_attempts(),
                                       big=args.big)
    blockers = shim_blockers(last_report)

    if args.json:
        print(json.dumps({
            "ledger": ledger, "sweep_meta": staleness,
            "slot": slot, "pool": pool, "filtered": filtered,
            "sweep_winners": winners, "drift_quick_wins": drifts,
            "structural": structural,
            "shim_blockers": blockers,
            "pointers": [cmd for cmd, _ in POINTERS],
        }, indent=2))
        return

    print("== 0. ledger health ==")
    print(f"  {ledger}")
    if staleness:
        print(f"  {staleness}")
    if filtered:
        print(f"  [slot {slot}/{pool}: sections 1-2 show only this agent's slice; "
              f"--any shows everything]")

    if args.tier != "structural":
        print(f"\n== 1. sweep winners still landable ({len(winners)}) ==")
        for c in winners[:args.limit]:
            print(f"  landable {c['landable']:>2}  {c['file']}")
            print(f"               {c['command']}")

        print(f"\n== 2. drift quick wins: literal-only diffs ({len(drifts)}) ==")
        for c in drifts[:args.limit]:
            print(f"  {c['aligned_pct']:>3}% {c['class']:<14} {c['function']}")
            print(f"       {c['source']} @ {c['candidate_rva']}  hint: {c['hint']}")
            print(f"       fix the literal in source, then byte-verify: {c['command']}")

    if args.tier != "harvest":
        shown = structural[:args.limit if args.tier != "structural" else args.limit * 3]
        print(f"\n== 2b. structural reconciliation — manual RE ({len(structural)}; "
              f"workflow: docs/structural.md) ==")
        for c in shown:
            tried = f"  [tried {c['attempts']}x: {c['last_attempt']}]" if c["attempts"] else ""
            print(f"  {c['aligned_pct']:>3}% {c['size']:>5}B {c['function']}{tried}")
            print(f"       {c['source']} @ {c['candidate_rva']}  hint: {c['hint']}")
            print(f"       start: {c['command']}")
        if structural:
            print("       log every attempt: python3 tools/log_attempt.py '<symbol>' "
                  "<landed|no-match|dead|blocked> 'what you tried'")

    if args.tier == "structural":
        return

    print(f"\n== 3. shim unblocking (top {len(blockers)} blockers) ==")
    for b in blockers:
        print(f"  grow reference/shims/sweep/ to unblock {b['files']:>3} files: "
              f"{b['blocker']}  (e.g. {', '.join(b['examples'])})")
    if blockers:
        print("  then re-sweep the unblocked files: python3 tools/sweep_generalsmd.py")

    print("\n== 4. rest of the ladder ==")
    for cmd, why in POINTERS:
        print(f"  {cmd:<55} # {why}")


if __name__ == "__main__":
    main()
