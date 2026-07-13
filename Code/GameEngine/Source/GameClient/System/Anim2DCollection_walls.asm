.386
.model flat

; ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
; Exact 106 retail bytes @ 0x005BB050; by-value AsciiString arg copy is
; out-of-line in BFME (AsciiString reconciliation wall).
_TEXT SEGMENT
public ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z PROC
    db 06Ah,0FFh,068h,0FBh,093h,003h,001h,064h
    db 0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,008h
    db 056h,057h,06Ah,01Ch,08Bh,0F9h,0E8h,0BDh
    db 06Eh,02Ch,000h,08Bh,0F0h,083h,0C4h,004h
    db 089h,074h,024h,008h,033h,0C0h,03Bh,0F0h
    db 089h,044h,024h,018h,074h,018h,08Bh,044h
    db 024h,020h,051h,089h,064h,024h,010h,08Bh
    db 0CCh,050h,0E8h,0C9h,0CAh,02Ch,000h,08Bh
    db 0CEh,0E8h,043h,0C2h,0A6h,0FFh,08Bh,04Fh
    db 008h,089h,048h,004h,08Bh,04Ch,024h,010h
    db 089h,047h,008h,05Fh,064h,089h,00Dh,000h
    db 000h,000h,000h,05Eh,083h,0C4h,014h,0C2h
    db 004h,000h
?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z ENDP
_TEXT ENDS

; ?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
; Exact 155 retail bytes @ 0x005BB330; BFME AsciiString compare with
; TheEmptyString fallback (AsciiString reconciliation wall).
_TEXT SEGMENT
public ?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z PROC
    db 051h,053h,055h,08Bh,069h,008h,085h,0EDh
    db 056h,057h,074h,07Bh,08Dh,064h,024h,000h
    db 08Dh,044h,024h,010h,050h,08Bh,0CDh,0E8h
    db 026h,07Bh,0A5h,0FFh,08Bh,04Ch,024h,018h
    db 08Bh,009h,085h,0C9h,074h,006h,00Fh,0B7h
    db 059h,004h,0EBh,002h,033h,0DBh,085h,0C9h
    db 08Dh,079h,008h,075h,005h,0BFh,08Bh,038h
    db 007h,001h,08Bh,000h,085h,0C0h,074h,006h
    db 00Fh,0B7h,050h,004h,0EBh,002h,033h,0D2h
    db 085h,0C0h,08Dh,070h,008h,075h,005h,0BEh
    db 08Bh,038h,007h,001h,03Bh,0D3h,08Bh,0CAh
    db 07Ch,002h,08Bh,0CBh,033h,0C0h,0F3h,0A6h
    db 074h,005h,01Bh,0C0h,083h,0D8h,0FFh,085h
    db 0C0h,074h,004h,08Bh,0F0h,0EBh,004h,02Bh
    db 0D3h,08Bh,0F2h,08Dh,04Ch,024h,010h,0E8h
    db 094h,0C5h,02Ch,000h,085h,0F6h,074h,011h
    db 08Bh,06Dh,004h,085h,0EDh,075h,089h,05Fh
    db 05Eh,05Dh,033h,0C0h,05Bh,059h,0C2h,004h
    db 000h,05Fh,05Eh,08Bh,0C5h,05Dh,05Bh,059h
    db 0C2h,004h,000h
?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z ENDP
_TEXT ENDS

END
