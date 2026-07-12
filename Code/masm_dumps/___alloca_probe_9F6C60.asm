.386
.model flat

; __alloca_probe
; Retail @ 0x009F6C60 size 159
_TEXT SEGMENT
public __alloca_probe
__alloca_probe PROC
    db 3Dh,00h,10h,00h,00h,73h,0Eh,0F7h
    db 0D8h,03h,0C4h,83h,0C0h,04h,85h,00h
    db 94h,8Bh,00h,50h,0C3h,51h,8Dh,4Ch
    db 24h,08h,81h,0E9h,00h,10h,00h,00h
    db 2Dh,00h,10h,00h,00h,85h,01h,3Dh
    db 00h,10h,00h,00h,73h,0ECh,2Bh,0C8h
    db 8Bh,0C4h,85h,01h,8Bh,0E1h,8Bh,08h
    db 8Bh,40h,04h,50h,0C3h,0CCh,0FFh,25h
    db 20h,95h,35h,01h,8Bh,0C1h,0C7h,00h
    db 68h,58h,14h,01h,0C2h,04h,00h,53h
    db 8Ah,5Ch,24h,08h,0F6h,0C3h,02h,56h
    db 8Bh,0F1h,74h,24h,57h,68h,0D4h,7Eh
    db 0DFh,00h,8Dh,7Eh,0FCh,0FFh,37h,6Ah
    db 0Ch,56h,0E8h,0A7h,00h,00h,00h,0F6h
    db 0C3h,01h,74h,07h,57h,0E8h,0D6h,0B1h
    db 0E8h,0FFh,59h,8Bh,0C7h,5Fh,0EBh,15h
    db 8Bh,0CEh,0E8h,0EDh,11h,00h,00h,0F6h
    db 0C3h,01h,74h,07h,56h,0E8h,0BEh,0B1h
    db 0E8h,0FFh,59h,8Bh,0C6h,5Eh,5Bh,0C2h
    db 04h,00h,8Bh,0C1h,0C2h,04h,00h
__alloca_probe ENDP
_TEXT ENDS
END
