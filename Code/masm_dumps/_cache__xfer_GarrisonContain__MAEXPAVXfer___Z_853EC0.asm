.386
.model flat
; ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z
; Exact 72B @ 0x853EC0; Open-BFME4+Grok
_TEXT SEGMENT
public ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z
?xfer@GarrisonContain@@MAEXPAVXfer@@@Z PROC
    db 6Ah, 0FFh, 68h, 0FBh, 65h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 33h, 0C0h, 56h, 8Bh, 0F1h, 89h, 46h, 04h, 89h, 46h
    db 08h, 89h, 74h, 24h, 04h, 89h, 46h, 0Ch, 6Ah, 64h, 89h, 44h, 24h, 14h, 89h, 46h
    db 10h, 0E8h, 1Ah, 0F6h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?xfer@GarrisonContain@@MAEXPAVXfer@@@Z ENDP
_TEXT ENDS
END
