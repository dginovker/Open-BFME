.386
.model flat
; ?getMaxPing@QuickMatchPreferences@@QAEHXZ
; Exact 85B @ 0xAC140; MaxPing string-anchor; sibling getter shape
_TEXT SEGMENT
public ?getMaxPing@QuickMatchPreferences@@QAEHXZ
?getMaxPing@QuickMatchPreferences@@QAEHXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F1h, 68h, 0CCh, 11h, 08h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 6Dh
    db 0CAh, 7Dh, 00h, 8Dh, 44h, 24h, 08h, 83h, 0C6h, 04h, 50h, 8Bh, 0CEh, 0E8h, 4Ah, 0EDh
    db 0F5h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Bh, 0F8h, 0E8h, 0D3h, 0B7h, 7Dh, 00h, 3Bh, 3Eh, 75h
    db 07h, 5Fh, 83h, 0C8h, 0FFh, 5Eh, 59h, 0C3h, 8Bh, 7Fh, 14h, 85h, 0FFh, 8Dh, 47h, 08h
    db 75h, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0FFh, 15h, 84h, 93h, 35h, 01h, 83h, 0C4h
    db 04h, 5Fh, 5Eh, 59h, 0C3h
?getMaxPing@QuickMatchPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
