.386
.model flat
; ?Set_Render_Device@WW3D@@SA?AW4WW3DErrorType@@HHHHH_N00@Z
; Exact 54B @ 0x8FD120; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?Set_Render_Device@WW3D@@SA?AW4WW3DErrorType@@HHHHH_N00@Z
?Set_Render_Device@WW3D@@SA?AW4WW3DErrorType@@HHHHH_N00@Z PROC
    db 8Bh, 44h, 24h, 20h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 54h, 24h, 18h, 50h, 8Bh, 44h, 24h
    db 18h, 51h, 8Bh, 4Ch, 24h, 18h, 52h, 8Bh, 54h, 24h, 18h, 50h, 8Bh, 44h, 24h, 18h
    db 51h, 8Bh, 4Ch, 24h, 18h, 52h, 50h, 51h, 0E8h, 0D3h, 0DEh, 00h, 00h, 83h, 0C4h, 20h
    db 84h, 0C0h, 0Fh, 95h, 0C0h, 0C3h
?Set_Render_Device@WW3D@@SA?AW4WW3DErrorType@@HHHHH_N00@Z ENDP
_TEXT ENDS
END
