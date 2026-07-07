# BFME forked from Zero Hour (GeneralsMD) — binary-grounded proof + never-swept worklist

**Date:** 2026-07-06. **Question:** "ZH source is much closer to BFME, but we don't have it" — investigated.

## We DO have it
`reference/CnC_Generals_Zero_Hour/GeneralsMD/` **is** Zero Hour ("MD" = Mission Disk, EA's internal
name for the expansion). EA's GPL release ships both trees. GeneralsMD is the complete engine
(GameEngine, GameEngineDevice, WWVegas incl. WW3D2/WWLib/WWMath/WWSaveLoad, Tools): 2,892 .cpp/.h
vs Generals' 2,618. Every one of the 2,604 shared files differs at least trivially (EA re-stamped
banners); real content divergence ranges from 2 lines (UnicodeString.cpp) to 1,755 (ScriptEngine.cpp).

## The binary votes: BFME descends from ZH, not vanilla Generals
String-literal test over all GameEngine/Source .cpp (literals ≥10 chars, no escapes), presence in
lotrbfme.exe:
- unique-to-ZH strings: **939/1815 = 51% present in BFME**
- unique-to-Generals strings: **27/550 = 4% present**

(The ~49% of ZH-unique strings NOT in BFME = BFME's own post-ZH drift: LOTR replaced ZH gameplay.)

**Porting rule: always port game-side files from GeneralsMD, never from Generals.** (WW3D2 side was
already known — see ww3d2-generalsmd-variant; this extends the rule to the whole tree.)

## Never-swept worklist: 147 .cpp exist ONLY in ZH (couldn't be found sweeping Generals)
Ranked by fraction of their string literals present in the BFME binary:

| pct | hits | file |
|----:|-----:|------|
| 100% | 3/3   | Libraries/Source/debug/debug_internal.cpp |
| 81%  | 9/11  | Libraries/Source/debug/debug_stack.cpp |
| 78%  | 11/14 | Libraries/Source/debug/debug_cmd.cpp |
| 77%  | 7/9   | Libraries/Source/debug/debug_io_flat.cpp |
| 73%  | 39/53 | Libraries/Source/debug/debug_except.cpp |
| 65%  | 19/29 | Libraries/Source/debug/debug_debug.cpp |
| 65%  | 17/26 | GameEngineDevice/.../Draw/W3DTreeDraw.cpp |
| 59%  | 25/42 | GameEngine/Source/Common/System/ObjectStatusTypes.cpp |
| 58%  | 10/17 | GameEngine/Source/GameClient/Snow.cpp |

**The ZH-only `debug` library is the headline:** a whole standalone library (~10 .cpp, pch-based,
self-contained) absent from Generals, heavily present in BFME, and its symbols ARE in BFME's export
table (15+ `Debug@@` exports, e.g. `??$?6D@@YAAAVDebug@@AAV0@ABV?$StringBase@D@@@Z` body 0x5F590 —
note it streams BFME's StringBase<D>, confirming BFME-side adoption). Low-ranked ZH-gameplay files
(Sabotage*, BattleBus*, SpectreGunship*) are as-expected absent from BFME.

## Bring-up note for the debug lib
`_pch.h` includes `<windows.h>`; the vendored VS2003 toolchain has NO PlatformSDK (only Vc7/include),
so port via the established stub-header recipe (see game-file-recipe / src/game/winsock2.h precedent),
don't compile the reference tree in place.

## Reproduce
The string-vote and ranking scripts are one-liners over the trees + `build.read_target_bytes`; see
session notes. Core method: `strings_unique_to_tree ∩ exe_bytes`, per-file and tree-wide.
