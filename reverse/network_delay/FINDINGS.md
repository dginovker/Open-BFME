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

BFME does not keep this command-message path verbatim. ZH remains useful as an
intent map, but the BFME binary is the source of truth.

## ZH delay map

| Area | Function | BFME RVA | Status |
| --- | --- | --- | --- |
| constants | `MAX_FRAMES_AHEAD`, `MIN_RUNAHEAD`, `FRAME_DATA_LENGTH`, `FRAMES_TO_KEEP` | TBD | not recovered |
| scheduling | `Network::getExecutionFrame` | TBD | not recovered |
| setup | `Network::init` | TBD | not recovered |
| local commands | `ConnectionManager::sendLocalGameMessage` | TBD | not recovered |
| command relay | `ConnectionManager::sendLocalCommand` | TBD | not recovered |
| readiness gate | `ConnectionManager::allCommandsReady` | TBD | not recovered |
| dynamic delay | `ConnectionManager::updateRunAhead` | TBD | not recovered; ZH command path disproven for BFME |
| apply delay | `Network::processRunAheadCommand` | TBD | not recovered; BFME has no run-ahead command type |
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

## BFME command-type correction

The old ZH run-ahead command trail is now ruled out for BFME retail. The BFME
command-type string mapper at `0x00683020` names the relevant values as:

| Value | BFME name |
| --- | --- |
| `3` | `NETCOMMANDTYPE_FRAMEINFO` |
| `4` | `NETCOMMANDTYPE_GAMECOMMAND` |
| `5` | `NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY` |
| `6` | `NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY` |
| `7` | `NETCOMMANDTYPE_REQUESTPLAYERLEAVE` |
| `8` | `NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME` |
| `9` | `NETCOMMANDTYPE_REQUESTFRAMEDATA` |
| `10` | `NETCOMMANDTYPE_PLAYERLEAVE` |
| `11` | `NETCOMMANDTYPE_DESTROYPLAYER` |

This differs from Zero Hour, where values `6` and `7` are run-ahead metrics and
run-ahead. In BFME:

- `0x006741F0` is byte-matched as the command type `7` constructor and initializes
  a single dword payload at `+0x1C`; it is now named
  `BFMENetRequestPlayerLeaveCommandMsg::construct`.
- `0x00674240` and `0x00674250` are byte-matched as the payload setter/getter.
- `0x00677530` writes the type `7` wire payload as a four-byte `D` field after
  `T/R/P/C`; there is no ZH-style frame-rate byte.
- `0x00675BE0` constructs command type `6`, whose callers populate two
  `AsciiString`-like fields. It is GameSpy stats auth-key traffic, not
  run-ahead metrics.

So a future delay fix should not patch BFME command types `6` or `7` as if they
were ZH `NetRunAhead*` classes.

The incoming command dispatcher at `0x0066A3F0` uses the command type at message
offset `+0x14` and a jump table at `0x0066A634`. For the frame-delay path:

| Value | Dispatcher evidence |
| --- | --- |
| `3` | inline frame-info-ish state update for per-player latest frame fields at `+0x12060`/`+0x120A0` |
| `8` | calls `0x00664430`, the next frame-info/request helper to recover |
| `9` | calls matched `BFMEConnectionManager::processRequestFrameDataCommand` at `0x006659B0` |

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
| backend event dispatcher | RVA `0x0065CA50` | byte-matched as `BFMENetworkBackend::dispatchEvents`; backend vtable slot `+0x08`; body ends at `0x0065D6F2` before EH catch thunk and switch table | matched |
| dispatcher catch thunk | RVA `0x0065D6F3` | byte-matched as `BFMENetworkBackendDispatchCatch`; returns cleanup resume VA `0x00A5CAEB` | matched |
| registered callback | RVA `0x0065C260` | byte-matched as `BFMENetworkRegisteredCallback`; dispatcher pushes callback VA `0x00A5C260` before call to `0x009D5330`; callback calls wrapper slots `+0x18` and `+0x10` | matched |

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

The dispatcher at `0x0065CA50` is now bounded and byte-matched. Its switch table
starts at `0x0065D6FC`; that table is data and is intentionally not part of the
function row. Cases `4`, `8`, and `9` share the cleanup block at `0x0065D69E`;
case `10` calls helper `0x0062F7F2`; case `0` registers callback VA
`0x00A5C260`; and case `1` reads `LoTRB4MEOnline\MiscPref%d.ini` keys `"0"`
through `"5"` with default value `10`. Treat those key/default reads as GameSpy
misc-preference evidence until another caller proves they feed gameplay delay.

## BFME timing fields

The first native timing slice is now byte-matched:

| Function | RVA | Timing evidence |
| --- | --- | --- |
| `BFMEConnectionManager::isPlayerConnected` | `0x00662A50` | uses `timeGetTime`; compares elapsed time against `TheGlobalData + 0xCBC` (`NetworkPlayerTimeoutTime`); before frame threshold `0x010EAD50`, uses `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::isPlayerConnectedForTimeout` | `0x00662B00` | same connection timestamp at peer object `+0x34C`; normally uses caller timeout, but startup path still falls back to `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::hasPacketRouterFrameStall` | `0x00664260` | only runs when local player is packet router; after frame `5`, uses `TheGlobalData + 0xCB4` (`NetworkKeepAliveDelay`) to detect stale per-player frame data |
| `BFMEDisconnectManager::hasDisconnectScreenNotifyTimedOut` | `0x0066B510` | compares elapsed time against `TheGlobalData + 0xCC0` (`NetworkDisconnectScreenNotifyTime`) |
| `BFMEConnectionManager::processRequestFrameDataCommand` | `0x006659B0` | command type `9` handler; rejects/clamps requested resend windows using `NetworkKeepAliveDelay`, then calls `0x0040D8CD` with player id and frame range |

These are timeout/readiness gates, not the delay patch itself, but they expose the
retail frame and keep-alive timing constants that a later patch design must not
confuse with ZH run-ahead command traffic.

## BFME frame pacing

ZH `Network::timeForNewFrame` is not a BFME byte match. A locate-only probe of
the 256-byte ZH-shaped body returned `0 located`, and BFME has no code xrefs to
the `NetworkRunAheadSlack`/`NetworkRunAheadMetricsTime` strings beyond their INI
parse-table rows. That rules out the ZH run-ahead pacing body as the direct patch
site.

The BFME-native `Network` object instead initializes QPC pacing state in the
constructor body at `0x006818B0`, now byte-matched as
`BFMENativeNetwork::construct`:

| Field | Constructor evidence |
| --- | --- |
| `+0x08` | connection manager pointer initialized to null |
| `+0x0C` | local/network status initialized to `0` |
| `+0x10` | `QueryPerformanceFrequency` output |
| `+0x18` | initial `QueryPerformanceCounter` output |
| `+0x20`/`+0x24` | QPC accumulator initialized to `0` |
| `+0x28`, `+0x34`, `+0x35` | pacing/status flags initialized to false |
| `+0x38` | frame/player sentinel initialized to `-1` |

The native vtable at `0x0111A968` resolves slot `+0x3C` to `0x00681F70` and
slot `+0x40` to `0x00682160`. Slot `+0x40` is now byte-matched as
`BFMENativeNetwork::getFramePacingStatus`:

| Function | RVA | Pacing evidence |
| --- | --- | --- |
| `BFMENativeNetwork::getFramePacingStatus` | `0x00682160` | returns `1` when not in active network status; without packet-router timing mode, returns `connectionManager->+0x1205C - currentFrame + 1`; otherwise accumulates QPC ticks and returns `0`, `1`, or `2` based on elapsed budget |

The remaining slot `+0x3C` at `0x00681F70` also uses connection manager
`+0x1205C`, current game frame `TheGameLogic + 0x3C`, and globals
`0x012F7718`, `0x012F771C`, `0x012F7724`, and `0x012F7728`.

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
- `src/game/native_network_callback.cpp` contains `BFMENetworkRegisteredCallback`
  at `0x0065C260`.
- `src/game/native_network_dispatcher.cpp` contains `BFMENetworkBackend::dispatchEvents`
  at `0x0065CA50` and its EH catch thunk at `0x0065D6F3`.
- `src/game/native_netcommandmsg.cpp` contains the BFME command type `7`
  request-player-leave constructor/destructor and its single dword payload
  setter/getter at `0x006741F0`, `0x00674230`, `0x00674240`, and `0x00674250`.
- `src/game/native_connection_timing.cpp` contains the first byte-matched BFME
  player-timeout, packet-router stall, disconnect-screen timeout, and request
  frame-data handler checks at `0x00662A50`, `0x00662B00`, `0x00664260`,
  `0x0066B510`, and `0x006659B0`.
- `src/game/native_network_interface.cpp` contains the native BFME `Network`
  constructor body at `0x006818B0`, anchoring the QPC frame-pacing fields, and
  the QPC-backed pacing-status helper at `0x00682160`.
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
4. DONE: recover the native dispatcher boundary and name the remaining wrapper
   fields before attempting any patch design.
5. DONE: rule out the ZH `NetRunAhead*` command classes for BFME command types
   `6` and `7`.
6. DONE: match the first BFME timing/readiness gates that consume
   `NetworkPlayerTimeoutTime`, `NetworkKeepAliveDelay`, and
   `NetworkDisconnectScreenNotifyTime`.
7. NEXT: trace the BFME frame scheduler that sends/consumes frame info, request
   frame-data, inform-player-leave-frame, and keep-alive commands. Command type
   `9` request-frame-data handling is matched; command type `8` and the frame
   tick sender remain next. Native QPC frame pacing is anchored, and slot
   `0x00682160` is matched; slot `0x00681F70` still needs a name/match before
   patch design.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.
