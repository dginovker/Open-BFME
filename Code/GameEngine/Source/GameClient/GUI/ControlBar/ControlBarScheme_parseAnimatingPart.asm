.386
.model flat

; ?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
; Exact 219B @ 0x004AEA00; FieldParse Name/Animation/Duration/FinalPos/ImagePart@0xcfd0a8
; Sibling parseImagePart @ 0x4AE920 (MASM); queue 0xB026D6 was pad/epilogue junk.
; Retail inlines addAnimation+addImage list inserts; C++ cannot emit that shape.
_TEXT SEGMENT
public ?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z PROC
    db 6Ah,0FFh,68h,9Bh,88h,02h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,53h,56h,57h,6Ah,24h,0E8h,10h,35h,3Dh,00h
    db 83h,0C4h,04h,89h,44h,24h,0Ch,85h,0C0h,0C7h,44h,24h,18h,00h,00h,00h
    db 00h,74h,0Bh,8Bh,0C8h,0E8h,68h,71h,0B8h,0FFh,8Bh,0F8h,0EBh,02h,33h,0FFh
    db 8Bh,4Ch,24h,20h,68h,0A8h,0D0h,0Fh,01h,57h,0C7h,44h,24h,20h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,49h,36h,3Ah,00h,85h,0FFh,8Bh,5Ch,24h,24h,74h,26h,8Bh
    db 0B3h,70h,01h,00h,00h,6Ah,0Ch,0E8h,0D4h,0FAh,37h,00h,8Dh,48h,08h,83h
    db 0C4h,04h,85h,0C9h,74h,02h,89h,39h,8Bh,4Eh,04h,89h,30h,89h,48h,04h
    db 89h,01h,89h,46h,04h,8Bh,77h,08h,85h,0F6h,74h,3Dh,8Bh,46h,18h,85h
    db 0C0h,7Ch,05h,83h,0F8h,06h,7Ch,07h,0C7h,46h,18h,00h,00h,00h,00h,8Bh
    db 46h,18h,8Bh,0BCh,83h,58h,01h,00h,00h,6Ah,0Ch,0E8h,90h,0FAh,37h,00h
    db 8Dh,48h,08h,83h,0C4h,04h,85h,0C9h,74h,02h,89h,31h,8Bh,4Fh,04h,89h
    db 38h,89h,48h,04h,89h,01h,89h,47h,04h,8Bh,4Ch,24h,10h,5Fh,5Eh,64h
    db 89h,0Dh,00h,00h,00h,00h,5Bh,83h,0C4h,10h,0C3h
?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
