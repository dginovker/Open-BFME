.386
.model flat

; ?setFramesPerSecondLimit@GameEngine@@UAEXH@Z
; Exact 10 retail bytes @ RVA 0x0006B6F0; release FPS-limit member assignment
_TEXT SEGMENT
public ?setFramesPerSecondLimit@GameEngine@@UAEXH@Z
?setFramesPerSecondLimit@GameEngine@@UAEXH@Z PROC
    db 08Bh,044h,024h,004h,089h,041h,008h,0C2h,004h,000h
?setFramesPerSecondLimit@GameEngine@@UAEXH@Z ENDP
_TEXT ENDS
END
