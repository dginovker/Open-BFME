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
* `build.py <file>` does not reliably recompile when only an included header changed (it can verify a stale object and report green); a header/shim/layout edit is only proven by the full `./build.sh` — which the pre-commit hook runs for you.
* `src/zh/*.cpp` compile against the REFERENCE ZH headers (the `// cl: /Ireference/...` preamble), not `src/w3d`. MSVC's `#include "..."` same-dir rule means a header pulls siblings from ITS OWN dir first, so to shadow a reference header you must also shim every header on the include chain that names it (e.g. camera drift needed BOTH `camera.h` and `rendobj.h` in `reference/shims/sweep/` — shimming `rendobj.h` alone was invisible because reference `camera.h` pulled reference `rendobj.h`).
* Once the camera shim lands, the per-function lanes are DRY: a full `src/zh/*.cpp` `locate` sweep yields ~0 (the one hit, `InitDbghelp`, fails string-verify — pooled literal), `next_work`'s "literal quick wins" are class-layout/width drifts in disguise (rendobj +0x34, BitFlags 0xff->0x7ff, flag bits), and the structural queue is 100% systemic (File vtable −1 slot, Object +0x20, AsciiString/StringBase ctor, STLport `_List_node` 0x0c->0x2c). Further % needs a header/class-layout reconstruction + full `./build.sh`, NOT per-function edits. Also: structural-queue RVAs are often misplaced (e.g. `getClassMemoryPool` "true start" was actually the already-matched `getModuleNameKey`) — verify an RVA is unclaimed before analyzing.
* Many "size mismatch (110B vs 104B) / misplaced" structural candidates are ICF-folded twins: `getClassMemoryPool@X` and `getModuleNameKey@X` compile to identical 104B so the linker folds them to ONE address; we already match that address as `getModuleNameKey`. The 6 trailing `0xcc` are inter-function padding ghidra counted, not code — and the twin is NOT extra landable bytes (same RVA, one-name-one-address). Don't chase these.
* BFME was built with RTTI off (`/GR-`): only 33 type descriptors exist and they're all exception/STL/locale/ATL types — NO game class (no `File`/`Object`/`LocalFile`). So you cannot read a class vtable from the binary via RTTI; class layout must be triangulated from `call [reg+slot]` sites. Also note matched INI parsers dispatch via function-pointer tables (`call esi`/`edi`), not C++ vtables, so they don't expose the `File` vtable either.
* Confirmed by disassembling `parseDefaultColor` (0x485970): BFME `File::scanString` is vtable slot **9** (`call [eax+0x24]`, `eax=[esi]`=File vtbl) while our ZH build puts it at slot 10 (`0x28`) — so BFME's `File` really does have one fewer virtual before `scanString` (the +1 shift is real, not a misread). To pin the dropped slot you still need BFME's slots for the methods adjacent to `scanString` (`scanReal` our-slot-9, `print` our-slot-11); get them from functions that call those via vtable (not the fn-ptr INI parsers).
