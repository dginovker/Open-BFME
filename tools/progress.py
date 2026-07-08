#!/usr/bin/env python3
"""Audit verified progress between two states of the repo.

The ONLY numbers that count as progress are matched rows in reverse/functions.csv
(each is byte-verified against retail by the build gates on every run). Source
text, present-unmatched markers, docs, and prose claims are NOT progress. Use
this to check any session's "done" claim in seconds:

  python3 tools/progress.py                # HEAD vs worktree
  python3 tools/progress.py REF            # REF vs worktree
  python3 tools/progress.py REF1..REF2     # between two commits
"""
import argparse
import csv
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"


def matched_at(ref):
    """(name, target_rva) -> (size, source) for matched rows at a git ref, or the
    worktree if ref is None. Keyed by address too: exact-ambiguous template copies
    are distinct rows sharing one mangled name, and an auditor must not collapse them."""
    if ref is None:
        text = (ROOT / FUNCTIONS).read_text(encoding="utf-8")
    else:
        proc = subprocess.run(
            ["git", "show", f"{ref}:{FUNCTIONS}"],
            cwd=ROOT, capture_output=True, text=True,
        )
        if proc.returncode != 0:
            raise SystemExit(f"cannot read {FUNCTIONS} at {ref}: {proc.stderr.strip()}")
        text = proc.stdout
    out = {}
    for row in csv.DictReader(text.splitlines()):
        if row["status"] == "matched":
            out[(row["name"], row["target_rva"])] = (int(row["target_size"]), row["source"])
    return out


def marker_delta(ref1, ref2):
    """Net present-unmatched/absent-from-retail marker lines added between the states."""
    cmd = ["git", "diff", ref1] + ([ref2] if ref2 else []) + ["--", "src"]
    diff = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True).stdout
    added = removed = 0
    for line in diff.splitlines():
        if line.startswith("+++") or line.startswith("---"):
            continue
        if "present-unmatched" in line or "absent-from-retail" in line:
            if line.startswith("+"):
                added += 1
            elif line.startswith("-"):
                removed += 1
    return added - removed


def area(source):
    parts = source.split("/")
    return "/".join(parts[:2]) if len(parts) > 1 else source


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("range", nargs="?", default="HEAD",
                    help="REF (vs worktree) or REF1..REF2 (default: HEAD vs worktree)")
    args = ap.parse_args()

    if ".." in args.range:
        ref1, _, ref2 = args.range.partition("..")
        ref2 = ref2 or None
    else:
        ref1, ref2 = args.range, None

    old = matched_at(ref1)
    new = matched_at(ref2)

    added = {n: new[n] for n in new.keys() - old.keys()}
    removed = {n: old[n] for n in old.keys() - new.keys()}
    markers = marker_delta(ref1, ref2)

    label2 = ref2 or "worktree"
    print(f"verified progress {ref1} -> {label2}")
    print(f"  matched functions: {len(old)} -> {len(new)}  "
          f"(+{len(added)}, -{len(removed)})")
    print(f"  matched bytes:     +{sum(s for s, _ in added.values())}"
          f"{'' if not removed else f'  (-{sum(s for s, _ in removed.values())} removed)'}")
    print(f"  unclaimed markers: {markers:+d}")

    if added:
        by_area = Counter()
        by_file = Counter()
        for size, source in added.values():
            by_area[area(source)] += 1
            by_file[source] += 1
        print("  by area: " + ", ".join(f"{a} +{n}" for a, n in by_area.most_common()))
        print("  top files:")
        for source, n in by_file.most_common(10):
            print(f"    +{n:<4d} {source}")
    if removed:
        print("  removed claims:")
        for (name, rva), (size, source) in sorted(removed.items())[:10]:
            print(f"    -{size:<5d} {source}  {name[:60]}")

    print("\nanything a session claims beyond these numbers is unverified prose.")


if __name__ == "__main__":
    main()
