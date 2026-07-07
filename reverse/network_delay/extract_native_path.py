#!/usr/bin/env python3
import csv
import struct
import sys
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402


IMAGE_BASE = 0x400000
THE_NETWORK_VA = 0x012F76F0
WRAPPER_VTABLE_VA = 0x01119C8C
BACKEND_VTABLE_VA = 0x0111988C

WRAPPER_EXPECTED = [
    (0x00, 0x0065ADB0, "deleting destructor-ish"),
    (0x04, 0x006548C0, "init / alloc backend"),
    (0x08, 0x00652AB0, "shutdown/reset-ish"),
    (0x0C, 0x00651780, "backend proxy"),
    (0x10, 0x0065E050, "queue/list +0x14"),
    (0x14, 0x0065ADE0, "queue/list +0x14 bool"),
    (0x18, 0x0065E120, "queue/list +0x3c"),
    (0x1C, 0x00658E20, "queue/list +0x3c bool"),
    (0x20, 0x0065E340, "list transfer-ish +0x90"),
    (0x24, 0x0065AEB0, "list op +0x90"),
]

BACKEND_EXPECTED = [
    (0x00, 0x00654890, "deleting destructor-ish"),
    (0x04, 0x009DB650, "base/init-ish"),
    (0x08, 0x0065CA50, "event dispatcher"),
]

NATIVE_TARGETS = [
    ("create_network", 0x0065C1F0),
    ("wrapper_ctor", 0x0065AC30),
    ("wrapper_init", 0x006548C0),
    ("backend_ctor", 0x006547F0),
    ("backend_dispatcher", 0x0065CA50),
    ("registered_callback", 0x0065C260),
]


exe = build.EXE.read_bytes()
pe = build.pe_sections(exe)
text = next(section for section in pe if section["name"] == ".text")
text_lo = text["rva"]
text_hi = text_lo + text["size"]
text_raw = text["raw_pointer"]


def fmt(value):
    return f"0x{value:08X}"


def rvoff(rva):
    return build.rva_to_file_offset(pe, rva)


def u32_at_rva(rva):
    return struct.unpack_from("<I", exe, rvoff(rva))[0]


def s32_at_offset(offset):
    return struct.unpack_from("<i", exe, offset)[0]


def va_to_rva(va):
    return va - IMAGE_BASE


def resolve_ilt(rva):
    if not (text_lo <= rva < text_hi):
        return rva
    off = rvoff(rva)
    if exe[off] != 0xE9:
        return rva
    target = rva + 5 + s32_at_offset(off + 1)
    return target if text_lo <= target < text_hi else rva


def load_ghidra_functions():
    rows = []
    with (ROOT / "reverse" / "ghidra_functions.csv").open(newline="") as handle:
        for row in csv.DictReader(handle):
            start = int(row["rva"], 16)
            rows.append((start, int(row["size"]), row["name"]))
    return sorted(rows)


ghidra_functions = load_ghidra_functions()


def ghidra_status(rva):
    for start, size, name in ghidra_functions:
        if start == rva:
            return f"start size={size} name={name}"
        if start < rva < start + size:
            return f"inside {fmt(start)} size={size} name={name}"
        if start > rva:
            return "missing start"
    return "missing start"


def dump_vtable(label, vtable_va, expected):
    failures = 0
    print(f"{label}: VA {fmt(vtable_va)} / RVA {fmt(va_to_rva(vtable_va))}")
    for slot, expected_body, note in expected:
        entry_va = u32_at_rva(va_to_rva(vtable_va) + slot)
        entry_rva = va_to_rva(entry_va)
        body = resolve_ilt(entry_rva)
        status = "ok" if body == expected_body else f"expected {fmt(expected_body)}"
        if body != expected_body:
            failures += 1
        print(
            f"  +0x{slot:02X}: entry {fmt(entry_rva)} -> body {fmt(body)} "
            f"{status} ({note})"
        )
    return failures


def find_the_network_refs():
    needle = struct.pack("<I", THE_NETWORK_VA)
    refs = []
    start = text_raw
    end = text_raw + text["size"]
    pos = start
    while True:
        pos = exe.find(needle, pos, end)
        if pos == -1:
            break
        refs.append(text_lo + (pos - text_raw))
        pos += 1
    return refs


def first_indirect_call_slot(ref_rva):
    start = rvoff(ref_rva) - 2
    end = start + 80
    object_regs = set()
    vtable_regs = set()
    index = start
    while index < end:
        op = exe[index]

        if op == 0xA1:
            if struct.unpack_from("<I", exe, index + 1)[0] == THE_NETWORK_VA:
                object_regs.add(0)
            index += 5
            continue

        if op == 0x8B:
            modrm = exe[index + 1]
            mod = modrm >> 6
            dst = (modrm >> 3) & 7
            src = modrm & 7
            if mod == 3:
                if src in object_regs:
                    object_regs.add(dst)
                if src in vtable_regs:
                    vtable_regs.add(dst)
                index += 2
                continue
            if mod == 0 and src == 5:
                if struct.unpack_from("<I", exe, index + 2)[0] == THE_NETWORK_VA:
                    object_regs.add(dst)
                index += 6
                continue
            if mod == 0:
                if src in object_regs:
                    vtable_regs.add(dst)
                index += 2
                continue
            if mod == 1:
                if src in object_regs and exe[index + 2] == 0:
                    vtable_regs.add(dst)
                index += 3
                continue
            index += 6
            continue

        if op == 0xFF:
            modrm = exe[index + 1]
            mod = modrm >> 6
            subop = (modrm >> 3) & 7
            src = modrm & 7
            if subop == 2 and mod == 1 and src in vtable_regs:
                return exe[index + 2]
            if subop == 2 and mod == 0 and src in vtable_regs:
                return 0
            index += 3 if mod == 1 else 2
            continue

        index += 1
    return None


def main():
    failures = 0
    failures += dump_vtable("wrapper_vtable", WRAPPER_VTABLE_VA, WRAPPER_EXPECTED)
    failures += dump_vtable("backend_vtable", BACKEND_VTABLE_VA, BACKEND_EXPECTED)

    print("native_targets:")
    for name, rva in NATIVE_TARGETS:
        print(f"  {name}: {fmt(rva)} ({ghidra_status(rva)})")

    refs = find_the_network_refs()
    known_wrapper_slots = {slot for slot, _, _ in WRAPPER_EXPECTED}
    slots = Counter(
        slot
        for slot in (first_indirect_call_slot(ref) for ref in refs)
        if slot in known_wrapper_slots
    )
    print(f"TheNetwork refs: {len(refs)} text refs to VA {fmt(THE_NETWORK_VA)}")
    if slots:
        rendered = ", ".join(f"+0x{slot:02X}={count}" for slot, count in sorted(slots.items()))
        print(f"TheNetwork heuristic known-wrapper vcall slots: {rendered}")

    if failures:
        raise SystemExit(f"{failures} vtable slot(s) did not match expected bodies")


if __name__ == "__main__":
    main()
