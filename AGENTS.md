# How to Contribute

You are usually one of several agents pushing to the same `origin/master`.
The workflow docs: `docs/matching.md` (core byte-matching loop) and
`docs/structural.md` (the manual-RE tier, where most remaining work is).
Hard-won operational facts live in `docs/lessons.md` — read it once, it is
short and true.

## Session start (once)

1. `git pull --rebase origin master` — never work on a stale base.
2. `python3 tools/check_csv.py` — if it fails, fix the ledger FIRST
   (`python3 tools/dedup_csv.py`, then byte-verify any surviving conflict).
3. `python3 tools/next_work.py` — your ranked, validated work queue.

## The loop (every iteration, no exceptions)

1. Pick ONE small unit from `tools/next_work.py` (one function or one file).
2. Do the work; iterate with `./build.sh <file-or-symbol>` (seconds).
3. `git add <specific files>` — never `git add -A` or `git add .` Landed a
   new source? Add THAT FILE too (check `git status` for `??` entries) —
   ledger rows referencing an untracked file break every other clone.
4. `git commit` — the hook takes seconds (static ledger checks + byte-verify
   of your delta). NEVER `--no-verify`: a bad row committed here becomes
   every other agent's red build.
5. `git pull --rebase origin master`, `git push`, then
   `git pull --rebase origin master` AGAIN — after EVERY commit, not at
   session end. The final pull is mandatory: start the next unit from the
   latest shared tree. Push rejected? pull, push, and final-pull again. Merge
   made `check_csv` fail? `python3 tools/dedup_csv.py`, commit the fix, and
   repeat the pull-push-pull sequence.
6. Work you don't commit+push is work that evaporates. Bank every win
   immediately; then start the next unit.

## Ghidra queue loop

Repeat this loop while manual reverse-engineering work remains:

1. `python3 tools/next_work.py --tier ghidra` — take the first fresh candidate.
   If the anchored queue is dry, use `--tier structural`.
2. Run the candidate's printed `explain_mismatch.py` command, then decompile
   its RVA with `tools/ghidra/decompile_function.java` (see
   `tools/ghidra/README.md`). Use Ghidra boundaries, xrefs, callees, and vtables
   as identity evidence; never trust decompiled C as byte-match proof.
3. Reconcile one function. Resolve REL32 pins only while call sites still
   align; after early shape drift, bogus decoded calls are not evidence.
4. Exact match: `tools/add_match.py`, focused `build.sh`, commit, pull-push-pull.
   No match: revert source edits, `tools/log_attempt.py`, commit, pull-push-pull.
5. Re-run the queue. Logged candidates sort behind fresh work; never hand-pick
   yesterday's blocker while an untried candidate remains.

## When your current approach runs dry, fall down this ladder — do not stop, do not ask

Clean C++ is the deliverable; a MASM dump is a byte-blob, not source. Prefer
C++ for any field/logic body — dump only x87/SEH/codegen-blocked ones.

1. Thunk-dump → C++: a 5-byte `E9 rel32` in `Code/masm_dumps/` jumps to the
   body clean C++ compiles to. Write it, repoint the row, delete the .asm,
   verify. Surface them: `python3 tools/list_thunk_dumps.py`.
2. Stub/drifted class blocking a dump cluster: pin its offsets from several
   accessor bodies, shim the layout TU-scoped (private `/I`), convert the
   cluster. Precedent: `reference/shims/gamewindow/`.
3. `python3 tools/land_ambiguous.py` — string-anchored drift copies.
4. Structural RE: `tools/next_work.py --tier structural`, per
   `docs/structural.md`; 30-60 min/function, log EVERY attempt
   (`tools/log_attempt.py`), 3 strikes → move on.
5. REL32 pin (`reverse/symbols.csv`, docs/matching.md), or a small
   `__asm`/export → C++ (`tools/list_naked_candidates.py Code --limit 20`).

## Tree layout

Sources live under `Code/` at the official BFME tree path (from `__FILE__`
strings in the exe): `Code/GameEngine/{Source,Include}/...`,
`Code/GameEngineDevice/...`, `Code/Libraries/Source/WWVegas/{WWLib,WWMath,WWDebug,WW3D2,...}`.
New hand-ports go to the same official location as the original file.
Headers are shared truth — moving/editing one means every source that
includes it must still byte-match.

## File placement

* Sources → `Code/` at the official BFME path (exe `__FILE__` strings;
  mirror the ZH reference tree). No invented layouts (`src/`, `zh/`,
  `game/`, repo root) — all tried before, all deleted. The pre-commit hook
  rejects sources added anywhere else.
* MASM dumps → `Code/masm_dumps/`; scratch → untracked `build/`;
  `tools/` is dev tooling — never game code.

## Stopping rules

* 3 failed attempts on one function → note it and move on (skip, don't sink).
* ~30 minutes on one function with no byte-progress → same.
* NEVER end a session with uncommitted work. If it verifies, commit and push
  it; if it doesn't, revert it — half-done state left in the tree is lost.
* Do not ask the user what to do next; the ladder above is the answer.

## Verification

* NEVER full-gate (`./build.sh` no-args) a clean `origin/master` checkout —
  it's already green and its ~10-min exclusive lock stalls everyone else.
  Per-file builds + the commit/push hooks verify your delta. Full-gate ONLY
  after a hand-resolved merge.
* Never pipe gate commands through `tail`/`grep` in a way that masks the
  exit code. Check `$?` of the build itself.
* `tools/progress.py <start-ref>` counts ledger rows — it does not verify.
  Only `build.sh` output is proof.

## No push access? (external contributors / forks)

Fork, branch from `master`, same loop, but PR per small batch instead of
pushing: one contribution per commit, rebased on upstream, full gate green
before opening. Maintainers verify with `tools/verify_pr.sh <pr#>`; state your
gate output or the PR gets rebuilt from scratch (no server CI).

# Rules

* Keep it lean — code and docs. Temp scripts/tests are fine if you clean them
  up. A commit past 33% above the project's median size deserves a hard look.
* Don't add fallback code paths as a convenience. They hide mismatches and
  create subtle bugs that cost more time than they save. If the original
  toolchain matters, use the original toolchain.
* Progress = matched functions.csv rows backed by real source. Landing
  `present-unmatched` markers is not work; gates reject zero-matched sources.
* Never read `reverse/functions.csv`, `reverse/ghidra_functions.csv`, or
  `reverse/exports.csv` into your context — they are huge. Query them with
  the tools or grep/python.
* Learned something operational the docs don't cover? Append ONE line to
  `docs/lessons.md`. That file is the only doc you may extend without
  explicit user permission.
