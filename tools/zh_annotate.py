#!/usr/bin/env python3
"""Annotate the unmatched (drifted) definitions in a landed Code/ file with the
project's established `// ?<mangled> present-unmatched` marker: the function exists in
retail but its bytes/address aren't pinned yet, and it stays in the TU because trimming
it could change inlining of the matched functions (find_declared_unmatched.py honors
the marker; the pre-commit hook enforces it).

Regenerates the file VERBATIM from the reference first (so a previous excision/annotation
run never compounds), inserts markers, then byte-verifies the matched set is unchanged.

Usage: python3 tools/zh_annotate.py Code/GameEngine/Source/Common/Dict.cpp [...]
"""
import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
sys.path.insert(0, str(ROOT / "tools"))
from find_declared_unmatched import mangle_method  # noqa: E402
from land_zh import prepared_source  # noqa: E402
import build  # noqa: E402


def matched_names(source_rel):
    names = set()
    with (ROOT / "reverse" / "functions.csv").open(newline="") as handle:
        for row in csv.DictReader(handle):
            if row["source"] == source_rel and row["status"] == "matched":
                names.add(row["name"])
    return names


def object_symbols(stem):
    """Mangled function symbols the TU actually emits (from the last build's obj)."""
    for candidate in (build.BUILD_DIR / f"{stem}.obj", build.BUILD_DIR / f"{stem}.harvest.obj"):
        if candidate.exists():
            data = candidate.read_bytes()
            return {s["name"] for s in build.read_object_symbols(data)
                    if s["section"] > 0 and s["name"].startswith("?")}
    return set()


DEFINITION = re.compile(
    r"^[\w:&*~\s]*?((?:\w+::)*\w+)::(operator[\s=\+\-\*/\[\]\(\)<>!]+|\~?\w+)\s*\(",
)


def annotate(path):
    source_rel = str(path.relative_to(ROOT))
    matched = matched_names(source_rel)
    reference_path = REF / path.relative_to(ROOT / "Code")
    ref_hits = ([reference_path] if reference_path.is_file() else
                [candidate for candidate in reference_path.parent.glob("*.cpp")
                 if candidate.name.casefold() == reference_path.name.casefold()])
    if not ref_hits:
        print(f"{path.name}: no reference original found — skipping regeneration")
        return False
    path.write_text(prepared_source(ref_hits[0]))

    symbols = object_symbols(path.stem)
    lines = path.read_text(errors="replace").splitlines(keepends=True)
    out = []
    count = 0
    for line in lines:
        stripped = line.strip()
        if not stripped.endswith(";"):
            found = DEFINITION.match(line)
            if found:
                class_name, method = found.group(1), found.group(2)
                if method.startswith("operator"):
                    method = "operator" + re.sub(r"\s+", "", method[len("operator"):])
                fragment = mangle_method(class_name.split("::")[-1], method)
                is_matched = (
                    any(name.startswith(fragment) for name in matched)
                    if fragment.startswith(("??0", "??1"))
                    else any(fragment in name for name in matched)
                )
                if not is_matched:
                    exact = [s for s in symbols if (s.startswith(fragment)
                             if fragment.startswith(("??0", "??1")) else fragment in s)]
                    label = exact[0] if len(exact) == 1 else fragment
                    out.append(f"// {label} present-unmatched\n")
                    count += 1
        out.append(line)
    path.write_text("".join(out))

    verify = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "build.py"), source_rel],
        cwd=ROOT, capture_output=True, text=True, timeout=420,
    )
    if verify.returncode != 0:
        print(f"{path.name}: verify FAILED after regeneration+annotation — investigate")
        print("    " + "\n    ".join(verify.stdout.strip().splitlines()[-3:]))
        return False
    print(f"{path.name}: {count} drifted definition(s) marked present-unmatched; byte-verify OK")
    return True


def main():
    if len(sys.argv) < 2:
        raise SystemExit("usage: zh_annotate.py <Code/.../file.cpp> [...]")
    ok = True
    for arg in sys.argv[1:]:
        ok &= annotate(Path(arg).resolve())
    raise SystemExit(0 if ok else 1)


if __name__ == "__main__":
    main()
