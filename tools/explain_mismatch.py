#!/usr/bin/env python3
"""Explain a function byte mismatch with byte windows and side-by-side disassembly."""
import argparse
import shutil
import subprocess
import sys
import tempfile

import build


def find_row(selector):
    matches = [
        row for row in build.load_function_rows()
        if selector in row["name"] or selector in row["source"]
    ]
    if not matches:
        raise SystemExit(f"no matched function contains: {selector}")
    if len(matches) > 1:
        print(f"{len(matches)} functions match; use a more specific selector:", file=sys.stderr)
        for row in matches[:30]:
            print(f"  {row['name']} ({row['source']})", file=sys.stderr)
        if len(matches) > 30:
            print(f"  ... {len(matches) - 30} more", file=sys.stderr)
        raise SystemExit(2)
    return matches[0]


def hexdump(data, base, mark=None, width=8):
    lines = []
    for offset in range(0, len(data), width):
        chunk = data[offset : offset + width]
        prefix = ">" if mark is not None and offset <= mark < offset + len(chunk) else " "
        lines.append(f"{prefix} {base + offset:08X}: " + " ".join(f"{b:02x}" for b in chunk))
    return lines


def disassemble(data, base):
    objdump = shutil.which("objdump") or shutil.which("llvm-objdump")
    if objdump is None:
        return ["objdump not found; install binutils for disassembly"]

    with tempfile.NamedTemporaryFile(prefix="bfme-bytes-", delete=False) as handle:
        handle.write(data)
        path = handle.name

    try:
        result = subprocess.run(
            [objdump, "-D", "-b", "binary", "-m", "i386", "-M", "intel", f"--adjust-vma=0x{base:X}", path],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            check=False,
        )
    finally:
        build.Path(path).unlink(missing_ok=True)

    lines = []
    for line in result.stdout.splitlines():
        stripped = line.strip()
        if not stripped or stripped.endswith("file format binary") or stripped.startswith("Disassembly of"):
            continue
        if "<.data>" in stripped:
            continue
        lines.append(stripped)
    return lines


def first_diff(left, right):
    limit = min(len(left), len(right))
    for index in range(limit):
        if left[index] != right[index]:
            return index
    if len(left) != len(right):
        return limit
    return None


def classify(target, compiled, offset, relocs, unresolved):
    if unresolved:
        return "unresolved REL32 call"
    if offset is None:
        return "exact match"
    if len(target) != len(compiled):
        return "size mismatch"
    if any(ro <= offset < ro + 4 for ro, _rtype, _name in relocs):
        return "relocation-adjacent mismatch"
    t = target[offset]
    c = compiled[offset]
    if t in (0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x7C, 0x7D, 0x7E, 0x7F) or c in (
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x7C, 0x7D, 0x7E, 0x7F,
    ):
        return "branch-shape mismatch"
    if t in (0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF) or c in (
        0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    ):
        return "x87 instruction mismatch"
    if t in (0x50, 0x51, 0x52, 0x53, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5E, 0x5F) or c in (
        0x50, 0x51, 0x52, 0x53, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5E, 0x5F,
    ):
        return "register-save/allocation mismatch"
    if t == 0xE8 or c == 0xE8:
        return "call-shape mismatch"
    return "instruction/register encoding mismatch"


def candidate_row(args):
    """Synthesize a row for an unmatched candidate (drift/structural work):
    the function has no ledger row yet, so the caller supplies where it is
    believed to live. Size defaults from the ghidra function inventory, which
    also guards against explaining a mid-function misplacement."""
    if not args.source:
        raise SystemExit("--rva needs --source (the file defining the symbol)")
    rva = int(args.rva, 16)
    size = args.size
    if size is None:
        ghidra = build.ROOT / "reverse" / "ghidra_functions.csv"
        if not ghidra.exists():
            raise SystemExit("--size omitted and reverse/ghidra_functions.csv absent "
                             "(generate it per tools/ghidra/README.md, or pass --size)")
        for line in ghidra.open():
            parts = line.split(",", 2)
            try:
                if int(parts[0], 16) == rva:
                    size = int(parts[1])
                    break
            except ValueError:
                continue
        if size is None:
            raise SystemExit(f"0x{rva:08X} is not a ghidra function start — likely a "
                             "misplaced candidate; verify the address before shaping")
    return {"name": args.selector, "export_rva": "", "target_rva": f"0x{rva:08X}",
            "target_size": str(size), "source": args.source, "status": "matched", "notes": ""}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("selector", help="Decorated symbol substring or source path substring; "
                        "with --rva, the EXACT decorated symbol")
    parser.add_argument("--context", type=int, default=24, help="bytes around the first difference")
    parser.add_argument("--rva", help="explain an unmatched candidate believed to live at this "
                        "target RVA (drift_report candidate_rva); needs --source")
    parser.add_argument("--size", type=int, help="candidate size (default: ghidra inventory)")
    parser.add_argument("--source", help="source file defining the candidate symbol")
    args = parser.parse_args()

    row = candidate_row(args) if args.rva else find_row(args.selector)
    source = build.ROOT / row["source"]
    output = build.obj_path(source)
    build.compile_source(source, output)

    compiled_raw, relocs = build.read_object_symbol_bytes(
        output, build.ledger_object_symbol(row), int(row["target_size"]))
    patch = build.compile_function(row, build.load_symbol_map(), output)
    target = patch["target"]
    compiled = patch["bytes"]
    target_rva = patch["target_rva"]
    offset = first_diff(target, compiled)

    print(f"{row['name']} ({row['source']})")
    print(f"target RVA: 0x{target_rva:08X}")
    print(f"target size: {len(target)} bytes")
    print(f"compiled symbol size: {len(compiled_raw)} bytes")
    print(f"classification: {classify(target, compiled, offset, relocs, patch['unresolved'])}")
    if patch["unresolved"]:
        print("unresolved: " + ", ".join(sorted(set(patch["unresolved"]))))
    if offset is None:
        print("OK: bytes match")
        return

    start = max(0, offset - args.context)
    end = min(max(len(target), len(compiled)), offset + args.context)
    print(f"first diff: +0x{offset:X} at RVA 0x{target_rva + offset:08X}")
    if offset < len(target):
        print(f"  target byte:   {target[offset]:02x}")
    if offset < len(compiled):
        print(f"  compiled byte: {compiled[offset]:02x}")

    print("\nBytes:")
    print("target:")
    print("\n".join(hexdump(target[start:end], target_rva + start, offset - start)))
    print("compiled:")
    print("\n".join(hexdump(compiled[start:end], target_rva + start, offset - start)))

    print("\nDisassembly:")
    target_disasm = disassemble(target, target_rva)
    compiled_disasm = disassemble(compiled, target_rva)
    width = max([len(line) for line in target_disasm[:40]] + [6])
    for index in range(max(len(target_disasm), len(compiled_disasm))):
        left = target_disasm[index] if index < len(target_disasm) else ""
        right = compiled_disasm[index] if index < len(compiled_disasm) else ""
        marker = "!=" if left != right else "  "
        print(f"{marker} {left:<{width}} | {right}")


if __name__ == "__main__":
    main()
