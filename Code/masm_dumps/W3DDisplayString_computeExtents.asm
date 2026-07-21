.386
.model flat

; ?computeExtents@W3DDisplayString@@IAEXXZ
; Exact 192 retail bytes @ 0X006F5420.
; True start after 1B int3 pad at queued 0x006F541F; getWidth matched @ 0x006F53A0.
; Identity: SEH prologue, vcall getTextLength [vtbl+0xC], m_font@+8, vcall getText [vtbl+8],
; m_textRenderer@+0x14 Get_Formatted_Text_Extents, releaseBuffer, __ftol2 -> m_size@+0x1F0.
_TEXT SEGMENT
public ?computeExtents@W3DDisplayString@@IAEXXZ
?computeExtents@W3DDisplayString@@IAEXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0C8h, 0BAh, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 0Ch
    db 85h, 0C0h, 74h, 78h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 71h, 8Bh, 16h, 8Dh, 44h, 24h
    db 04h, 50h, 8Bh, 0CEh, 0FFh, 52h, 08h, 8Bh, 00h, 85h, 0C0h, 0C7h, 44h, 24h, 18h, 00h
    db 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Ch, 38h, 07h, 01h, 50h
    db 8Dh, 4Ch, 24h, 0Ch, 51h, 8Dh, 4Eh, 14h, 0E8h, 73h, 0D7h, 24h, 00h, 8Dh, 4Ch, 24h
    db 04h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 42h, 2Dh, 19h, 00h, 0D9h, 44h
    db 24h, 08h, 0E8h, 0A1h, 19h, 30h, 00h, 0D9h, 44h, 24h, 0Ch, 89h, 86h, 0F0h, 01h, 00h
    db 00h, 0E8h, 92h, 19h, 30h, 00h, 89h, 86h, 0F4h, 01h, 00h, 00h, 5Eh, 8Bh, 4Ch, 24h
    db 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h, 8Bh, 4Ch, 24h, 10h
    db 0C7h, 86h, 0F0h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 86h, 0F4h, 01h, 00h, 00h
    db 00h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h
?computeExtents@W3DDisplayString@@IAEXXZ ENDP
_TEXT ENDS
END
