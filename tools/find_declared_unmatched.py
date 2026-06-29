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
    and ordinary methods use ?name@Class@Namespace@@.
    class_name may be qualified (e.g. "FXParticleSystem::ButterflyDrawModuleInfo").
    """
    parts = class_name.split("::")
    if method_name == parts[-1]:
        prefix = "??0"
    elif method_name == f"~{parts[-1]}":
        prefix = "??1"
    elif method_name in OPERATOR_CODES:
        prefix = OPERATOR_CODES[method_name]
    else:
        prefix = f"?{method_name}"
    mangled_class = "@".join(reversed(parts))
    # Constructors, destructors and operators attach directly to the class name;
    # ordinary methods are separated from the class by an @.
    if prefix.startswith("?") and not prefix.startswith("??"):
        return f"{prefix}@{mangled_class}@@"
    return f"{prefix}{mangled_class}@@"


def find_defined_functions(source_path: Path):
    text = source_path.read_text(encoding="utf-8")
    # Match definitions like:
    #   ReturnType ClassName::methodName(
    #   Namespace::ClassName::methodName(
    #   ClassName::ClassName(
    #   ClassName::~ClassName(
    definition_pattern = re.compile(
        r"^[\w:&*~\s]*?((?:\w+::)*\w+)::(operator[\s=\+\-\*/\[\]\(\)<>!]+|\~?\w+)\s*\(",
        re.MULTILINE,
    )
    namespace_pattern = re.compile(r"\bnamespace\s+(\w+)\s*\{")

    results = set()
    # Stack of (namespace_name, brace_depth_at_open). Anonymous namespaces use "".
    namespace_stack = []
    brace_depth = 0

    for line in text.splitlines():
        stripped = line.strip()
        is_namespace_line = stripped.startswith("namespace ") or stripped.startswith("namespace\t") or stripped.startswith("namespace {")

        open_count = line.count("{")
        close_count = line.count("}")

        if is_namespace_line:
            match = namespace_pattern.search(line)
            ns_name = match.group(1) if match else ""
            # The namespace opens at the next unmatched brace depth.
            namespace_stack.append((ns_name, brace_depth + 1))

        brace_depth += open_count - close_count

        # Close any namespaces whose opening brace has now been matched.
        while namespace_stack and namespace_stack[-1][1] > brace_depth:
            namespace_stack.pop()

        match = definition_pattern.match(line)
        if match:
            class_name = match.group(1)
            method_name = match.group(2)
            if namespace_stack and "::" not in class_name:
                # Filter out anonymous namespace entries.
                ns_parts = [ns for ns, _ in namespace_stack if ns]
                class_name = "::".join(ns_parts + [class_name])
            results.add((class_name, method_name))
    return results


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
