.386
.model flat

; ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z
; Exact 334B @ 0x001D7BC0; true body via RadiusDecalUpdate string + AttackNugget
; vtbl slot (thunk 0xBD25 -> body). Queue 0x3992F7 was INSIDE another fn mid-insn.
; C++ blocked: Object AI@+0x204 (ZH +0x19c), AttackNugget fields template/radius/shots/slot
; @+4/+0x34/+0x38/+0x3c (RadiusDecalTemplate size), setWeaponLock on Object, ret 0x10.
_TEXT SEGMENT
public ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z
?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,09h,9Bh,00h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,81h,0ECh,9Ch,00h,00h,00h,53h,8Bh,9Ch,24h,0B0h
    db 00h,00h,00h,85h,0DBh,57h,8Bh,0F9h,0Fh,84h,07h,01h,00h,00h,8Bh,84h
    db 24h,0B8h,00h,00h,00h,85h,0C0h,0Fh,84h,0F8h,00h,00h,00h,8Bh,84h,24h
    db 0BCh,00h,00h,00h,85h,0C0h,0Fh,84h,0E9h,00h,00h,00h,56h,8Bh,0B3h,04h
    db 02h,00h,00h,85h,0F6h,74h,6Bh,8Bh,47h,3Ch,55h,6Ah,01h,50h,8Bh,0CBh
    db 0E8h,99h,72h,0E6h,0FFh,8Bh,6Fh,38h,6Ah,02h,6Ah,0Eh,8Dh,4Ch,24h,18h
    db 83h,0C6h,20h,0E8h,6Ch,92h,0E5h,0FFh,8Bh,8Ch,24h,0C4h,00h,00h,00h,8Bh
    db 11h,8Bh,41h,04h,8Bh,49h,08h,89h,44h,24h,1Ch,8Dh,44h,24h,10h,89h
    db 54h,24h,18h,8Bh,16h,89h,4Ch,24h,20h,50h,8Bh,0CEh,0C7h,84h,24h,0B8h
    db 00h,00h,00h,00h,00h,00h,00h,89h,6Ch,24h,48h,0FFh,12h,8Dh,4Ch,24h
    db 30h,0C7h,84h,24h,0B4h,00h,00h,00h,0FFh,0FFh,0FFh,0FFh,0E8h,0E7h,61h,0E3h
    db 0FFh,5Dh,0F6h,05h,18h,0F7h,2Eh,01h,01h,75h,3Ah,8Bh,0Dh,18h,0F7h,2Eh
    db 01h,0B8h,01h,00h,00h,00h,0Bh,0C8h,89h,0Dh,18h,0F7h,2Eh,01h,8Bh,0Dh
    db 00h,0D6h,2Eh,01h,68h,5Ch,06h,09h,01h,89h,84h,24h,0B4h,00h,00h,00h
    db 0E8h,22h,31h,0E6h,0FFh,0A3h,14h,0F7h,2Eh,01h,0C7h,84h,24h,0B0h,00h,00h
    db 00h,0FFh,0FFh,0FFh,0FFh,8Bh,0Dh,14h,0F7h,2Eh,01h,51h,8Bh,0CBh,0E8h,50h
    db 31h,0E5h,0FFh,8Bh,0F0h,85h,0F6h,74h,1Bh,8Bh,94h,24h,0C0h,00h,00h,00h
    db 8Bh,47h,34h,52h,50h,83h,0C7h,04h,57h,8Bh,0CEh,0E8h,0FAh,0E2h,0E4h,0FFh
    db 0C6h,46h,30h,01h,5Eh,8Bh,8Ch,24h,0A4h,00h,00h,00h,5Fh,5Bh,64h,89h
    db 0Dh,00h,00h,00h,00h,81h,0C4h,0A8h,00h,00h,00h,0C2h,10h,00h
?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z ENDP
_TEXT ENDS
END
