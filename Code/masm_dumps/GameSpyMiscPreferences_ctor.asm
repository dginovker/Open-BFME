.386
.model flat

; ??0GameSpyMiscPreferences@@QAE@XZ
; Exact 192 retail bytes @ 0x004AB910; constructs BFME GameSpy preferences and loads the local profile file.
_TEXT SEGMENT
public ??0GameSpyMiscPreferences@@QAE@XZ
??0GameSpyMiscPreferences@@QAE@XZ PROC
    db 06Ah,0FFh,068h,000h,077h,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,00Ch,053h,056h,08Bh,0F1h,033h,0DBh,06Ah,018h
    db 089h,074h,024h,010h,089h,05Eh,004h,0E8h,004h,02Ch,078h,000h,089h,046h,004h,089h
    db 05Eh,008h,088h,018h,08Bh,046h,004h,089h,058h,004h,08Bh,046h,004h,089h,040h,008h
    db 08Bh,046h,004h,089h,040h,00Ch,083h,0C4h,004h,089h,05Eh,010h,089h,05Ch,024h,01Ch
    db 0C7h,006h,048h,010h,008h,001h,089h,05Ch,024h,008h,08Bh,00Dh,094h,071h,02Fh,001h
    db 08Bh,011h,0C6h,044h,024h,01Ch,001h,0FFh,052h,070h,050h,051h,089h,064h,024h,018h
    db 08Bh,0CCh,068h,0E4h,010h,008h,001h,0E8h,034h,0D2h,07Dh,000h,08Dh,044h,024h,010h
    db 050h,0E8h,05Ah,0D6h,07Dh,000h,083h,0C4h,008h,08Dh,054h,024h,00Ch,089h,064h,024h
    db 014h,08Bh,0CCh,052h,0E8h,0B7h,0C1h,07Dh,000h,08Bh,0CEh,0E8h,058h,089h,0F6h,0FFh
    db 08Dh,04Ch,024h,008h,088h,05Ch,024h,01Ch,0E8h,083h,0BFh,07Dh,000h,08Bh,04Ch,024h
    db 014h,08Bh,0C6h,05Eh,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,018h,0C3h
??0GameSpyMiscPreferences@@QAE@XZ ENDP
_TEXT ENDS
END
