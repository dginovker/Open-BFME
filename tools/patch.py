#!/usr/bin/env python3
import argparse
from pathlib import Path

import build as build_tool


DEFAULT_OUTPUT = build_tool.PATCH_DIR / "lotrbfme.patched.exe"


def selected_rows(names):
    rows = build_tool.load_function_rows()
    if not names:
        return rows

    wanted = set(names)
    selected = [row for row in rows if row["name"] in wanted]
    found = {row["name"] for row in selected}
    missing = sorted(wanted - found)
    if missing:
        raise SystemExit(f"function not found: {', '.join(missing)}")
    return selected


def output_path(path):
    output = Path(path)
    if not output.is_absolute():
        output = build_tool.ROOT / output
    if output.resolve() == build_tool.EXE.resolve():
        raise SystemExit("refusing to patch the baseline executable in place")
    return output


def display_path(path):
    try:
        return path.relative_to(build_tool.ROOT)
    except ValueError:
        return path


def main():
    parser = argparse.ArgumentParser(description="Patch compiled function bodies into lotrbfme.exe.")
    parser.add_argument(
        "-f",
        "--function",
        action="append",
        dest="functions",
        help="Decorated function name to patch. Defaults to every row in reverse/functions.csv.",
    )
    parser.add_argument(
        "-o",
        "--output",
        default=DEFAULT_OUTPUT,
        help=f"Patched executable path. Defaults to {DEFAULT_OUTPUT.relative_to(build_tool.ROOT)}.",
    )
    args = parser.parse_args()

    symbol_map = build_tool.load_symbol_map()

    patches = []
    changed = 0
    for row in selected_rows(args.functions):
        patch = build_tool.compile_function(row, symbol_map)
        if len(patch["bytes"]) != len(patch["target"]):
            raise SystemExit(
                f"{patch['name']}: compiled size {len(patch['bytes'])} != "
                f"target size {len(patch['target'])}"
            )
        if patch["bytes"] != patch["target"]:
            changed += 1
        patches.append(patch)

    output = build_tool.patch_exe(patches, output_path(args.output))
    print(f"Patched: {display_path(output)}")
    print(f"Functions: {len(patches)} ({changed} changed)")
    print(f"sha256: {build_tool.hash_file(output, 'sha256')}")


if __name__ == "__main__":
    main()
