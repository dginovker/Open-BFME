#!/usr/bin/env python3
"""Fail if any two tracked paths differ only in case.

Such a pair cannot coexist in a Windows/macOS working tree (case-insensitive
filesystems): git checks out one and silently drops the other, breaking the build
and emitting a "paths have collided" warning on clone. This guard runs in the
pre-commit hook so a colliding path can never reach master. Alternate-case sweep
shims are generated at build time (see gen_case_shims.py) and git-ignored, so they
are not tracked and never trip this check.
"""
import collections
import subprocess
import sys


def tracked_paths():
    out = subprocess.run(
        ["git", "ls-files"], capture_output=True, text=True, check=True
    ).stdout
    return [p for p in out.splitlines() if p]


def find_collisions(paths):
    by_lower = collections.defaultdict(list)
    for p in paths:
        by_lower[p.lower()].append(p)
    return [sorted(group) for group in by_lower.values() if len(group) > 1]


def main():
    collisions = find_collisions(tracked_paths())
    if not collisions:
        return 0
    print("case-only path collision (breaks Windows/macOS checkout):", file=sys.stderr)
    for group in sorted(collisions):
        print("  " + "  <->  ".join(group), file=sys.stderr)
    print(
        "rename one path so they differ by more than case, or (for a dual-case "
        "include shim) make one canonical and generate the other via "
        "tools/gen_case_shims.py.",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    sys.exit(main())
