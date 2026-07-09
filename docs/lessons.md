# Lessons

Operational facts agents paid for once already. Append ONE line per lesson
(what + the working alternative). Keep entries that stay true; delete ones a
tool fix has made obsolete.

* `land_zh.py` takes reference BASENAMES (`Dict`), not paths; 1-2 per call — batching many files blows the subprocess timeout and hides which succeeded.
* `sweep_generalsmd.py --files` also wants basenames without `.cpp`.
* The sweep report's `located` counts are an upper bound from sweep time: sub-`--min-size` functions and rows other agents landed since make `land_zh` return "nothing landed" — that's stale data, not a bug.
* `functions.csv` is CRLF; python `csv.writer` defaults reformat the whole file. Use `tools/dedup_csv.py` / binary-safe edits, never hand-rolled rewrites.
* Mangled names contain commas — `awk -F,`/`cut -d,` mis-parse both ledgers; use python `csv` or the tools.
* `harvest.py` recompiles the whole file per run (3-20s); never loop it over all of `src/` — 40 min of that produced 0 matches overnight.
* Piping a gate command through `tail`/`grep` masks its exit code; agents have shipped broken rows because "the output looked green".
* Compile errors from `land_zh` were once swallowed; run `tools/sweep_generalsmd.py --files <name>` to see a file's real blocker.
* A near-match (register choice, branch layout, x87 order) is a FAILURE — revert it; do not commit "close".
* Drift-report rows lack resolved callees; hand-appending them to functions.csv fails the gate later. Only `locate.py --emit` / `land_zh.py` / `land_ambiguous.py` write safe rows.
* String literals must be byte-exact incl. encoding: a CP1252 `µ` re-encoded to UTF-8 U+FFFD passed compile and failed the string-ref gate. Use `\xNN` escapes for non-ASCII bytes.
* After compaction/summarization, trust `git status` + `tools/progress.py`, not your summary's claims about what was reverted or committed.
* Inline `static`/tiny helpers (e.g. `flipCoord3D`) often don't exist standalone in the binary — a "unique" locate hit inside another function's body is a misplacement; check `ghidra_functions.csv` boundaries before claiming.
* This host runs a second fleet (`~/Projects/fleet/wt/*`) sharing wine and /tmp (tmpfs with quota): never kill cl.exe/build.py by name — scope by path; if /tmp hits quota, set TMPDIR to a repo-local dir.
* `locate.py --emit` historically appended LF-tail rows into the CRLF ledger; `tools/add_match.py` / `tools/dedup_csv.py` write it correctly — prefer them over hand-appends.
