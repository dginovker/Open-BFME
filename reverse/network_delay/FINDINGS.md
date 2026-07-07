# Multiplayer delay reconstruction

Goal: recover the original BFME 1 multiplayer command-delay path, byte-verify it,
and document the exact BFME addresses needed for any future opt-in patch. This
track does not change gameplay behavior.

## Current hypothesis

Zero Hour schedules synchronized network commands for a future logic frame:

- `Network::GetCommandsFromCommandList` forwards local network `GameMessage`s.
- `Network::getExecutionFrame` returns `TheGameLogic->getFrame() + m_runAhead`.
- `ConnectionManager::sendLocalGameMessage` stores that future frame on the
  generated `NetGameCommandMsg`.
- `ConnectionManager::allCommandsReady` gates logic-frame advancement until
  every player has command data for the current frame.
- `ConnectionManager::updateRunAhead` computes and broadcasts later run-ahead
  values from latency/FPS metrics.
- `Network::processRunAheadCommand` applies those values and adjusts packet
  frame grouping.

BFME may drift from ZH, so ZH is only the search map. The BFME binary remains the
source of truth.

## ZH delay map

| Area | Function | BFME RVA | Status |
| --- | --- | --- | --- |
| constants | `MAX_FRAMES_AHEAD`, `MIN_RUNAHEAD`, `FRAME_DATA_LENGTH`, `FRAMES_TO_KEEP` | TBD | not recovered |
| scheduling | `Network::getExecutionFrame` | TBD | not recovered |
| setup | `Network::init` | TBD | not recovered |
| local commands | `ConnectionManager::sendLocalGameMessage` | TBD | not recovered |
| command relay | `ConnectionManager::sendLocalCommand` | TBD | not recovered |
| readiness gate | `ConnectionManager::allCommandsReady` | TBD | not recovered |
| dynamic delay | `ConnectionManager::updateRunAhead` | TBD | not recovered |
| apply delay | `Network::processRunAheadCommand` | TBD | not recovered |
| frame pacing | `Network::timeForNewFrame` | TBD | not recovered |

These names are useful search targets, but the current evidence says the BFME
runtime path is not the ZH `Network`/`ConnectionManager` path verbatim:

- `ConnectionManager::sendLocalCommandDirect`,
  `ConnectionManager::setFrameGrouping`,
  `ConnectionManager::sendLocalCommand`,
  `ConnectionManager::sendLocalGameMessage`,
  `ConnectionManager::allCommandsReady`,
  `Network::processRunAheadCommand`,
  `Network::timeForNewFrame`,
  `Network::GetCommandsFromCommandList`, and `Network::update` classify as
  absent from the ZH sweep.
- `Network::init` and `ConnectionManager::updateRunAhead` classify as weak
  structural matches only. They are not byte-level anchors.
- `Network::getExecutionFrame` has no useful anchor, and
  `GameLogic::getFrame` is an inline load (`mov eax, [ecx+0x3c]; ret`) in the
  current build, so it does not pin the retail path by itself.

If the delay code is not in ZH, that is still actionable: use ZH for intent and
recover BFME's native wrapper/backend path directly from the retail binary.

## BFME-native path

The BFME binary routes the proven multiplayer entry point through a smaller
network wrapper/backend pair. These addresses are current reverse-engineering
anchors, not behavior changes.

| Item | Address | Evidence | Status |
| --- | --- | --- | --- |
| `TheNetwork` global | VA `0x012F76F0` / RVA `0x00EF76F0` | caller at `0x006377D0` stores the `createNetwork` return value, then calls vtable slot `+0x04` | recovered |
| `NetworkInterface::createNetwork` | RVA `0x0065C1F0`, ILT `0x000362C3` | byte-matched row; allocates `0xA8` bytes | matched |
| BFME network wrapper constructor | RVA `0x0065AC30`, ILT `0x00029C12` | called by `createNetwork`; installs vtable VA `0x01119C8C` | recovered |
| BFME network wrapper vtable | VA `0x01119C8C` / RVA `0x00D19C8C` | referenced by constructor | recovered |
| backend constructor | RVA `0x006547F0`, ILT `0x00040E44` | allocated by wrapper init; stores owner pointer at backend `+0x68` | recovered |
| backend vtable | VA `0x0111988C` / RVA `0x00D1988C` | installed by backend constructor | recovered |
| backend event dispatcher | RVA `0x0065CA50` | backend vtable slot `+0x08`; switch/jump table at VA `0x00A5D6FC` | boundary suspect |
| registered callback | RVA `0x0065C260` | pushed as callback VA `0x00A5C260` by dispatcher before call to `0x009D5330` | Ghidra start missing |

Known wrapper slots from vtable VA `0x01119C8C`:

| Slot | Body RVA | Current role |
| --- | --- | --- |
| `+0x00` | `0x0065ADB0` | deleting destructor-ish |
| `+0x04` | `0x006548C0` | init; allocates backend object and calls backend slot `+0x04` |
| `+0x08` | `0x00652AB0` | shutdown/reset-ish |
| `+0x0C` | `0x00651780` | proxies backend pointer at wrapper `+0x64` |
| `+0x10` | `0x0065E050` | queue/list operation on wrapper `+0x14` |
| `+0x14` | `0x0065ADE0` | queue/list operation on wrapper `+0x14`, returns bool |
| `+0x18` | `0x0065E120` | queue/list operation on wrapper `+0x3C` |
| `+0x1C` | `0x00658E20` | queue/list operation on wrapper `+0x3C`, returns bool |
| `+0x20` | `0x0065E340` | list transfer-ish operation using wrapper `+0x90` |
| `+0x24` | `0x0065AEB0` | list operation using wrapper `+0x90` |

The wrapper constructor initializes locks at `+0x04`, `+0x0C`, and `+0x9C`;
queue/list structures at `+0x14` and `+0x3C`; object/array regions at `+0x6C`,
`+0x78`, and `+0x84`; backend pointer at `+0x64`; and a current/session-ish
field at `+0x68`.

The dispatcher at `0x0065CA50` should be treated as one of the next primary
targets. It references packet/event cases `0..0x0B`, calls wrapper slot `+0x14`,
reads and writes `TheNetwork+0x68`, and jumps through table VA `0x00A5D6FC`.
Ghidra currently reports a short function boundary even though control flow
continues to `0x0065D69E`, so its boundary is suspect. The callback at
`0x0065C260` also needs a manual function start; it calls wrapper slots `+0x18`
and `+0x10` and reads `TheNetwork+0x68`.

## Landed evidence

- `src/zh/connectionmanager.cpp` is present from ZH and byte-verifies 5 emitted
  functions. `land_zh.py` marked 88 drifted definitions `present-unmatched`.
- `src/zh/network.cpp` is present from ZH and byte-verifies 2 emitted functions.
  `land_zh.py` marked 55 drifted definitions `present-unmatched`.
- The current matched network rows are:
  - `ConnectionManager::processProgress` at `0x00662D20`.
  - `NetworkInterface::createNetwork` at `0x0065C1F0`.
  - `Network::isPacketRouter` at `0x00681B20`.
  - Three STL helper/template rows emitted from `connectionmanager.cpp`.
- The core delay functions in the table above are now source-visible in `src/zh/`,
  but still not byte-matched. Treat their bodies as a map for manual BFME
  reconciliation, not as proven BFME code.

## Work plan

1. DONE: unblock targeted ZH sweeps for the GameNetwork files with minimal
   compile shims.
2. DONE: land the first byte-verified `ConnectionManager` and `Network` rows.
3. DONE: prove that the needed path is BFME-native enough that ZH is a search
   map, not the source of truth.
4. NEXT: recover the native dispatcher/callback boundaries and name the wrapper
   slots/fields before attempting any patch design.
5. NEXT: trace the dispatcher cases that schedule, hold, or advance synchronized
   command frames and only then decide whether a delay constant or runtime field
   exists.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.
