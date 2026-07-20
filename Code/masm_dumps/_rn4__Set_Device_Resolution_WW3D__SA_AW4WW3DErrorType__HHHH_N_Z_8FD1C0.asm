.386
.model flat
; ?Set_Device_Resolution@WW3D@@SA?AW4WW3DErrorType@@HHHH_N@Z
; Exact 39B @ 0x8FD1C0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?Set_Device_Resolution@WW3D@@SA?AW4WW3DErrorType@@HHHH_N@Z
?Set_Device_Resolution@WW3D@@SA?AW4WW3DErrorType@@HHHH_N@Z PROC
    db 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 0Ch, 50h, 8Bh, 44h, 24h
    db 0Ch, 51h, 8Bh, 4Ch, 24h, 0Ch, 52h, 50h, 51h, 0E8h, 0E2h, 0BCh, 00h, 00h, 83h, 0C4h
    db 14h, 84h, 0C0h, 0Fh, 95h, 0C0h, 0C3h
?Set_Device_Resolution@WW3D@@SA?AW4WW3DErrorType@@HHHH_N@Z ENDP
_TEXT ENDS
END
