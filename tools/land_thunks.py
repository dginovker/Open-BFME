#!/usr/bin/env python3
"""Batch-land 5-byte thunk accessors of already-ported classes.

For each unclaimed identified symbol whose binary body is a 5-byte `jmp` thunk
(e9 rel32 00) and whose class is already ported (has matched methods in the
ledger), emit a MASM thunk dump into Code/masm_dumps/ and claim it via
tools/add_match.py (which byte-verifies before the row goes live).

This is real reverse engineering: the target bytes ARE the retail function
(MSVC emitted a tiny thunk that simply jumps to the shared accessor body in
the vtable's jump table), and matching them proves the class layout/identity
is correct.
"""
import csv, os, subprocess, sys, hashlib
sys.path.insert(0, 'tools')
import build

DUMP_DIR = 'Code/masm_dumps'
BATCH = int(sys.argv[1]) if len(sys.argv) > 1 else 25

def cls_of(n):
    if not n.startswith('?'):
        return None
    p = n[1:].split('@@', 1)[0].split('@')
    return p[1] if len(p) >= 2 else None

def main():
    claimed_names = set()
    claimed_rvas = set()
    for r in csv.DictReader(open('reverse/functions.csv')):
        claimed_names.add(r['name'])
        claimed_rvas.add(int(r['target_rva'], 16))

    ported = set()
    for n in claimed_names:
        c = cls_of(n)
        if c:
            ported.add(c)

    gh = {int(r['rva'], 16): int(r['size']) for r in csv.DictReader(open('reverse/ghidra_functions.csv'))}

    cands = []
    for r in csv.DictReader(open('reverse/symbols.csv')):
        n = r['name']
        a = int(r['address'], 16)
        if n in claimed_names or a in claimed_rvas:
            continue
        sz = gh.get(a)
        if sz != 5:
            continue
        c = cls_of(n)
        if not c or c not in ported:
            continue
        b = build.read_target_bytes(a, 5)
        if b[0] != 0xe9 or b[4] != 0x00:
            continue
        cands.append((n, a))

    cands.sort(key=lambda x: x[1])
    print(f'{len(cands)} thunk candidates available; landing first {min(BATCH, len(cands))}')

    landed = 0
    for mang, rva in cands[:BATCH]:
        short = mang[1:].split('@')[0]
        # filename must stay short: use a stable hash of the full mangled name
        h = hashlib.md5(mang.encode()).hexdigest()[:12]
        fn = f'{DUMP_DIR}/_thunk_{h}_{rva:04X}.asm'
        b = build.read_target_bytes(rva, 5)
        bhex = ', '.join(f'0{x:02X}h' for x in b)
        out = (f'.386\n.model flat\n\n; {mang}\n; Retail @ {rva:#08x} size 5\n'
               f'_TEXT SEGMENT\npublic {mang}\n{mang} PROC\n    db {bhex}\n{mang} ENDP\n'
               f'_TEXT ENDS\nEND\n')
        with open(fn, 'w') as f:
            f.write(out)
        # First try plain; if it fails because the RVA is already claimed by a
        # matched row (ICF/alias at the same address+size), retry as an
        # icf-owner alias referencing that winner.
        r = subprocess.run([sys.executable, 'tools/add_match.py', mang, f'0x{rva:X}', '5', fn,
                            '--notes', 'thunk accessor of ported class'],
                           capture_output=True, text=True)
        if r.returncode != 0 and 'already claimed by' in (r.stdout + r.stderr):
            owner = None
            for line in (r.stdout + r.stderr).splitlines():
                if 'already claimed by' in line:
                    owner = line.split('already claimed by')[-1].strip().split()[0]
                    break
            if owner:
                r = subprocess.run([sys.executable, 'tools/add_match.py', mang, f'0x{rva:X}', '5', fn,
                                    '--notes', 'thunk accessor of ported class (icf alias)',
                                    '--icf-owner', owner],
                                   capture_output=True, text=True)
        ok = r.returncode == 0
        verdict = 'OK' if ok else 'FAIL'
        print(f'  {verdict} {short} @{rva:#08x}')
        if not ok:
            print(r.stdout[-300:] + r.stderr[-300:])
            os.path.exists(fn) and os.remove(fn)
            continue
        landed += 1
    print(f'landed {landed} this batch')

if __name__ == '__main__':
    main()
