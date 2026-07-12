.386
.model flat

; __CxxThrowException@8
; Retail @ 0x00850600 size 103
_TEXT SEGMENT
public __CxxThrowException@8
__CxxThrowException@8 PROC
    db 8Bh,44h,24h,08h,53h,8Bh,5Ch,24h
    db 08h,89h,43h,04h,8Bh,44h,24h,10h
    db 85h,0C0h,0C7h,03h,00h,00h,00h,00h
    db 74h,49h,55h,56h,57h,8Dh,4Ch,24h
    db 20h,51h,50h,68h,0FFh,07h,00h,00h
    db 68h,50h,0C6h,30h,01h,0FFh,15h,60h
    db 93h,35h,01h,8Bh,0E8h,8Dh,55h,01h
    db 52h,0E8h,32h,19h,03h,00h,89h,03h
    db 8Bh,0CDh,8Bh,0F8h,8Bh,0C1h,0C1h,0E9h
    db 02h,0BEh,50h,0C6h,30h,01h,0F3h,0A5h
    db 83h,0C4h,14h,8Bh,0C8h,83h,0E1h,03h
    db 0F3h,0A4h,8Bh,0Bh,5Fh,5Eh,0C6h,04h
    db 29h,00h,5Dh,8Bh,0C3h,5Bh,0C3h
__CxxThrowException@8 ENDP
_TEXT ENDS
END
