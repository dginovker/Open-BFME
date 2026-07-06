#!/usr/bin/env python3
"""Bring-up probe: apply the full WW3D2 recipe to reference .cpp files and report
which ones compile and locate matchable functions.

Sequential one-file probing MISSED the biggest wins (part_emt +25, segline +22
were found only by sweeping a LIST). This automates the recipe so you can sweep
dozens of candidates and harvest the winners together. It NEVER overwrites a
git-tracked source file, and it leaves winners (>= --min located) on disk for you
to `locate --emit` + build + commit; non-winners are removed.

    python3 tools/harvest_probe.py part_emt segline collect coltest   # by basename
    python3 tools/harvest_probe.py --list WW3D2                       # all untracked in a lib

The recipe (per file), matching what landed the WW3D2/anim harvest:
  * line 1: `// cl: /DNDEBUG /MD`
  * line 2: `#define Matrix4x4 Matrix4`  (BFME renamed it; 0 matched fns mangle it)
  * `class CameraClass;` before `#include "rinfo.h"`
  * `#include "winbase_shim.h"` for lstr*/TRUE/FALSE
  * empty-guard shims for dx8*.h / d3d*.h
  * vendor any other missing header flat from the reference (angle->quote redirect)
  * STOP at windows.h / win.h walls
It does NOT stub DX8 Render bodies (do that by hand for renderer files — see
plans/deepseek/README.md "renderer recipe"); files needing it show as COMPILE-FAIL.
"""
import subprocess, sys, re, shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
W3D = ROOT / "src" / "w3d"


def tracked(path: Path) -> bool:
    return subprocess.run(["git", "ls-files", "--error-unmatch", str(path.relative_to(ROOT))],
                          cwd=ROOT, capture_output=True).returncode == 0


def find_ref(name: str, suffix: str):
    hits = list(REF.rglob(f"{name}{suffix}"))
    return hits[0] if hits else None


def apply_recipe(cpp: Path):
    t = cpp.read_text(errors="replace")
    head = "// cl: /DNDEBUG /MD\n#define Matrix4x4 Matrix4\n#include \"winbase_shim.h\"\n"
    if 'class CameraClass;' not in t and '#include "rinfo.h"' in t:
        t = t.replace('#include "rinfo.h"', 'class CameraClass;\n#include "rinfo.h"', 1)
    cpp.write_text(head + t)


def resolve_headers(cpp: Path, limit=30):
    for _ in range(limit):
        out = subprocess.run(["python3", str(ROOT / "tools" / "locate.py"), str(cpp.relative_to(ROOT))],
                             cwd=ROOT, capture_output=True, text=True).stdout + \
              subprocess.run(["python3", str(ROOT / "tools" / "locate.py"), str(cpp.relative_to(ROOT))],
                             cwd=ROOT, capture_output=True, text=True).stderr
        m = re.search(r"Cannot open include file: '([^']+)'", out)
        if not m:
            return
        base = Path(m.group(1)).name
        lc = base.lower()
        if lc in ("windows.h", "win.h") or lc.startswith(("dx8", "d3d")):
            if lc.startswith(("dx8", "d3d")):
                (W3D / lc).write_text(f"#pragma once\n#ifndef {lc[:-2]}_S\n#define {lc[:-2]}_S\n#endif\n")
                continue
            return  # windows wall
        dest = W3D / lc
        if dest.exists() or tracked(dest):
            return
        ref = find_ref(Path(base).stem, ".h")
        if not ref:
            return
        shutil.copy(ref, dest)
        # redirect local angle-includes to quotes
        for other in W3D.glob("*.h"):
            txt = other.read_text(errors="replace")
            if f"<{lc}>" in txt:
                other.write_text(txt.replace(f"<{lc}>", f'"{lc}"'))


def located(cpp: Path):
    out = subprocess.run(["python3", str(ROOT / "tools" / "locate.py"), str(cpp.relative_to(ROOT))],
                         cwd=ROOT, capture_output=True, text=True).stdout
    m = re.search(r"(\d+) located, (\d+) ambiguous, (\d+) unlocated", out)
    if m:
        return int(m.group(1)), out
    err = re.search(r"error C\d+[^\n]*", out)
    return None, (err.group(0) if err else "COMPILE-FAIL")


def probe(name: str, min_located: int):
    tgt = W3D / f"{name.lower()}.cpp"
    if tracked(tgt):
        print(f"{name}: TRACKED — skip")
        return
    src = find_ref(name, ".cpp")
    if not src:
        print(f"{name}: no ref")
        return
    shutil.copy(src, tgt)
    apply_recipe(tgt)
    resolve_headers(tgt)
    loc, info = located(tgt)
    if loc is None:
        print(f"{name}: FAIL {info}")
        tgt.unlink(missing_ok=True)
    elif loc >= min_located:
        print(f"{name}: WINNER {info.strip().splitlines()[0]}")
    else:
        print(f"{name}: {loc} located (< {min_located})")
        tgt.unlink(missing_ok=True)


def main():
    args = sys.argv[1:]
    min_located = 2
    if "--min" in args:
        i = args.index("--min"); min_located = int(args[i + 1]); del args[i:i + 2]
    names = []
    if "--list" in args:
        i = args.index("--list"); lib = args[i + 1]; del args[i:i + 2]
        tracked_names = {p.stem.lower() for p in ROOT.glob("src/**/*.cpp")}
        for cpp in (REF / "Libraries" / "Source" / "WWVegas" / lib).rglob("*.cpp"):
            if cpp.stem.lower() not in tracked_names:
                names.append(cpp.stem)
    names += args
    for n in names:
        probe(n, min_located)


if __name__ == "__main__":
    main()
