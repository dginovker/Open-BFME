.386
.model flat
; ?init@DirectInputMouse@@UAEXXZ
; Exact 76B @ 0x6BBD20; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?init@DirectInputMouse@@UAEXXZ
?init@DirectInputMouse@@UAEXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 0E8h, 2Fh, 67h, 94h, 0FFh, 8Bh, 0CEh, 0E8h, 4Bh, 6Dh
    db 98h, 0FFh, 8Bh, 86h, 10h, 4Dh, 00h, 00h, 8Bh, 8Eh, 14h, 4Dh, 00h, 00h, 8Dh, 54h
    db 24h, 04h, 89h, 44h, 24h, 04h, 0A1h, 38h, 0D2h, 2Eh, 01h, 52h, 50h, 89h, 4Ch, 24h
    db 10h, 0FFh, 15h, 0ACh, 8Fh, 35h, 01h, 8Bh, 4Ch, 24h, 08h, 8Bh, 54h, 24h, 04h, 51h
    db 52h, 0FFh, 15h, 70h, 90h, 35h, 01h, 5Eh, 83h, 0C4h, 08h, 0C3h
?init@DirectInputMouse@@UAEXXZ ENDP
_TEXT ENDS
END
