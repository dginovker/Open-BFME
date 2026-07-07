#!/usr/bin/env python3
"""Land a GeneralsMD sweep winner: copy the reference .cpp verbatim into src/zh/
with the sweep-environment flags head, fingerprint-locate its functions, emit the
matched rows, and byte-verify through build.py.

    python3 tools/land_zh.py Dict MessageStream GameAudio

Winners come from reverse/zh_sweep/report.csv (tools/sweep_generalsmd.py). A file
whose located functions all fail verification is removed again — nothing lands
unverified. src/zh/ holds verbatim ZH sources on purpose: the sweep shims supply
the environment via /I flags, and src/game's own prerts.h must not shadow them.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
DEST = ROOT / "src" / "zh"

REF_REL = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
HEAD = (
    f"// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /I{REF_REL}/GameEngine/Include"
    f" /I{REF_REL}/GameEngine/Source /I{REF_REL}/Libraries/Include /I{REF_REL}/Libraries/Source"
    f" /I{REF_REL}/Libraries/Source/WWVegas /I{REF_REL}/Libraries/Source/WWVegas/WWLib"
    f" /I{REF_REL}/GameEngineDevice/Include /I{REF_REL}/Libraries/Source/WWVegas/WW3D2"
    f" /I{REF_REL}/Libraries/Source/WWVegas/WWMath /I{REF_REL}/Libraries/Source/WWVegas/WWDebug\n"
    "// stlport\n"
    "#define Matrix4x4 Matrix4  // BFME renamed it\n"
)


def land(name):
    hits = sorted(REF.rglob(f"{name}.cpp"))
    if not hits:
        print(f"{name}: no reference file")
        return False
    dest = DEST / f"{name.lower()}.cpp"
    if dest.exists():
        print(f"{name}: {dest.relative_to(ROOT)} already exists")
        return False
    dest.write_text(HEAD + hits[0].read_text(errors="replace"))

    out = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "locate.py"), str(dest.relative_to(ROOT)), "--emit"],
        cwd=ROOT, capture_output=True, text=True, timeout=420,
    ).stdout
    emitted = re.search(r"emitted (\d+) row", out)
    if not emitted:
        summary = re.search(r"\d+ located.*", out)
        print(f"{name}: nothing landed ({summary.group(0) if summary else 'compile fail'})")
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
    return True


def main():
    if len(sys.argv) < 2:
        raise SystemExit("usage: land_zh.py <RefBasename> [...]")
    DEST.mkdir(parents=True, exist_ok=True)
    for name in sys.argv[1:]:
        land(name)


if __name__ == "__main__":
    main()
