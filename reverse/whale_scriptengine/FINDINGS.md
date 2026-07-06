# ScriptEngine::init() whale — analysis (not yet matched)

**Target:** 0x003107F0, 57,072 B = BFME `ScriptEngine::init()` action-template registration.
**Sibling:** 0x003307E0, 19,131 B = script-CONDITION templates (same structure).

## Recovered facts (verified by disassembly)
- **Only callee:** `AsciiString::operator=(const char*)` @ export rva 0x28BB9 (body 0x62040, MATCHED). Every `call` is a string assignment. No out-of-line helper (so NO inline-budget issue).
- **`Template` layout** (`Scripts.h` class Template : public MemoryPoolObject), **sizeof = 0x7C (124)**:
  - +0x00 vtable ptr (MemoryPoolObject has a vtable — 4-byte shift)
  - +0x04 m_uiName, +0x08 m_uiName2, +0x0C m_internalName (AsciiString=4B each)
  - +0x10 m_internalNameKey (Int)  +0x14 m_numUiStrings (Int)
  - +0x18 m_uiStrings[12] (AsciiString[12], +0x18..+0x44)
  - +0x48 m_numParameters (Int)  +0x4C m_parameters[12] (enum ParameterType[12], +0x4C..+0x78)
- **Array member:** `m_actionTemplates` at `ScriptEngine + 0x1C` (this=esi). ScriptEngine : SubsystemInterface.
- **BFME enum values are scattered** (NOT sequential): DEBUG_MESSAGE_BOX=0, DEBUG_STRING=104, DEBUG_CRASH_BOX=220, SET_FLAG=1, ... (array has 508+ slots). Source order ≠ enum order; each block does `curTemplate = &m_actionTemplates[ENUM]`.
- **Per-template source order** (matches Generals ScriptEngine.cpp shape):
  internalName; uiName; numParameters; parameters[0..]; numUiStrings; uiStrings[0..].
- Param enum values 0..19+ seen (Parameter::ParameterType).

## Why it's a hard multi-session whale (NOT a one-shot)
Unlike ModuleFactory (independent inline blocks), this function:
1. **Caches constants in registers ACROSS blocks** — `mov ebp,1` then ebp reused for numParameters/numUiStrings in this AND the next block without reload; likewise a cached param-enum in ebx. Reproducing requires MSVC's GLOBAL register allocator to match over all 9844 instructions.
2. **Interleaves the int stores between each string-assignment's `lea ecx` and `call`** (scheduling-sensitive).
So it's all-or-nothing: generate all ~247 templates, compile the whole function, and it must match — not incrementally verifiable. Needs many build/explain_mismatch cycles.

## Artifacts here
- `extract_actions.py` — linear x86 decoder + state-machine field extractor for 0x3107F0.
- `actions_worklist.json` — ~unique action templates by internalName (extraction ~90% clean; residual noise: a few imm stores mis-attributed to uiStrings[5]/[6] slots — the cached-register stores need offset disambiguation).

## Recipe to finish (for a dedicated attempt)
1. Fix extractor's stale-base attribution (track per-block base reset; disambiguate cached-register int stores).
2. Reconstruct `struct Template { void* vtbl; AsciiString m_uiName,m_uiName2,m_internalName; int m_internalNameKey,m_numUiStrings; AsciiString m_uiStrings[12]; int m_numParameters; int m_parameters[12]; };` (sizeof 0x7C) + `ScriptEngine` with `Template m_actionTemplates[N]` at +0x1C.
3. Generate init() from worklist in source order (enum index literals). `// cl: /EHsc`.
4. Iterate the WHOLE function with explain_mismatch (register alloc will be the fight).
