.386
.model flat
; ?winIsChild@GameWindow@@QAE_NPAV1@@Z
; Exact 34B @ 0x478D30; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?winIsChild@GameWindow@@QAE_NPAV1@@Z
?winIsChild@GameWindow@@QAE_NPAV1@@Z PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 16h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 80h, 00h, 02h, 00h, 00h, 3Bh, 0C8h, 74h, 09h, 85h, 0C0h, 75h, 0F2h, 32h, 0C0h
    db 0C2h, 04h
?winIsChild@GameWindow@@QAE_NPAV1@@Z ENDP
_TEXT ENDS
END
