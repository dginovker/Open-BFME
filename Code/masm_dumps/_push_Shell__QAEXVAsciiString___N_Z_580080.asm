.386
.model flat

; ?push@Shell@@QAEXVAsciiString@@_N@Z
; Exact 164B @ 0x00580080; true body (queue 0x9D234B was INSIDE unrelated fn);
; identity: GameSpyClose+ m_screenCount<16 + pendingPush + StringBase::set + runShutdown/shutdownComplete
_TEXT SEGMENT
public ?push@Shell@@QAEXVAsciiString@@_N@Z
?push@Shell@@QAEXVAsciiString@@_N@Z PROC
    db 064h,0A1h,000h,000h,000h,000h,06Ah,0FFh,068h,0D8h,068h,003h,001h,050h,064h,089h
    db 025h,000h,000h,000h,000h,056h,08Bh,0F1h,08Bh,044h,024h,014h,085h,0C0h,0C7h,044h
    db 024h,00Ch,000h,000h,000h,000h,074h,059h,066h,083h,078h,004h,000h,074h,052h,0A1h
    db 094h,071h,02Fh,001h,085h,0C0h,074h,005h,0E8h,0EEh,0F4h,0A8h,0FFh,083h,07Eh,048h
    db 010h,07Dh,03Eh,08Dh,044h,024h,014h,08Dh,04Eh,054h,050h,0C6h,046h,04Ch,001h,0E8h
    db 0BCh,07Bh,030h,000h,08Bh,046h,048h,085h,0C0h,074h,01Bh,08Bh,04Ch,086h,004h,085h
    db 0C9h,074h,013h,08Ah,041h,014h,084h,0C0h,075h,00Ch,08Bh,011h,08Dh,044h,024h,018h
    db 050h,0FFh,052h,00Ch,0EBh,00Bh,06Ah,000h,06Ah,000h,08Bh,0CEh,0E8h,01Ch,02Eh,0A8h
    db 0FFh,08Dh,04Ch,024h,014h,0C7h,044h,024h,00Ch,0FFh,0FFh,0FFh,0FFh,0E8h,02Eh,078h
    db 030h,000h,08Bh,04Ch,024h,004h,064h,089h,00Dh,000h,000h,000h,000h,05Eh,083h,0C4h
    db 00Ch,0C2h,008h,000h
?push@Shell@@QAEXVAsciiString@@_N@Z ENDP
_TEXT ENDS
END
