.386
.model flat

; ?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z
; Exact 212 retail bytes @ RVA 0x0043ADE0
; Identity: InGameUI vtable @ 0x10F5B38 slot 46 (+0xB8); neighbors setScrollAmount@+0xB0, getGUICommand@+0xBC
; Queue RVA 0x00613D76/206 was wrong body (maps path helper); true start 0x43ADE0
; Layout vs ZH: m_pendingGUICommand@+0x230 (ZH +0x143C), m_mouseMode@+0x824 (ZH +0x1940), m_mouseModeCursor@+0x828
_TEXT SEGMENT
public ?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z
?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z PROC
    db 57h,8Bh,0F9h,8Bh,0Dh,2Ch,0D6h,2Eh,01h,85h,0C9h,74h,0Eh,0E8h,0F9h,90h
    db 0C0h,0FFh,83h,0F8h,01h,0Fh,84h,0B5h,00h,00h,00h,56h,8Bh,74h,24h,0Ch
    db 85h,0F6h,0B8h,27h,02h,00h,00h,74h,2Ah,85h,46h,18h,75h,19h,5Eh,0C7h
    db 87h,30h,02h,00h,00h,00h,00h,00h,00h,0C7h,87h,24h,08h,00h,00h,00h
    db 00h,00h,00h,5Fh,0C2h,04h,00h,0C7h,87h,24h,08h,00h,00h,02h,00h,00h
    db 00h,0EBh,0Ah,0C7h,87h,24h,08h,00h,00h,00h,00h,00h,00h,85h,0F6h,89h
    db 0B7h,30h,02h,00h,00h,74h,3Bh,85h,46h,18h,74h,36h,8Bh,0CEh,0E8h,89h
    db 03h,0C1h,0FFh,84h,0C0h,75h,2Bh,8Bh,0Dh,5Ch,4Ch,2Fh,01h,85h,0C9h,74h
    db 07h,8Bh,01h,6Ah,02h,0FFh,50h,38h,8Bh,46h,6Ch,8Bh,4Eh,34h,8Bh,17h
    db 6Ah,01h,50h,8Bh,46h,38h,51h,50h,8Bh,0CFh,0FFh,92h,18h,01h,00h,00h
    db 0EBh,1Bh,8Bh,0Dh,5Ch,4Ch,2Fh,01h,85h,0C9h,74h,07h,8Bh,11h,6Ah,02h
    db 0FFh,52h,38h,8Bh,07h,8Bh,0CFh,0FFh,90h,1Ch,01h,00h,00h,8Bh,0Dh,5Ch
    db 4Ch,2Fh,01h,8Bh,91h,0A8h,4Dh,00h,00h,89h,97h,28h,08h,00h,00h,5Eh
    db 5Fh,0C2h,04h,00h
?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z ENDP
_TEXT ENDS
END
