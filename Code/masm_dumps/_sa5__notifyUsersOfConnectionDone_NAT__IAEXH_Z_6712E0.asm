.386
.model flat
; ?notifyUsersOfConnectionDone@NAT@@IAEXH@Z
; Exact 578B @ 0x006712E0; Open-BFME4
_TEXT SEGMENT
public ?notifyUsersOfConnectionDone@NAT@@IAEXH@Z
?notifyUsersOfConnectionDone@NAT@@IAEXH@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 57h, 4Eh, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0A8h, 01h, 00h, 00h, 53h, 56h, 8Bh, 0F1h, 8Bh
    db 46h, 10h, 8Bh, 4Ch, 0C6h, 68h, 8Bh, 56h, 08h, 8Bh, 0Ch, 8Ah, 33h, 0DBh, 3Bh, 0CBh
    db 57h, 75h, 0Fh, 6Ah, 06h, 50h, 8Bh, 0CEh, 0E8h, 0B4h, 0D8h, 9Bh, 0FFh, 0E9h, 0E9h, 01h
    db 00h, 00h, 8Dh, 4Ch, 24h, 20h, 0E8h, 0D1h, 5Eh, 9Ah, 0FFh, 89h, 9Ch, 24h, 0BCh, 01h
    db 00h, 00h, 89h, 5Ch, 24h, 18h, 8Bh, 46h, 10h, 8Bh, 8Ch, 24h, 0C4h, 01h, 00h, 00h
    db 50h, 51h, 51h, 89h, 64h, 24h, 28h, 8Bh, 0CCh, 68h, 0ECh, 0A3h, 11h, 01h, 0C6h, 84h
    db 24h, 0CCh, 01h, 00h, 00h, 01h, 0E8h, 65h, 78h, 21h, 00h, 8Dh, 54h, 24h, 24h, 52h
    db 0E8h, 8Bh, 7Ch, 21h, 00h, 83h, 0C4h, 10h, 68h, 6Bh, 2Eh, 10h, 01h, 68h, 68h, 2Eh
    db 10h, 01h, 8Dh, 4Ch, 24h, 5Ch, 0C7h, 44h, 24h, 28h, 0Dh, 00h, 00h, 00h, 0C6h, 84h
    db 24h, 0Ch, 01h, 00h, 00h, 01h, 0E8h, 0Ch, 9Fh, 9Bh, 0FFh, 89h, 5Ch, 24h, 10h, 0C6h
    db 84h, 24h, 0BCh, 01h, 00h, 00h, 02h, 33h, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 10h, 39h, 7Ch, 0C6h, 68h, 0Fh, 84h, 0B1h, 00h, 00h, 00h, 8Bh, 4Eh, 08h
    db 8Bh, 0Ch, 0B9h, 3Bh, 0CBh, 0Fh, 84h, 0A3h, 00h, 00h, 00h, 0E8h, 0Bh, 66h, 9Bh, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 96h, 00h, 00h, 00h, 89h, 5Ch, 24h, 14h, 8Bh, 46h, 08h, 8Bh
    db 0Ch, 0B8h, 8Dh, 54h, 24h, 1Ch, 52h, 0C6h, 84h, 24h, 0C0h, 01h, 00h, 00h, 03h, 0E8h
    db 27h, 8Eh, 9Ch, 0FFh, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h, 84h, 24h, 0C0h, 01h, 00h, 00h
    db 04h, 0E8h, 5Ah, 7Ch, 21h, 00h, 8Dh, 4Ch, 24h, 1Ch, 0C6h, 84h, 24h, 0BCh, 01h, 00h
    db 00h, 03h, 0E8h, 0C9h, 6Dh, 21h, 00h, 8Bh, 44h, 24h, 10h, 3Bh, 0C3h, 74h, 1Bh, 66h
    db 39h, 58h, 04h, 74h, 15h, 6Ah, 01h, 8Dh, 4Ch, 24h, 10h, 51h, 8Dh, 4Ch, 24h, 18h
    db 0C6h, 44h, 24h, 14h, 2Ch, 0E8h, 36h, 69h, 21h, 00h, 8Bh, 44h, 24h, 14h, 3Bh, 0C3h
    db 74h, 09h, 0Fh, 0B7h, 48h, 04h, 83h, 0C0h, 08h, 0EBh, 07h, 33h, 0C9h, 0B8h, 8Bh, 38h
    db 07h, 01h, 51h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 13h, 69h, 21h, 00h, 8Dh, 4Ch, 24h
    db 14h, 0C6h, 84h, 24h, 0BCh, 01h, 00h, 00h, 02h, 0E8h, 0E2h, 64h, 21h, 00h, 47h, 83h
    db 0FFh, 08h, 0Fh, 8Ch, 38h, 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 10h, 3Bh, 0CBh, 74h, 05h
    db 83h, 0C1h, 08h, 0EBh, 05h, 0B9h, 8Bh, 38h, 07h, 01h, 8Bh, 0C1h, 8Dh, 70h, 01h, 90h
    db 8Ah, 10h, 40h, 3Ah, 0D3h, 75h, 0F9h, 2Bh, 0C6h, 03h, 0C1h, 50h, 51h, 8Dh, 4Ch, 24h
    db 2Ch, 0E8h, 01h, 9Eh, 9Bh, 0FFh, 8Bh, 44h, 24h, 18h, 3Bh, 0C3h, 8Dh, 48h, 08h, 75h
    db 05h, 0B9h, 8Bh, 38h, 07h, 01h, 8Bh, 0C1h, 8Dh, 70h, 01h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Ah, 10h, 40h, 3Ah, 0D3h, 75h, 0F9h, 2Bh, 0C6h, 03h, 0C1h, 50h, 51h, 8Dh, 4Ch, 24h
    db 68h, 0E8h, 0D1h, 9Dh, 9Bh, 0FFh, 8Bh, 0Dh, 0C8h, 71h, 2Fh, 01h, 8Bh, 11h, 8Dh, 44h
    db 24h, 20h, 50h, 0FFh, 52h, 18h, 8Dh, 4Ch, 24h, 10h, 0C6h, 84h, 24h, 0BCh, 01h, 00h
    db 00h, 01h, 0E8h, 59h, 64h, 21h, 00h, 8Dh, 4Ch, 24h, 18h, 88h, 9Ch, 24h, 0BCh, 01h
    db 00h, 00h, 0E8h, 49h, 64h, 21h, 00h, 8Dh, 4Ch, 24h, 20h, 0C7h, 84h, 24h, 0BCh, 01h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0CAh, 56h, 9Ah, 0FFh, 8Bh, 8Ch, 24h, 0B4h, 01h
    db 00h, 00h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 0B4h, 01h
    db 00h, 00h
?notifyUsersOfConnectionDone@NAT@@IAEXH@Z ENDP
_TEXT ENDS
END
