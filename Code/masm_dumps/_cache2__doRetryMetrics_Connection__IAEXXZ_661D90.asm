.386
.model flat
; ?doRetryMetrics@Connection@@IAEXXZ
; Exact 51B @ 0x661D90; Open-BFME4+Grok
_TEXT SEGMENT
public ?doRetryMetrics@Connection@@IAEXXZ
?doRetryMetrics@Connection@@IAEXXZ PROC
    db 56h, 8Bh, 0F1h, 0FFh, 15h, 44h, 95h, 35h, 01h, 8Bh, 96h, 54h, 03h, 00h, 00h, 8Bh
    db 0C8h, 2Bh, 0CAh, 81h, 0F9h, 10h, 27h, 00h, 00h, 76h, 16h, 89h, 86h, 54h, 03h, 00h
    db 00h, 0FFh, 05h, 0F8h, 76h, 2Fh, 01h, 0C7h, 86h, 50h, 03h, 00h, 00h, 00h, 00h, 00h
    db 00h, 5Eh, 0C3h
?doRetryMetrics@Connection@@IAEXXZ ENDP
_TEXT ENDS
END
