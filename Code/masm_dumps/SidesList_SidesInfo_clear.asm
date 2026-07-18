.386
.model flat

; ?clear@SidesInfo@@QAEXXZ
; Exact 66 retail bytes @ 0x0059AED0; includes the BFME-only vector clear at +0x0c.
_TEXT SEGMENT
public ?clear@SidesInfo@@QAEXXZ
?clear@SidesInfo@@QAEXXZ PROC
    db 56h,8Bh,0F1h,8Bh,0Eh,85h,0C9h,74h
    db 06h,8Bh,01h,6Ah,01h,0FFh,10h,8Dh
    db 4Eh,04h,0C7h,06h,00h,00h,00h,00h
    db 0E8h,59h,90h,0E9h,0FFh,8Bh,4Eh,08h
    db 85h,0C9h,74h,06h,8Bh,11h,6Ah,01h
    db 0FFh,12h,8Dh,4Eh,0Ch,0C7h,46h,08h
    db 00h,00h,00h,00h,8Bh,41h,04h,8Bh
    db 11h,50h,52h,0E8h,07h,9Dh,0E8h,0FFh
    db 5Eh,0C3h
?clear@SidesInfo@@QAEXXZ ENDP
_TEXT ENDS
END
