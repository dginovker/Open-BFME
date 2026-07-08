# The ZH sweep pipeline (highest-yield path)

BFME forked from **Zero Hour** — `reference/CnC_Generals_Zero_Hour/GeneralsMD/` IS the ZH source
("MD" = Mission Disk), proven binary-side in `reverse/zh_provenance/FINDINGS.md` (51% of ZH-unique
strings appear in lotrbfme.exe vs 4% of Generals-unique). **Always port from `GeneralsMD/`, never
`Generals/`.** Many ZH functions still match BFME verbatim; this pipeline finds and lands them in bulk.

## The loop

```
python3 tools/sweep_generalsmd.py --area GameEngine/Source --skip-done   # hours; resumable
sort -t, -k3 -rn reverse/zh_sweep/report.csv | head -20                  # ranked winners
python3 tools/land_zh.py Dict MessageStream GameAudio                    # land them (basenames)
./build.sh && git add -A src/zh reverse && git commit                    # full verify runs in the hook
```

- **sweep** compiles each never-attempted reference `.cpp` against the reference's own engine
  headers (only Windows/SDK walls are shimmed — `reference/shims/sweep/`), then fingerprint-locates
  every emitted function in the binary (`tools/locate.py`: unique masked placement + callee
  validation; no export entry needed). Appends to `reverse/zh_sweep/report.csv`.
- **land_zh** copies the reference file **verbatim** into `src/zh/` with a 2-line head
  (`// cl:` flags carrying the `/I` include chain + `// stlport`), locates, emits the
  functions.csv/symbols.csv rows, **byte-verifies via build.py**, then marks every drifted sibling
  definition with the `present-unmatched` convention (`tools/zh_annotate.py`) so the pre-commit
  gate passes without pretending they're matched.

## Landing is not matching (claims gates)

Progress is **matched rows in reverse/functions.csv** — byte-verified on every build —
and nothing else. `present-unmatched` definitions are unclaimed reference text: invisible
to stats, never patched, never verified. Enforced mechanically, not by convention:

- a src `.cpp` owning ZERO matched rows fails both the pre-commit checker and the build's
  `Source claims` gate (explicit parked exceptions with reasons:
  `reverse/unclaimed_sources_whitelist.txt`; stale entries also fail);
- a marker on a symbol matched **from the same file** fails (stale annotation);
- `land_zh.py` refuses files where locate finds nothing.

Audit any session's real output before believing a "done" claim:
`python3 tools/progress.py <ref>` — verified functions/bytes delta + marker delta.
Anything claimed beyond those numbers is unverified prose.

## Growing the shims (when the sweep reports blockers)

The sweep summary histograms blockers. Fix the top one, delete its rows from the report
(or rerun without `--skip-done` on those files), re-sweep. Rules learned the hard way:

- Never edit the reference tree. Shadow-patch instead: copy the header into
  `reference/shims/sweep/<same relative path>` and fix it there (shims precede the reference in
  `/I` order). Precedent: `GameClient/Display.h` (a VC6-only default-arg on a function typedef).
- `windows.h` stand-in declarations must be `__declspec(dllimport) __stdcall` with exact SDK
  signatures — that's what makes call-site codegen byte-identical. STLport re-declares some
  (`InterlockedIncrement(long volatile *)`); any signature drift is a C2733 hard error.
- `#define __PLACEMENT_VEC_NEW_INLINE` before `<new>`: GameMemory.h defines array placement
  new itself (its scalar one is commented out, so the CRT's must stay visible).
- Constants in stubs must be the real SDK values (DIK_* scancodes, MB_* flags…) — they compile
  into instruction immediates.

## Traps

- **grep on reference files silently returns nothing** (the © byte makes them "binary"): use
  `grep -a`.
- Quoted includes resolve file-relative *first*: a swept file placed in `src/game/` picks up
  `src/game/prerts.h` instead of the sweep shims. That's why landed files live in `src/zh/`.
- `locate.py` CONFLICT/AMBIGUOUS lines are conservative skips, not errors — leave them; never
  hand-force an address.
- A landed file whose excised/annotated sibling was *inlined* by a matched function will fail the
  byte-verify — land_zh reverts it; reconcile manually or drop that file.
- The pre-commit hook runs the full build (several minutes); don't bypass it, budget for it.

## Territory map (string-vote: fraction of an area's literals present in lotrbfme.exe)

Sweepable, in current include-chain order of value:
- `GameEngine/Source` (51% overall) — first swept; the richest area.
- `GameEngineDevice/Source/W3DDevice` (25%, 206 hits) + `Win32Device` (42%) — renderer/OS glue;
  needs the d3d8 shim routing + `#define Matrix4x4 Matrix4` (BFME renamed it), already in the HEAD.
- `Libraries/Source/WWVegas/WWLib` remainder (48% strings but mostly from already-landed files;
  measured yield small — refcount/mutex drifted). Probe route: `tools/harvest_probe.py --min 1 <names>`.

**Measured DEAD — do not sweep** (0–5% string survival; BFME replaced these subsystems):
`wwshade` (own shader system), `WWSaveLoad` (BFME uses Xfer/Snapshot), `WWAudio` + `MilesAudioDevice`
(audio rewritten; no "Miles Sound System" banner in the exe), `VideoDevice` (Bink wrapper rewritten).
Evidence: reverse/zh_provenance/FINDINGS.md method, measured 2026-07-06.

## Reconciling drift (the tail after the verbatim tier)

`python3 tools/drift_classify.py` ranks every drifted function (`present-unmatched` in landed files)
into `reverse/zh_sweep/drift_report.csv`: best candidate address in the binary (voted by known-callee
call sites, verified string refs, rare byte runs), % aligned, and a **class that tells you what to do**:

- **`immediate-only`** — same code shape, a literal/offset changed (BFME resized a class, tweaked a
  constant). THE mechanical queue: find the value in the ZH source, fix it, `./build.sh <file>`,
  then `tools/locate.py <file> --emit` to land the now-exact function. Remove its
  `present-unmatched` marker.
- **`structural`** — real logic drift; the hint gives shape-ratio and size delta. Medium task:
  disassemble at the candidate (`objdump`-style windows via tools/explain_mismatch.py once a row
  exists) and reconcile the source against the binary.
- **`register-swap` / `imm+reg` with heavy reg diffs** — the MSVC global-regalloc wall (proven on
  the whales). Do NOT burn time trying C++ source tweaks; these are asm-recipe candidates at best.
- **`absent`** — anchors found no plausible placement; BFME likely removed it. Prune it from plans.
- **`no-anchors`** — too small/reloc-dense to fingerprint; needs a manual look, low priority.

The report is ADVISORY: candidates are heuristic votes. Nothing lands without the byte-verify +
gate suite, so a wrong candidate costs a look, never a bad match. Re-run the tool after landing
batches — newly pinned callees improve candidates for the rest (same fixpoint idea as
tools/relocate_cascade.py).

## State

`reverse/zh_sweep/report.csv` is the sweep ledger (resumable via `--skip-done`).
`src/zh/` files are verbatim ZH sources: reconciling a `present-unmatched` sibling against the
binary is a normal `docs/matching.md` task afterwards — start from the ZH text, not from scratch.
147 files exist ONLY in ZH (never in Generals): ranked candidates in `reverse/zh_provenance/FINDINGS.md`.
