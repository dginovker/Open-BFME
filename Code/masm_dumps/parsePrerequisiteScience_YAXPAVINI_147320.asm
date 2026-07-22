.386
.model flat

; ?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z
; Exact 220 retail bytes @ 0x00147320.
; Identity: ghidra ENTRY FUN_00547320; SEH+default-ctor+scanScience+vector push_back
; with element size 0x24 (BFME ProductionPrerequisite layout) + dtor.
; C++ blocked: ZH sizeof ProductionPrerequisite 0x18 vs retail 0x24 (extra
; vector at +0x18; addScience stays at +0x0c; stack sub esp 0x1c vs 0x28).
_TEXT SEGMENT
public ?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z
?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z PROC
    db 6Ah,0FFh,68h,0C9h,3Fh,00h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,28h,8Dh,4Ch,24h,04h,0E8h,9Fh,48h,0ECh
    db 0FFh,8Bh,4Ch,24h,38h,6Ah,00h,0C7h,44h,24h,34h,00h,00h,00h,00h,0E8h
    db 1Ch,96h,70h,00h,50h,0E8h,20h,0E0h,0ECh,0FFh,8Bh,4Ch,24h,18h,8Bh,54h
    db 24h,1Ch,83h,0C4h,04h,3Bh,0CAh,89h,04h,24h,74h,13h,85h,0C9h,74h,06h
    db 89h,01h,8Bh,4Ch,24h,14h,83h,0C1h,04h,89h,4Ch,24h,14h,0EBh,18h,6Ah
    db 01h,6Ah,01h,8Dh,44h,24h,44h,50h,8Dh,54h,24h,0Ch,52h,51h,8Dh,4Ch
    db 24h,24h,0E8h,0F1h,0C1h,0EDh,0FFh,56h,8Bh,74h,24h,40h,8Bh,4Eh,04h,3Bh
    db 4Eh,08h,74h,21h,89h,4Ch,24h,40h,89h,4Ch,24h,04h,85h,0C9h,0C6h,44h
    db 24h,34h,01h,74h,0Ah,8Dh,44h,24h,08h,50h,0E8h,47h,0A7h,0EEh,0FFh,83h
    db 46h,04h,24h,0EBh,16h,6Ah,01h,6Ah,01h,8Dh,54h,24h,48h,52h,8Dh,44h
    db 24h,14h,50h,51h,8Bh,0CEh,0E8h,0D5h,3Ah,0EDh,0FFh,8Dh,4Ch,24h,08h,0C7h
    db 44h,24h,34h,0FFh,0FFh,0FFh,0FFh,0E8h,12h,45h,0EFh,0FFh,8Bh,4Ch,24h,2Ch
    db 5Eh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,34h,0C3h
?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
