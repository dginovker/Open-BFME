# How to Contribute

You are usually one of several agents pushing to the same `origin/master`.
The workflow docs: `docs/matching.md` (core byte-matching loop),
`docs/zh_sweep.md` (bulk ZH porting). Hard-won operational facts live in
`docs/lessons.md` — read it once, it is short and true.

## Session start (once)

1. `git pull` (rebases automatically) — never work on a stale base.
2. `python3 tools/check_csv.py` — if it fails, fix the ledger FIRST
   (`python3 tools/dedup_csv.py`, then byte-verify any surviving conflict).
3. `python3 tools/next_work.py` — your ranked, validated work queue.

## The loop (every iteration, no exceptions)

1. Pick ONE small unit from `tools/next_work.py` (one function or one file).
2. Do the work; iterate with `./build.sh <file-or-symbol>` (seconds).
3. `git add <specific files>` — never `git add -A` or `git add .`
4. `git commit` — the hook takes seconds (static ledger checks + byte-verify
   of your delta). NEVER `--no-verify`: a bad row committed here becomes
   every other agent's red build.
5. `git pull` then `git push` — after EVERY commit, not at session end.
   Push rejected? `git pull` and push again. Merge made `check_csv` fail?
   `python3 tools/dedup_csv.py`, commit the fix, push.
6. Work you don't commit+push is work that evaporates. Bank every win
   immediately; then start the next unit.

## When your current approach runs dry, fall down this ladder — do not stop, do not ask

1. `python3 tools/land_ambiguous.py` — string-anchored exact-ambiguous drift
   copies; cheapest wins when available.
2. `tools/next_work.py` sweep winners → `python3 tools/land_zh.py <Basename>`
   (one or two at a time; big batches time out). If a winner comes back
   "0 located", the report entry is stale — refresh it with
   `python3 tools/sweep_generalsmd.py --files <Basename>` and move on; when
   the whole sweep section is dry, rung 3 is where the volume is.
3. Grow a shim to unblock swept-out areas: `reverse/zh_sweep/report.csv`
   rows with `missing-header`/`compile-error` blockers. Add MINIMAL verbatim
   declarations to `reference/shims/sweep/`, then re-sweep those files.
4. Drift reconciliation: `reverse/zh_sweep/drift_report.csv` class
   `immediate-only` first (fix a constant), then `imm+reg`. `structural` and
   `absent` are real reverse-engineering — budget accordingly.
5. Resolve REL32-blocked functions: find the callee address, add a
   `name,address` pin to `reverse/symbols.csv` (see docs/matching.md).
6. Translate a `__asm` block or a small unmatched export to C++
   (`python3 tools/list_naked_candidates.py src --limit 20`).

## Stopping rules

* 3 failed attempts on one function → note it and move on (skip, don't sink).
* ~30 minutes on one function with no byte-progress → same.
* NEVER end a session with uncommitted work. If it verifies, commit and push
  it; if it doesn't, revert it — half-done state left in the tree is lost.
* Do not ask the user what to do next; the ladder above is the answer.

## Verification

* Full gate (`./build.sh`, no args) at session START only, or after a messy
  merge — it takes ~10 minutes solo, longer when other clones build. The
  commit/push hooks already verify your delta; don't re-run full builds
  around every commit.
* Never pipe gate commands through `tail`/`grep` in a way that masks the
  exit code. Check `$?` of the build itself.
* `tools/progress.py <start-ref>` counts ledger rows — it does not verify.
  Only `build.sh` output is proof.

## No push access? (external contributors / forks)

Fork, branch from `master`, same loop — but instead of pushing to master,
open a PR per small batch: each commit one contribution, rebased on upstream
`master`, full local gate green before opening. Maintainers verify with
`tools/verify_pr.sh <pr#>` and merge; no CI runs server-side, so a PR that
does not state its gate output will be rebuilt from scratch and reviewed
slower.

# Rules

* Keep shit lean. It's very easy to generate verbose code and verbose docs
  with AI. Always ask yourself if you're being helpful by generating it.
  Temporary scripts and tests are fine if you clean them up. Really ask
  yourself a question if your commit is larger than 33% of the median of
  previous commits in the project.
* Don't add fallback code paths as a convenience. They hide mismatches and
  create subtle bugs that cost more time than they save. If the original
  toolchain matters, use the original toolchain.
* Progress = matched functions.csv rows, nothing else. Landing files of
  `present-unmatched` markers is not work, and the gates reject sources with
  zero matched rows.
* Never read `reverse/functions.csv`, `reverse/ghidra_functions.csv`, or
  `reverse/exports.csv` into your context — they are huge. Query them with
  the tools or grep/python.
* Learned something operational the docs don't cover? Append ONE line to
  `docs/lessons.md`. That file is the only doc you may extend without
  explicit user permission.
