.386
.model flat

; ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z
; Exact 132 retail bytes @ RVA 0x0068E8D0
; Caller-proven via matched getSlotNum@LANGameInfo (call thunk 0x21ED6 -> body).
; Queue RVA 0x791BEF was INSIDE FUN_00b91730 (1380B), not this function.
_TEXT SEGMENT
public ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z
?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z PROC
    db 6Ah,0FFh,68h,58h,6Dh,04h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h,53h,33h,0DBh,89h,5Ch,24h,08h,83h
    db 79h,04h,05h,89h,5Ch,24h,14h,75h,21h,8Dh,44h,24h,08h,50h,0E8h,08h
    db 0B9h,9Ah,0FFh,50h,8Dh,4Ch,24h,20h,0BBh,01h,00h,00h,00h,0E8h,8Dh,77h
    db 98h,0FFh,85h,0C0h,88h,5Ch,24h,07h,74h,05h,0C6h,44h,24h,07h,00h,0F6h
    db 0C3h,01h,5Bh,74h,09h,8Dh,4Ch,24h,04h,0E8h,0A2h,98h,1Fh,00h,8Dh,4Ch
    db 24h,18h,0C7h,44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,91h,98h,1Fh,00h,8Bh
    db 4Ch,24h,08h,8Ah,44h,24h,03h,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h
    db 14h,0C2h,04h,00h
?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z ENDP
_TEXT ENDS
END
