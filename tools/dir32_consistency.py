#!/usr/bin/env python3
# INVESTIGATION 2026-07-06: the 11 flagged candidates are all LEGITIMATE patterns, not bugs:
#   - CRC32_Table, _COLLISION_EPSILON: their translation units are LINKED TWICE in lotrbfme.exe
#     (see realcrc.cpp comment) -> two byte-identical copies at two addresses. Expected.
#   - 8 FX module ??_7Class ctor-vs-dtor: same vtable symbol resolves to DIFFERENT addresses with
#     DIFFERENT content in ctor (0x1110920, real fn-ptr vtable) vs dtor (0x1073744). This is NOT
#     double-linking (contents differ) and NOT a normal construction vtable (those have a different
#     ??_8/??_R symbol). UNEXPLAINED — a genuine candidate byte-fidelity gap the masking hides: the
#     empty `~Class(){}` source compiles a reference to the class's regular vtable, but the binary
#     dtor sets a different vtable. CONFIRMED (2026-07-06): ctor and dtor carry the BYTE-IDENTICAL
#     symbol ??_7DefaultDrawModuleInfo@FXParticleSystem@@6B@, yet it resolves to 0x1110920 (ctor) vs
#     0x1073744 (dtor) — two different-content vtables for one symbol, which a normal single link
#     can't produce. NOT double-linking (contents differ). This is a BFME-build-specific anomaly.
#     IMPORTANT: it does NOT affect the current PATCH-BASED drop-in (compile_function masks the DIR32
#     with the original correct bytes, so the no-op whole-binary SHA still passes and the produced
#     binary is byte-identical). It is a LATENT source-fidelity gap: a hypothetical 100%-from-source
#     rebuild would resolve both refs to one address and diverge here. Needs deep vtable/linker
#     analysis to reproduce; not fixable by a literal edit like the two strings were.
# NET: 2 confirmed real string bugs fixed; CRC/COLLISION confirmed legitimate (double-link); the 8 FX
# vtable diffs are OPEN — real candidate defects to resolve before this can be a clean build gate.
"""Consistency verifier for the NON-string DIR32 relocations that build.py masks (globals, vtables,
function-address references). Strings are handled by verify_string_refs (content self-verification);
these have no content signature, but they DO have a consistency signature: a given symbol has exactly
ONE address, so every reference to it must resolve to the same base once the relocation ADDEND is
subtracted (base = binary_final_address - compiled_addend). A symbol resolving to >1 base is a
candidate hidden discrepancy (the same class of masked bug as the %S/FXParticleSystemInfo string bugs).

Self-bootstrapping (no pins). Reports candidates for review; a clean gate would whitelist the
known-legitimate patterns below. Run: python3 tools/dir32_consistency.py
"""
import sys, struct, csv, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__)))
import build, harvest
from collections import defaultdict

def main():
    sym2base = defaultdict(lambda: defaultdict(list))
    rows = [r for r in csv.DictReader(open(build.ROOT/"reverse"/"functions.csv")) if r["status"]=="matched"]
    bysrc = defaultdict(list)
    for r in rows: bysrc[r["source"]].append(r)
    for src, frows in bysrc.items():
        if not (build.ROOT/src).exists(): continue
        try: obj = harvest.compile_obj(build.Path(src), [])
        except SystemExit: continue
        for r in frows:
            trva, tsz = int(r["target_rva"],16), int(r["target_size"])
            target = build.read_target_bytes(trva, tsz)
            try: body, relocs = build.read_object_symbol_bytes(obj, r["name"])
            except ValueError: continue
            for off, rt, sym in relocs:
                if rt != 0x0006 or off+4 > tsz or off+4 > len(body) or sym.startswith("??_C@"):
                    continue
                final = struct.unpack_from("<I", target, off)[0]
                addend = struct.unpack_from("<I", body, off)[0]
                sym2base[sym][(final - addend) & 0xFFFFFFFF].append(r["name"])
    inc = [(s,d) for s,d in sym2base.items() if len(d) > 1]
    print(f"non-string DIR32 symbols: {len(sym2base)} | consistent: {len(sym2base)-len(inc)} | INCONSISTENT: {len(inc)}")
    for s, d in sorted(inc):
        print(f"  {s} -> {len(d)} bases: {[hex(b) for b in d]}")
        for b, fns in d.items():
            print(f"      0x{b:x} <- {fns[0]}" + (f" +{len(fns)-1}" if len(fns)>1 else ""))
    return len(inc)

if __name__ == "__main__":
    raise SystemExit(1 if main() else 0)
