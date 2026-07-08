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
| BFME network wrapper constructor | RVA `0x0065AC30`, ILT `0x00029C12` | byte-matched as `BFMENetwork::construct`; installs vtable VA `0x01119C8C` and initializes wrapper queues/list | matched |
| BFME network wrapper vtable | VA `0x01119C8C` / RVA `0x00D19C8C` | referenced by constructor | recovered |
| backend constructor | RVA `0x006547F0`, ILT `0x00040E44` | byte-matched as `BFMENetworkBackend::construct`; stores owner pointer at backend `+0x68` and initializes list at `+0x5C` | matched |
| backend vtable | VA `0x0111988C` / RVA `0x00D1988C` | installed by backend constructor | recovered |
| backend deleting destructor | RVA `0x00654890` | byte-matched as `BFMENetworkBackend::destroyAndMaybeDelete`; backend vtable slot `+0x00` | matched |
| backend live-handle opener | RVA `0x009DB650` | byte-matched as `BFMENetworkBackend::openLiveHandle`; backend vtable slot `+0x04`, starts thread and stores handle at `+0x48` | matched |
| backend thread start | RVA `0x009DB630` | byte-matched as `BFMENetworkBackendThreadStart`; calls global slot `+0x58`, then backend vtable slot `+0x08` | matched |
| backend event callback | RVA `0x006549C0`, ILT `0x000276B0` | byte-matched as `BFMENetworkBackendEventCallback`; dispatcher calls it through the ILT in multiple cases, callback returns with `ret 0x28` | matched |
| wrapper deleting destructor | RVA `0x0065ADB0` | byte-matched as `BFMENetwork::destroyAndMaybeDelete`; wrapper vtable slot `+0x00` | matched |
| wrapper init | RVA `0x006548C0` | byte-matched as `BFMENetwork::init`; creates backend at wrapper `+0x64` and calls backend vtable slot `+0x04` | matched |
| backend handle check | RVA `0x009DB590` | byte-matched as `BFMENetworkBackend::hasLiveHandle`; reads backend `+0x48` | matched |
| backend handle clear | RVA `0x009DB5A0` | byte-matched as `BFMENetworkBackend::closeLiveHandle`; waits on/clears backend `+0x48` and `+0x44` | matched |
| lock-ref release | RVA `0x009DB400` | byte-matched as `BFMEAutoLockRef::~BFMEAutoLockRef`; releases lock handle at `+0x00` when `+0x04` is false | matched |
| wrapper queue 0 push | RVA `0x0065E050` | byte-matched as `BFMENetwork::pushQueue0`; locks wrapper `+0x04`, appends to queue at `+0x14` | matched |
| wrapper queue 0 pop | RVA `0x0065ADE0` | byte-matched as `BFMENetwork::popQueue0`; locks wrapper `+0x04`, pops queue at `+0x14` into caller output | matched |
| wrapper queue 1 push | RVA `0x0065E120` | byte-matched as `BFMENetwork::pushQueue1`; locks wrapper `+0x0C`, appends to queue at `+0x3C` | matched |
| wrapper queue 1 pop | RVA `0x00658E20` | byte-matched as `BFMENetwork::popQueue1`; locks wrapper `+0x0C`, pops queue at `+0x3C` into caller output | matched |
| wrapper payload-list push | RVA `0x0065E340` | byte-matched as `BFMENetwork::pushList90`; dispatcher calls wrapper slot `+0x20` after building a payload, appending to list at `+0x90` | matched |
| wrapper payload-list find/create | RVA `0x0065AEB0` | byte-matched as `BFMENetwork::findList90`; wrapper slot `+0x24` searches or materializes an entry in list at `+0x90` | matched |
| wrapper state-copy helpers | RVAs `0x00655060`, `0x00655090`, `0x006550C0` | byte-matched as `BFMENetwork::copyState6C`, `copyState78`, `copyState84`; callback uses these to copy wrapper fields `+0x6C`, `+0x78`, `+0x84` | matched |
| backend event dispatcher | RVA `0x0065CA50` | backend vtable slot `+0x08`; switch/jump table at VA `0x00A5D6FC` | boundary suspect |
| registered callback | RVA `0x0065C260` | pushed as callback VA `0x00A5C260` by dispatcher before call to `0x009D5330` | Ghidra start missing |

Known wrapper slots from vtable VA `0x01119C8C`:

| Slot | Body RVA | Current role |
| --- | --- | --- |
| `+0x00` | `0x0065ADB0` | matched as `BFMENetwork::destroyAndMaybeDelete`; scalar deleting destructor wrapper |
| `+0x04` | `0x006548C0` | matched as `BFMENetwork::init`; allocates backend object and calls backend slot `+0x04` |
| `+0x08` | `0x00652AB0` | matched as `BFMENetwork::destroyBackend`; releases lock-ref `+0xA4`, backend handle, then backend `+0x64` |
| `+0x0C` | `0x00651780` | matched as `BFMENetwork::backendHasLiveHandle`; proxies backend pointer at wrapper `+0x64` |
| `+0x10` | `0x0065E050` | matched as `BFMENetwork::pushQueue0`; pushes queue at wrapper `+0x14` |
| `+0x14` | `0x0065ADE0` | matched as `BFMENetwork::popQueue0`; pops queue at wrapper `+0x14`, returns bool |
| `+0x18` | `0x0065E120` | matched as `BFMENetwork::pushQueue1`; pushes queue at wrapper `+0x3C` |
| `+0x1C` | `0x00658E20` | matched as `BFMENetwork::popQueue1`; pops queue at wrapper `+0x3C`, returns bool |
| `+0x20` | `0x0065E340` | matched as `BFMENetwork::pushList90`; appends payload list at wrapper `+0x90` |
| `+0x24` | `0x0065AEB0` | matched as `BFMENetwork::findList90`; searches or creates payload list entry at wrapper `+0x90` |

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

- `src/zh/connectionmanager.cpp`, `src/zh/network.cpp`,
  `src/zh/netcommandmsg.cpp`, and `src/zh/messagestream.cpp` are now trimmed to
  byte-matched surfaces only; the previous unclaimed ZH bodies were removed
  rather than treated as progress.
- `src/game/native_network.cpp` contains the first byte-matched BFME-native
  wrapper/backend code:
  - `BFMENetworkBackend::construct` at `0x006547F0` (constructor body).
  - `BFMENetworkBackend::destroyAndMaybeDelete` at `0x00654890`.
  - `BFMENetworkBackend::openLiveHandle` at `0x009DB650`.
  - `BFMENetworkBackendThreadStart` at `0x009DB630`.
  - `BFMENetworkBackendEventCallback` at `0x006549C0`.
  - `BFMENetwork::construct` at `0x0065AC30` (constructor body).
  - `BFMENetwork::destroyAndMaybeDelete` at `0x0065ADB0`.
  - `BFMENetwork::init` at `0x006548C0`.
  - `BFMENetwork::backendHasLiveHandle` at `0x00651780`.
  - `BFMENetwork::destroyBackend` at `0x00652AB0`.
  - `BFMENetwork::pushQueue0` at `0x0065E050`.
  - `BFMENetworkBackend::hasLiveHandle` at `0x009DB590`.
  - `BFMENetworkBackend::closeLiveHandle` at `0x009DB5A0`.
  - `BFMEAutoLockRef::~BFMEAutoLockRef` at `0x009DB400`.
  - `BFMENetwork::popQueue0` at `0x0065ADE0`.
  - `BFMENetwork::pushQueue1` at `0x0065E120`.
  - `BFMENetwork::popQueue1` at `0x00658E20`.
  - `BFMENetwork::pushList90` at `0x0065E340`.
  - `BFMENetwork::findList90` at `0x0065AEB0`.
  - `BFMENetwork::copyState6C`, `copyState78`, and `copyState84` at
    `0x00655060`, `0x00655090`, and `0x006550C0`.
- The current matched network rows are:
  - `ConnectionManager::processProgress` at `0x00662D20`.
  - `NetworkInterface::createNetwork` at `0x0065C1F0`.
  - `Network::isPacketRouter` at `0x00681B20`.
  - Three STL helper/template rows emitted from `connectionmanager.cpp`.
- The old ZH delay functions are not proven BFME code. Treat ZH as an intent map
  and the BFME-native rows above as the patchable evidence.

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
