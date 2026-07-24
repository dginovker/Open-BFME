#!/usr/bin/env python3
"""List MASM-dump rows that are 5-byte incremental-link thunks (`E9 rel32`) — the
cheapest clean-C++ opportunity. Each such dump only jumps to a real body that
clean C++ compiles to (see the AGENTS.md ladder); converting it turns a byte-blob
into source with no new RE. Grouped by class, largest cluster first.

Usage: python3 tools/list_thunk_dumps.py [--limit N]
"""
import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build


def klass(name):
    m = re.search(r"@([A-Za-z0-9_]+)@@", name)
    return m.group(1) if m else "(free function)"


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, default=40, help="max classes to print")
    args = ap.parse_args()

    thunks = []
    for r in build.load_all_function_rows():
        if "masm_dumps" not in r.get("source", ""):
            continue
        try:
            rva, size = int(r["target_rva"], 16), int(r["target_size"])
        except (ValueError, KeyError, TypeError):
            continue
        if size != 5:
            continue
        try:
            body = build.read_target_bytes(rva, 5)
        except Exception:
            continue
        if body[0] != 0xE9:
            continue
        dest = (rva + 5 + struct.unpack_from("<i", body, 1)[0]) & 0xFFFFFFFF
        thunks.append((klass(r["name"]), r["name"], dest))

    by_class = {}
    for cls, name, dest in thunks:
        by_class.setdefault(cls, []).append((name, dest))

    print(f"{len(thunks)} convertible thunk-dumps across {len(by_class)} classes "
          f"(body = the jump target clean C++ must reproduce):\n")
    for cls, items in sorted(by_class.items(), key=lambda kv: -len(kv[1]))[:args.limit]:
        ex_name, ex_dest = items[0]
        print(f"  {cls:32} {len(items):3}  e.g. {ex_name[:48]} -> 0x{ex_dest:06X}")
    print("\nConvert one: write its body's C++, repoint the row to your .cpp, "
          "delete the .asm, then `./build.sh <file>` to byte-verify.")


if __name__ == "__main__":
    main()
