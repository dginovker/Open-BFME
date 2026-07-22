.386
.model flat
; ?initiateIntentToDoSpecialPower@SpecialPowerModule@@IAE_NPBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z
; Exact 488B @ 0x0026A2E0; queue 0x0076E966 was INSIDE unrelated fn (mid lea [esi+0x220])
; Identity: 5 ILT(0x361AB) callers = base doSpecialPower* family @0x26A55x/0x26A6xx;
; ret 0x10; SPU behavior-module loop + vcall initiateIntent; BFME-expanded vs ZH 165B
_TEXT SEGMENT
public ?initiateIntentToDoSpecialPower@SpecialPowerModule@@IAE_NPBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z
?initiateIntentToDoSpecialPower@SpecialPowerModule@@IAE_NPBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 68h, 0FFh, 00h, 01h, 50h, 8Bh, 44h
    db 24h, 10h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 85h, 0C0h, 53h, 55h
    db 56h, 57h, 8Bh, 0F9h, 74h, 06h, 8Bh, 40h, 74h, 89h, 47h, 28h, 8Bh, 47h, 04h, 8Bh
    db 48h, 08h, 89h, 44h, 24h, 10h, 8Bh, 41h, 04h, 85h, 0C0h, 74h, 0Eh, 8Bh, 48h, 04h
    db 85h, 0C9h, 74h, 05h, 0E8h, 38h, 0E9h, 0DDh, 0FFh, 8Bh, 0C8h, 8Bh, 41h, 14h, 83h, 0F8h
    db 34h, 74h, 53h, 83h, 0F8h, 6Eh, 74h, 4Ah, 83h, 0F8h, 73h, 75h, 5Eh, 8Bh, 77h, 08h
    db 8Bh, 0AEh, 04h, 02h, 00h, 00h, 85h, 0EDh, 74h, 51h, 8Bh, 0CEh, 0E8h, 0D3h, 64h, 0DBh
    db 0FFh, 8Bh, 88h, 28h, 02h, 00h, 00h, 85h, 0C9h, 74h, 40h, 8Dh, 44h, 24h, 14h, 50h
    db 56h, 0E8h, 25h, 08h, 0DBh, 0FFh, 84h, 0C0h, 74h, 31h, 6Ah, 02h, 8Dh, 4Ch, 24h, 18h
    db 51h, 8Dh, 4Dh, 20h, 0E8h, 0FBh, 83h, 0DAh, 0FFh, 0C6h, 85h, 3Ah, 03h, 00h, 00h, 00h
    db 0EBh, 19h, 6Ah, 34h, 0EBh, 02h, 6Ah, 6Eh, 8Bh, 4Fh, 08h, 0E8h, 6Ch, 11h, 0DEh, 0FFh
    db 85h, 0C0h, 74h, 07h, 8Bh, 0C8h, 0E8h, 07h, 1Ah, 0DAh, 0FFh, 8Bh, 47h, 08h, 8Bh, 0A8h
    db 0F0h, 01h, 00h, 00h, 8Bh, 45h, 00h, 32h, 0DBh, 85h, 0C0h, 74h, 53h, 8Dh, 49h, 00h
    db 8Bh, 50h, 0Ch, 8Dh, 48h, 0Ch, 0FFh, 52h, 60h, 8Bh, 0F0h, 85h, 0F6h, 74h, 12h, 8Bh
    db 47h, 04h, 8Bh, 40h, 08h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 1Ch, 84h, 0C0h, 75h
    db 0Ch, 8Bh, 45h, 04h, 83h, 0C5h, 04h, 85h, 0C0h, 75h, 0D5h, 0EBh, 23h, 8Bh, 4Ch, 24h
    db 3Ch, 8Bh, 47h, 04h, 8Bh, 40h, 08h, 8Bh, 16h, 51h, 8Bh, 4Ch, 24h, 3Ch, 51h, 8Bh
    db 4Ch, 24h, 3Ch, 51h, 8Bh, 4Ch, 24h, 3Ch, 51h, 50h, 8Bh, 0CEh, 0FFh, 12h, 0B3h, 01h
    db 8Bh, 47h, 04h, 8Ah, 88h, 09h, 02h, 00h, 00h, 84h, 0C9h, 74h, 17h, 8Bh, 47h, 08h
    db 8Bh, 80h, 04h, 02h, 00h, 00h, 85h, 0C0h, 74h, 0Ah, 6Ah, 02h, 8Dh, 48h, 20h, 0E8h
    db 4Ch, 0A9h, 0DBh, 0FFh, 84h, 0DBh, 0Fh, 84h, 87h, 00h, 00h, 00h, 8Bh, 47h, 04h, 8Bh
    db 40h, 08h, 8Dh, 4Ch, 24h, 3Ch, 51h, 8Bh, 0C8h, 0E8h, 6Ah, 67h, 0DBh, 0FFh, 8Bh, 44h
    db 24h, 3Ch, 85h, 0C0h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h, 00h, 74h, 19h, 66h, 83h
    db 78h, 04h, 00h, 74h, 12h, 8Bh, 0Dh, 98h, 4Bh, 2Fh, 01h, 6Ah, 00h, 8Dh, 54h, 24h
    db 40h, 52h, 0E8h, 0E4h, 99h, 0DDh, 0FFh, 0F7h, 44h, 24h, 38h, 00h, 00h, 04h, 00h, 74h
    db 04h, 0C6h, 47h, 24h, 01h, 8Bh, 7Fh, 08h, 85h, 0FFh, 74h, 26h, 8Bh, 44h, 24h, 10h
    db 8Bh, 0B0h, 0F0h, 01h, 00h, 00h, 85h, 0F6h, 74h, 18h, 8Bh, 0CEh, 0E8h, 0E6h, 7Ah, 0DAh
    db 0FFh, 84h, 0C0h, 75h, 0Dh, 8Bh, 4Ch, 24h, 30h, 51h, 57h, 8Bh, 0CEh, 0E8h, 18h, 87h
    db 0DBh, 0FFh, 8Dh, 4Ch, 24h, 3Ch, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 8Dh
    db 0D4h, 61h, 00h, 8Bh, 4Ch, 24h, 20h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 10h, 00h
?initiateIntentToDoSpecialPower@SpecialPowerModule@@IAE_NPBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z ENDP
_TEXT ENDS
END
