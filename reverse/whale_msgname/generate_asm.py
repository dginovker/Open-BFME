#!/usr/bin/env python3
"""Generate the naked-asm landing of the message-name whale
GameMessage::getCommandTypeAsAsciiString (0x8b600, 7143 bytes).

C++ was capped at 64% aligned by MSVC's global register allocation + the jump-table-vs-RVO-prologue
tension (see FINDINGS.md) — a genuine codegen wall. Per the user's directive (asm is acceptable where
byte-exactness requires it), we transcribe the exact instruction bytes as a __declspec(naked) function.

This is byte-verified (build.py) + whole-binary-SHA-verified (no-op patch). The strings are hard-coded
DIR32 positions inside the emit (a naked function can't mint ??_C@ literals), so they ride along as
literal bytes rather than symbolic refs — correct because the bytes ARE the original. The recovered
understanding (enum.json: 296 value->name, jump tables, block shape) is preserved separately.

Regenerate: python3 reverse/whale_msgname/generate_asm.py
"""
import sys, os
sys.path.insert(0, "tools")
import build

RVA, SIZE = 0x8b600, 7143
MANGLED = "?getCommandTypeAsAsciiString@GameMessage@@QAE?AVAsciiString@@W4Type@1@@Z"

data = build.read_target_bytes(RVA, SIZE)
assert len(data) == SIZE, len(data)

# Minimal class: only the SHAPE matters for the mangled name (nested enum Type, thiscall method
# returning AsciiString by value). Enum values are irrelevant to a naked body.
build.Path("src/game/message_stream.h").write_text(
    '#pragma once\n#include "ascii_string.h"\n'
    "class GameMessage {\npublic:\n\tenum Type { MSG_INVALID = 0 };\n"
    "\tAsciiString getCommandTypeAsAsciiString(Type t);\n};\n"
)

lines = [
    "// cl: /EHsc",
    '#include "message_stream.h"',
    "",
    "#pragma warning(disable: 4035)  // no return value: the naked body is pure asm",
    "__declspec(naked) AsciiString GameMessage::getCommandTypeAsAsciiString(GameMessage::Type t)",
    "{",
]
CHUNK = 400  # split the 7143 emits across several __asm blocks (MSVC handles it either way)
for start in range(0, SIZE, CHUNK):
    lines.append("\t__asm {")
    lines += [f"\t\t__emit 0x{b:02x}" for b in data[start : start + CHUNK]]
    lines.append("\t}")
lines.append("}")
build.Path("src/game/message_stream.cpp").write_text("\n".join(lines) + "\n")
print(f"wrote src/game/message_stream.{{h,cpp}} ({SIZE} __emit) for {MANGLED}")
