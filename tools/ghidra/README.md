# Ghidra inventory (optional accelerator)

The PE export table names only ~1,300 of the binary's ~78,000 functions. Ghidra recovers
the rest — exact boundaries, sizes, and the call graph — which gives accurate function sizes
for `functions.csv`, callee addresses for `symbols.csv`, and the string anchors used to map
anonymous functions to Generals source. The outputs are pinned to the baseline binary;
regenerate only if the baseline changes (it shouldn't).

## Setup (one-time)
1. Install Ghidra (https://github.com/NationalSecurityAgency/ghidra/releases) and a JDK 21.
   Note: Ghidra 12 dropped bundled Jython — these scripts are Java, run via `-scriptPath`.

## Regenerate (≈3 min)
Run from the repo root; replace `$EXE` with `baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe`:

    analyzeHeadless /tmp/bfme_ghidra bfme -import $EXE -overwrite \
        -scriptPath tools/ghidra -postScript list_functions.java $PWD/reverse/ghidra_functions.csv
    # reuse the saved project (no re-analysis) for further scripts:
    analyzeHeadless /tmp/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript list_string_xrefs.java $PWD/reverse/string_xrefs.tsv

Outputs (gitignored, derived from the binary, like `reverse/exports.csv`):
- `reverse/ghidra_functions.csv` — `rva,size,name` for every function. Consumed by `tools/harvest.py`.
- `reverse/string_xrefs.tsv` — `string<TAB>referencing function rvas`. For identification.
- `reverse/vtables.tsv` — `vtable_rva<TAB>label<TAB>slot<TAB>func_rva<TAB>func_name` for every
  recovered vtable. Read BFME's exact class vtable slot order instead of hand-triangulating.
  Generate (reuse the analyzed project, store it on disk not /tmp — tmpfs quota):
    analyzeHeadless build/toolchains/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript export_vtables.java $PWD/reverse/vtables.tsv

## Use
- **Sizes:** look up a function's exact `target_size` instead of guessing from export gaps.
- **Calls:** a call target's address (e.g. `__ftol2` at `0x9F6E38`) goes in `reverse/symbols.csv`.
- **Identification:** ~12% of `.text` is in functions referencing strings that are greppable in
  the Generals source — anchoring them to a specific source file. See `tools/harvest.py` and `../../docs/matching.md`.

## Decompile a queued candidate

`tools/next_work.py --tier ghidra` prints an RVA backed by source-string xrefs.
Decompile it, including callers/data references and direct callees, with:

    analyzeHeadless build/toolchains/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript decompile_function.java 0x82190
