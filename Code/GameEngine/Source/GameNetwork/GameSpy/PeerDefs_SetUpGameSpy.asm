.386
.model flat

; ?SetUpGameSpy@@YAXPBD0@Z
; Exact 723 retail bytes @ 0x006377D0.
; True start is SEH prologue after createNewGameSpyInfoInterface @ 0x00637760 (89B).
; Queue candidate 0x0063777A was INSIDE createNew; snapped to 0x006377D0 size 723.
; Identity: TearDownGameSpy; CreateDirectory %sLoTRB4MEOnline[+\Ladders];
; buddy/peer/pinger/info factories; setMOTD/setConfig; CustomMatchPreferences;
; GameSpyConfig create; LadderList; 0xb4 factory+startThreads; RankPoints.
_TEXT SEGMENT
public ?SetUpGameSpy@@YAXPBD0@Z
?SetUpGameSpy@@YAXPBD0@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 66h, 12h, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 53h, 8Bh, 5Ch, 24h, 2Ch, 85h, 0DBh, 56h
    db 57h, 75h, 05h, 0BBh, 1Ch, 30h, 07h, 01h, 8Bh, 7Ch, 24h, 38h, 85h, 0FFh, 75h, 05h
    db 0BFh, 1Ch, 30h, 07h, 01h, 0E8h, 0DFh, 32h, 0A0h, 0FFh, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h
    db 8Dh, 44h, 24h, 34h, 50h, 0E8h, 0D0h, 8Eh, 9Dh, 0FFh, 8Bh, 44h, 24h, 34h, 85h, 0C0h
    db 0C7h, 44h, 24h, 2Ch, 00h, 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 8Bh, 35h, 0DCh, 8Ch, 35h, 01h, 6Ah, 00h, 50h, 0FFh, 0D6h, 8Dh
    db 4Ch, 24h, 38h, 51h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0E8h, 9Bh, 8Eh, 9Dh, 0FFh, 8Bh
    db 00h, 85h, 0C0h, 0C6h, 44h, 24h, 2Ch, 01h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 50h, 51h, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 68h, 0C4h, 8Ah, 11h
    db 01h, 0E8h, 4Ah, 13h, 25h, 00h, 8Dh, 54h, 24h, 3Ch, 52h, 0E8h, 70h, 17h, 25h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 38h, 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 0AFh, 00h, 25h
    db 00h, 8Bh, 44h, 24h, 34h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 6Ah, 00h, 50h, 0FFh, 0D6h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Dh, 44h
    db 24h, 38h, 50h, 0E8h, 32h, 8Eh, 9Dh, 0FFh, 8Bh, 00h, 85h, 0C0h, 0C6h, 44h, 24h, 2Ch
    db 02h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 51h, 89h
    db 64h, 24h, 14h, 8Bh, 0CCh, 68h, 0A4h, 8Ah, 11h, 01h, 0E8h, 0E1h, 12h, 25h, 00h, 8Dh
    db 4Ch, 24h, 3Ch, 51h, 0E8h, 07h, 17h, 25h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 38h
    db 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 46h, 00h, 25h, 00h, 8Bh, 44h, 24h, 34h, 85h, 0C0h
    db 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 6Ah, 00h, 50h, 0FFh
    db 0D6h, 0E8h, 09h, 72h, 9Dh, 0FFh, 0A3h, 0B4h, 71h, 2Fh, 01h, 8Bh, 10h, 8Bh, 0C8h, 0FFh
    db 52h, 04h, 0E8h, 58h, 0C7h, 9Ch, 0FFh, 0A3h, 0C8h, 71h, 2Fh, 01h, 8Bh, 10h, 8Bh, 0C8h
    db 0FFh, 52h, 04h, 0E8h, 8Bh, 0E9h, 9Fh, 0FFh, 0A3h, 0F0h, 76h, 2Fh, 01h, 8Bh, 10h, 8Bh
    db 0C8h, 0FFh, 52h, 04h, 0E8h, 0C6h, 35h, 9Eh, 0FFh, 53h, 8Dh, 4Ch, 24h, 3Ch, 0A3h, 94h
    db 71h, 2Fh, 01h, 0E8h, 68h, 12h, 25h, 00h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 8Bh, 01h
    db 8Dh, 54h, 24h, 38h, 52h, 0C6h, 44h, 24h, 30h, 03h, 0FFh, 90h, 00h, 01h, 00h, 00h
    db 8Dh, 4Ch, 24h, 38h, 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 0C2h, 0FFh, 24h, 00h, 57h, 8Dh
    db 4Ch, 24h, 3Ch, 0E8h, 38h, 12h, 25h, 00h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h, 8Bh, 01h
    db 8Dh, 54h, 24h, 38h, 52h, 0C6h, 44h, 24h, 30h, 04h, 0FFh, 90h, 08h, 01h, 00h, 00h
    db 8Dh, 4Ch, 24h, 38h, 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 92h, 0FFh, 24h, 00h, 8Dh, 4Ch
    db 24h, 10h, 0E8h, 3Eh, 37h, 9Dh, 0FFh, 0A1h, 94h, 71h, 2Fh, 01h, 8Bh, 30h, 0B3h, 05h
    db 8Dh, 4Ch, 24h, 10h, 88h, 5Ch, 24h, 2Ch, 0E8h, 0A5h, 22h, 9Eh, 0FFh, 8Bh, 0Dh, 94h
    db 71h, 2Fh, 01h, 50h, 0FFh, 96h, 0D4h, 00h, 00h, 00h, 8Bh, 0Dh, 94h, 71h, 2Fh, 01h
    db 8Bh, 31h, 8Dh, 4Ch, 24h, 10h, 0E8h, 83h, 04h, 9Dh, 0FFh, 8Bh, 0Dh, 94h, 71h, 2Fh
    db 01h, 50h, 0FFh, 96h, 0D8h, 00h, 00h, 00h, 51h, 89h, 64h, 24h, 10h, 8Bh, 0CCh, 57h
    db 0E8h, 0BBh, 11h, 25h, 00h, 0E8h, 0BFh, 0BAh, 9Fh, 0FFh, 6Ah, 0Ch, 0A3h, 0E4h, 70h, 2Fh
    db 01h, 0E8h, 1Ah, 0A5h, 24h, 00h, 83h, 0C4h, 08h, 89h, 44h, 24h, 0Ch, 85h, 0C0h, 0C6h
    db 44h, 24h, 2Ch, 06h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0DAh, 41h, 9Eh, 0FFh, 0EBh, 02h, 33h
    db 0C0h, 88h, 5Ch, 24h, 2Ch, 0A3h, 0E8h, 70h, 2Fh, 01h, 0E8h, 44h, 32h, 0A0h, 0FFh, 0A3h
    db 0F4h, 76h, 2Fh, 01h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 04h, 6Ah, 30h, 0E8h, 0DEh, 0A4h
    db 24h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 85h, 0C0h, 0C6h, 44h, 24h, 2Ch, 07h
    db 74h, 09h, 8Bh, 0C8h, 0E8h, 0ECh, 0F6h, 9Fh, 0FFh, 0EBh, 02h, 33h, 0C0h, 8Dh, 4Ch, 24h
    db 10h, 0A3h, 1Ch, 40h, 2Fh, 01h, 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 0EAh, 0A4h, 0A0h, 0FFh
    db 8Dh, 4Ch, 24h, 34h, 0C7h, 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0AFh, 0FEh, 24h
    db 00h, 8Bh, 4Ch, 24h, 24h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h
    db 0C4h, 24h, 0C3h
?SetUpGameSpy@@YAXPBD0@Z ENDP
_TEXT ENDS
END
