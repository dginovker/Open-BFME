.386
.model flat
; ?getMusicVolume@OptionPreferences@@QAEMXZ
; Exact 101B @ 0x91B40; string-anchored Open-BFME4+Grok
_TEXT SEGMENT
public ?getMusicVolume@OptionPreferences@@QAEMXZ
?getMusicVolume@OptionPreferences@@QAEMXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F1h, 68h, 14h, 0FBh, 07h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 6Dh
    db 70h, 7Fh, 00h, 8Dh, 44h, 24h, 08h, 83h, 0C6h, 04h, 50h, 8Bh, 0CEh, 0E8h, 4Ah, 93h
    db 0F7h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Bh, 0F8h, 0E8h, 0D3h, 5Dh, 7Fh, 00h, 3Bh, 3Eh, 75h
    db 10h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 81h, 04h, 0Ch, 00h, 00h, 5Fh, 5Eh, 59h
    db 0C3h, 8Bh, 7Fh, 14h, 85h, 0FFh, 8Dh, 77h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h
    db 0BFh, 6Ch, 0C7h, 07h, 01h, 0B9h, 04h, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 5Fh, 0Fh
    db 94h, 0C0h, 5Eh, 59h, 0C3h
?getMusicVolume@OptionPreferences@@QAEMXZ ENDP
_TEXT ENDS
END
