#!/usr/bin/env python3
"""Compile a source file and byte-compare every function it emits against the binary,
reporting which match, which need source reconciliation, and which call an unresolved
symbol. Discovers candidate matches with zero per-function effort, then you paste the
emitted rows into reverse/functions.csv.

Only functions present in the export table are addressable here (name -> address).
Sizes come from reverse/ghidra_functions.csv when present (see tools/ghidra/README.md),
otherwise they are estimated from export-address gaps.

Usage: python3 tools/harvest.py <source.cpp> [-I includedir ...]
"""
import os
import sys
import csv
import bisect
import struct
import subprocess
import argparse

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build


def load_tables():
    export_rva = {}
    body_rva = {}
    bodies = set()
    with (build.ROOT / "reverse" / "exports.csv").open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] != "code":
                continue
            body = int(row["target_rva"] or row["rva"], 16)
            export_rva.setdefault(row["name"], int(row["rva"], 16))
            body_rva.setdefault(row["name"], body)
            bodies.add(body)
    bodies = sorted(bodies)

    rows = build.load_function_rows()
    matched = {row["name"] for row in rows}
    auth_size = {row["name"]: int(row["target_size"]) for row in rows}

    ghidra_size = {}
    inventory = build.ROOT / "reverse" / "ghidra_functions.csv"
    if inventory.exists():
        with inventory.open(encoding="utf-8", newline="") as handle:
            ghidra_size = {int(r["rva"], 16): int(r["size"]) for r in csv.DictReader(handle)}

    def size_of(name, rva):
        if name in auth_size:
            return auth_size[name]
        if rva in ghidra_size:
            return ghidra_size[rva]
        index = bisect.bisect_right(bodies, rva)
        return bodies[index] - rva if index < len(bodies) else 0

    return export_rva, body_rva, size_of, matched


def compile_obj(source, includes):
    obj = build.BUILD_DIR / (source.stem + ".harvest.obj")
    obj.parent.mkdir(parents=True, exist_ok=True)
    compiler = build.vc71_root() / "Vc7" / "bin" / "cl.exe"
    command = ["wine"] if os.name != "nt" else []
    command += [str(compiler), "/nologo", "/c", "/O2", "/GR-", "/EHsc-"]
    for directory in includes:
        command += ["/I", build.wine_path(build.Path(directory).resolve())]
    command += ["/Fo" + build.wine_path(obj), build.wine_path(source.resolve())]
    result = subprocess.run(
        command, cwd=build.ROOT, env=build.compiler_environment(build.vc71_root()),
        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
    )
    if result.returncode != 0:
        print("COMPILE FAILED:\n" + result.stdout[-3000:])
        raise SystemExit(1)
    return obj


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source")
    parser.add_argument("-I", dest="includes", action="append", default=[])
    args = parser.parse_args()

    export_rva, body_rva, size_of, matched = load_tables()
    symbol_map = build.load_symbol_map()
    source = build.Path(args.source)
    obj = compile_obj(source, args.includes)

    data = obj.read_bytes()
    emitted = sorted({
        s["name"] for s in build.read_object_symbols(data)
        if s["section"] > 0 and s["name"].startswith("?")
    })

    new_rows, drift, unresolved = [], [], set()
    for name in emitted:
        if name not in body_rva:
            continue  # not in the export table -> no address to compare against
        rva = body_rva[name]
        size = size_of(name, rva)
        if not size or size > 8192:
            continue
        target = build.read_target_bytes(rva, size).rstrip(b"\xcc")
        try:
            compiled, relocs = build.read_object_symbol_bytes(obj, name)
        except ValueError:
            continue
        resolved = bytearray(compiled[: len(target)])
        missing = []
        for offset, rtype, sym in relocs:
            if offset >= len(target):
                continue
            if rtype == 0x0006:  # DIR32
                resolved[offset : offset + 4] = target[offset : offset + 4]
            elif rtype == 0x0014:  # REL32
                if sym in symbol_map:
                    resolved[offset : offset + 4] = struct.pack("<i", symbol_map[sym] - (rva + offset + 4))
                else:
                    missing.append(sym)
        if bytes(resolved) == target and not missing:
            if name not in matched:
                rel = source.resolve().relative_to(build.ROOT)
                new_rows.append(f"{name},0x{export_rva[name]:08X},0x{rva:08X},{len(target)},{rel},matched,")
        elif missing:
            unresolved.update(missing)
        else:
            drift.append(name)

    print(f"{source.name}: {len(new_rows)} new match(es), {len(drift)} drift, {len(unresolved)} blocked by an unresolved call")
    for row in new_rows:
        print("  " + row)
    if unresolved:
        print("  add to reverse/symbols.csv (address from Ghidra) to unblock: " + ", ".join(sorted(unresolved)))
    if drift:
        print("  source drift, reconcile against the binary: " + ", ".join(drift[:10]))


if __name__ == "__main__":
    main()
