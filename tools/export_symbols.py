#!/usr/bin/env python3
import csv
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXE = ROOT / "baselines" / "bfme1" / "workshop-vanilla-1.03" / "files" / "lotrbfme.exe"
OUT = ROOT / "reverse" / "exports.csv"


def u16(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def u32(data, offset):
    return struct.unpack_from("<I", data, offset)[0]


def read_c_string(data, offset):
    end = data.index(b"\0", offset)
    return data[offset:end].decode("ascii", errors="replace")


def parse_sections(data, section_table, count):
    sections = []
    for index in range(count):
        offset = section_table + index * 40
        raw_name = data[offset : offset + 8].rstrip(b"\0")
        name = raw_name.decode("ascii", errors="replace").strip() or "<unnamed>"
        virtual_size = u32(data, offset + 8)
        virtual_address = u32(data, offset + 12)
        raw_size = u32(data, offset + 16)
        raw_pointer = u32(data, offset + 20)
        sections.append(
            {
                "name": name,
                "rva": virtual_address,
                "size": max(virtual_size, raw_size),
                "raw_pointer": raw_pointer,
            }
        )
    return sections


def section_for_rva(sections, rva):
    for section in sections:
        start = section["rva"]
        end = start + section["size"]
        if start <= rva < end:
            return section
    raise ValueError(f"RVA 0x{rva:08X} is outside all sections")


def rva_to_offset(sections, rva):
    section = section_for_rva(sections, rva)
    return section["raw_pointer"] + (rva - section["rva"])


def export_kind(section_name, rva, export_rva, export_size):
    if rva == 0:
        return "missing"
    if export_rva <= rva < export_rva + export_size:
        return "forwarder"
    if section_name == ".text":
        return "code"
    return "data"


def direct_jump_target(data, sections, rva, kind):
    if kind != "code":
        return ""

    offset = rva_to_offset(sections, rva)
    if data[offset] != 0xE9:
        return ""

    relative = struct.unpack_from("<i", data, offset + 1)[0]
    return f"0x{rva + 5 + relative:08X}"


def parse_exports(data):
    if data[:2] != b"MZ":
        raise ValueError("not an MZ executable")

    pe_offset = u32(data, 0x3C)
    if data[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")

    coff = pe_offset + 4
    section_count = u16(data, coff + 2)
    optional_header_size = u16(data, coff + 16)
    optional = coff + 20

    if u16(data, optional) != 0x10B:
        raise ValueError("expected PE32 optional header")

    data_directories = optional + 96
    export_rva = u32(data, data_directories)
    export_size = u32(data, data_directories + 4)
    sections = parse_sections(data, optional + optional_header_size, section_count)

    export_offset = rva_to_offset(sections, export_rva)
    ordinal_base = u32(data, export_offset + 16)
    function_count = u32(data, export_offset + 20)
    name_count = u32(data, export_offset + 24)
    functions_rva = u32(data, export_offset + 28)
    names_rva = u32(data, export_offset + 32)
    ordinals_rva = u32(data, export_offset + 36)

    functions_offset = rva_to_offset(sections, functions_rva)
    names_offset = rva_to_offset(sections, names_rva)
    ordinals_offset = rva_to_offset(sections, ordinals_rva)

    rows = []
    for index in range(name_count):
        name_rva = u32(data, names_offset + index * 4)
        name = read_c_string(data, rva_to_offset(sections, name_rva))
        ordinal_index = u16(data, ordinals_offset + index * 2)
        if ordinal_index >= function_count:
            raise ValueError(f"bad ordinal index {ordinal_index} for {name}")

        rva = u32(data, functions_offset + ordinal_index * 4)
        section_name = "" if rva == 0 else section_for_rva(sections, rva)["name"]
        kind = export_kind(section_name, rva, export_rva, export_size)
        rows.append(
            {
                "ordinal": ordinal_base + ordinal_index,
                "rva": f"0x{rva:08X}",
                "target_rva": direct_jump_target(data, sections, rva, kind),
                "section": section_name,
                "kind": kind,
                "name": name,
            }
        )

    return sorted(rows, key=lambda row: row["ordinal"])


def main():
    rows = parse_exports(EXE.read_bytes())
    OUT.parent.mkdir(parents=True, exist_ok=True)
    with OUT.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(
            handle,
            fieldnames=["ordinal", "rva", "target_rva", "section", "kind", "name"],
        )
        writer.writeheader()
        writer.writerows(rows)
    print(f"wrote {len(rows)} exports to {OUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
