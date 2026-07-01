#!/usr/bin/env python3
"""List unmatched code exports sorted by approximate size.

Useful for finding the next small functions to reverse-engineer.
Run after generating reverse/exports.csv with export_symbols.py.
"""
import csv
import signal
from pathlib import Path

# Exit silently when piped to a tool that closes early (e.g. head).
signal.signal(signal.SIGPIPE, signal.SIG_DFL)

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
EXPORTS = ROOT / "reverse" / "exports.csv"


def main():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        matched = {
            row["name"]
            for row in csv.DictReader(handle)
            if row.get("status", "matched") == "matched"
        }

    with EXPORTS.open("r", encoding="utf-8", newline="") as handle:
        exports = list(csv.DictReader(handle))

    code = [row for row in exports if row["kind"] == "code" and row["name"] not in matched]
    code.sort(key=lambda row: int(row["rva"], 16))

    entries = []
    for i, row in enumerate(code):
        rva = int(row["rva"], 16)
        if i + 1 < len(code):
            next_rva = int(code[i + 1]["rva"], 16)
            size = next_rva - rva
        else:
            size = 0
        entries.append((size, row))

    entries.sort(key=lambda entry: (entry[0] == 0, entry[0], int(entry[1]["rva"], 16)))

    for size, row in entries:
        target = row["target_rva"] or row["rva"]
        size_note = f"size~{size:4d}" if size else "size~   ?"
        print(f"{row['rva']} -> {target} {size_note} {row['name']}")


if __name__ == "__main__":
    main()
