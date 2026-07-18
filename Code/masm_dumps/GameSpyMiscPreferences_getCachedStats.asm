.386
.model flat

; ?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ
; Exact 113 retail bytes @ 0x004A9A00; reads CachedStats with the empty string default.
_TEXT SEGMENT
public ?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ
?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ PROC
    db 06Ah,0FFh,068h,0A8h,074h,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,008h,056h,057h,051h,033h,0FFh,08Bh,0F1h,089h
    db 07Ch,024h,00Ch,089h,064h,024h,00Ch,08Bh,0CCh,068h,050h,06Eh,033h,001h,0E8h,02Dh
    db 0E1h,07Dh,000h,051h,089h,064h,024h,014h,08Bh,0CCh,068h,074h,00Fh,008h,001h,089h
    db 07Ch,024h,024h,0E8h,078h,0F1h,07Dh,000h,08Bh,07Ch,024h,028h,08Bh,006h,057h,08Bh
    db 0CEh,0C7h,044h,024h,024h,0FFh,0FFh,0FFh,0FFh,0FFh,050h,018h,08Bh,04Ch,024h,010h
    db 08Bh,0C7h,05Fh,064h,089h,00Dh,000h,000h,000h,000h,05Eh,083h,0C4h,014h,0C2h,004h
    db 000h
?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ ENDP
_TEXT ENDS
END
