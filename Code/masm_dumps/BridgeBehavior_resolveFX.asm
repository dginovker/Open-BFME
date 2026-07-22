.386
.model flat
; ?resolveFX@BridgeBehavior@@IAEXXZ
; Exact 723B @ 0x001F2AF0; queue 0x00776416 was INSIDE ModelConditionInfo ctor (0x776330);
; true body: BODYDAMAGETYPE_COUNT=4 x MAX_BRIDGE_BODY_FX=3 OCL/FX/sound resolve; m_fxResolved@+0x47c
_TEXT SEGMENT
public ?resolveFX@BridgeBehavior@@IAEXXZ
?resolveFX@BridgeBehavior@@IAEXXZ PROC
    db 6Ah, 0FFh, 68h, 40h, 0AAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 30h, 53h, 8Bh, 0D9h, 8Bh, 43h, 08h, 8Bh, 0Dh
    db 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 55h, 56h, 89h, 44h, 24h, 18h, 57h, 83h, 0C0h, 38h
    db 50h, 89h, 5Ch, 24h, 3Ch, 0FFh, 92h, 98h, 00h, 00h, 00h, 33h, 0F6h, 3Bh, 0C6h, 0Fh
    db 84h, 7Bh, 02h, 00h, 00h, 8Dh, 4Ch, 24h, 18h, 51h, 8Bh, 0C8h, 0E8h, 0FAh, 7Ch, 0E5h
    db 0FFh, 51h, 8Dh, 54h, 24h, 1Ch, 89h, 64h, 24h, 38h, 8Bh, 0CCh, 52h, 89h, 74h, 24h
    db 50h, 0E8h, 0Ah, 50h, 69h, 00h, 8Bh, 0Dh, 08h, 70h, 2Fh, 01h, 0E8h, 2Ch, 22h, 0E4h
    db 0FFh, 8Bh, 0F8h, 3Bh, 0FEh, 0Fh, 84h, 34h, 02h, 00h, 00h, 89h, 74h, 24h, 10h, 8Dh
    db 83h, 0BCh, 02h, 00h, 00h, 0C6h, 44h, 24h, 48h, 01h, 89h, 44h, 24h, 14h, 83h, 0C3h
    db 6Ch, 33h, 0EDh, 55h, 56h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0CFh, 0E8h, 9Eh, 15h, 0E5h
    db 0FFh, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 4Ch, 02h, 0E8h, 0F0h, 50h, 69h, 00h
    db 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 48h, 01h, 0E8h, 92h, 4Dh, 69h, 00h, 8Bh, 44h
    db 24h, 10h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 8Bh, 0Dh, 0Ch, 0F7h, 2Eh, 01h, 50h, 0E8h, 1Dh, 0C2h, 0E2h, 0FFh, 55h, 56h, 8Dh, 54h
    db 24h, 2Ch, 52h, 8Bh, 0CFh, 89h, 43h, 0D0h, 0E8h, 1Fh, 0AFh, 0E2h, 0FFh, 50h, 8Dh, 4Ch
    db 24h, 14h, 0C6h, 44h, 24h, 4Ch, 03h, 0E8h, 0A4h, 50h, 69h, 00h, 8Dh, 4Ch, 24h, 24h
    db 0C6h, 44h, 24h, 48h, 01h, 0E8h, 46h, 4Dh, 69h, 00h, 8Bh, 44h, 24h, 10h, 85h, 0C0h
    db 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 4Ch, 14h
    db 2Fh, 01h, 50h, 0E8h, 86h, 3Ah, 0E2h, 0FFh, 55h, 89h, 03h, 56h, 8Dh, 44h, 24h, 30h
    db 50h, 8Bh, 0CFh, 0E8h, 0D1h, 0D2h, 0E4h, 0FFh, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h
    db 4Ch, 04h, 0E8h, 59h, 50h, 69h, 00h, 8Dh, 4Ch, 24h, 28h, 0C6h, 44h, 24h, 48h, 01h
    db 0E8h, 0FBh, 4Ch, 69h, 00h, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h
    db 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 0Ch, 0F7h, 2Eh, 01h, 50h, 0E8h, 86h
    db 0C1h, 0E2h, 0FFh, 55h, 56h, 8Dh, 4Ch, 24h, 34h, 51h, 8Bh, 0CFh, 89h, 83h, 0F0h, 01h
    db 00h, 00h, 0E8h, 0C2h, 0CFh, 0E3h, 0FFh, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 4Ch
    db 05h, 0E8h, 0Ah, 50h, 69h, 00h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 48h, 01h, 0E8h
    db 0ACh, 4Ch, 69h, 00h, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh
    db 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 4Ch, 14h, 2Fh, 01h, 50h, 0E8h, 0ECh, 39h
    db 0E2h, 0FFh, 89h, 83h, 20h, 02h, 00h, 00h, 45h, 83h, 0C3h, 04h, 83h, 0FDh, 03h, 0Fh
    db 8Ch, 0BEh, 0FEh, 0FFh, 0FFh, 56h, 8Dh, 54h, 24h, 34h, 52h, 8Bh, 0CFh, 0E8h, 17h, 60h
    db 0E4h, 0FFh, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 4Ch, 06h, 0E8h, 0AFh, 4Fh, 69h
    db 00h, 8Dh, 4Ch, 24h, 30h, 0C6h, 44h, 24h, 48h, 01h, 0E8h, 51h, 4Ch, 69h, 00h, 51h
    db 8Dh, 44h, 24h, 14h, 89h, 64h, 24h, 40h, 8Bh, 0CCh, 50h, 0E8h, 60h, 4Eh, 69h, 00h
    db 8Bh, 6Ch, 24h, 18h, 81h, 0C5h, 0E0h, 0FDh, 0FFh, 0FFh, 8Bh, 0CDh, 0E8h, 55h, 25h, 0E3h
    db 0FFh, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 41h, 74h, 50h, 8Bh, 0CDh, 0E8h, 4Ah, 6Dh, 0E2h, 0FFh
    db 56h, 8Dh, 54h, 24h, 38h, 52h, 8Bh, 0CFh, 0E8h, 71h, 47h, 0E3h, 0FFh, 50h, 8Dh, 4Ch
    db 24h, 14h, 0C6h, 44h, 24h, 4Ch, 07h, 0E8h, 54h, 4Fh, 69h, 00h, 8Dh, 4Ch, 24h, 34h
    db 0C6h, 44h, 24h, 48h, 01h, 0E8h, 0F6h, 4Bh, 69h, 00h, 51h, 8Dh, 44h, 24h, 14h, 89h
    db 64h, 24h, 40h, 8Bh, 0CCh, 50h, 0E8h, 05h, 4Eh, 69h, 00h, 8Bh, 6Ch, 24h, 18h, 8Bh
    db 0CDh, 0E8h, 00h, 25h, 0E3h, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 41h, 74h, 50h, 8Bh, 0CDh
    db 0E8h, 0F5h, 6Ch, 0E2h, 0FFh, 46h, 83h, 0C5h, 70h, 83h, 0FEh, 04h, 89h, 6Ch, 24h, 14h
    db 0Fh, 8Ch, 0FBh, 0FDh, 0FFh, 0FFh, 8Bh, 54h, 24h, 38h, 8Dh, 4Ch, 24h, 10h, 0C6h, 82h
    db 7Ch, 04h, 00h, 00h, 01h, 0C6h, 44h, 24h, 48h, 00h, 0E8h, 0A1h, 4Bh, 69h, 00h, 8Dh
    db 4Ch, 24h, 18h, 0C7h, 44h, 24h, 48h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 90h, 4Bh, 69h, 00h
    db 8Bh, 4Ch, 24h, 40h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h
    db 0C4h, 3Ch, 0C3h
?resolveFX@BridgeBehavior@@IAEXXZ ENDP
_TEXT ENDS
END
