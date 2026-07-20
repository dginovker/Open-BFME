.386
.model flat
; ?countBuildings@Player@@QAEHXZ
; Exact 45B @ 0xCDDC0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?countBuildings@Player@@QAEHXZ
?countBuildings@Player@@QAEHXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 87h, 88h, 02h, 00h, 00h, 8Bh, 30h, 33h, 0DBh, 3Bh
    db 0F0h, 74h, 14h, 8Bh, 4Eh, 08h, 0E8h, 0F4h, 4Ch, 0F5h, 0FFh, 8Bh, 36h, 03h, 0D8h, 3Bh
    db 0B7h, 88h, 02h, 00h, 00h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 0C3h
?countBuildings@Player@@QAEHXZ ENDP
_TEXT ENDS
END
