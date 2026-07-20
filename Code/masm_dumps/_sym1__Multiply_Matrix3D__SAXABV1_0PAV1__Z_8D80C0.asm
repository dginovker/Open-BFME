.386
.model flat
; ?Multiply@Matrix3D@@SAXABV1@0PAV1@@Z
; Exact 403B @ 0x8D80C0; symbol-pin Open-BFME4+Grok
_TEXT SEGMENT
public ?Multiply@Matrix3D@@SAXABV1@0PAV1@@Z
?Multiply@Matrix3D@@SAXABV1@0PAV1@@Z PROC
    db 8Bh, 54h, 24h, 0Ch, 8Bh, 44h, 24h, 04h, 83h, 0ECh, 30h, 3Bh, 0D0h, 75h, 55h, 8Bh
    db 08h, 89h, 0Ch, 24h, 8Bh, 48h, 04h, 89h, 4Ch, 24h, 04h, 8Bh, 48h, 08h, 89h, 4Ch
    db 24h, 08h, 8Bh, 48h, 0Ch, 89h, 4Ch, 24h, 0Ch, 8Bh, 48h, 10h, 89h, 4Ch, 24h, 10h
    db 8Bh, 48h, 14h, 89h, 4Ch, 24h, 14h, 8Bh, 48h, 18h, 89h, 4Ch, 24h, 18h, 8Bh, 48h
    db 1Ch, 89h, 4Ch, 24h, 1Ch, 8Bh, 48h, 20h, 89h, 4Ch, 24h, 20h, 8Bh, 48h, 24h, 89h
    db 4Ch, 24h, 24h, 8Bh, 48h, 28h, 8Bh, 40h, 2Ch, 89h, 44h, 24h, 2Ch, 89h, 4Ch, 24h
    db 28h, 8Dh, 04h, 24h, 8Bh, 4Ch, 24h, 38h, 0D9h, 01h, 0D9h, 41h, 10h, 0D9h, 41h, 20h
    db 0D9h, 0C2h, 0D8h, 08h, 0D9h, 0C1h, 0D8h, 48h, 08h, 0DEh, 0C1h, 0D9h, 0C2h, 0D8h, 48h, 04h
    db 0DEh, 0C1h, 0D9h, 1Ah, 0D9h, 0C0h, 0D8h, 48h, 18h, 0D9h, 0C2h, 0D8h, 48h, 14h, 0DEh, 0C1h
    db 0D9h, 0C3h, 0D8h, 48h, 10h, 0DEh, 0C1h, 0D9h, 5Ah, 10h, 0D8h, 48h, 28h, 0D9h, 0C9h, 0D8h
    db 48h, 24h, 0DEh, 0C1h, 0D9h, 0C9h, 0D8h, 48h, 20h, 0DEh, 0C1h, 0D9h, 5Ah, 20h, 0D9h, 41h
    db 04h, 0D9h, 41h, 14h, 0D9h, 41h, 24h, 0D9h, 0C2h, 0D8h, 08h, 0D9h, 0C1h, 0D8h, 48h, 08h
    db 0DEh, 0C1h, 0D9h, 0C2h, 0D8h, 48h, 04h, 0DEh, 0C1h, 0D9h, 5Ah, 04h, 0D9h, 0C0h, 0D8h, 48h
    db 18h, 0D9h, 0C2h, 0D8h, 48h, 14h, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 48h, 10h, 0DEh, 0C1h, 0D9h
    db 5Ah, 14h, 0D8h, 48h, 28h, 0D9h, 0C9h, 0D8h, 48h, 24h, 0DEh, 0C1h, 0D9h, 0C9h, 0D8h, 48h
    db 20h, 0DEh, 0C1h, 0D9h, 5Ah, 24h, 0D9h, 41h, 08h, 0D9h, 41h, 18h, 0D9h, 41h, 28h, 0D9h
    db 0C2h, 0D8h, 08h, 0D9h, 0C1h, 0D8h, 48h, 08h, 0DEh, 0C1h, 0D9h, 0C2h, 0D8h, 48h, 04h, 0DEh
    db 0C1h, 0D9h, 5Ah, 08h, 0D9h, 0C0h, 0D8h, 48h, 18h, 0D9h, 0C2h, 0D8h, 48h, 14h, 0DEh, 0C1h
    db 0D9h, 0C3h, 0D8h, 48h, 10h, 0DEh, 0C1h, 0D9h, 5Ah, 18h, 0D8h, 48h, 28h, 0D9h, 0C9h, 0D8h
    db 48h, 24h, 0DEh, 0C1h, 0D9h, 0C9h, 0D8h, 48h, 20h, 0DEh, 0C1h, 0D9h, 5Ah, 28h, 0D9h, 41h
    db 0Ch, 0D9h, 41h, 1Ch, 0D9h, 41h, 2Ch, 0D9h, 0C2h, 0D8h, 08h, 0D9h, 0C1h, 0D8h, 48h, 08h
    db 0DEh, 0C1h, 0D9h, 0C2h, 0D8h, 48h, 04h, 0DEh, 0C1h, 0D8h, 40h, 0Ch, 0D9h, 5Ah, 0Ch, 0D9h
    db 0C0h, 0D8h, 48h, 18h, 0D9h, 0C2h, 0D8h, 48h, 14h, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 48h, 10h
    db 0DEh, 0C1h, 0D8h, 40h, 1Ch, 0D9h, 5Ah, 1Ch, 0D8h, 48h, 28h, 0D9h, 0C9h, 0D8h, 48h, 24h
    db 0DEh, 0C1h, 0D9h, 0C9h, 0D8h, 48h, 20h, 0DEh, 0C1h, 0D8h, 40h, 2Ch, 0D9h, 5Ah, 2Ch, 83h
    db 0C4h, 30h, 0C3h
?Multiply@Matrix3D@@SAXABV1@0PAV1@@Z ENDP
_TEXT ENDS
END
