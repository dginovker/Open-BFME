.386
.model flat

; ??0SidesInfo@@QAE@XZ
; Exact 34 retail bytes @ 0x005985B0; retail SidesInfo is 0x18 bytes with a vector at +0x0c.
_TEXT SEGMENT
public ??0SidesInfo@@QAE@XZ
??0SidesInfo@@QAE@XZ PROC
    db 56h,57h,8Bh,0F1h,33h,0FFh,57h,8Dh
    db 4Eh,04h,89h,3Eh,0E8h,0Ch,0A9h,0E6h
    db 0FFh,89h,7Eh,08h,89h,7Eh,0Ch,89h
    db 7Eh,10h,89h,7Eh,14h,5Fh,8Bh,0C6h
    db 5Eh,0C3h
??0SidesInfo@@QAE@XZ ENDP
_TEXT ENDS
END
