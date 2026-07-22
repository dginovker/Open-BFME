.386
.model flat

; ?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z
; Exact 282 retail bytes @ 0x002F3E90
; Identity: getTeamNamed (TheScriptEngine vtbl+0x44), hasAnyObjects,
; DLINK team-member walk, flash count via 0x88888889 /15, Drawable+0x160/+0x164
; (same fields as doNamedFlash @ 0x2EE7C0). Drift 0x933119 was mid-fn x87.
_TEXT SEGMENT
public ?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z
?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z PROC
    db 83h,0ECh,1Ch,8Bh,44h,24h,20h,53h
    db 55h,56h,57h,6Ah,00h,51h,89h,64h
    db 24h,18h,8Bh,0CCh,50h,0E8h,0B6h,3Ch
    db 59h,00h,8Bh,0Dh,6Ch,07h,2Fh,01h
    db 8Bh,11h,0FFh,52h,44h,8Bh,0F0h,85h
    db 0F6h,0Fh,84h,0E1h,00h,00h,00h,6Ah
    db 00h,8Bh,0CEh,0E8h,0C3h,08h,0D2h,0FFh
    db 84h,0C0h,0Fh,84h,0D0h,00h,00h,00h
    db 8Bh,76h,0Ch,33h,0D2h,85h,0F6h,0B8h
    db 40h,11h,40h,00h,0B9h,9Ch,0FFh,0FFh
    db 0FFh,89h,44h,24h,1Ch,89h,4Ch,24h
    db 20h,89h,54h,24h,24h,0Fh,84h,0ADh
    db 00h,00h,00h,85h,0F6h,8Bh,0DEh,0Fh
    db 84h,0A3h,00h,00h,00h,8Bh,46h,68h
    db 8Bh,4Ch,24h,24h,8Bh,14h,08h,03h
    db 54h,24h,20h,8Dh,4Ch,32h,68h,0FFh
    db 54h,24h,1Ch,8Bh,0F0h,8Bh,03h,8Bh
    db 0CBh,0FFh,50h,28h,8Bh,0E8h,85h,0EDh
    db 74h,7Eh,8Bh,4Ch,24h,34h,8Dh,0Ch
    db 89h,0B8h,89h,88h,88h,88h,0F7h,0E9h
    db 8Bh,44h,24h,38h,03h,0D1h,0C1h,0FAh
    db 03h,8Bh,0FAh,0C1h,0EFh,1Fh,03h,0FAh
    db 85h,0C0h,75h,0Bh,8Bh,0CBh,0E8h,55h
    db 5Dh,0D1h,0FFh,8Bh,0D8h,0EBh,3Dh,0D9h
    db 00h,0DCh,0Dh,48h,0F9h,07h,01h,0E8h
    db 0DCh,2Eh,70h,00h,8Bh,4Ch,24h,38h
    db 0D9h,41h,04h,8Bh,0D8h,0DCh,0Dh,48h
    db 0F9h,07h,01h,0C1h,0E3h,08h,0E8h,0C5h
    db 2Eh,70h,00h,8Bh,54h,24h,38h,0D9h
    db 42h,08h,0Bh,0D8h,0DCh,0Dh,48h,0F9h
    db 07h,01h,0C1h,0E3h,08h,0E8h,0AEh,2Eh
    db 70h,00h,0Bh,0D8h,85h,0F6h,89h,9Dh
    db 64h,01h,00h,00h,89h,0BDh,60h,01h
    db 00h,00h,0Fh,85h,53h,0FFh,0FFh,0FFh
    db 5Fh,5Eh,5Dh,5Bh,83h,0C4h,1Ch,0C2h
    db 0Ch,00h
?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z ENDP
_TEXT ENDS
END
