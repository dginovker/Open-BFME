.386
.model flat

; ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
; Exact 605 retail bytes @ 0x00454760
; Identity: true start 0x454760 (queue 0x454759 was 7B int3 pad). SEH frame;
; readReal x4 + readInt + readAsciiString + optional readDict; operator new(0x60);
; MapObject ctor @0x88160 (thunk 0x1230A); waypoint Dict getType + setIsWaypoint;
; m_waypoints map[] / tech+supply list push paths; deleteInstance; return TRUE.
; C++ blocked: MapObject newInstance sizeof 0x60 vs ZH pool 0x48 + stack/reg shape.
_TEXT SEGMENT
public ?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z PROC
    db 06Ah,0FFh,068h,0E6h,03Eh,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,018h,053h,056h,08Bh,074h,024h,030h,057h,08Bh
    db 07Ch,024h,038h,066h,083h,07Fh,008h,002h,08Bh,0CEh,01Ah,0DBh,0FEh,0C3h,0E8h,04Eh
    db 09Eh,0BDh,0FFh,0D9h,05Ch,024h,018h,08Bh,0CEh,0E8h,043h,09Eh,0BDh,0FFh,0D9h,05Ch
    db 024h,01Ch,08Bh,0CEh,0E8h,038h,09Eh,0BDh,0FFh,0D9h,05Ch,024h,020h,066h,083h,07Fh
    db 008h,002h,077h,008h,0C7h,044h,024h,020h,000h,000h,000h,000h,08Bh,0CEh,0E8h,01Eh
    db 09Eh,0BDh,0FFh,0D9h,05Ch,024h,010h,08Bh,0CEh,0E8h,037h,060h,0BEh,0FFh,08Bh,0F8h
    db 08Dh,044h,024h,038h,050h,08Bh,0CEh,0E8h,0EDh,0F9h,0BAh,0FFh,06Ah,000h,08Dh,04Ch
    db 024h,010h,0C7h,044h,024h,030h,000h,000h,000h,000h,0E8h,0DEh,0E6h,0BAh,0FFh,084h
    db 0DBh,0C6h,044h,024h,02Ch,001h,074h,029h,08Dh,04Ch,024h,014h,051h,08Bh,0CEh,0E8h
    db 07Fh,0DEh,0BCh,0FFh,050h,08Dh,04Ch,024h,010h,0C6h,044h,024h,030h,002h,0E8h,053h
    db 00Dh,0BFh,0FFh,08Dh,04Ch,024h,014h,0C6h,044h,024h,02Ch,001h,0E8h,054h,0FCh,0BBh
    db 0FFh,08Bh,00Dh,0D8h,0F1h,02Eh,001h,08Dh,054h,024h,038h,052h,0E8h,00Ah,0EAh,0BCh
    db 0FFh,084h,0C0h,0BBh,004h,000h,000h,000h,06Ah,060h,074h,062h,0E8h,0EFh,0D6h,042h
    db 000h,08Bh,0F0h,083h,0C4h,004h,089h,074h,024h,014h,085h,0F6h,0C6h,044h,024h,02Ch
    db 003h,00Fh,084h,093h,000h,000h,000h,08Bh,00Dh,0D8h,0F1h,02Eh,001h,08Dh,044h,024h
    db 038h,050h,0E8h,0F9h,03Ch,0BDh,0FFh,08Bh,054h,024h,010h,050h,08Dh,04Ch,024h,010h
    db 051h,08Bh,04Ch,024h,020h,057h,052h,08Bh,054h,024h,02Ch,08Dh,044h,024h,048h,050h
    db 083h,0ECh,00Ch,08Bh,0C4h,089h,008h,08Bh,04Ch,024h,040h,089h,048h,008h,08Bh,0CEh
    db 089h,064h,024h,030h,089h,050h,004h,0E8h,06Eh,0DAh,0BBh,0FFh,0EBh,04Eh,0E8h,08Dh
    db 0D6h,042h,000h,083h,0C4h,004h,089h,044h,024h,014h,085h,0C0h,088h,05Ch,024h,02Ch
    db 074h,038h,08Bh,04Ch,024h,010h,06Ah,000h,08Dh,054h,024h,010h,052h,057h,051h,08Bh
    db 04Ch,024h,028h,08Dh,054h,024h,048h,052h,083h,0ECh,00Ch,08Bh,0D4h,089h,00Ah,08Bh
    db 04Ch,024h,03Ch,089h,04Ah,004h,08Bh,04Ch,024h,040h,089h,04Ah,008h,08Bh,0C8h,089h
    db 064h,024h,030h,0E8h,022h,0DAh,0BBh,0FFh,0EBh,002h,033h,0C0h,0B9h,0B0h,077h,02Ah
    db 001h,0C6h,044h,024h,02Ch,001h,08Bh,0F0h,0E8h,007h,04Ah,0BBh,0FFh,050h,08Dh,04Eh
    db 024h,0E8h,0D2h,0A6h,0BCh,0FFh,083h,0F8h,001h,08Bh,0CEh,075h,047h,08Bh,046h,044h
    db 08Dh,054h,024h,014h,00Bh,0C3h,052h,089h,046h,044h,0E8h,0E6h,0C5h,0BBh,0FFh,08Bh
    db 00Dh,088h,015h,02Fh,001h,050h,0C6h,044h,024h,030h,005h,0E8h,067h,084h,0BBh,0FFh
    db 08Bh,04Ch,024h,018h,08Bh,054h,024h,01Ch,089h,008h,08Bh,04Ch,024h,020h,089h,050h
    db 004h,089h,048h,008h,08Dh,04Ch,024h,014h,0C6h,044h,024h,02Ch,001h,0E8h,0EEh,02Fh
    db 043h,000h,0EBh,02Ah,0E8h,0BBh,0DEh,0BBh,0FFh,085h,0C0h,074h,021h,08Bh,0CEh,0E8h
    db 0B0h,0DEh,0BBh,0FFh,08Bh,088h,0D0h,000h,000h,000h,0F6h,0C5h,010h,074h,00Fh,08Dh
    db 054h,024h,018h,052h,0B9h,0A8h,015h,02Fh,001h,0E8h,001h,0C9h,0BBh,0FFh,085h,0F6h
    db 074h,008h,08Bh,006h,06Ah,001h,08Bh,0CEh,0FFh,010h,08Dh,04Ch,024h,00Ch,0C6h,044h
    db 024h,02Ch,000h,0E8h,0DDh,0FAh,0BBh,0FFh,08Dh,04Ch,024h,038h,0C7h,044h,024h,02Ch
    db 0FFh,0FFh,0FFh,0FFh,0E8h,097h,02Fh,043h,000h,08Bh,04Ch,024h,024h,05Fh,05Eh,0B0h
    db 001h,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,024h,0C3h
?ParseObjectDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z ENDP
_TEXT ENDS
END
