#!/usr/bin/env python3
"""Append ONE matched row to reverse/functions.csv, safely.

Hand-editing the ledger has repeatedly corrupted it (LF damage, wrong column
counts, duplicate/overlapping claims). This tool is the safe path: it validates
the claim against the existing ledger, appends in binary mode with CRLF, strips
the source's `// <name> present-unmatched` marker, and byte-verifies the result
with ./build.sh — reverting everything if verification fails. A row never
survives unverified (unless you explicitly pass --no-verify).

Usage:
  python3 tools/add_match.py <mangled-name> <target_rva> <target_size> <source> \\
      [--notes TEXT] [--no-verify] [--root DIR]
"""
import argparse
import csv
import fcntl
import io
import re
import subprocess
import sys
from pathlib import Path

DEFAULT_ROOT = Path(__file__).resolve().parents[1]

MARKER_RE = re.compile(r"^\s*//\s*(\S+)\s+present-unmatched\b")


def fail(*lines):
    for line in lines:
        print(f"add_match: {line}", file=sys.stderr)
    raise SystemExit(1)


def parse_ledger(raw):
    """Strict parse: any malformed row means the ledger is already corrupt and
    our duplicate/overlap validations cannot be trusted — refuse to append."""
    text = raw.decode("utf-8", errors="replace")
    rows = []
    for i, r in enumerate(csv.reader(io.StringIO(text)), start=1):
        if i == 1 or not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            fail(f"functions.csv line {i} has {len(r)} fields, expected 7: {r[:3]}...",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        name, _export, target_rva, target_size, source, status, _notes = r
        try:
            rva = int(target_rva, 16)
        except ValueError:
            fail(f"functions.csv line {i} ({name}): unparseable target_rva '{target_rva}'",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        try:
            size = int(target_size) if target_size else 0
        except ValueError:
            fail(f"functions.csv line {i} ({name}): unparseable target_size '{target_size}'",
                 "the ledger is corrupt — fix it first: python3 tools/check_csv.py")
        rows.append({"line": i, "name": name, "rva": rva, "size": size,
                     "source": source, "status": status})
    return rows


def strip_marker(source_path, name):
    """Remove the `// <token> present-unmatched` line whose token is the full
    mangled name or a prefix of it (markers are often truncated at a @@, e.g.
    `// ?getUnicodeString@Dict@@ present-unmatched`). Byte-level line surgery so
    the file's own line endings survive untouched. Returns new bytes or None."""
    raw = source_path.read_bytes()
    lines = raw.splitlines(keepends=True)
    exact, prefix = [], []
    for index, line in enumerate(lines):
        match = MARKER_RE.match(line.decode("utf-8", errors="replace"))
        if not match:
            continue
        token = match.group(1)
        if token == name:
            exact.append(index)
        elif name.startswith(token):
            prefix.append(index)
    candidates = exact or prefix
    if not candidates:
        return None
    victim = candidates[0]
    stripped = lines[victim].rstrip(b"\r\n").decode("utf-8", errors="replace")
    print(f"add_match: stripping marker at {source_path.name}:{victim + 1}: {stripped.strip()}")
    return b"".join(lines[:victim] + lines[victim + 1:])


def lookup_export_rva(root, name):
    exports = root / "reverse" / "exports.csv"
    if not exports.exists():
        # exports.csv is generated (gitignored); its absence only costs the
        # optional export_rva column, so say so instead of silently omitting
        print("add_match: note: reverse/exports.csv not present — export_rva left empty")
        return ""
    with exports.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] == "code" and row["name"] == name:
                return row["rva"]
    return ""


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("name", help="decorated (mangled) symbol name")
    parser.add_argument("target_rva", help="RVA of the function body, hex (0x...)")
    parser.add_argument("target_size", help="function size in bytes, decimal")
    parser.add_argument("source", help="repo-relative source path (src/...)")
    parser.add_argument("--notes", default="", help="notes column text (no commas)")
    parser.add_argument("--icf-owner", help="existing matched symbol at the same RVA and size; "
                        "allows a verified identical-code-folding alias")
    parser.add_argument("--no-verify", action="store_true",
                        help="skip ./build.sh verification (row lands UNVERIFIED — "
                             "verify before committing)")
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                        help="TEST-ONLY: operate on a copy of the repo rooted here "
                             "instead of the live ledger (default: repo root)")
    args = parser.parse_args()

    root = args.root.resolve()
    functions_csv = root / "reverse" / "functions.csv"
    if not functions_csv.exists():
        fail(f"no ledger at {functions_csv}")

    name = args.name
    try:
        rva = int(args.target_rva, 16)
    except ValueError:
        fail(f"target_rva '{args.target_rva}' is not hex (expected e.g. 0x00812340)")
    try:
        size = int(args.target_size)
    except ValueError:
        fail(f"target_size '{args.target_size}' is not a decimal byte count")
    if size <= 0:
        fail(f"target_size must be positive, got {size}")

    source_rel = args.source.lstrip("./") if not Path(args.source).is_absolute() else None
    if source_rel is None:
        try:
            source_rel = Path(args.source).resolve().relative_to(root).as_posix()
        except ValueError:
            fail(f"source {args.source} is not under {root}")
    source_path = root / source_rel
    if not source_path.exists():
        fail(f"source does not exist: {source_path}",
             "a ledger row must never point at a missing file")

    for label, value in [("name", name), ("source", source_rel), ("--notes", args.notes)]:
        bad = set(value) & set(',"\r\n')
        if bad:
            fail(f"{label} contains {sorted(bad)} — functions.csv rows are raw "
                 "comma-joined fields with no quoting, this would corrupt the ledger")

    # Exclusive lock across validate->append->verify so concurrent agents cannot
    # interleave appends or double-claim, and so revert-on-failure cannot clobber
    # a row someone else appended meanwhile.
    lock_file = (root / "reverse" / ".add_match.lock").open("a")
    try:
        fcntl.flock(lock_file, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except OSError:
        print("add_match: waiting for ledger lock (another add_match is running)...")
        fcntl.flock(lock_file, fcntl.LOCK_EX)

    raw = functions_csv.read_bytes()
    if b"\r\n" not in raw[:200]:
        fail("functions.csv has lost its CRLF line endings — restore it from git "
             "before appending (see python3 tools/check_csv.py)")
    if not raw.endswith(b"\n"):
        fail("functions.csv does not end with a newline (truncated last row?) — "
             "fix the ledger before appending")

    rows = parse_ledger(raw)
    new_end = rva + size
    icf_owner = None
    if args.icf_owner:
        owners = [row for row in rows if row["name"] == args.icf_owner]
        if len(owners) != 1:
            fail(f"--icf-owner {args.icf_owner} must name exactly one existing row")
        icf_owner = owners[0]
        if (icf_owner["status"] != "matched" or icf_owner["rva"] != rva or
                icf_owner["size"] != size):
            fail(f"--icf-owner {args.icf_owner} is not a matched {size}-byte claim "
                 f"at 0x{rva:08X}")
    for row in rows:
        same_icf_group = (icf_owner is not None and row["status"] == "matched" and
                          row["rva"] == rva and row["size"] == size)
        if row["rva"] == rva:
            if same_icf_group:
                continue
            fail(f"target_rva 0x{rva:08X} is already claimed by {row['name']} "
                 f"({row['source']}, {row['status']}, line {row['line']})")
        if row["status"] == "matched" and row["rva"] < new_end and rva < row["rva"] + row["size"]:
            if same_icf_group:
                continue
            fail(f"range [0x{rva:08X}, 0x{new_end:08X}) overlaps matched row "
                 f"{row['name']} [0x{row['rva']:08X}, 0x{row['rva'] + row['size']:08X}) "
                 f"({row['source']}, line {row['line']})")
    claims = [row for row in rows if row["name"] == name]
    if claims:
        addresses = ", ".join(f"0x{row['rva']:08X} ({row['source']}, {row['status']})"
                              for row in claims)
        fail(f"{name} is already in the ledger at {addresses}",
             "one name = one address; the only legit double-linked names "
             "(realcrc.cpp) already have both rows")

    export_rva = lookup_export_rva(root, name)
    ledger_row = f"{name},{export_rva},0x{rva:08X},{size},{source_rel},matched,{args.notes}"

    saved_source = source_path.read_bytes()
    new_source = strip_marker(source_path, name)
    if new_source is not None:
        source_path.write_bytes(new_source)

    with functions_csv.open("ab") as handle:
        handle.write(ledger_row.encode("utf-8") + b"\r\n")
    print(f"add_match: appended: {ledger_row}")

    if args.no_verify:
        print("add_match: --no-verify: row is UNVERIFIED — run "
              f"./build.sh {source_rel} before committing")
        return

    build_sh = root / "build.sh"
    if not build_sh.exists():
        # revert: an unverifiable row must not survive
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        fail(f"no build.sh at {root} — cannot verify; append reverted")

    print(f"add_match: verifying: ./build.sh {source_rel}")
    try:
        result = subprocess.run([str(build_sh), source_rel], cwd=root)
    except BaseException:
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        print("add_match: interrupted — append and marker strip REVERTED", file=sys.stderr)
        raise
    if result.returncode != 0:
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        fail(f"verification failed (exit {result.returncode}) — append and "
             "marker strip REVERTED; nothing was changed")
    print("add_match: verified OK — row is live")


if __name__ == "__main__":
    main()
