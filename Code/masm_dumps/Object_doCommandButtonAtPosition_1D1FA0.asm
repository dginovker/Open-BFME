.386
.model flat

; ?doCommandButtonAtPosition@Object@@QAEXPBVCommandButton@@PBUCoord3D@@W4CommandSourceType@@@Z
; Exact 417B retail @ RVA 0x001D1FA0; full SEH (mov eax,fs:[0]) + isDisabled@+0x1a4;
; cmdType switch (cmd-9..); Coord3D pos + optional bool; SPECIAL_POWER path.
; Queue 0x77B0CA was INSIDE ctor 0x77B090 - true body via isDisabled/CommandButton + ILT xrefs.
_TEXT SEGMENT
public ?doCommandButtonAtPosition@Object@@QAEXPBVCommandButton@@PBUCoord3D@@W4CommandSourceType@@@Z
?doCommandButtonAtPosition@Object@@QAEXPBVCommandButton@@PBUCoord3D@@W4CommandSourceType@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,18h,95h,00h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,20h,57h,8Bh,0F9h,8Bh,87h,0A4h,01h,00h
    db 00h,85h,0C0h,0Fh,85h,66h,01h,00h,00h,53h,8Ah,5Ch,24h,44h,84h,0DBh
    db 55h,8Bh,6Ch,24h,40h,56h,8Bh,74h,24h,40h,0Fh,84h,0A0h,00h,00h,00h
    db 8Bh,07h,0FFh,50h,28h,85h,0C0h,0Fh,84h,93h,00h,00h,00h,85h,0F6h,0Fh
    db 84h,8Bh,00h,00h,00h,8Bh,4Eh,18h,0C1h,0E9h,03h,0F6h,0D1h,0F6h,0C1h,01h
    db 74h,7Eh,8Dh,4Ch,24h,10h,0E8h,59h,0D1h,0E3h,0FFh,85h,0EDh,89h,74h,24h
    db 2Ch,74h,16h,8Bh,0D5h,8Bh,02h,8Bh,4Ah,04h,8Bh,52h,08h,89h,44h,24h
    db 20h,89h,4Ch,24h,24h,89h,54h,24h,28h,8Dh,44h,24h,4Ch,50h,8Dh,4Ch
    db 24h,50h,0E8h,9Bh,43h,0E5h,0FFh,8Bh,17h,8Bh,0CFh,0C7h,44h,24h,38h,00h
    db 00h,00h,00h,0FFh,52h,28h,89h,44h,24h,44h,8Dh,44h,24h,44h,50h,8Dh
    db 4Ch,24h,50h,0E8h,0F9h,80h,0E7h,0FFh,8Dh,4Ch,24h,10h,51h,8Dh,54h,24h
    db 50h,68h,0E4h,07h,00h,00h,52h,0E8h,5Ch,76h,0E4h,0FFh,83h,0C4h,0Ch,8Dh
    db 4Ch,24h,4Ch,0C7h,44h,24h,38h,0FFh,0FFh,0FFh,0FFh,0E8h,0E3h,0E7h,0E6h,0FFh
    db 85h,0F6h,8Bh,87h,04h,02h,00h,00h,0Fh,84h,9Eh,00h,00h,00h,8Bh,4Eh
    db 10h,83h,0C1h,0F7h,83h,0F9h,1Bh,0Fh,87h,8Fh,00h,00h,00h,0Fh,0B6h,89h
    db 54h,21h,5Dh,00h,0FFh,24h,8Dh,44h,21h,5Dh,00h,8Bh,46h,34h,85h,0C0h
    db 74h,7Ah,8Bh,76h,18h,81h,0CEh,00h,00h,04h,00h,84h,0DBh,74h,06h,81h
    db 0CEh,00h,00h,00h,20h,83h,7Ch,24h,48h,01h,0Fh,94h,0C2h,8Bh,0CFh,52h
    db 56h,55h,50h,0E8h,0EAh,53h,0E4h,0FFh,5Eh,5Dh,5Bh,5Fh,8Bh,4Ch,24h,20h
    db 64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,2Ch,0C2h,10h,00h,85h,0C0h,74h
    db 3Bh,8Bh,4Ch,24h,48h,8Bh,96h,80h,00h,00h,00h,51h,52h,55h,8Dh,48h
    db 20h,0E8h,0FDh,0D9h,0E5h,0FFh,5Eh,5Dh,5Bh,5Fh,8Bh,4Ch,24h,20h,64h,89h
    db 0Dh,00h,00h,00h,00h,83h,0C4h,2Ch,0C2h,10h,00h,85h,0C0h,74h,0Dh,8Bh
    db 4Ch,24h,48h,51h,8Dh,48h,20h,0E8h,44h,2Ch,0E5h,0FFh,5Eh,5Dh,5Bh,8Bh
    db 4Ch,24h,24h,5Fh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,2Ch,0C2h,10h
    db 00h
?doCommandButtonAtPosition@Object@@QAEXPBVCommandButton@@PBUCoord3D@@W4CommandSourceType@@@Z ENDP
_TEXT ENDS
END
