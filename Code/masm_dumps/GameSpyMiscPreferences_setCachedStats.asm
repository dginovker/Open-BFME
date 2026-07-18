.386
.model flat

; ?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z
; Exact 121 retail bytes @ 0x004A9A90; writes the CachedStats preference.
_TEXT SEGMENT
public ?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z
?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z PROC
    db 06Ah,0FFh,068h,0D0h,074h,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,008h,056h,08Bh,0F1h,051h,08Dh,044h,024h,020h
    db 089h,064h,024h,008h,08Bh,0CCh,050h,0C7h,044h,024h,01Ch,000h,000h,000h,000h,0E8h
    db 09Ch,0E0h,07Dh,000h,051h,089h,064h,024h,010h,08Bh,0CCh,068h,074h,00Fh,008h,001h
    db 0C6h,044h,024h,020h,001h,0E8h,0E6h,0F0h,07Dh,000h,08Bh,016h,08Bh,0CEh,0C6h,044h
    db 024h,01Ch,000h,0FFh,052h,01Ch,08Dh,04Ch,024h,01Ch,0C7h,044h,024h,014h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,049h,0DEh,07Dh,000h,08Bh,04Ch,024h,00Ch,064h,089h,00Dh,000h,000h
    db 000h,000h,05Eh,083h,0C4h,014h,0C2h,004h,000h
?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z ENDP
_TEXT ENDS
END
