.386
.model flat
; ?setMaxPoints@QuickMatchPreferences@@QAEXH@Z
; Exact 169B @ 0xAD340; MaxPoints string-anchor sibling of setMaxDisconnects/setWaitTime
_TEXT SEGMENT
public ?setMaxPoints@QuickMatchPreferences@@QAEXH@Z
?setMaxPoints@QuickMatchPreferences@@QAEXH@Z PROC
    db 6Ah, 0FFh, 68h, 80h, 79h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 18h, 50h, 51h, 89h, 64h, 24h, 20h, 8Bh, 0CCh, 68h, 0B4h, 0C7h
    db 07h, 01h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 41h, 0B8h, 7Dh, 00h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 0E8h, 67h, 0BCh, 7Dh, 00h, 83h, 0C4h, 0Ch, 68h, 98h, 11h, 08h
    db 01h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 26h, 0B8h, 7Dh, 00h, 8Dh, 54h, 24h, 18h, 52h, 8Dh
    db 4Eh, 04h, 0C6h, 44h, 24h, 14h, 01h, 0E8h, 2Eh, 13h, 0F9h, 0FFh, 8Dh, 4Ch, 24h, 04h
    db 51h, 8Bh, 0C8h, 0E8h, 0D8h, 0A8h, 7Dh, 00h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 10h
    db 00h, 0E8h, 7Ah, 0A5h, 7Dh, 00h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 69h, 0A5h, 7Dh, 00h, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Eh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?setMaxPoints@QuickMatchPreferences@@QAEXH@Z ENDP
_TEXT ENDS
END
