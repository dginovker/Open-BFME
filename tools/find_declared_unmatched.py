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
CLAIMS_WHITELIST = ROOT / "reverse" / "unclaimed_sources_whitelist.txt"

# `// <label> present-unmatched` / `// <label> absent-from-retail` definition markers
UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(present-unmatched|absent-from-retail)\b", re.MULTILINE
)


def load_claims_whitelist():
    if not CLAIMS_WHITELIST.exists():
        return set()
    return {
        line.strip()
        for line in CLAIMS_WHITELIST.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }

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
    matched_by_source = {}
    matched_sources = {}
    for row in csv.DictReader(text.splitlines()):
        declared.add(row["name"])
        if row["status"] == "matched":
            matched.add(row["name"])
            matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
            matched_sources.setdefault(row["name"], set()).add(row["source"])
    return declared, matched, matched_by_source, matched_sources


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

        # a definition's signature line never ends with ';' — that's a call
        # statement or prototype (e.g. `BASECLASS::Read(buffer, size);`)
        if stripped.endswith(";"):
            match = None
        else:
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

    declared, matched, matched_by_source, matched_sources = read_function_names(FUNCTIONS_CSV, args.staged)
    whitelist = load_claims_whitelist()

    unmatched = []
    violations = []
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

        # Claims gate: a source file with ZERO byte-verified rows is not progress —
        # a wall of present-unmatched markers must not be committable as if it were.
        marker_labels = UNMATCHED_MARKER_RE.findall(text)
        file_matched = matched_by_source.get(rel_path.as_posix(), 0)
        if file_matched == 0 and rel_path.as_posix() not in whitelist:
            violations.append(
                f"{rel_path}: ZERO matched functions.csv rows — match at least one "
                f"function before committing this file, or whitelist it with a reason "
                f"(reverse/unclaimed_sources_whitelist.txt)"
            )
        for label, marker in marker_labels:
            # matched from ANOTHER file is correct bookkeeping (asm-whale scaffolds
            # claim symbols the verbatim ZH copy also defines); matched from THIS
            # file means the marker is stale
            if rel_path.as_posix() in matched_sources.get(label, ()):
                violations.append(
                    f"{rel_path}: {label} is matched in functions.csv from this file but "
                    f"still marked {marker} (stale annotation — remove the marker)"
                )
        if args.paths and marker_labels:
            print(
                f"note: {rel_path}: {file_matched} matched row(s), "
                f"{len(marker_labels)} unclaimed definition(s)"
            )

        for class_name, method_name, symbol_name in find_defined_functions(text):
            if symbol_name:
                # `// ?<mangled> absent-from-retail` marks a definition kept only to
                # force emission/instantiation of other matched functions; the retail
                # binary dead-stripped it, so there is no address for a CSV row.
                parts = symbol_name.split()
                if len(parts) >= 2 and parts[1] in ("absent-from-retail", "present-unmatched"):
                    # absent-from-retail: definition kept only to force emission of
                    # matched siblings; the retail binary dead-stripped it.
                    # present-unmatched: the function exists in retail but its bytes
                    # or address are not yet pinned; kept because trimming it would
                    # change inlining of matched functions in this TU.
                    continue
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

    if violations:
        for violation in violations:
            print(violation)
    if not unmatched and not violations:
        print("All defined functions are already matched.")
        return

    for rel_path, class_name, method_name in unmatched:
        print(f"{rel_path}: {class_name}::{method_name}")
    if args.fail:
        sys.exit(1)


if __name__ == "__main__":
    main()
