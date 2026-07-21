.386
.model flat

; ??0TeamFactory@@QAE@XZ
; Exact 130 retail bytes @ 0x000F2250
; Identity: sole code site writing TeamFactory vtables 0x1085F1C/0x1085F08;
; zeros m_uniqueTeamPrototypeID@+0x18 and m_uniqueTeamID@+0x1c (matches reset);
; map header alloc via __new_alloc::allocate(0x1c) @ 0x82E540.
; Queue RVA 0x009F272F was int3 pad before ControlBar ctor @ 0x009F2730.
_TEXT SEGMENT
public ??0TeamFactory@@QAE@XZ
??0TeamFactory@@QAE@XZ PROC
    db 06Ah,0FFh,068h,0D3h,0BAh,0FFh,000h,064h
    db 0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,053h,056h
    db 08Bh,0F1h,089h,074h,024h,008h,0E8h,0BDh
    db 0F7h,08Ah,000h,033h,0DBh,089h,05Ch,024h
    db 014h,0C7h,046h,008h,044h,037h,007h,001h
    db 0C7h,006h,01Ch,05Fh,008h,001h,0C7h,046h
    db 008h,008h,05Fh,008h,001h,06Ah,01Ch,0C6h
    db 044h,024h,018h,001h,089h,05Eh,00Ch,0E8h
    db 0A4h,0C2h,073h,000h,08Bh,04Ch,024h,010h
    db 089h,046h,00Ch,089h,05Eh,010h,088h,018h
    db 08Bh,046h,00Ch,089h,058h,004h,08Bh,046h
    db 00Ch,089h,040h,008h,08Bh,046h,00Ch,089h
    db 040h,00Ch,083h,0C4h,004h,089h,05Eh,018h
    db 089h,05Eh,01Ch,08Bh,0C6h,05Eh,05Bh,064h
    db 089h,00Dh,000h,000h,000h,000h,083h,0C4h
    db 010h,0C3h
??0TeamFactory@@QAE@XZ ENDP
_TEXT ENDS
END
