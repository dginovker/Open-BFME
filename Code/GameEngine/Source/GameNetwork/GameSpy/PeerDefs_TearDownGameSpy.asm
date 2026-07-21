.386
.model flat

; ?TearDownGameSpy@@YAXXZ
; Exact 607 retail bytes @ 0x00633390.
; Ghidra ENTRY FUN_00a33390 size 607 (queue said 575 — wrong; ret@+0x25e).
; Identity: SEH + TheGameSpyInfo getLocalProfileID(+0x70) + PSPlayerStats
; cache + endThread x4 + delete Rank/PS/Buddy/Peer/Info/Pinger/Ladder/Config
; + SignalUIInteraction(0x13) + deleteNotificationBox. ZH C++ blocked by
; GameSpyInfo vtable slots (0x70/0x14c vs 0x54/0x120) and PSPlayerStats frame
; (sub esp 0x1e8 vs 0x1c0). Sibling SetUpGameSpy also exact-MASM.
_TEXT SEGMENT
public ?TearDownGameSpy@@YAXXZ
?TearDownGameSpy@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 6Ah, 0FFh, 68h, 0D1h
    db 09h, 04h, 01h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0E8h, 01h, 00h
    db 00h, 53h, 33h, 0DBh, 3Bh, 0CBh, 56h, 0Fh, 84h, 0FEh, 00h, 00h, 00h, 8Bh, 01h, 0FFh
    db 50h, 70h, 85h, 0C0h, 0Fh, 84h, 0F1h, 00h, 00h, 00h, 8Bh, 0Dh, 0F0h, 76h, 2Fh, 01h
    db 8Bh, 31h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 70h, 8Bh, 0Dh, 0F0h
    db 76h, 2Fh, 01h, 50h, 8Dh, 44h, 24h, 30h, 50h, 0FFh, 56h, 24h, 39h, 5Ch, 24h, 2Ch
    db 89h, 9Ch, 24h, 0F8h, 01h, 00h, 00h, 0Fh, 84h, 0AAh, 00h, 00h, 00h, 8Dh, 4Ch, 24h
    db 18h, 0E8h, 0DCh, 33h, 9Fh, 0FFh, 81h, 0ECh, 0C4h, 01h, 00h, 00h, 8Dh, 94h, 24h, 0F0h
    db 01h, 00h, 00h, 8Bh, 0CCh, 89h, 0A4h, 24h, 0CCh, 01h, 00h, 00h, 52h, 0C6h, 84h, 24h
    db 0C0h, 03h, 00h, 00h, 01h, 0E8h, 59h, 93h, 9Eh, 0FFh, 8Dh, 84h, 24h, 0D0h, 01h, 00h
    db 00h, 50h, 0E8h, 49h, 4Bh, 9Eh, 0FFh, 8Bh, 00h, 81h, 0C4h, 0C4h, 01h, 00h, 00h, 89h
    db 64h, 24h, 0Ch, 8Bh, 0CCh, 50h, 0C6h, 84h, 24h, 00h, 02h, 00h, 00h, 02h, 0E8h, 6Dh
    db 57h, 25h, 00h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 97h, 0F3h, 0A0h, 0FFh, 8Bh, 4Ch, 24h, 0Ch
    db 8Bh, 44h, 24h, 14h, 2Bh, 0C1h, 3Bh, 0CBh, 0C6h, 84h, 24h, 0F8h, 01h, 00h, 00h, 01h
    db 74h, 1Ch, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 31h, 0EAh, 24h, 00h, 83h
    db 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 65h, 0B1h, 1Fh, 00h, 83h, 0C4h, 08h, 8Dh, 4Ch
    db 24h, 18h, 0E8h, 0FEh, 0CFh, 9Fh, 0FFh, 8Dh, 4Ch, 24h, 18h, 88h, 9Ch, 24h, 0F8h, 01h
    db 00h, 00h, 0E8h, 0F9h, 0Ch, 9Eh, 0FFh, 8Dh, 4Ch, 24h, 2Ch, 0C7h, 84h, 24h, 0F8h, 01h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 60h, 27h, 9Fh, 0FFh, 8Bh, 0Dh, 0F0h, 76h, 2Fh
    db 01h, 3Bh, 0CBh, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 08h, 8Bh, 0Dh, 0B4h, 71h, 2Fh, 01h
    db 3Bh, 0CBh, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 08h, 8Bh, 0Dh, 0C8h, 71h, 2Fh, 01h, 3Bh
    db 0CBh, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 08h, 8Bh, 0Dh, 0F4h, 76h, 2Fh, 01h, 3Bh, 0CBh
    db 74h, 05h, 8Bh, 01h, 0FFh, 50h, 08h, 0A1h, 1Ch, 40h, 2Fh, 01h, 3Bh, 0C3h, 74h, 0Fh
    db 50h, 0E8h, 0AAh, 0E9h, 24h, 00h, 83h, 0C4h, 04h, 89h, 1Dh, 1Ch, 40h, 2Fh, 01h, 8Bh
    db 0Dh, 0F0h, 76h, 2Fh, 01h, 3Bh, 0CBh, 74h, 0Ch, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h
    db 1Dh, 0F0h, 76h, 2Fh, 01h, 8Bh, 0Dh, 0B4h, 71h, 2Fh, 01h, 3Bh, 0CBh, 74h, 0Ch, 8Bh
    db 01h, 6Ah, 01h, 0FFh, 10h, 89h, 1Dh, 0B4h, 71h, 2Fh, 01h, 8Bh, 0Dh, 0C8h, 71h, 2Fh
    db 01h, 3Bh, 0CBh, 74h, 0Ch, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h, 1Dh, 0C8h, 71h, 2Fh
    db 01h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 3Bh, 0CBh, 74h, 2Ch, 8Bh, 01h, 0FFh, 90h, 4Ch
    db 01h, 00h, 00h, 85h, 0C0h, 74h, 0Ah, 6Ah, 13h, 0E8h, 6Fh, 13h, 0A0h, 0FFh, 83h, 0C4h
    db 04h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 3Bh, 0CBh, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh
    db 12h, 89h, 1Dh, 94h, 71h, 2Fh, 01h, 8Bh, 0Dh, 0F4h, 76h, 2Fh, 01h, 3Bh, 0CBh, 74h
    db 0Ch, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 89h, 1Dh, 0F4h, 76h, 2Fh, 01h, 8Bh, 0Dh, 0E8h
    db 70h, 2Fh, 01h, 3Bh, 0CBh, 74h, 16h, 8Bh, 0F1h, 0E8h, 8Eh, 0E9h, 9Ch, 0FFh, 56h, 0E8h
    db 0FCh, 0E8h, 24h, 00h, 83h, 0C4h, 04h, 89h, 1Dh, 0E8h, 70h, 2Fh, 01h, 8Bh, 0Dh, 0E4h
    db 70h, 2Fh, 01h, 3Bh, 0CBh, 74h, 0Ch, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h, 1Dh, 0E4h
    db 70h, 2Fh, 01h, 0E8h, 05h, 3Ch, 9Fh, 0FFh, 8Bh, 8Ch, 24h, 0F0h, 01h, 00h, 00h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 0F4h, 01h, 00h, 00h, 0C3h
?TearDownGameSpy@@YAXXZ ENDP
_TEXT ENDS
END
