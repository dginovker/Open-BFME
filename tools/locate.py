#!/usr/bin/env python3
"""Locate functions in the binary by masked byte-scan -- no export entry needed.

Compiles a source file, then for every function it emits searches all of .text for
placements whose bytes match after masking relocation sites (DIR32 pointers, REL32
call displacements). The search needle is the longest relocation-free run of bytes,
so it finds functions Ghidra never discovered. A placement is accepted only when it
is UNIQUE and every REL32 call site in the target resolves to a known function start
or link thunk; ambiguous or inconsistent placements are reported and skipped, never
guessed.

For each accepted placement it prints the reverse/functions.csv row plus the
reverse/symbols.csv rows for callees derived from the target's call displacements
(that is how you unblock call-using functions: the binary itself tells us the
callee address). Verify afterwards with ./build.sh <source>.

Usage: python3 tools/locate.py <source.cpp> [-I dir ...] [--min-size 24] [--emit]
"""
import argparse
import bisect
import csv
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build
import harvest

MIN_SIZE_DEFAULT = 24
MIN_NEEDLE = 8
IMAGE_SCN_MEM_EXECUTE = 0x20000000


def object_functions(obj_path):
    """Yield (name, bytes, relocs) for every function-sized symbol span in the
    object's executable sections. A span runs from a symbol to the next symbol
    in the same section (or the section end); relocs are (offset, type, symbol)."""
    data = obj_path.read_bytes()
    section_count = build.u16(data, 2)

    sections = []
    for index in range(section_count):
        offset = 20 + index * 40
        sections.append({
            "raw_size": build.u32(data, offset + 16),
            "raw_pointer": build.u32(data, offset + 20),
            "reloc_pointer": build.u32(data, offset + 24),
            "reloc_count": build.u16(data, offset + 32),
            "characteristics": build.u32(data, offset + 36),
        })

    symbols = build.read_object_symbols(data)
    by_section = {}
    for symbol in symbols:
        name, section = symbol["name"], symbol["section"]
        if section <= 0 or not name or name[0] not in "?_@":
            continue
        if not (sections[section - 1]["characteristics"] & IMAGE_SCN_MEM_EXECUTE):
            continue
        by_section.setdefault(section, {}).setdefault(symbol["value"], name)

    for section_index, values in by_section.items():
        section = sections[section_index - 1]
        starts = sorted(values)
        relocs = []
        for r in range(section["reloc_count"]):
            ro = section["reloc_pointer"] + r * 10
            relocs.append((build.u32(data, ro), build.u16(data, ro + 8), build.u32(data, ro + 4)))
        for i, value in enumerate(starts):
            end = starts[i + 1] if i + 1 < len(starts) else section["raw_size"]
            span = data[section["raw_pointer"] + value : section["raw_pointer"] + end]
            span_relocs = [
                (rva - value, rtype, symbols[sym_idx]["name"])
                for rva, rtype, sym_idx in relocs
                if value <= rva < end
            ]
            yield values[value], span, span_relocs


def masked(data, holes, size):
    out = bytearray(data[:size])
    for offset in holes:
        for i in range(offset, min(offset + 4, size)):
            out[i] = 0
    return bytes(out)


def hole_free_segments(length, holes):
    segments, prev = [], 0
    for hole in sorted(holes):
        if hole > prev:
            segments.append((prev, hole))
        prev = max(prev, hole + 4)
    if prev < length:
        segments.append((prev, length))
    return segments


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source")
    parser.add_argument("-I", dest="includes", action="append", default=[])
    parser.add_argument("--min-size", type=int, default=MIN_SIZE_DEFAULT)
    parser.add_argument("--emit", action="store_true",
                        help="append accepted rows to reverse/functions.csv and reverse/symbols.csv")
    args = parser.parse_args()

    exe = build.EXE.read_bytes()
    pe = build.pe_sections(exe)
    text = next(section for section in pe if section["name"] == ".text")
    text_rva, text_raw, text_size = text["rva"], text["raw_pointer"], text["size"]
    text_end = text_raw + text_size

    ghidra = {}
    with (build.ROOT / "reverse" / "ghidra_functions.csv").open(newline="") as handle:
        for row in csv.DictReader(handle):
            ghidra[int(row["rva"], 16)] = int(row["size"])
    ghidra_starts = sorted(ghidra)

    def plausible_small_start(rva, size):
        """Sub-24-byte patterns need boundary evidence beyond uniqueness.

        Accept an exact Ghidra boundary, or an uncovered 16-byte linker-aligned
        start. Reject starts inside a recovered function (the common tail-match
        false positive) and starts where Ghidra reports a different-sized body.
        """
        if size >= MIN_SIZE_DEFAULT:
            return True
        if rva in ghidra:
            return ghidra[rva] == size
        index = bisect.bisect_right(ghidra_starts, rva) - 1
        if index >= 0:
            start = ghidra_starts[index]
            if start < rva < start + ghidra[start]:
                return False
        return rva % 16 == 0
    body_to_thunks = build.build_call_thunks()  # body -> [incremental-link thunks]
    known_starts = set(ghidra) | set(body_to_thunks) | {
        thunk for thunks in body_to_thunks.values() for thunk in thunks
    }

    export_body = {}
    export_rva = {}
    with (build.ROOT / "reverse" / "exports.csv").open(newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] == "code":
                export_body.setdefault(row["name"], int(row["target_rva"] or row["rva"], 16))
                export_rva.setdefault(row["name"], int(row["rva"], 16))

    known_rows = build.load_all_function_rows()
    known_names = {row["name"] for row in known_rows}
    known_rvas = {int(row["target_rva"], 16) for row in known_rows}
    symbol_map = build.load_symbol_map()

    source = build.Path(args.source)
    obj = harvest.compile_obj(source, args.includes)
    source_rel = source.resolve().relative_to(build.ROOT)

    accepted, ambiguous, unlocated, conflicts, weak = [], [], [], [], []
    pending_multi = []
    deferred = []
    validate_hits = None  # bound inside the scan loop; reused by the fixpoint pass
    skipped_small = 0
    callee_map = {}  # symbol -> derived address, must stay consistent across all sites
    accepted_addr = {}  # name -> rva accepted this run
    taken = set(known_rvas)

    def read_ascii_string(va):
        """Read a short NUL-terminated retail string from an absolute VA."""
        try:
            offset = build.rva_to_file_offset(pe, va - 0x400000)
        except ValueError:
            return None
        end = exe.find(b"\0", offset, min(offset + 128, len(exe)))
        if end < 0:
            return None
        try:
            return exe[offset:end].decode("ascii")
        except UnicodeDecodeError:
            return None

    def class_string_candidate(name, size, relocs, validated):
        """Resolve pool/module helpers only when the binary names the class.

        These 104-byte static-init bodies are otherwise indistinguishable after
        relocations are masked.  An exact Ghidra boundary plus the helper's own
        class-name string is independent identity evidence; either alone is not.
        """
        match = re.search(r"\?(?:getModuleNameKey|getClassMemoryPool)@([^@]+)@@", name)
        if not match or len(validated) < 2:
            return None
        class_name = match.group(1)
        dir32 = [off for off, rtype, _ in relocs if rtype == 0x0006 and off + 4 <= size]
        identified = []
        for rva, callees in validated:
            if ghidra.get(rva) != size:
                continue
            start = text_raw + (rva - text_rva)
            target = exe[start : start + size]
            strings = [read_ascii_string(struct.unpack_from("<I", target, off)[0]) for off in dir32]
            if class_name in strings:
                identified.append((rva, callees))
        return identified[0] if len(identified) == 1 else None

    class_identified = set()

    def known_addresses(sym):
        """Every address a call to `sym` may legitimately encode, or None if unknown."""
        addresses = set()
        if sym in callee_map:
            addresses.add(callee_map[sym])
        for addr in symbol_map.get(sym, []):
            addresses.add(addr)
        if sym in accepted_addr:
            body = accepted_addr[sym]
            addresses.add(body)
            addresses.update(body_to_thunks.get(body, []))
        return addresses or None

    for name, span, relocs in object_functions(obj):
        if name in known_names:
            continue
        body = span.rstrip(b"\xcc")
        size = len(body)
        if size < args.min_size:
            skipped_small += 1
            continue
        holes = [off for off, rtype, _ in relocs if rtype in (0x0006, 0x0014) and off < size]
        rel32 = [(off, sym) for off, rtype, sym in relocs if rtype == 0x0014 and off < size]

        segments = hole_free_segments(size, holes)
        seg_start, seg_end = max(segments, key=lambda s: s[1] - s[0], default=(0, 0))
        if seg_end - seg_start < MIN_NEEDLE:
            weak.append((name, size))
            continue
        needle = bytes(body[seg_start:seg_end])
        pattern = masked(body, holes, size)

        hits = []
        cursor = text_raw
        while True:
            found = exe.find(needle, cursor, text_end)
            if found == -1:
                break
            cursor = found + 1
            start = found - seg_start
            if start < text_raw or start + size > text_end:
                continue
            if masked(exe[start : start + size], holes, size) == pattern:
                rva = start - text_raw + text_rva
                if rva not in known_rvas and plausible_small_start(rva, size):
                    hits.append(rva)

        # validate call sites: every REL32 must point at a known function start/thunk
        def validate_hits(hits, rel32, size, starts):
            validated = []
            for rva in hits:
                target = exe[text_raw + (rva - text_rva) : text_raw + (rva - text_rva) + size]
                callees = {}
                ok = True
                for off, sym in rel32:
                    if off + 4 > size:
                        ok = False
                        break
                    displacement = struct.unpack_from("<i", target, off)[0]
                    callee = rva + off + 4 + displacement
                    if callee not in starts:
                        ok = False
                        break
                    if callees.setdefault(sym, callee) != callee:
                        ok = False  # one symbol, two addresses inside one function
                        break
                if ok:
                    validated.append((rva, callees))
            return validated

        validated = validate_hits(hits, rel32, size, known_starts)

        if not validated:
            if hits and rel32:
                # a callee may be a same-file function not yet accepted (or missed by
                # Ghidra); retry in the fixpoint loop once siblings pin more addresses
                deferred.append((name, size, rel32, hits))
            else:
                unlocated.append((name, size))
            continue

        identified = class_string_candidate(name, size, relocs, validated)
        if identified is not None:
            validated = [identified]
            class_identified.add(name)

        def try_accept(name, size, validated):
            """Accept when exactly one candidate placement survives; returns True on accept."""
            live = [
                entry for entry in validated
                if entry[0] not in taken
                or (name in class_identified
                    and any(rva == entry[0] and accepted_size == size
                            for _, rva, accepted_size, _ in accepted))
            ]
            if len(live) > 1:
                # a call to a symbol with a known address disambiguates identical bodies
                consistent = [
                    (rva, callees) for rva, callees in live
                    if all((known_addresses(sym) or {addr}) >= {addr} for sym, addr in callees.items())
                ]
                if consistent:
                    live = consistent
            if not live:
                unlocated.append((name, size))
                return True
            if len(live) > 1:
                return False
            rva, callees = live[0]
            if name in export_body and export_body[name] != rva:
                conflicts.append(f"{name}: scan found 0x{rva:08X} but export table says 0x{export_body[name]:08X}")
                return True
            for sym, addr in callees.items():
                known = known_addresses(sym)
                if known is not None and addr not in known:
                    conflicts.append(f"{name}: callee {sym} = 0x{addr:08X} here but known addresses are "
                                     + ", ".join(f"0x{a:08X}" for a in sorted(known)))
                    return True
            callee_map.update(callees)
            accepted_addr[name] = rva
            taken.add(rva)
            accepted.append((name, rva, ghidra.get(rva, size), callees))
            return True

        if not try_accept(name, size, validated):
            pending_multi.append((name, size, validated))

    # identical bodies (template siblings) resolve once their callees' addresses are
    # pinned by other acceptances, and callee-validation rejections may pass once
    # same-file siblings are accepted; iterate both to a fixpoint
    progress = True
    while progress and (pending_multi or deferred):
        progress = False
        for entry in list(pending_multi):
            if try_accept(*entry):
                pending_multi.remove(entry)
                progress = True
        expanded = set(known_starts)
        for body in accepted_addr.values():
            expanded.add(body)
            expanded.update(body_to_thunks.get(body, []))
        for entry in list(deferred):
            name, size, rel32, hits = entry
            validated = validate_hits(hits, rel32, size, expanded)
            if validated:
                deferred.remove(entry)
                progress = True
                if not try_accept(name, size, validated):
                    pending_multi.append((name, size, validated))
    for name, size, validated in pending_multi:
        ambiguous.append((name, size, [hex(rva) for rva, _ in validated[:6]]))
    for name, size, rel32, hits in deferred:
        unlocated.append((name, size))

    accepted_names = {name for name, _, _, _ in accepted}
    new_symbols = sorted(
        (sym, addr) for sym, addr in callee_map.items()
        if sym not in symbol_map and sym not in accepted_names
        and any(sym in c for _, _, _, c in accepted)
    )

    print(f"{source.name}: {len(accepted)} located, {len(ambiguous)} ambiguous, "
          f"{len(unlocated)} unlocated, {len(conflicts)} conflicts, "
          f"{len(weak)} weak-needle, {skipped_small} below --min-size {args.min_size}")
    rows = []
    for name, rva, size, _ in sorted(accepted, key=lambda entry: entry[1]):
        export = f"0x{export_rva[name]:08X}" if name in export_rva else ""
        rows.append(f"{name},{export},0x{rva:08X},{size},{source_rel},matched,")
    for row in rows:
        print("  " + row)
    if new_symbols:
        print("reverse/symbols.csv additions (callee addresses read from the binary):")
        for sym, addr in new_symbols:
            print(f"  {sym},0x{addr:08X}")
    for name, size, candidates in ambiguous:
        print(f"  AMBIGUOUS {name} ({size}B): {', '.join(candidates)}")
    for line in conflicts:
        print(f"  CONFLICT {line}")
    for name, size in weak:
        print(f"  WEAK NEEDLE {name} ({size}B): longest relocation-free run under {MIN_NEEDLE} bytes")
    if unlocated:
        print("  unlocated (drifted or not in this binary): "
              + ", ".join(f"{n}({s}B)" for n, s in sorted(unlocated, key=lambda e: -e[1])[:20]))

    if args.emit and rows:
        with build.FUNCTIONS.open("a", encoding="utf-8", newline="") as handle:
            for row in rows:
                handle.write(row + "\n")
        if new_symbols:
            with build.SYMBOLS.open("a", encoding="utf-8", newline="") as handle:
                for sym, addr in new_symbols:
                    handle.write(f"{sym},0x{addr:08X}\n")
        print(f"emitted {len(rows)} row(s) to functions.csv"
              + (f", {len(new_symbols)} to symbols.csv" if new_symbols else ""))


if __name__ == "__main__":
    main()
