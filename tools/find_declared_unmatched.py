#!/usr/bin/env python3
"""List functions defined in source files that are not yet in functions.csv."""

import csv
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = ROOT / "src"
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"

# MSVC operator mangling codes for common operators.
OPERATOR_CODES = {
    "operator=": "??4",
    "operator==": "??8",
    "operator!=": "??9",
    "operator+": "??H",
    "operator-": "??G",
    "operator*": "??D",
    "operator/": "??K",
    "operator+=": "??Y",
    "operator-=": "??Z",
    "operator*=": "??X",
    "operator/=": "??_0",
    "operator<<": "??6",
    "operator>>": "??5",
    "operator[]": "??A",
    "operator()": "??R",
    "operator~": "??1",  # destructor is also ??1; handled separately
}


def read_matched_names(path: Path) -> set:
    with path.open("r", encoding="utf-8", newline="") as handle:
        return {row["name"] for row in csv.DictReader(handle)}


def mangle_method(class_name: str, method_name: str) -> str:
    """Return a rough MSVC mangled-name substring to search for.

    Constructors use ??0, destructors use ??1, operator= uses ??4,
    and ordinary methods use ?name@class@@.
    """
    if method_name == class_name:
        return f"??0{class_name}@@"
    if method_name == f"~{class_name}":
        return f"??1{class_name}@@"
    if method_name in OPERATOR_CODES:
        return f"{OPERATOR_CODES[method_name]}{class_name}@@"
    return f"?{method_name}@{class_name}@@"


def find_defined_functions(source_path: Path):
    text = source_path.read_text(encoding="utf-8")
    # Match definitions like:
    #   ReturnType ClassName::methodName(
    #   ClassName::ClassName(
    #   ClassName::~ClassName(
    pattern = re.compile(
        r"^[\w:&*~\s]+?(\w+)::(operator[\s=\+\-\*/\[\]\(\)<>!]+|\~?\w+)\s*\(",
        re.MULTILINE,
    )
    return set(pattern.findall(text))


def main():
    matched = read_matched_names(FUNCTIONS_CSV)

    unmatched = []
    for source_path in sorted(SRC_DIR.rglob("*.cpp")):
        for class_name, method_name in find_defined_functions(source_path):
            needle = mangle_method(class_name, method_name)
            # Constructors/destructors match a prefix; ordinary methods match a substring.
            if needle.startswith("??0") or needle.startswith("??1"):
                if any(name.startswith(needle) for name in matched):
                    continue
            else:
                if any(needle in name for name in matched):
                    continue
            unmatched.append((source_path.relative_to(ROOT), class_name, method_name))

    if not unmatched:
        print("All defined functions are already matched.")
        return

    for rel_path, class_name, method_name in unmatched:
        print(f"{rel_path}: {class_name}::{method_name}")


if __name__ == "__main__":
    main()
