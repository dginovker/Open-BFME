#!/usr/bin/env python3
"""Build a direct-call graph from the binary (e8 call scan over every ghidra function).
Emits /tmp/callgraph.json and prints the highest in-degree functions. High in-degree =
the fundamental shared functions (operator new/delete, malloc/free, string ops). Used to
IDENTIFY un-anchored cluster functions by structural role when locate/anchor/size find
nothing: e.g. operator delete was the #1 in-degree fn (7479 callers) at 0x881eb0, which
let us reconstruct+match it. Follows one ILT jmp thunk. Direct (e8) calls only.
"""
import sys, csv, struct
sys.path.insert(0,'tools'); import build
exe=build.EXE.read_bytes(); pe=build.pe_sections(exe)
def rvoff(rva):
    try: return build.rva_to_file_offset(pe,rva)
    except: return None
funcs=[(int(r['rva'],16),int(r['size'])) for r in csv.DictReader(open('reverse/ghidra_functions.csv'))]
starts={a for a,s in funcs}
# ILT map: address -> jmp target (thunk resolution)
from collections import defaultdict
indeg=defaultdict(int); callers=defaultdict(list)
n=0
for rva,size in funcs:
    off=rvoff(rva)
    if off is None: continue
    buf=exe[off:off+size]; i=0
    while i < len(buf)-4:
        if buf[i]==0xe8:
            dest=rva+i+5+struct.unpack_from('<i',buf,i+1)[0]
            if 0x1000<=dest<0xd00000:
                # follow one ILT jmp
                do=rvoff(dest)
                if do is not None and exe[do]==0xe9:
                    dest=dest+5+struct.unpack_from('<i',exe,do+1)[0]
                indeg[dest]+=1; 
                if len(callers[dest])<300: callers[dest].append(rva)
            i+=5
        else: i+=1
    n+=1
# save
import json
json.dump({'indeg':{hex(k):v for k,v in indeg.items()}}, open('/tmp/callgraph.json','w'))
print(f"call graph: {n} functions scanned, {len(indeg)} distinct call targets")
# top in-degree functions (candidates for malloc/pool/common utils)
sizemap={a:s for a,s in funcs}
top=sorted(indeg.items(), key=lambda x:-x[1])[:25]
print("Top in-degree functions (address, callers, size):")
for a,d in top:
    print(f"  0x{a:06x}  called_by={d:5}  size={sizemap.get(a,'?')}")
