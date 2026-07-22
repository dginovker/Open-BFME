.386
.model flat

; ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
; Exact 273 retail bytes @ 0x002FE110
; Identity: executeAction TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE case
; after BuildingClass (ILT 0x41D44); 3x getString args, ret 0xC; body @ 0x2FE110
; via ILT 0x38483. Queue RVA 0x614F75 was INSIDE mislocated 0x614F8E Kindof/INI claim
; (same pad cluster as Named/NearestEnemy). BFME rewrite 273B vs ZH partition path 898B.
_TEXT SEGMENT
public ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z PROC
    db 83h,0ECh,1Ch,8Bh,44h,24h,20h,53h
    db 55h,56h,57h,6Ah,00h,51h,8Bh,0D9h
    db 89h,64h,24h,18h,8Bh,0CCh,50h,0E8h
    db 34h,9Ah,58h,00h,8Bh,0Dh,6Ch,07h
    db 2Fh,01h,8Bh,11h,0FFh,52h,44h,8Bh
    db 0F0h,85h,0F6h,0Fh,84h,0D6h,00h,00h
    db 00h,8Bh,44h,24h,34h,8Bh,0Dh,0F8h
    db 33h,2Fh,01h,50h,0E8h,4Ch,0D4h,0D3h
    db 0FFh,8Bh,0F8h,85h,0FFh,0Fh,84h,0BCh
    db 00h,00h,00h,8Bh,0Dh,6Ch,07h,2Fh
    db 01h,8Bh,6Ch,24h,38h,8Bh,11h,55h
    db 0FFh,52h,50h,85h,0C0h,74h,34h,6Ah
    db 00h,50h,8Dh,44h,24h,1Ch,50h,8Bh
    db 0CEh,0E8h,8Dh,0B7h,0D2h,0FFh,50h,8Bh
    db 0CBh,0E8h,53h,33h,0D4h,0FFh,85h,0C0h
    db 0Fh,84h,89h,00h,00h,00h,8Bh,40h
    db 04h,85h,0C0h,74h,1Ah,8Bh,48h,04h
    db 85h,0C9h,74h,13h,0E8h,1Ah,41h,0D0h
    db 0FFh,0EBh,0Ch,8Bh,0Dh,0D8h,0F1h,2Eh
    db 01h,55h,0E8h,0B1h,0A3h,0D2h,0FFh,85h
    db 0C0h,89h,44h,24h,30h,74h,60h,8Bh
    db 5Ch,24h,18h,8Bh,76h,0Ch,0B9h,9Ch
    db 0FFh,0FFh,0FFh,33h,0D2h,85h,0F6h,8Bh
    db 0E9h,8Bh,4Ch,24h,28h,0B8h,40h,11h
    db 40h,00h,89h,5Ch,24h,18h,8Bh,0D8h
    db 89h,54h,24h,24h,89h,4Ch,24h,28h
    db 74h,35h,56h,8Bh,0CFh,0E8h,5Ah,0B9h
    db 0D3h,0FFh,84h,0C0h,74h,0Dh,8Bh,54h
    db 24h,30h,52h,0E8h,0C8h,0F8h,0FFh,0FFh
    db 83h,0C4h,04h,85h,0F6h,74h,18h,8Bh
    db 46h,68h,8Bh,4Ch,24h,24h,8Bh,14h
    db 08h,03h,0D5h,8Dh,4Ch,32h,68h,0FFh
    db 0D3h,8Bh,0F0h,85h,0F6h,75h,0CBh,5Fh
    db 5Eh,5Dh,5Bh,83h,0C4h,1Ch,0C2h,0Ch
    db 00h
?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z ENDP
_TEXT ENDS
END
