.386
.model flat

; ?setConnectionState@NAT@@IAEXHW4NATConnectionState@@@Z
; Retail @ 0x00A70DC0 size 116
_TEXT SEGMENT
public ?setConnectionState@NAT@@IAEXHW4NATConnectionState@@@Z
?setConnectionState@NAT@@IAEXHW4NATConnectionState@@@Z PROC
    db 8Bh,44h,24h,04h,56h,8Bh,0F1h,8Bh
    db 4Ch,24h,0Ch,89h,4Ch,86h,44h,8Bh
    db 4Eh,10h,3Bh,0C1h,75h,5Ah,8Bh,46h
    db 14h,3Bh,0C8h,74h,53h,83h,0F8h,0FFh
    db 74h,4Eh,53h,8Bh,5Ch,0C6h,68h,55h
    db 57h,33h,0EDh,33h,0FFh,8Dh,49h,00h
    db 8Bh,56h,08h,8Bh,0Ch,0BAh,85h,0C9h
    db 74h,17h,0E8h,0CCh,6Bh,9Bh,0FFh,84h
    db 0C0h,74h,0Eh,8Bh,46h,10h,3Bh,7Ch
    db 0C6h,68h,74h,05h,3Bh,0FBh,74h,07h
    db 45h,47h,83h,0FFh,08h,7Ch,0D9h,83h
    db 0FFh,08h,74h,11h,8Bh,44h,24h,18h
    db 8Bh,0Dh,3Ch,36h,2Fh,01h,8Bh,11h
    db 50h,55h,0FFh,52h,14h,5Fh,5Dh,5Bh
    db 5Eh,0C2h,08h,00h
?setConnectionState@NAT@@IAEXHW4NATConnectionState@@@Z ENDP
_TEXT ENDS
END
