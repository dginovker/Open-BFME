# Shared rules for automated contribution agents

You are one of many agents each working a **separate assigned plan file** in this
directory (e.g. `plans/deepseek/03-port-wwsaveload.md`). Read your plan file AND
this README in full before doing anything. This README is the part that is the
same for every agent; your plan file is your exclusive assignment.

## The mission (why nothing you commit can be wrong)

This project rebuilds `lotrbfme.exe` byte-for-byte from C++ source. A function
"matches" when the C++ you write compiles (MSVC 7.1) to **the exact bytes** at
that address in the original binary. The build **proves** this: `./build.sh`
byte-compares every tracked function and the pre-commit hook blocks any commit
that isn't identical. **You literally cannot commit a wrong or fake match** — the
worst outcome is a commit that doesn't happen. So: try things, let the build
judge, keep only what it accepts. Never argue with the byte comparison; it is
ground truth.

## Your latitude (you are an engineer, not a script)

Within your territory, use judgment freely: read the reference source, resolve
`#include` chains by copying headers, write small shims for headers your files
need, run `locate` as your own presence test, and reconcile drift with
`explain_mismatch`. You don't need permission for any of that — the byte compare
is the only judge. What you may NOT do is anything in "Hard rules" below.

## Gotchas already discovered (don't waste hours re-learning these)

- **Compiler flags go on line 1** of the `.cpp` as a comment: `// cl: /DNDEBUG /MD`.
  `/DNDEBUG` (retail strips asserts) is almost always needed. Add `/MD` when a file
  calls a CRT library function (`sprintf`, `rand`, `toupper`, `wcslen`, `bsearch`…)
  — retail links the DLL CRT, so those become `call [__imp__fn]`; without `/MD` you
  get a direct `call` and a mismatch. Add `/EHsc` when a function has an exception
  frame (its prologue starts `6a ff 68 …` / it constructs objects with destructors).
- **Use the `GeneralsMD/` (Zero Hour) reference variant first.** BFME tracks it, not
  base `Generals/`. If a class is 12 bytes too small or a member is missing, you're
  probably on the wrong variant.
- **BFME's RenderObjClass hierarchy (WW3D2) has pinned drift — trust the local
  headers.** `src/w3d/rendobj.h` / `refcount.h` / `part_buf.h` already encode it:
  PersistClass is DROPPED from RenderObjClass's bases, the base carries a 0x34-byte
  pad of unknown members, `RefCountClass::Release_Ref` is NON-virtual (call sites
  inline dec/test/Delete_This; Delete_This is vtable slot 0), and REF_PTR_RELEASE
  stores NULL inside the if. If a renderobj-derived port mismatches on member
  offsets or an extra vtable-pointer store, you are using a reference header where
  a local pinned one exists — prefer the local. Useful pinned addresses:
  `~RenderObjClass` = 0x0091FC10 (already in symbols.csv).
- **`// ?<name> present-unmatched` marker**: for a definition that exists in retail
  but isn't byte-pinned yet, kept because trimming would change inlining of matched
  functions. Use it instead of fake CSV rows (see src/w3d/part_buf.cpp).
- **`W3DMPO` does not exist in BFME.** In WW3D2 classes, delete `public W3DMPO,` and
  every `W3DMPO_GLUE(...)` line → single-vtable `RefCountClass` bases. Otherwise
  layout is off by a vtable pointer and nothing matches.
- **Header filenames are case-sensitive here.** The reference has `Vector.H`; the
  include says `vector.h`. Copy to the lowercase name: `cp .../Vector.H src/w3d/vector.h`.
- **Skip DX8/Direct3D/system-header walls.** If resolving includes leads to
  `dx8wrapper.h`, `d3d*.h`, `<windows.h>` (with real Win32 use), or similar, that file
  needs heavy shimming — SKIP it and move on. Data/container/math files rarely hit
  this; renderer files usually do.
- **Retail-empty debug macros.** `WWLOG_*`, `WWMEMLOG_*`, `WWASSERT`, `WWDEBUG_SAY`
  compile to nothing in retail. If they're undefined, it's because a debug flag is
  off — that's correct; supply empty `#define`s in a small local shim if needed.
- **`locate` says "unlocated" ≠ absent.** It can also mean a callee isn't a known
  function start yet. If you believe a function is present, confirm with a raw byte
  search or `explain_mismatch` before declaring it absent. But if its distinctive
  constants/strings appear 0 times in the exe, it's genuinely absent — SKIP.
- **Ambiguous shared inlines** (Vector3 ctors, `??_H` vector-dtor thunks, tiny
  getters): `locate` refuses to place them and it's right to. Don't hand-place them.

## First: confirm your environment is healthy (do this once, at the very start)

```bash
git lfs pull                 # fetch the baseline exe + toolchain (large)
./tools/setup_hooks.sh       # enable the pre-commit byte-check hook
./build.sh                   # MUST end with "Functions: OK N/N" + "No-op patch: OK"
```

If that final `./build.sh` does **not** print `No-op patch: OK`, STOP and report
"baseline broken" — do not try to fix the toolchain, and do not start work.

## Orientation ritual — RUN THIS EVERY TIME YOU START OR RESUME

Your memory is wiped periodically. Your progress lives in **git history** and in
your own **`plans/deepseek/PROGRESS-<your-name>.md`** file, not in your head. On
every start or restart:

1. Re-read your plan file and this README.
2. `git pull --rebase origin master` (get everyone's latest work).
3. `cat plans/deepseek/PROGRESS-<your-name>.md` (what you already did/skipped).
4. `git log --oneline --author=<your-name> | head` (double-check your commits).
5. Find the **first item in your worklist that is not yet done or skipped** and
   continue from there. Never redo a done item. Never start over.

## The match loop (per worklist item)

Your plan file gives the exact commands, but every archetype ends the same way:

```bash
./build.sh <your-file>       # compile + byte-compare just your file, seconds
# (green?) -> commit it (see push ritual). (not green?) -> follow your skip rule.
python3 tools/find_declared_unmatched.py --fail <your-file>   # must be clean before commit
```

## Committing straight to main — the SAFE PUSH RITUAL (never skip a step)

Everyone commits to `origin/master`. To avoid corrupting the shared ledger, do
**exactly** this for every commit — it is a dumb, safe loop:

```bash
# 1. commit only YOUR files (never use `git add -A`)
git add <the specific files you changed>
git commit -m "Port/Translate <thing>"          # the hook runs the full build; if it
                                                 # fails, your change was not actually a
                                                 # match — revert it and move on.
# 2. rebase onto everyone else's latest, then re-verify, then push
git pull --rebase origin master                  # CSV row-appends auto-merge (union driver)
./build.sh                                        # if it FAILS with "overlap"/"duplicate":
                                                 #   python3 tools/dedup_csv.py
                                                 #   git add reverse/functions.csv reverse/symbols.csv
                                                 #   git commit --amend --no-edit
git push origin master                            # if REJECTED (someone pushed first):
                                                 #   git pull --rebase origin master ; repeat from ./build.sh
```

Commit **one function (or one small file) at a time** so each push window is tiny
and rebases stay trivial.

## Hard rules — breaking these wastes everyone's work

- **Stay in your territory.** Only create/edit the files your plan file lists.
  Touching another agent's file causes conflicts that lose work.
- **Shared headers are READ-ONLY.** Never edit any header that already exists in
  `src/w3d/` and is not explicitly listed as yours. If you think you need to
  change one, you are wrong — SKIP that function and log it.
- **Copy new headers VERBATIM from the reference** (never overwrite an existing
  one). If another agent copies the same reference header, byte-identical copies
  merge cleanly. Only *your own territory's* `.cpp`/`.h` files may carry a custom
  shim — never give a shared-looking header (e.g. `persist.h`, `vector.h`) a
  divergent shim; if it truly needs one, SKIP the affected functions instead.
- **Never `git add -A` or `git add .`** — only `git add` the exact files you own.
- **Never commit a red build.** The hook enforces this; do not try to disable it.
- **Never leave `__declspec(naked)` asm as your "answer"** unless your plan file
  is a translation plan and the block was already naked when you started (then
  restoring it is the correct SKIP).
- **3 strikes then SKIP.** If a function resists after 3 genuine attempts, restore
  the original, write one line in your PROGRESS file, and move on. Never spin.

## Recording progress

Maintain `plans/deepseek/PROGRESS-<your-name>.md` (create it if missing; it is
yours alone, never edited by others). One line per worklist item:
`DONE <name>` / `SKIP <name> — <one-line reason>`. Commit it together with the
work it describes.

## Tool cheat-sheet

- `./build.sh <file>` — compile + byte-compare one file (fast). No arg = full build.
- `python3 tools/locate.py <file>` — compile a file and find where its functions
  live in the binary; `--emit` appends the matched rows to `reverse/functions.csv`.
- `python3 tools/find_declared_unmatched.py --fail <file>` — must pass before commit.
- `python3 tools/dedup_csv.py` — normalize the CSV ledgers after a merge conflict.
- `python3 tools/explain_mismatch.py '<mangled-name>'` — show the first differing
  byte + disassembly when a function is close but not matching.

## The reference source

BFME is the SAGE engine; EA's GPL C&C Generals source is vendored under
`reference/CnC_Generals_Zero_Hour/`. **Use the `GeneralsMD/` (Zero Hour) variant
first** — BFME's libraries track it. Match against the binary, which is truth.

## Advanced harvest techniques (2026-07 overnight findings)

These were discovered running the harvest at scale; use them to go faster.

- **Bulk-probe over a file LIST, not one at a time.** Sequential one-file probing
  missed big wins (part_emt +25, segline +22 were found only by sweeping a list).
  Copy a batch of untracked reference `.cpp`, apply the full recipe to each, keep
  the ones that locate >=2, harvest them together.
- **The full renderer recipe** (for WW3D2 files that hit `Matrix4x4`/DX8/Win32):
  line 2 `#define Matrix4x4 Matrix4` (BFME renamed it; 0 matched fns mangle
  Matrix4x4); `class CameraClass;` before `#include "rinfo.h"`; `#include
  "winbase_shim.h"` (declares lstrcpy/lstrlen/lstrcmpi/lstrcpyn + TRUE/FALSE);
  empty-guard shims for `dx8*.h`/`d3d*.h`; **stub the DX8 `Render`/`Create_Decal`/
  `Render_Material_Pass` bodies** (slice `lines[:open]+stub+lines[close+1:]` — the
  +1 skips the original `}`); add WW3D shim methods (`Get_Frame_Time`,
  `Get_Default_Native_Screen_Size`, N-Patch accessors) as C3861 errors demand;
  redirect angle-includes of local headers (`<tri.h>`) to quotes.
- **Re-locate cascade — run `tools/relocate_cascade.py` after EVERY harvest and
  after pulling.** New matches unlock previously callee-gated functions (their
  callees are now known starts). One pass after a merged PR cascaded +93. Free,
  safe, converges in a few passes.
- **Game files (`src/game/`): use the `prerts.h` shim** (see memory
  game-file-recipe). `#include "PreRTS.h"` -> `"prerts.h"`; flatten `Common/X.h`
  -> `x.h`; `Lib/BaseType.h` -> a `base_type.h` that includes prerts.h. Only files
  needing just AsciiString/UnicodeString (+ inline accessors you add safely) bring
  up; anything using `TheXxx` globals or extending a shared vtable (Xfer) is a wall
  or a bigger job. Extend AsciiString/UnicodeString inline, then FULL BUILD to
  confirm the existing matched fx-parser/module-factory fns survive.
- **Register-coloring / source-drift are the hard wall.** Functions that lack a
  clean locate-needle are disproportionately the ones whose retail bytes differ by
  register allocation (this-in-EDI-vs-EBP), frame-pointer retention (source-driven,
  `/EHsc` does NOT flip it), or genuine BFME-vs-GeneralsMD source rewrites (e.g.
  MeshGeometryClass::Compute_Vertex_Normals: retail 1236-byte frame vs GeneralsMD's
  8). `tools/anchor_by_string.py` and size-pairing FIND these (correct addresses)
  but they can't byte-match without the BFME source or a register technique — don't
  sink time into them; leave the address in a note and move on.
