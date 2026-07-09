#!/usr/bin/env python3
"""Explain unresolved REL32 callees and suggest reverse/symbols.csv pins.

When ./build.sh fails with "unresolved call(s): <symbol>", the fix is a pin in
reverse/symbols.csv giving the address that call site encodes in the binary.
Deriving it by hand (compile, dump relocs, read the e8 displacement out of the
target bytes, look the RVA up) was re-rolled dozens of times overnight — this
tool does exactly that: it compiles the source the way build.py does, finds
every REL32 relocation whose symbol load_symbol_map() cannot resolve, decodes
the rel32 displacement from the TARGET bytes at the function's ledger RVA, and
prints the callee RVA, every name known for it (exports / functions.csv /
symbols.csv / ghidra inventory), and the ready-to-paste symbols.csv line.

Usage:
  python3 tools/decode_calls.py src/zh/foo.cpp                 # all ledger rows of the source
  python3 tools/decode_calls.py '?fn@Cls@@QAEXXZ'              # one function, source from its row
  python3 tools/decode_calls.py '?fn@Cls@@QAEXXZ' --rva 0x00812340 --source src/zh/foo.cpp
                                                               # candidate without a ledger row
"""
import argparse
import bisect
import csv
import os
import struct
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build


def fail(*lines):
    for line in lines:
        print(f"decode_calls: {line}", file=sys.stderr)
    raise SystemExit(1)


def load_ghidra(reverse_dir):
    path = reverse_dir / "ghidra_functions.csv"
    if not path.exists():
        fail(f"{path} not found — it is generated (see tools/ghidra/README.md) and "
             "required to name callee RVAs")
    table = {}
    with path.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            table[int(row["rva"], 16)] = (int(row["size"]), row["name"])
    return table, sorted(table)


def load_exports(reverse_dir):
    path = reverse_dir / "exports.csv"
    by_addr = {}
    if not path.exists():
        print(f"decode_calls: note: {path} not present — export names unavailable")
        return by_addr
    with path.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] != "code":
                continue
            for field in ("rva", "target_rva"):
                if row[field]:
                    by_addr.setdefault(int(row[field], 16), []).append(row["name"])
    return by_addr


def describe_rva(rva, names_at, ghidra, ghidra_starts, thunk_of):
    """Everything we know about an address: names pinned/matched/exported there,
    ghidra inventory entry, thunk->body relation, or the containing function when
    the address is NOT a function start (likely a bogus placement)."""
    known = list(dict.fromkeys(names_at.get(rva, [])))
    notes = []
    if rva in ghidra:
        size, gname = ghidra[rva]
        known.append(f"{gname} (ghidra, {size}B)")
    if rva in thunk_of:
        body = thunk_of[rva]
        body_names = names_at.get(body, [])
        notes.append(f"ILT thunk -> body 0x{body:08X}"
                     + (f" = {body_names[0]}" if body_names else ""))
    if rva not in ghidra:
        index = bisect.bisect_right(ghidra_starts, rva) - 1
        if index >= 0:
            start = ghidra_starts[index]
            size, gname = ghidra[start]
            if start < rva < start + size:
                notes.append(f"INSIDE ghidra function {gname} "
                             f"[0x{start:08X}+{size}] — likely an ILT thunk missing "
                             "from the inventory or a misidentified placement")
        if not notes:
            notes.append("no known function here — the row's target_rva or the "
                         "placement is probably wrong")
    return known, notes


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("what", help="source path (src/...) or decorated symbol name")
    parser.add_argument("--rva", help="where the function is believed to live (hex), "
                        "for candidates without a usable ledger row")
    parser.add_argument("--source", help="source file to compile when the symbol has "
                        "no ledger row (requires --rva)")
    parser.add_argument("--root", type=Path,
                        help="TEST-ONLY: read the ledgers from DIR/reverse instead of "
                             "the repo's (compile and exe stay in the repo)")
    args = parser.parse_args()

    reverse_dir = build.ROOT / "reverse"
    if args.root:
        reverse_dir = args.root.resolve() / "reverse"
        # build.py helpers read module globals; rebase just the ledgers so
        # load_symbol_map()/load_all_function_rows() see the test copy
        build.FUNCTIONS = reverse_dir / "functions.csv"
        build.SYMBOLS = reverse_dir / "symbols.csv"
        if not build.FUNCTIONS.exists():
            fail(f"--root: no ledger at {build.FUNCTIONS}")

    override_rva = None
    if args.rva:
        try:
            override_rva = int(args.rva, 16)
        except ValueError:
            fail(f"--rva '{args.rva}' is not hex")

    rows = build.load_all_function_rows()
    is_source = "/" in args.what or args.what.endswith((".cpp", ".h"))
    # (name, rva, row_size or None, source, status)
    if is_source:
        source_rel = args.what.lstrip("./")
        targets = [(r["name"], int(r["target_rva"], 16),
                    int(r["target_size"]) if r["target_size"] else 0,
                    r["source"], r["status"])
                   for r in rows if r["source"] == source_rel]
        if not targets:
            fail(f"no ledger rows for {source_rel} — decode needs a target_rva per "
                 "function; run it on a symbol with --rva/--source, or add rows first")
        if override_rva is not None:
            fail("--rva only makes sense with a single symbol, not a whole source")
    else:
        name = args.what
        my_rows = [r for r in rows if r["name"] == name]
        if my_rows:
            r = my_rows[0]
            rva = override_rva if override_rva is not None else int(r["target_rva"], 16)
            targets = [(name, rva, int(r["target_size"]) if r["target_size"] else 0,
                        r["source"], r["status"])]
            source_rel = r["source"]
        else:
            if override_rva is None:
                fail(f"{name} has no ledger row and no --rva was given — without an "
                     "address there are no target bytes to decode",
                     "pass --rva 0x... (and --source src/...) for an unmatched candidate")
            if not args.source:
                fail(f"{name} has no ledger row, so its source is unknown — "
                     "pass --source src/... along with --rva")
            source_rel = args.source.lstrip("./")
            targets = [(name, override_rva, 0, source_rel, "no-ledger-row")]

    source = build.ROOT / source_rel
    if not source.exists():
        fail(f"source does not exist: {source}")

    obj = build.obj_path(source)
    print(f"decode_calls: compiling {source_rel} -> {obj.relative_to(build.ROOT)}")
    build.compile_source(source, obj)

    symbol_map = build.load_symbol_map()
    ghidra, ghidra_starts = load_ghidra(reverse_dir)
    exports_at = load_exports(reverse_dir)
    thunk_of = {thunk: body
                for body, thunks in build.build_call_thunks().items() for thunk in thunks}

    names_at = dict(exports_at)
    for r in rows:
        names_at.setdefault(int(r["target_rva"], 16), []).append(f"{r['name']} ({r['status']})")
    for sym, addresses in symbol_map.items():
        for address in addresses:
            names_at.setdefault(address, []).append(sym)

    errors = []
    total_unresolved = 0
    for name, rva, row_size, _src, status in targets:
        try:
            body, relocs = build.read_object_symbol_bytes(obj, name)
        except ValueError as exc:
            errors.append(f"{name}: {exc} (obj from {source_rel})")
            continue
        size = row_size
        size_note = ""
        if not size:
            if rva in ghidra:
                size = ghidra[rva][0]
                size_note = " (size from ghidra inventory)"
            else:
                size = len(body.rstrip(b"\xcc"))
                size_note = " (size from compiled body — no row/ghidra size)"
        try:
            target = build.read_target_bytes(rva, size)
        except ValueError as exc:
            errors.append(f"{name}: cannot read target bytes at 0x{rva:08X}: {exc}")
            continue

        rel32 = [(off, sym) for off, rtype, sym in relocs
                 if rtype == 0x0014 and off + 4 <= size]
        unresolved = [(off, sym) for off, sym in rel32 if sym not in symbol_map]
        print(f"\n{name} @ 0x{rva:08X} ({status}, {size}B{size_note}): "
              f"{len(rel32)} REL32 site(s), {len(unresolved)} unresolved")
        if not unresolved:
            print("  all callees resolved — no pins needed")
            continue
        total_unresolved += len(unresolved)
        for off, sym in unresolved:
            opcode = target[off - 1] if off >= 1 else None
            kind = {0xE8: "call", 0xE9: "jmp"}.get(opcode, f"op={opcode:02x}" if opcode is not None else "op=?")
            displacement = struct.unpack_from("<i", target, off)[0]
            callee = (rva + off + 4 + displacement) & 0xFFFFFFFF
            known, notes = describe_rva(callee, names_at, ghidra, ghidra_starts, thunk_of)
            known_text = "; ".join(known) if known else "no known name"
            print(f"  +0x{off:04x} {kind} -> 0x{callee:08X}  [{known_text}]  "
                  f"pin: {sym},0x{callee:08X}")
            for note in notes:
                print(f"          NOTE: {note}")

    if errors:
        print(f"\ndecode_calls: {len(errors)} function(s) could not be decoded:", file=sys.stderr)
        for error in errors:
            print(f"  - {error}", file=sys.stderr)
        raise SystemExit(1)
    if total_unresolved:
        print(f"\ndecode_calls: {total_unresolved} unresolved callee(s) — verify with "
              "./build.sh after pinning (a pin is a claim; the byte comparison is the judge)")


if __name__ == "__main__":
    main()
