# Progress: translate-game-misc (Agent 16)

## Attempted / Skipped

| File | Line | Symbol / Function | Status | Notes |
|------|------|-------------------|--------|-------|
| `src/game/xfer.cpp` | 988 | `?XferRawBytes@Xfer@@UAEAAV1@PAXI@Z` | SKIPPED | Tried 4 C++ shapes; could not reproduce MSVC's exact register/stack scheduling (original saves `edi` for `data`, uses `lea [esp+0x14]`, and emits a redundant null test). Restored original naked block. |
| `src/game/memory_pool.cpp` | 28 | `MemoryPool::_IsValidBlock` | SKIPPED | References hardcoded globals (`0x0130e9f9`, `0x0130ea10`) and an unknown callee; no matching C++ symbols available. Risk of fake/magic-number translation. |
| `src/game/ascii_string.cpp` | 101 | `AsciiString::AsciiString(const UnicodeString &)` | SKIPPED | Exception-frame prologue, SEH, Unicode→ASCII conversion call, x87 — high scheduling risk. |
| `src/game/ascii_string.cpp` | 224 | `AsciiString::operator+=(const UnicodeString &)` | SKIPPED | Similar to ctor; string conversion + SEH + multiple branches. |
| `src/game/debug.cpp` | 3 | `Debug::PreStaticInit` | SKIPPED | SEH prologue, operator-new call, static global init; large and scheduling-sensitive. |
| `src/game/game_client_random_variable.cpp` | 30 | `GameClientRandomVariable::getValue` | SKIPPED | x87 distribution dispatch (CONSTANT/UNIFORM/...), FPU status checks, call to unknown random function. |

## Result

No translations landed in this pass. The remaining game-misc naked blocks are all
allocator/global-heavy, SEH-framed, string-conversion, or x87-dispatch functions and
fall into the "skip freely, never spin" category per
`plans/deepseek/16-translate-game-misc.md`.

All owned files were left byte-verified green:
- `src/game/xfer.cpp`: 35/35 matched
