.386
.model flat
; ?getMinPoints@QuickMatchPreferences@@QAEHXZ
; Exact 84B @ 0xABFF0; sealed MinPoints getter recovery
_TEXT SEGMENT
public ?getMinPoints@QuickMatchPreferences@@QAEHXZ
?getMinPoints@QuickMatchPreferences@@QAEHXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F1h, 68h, 0A4h, 11h, 08h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0BDh
    db 0CBh, 7Dh, 00h, 8Dh, 44h, 24h, 08h, 83h, 0C6h, 04h, 50h, 8Bh, 0CEh, 0E8h, 9Ah, 0EEh
    db 0F5h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Bh, 0F8h, 0E8h, 23h, 0B9h, 7Dh, 00h, 3Bh, 3Eh, 75h
    db 06h, 5Fh, 33h, 0C0h, 5Eh, 59h, 0C3h, 8Bh, 7Fh, 14h, 85h, 0FFh, 8Dh, 47h, 08h, 75h
    db 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0FFh, 15h, 84h, 93h, 35h, 01h, 83h, 0C4h, 04h
    db 5Fh, 5Eh, 59h, 0C3h
?getMinPoints@QuickMatchPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
