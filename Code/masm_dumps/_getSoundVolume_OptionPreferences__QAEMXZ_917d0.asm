.386
.model flat
; ?getSoundVolume@OptionPreferences@@QAEMXZ
; Exact 129B @ 0x917D0; string-anchor SFXVolume true body (queue 0x561741 was OptionsMenuInit interior)
_TEXT SEGMENT
public ?getSoundVolume@OptionPreferences@@QAEMXZ
?getSoundVolume@OptionPreferences@@QAEMXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F1h, 68h, 0C8h, 0FAh, 07h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0DDh
    db 73h, 7Fh, 00h, 8Dh, 44h, 24h, 08h, 83h, 0C6h, 04h, 50h, 8Bh, 0CEh, 0E8h, 0BAh, 96h
    db 0F7h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Bh, 0F8h, 0E8h, 43h, 61h, 7Fh, 00h, 3Bh, 3Eh, 75h
    db 1Eh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 0FFh, 92h, 20h, 01h, 00h, 00h, 0D9h
    db 80h, 80h, 00h, 00h, 00h, 0D8h, 0Dh, 0C4h, 0FAh, 07h, 01h, 5Fh, 5Eh, 59h, 0C3h, 8Bh
    db 7Fh, 14h, 85h, 0FFh, 8Dh, 47h, 08h, 75h, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0FFh
    db 15h, 80h, 93h, 35h, 01h, 0D8h, 15h, 50h, 53h, 07h, 01h, 83h, 0C4h, 04h, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Ah, 08h, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 5Fh, 5Eh, 59h
    db 0C3h
?getSoundVolume@OptionPreferences@@QAEMXZ ENDP
_TEXT ENDS
END
