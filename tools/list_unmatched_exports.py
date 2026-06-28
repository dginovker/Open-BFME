#!/usr/bin/env python3
"""List unmatched code exports sorted by approximate size.

Useful for finding the next small functions to reverse-engineer.
Run after generating reverse/exports.csv with export_symbols.py.
"""
import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
EXPORTS = ROOT / "reverse" / "exports.csv"


def main():
    with FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
        matched = {row["name"] for row in csv.DictReader(handle)}

    with EXPORTS.open("r", encoding="utf-8", newline="") as handle:
        exports = list(csv.DictReader(handle))

    code = [row for row in exports if row["kind"] == "code" and row["name"] not in matched]
    code.sort(key=lambda row: int(row["rva"], 16))

    for i, row in enumerate(code):
        rva = int(row["rva"], 16)
        next_rva = int(code[i + 1]["rva"], 16) if i + 1 < len(code) else rva + 200
        size = next_rva - rva
        target = row["target_rva"] or row["rva"]
        print(f"{row['rva']} -> {target} size~{size:4d} {row['name']}")


if __name__ == "__main__":
    main()
