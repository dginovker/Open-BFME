.386
.model flat

; ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
; Exact 186 retail bytes @ 0x002F24F0; drift 0x007A85DF was INSIDE FUN_00ba8400 (2440B), not this body.
; BFME: getWaypointByName (TerrainLogic+0x7c) + TacticalView name-list fallback + View+0x60 moveCameraTo.
_TEXT SEGMENT
public ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z PROC
    db 83h,0ECh,10h,53h,56h,57h,8Bh,7Ch,24h,20h,51h,89h,64h,24h,10h,8Bh
    db 0CCh,57h,0E8h,59h,56h,59h,00h,8Bh,0Dh,0CCh,0F4h,2Eh,01h,8Bh,01h,0FFh
    db 50h,7Ch,8Bh,0Dh,00h,16h,2Fh,01h,57h,8Bh,0F0h,0E8h,23h,45h,0D4h,0FFh
    db 85h,0F6h,8Bh,0F8h,75h,06h,85h,0FFh,74h,77h,0EBh,1Bh,83h,0C6h,0Ch,85h
    db 0FFh,8Bh,0Eh,8Bh,56h,04h,8Bh,46h,08h,89h,4Ch,24h,10h,89h,54h,24h
    db 14h,89h,44h,24h,18h,74h,17h,8Dh,4Fh,08h,8Bh,11h,8Bh,41h,04h,8Bh
    db 49h,08h,89h,54h,24h,10h,89h,44h,24h,14h,89h,4Ch,24h,18h,0D9h,44h
    db 24h,30h,8Bh,35h,00h,16h,2Fh,01h,0D8h,0Dh,68h,5Ch,07h,01h,8Bh,1Eh
    db 83h,0ECh,08h,0D9h,5Ch,24h,04h,0D9h,44h,24h,34h,0D8h,0Dh,68h,5Ch,07h
    db 01h,0D9h,1Ch,24h,6Ah,01h,0D9h,44h,24h,30h,0D8h,0Dh,68h,5Ch,07h,01h
    db 0E8h,0A3h,48h,70h,00h,50h,57h,8Dh,54h,24h,24h,52h,8Bh,0CEh,0FFh,53h
    db 60h,5Fh,5Eh,5Bh,83h,0C4h,10h,0C2h,14h,00h
?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z ENDP
_TEXT ENDS
END
