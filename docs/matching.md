# Matching a function

1. Write the C++ in `src/`, add a row to `reverse/functions.csv`, then verify.
   - Iterate fast: `./build.sh src/your_file.cpp` (or a function name) compiles+byte-compares
     just that source in a few seconds.
   - Before committing: `./build.sh` (no args) runs the full check — every function, plus the
     baseline hash and the no-op patch that confirms the rebuilt exe is identical.
   It compiles with MSVC 7.1 and fails loudly on any mismatch.

2. Relocations the patcher fills in for you (so don't worry about matching these bytes):
   - **DIR32** (constants, vtables, string literals): copied from the target binary. The
     address your source produces is irrelevant — only the surrounding instruction bytes matter.
   - **REL32** (calls/jumps): resolved to the callee's address. A matched callee resolves
     automatically; for anything else (CRT helpers like `__ftol2`, not-yet-matched functions)
     add `name,address` to `reverse/symbols.csv`. The build prints the unresolved name on
     failure. Find the address by disassembling the target and computing the call destination,
     or look it up in the Ghidra inventory (`tools/ghidra/`).

Leaf functions (no calls) are easiest; `reverse/symbols.csv` is what makes call-using functions matchable.

## MSVC 7.1 shaping notes

Near-matches are still failures. If a candidate differs only by register choice, branch layout, or
x87 operand order, revert it unless the exact decorated-symbol check passes.

Observed traps:

- `register` did not force MSVC 7.1 to preload constants. In `Matrix4D::Set(const Coord3D&)`,
  C++ kept `0x3f800000` near first use instead of matching the target's early `mov edx, 0x3f800000`.
- Equivalent x87 expressions can compile differently. `Coord3D::CrossProduct` commuted
  multiplication operands, changing `fld`/`fmul` order while preserving behavior.
- Ternary min/max forms can switch between integer bit copies and x87 stores. `RealRange::combine`
  needs both the target condition flags and the target raw float-copy shape.
- Pointer/index loops are unstable. `Matrix4D::IsExactlyEqualTo` compiled to a different loop shape
  from the target's four-dword xor/or block.
- Virtual-call wrappers may match semantically while saving registers or branching differently.
  `Xfer::XferRawBytes` was a near-match but not byte-identical.

Use these as negative patterns: once a diff shows one of these traps, prefer another function family
or first find a source pattern that proves the exact instruction shape in a targeted build.

One positive pattern: MSVC 7.1 groups overloaded virtual operators at the first overload slot and
emits them in reverse declaration order. The `Debug` shim intentionally declares stream overloads
so `float`, `unsigned int`, `int`, and `const char *` land at the target vtable slots `0x20`,
`0x30`, `0x34`, and `0x38`.

## Reference source

BFME is the SAGE engine — its original source largely survives in C&C Generals, vendored under
`reference/CnC_Generals_Zero_Hour/` (GPLv3, same license as this repo). Many functions match it
verbatim. Use it as a guide and reconcile against the binary (the source of truth).

For exact function sizes, the full function inventory, and the bulk-port pipeline, see
`tools/ghidra/README.md`.
