.386
.model flat

; ?gotInternalAddress@NAT@@IAEXHI@Z
; Retail @ 0x00A70D70 size 59
_TEXT SEGMENT
public ?gotInternalAddress@NAT@@IAEXHI@Z
?gotInternalAddress@NAT@@IAEXHI@Z PROC
    db 8Bh,41h,08h,56h,8Bh,74h,24h,08h
    db 8Bh,54h,0F1h,68h,8Bh,14h,90h,85h
    db 0D2h,74h,24h,57h,8Bh,79h,10h,8Bh
    db 7Ch,0F9h,68h,8Bh,04h,0B8h,85h,0C0h
    db 74h,14h,3Bh,71h,14h,75h,0Fh,8Bh
    db 40h,30h,3Bh,42h,30h,75h,07h,8Bh
    db 4Ch,24h,10h,89h,4Ah,30h,5Fh,5Eh
    db 0C2h,08h,00h
?gotInternalAddress@NAT@@IAEXHI@Z ENDP
_TEXT ENDS
END
