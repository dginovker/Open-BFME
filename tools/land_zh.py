#!/usr/bin/env python3
"""Land a GeneralsMD sweep winner: copy the reference .cpp verbatim into Code/
at its reference-relative (official tree) path, with the sweep-environment flags
head, fingerprint-locate its functions, emit the matched rows, and byte-verify
through build.py.

    python3 tools/land_zh.py Dict MessageStream GameAudio
    python3 tools/land_zh.py --dry-run GameEngine/Source/Common/Dict.cpp

Names may be reference basenames or paths (directories and .cpp are stripped).
--dry-run reports whether each name could land (reference file found, dest free)
without writing anything.

Winners come from reverse/zh_sweep/report.csv (tools/sweep_generalsmd.py). A file
whose located functions all fail verification is removed again — nothing lands
unverified. Landed files are verbatim ZH sources on purpose: the sweep shims
supply the environment via /I flags.

Exit code is 0 when every name landed or was skipped (already landed), 1 when
any name failed (no reference file, compile failure, nothing located).
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
DEST = ROOT / "Code"

REF_REL = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
HEAD = (
    f"// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /I{REF_REL}/GameEngine/Include"
    f" /I{REF_REL}/GameEngine/Include/GameNetwork"
    f" /I{REF_REL}/GameEngine/Source /I{REF_REL}/Libraries/Include /I{REF_REL}/Libraries/Source"
    f" /I{REF_REL}/Libraries/Source/Compression /I{REF_REL}/Libraries/Source/Benchmark"
    f" /I{REF_REL}/Libraries/Source/debug"
    f" /I{REF_REL}/Libraries/Source/WWVegas /I{REF_REL}/Libraries/Source/WWVegas/WWLib"
    f" /I{REF_REL}/GameEngineDevice/Include /I{REF_REL}/Libraries/Source/WWVegas/WW3D2"
    f" /I{REF_REL}/Libraries/Source/WWVegas/WWMath /I{REF_REL}/Libraries/Source/WWVegas/WWDebug"
    f" /I{REF_REL}/Libraries/Source/WWVegas/WWSaveLoad /I{REF_REL}/Libraries/Source/WWVegas/WWAudio"
    f" /I{REF_REL}/Main\n"
    "// stlport\n"
    "#define Matrix4x4 Matrix4  // BFME renamed it\n"
    "#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves\n"
)
SOURCE_HEADS = {
    "registry.cpp": '#include "registry_win32.h"\n',
    "w3dshadermanager.cpp": """#define HEAP_ZERO_MEMORY 8
extern \"C\" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern \"C\" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern \"C\" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
""",
}
SOURCE_REPLACEMENTS = {
    "registry.cpp": (('#include "inisup.h"', '#include <inisup.h>'),),
    "w3dshadermanager.cpp": (
        (
            "DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(0,   D3DXVECTOR4(0.3f, 0.59f, 0.11f, 1.0f), 1);",
            "D3DXVECTOR4 c0(0.3f, 0.59f, 0.11f, 1.0f); DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(0, &c0, 1);",
        ),
        ("SetPixelShaderConstant(1,   color, 1)", "SetPixelShaderConstant(1, &color, 1)"),
        (
            "DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(2,\tD3DXVECTOR4(m_curFadeValue, m_curFadeValue, m_curFadeValue, 1.0f), 1);",
            "D3DXVECTOR4 c2(m_curFadeValue, m_curFadeValue, m_curFadeValue, 1.0f); DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(2, &c2, 1);",
        ),
        ("*destMatrix *= offset;", "D3DXMatrixMultiply(destMatrix, destMatrix, &offset);"),
    ),
}


def prepared_source(ref_cpp):
    text = ref_cpp.read_text(errors="replace")
    for old, new in SOURCE_REPLACEMENTS.get(ref_cpp.name.casefold(), ()):
        text = text.replace(old, new)
    return HEAD + SOURCE_HEADS.get(ref_cpp.name.casefold(), "") + text


def land(name, dry_run=False):
    """True when landed or skipped, False when the name failed."""
    requested = Path(name.replace("\\", "/"))
    if requested.suffix.casefold() != ".cpp":
        requested = requested.with_name(requested.name + ".cpp")
    if len(requested.parts) > 1:
        exact = REF / requested
        hits = [exact] if exact.is_file() else []
    else:
        hits = sorted(REF.rglob(requested.name))
    if not hits:
        print(f"{name}: FAIL — no reference file {requested} under {REF.relative_to(ROOT)}")
        return False
    dest = DEST / hits[0].relative_to(REF)
    existing = next(
        (path for path in dest.parent.glob("*.cpp") if path.name.casefold() == dest.name.casefold()),
        None,
    )
    if existing is not None:
        print(f"{name}: SKIP — {dest.relative_to(ROOT)} already exists (already landed)")
        return True
    if dry_run:
        print(f"{name}: would land {hits[0].relative_to(ROOT)} -> {dest.relative_to(ROOT)}")
        return True
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text(prepared_source(hits[0]))

    proc = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "locate.py"), str(dest.relative_to(ROOT)), "--emit"],
        cwd=ROOT, capture_output=True, text=True, timeout=420,
    )
    out = proc.stdout
    emitted = re.search(r"emitted (\d+) row", out)
    if not emitted:
        # surface the actual blocker: locate prints cl's error lines on stdout
        summary = re.search(r"\d+ located.*", out)
        error = re.search(r"^.*error C\d+.*$", out, re.M)
        if summary:
            reason = summary.group(0)
        elif error:
            reason = error.group(0).strip()
        else:
            reason = (proc.stderr.strip().splitlines()
                      or [f"locate exited {proc.returncode} with no diagnostics"])[-1]
        print(f"{name}: FAIL — nothing landed ({reason})")
        dest.unlink()
        return False

    verify = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "build.py"), str(dest.relative_to(ROOT))],
        cwd=ROOT, capture_output=True, text=True, timeout=420,
    )
    result = (verify.stdout.strip().splitlines() or ["no output"])[-1]
    print(f"{name}: {emitted.group(1)} emitted -> {result}")
    if verify.returncode != 0:
        raise SystemExit(
            f"{name}: locate emitted rows that FAILED byte-verification — reconcile or revert "
            f"the functions.csv/symbols.csv rows before continuing (build output above)."
        )
    # mark drifted siblings present-unmatched (the pre-commit gate requires it) and re-verify
    annotate = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "zh_annotate.py"), str(dest.relative_to(ROOT))],
        cwd=ROOT, capture_output=True, text=True, timeout=420,
    )
    print("    " + (annotate.stdout.strip().splitlines() or ["annotation: no output"])[-1])
    if annotate.returncode != 0:
        raise SystemExit(f"{name}: present-unmatched annotation failed — see above")
    # the new source is untracked until added; rows referencing an untracked
    # file break every other clone once pushed
    print(f"    now: git add {dest.relative_to(ROOT)} reverse/functions.csv reverse/symbols.csv")
    return True


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("names", nargs="+",
                        help="reference basenames or paths (directories and .cpp stripped)")
    parser.add_argument("--dry-run", action="store_true",
                        help="report what would land without writing anything")
    args = parser.parse_args()

    if not args.dry_run:
        DEST.mkdir(parents=True, exist_ok=True)
    failed = []
    for raw in args.names:
        name = raw[:-4] if raw.lower().endswith(".cpp") else raw
        if not land(name, args.dry_run):
            failed.append(name)
    if failed:
        raise SystemExit(f"land_zh: {len(failed)} of {len(args.names)} failed: {', '.join(failed)}")


if __name__ == "__main__":
    main()
