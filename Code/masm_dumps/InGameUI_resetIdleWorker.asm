.386
.model flat

; ?resetIdleWorker@InGameUI@@EAEXXZ
; Exact 121 retail bytes @ RVA 0x0043FAF0; idle-worker list reset (post-hideIdleWorkerLayout)
_TEXT SEGMENT
public ?resetIdleWorker@InGameUI@@EAEXXZ
?resetIdleWorker@InGameUI@@EAEXXZ PROC
    db 51h,53h,56h,8Bh,0F1h,8Bh,86h,9Ch,13h,00h,00h,85h,0C0h,57h,74h,20h
    db 51h,89h,64h,24h,10h,8Bh,0CCh,68h,54h,6Eh,33h,01h,0E8h,0EFh,88h,44h
    db 00h,8Bh,86h,9Ch,13h,00h,00h,50h,0E8h,0D4h,29h,0C0h,0FFh,83h,0C4h,08h
    db 0C7h,86h,0A0h,13h,00h,00h,0FFh,0FFh,0FFh,0FFh,8Dh,0BEh,1Ch,13h,00h,00h
    db 0BBh,20h,00h,00h,00h,8Bh,07h,8Bh,30h,3Bh,0F0h,74h,18h,8Dh,49h,00h
    db 8Bh,0C6h,8Bh,36h,6Ah,0Ch,50h,0E8h,0A4h,0EAh,3Eh,00h,8Bh,07h,83h,0C4h
    db 08h,3Bh,0F0h,75h,0EBh,8Bh,07h,89h,00h,8Bh,07h,83h,0C7h,04h,4Bh,89h
    db 40h,04h,75h,0D1h,5Fh,5Eh,5Bh,59h,0C3h
?resetIdleWorker@InGameUI@@EAEXXZ ENDP
_TEXT ENDS
END
