.386
.model flat
; ?winSetParent@GameWindow@@QAEHPAV1@@Z
; Exact 84B @ 0x478CB0; Open-BFME4+Grok
_TEXT SEGMENT
public ?winSetParent@GameWindow@@QAEHPAV1@@Z
?winSetParent@GameWindow@@QAEHPAV1@@Z PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 00h, 02h, 00h, 00h, 85h, 0C0h, 8Bh, 0Dh, 40h, 1Bh, 2Fh
    db 01h, 56h, 75h, 07h, 0E8h, 3Ch, 0Dh, 0BBh, 0FFh, 0EBh, 05h, 0E8h, 85h, 0CDh, 0B9h, 0FFh
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 75h, 16h, 56h, 0E8h
    db 99h, 2Bh, 0BBh, 0FFh, 0C7h, 86h, 00h, 02h, 00h, 00h, 00h, 00h, 00h, 00h, 33h, 0C0h
    db 5Eh, 0C2h, 04h, 00h, 8Bh, 11h, 50h, 56h, 0FFh, 92h, 0CCh, 00h, 00h, 00h, 33h, 0C0h
    db 5Eh, 0C2h, 04h, 00h
?winSetParent@GameWindow@@QAEHPAV1@@Z ENDP
_TEXT ENDS
END
