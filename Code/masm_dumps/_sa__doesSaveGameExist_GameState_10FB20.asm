.386
.model flat

; ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z
; Exact 133B @ 0x0010FB20; caller-anchored from loadGame@0x1107B0 via ILT 0x30E81
_TEXT SEGMENT
public ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z
?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z PROC
    db 6Ah,0FFh,68h,0E0h,0DAh,0FFh,00h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,8Dh,44h,24h,14h,50h,8Dh,54h,24h,04h,52h
    db 0C7h,44h,24h,14h,00h,00h,00h,00h,0E8h,75h,0DDh,0F0h,0FFh,8Bh,04h,24h
    db 85h,0C0h,0C6h,44h,24h,0Ch,01h,74h,05h,83h,0C0h,08h,0EBh,05h,0B8h,8Bh
    db 38h,07h,01h,8Bh,0Dh,48h,0CBh,34h,01h,53h,50h,0E8h,30h,8Bh,8Bh,00h
    db 8Dh,4Ch,24h,04h,8Ah,0D8h,0C6h,44h,24h,10h,00h,0E8h,0C0h,7Dh,77h,00h
    db 8Dh,4Ch,24h,18h,0C7h,44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,0AFh,7Dh,77h
    db 00h,8Bh,4Ch,24h,08h,8Ah,0C3h,5Bh,64h,89h,0Dh,00h,00h,00h,00h,83h
    db 0C4h,10h,0C2h,04h,00h
?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z ENDP
_TEXT ENDS
END
