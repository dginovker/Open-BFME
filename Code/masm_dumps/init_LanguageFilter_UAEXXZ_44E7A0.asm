.386
.model flat

; ?init@LanguageFilter@@UAEXXZ
; Exact 310 retail bytes @ 0x0044E7A0; queue 0x0044E79E was 2x int3 pad before true start
; identity: langdata.dat 0x10F5D64, XOR 0x5555, map clear this+8, File convertToRAMFile vtbl+0x38, close +0x8
; C++ blocked: SEH prologue order (fs:0 before push -1), File vtable -1 slot, convertToRAMFile insert, UnicodeString layout
_TEXT SEGMENT
public ?init@LanguageFilter@@UAEXXZ
?init@LanguageFilter@@UAEXXZ PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,0EBh,39h,02h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,81h,0ECh,04h,01h,00h,00h,53h,56h,57h,8Bh,0F9h
    db 8Bh,47h,0Ch,8Dh,77h,08h,33h,0DBh,3Bh,0C3h,74h,1Fh,8Bh,06h,8Bh,48h
    db 04h,51h,8Bh,0CEh,0E8h,5Bh,0A3h,0BBh,0FFh,8Bh,06h,89h,40h,08h,8Bh,16h
    db 89h,5Ah,04h,8Bh,06h,89h,40h,0Ch,89h,5Eh,04h,8Bh,0Dh,48h,0CBh,34h
    db 01h,6Ah,41h,68h,64h,5Dh,0Fh,01h,0E8h,63h,0A0h,57h,00h,3Bh,0C3h,0Fh
    db 84h,0B9h,00h,00h,00h,8Bh,10h,55h,8Bh,0C8h,0FFh,52h,38h,8Bh,0E8h,3Bh
    db 0EBh,0Fh,84h,0A6h,00h,00h,00h,8Dh,44h,24h,14h,50h,55h,8Bh,0CFh,0C6h
    db 45h,0Dh,01h,0E8h,3Ch,77h,0BCh,0FFh,84h,0C0h,0Fh,84h,85h,00h,00h,00h
    db 8Dh,4Ch,24h,14h,51h,0FFh,15h,24h,95h,35h,01h,83h,0C4h,04h,3Bh,0C3h
    db 74h,5Eh,33h,0C9h,3Bh,0C3h,7Eh,14h,0EBh,06h,8Dh,9Bh,00h,00h,00h,00h
    db 66h,81h,74h,4Ch,14h,55h,55h,41h,3Bh,0C8h,7Ch,0F4h,8Dh,54h,24h,14h
    db 52h,8Dh,4Ch,24h,14h,0E8h,76h,0A5h,43h,00h,8Dh,44h,24h,10h,50h,8Bh
    db 0CFh,89h,9Ch,24h,20h,01h,00h,00h,0E8h,9Dh,13h,0BFh,0FFh,8Dh,4Ch,24h
    db 10h,51h,8Bh,0CEh,0E8h,0C5h,0BAh,0BBh,0FFh,8Dh,4Ch,24h,10h,0C6h,00h,01h
    db 0C7h,84h,24h,1Ch,01h,00h,00h,0FFh,0FFh,0FFh,0FFh,0E8h,30h,99h,43h,00h
    db 8Dh,54h,24h,14h,52h,55h,8Bh,0CFh,0E8h,0B7h,76h,0BCh,0FFh,84h,0C0h,0Fh
    db 85h,7Bh,0FFh,0FFh,0FFh,8Bh,45h,00h,8Bh,0CDh,0FFh,50h,08h,5Dh,8Bh,8Ch
    db 24h,10h,01h,00h,00h,5Fh,5Eh,5Bh,64h,89h,0Dh,00h,00h,00h,00h,81h
    db 0C4h,10h,01h,00h,00h,0C3h
?init@LanguageFilter@@UAEXXZ ENDP
_TEXT ENDS
END
