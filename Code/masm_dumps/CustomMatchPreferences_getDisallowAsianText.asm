.386
.model flat

; ?getDisallowAsianText@CustomMatchPreferences@@QAE_NXZ
; Exact 95 retail bytes @ 0x004AC590; reads the DisallowAsianText preference.
_TEXT SEGMENT
public ?getDisallowAsianText@CustomMatchPreferences@@QAE_NXZ
?getDisallowAsianText@CustomMatchPreferences@@QAE_NXZ PROC
    db 051h,056h,057h,08Bh,0F1h,068h,0FCh,011h,008h,001h,08Dh,04Ch,024h,00Ch,0E8h,01Dh
    db 0C6h,07Dh,000h,08Dh,044h,024h,008h,083h,0C6h,004h,050h,08Bh,0CEh,0E8h,0FAh,0E8h
    db 0F5h,0FFh,08Dh,04Ch,024h,008h,08Bh,0F8h,0E8h,083h,0B3h,07Dh,000h,03Bh,03Eh,075h
    db 006h,05Fh,032h,0C0h,05Eh,059h,0C3h,08Bh,07Fh,014h,085h,0FFh,08Dh,047h,008h,075h
    db 005h,0B8h,08Bh,038h,007h,001h,068h,0C0h,00Fh,008h,001h,050h,0FFh,015h,03Ch,093h
    db 035h,001h,083h,0C4h,008h,0F7h,0D8h,01Ah,0C0h,05Fh,0FEh,0C0h,05Eh,059h,0C3h
?getDisallowAsianText@CustomMatchPreferences@@QAE_NXZ ENDP
_TEXT ENDS
END
