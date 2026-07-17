.386
.model flat

; ?hideInfoGadgets@@YAX_N@Z
; Exact 61 retail bytes @ 0x00505730; BFME stores stats controls on the menu object.
_TEXT SEGMENT
public ?hideInfoGadgets@@YAX_N@Z
?hideInfoGadgets@@YAX_N@Z PROC
    db 056h,057h,08Bh,07Ch,024h,00Ch,08Bh,0F1h
    db 08Bh,08Eh,08Ch,002h,000h,000h,057h,0E8h
    db 0E6h,027h,0B2h,0FFh,08Bh,08Eh,094h,002h
    db 000h,000h,057h,0E8h,0DAh,027h,0B2h,0FFh
    db 08Bh,08Eh,0A4h,002h,000h,000h,057h,0E8h
    db 0CEh,027h,0B2h,0FFh,08Bh,08Eh,09Ch,002h
    db 000h,000h,057h,0E8h,0C2h,027h,0B2h,0FFh
    db 05Fh,05Eh,0C2h,004h,000h
?hideInfoGadgets@@YAX_N@Z ENDP
_TEXT ENDS
END
