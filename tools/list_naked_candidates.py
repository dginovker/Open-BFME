#!/usr/bin/env python3
"""Rank naked asm functions that look like good C++ decompilation candidates."""
import argparse
import re

import build


NAKED_RE = re.compile(r"__declspec\s*\(\s*naked\s*\)")
EMIT_RE = re.compile(r"__emit\s+0x([0-9a-fA-F]{1,2})")


def collect_rows():
    rows = {}
    for row in build.load_all_function_rows():
        rows.setdefault(row["source"], []).append(row)
    return rows


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
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--max-bytes", type=int, default=160)
    args = parser.parse_args()

    row_by_source = collect_rows()
    files = []
    for raw in args.paths:
        path = build.ROOT / raw
        if path.is_dir():
            files.extend(sorted(path.rglob("*.cpp")))
        elif path.exists():
            files.append(path)

    candidates = []
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
            score, reasons = score_candidate(data, sig)
            candidates.append(
                {
                    "score": score,
                    "path": rel,
                    "line": index + 1,
                    "end": end + 1,
                    "size": len(data),
                    "signature": sig,
                    "reasons": reasons,
                    "unmatched_count": unmatched_count,
                }
            )

    candidates.sort(key=lambda item: (-item["score"], item["size"], item["path"], item["line"]))
    for item in candidates[: args.limit]:
        location = f"{item['path']}:{item['line']}"
        reasons = ", ".join(item["reasons"])
        print(f"{item['score']:4d}  {item['size']:4d} bytes  {location}")
        print(f"      {item['signature']}")
        print(f"      {reasons}; file has {item['unmatched_count']} unmatched csv row(s)")


if __name__ == "__main__":
    main()
