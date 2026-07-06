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
