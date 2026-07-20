.386
.model flat
; ?Check_Shader_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
; Exact 95B @ 0x91B9A0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?Check_Shader_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z
?Check_Shader_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 88h, 0C4h, 00h, 00h, 00h, 89h, 8Eh, 7Ch
    db 02h, 00h, 00h, 8Bh, 80h, 0CCh, 00h, 00h, 00h, 8Bh, 0D0h, 89h, 86h, 80h, 02h, 00h
    db 00h, 81h, 0E2h, 0FFh, 00h, 00h, 00h, 52h, 0Fh, 0B6h, 0C4h, 50h, 8Bh, 0D1h, 81h, 0E2h
    db 0FFh, 00h, 00h, 00h, 52h, 0Fh, 0B6h, 0C5h, 50h, 68h, 0C0h, 0B5h, 13h, 01h, 68h, 18h
    db 67h, 34h, 01h, 0E8h, 0A8h, 01h, 0Ch, 00h, 83h, 0C4h, 18h, 68h, 18h, 67h, 34h, 01h
    db 8Dh, 8Eh, 0A4h, 02h, 00h, 00h, 0E8h, 0E5h, 0FDh, 0FFh, 0FFh, 5Eh, 0C2h, 04h, 00h
?Check_Shader_Support@DX8Caps@@AAEXABU_D3DCAPS8@@@Z ENDP
_TEXT ENDS
END
