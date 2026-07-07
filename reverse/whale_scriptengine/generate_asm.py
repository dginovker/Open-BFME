#!/usr/bin/env python3
"""Generate the naked-asm landing of the ScriptEngine action-template whale
ScriptEngine::init (0x3107f0, 57072 bytes) — the single biggest function in lotrbfme.exe.

C++ was proven capped at ~44% aligned by MSVC's global register allocation across 537 template
blocks (see FINDINGS.md). Per the asm-for-whales directive, transcribe the exact bytes as a
__declspec(naked) function. Reached via an incremental-link jmp thunk (0x4b169); it is the action
registration inline in ScriptEngine::init (SubsystemInterface override, virtual void) — confirmed by
the this->m_actionTemplates(+0x1c) prologue and the reference GeneralsMD ScriptEngine::init shape.

Byte-verified + whole-binary-SHA-verified. The recovered understanding (actions_worklist.json: 541
templates, enum order, layout) is preserved separately. Fully reversible: a future byte-matching C++
init() swaps in via one functions.csv source edit; the 57072 target bytes are a permanent answer key.

Regenerate: python3 reverse/whale_scriptengine/generate_asm.py
"""
import sys
sys.path.insert(0, "tools")
import build

RVA, SIZE = 0x3107f0, 57072
MANGLED = "?init@ScriptEngine@@UAEXXZ"

data = build.read_target_bytes(RVA, SIZE)
assert len(data) == SIZE, len(data)

# Minimal class: only the shape matters for the mangled name (virtual void init on ScriptEngine).
build.Path("src/game/script_engine.h").write_text(
    "#pragma once\n"
    "// ScriptEngine::init registers all script action templates. Landed as naked asm (whale):\n"
    "// C++ capped at ~44% by global regalloc across 537 blocks. See reverse/whale_scriptengine/.\n"
    "class ScriptEngine {\npublic:\n\tvirtual void init();\n};\n"
)

lines = [
    "// cl: /EHsc",
    '#include "script_engine.h"',
    "",
    "#pragma warning(disable: 4035)  // no return value: the naked body is pure asm",
    "__declspec(naked) void ScriptEngine::init()",
    "{",
]
CHUNK = 400
for start in range(0, SIZE, CHUNK):
    lines.append("\t__asm {")
    lines += [f"\t\t__emit 0x{b:02x}" for b in data[start : start + CHUNK]]
    lines.append("\t}")
lines.append("}")
build.Path("src/game/script_engine.cpp").write_text("\n".join(lines) + "\n")
print(f"wrote src/game/script_engine.{{h,cpp}} ({SIZE} __emit) for {MANGLED}")
