.386
.model flat

; ?readUntilSemicolon@@YAXPAVFile@@PADH@Z
; Retail @ 0x004843E0 size 110
_TEXT SEGMENT
public ?readUntilSemicolon@@YAXPAVFile@@PADH@Z
?readUntilSemicolon@@YAXPAVFile@@PADH@Z PROC
    db 8Bh,44h,24h,0Ch,53h,55h,8Bh,6Ch
    db 24h,0Ch,56h,57h,33h,0FFh,85h,0C0h
    db 0B3h,01h,7Eh,3Bh,8Bh,44h,24h,18h
    db 8Bh,55h,00h,8Dh,34h,07h,6Ah,01h
    db 56h,8Bh,0CDh,0FFh,52h,0Ch,0Fh,0BEh
    db 06h,50h,0FFh,15h,20h,94h,35h,01h
    db 83h,0C4h,04h,85h,0C0h,74h,09h,84h
    db 0DBh,75h,0Eh,0C6h,06h,20h,0EBh,08h
    db 8Ah,06h,32h,0DBh,3Ch,3Bh,74h,19h
    db 47h,3Bh,7Ch,24h,1Ch,7Ch,0C5h,8Bh
    db 54h,24h,18h,8Bh,44h,24h,1Ch,5Fh
    db 5Eh,5Dh,0C6h,44h,02h,0FFh,00h,5Bh
    db 0C3h,8Bh,4Ch,24h,18h,0C6h,04h,0Fh
    db 00h,5Fh,5Eh,5Dh,5Bh,0C3h
?readUntilSemicolon@@YAXPAVFile@@PADH@Z ENDP
_TEXT ENDS
END
