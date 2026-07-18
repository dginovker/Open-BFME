.386
.model flat

; ?setPlayingHandle@AudioEventRTS@@QAEXI@Z
; Exact 10 retail bytes @ RVA 0x000B2200; playing-handle member assignment
_TEXT SEGMENT
public ?setPlayingHandle@AudioEventRTS@@QAEXI@Z
?setPlayingHandle@AudioEventRTS@@QAEXI@Z PROC
    db 08Bh,044h,024h,004h,089h,041h,00Ch,0C2h,004h,000h
?setPlayingHandle@AudioEventRTS@@QAEXI@Z ENDP
_TEXT ENDS
END
