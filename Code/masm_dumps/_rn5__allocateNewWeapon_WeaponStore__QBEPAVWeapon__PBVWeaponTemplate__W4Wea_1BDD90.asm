.386
.model flat
; ?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z
; Exact 100B @ 0x1BDD90; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z
?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z PROC
    db 6Ah, 0FFh, 68h, 0BBh, 8Ch, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 5Ch, 0E8h, 83h, 41h, 6Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 22h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 33h, 4Dh, 0E4h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h
    db 00h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 08h, 00h
?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z ENDP
_TEXT ENDS
END
