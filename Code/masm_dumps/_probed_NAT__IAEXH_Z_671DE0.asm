.386
.model flat

; ?probed@NAT@@IAEXH@Z
; Retail @ 0x00A71DE0 size 155
_TEXT SEGMENT
public ?probed@NAT@@IAEXH@Z
?probed@NAT@@IAEXH@Z PROC
    db 56h,8Bh,0F1h,8Bh,46h,10h,8Bh,4Eh
    db 08h,8Bh,54h,0C6h,68h,8Bh,14h,91h
    db 85h,0D2h,75h,0Eh,6Ah,06h,50h,8Bh
    db 0CEh,0E8h,0D3h,0CDh,9Bh,0FFh,5Eh,0C2h
    db 04h,00h,53h,8Ah,5Eh,3Ah,84h,0DBh
    db 75h,6Ch,0C6h,46h,3Ah,01h,0F6h,42h
    db 38h,08h,74h,62h,8Bh,56h,14h,8Bh
    db 54h,0D6h,68h,57h,8Bh,3Ch,91h,85h
    db 0FFh,75h,10h,6Ah,06h,50h,8Bh,0CEh
    db 0E8h,0A4h,0CDh,9Bh,0FFh,5Fh,5Bh,5Eh
    db 0C2h,04h,00h,83h,7Ch,86h,44h,02h
    db 74h,3Bh,66h,8Bh,4Fh,34h,66h,85h
    db 0C9h,75h,10h,6Ah,03h,50h,8Bh,0CEh
    db 0E8h,84h,0CDh,9Bh,0FFh,5Fh,5Bh,5Eh
    db 0C2h,04h,00h,50h,8Bh,47h,30h,51h
    db 50h,8Bh,0CEh,0E8h,79h,3Eh,9Bh,0FFh
    db 57h,8Bh,0CEh,0E8h,0B4h,6Eh,9Bh,0FFh
    db 8Bh,4Eh,10h,6Ah,04h,51h,8Bh,0CEh
    db 0E8h,5Ch,0CDh,9Bh,0FFh,5Fh,5Bh,5Eh
    db 0C2h,04h,00h
?probed@NAT@@IAEXH@Z ENDP
_TEXT ENDS
END
