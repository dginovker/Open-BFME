import sys, struct, json, re
sys.path.insert(0,'tools'); import build
exe=build.EXE.read_bytes(); pe=build.pe_sections(exe); IMG=0x400000
def rvoff(rva): return build.rva_to_file_offset(pe,rva)
def rs(va):
    try:
        o=rvoff(va-IMG); e=exe.find(b'\x00',o)
        if 0<=e-o<120: return exe[o:e].decode('ascii','replace')
    except: pass
    return None
RVA,SZ=0x3107f0,57072; o=rvoff(RVA); buf=exe[o:o+SZ]
R={0:'eax',1:'ecx',2:'edx',3:'ebx',4:'esp',5:'ebp',6:'esi',7:'edi'}
i=0; ins=[]
while i<len(buf):
    b=buf[i]
    if b==0x68 and i+5<=len(buf): va=struct.unpack_from('<I',buf,i+1)[0]; ins.append(('push',va,rs(va))); i+=5
    elif b in(0xb8,0xb9,0xba,0xbb,0xbd,0xbe,0xbf): ins.append(('movri',R[b-0xb8],struct.unpack_from('<I',buf,i+1)[0])); i+=5
    elif b==0x8d:
        m=buf[i+1]; reg=R[(m>>3)&7]; rm=R[m&7]; mod=m>>6
        if mod==1: ins.append(('lea',reg,rm,buf[i+2]-(256 if buf[i+2]>127 else 0))); i+=3
        elif mod==2: ins.append(('lea',reg,rm,struct.unpack_from('<i',buf,i+2)[0])); i+=6
        else: i+=2
    elif b==0x89:
        m=buf[i+1]; reg=R[(m>>3)&7]; rm=R[m&7]; mod=m>>6
        if mod==1: ins.append(('mr',rm,buf[i+2]-(256 if buf[i+2]>127 else 0),reg)); i+=3
        elif mod==2: ins.append(('mr',rm,struct.unpack_from('<i',buf,i+2)[0],reg)); i+=6
        elif mod==0: ins.append(('mr',rm,0,reg)); i+=2
        else: i+=2
    elif b==0xc7:
        m=buf[i+1]; rm=R[m&7]; mod=m>>6
        if mod==1: ins.append(('mi',rm,buf[i+2]-(256 if buf[i+2]>127 else 0),struct.unpack_from('<I',buf,i+3)[0])); i+=7
        elif mod==2: ins.append(('mi',rm,struct.unpack_from('<i',buf,i+2)[0],struct.unpack_from('<I',buf,i+6)[0])); i+=10
        else: i+=2
    elif b==0xe8: ins.append(('call',RVA+i+5+struct.unpack_from('<i',buf,i+1)[0])); i+=5
    elif b==0x8b:
        m=buf[i+1]; mod=m>>6
        if mod==3: ins.append(('rr',R[(m>>3)&7],R[m&7])); i+=2
        else: i+= (2 if mod==0 else 3 if mod==1 else 6)
    else: i+=1
# state machine. MSVC addresses fields two ways: absolute `[esi+ABSOFF]` (dominant, 2508x) and
# via a cached base reg `lea edi,[esi+baseoff]; [edi+fieldoff]`. Resolve BOTH to an absolute
# offset; the noise (stale cached bases bleeding phantom high-index uiStrings/params) is removed
# structurally AFTER, by clamping each template's arrays to its own numUiStrings/numParameters.
regval={}; pend_push=None; pend_ecx=None; fields=[]
def resolve(reg,off):
    if reg=='esi': return off                       # absolute from this
    v=regval.get(reg)
    if v and v[0]=='base': return v[1]+off           # cached base = &array[E]
    return None
for it in ins:
    t=it[0]
    if t=='lea' and it[2]=='esi': regval[it[1]]=('base',it[3])
    elif t=='rr': regval[it[1]]=regval.get(it[2])
    elif t=='movri': regval[it[1]]=('imm',it[2])
    if t=='push' and it[2] is not None: pend_push=it[2]
    elif t=='lea' and it[1]=='ecx': pend_ecx=resolve(it[2],it[3])
    elif t=='rr' and it[1]=='ecx': pend_ecx=(regval[it[2]][1] if regval.get(it[2]) and regval[it[2]][0]=='base' else None)
    elif t=='call':
        if pend_push is not None and pend_ecx is not None: fields.append((pend_ecx,'str',pend_push))
        pend_push=None; pend_ecx=None
    elif t=='mi':
        a=resolve(it[1],it[2])
        if a is not None: fields.append((a,'imm',it[3]))
    elif t=='mr':
        a=resolve(it[1],it[2])
        if a is not None:
            v=regval.get(it[3]); fields.append((a,'imm',v[1]) if v and v[0]=='imm' else (a,'reg',it[3]))
ARR=0x1c; TSZ=0x7c
tmpl={}; order=[]; seen=set()
for a,k,v in fields:
    if a<ARR: continue
    E=(a-ARR)//TSZ
    if E not in seen: seen.add(E); order.append(E)
    tmpl.setdefault(E,{})[a-(ARR+E*TSZ)]=(k,v)
# real templates = those with an internalName (offset 0x08) that's an identifier
real=[E for E in order if 0x08 in tmpl[E] and tmpl[E][0x08][0]=='str']
print(f"{len(ins)} instrs, {len(fields)} fields, {len(order)} indices, {len(real)} REAL templates (have internalName)")
# Build CLEAN per-template records. Layout (struct-offset): uiName@0, uiName2@4, internalName@8,
# internalNameKey@0xC, numUiStrings@0x10, uiStrings[i]@0x14+4i, numParameters@0x44, params[i]@0x48+4i.
# Clamp arrays to the template's own counts -> drops stale-base phantom high-index writes.
def geti(d,off,default=None):
    return d[off][1] if off in d and d[off][0]=='imm' else default
def gets(d,off):
    return d[off][1] if off in d and d[off][0]=='str' else None
wl=[]
for E in real:
    d=tmpl[E]
    nP=geti(d,0x44,0); nU=geti(d,0x10,0)
    rec={'i':E,'internalName':gets(d,0x08),'uiName':gets(d,0x00),
         'uiName2':gets(d,0x04),
         'numParameters':nP,'parameters':[geti(d,0x48+4*k,0) for k in range(nP or 0)],
         'numUiStrings':nU,'uiStrings':[gets(d,0x14+4*k) for k in range(nU or 0)]}
    wl.append(rec)
json.dump(wl,open('reverse/scriptengine_actions_worklist.json','w'),indent=0)
print("sample template 0:",{k:v for k,v in wl[0].items() if k!='i'})
print("enum indices (first 12):",[t['i'] for t in wl[:12]])
# sanity: how many have clean (non-None) required fields + no None in clamped arrays
clean=sum(1 for r in wl if r['internalName'] and r['uiName'] is not None and None not in r['uiStrings'] and None not in r['parameters'])
print(f"{clean}/{len(wl)} templates fully clean (internalName+uiName+all clamped strings present)")
