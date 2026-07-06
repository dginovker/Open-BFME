# Message-name whale — 0x8b600 (7KB) = GameMessage::getCommandTypeAsAsciiString(Type t)

Generals source: Common/MessageStream.cpp:235 `#define CHECK_IF(x) if(t==x){return #x;}` + ~410 lines.
BFME: 307 MSG_ names (drifted — added MSG_*_HINT, removed ~100). MSG_META_SAVE_VIEW1=33 MATCHES Generals.

## Structure (verified)
- Mixed dispatch: **jump table @ VA 0x48d1e8** covers META range (t=0x21..0x92, `lea eax,[edi-0x21];
  cmp eax,0x71; ja default; jmp [eax*4+0x48d1e8]`), rest is if-cascade. t (the Type arg) is in edi.
- Only callees: AsciiString ctors 0x12c42 / 0x888bc0 (both MATCHED). SEH prologue.
- Returns AsciiString by value (RVO). Two AsciiString slots (commandName local + RVO return) are
  0-inited in the prologue via interleaved `mov [esp+d],ebx` (ebx=0) between register pushes.

## GO/NO-GO measured 2026-07-06
Ported Generals fn + full 411-entry enum, built: 7534B vs 7143B, **32% aligned, first divergence
at byte 25 (PROLOGUE)** — target interleaves the two-slot 0-init differently than a direct-ctor port;
plus enum drift adds ~100 extra cases. So: switch/independent-cases advantage is real, but prologue
regalloc + drift make it a dedicated run (like [[scriptengine-whale]], multi-day).

## Extraction (enum.json) — 185/307 value->name so far
- **Jump table: 114/114 META values CLEAN** (33..146, read directly from 0x48d1e8 -> case -> pushed str).
- If-cascade: 73 (NOISY — my nearest-preceding-cmp pairing caught non-enum cmps up to 2008; needs a
  proper cascade walk: match each `cmp edi,IMM; je` to its return-string block, filter IMM<~500).
## Recipe to finish (dedicated run)
1. Complete the enum extraction (walk the if-cascade properly; ~193 non-META messages).
2. Reconstruct GameMessage + exact Type enum (BFME values), generate the fn.
3. Fix the prologue: two AsciiString slots 0-init (default-construct commandName + RVO), match the
   interleaved `mov [esp+d],ebx`. Then the independent switch cases should fall out (local regalloc).

## Enum extraction COMPLETE-ish + 2nd measurement (2026-07-06)
BFME's Type enum is SECTIONED (explicit boundaries): UI/input 2-180, then a gap, then
network/game 1002-1121 (`MSG_BEGIN_*_MESSAGES = 1000`-style). TWO jump tables:
0x48d1e8 (lo=33,N=114) + 0x48d3b0 (lo=1002,N=120). Extracted **296 unique** value->name
(enum.json). Regenerated fn with the correct sectioned enum: **8328B vs 7143B, 39%** (up from
32% with the Generals enum — the correct values help). STILL not landing because: (a) a few
extraction value-errors (dup names -> some jump-table cases fall through to a shared string, so
their value is wrong -> MSVC won't regenerate the exact jump table); (b) the AsciiString
local/RVO prologue diverges; (c) generated is LARGER, so some CHECK_IFs stay if-cascade instead
of folding into the jump tables. To land: fix the ~few dup/fallthrough cases (decode each 2nd-table
case past the first push to the ACTUAL return string), match the prologue two-slot 0-init, verify
the two dense ranges fold to jump tables. Still multi-day but closer + independent-cases.

## SWITCH form + jump-table finding (2026-07-06, final for this session)
KEY: an if-cascade (`if(t==x)return`) source compiles to **0 jump tables** (pure sequential), but
the TARGET has 2. A **switch(t){case MSG_X:...}** form DOES regenerate **2 jump tables** (structurally
matching) at 8120B. BUT still only the 219B TAIL aligns (the default/return-commandName epilogue);
the jump-table bounds, case bodies (AsciiString return construction), and prologue all diverge. So
even structurally-correct + correct-enum, it's the same MSVC-codegen matching wall as the scripting
whale. The reference source is if-cascade yet the binary has jump tables -> MSVC 7.1 converted it;
reproducing that exact conversion (bounds, case layout, the RVO/EH prologue) is the multi-day fight.
BOTH whales: confirmed matchable, structure/enum/layout recovered, register-alloc + codegen is the wall.

## CONVERGENCE: 32% -> 64% (2026-07-06, generate_msgfunc.py)
Source-form tweaks each lifted the match, prologue now aligns through byte 24:
1. correct sectioned enum: 32->39%. 2. switch (not if-cascade -> gets the 2 jump tables): keeps.
3. `commandName` local present (2nd AsciiString -> correct 2-slot EH prologue): 39->47%.
4. `AsciiString commandName;` default-ctor THEN assign (not copy-init): 47->**64%**.
REMAINING divergence at byte 25: target 0-inits BOTH AsciiString slots (commandName + RVO return)
INTERLEAVED with the register pushes (`push ebx;xor ebx,ebx;push esi;mov[esp+0xc],ebx;push edi;
mov[esp+0xc],ebx`); my form emits one 0-init + constructs. The RVO-return-slot upfront 0-init +
that exact push/zero interleave is MSVC scheduling — the last (hardest) mile. This whale is CLOSE:
switch-based (independent cases), 64% with the prologue nearly matched. Best landing candidate.

## Variant sweep confirms 64% is the SOURCE-FORM CEILING (2026-07-06)
Tested prologue variants: no-MSG_COUNT-check 48%, copy-init+switch 47%, commandName-after-switch 35%
— ALL worse than the committed default-ctor+MSG_COUNT-check+switch form (64%). So 64% is the best
achievable by source structure; the remaining 36% is MSVC's exact RVO-return-slot 0-init INTERLEAVE
scheduling (byte 25 onward), which source changes can't steer (same MSVC-codegen wall as scripting's
register allocation, just reached at 64% vs 44%). NET for both whales: layouts/enums/forms fully
recovered and committed; the final mile is MSVC internal codegen matching = the dedicated multi-day run.

## THE CONCRETE C++ DEAD-END (deep iterate loop, 2026-07-06)
Ran the real explain_mismatch loop (not just form sweeps). The 64% form gives jt=2 (both jump
tables, matching target) but only **1** prologue AsciiString slot-zeroing; the TARGET has **2**
(commandName local + the RVO return slot, both 0-inited upfront for EH). Root cause is a genuine
TENSION with no C++ resolution found:
- The 2 jump tables require a CLEAN switch — returns deferred past the dispatch, so MSVC sees the
  RVO return value as live only inside the cases -> it 0-inits that slot late, not in the prologue
  (1 zeroing).
- Forcing the RVO live upfront (an early `return` before the switch) DOES add the 2nd zeroing, but
  it BREAKS the jump-table conversion (jt drops to 0). Verified: early-return-literal jt=0,
  switch+explicit-default jt=0, switch-break-to-var jt=0/zeroings=0.
So "2 jump tables" and "RVO-slot 0-inited in the prologue" are mutually exclusive across every C++
form tried. This is why 64% is a hard C++ ceiling: MSVC's exact EH/RVO schedule for THIS control
flow isn't reproducible from source while keeping the jump tables. The logic is fully & correctly
decompiled (the 64% C++ IS the right source); only the compiler's schedule differs. => this is the
canonical "asm would close it, but only by forcing schedule on already-correct logic" case.

## LANDED 2026-07-06 via naked asm (user directive: asm for whales)
C++ was proven capped at 64% (jump-table-vs-RVO-prologue tension, global regalloc). Per the user's
reframing (byte-exact drop-in is the hard proof; asm is acceptable where C++ can't reach it), the
whale is now MATCHED as `__declspec(naked)` + `__emit` of the exact 7143 bytes (`generate_asm.py`).
- Build: **Functions OK 2301/2301, no-op patch (whole-binary SHA) identical** — byte-exact, drop-in safe.
- MSVC 7.1 compiled the 7143-byte emit block fine (split into 18 `__asm` blocks of 400).
- The strings ride as literal DIR32-position bytes (a naked fn can't mint ??_C@ literals); correct
  because the emitted bytes ARE the original. Recovered understanding (enum.json, jump tables) kept.
- Fully reversible: a future C++ version that byte-matches can replace the asm via one functions.csv
  source swap; the 7143 target bytes are a permanent answer key.
