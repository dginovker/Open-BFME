.386
.model flat
; ?update@NAT@@
; Exact 517B @ 0x0086C0C0; Open-BFME4
_TEXT SEGMENT
public ?update@NAT@@
?update@NAT@@ PROC
    db 83h, 0ECh, 1Ch, 56h, 8Bh, 0F0h, 8Bh, 0Eh, 33h, 0C0h, 3Bh, 0C8h, 0Fh, 84h, 65h, 01h
    db 00h, 00h, 83h, 0F9h, 01h, 75h, 25h, 89h, 44h, 24h, 04h, 8Bh, 46h, 08h, 89h, 44h
    db 24h, 0Ch, 8Dh, 44h, 24h, 04h, 52h, 0C7h, 44h, 24h, 0Ch, 07h, 00h, 00h, 00h, 0E8h
    db 0FCh, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h, 02h, 0Fh
    db 84h, 98h, 00h, 00h, 00h, 83h, 0F9h, 03h, 74h, 65h, 83h, 0F9h, 04h, 75h, 31h, 8Bh
    db 4Eh, 08h, 89h, 44h, 24h, 04h, 89h, 44h, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h, 44h
    db 24h, 14h, 89h, 44h, 24h, 18h, 89h, 44h, 24h, 1Ch, 8Dh, 44h, 24h, 04h, 52h, 89h
    db 4Ch, 24h, 0Ch, 0E8h, 0B8h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h
    db 83h, 0F9h, 0Ah, 75h, 25h, 89h, 44h, 24h, 04h, 8Bh, 4Eh, 08h, 89h, 44h, 24h, 0Ch
    db 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 04h, 52h, 89h, 4Ch, 24h, 0Ch, 0E8h, 8Eh, 0FAh
    db 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h, 0Bh, 75h, 29h, 8Bh
    db 4Eh, 08h, 89h, 44h, 24h, 04h, 89h, 44h, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h, 44h
    db 24h, 14h, 8Dh, 44h, 24h, 04h, 52h, 89h, 4Ch, 24h, 0Ch, 0E8h, 60h, 0FAh, 0FFh, 0FFh
    db 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h, 05h, 75h, 21h, 8Bh, 4Eh, 08h
    db 89h, 44h, 24h, 04h, 89h, 44h, 24h, 0Ch, 8Dh, 44h, 24h, 04h, 52h, 89h, 4Ch, 24h
    db 0Ch, 0E8h, 3Ah, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h
    db 06h, 75h, 28h, 8Bh, 4Eh, 0Ch, 89h, 4Ch, 24h, 08h, 8Bh, 4Eh, 08h, 89h, 44h, 24h
    db 04h, 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 04h, 52h, 89h, 4Ch, 24h, 10h, 0E8h, 0Dh
    db 0FAh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h, 07h, 75h, 10h
    db 33h, 0C0h, 52h, 0E8h, 0F8h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h
    db 83h, 0F9h, 08h, 0Fh, 84h, 40h, 0FFh, 0FFh, 0FFh, 83h, 0F9h, 09h, 75h, 24h, 8Bh, 4Eh
    db 0Ch, 89h, 44h, 24h, 04h, 8Bh, 46h, 08h, 89h, 44h, 24h, 08h, 8Dh, 44h, 24h, 04h
    db 52h, 89h, 4Ch, 24h, 10h, 0E8h, 0C6h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h
    db 1Ch, 0C3h, 83h, 0F9h, 0Ch, 75h, 26h, 89h, 44h, 24h, 04h, 89h, 44h, 24h, 08h, 89h
    db 44h, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h, 44h, 24h, 14h, 8Dh, 44h, 24h, 04h, 52h
    db 0E8h, 9Bh, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch, 0C3h, 83h, 0F9h, 0Dh
    db 74h, 05h, 83h, 0F9h, 0Eh, 75h, 2Ah, 89h, 44h, 24h, 04h, 89h, 44h, 24h, 08h, 89h
    db 44h, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h, 44h, 24h, 14h, 89h, 44h, 24h, 18h, 8Dh
    db 44h, 24h, 04h, 52h, 0E8h, 67h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Eh, 83h, 0C4h, 1Ch
    db 0C3h, 83h, 0F9h, 0Fh, 75h, 0Ch, 8Bh, 0C6h, 0E8h, 0E3h, 0F8h, 0FFh, 0FFh, 5Eh, 83h, 0C4h
    db 1Ch, 0C3h, 83h, 0F9h, 10h, 75h, 19h, 89h, 44h, 24h, 04h, 8Dh, 44h, 24h, 04h, 52h
    db 0C7h, 44h, 24h, 0Ch, 0A0h, 15h, 13h, 01h, 0E8h, 33h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 04h
    db 5Eh, 83h, 0C4h, 1Ch, 0C3h
?update@NAT@@ ENDP
_TEXT ENDS
END
