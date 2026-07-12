.386
.model flat

; ?winGetStatus@GameWindow@@QAEIXZ
; Retail @ 0x00423DDA size 5
_TEXT SEGMENT
public ?winGetStatus@GameWindow@@QAEIXZ
?winGetStatus@GameWindow@@QAEIXZ PROC
    db 0E9h,0A1h,46h,45h,00h
?winGetStatus@GameWindow@@QAEIXZ ENDP
_TEXT ENDS
END
