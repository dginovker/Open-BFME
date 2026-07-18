.386
.model flat

; ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
; Exact 167 retail bytes @ 0x00751320; writes a BFME script parameter.
_TEXT SEGMENT
public ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z PROC
    db 055h,08Bh,06Ch,024h,008h,056h,08Bh,0F1h,08Bh,006h,050h,08Bh,0CDh,0E8h,082h,07Fh
    db 0CBh,0FFh,083h,03Eh,01Bh,075h,03Fh,08Bh,046h,008h,085h,0C0h,057h,07Ch,010h,03Dh
    db 0B5h,000h,000h,000h,073h,009h,08Bh,03Ch,085h,068h,0A0h,02Ah,001h,0EBh,002h,033h
    db 0FFh,085h,0FFh,08Dh,04Eh,010h,074h,014h,08Bh,0C7h,053h,08Dh,058h,001h,08Bh,0FFh
    db 08Ah,010h,040h,084h,0D2h,075h,0F9h,02Bh,0C3h,05Bh,0EBh,002h,033h,0C0h,050h,057h
    db 0E8h,0ABh,069h,053h,000h,05Fh,083h,03Eh,010h,075h,026h,08Bh,04Eh,014h,051h,08Bh
    db 0CDh,0E8h,00Eh,035h,0CCh,0FFh,08Bh,056h,018h,052h,08Bh,0CDh,0E8h,003h,035h,0CCh
    db 0FFh,08Bh,046h,01Ch,050h,08Bh,0CDh,0E8h,0F8h,034h,0CCh,0FFh,05Eh,05Dh,0C2h,004h
    db 000h,08Bh,04Eh,008h,051h,08Bh,0CDh,0E8h,008h,07Fh,0CBh,0FFh,08Bh,056h,00Ch,052h
    db 08Bh,0CDh,0E8h,0DDh,034h,0CCh,0FFh,083h,0C6h,010h,056h,08Bh,0CDh,0E8h,0FCh,0D7h
    db 0CCh,0FFh,05Eh,05Dh,0C2h,004h,000h
?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z ENDP
_TEXT ENDS
END
