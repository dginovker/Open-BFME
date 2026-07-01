#!/usr/bin/env python3
"""List functions defined in source files that are not yet in functions.csv."""

import csv
import argparse
import re
import subprocess
import sys
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


def git_show(path: Path):
    result = subprocess.run(
        ["git", "show", f":{path.as_posix()}"],
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
    )
    if result.returncode != 0:
        return None
    return result.stdout


def read_function_names(path: Path, staged: bool):
    text = git_show(path.relative_to(ROOT)) if staged else None
    if text is None:
        text = path.read_text(encoding="utf-8")
    declared = set()
    matched = set()
    for row in csv.DictReader(text.splitlines()):
        declared.add(row["name"])
        if row["status"] == "matched":
            matched.add(row["name"])
    return declared, matched


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


def find_defined_functions(text: str):
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
    symbol_comment = None
    # Stack of (namespace_name, brace_depth_at_open). Anonymous namespaces use "".
    namespace_stack = []
    brace_depth = 0

    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("// ?"):
            symbol_comment = stripped[3:].strip()
            continue
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
            if method_name.startswith("operator"):
                # normalize "operator ()" / "operator() " to "operator()"
                method_name = "operator" + re.sub(r"\s+", "", method_name[len("operator"):])
            if namespace_stack and "::" not in class_name:
                # Filter out anonymous namespace entries.
                ns_parts = [ns for ns, _ in namespace_stack if ns]
                class_name = "::".join(ns_parts + [class_name])
            results.add((class_name, method_name, symbol_comment))
            symbol_comment = None
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="*", help="source files to inspect; defaults to every src/*.cpp")
    parser.add_argument("--fail", action="store_true", help="exit non-zero when unmatched functions are found")
    parser.add_argument("--staged", action="store_true", help="read paths from the git index")
    args = parser.parse_args()

    declared, matched = read_function_names(FUNCTIONS_CSV, args.staged)

    unmatched = []
    source_paths = [ROOT / path for path in args.paths] if args.paths else sorted(SRC_DIR.rglob("*.cpp"))
    for source_path in source_paths:
        if source_path.suffix != ".cpp":
            continue
        rel_path = source_path.relative_to(ROOT)
        if args.staged:
            text = git_show(rel_path)
            if text is None:
                continue
        else:
            text = source_path.read_text(encoding="utf-8")
        for class_name, method_name, symbol_name in find_defined_functions(text):
            if symbol_name:
                if symbol_name in declared:
                    continue
                unmatched.append((rel_path, class_name, method_name))
                continue

            needle = mangle_method(class_name, method_name)
            # Constructors/destructors match a prefix; ordinary methods match a substring.
            if needle.startswith("??0") or needle.startswith("??1"):
                if any(name.startswith(needle) for name in matched):
                    continue
            else:
                if any(needle in name for name in matched):
                    continue
            unmatched.append((rel_path, class_name, method_name))

    if not unmatched:
        print("All defined functions are already matched.")
        return

    for rel_path, class_name, method_name in unmatched:
        print(f"{rel_path}: {class_name}::{method_name}")
    if args.fail:
        sys.exit(1)


if __name__ == "__main__":
    main()
