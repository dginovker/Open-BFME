#!/usr/bin/env python3
"""Tests for tools/next_work.py against the live repo data plus a corrupt-ledger
fixture. Stdlib only, no pytest needed:

    python3 tools/tests/test_next_work.py
"""
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "next_work.py"
REF = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
POOL = 7


def run(args=(), slot=None, pool=None, cwd=ROOT):
    env = {k: v for k, v in os.environ.items() if k not in ("AGENT_SLOT", "AGENT_POOL")}
    if slot is not None:
        env["AGENT_SLOT"] = str(slot)
    if pool is not None:
        env["AGENT_POOL"] = str(pool)
    return subprocess.run(
        [sys.executable, str(cwd / "tools" / "next_work.py"), *args],
        env=env, cwd=cwd, capture_output=True, text=True, timeout=60, check=False)


def get_json(slot=None, pool=None, extra=()):
    proc = run(["--json", *extra], slot=slot, pool=pool)
    assert proc.returncode == 0, f"--json run failed (rc {proc.returncode}):\n{proc.stderr}"
    return json.loads(proc.stdout)  # test 4: must parse


def test_plain_run():
    proc = run()
    assert proc.returncode == 0, f"plain run failed (rc {proc.returncode}):\n{proc.stderr}"
    for needle in ("== 0. ledger health ==", "== 1. sweep winners", "== 2. drift quick wins",
                   "== 3. shim unblocking", "== 4. rest of the ladder ==",
                   "tools/land_ambiguous.py", "tools/list_naked_candidates.py"):
        assert needle in proc.stdout, f"plain output missing {needle!r}"
    print("PASS plain run: all sections present")


def test_partition():
    full = get_json()
    full_files = {c["file"] for c in full["sweep_winners"]}
    full_funcs = {c["function"] for c in full["drift_quick_wins"]}

    seen_files, seen_funcs = set(), set()
    for slot in range(1, POOL + 1):
        part = get_json(slot=slot, pool=POOL)
        files = {c["file"] for c in part["sweep_winners"]}
        funcs = {c["function"] for c in part["drift_quick_wins"]}
        assert not files & seen_files, f"slot {slot} sweep items overlap another slot"
        assert not funcs & seen_funcs, f"slot {slot} drift items overlap another slot"
        seen_files |= files
        seen_funcs |= funcs
    assert seen_files == full_files, (
        f"union of slot sweep sets != unfiltered set "
        f"(missing {full_files - seen_files}, extra {seen_files - full_files})")
    assert seen_funcs == full_funcs, (
        f"union of slot drift sets != unfiltered set "
        f"(missing {full_funcs - seen_funcs}, extra {seen_funcs - full_funcs})")

    anyrun = get_json(slot=3, pool=POOL, extra=["--any"])
    assert {c["file"] for c in anyrun["sweep_winners"]} == full_files, "--any must undo the filter"

    bad = run(["--json"], slot=0, pool=POOL)
    assert bad.returncode != 0 and "AGENT_SLOT" in bad.stderr, "slot 0 must fail loudly"
    print(f"PASS partition: {POOL} slots disjoint, union == unfiltered "
          f"({len(full_files)} sweep, {len(full_funcs)} drift items)")


def test_sweep_winners_validated(data):
    for c in data["sweep_winners"]:
        ref = REF / c["file"]
        assert ref.exists(), f"candidate reference file missing: {ref}"
        legacy_dest = ROOT / "src" / "zh" / (Path(c["file"]).stem.lower() + ".cpp")
        assert not legacy_dest.exists(), f"candidate already landed: {legacy_dest}"
        code_rel = Path(*Path(c["file"]).parts)
        code_dest = ROOT / "Code" / code_rel
        code_siblings = {p.name.casefold() for p in code_dest.parent.glob("*.cpp")}
        assert code_dest.name.casefold() not in code_siblings, f"candidate already landed: {code_dest}"
        assert c["command"].startswith("python3 tools/land_zh.py "), c["command"]
        assert c["landable"] >= 1, f"unlandable candidate listed: {c}"
    print(f"PASS sweep winners validated: {len(data['sweep_winners'])} candidates, "
          f"all reference files exist, none already in src/zh/")


def test_json_shape(data):
    for key in ("ledger", "sweep_meta", "slot", "pool", "filtered",
                "sweep_winners", "drift_quick_wins", "shim_blockers", "pointers"):
        assert key in data, f"--json output missing key {key!r}"
    for b in data["shim_blockers"]:
        assert b["files"] >= 1 and b["blocker"], f"bad blocker entry: {b}"
    assert len(data["shim_blockers"]) <= 8, "more than 8 blockers listed"
    print(f"PASS --json: parses, all keys present, {len(data['drift_quick_wins'])} drift wins, "
          f"{len(data['shim_blockers'])} blockers")


def test_corrupt_ledger():
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as tmp:
        tmp = Path(tmp)
        (tmp / "tools").mkdir()
        (tmp / "reverse" / "zh_sweep").mkdir(parents=True)
        (tmp / "src" / "zh").mkdir(parents=True)
        for name in ("next_work.py", "check_csv.py"):
            (tmp / "tools" / name).write_bytes((ROOT / "tools" / name).read_bytes())
        (tmp / "src" / "zh" / "stub.cpp").write_text("// stub\n")
        row = "?Foo@@QAEXXZ,,0x00400000,16,src/zh/stub.cpp,matched,\r\n"
        (tmp / "reverse" / "functions.csv").write_bytes(
            b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
            + (row + row).encode())  # duplicated row = the corruption under test
        (tmp / "reverse" / "symbols.csv").write_text("name,address,notes\n")
        (tmp / "reverse" / "zh_sweep" / "report.csv").write_text(
            "file,status,located,ambiguous,unlocated,blocker\r\n")
        (tmp / "reverse" / "zh_sweep" / "drift_report.csv").write_text(
            "function,source,size,candidate_rva,aligned_pct,class,first_diff,hint,votes\n")
        proc = run(cwd=tmp)
        out = proc.stdout + proc.stderr
        assert proc.returncode == 2, f"corrupt ledger must exit 2, got {proc.returncode}:\n{out}"
        assert "dedup_csv" in out, f"corrupt-ledger output must point at dedup_csv:\n{out}"
        assert "LEDGER CORRUPT" in out, f"missing fix banner:\n{out}"
        assert "sweep winners" not in out, "sections must not print when the ledger is corrupt"
    print("PASS corrupt ledger: exit 2, dedup_csv fix instructions, no sections")


def main():
    (ROOT / "build").mkdir(exist_ok=True)
    test_plain_run()
    data = get_json()
    test_json_shape(data)
    test_sweep_winners_validated(data)
    test_partition()
    test_corrupt_ledger()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
