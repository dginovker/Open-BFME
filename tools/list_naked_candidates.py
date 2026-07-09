#!/usr/bin/env python3
"""Rank naked asm functions that look like good C++ decompilation candidates."""
import argparse
from collections import defaultdict
import re

import build


NAKED_RE = re.compile(r"__declspec\s*\(\s*naked\s*\)")
EMIT_RE = re.compile(r"__emit\s+0x([0-9a-fA-F]{1,2})")


def collect_rows():
    rows = {}
    by_name = {}
    for row in build.load_all_function_rows():
        rows.setdefault(row["source"], []).append(row)
        by_name.setdefault(row["name"], []).append(row)
    return rows, by_name


def matched_body_index(rows_by_source, max_bytes):
    """Exact binary bytes of every matched row -> row. A naked body that
    byte-verifies is a literal copy of the binary, so an already-matched
    function is recognizable by its bytes even when the symbol comment is
    missing or the source mangles the name differently than the ledger."""
    exe = build.EXE.read_bytes()
    sections = build.pe_sections(exe)
    index = {}
    for rows in rows_by_source.values():
        for row in rows:
            if row["status"] != "matched":
                continue
            size = int(row["target_size"])
            if not 0 < size <= max_bytes:
                continue
            offset = build.rva_to_file_offset(sections, int(row["target_rva"], 16))
            index.setdefault(exe[offset : offset + size], row)
    return index


def symbol_comment(lines, index):
    for cursor in range(index - 1, max(-1, index - 5), -1):
        text = lines[cursor].strip()
        if not text:
            continue
        if text.startswith("// "):
            return text[3:].strip()
        break
    return None


def signature(lines, index):
    parts = []
    for cursor in range(index, max(-1, index - 4), -1):
        text = lines[cursor].strip()
        if text:
            parts.insert(0, text)
        if ")" in text and ("(" in text or parts):
            break
    sig = " ".join(parts)
    return " ".join(sig.split())


def block_bytes(lines, start):
    depth = 0
    seen_open = False
    data = []
    end = start
    for index in range(start, len(lines)):
        line = lines[index]
        if "{" in line:
            depth += line.count("{")
            seen_open = True
        if "__emit" in line:
            for match in EMIT_RE.finditer(line):
                data.append(int(match.group(1), 16))
        if "}" in line:
            depth -= line.count("}")
            if seen_open and depth <= 0:
                end = index
                break
    return bytes(data), end


def score_candidate(data, sig):
    score = 100
    reasons = []
    size = len(data)

    score -= size
    if size <= 16:
        reasons.append("tiny")
    elif size <= 64:
        reasons.append("small")

    calls = data.count(0xE8)
    if calls:
        score -= calls * 12
        reasons.append(f"{calls} call(s)")
    else:
        score += 12
        reasons.append("leaf")

    jumps = sum(data.count(op) for op in (0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x7C, 0x7D, 0x7E, 0x7F, 0xE9, 0xEB))
    if jumps:
        score -= jumps * 6
        reasons.append(f"{jumps} branch(es)")

    if any(byte in data for byte in (0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF)):
        score -= 18
        reasons.append("x87")

    if b"\xff\x52" in data or b"\xff\x50" in data:
        score += 10
        reasons.append("virtual-call pattern")

    if data in (bytes.fromhex("8b c1 c3"), bytes.fromhex("c3")):
        score += 30
        reasons.append("trivial return")

    if "operator<<" in sig and "Debug" in sig:
        score += 20
        reasons.append("Debug stream")

    if "operator=" in sig:
        score += 10
        reasons.append("assignment")

    return score, reasons


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="*", default=["src"], help="source files or directories to scan")
    parser.add_argument("--all", action="store_true", help="include untracked naked functions")
    parser.add_argument("--groups", action="store_true", help="show repeated naked byte patterns instead of individual functions")
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--max-bytes", type=int, default=160)
    args = parser.parse_args()

    row_by_source, rows_by_name = collect_rows()
    body_index = matched_body_index(row_by_source, args.max_bytes)
    files = []
    for raw in args.paths:
        path = build.ROOT / raw
        if path.is_dir():
            files.extend(sorted(path.rglob("*.cpp")))
        elif path.exists():
            files.append(path)

    candidates = []
    already_matched = 0
    for path in files:
        rel = path.relative_to(build.ROOT).as_posix()
        text = path.read_text(encoding="utf-8", errors="replace")
        if "__declspec(naked)" not in text:
            continue
        lines = text.splitlines()
        source_rows = row_by_source.get(rel, [])
        unmatched_count = sum(1 for row in source_rows if row["status"] != "matched")
        for index, line in enumerate(lines):
            if not NAKED_RE.search(line):
                continue
            data, end = block_bytes(lines, index)
            if not data or len(data) > args.max_bytes:
                continue
            sig = signature(lines, index)
            symbol = symbol_comment(lines, index)
            symbol_rows = rows_by_name.get(symbol, []) if symbol else []
            own = [row for row in symbol_rows if row["source"] == rel]
            row = own[0] if own else None
            if row is None:
                # not this file's ledger row, but the function may already be
                # matched — by name under another source, or (when the symbol
                # comment is missing) by its exact bytes; listing it as
                # "untracked" lures agents into redoing done work
                if any(r["status"] == "matched" for r in symbol_rows) or data in body_index:
                    already_matched += 1
                    continue
            if not row and not args.all:
                continue
            score, reasons = score_candidate(data, sig)
            candidates.append(
                {
                    "score": score,
                    "path": rel,
                    "line": index + 1,
                    "end": end + 1,
                    "size": len(data),
                    "bytes": data,
                    "symbol": symbol,
                    "tracked": row is not None,
                    "status": row["status"] if row else "untracked",
                    "signature": sig,
                    "reasons": reasons,
                    "unmatched_count": unmatched_count,
                }
            )

    if already_matched:
        print(f"{already_matched} excluded as already matched in reverse/functions.csv")
    candidates.sort(key=lambda item: (-item["score"], item["size"], item["path"], item["line"]))
    if args.groups:
        groups = defaultdict(list)
        for item in candidates:
            groups[item["bytes"]].append(item)
        grouped = sorted(groups.items(), key=lambda entry: (-len(entry[1]), -entry[1][0]["score"], len(entry[0])))
        for data, items in grouped[: args.limit]:
            tracked = sum(1 for item in items if item["tracked"])
            sample = items[0]
            reasons = ", ".join(sample["reasons"])
            print(f"{len(items):4d} function(s), {tracked:4d} tracked, {len(data):4d} bytes, score {sample['score']:4d}")
            print(f"      bytes: {' '.join(f'{byte:02x}' for byte in data)}")
            print(f"      {reasons}")
            for item in items[:5]:
                location = f"{item['path']}:{item['line']}"
                print(f"      {location}  {item['status']}  {item['signature']}")
                if item["tracked"]:
                    print(f"        ./build.sh '{item['symbol']}'")
            if len(items) > 5:
                print(f"      ... {len(items) - 5} more")
        return

    for item in candidates[: args.limit]:
        location = f"{item['path']}:{item['line']}"
        reasons = ", ".join(item["reasons"])
        print(f"{item['score']:4d}  {item['size']:4d} bytes  {location}  {item['status']}")
        print(f"      {item['signature']}")
        if item["symbol"]:
            print(f"      symbol: {item['symbol']}")
        if item["tracked"]:
            print(f"      verify: ./build.sh '{item['symbol']}'")
        print(f"      {reasons}; file has {item['unmatched_count']} unmatched csv row(s)")


if __name__ == "__main__":
    main()
