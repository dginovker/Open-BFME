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

## Reference source

BFME is the SAGE engine — its original source largely survives in C&C Generals, vendored under
`reference/CnC_Generals_Zero_Hour/` (GPLv3, same license as this repo). Many functions match it
verbatim. Use it as a guide and reconcile against the binary (the source of truth).

For exact function sizes, the full function inventory, and the bulk-port pipeline, see
`tools/ghidra/README.md`.
