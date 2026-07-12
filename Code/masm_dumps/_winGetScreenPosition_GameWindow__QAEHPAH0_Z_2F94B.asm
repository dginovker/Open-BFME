.386
.model flat

; ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
; Retail @ 0x0042F94B size 5
_TEXT SEGMENT
public ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
?winGetScreenPosition@GameWindow@@QAEHPAH0@Z PROC
    db 0E9h,80h,88h,44h,00h
?winGetScreenPosition@GameWindow@@QAEHPAH0@Z ENDP
_TEXT ENDS
END
