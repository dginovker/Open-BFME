.386
.model flat

; ?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ
; Exact 450 retail bytes @ 0x0043F640; InGameUI::preDraw tail-calls thunk 0x0002E8CA.
_TEXT SEGMENT
public ?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ
?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ PROC
    db 083h, 0ECh, 010h, 053h, 055h, 08Bh, 0E9h, 08Bh, 085h, 0C0h, 012h, 000h, 000h, 08Bh, 018h, 03Bh
    db 0D8h, 089h, 06Ch, 024h, 00Ch, 00Fh, 084h, 076h, 001h, 000h, 000h, 056h, 057h, 08Dh, 049h, 000h
    db 08Bh, 00Dh, 098h, 008h, 02Fh, 001h, 08Bh, 073h, 008h, 0E8h, 028h, 036h, 0BEh, 0FFh, 084h, 0C0h
    db 075h, 044h, 0A1h, 098h, 008h, 02Fh, 001h, 08Bh, 048h, 03Ch, 03Bh, 04Eh, 010h, 00Fh, 083h, 054h
    db 001h, 000h, 000h, 0F6h, 046h, 014h, 002h, 074h, 00Ch, 08Bh, 016h, 0F6h, 042h, 010h, 004h, 00Fh
    db 085h, 042h, 001h, 000h, 000h, 0D9h, 005h, 050h, 053h, 007h, 001h, 0D9h, 046h, 018h, 0DAh, 0E9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Fh, 0D9h, 046h, 018h, 0D8h, 00Dh, 0BCh, 00Bh, 008h, 001h
    db 0D8h, 046h, 00Ch, 0D9h, 05Eh, 00Ch, 08Bh, 00Dh, 048h, 0D7h, 02Eh, 001h, 08Bh, 051h, 00Ch, 08Bh
    db 042h, 024h, 08Bh, 00Dh, 0BCh, 0D5h, 02Eh, 001h, 08Dh, 07Eh, 004h, 057h, 050h, 0E8h, 05Eh, 07Dh
    db 04Bh, 000h, 085h, 0C0h, 00Fh, 085h, 0E7h, 000h, 000h, 000h, 0F6h, 046h, 014h, 001h, 074h, 02Eh
    db 08Bh, 00Dh, 098h, 008h, 02Fh, 001h, 08Bh, 046h, 010h, 02Bh, 041h, 03Ch, 083h, 0F8h, 005h, 073h
    db 01Dh, 085h, 0C0h, 089h, 044h, 024h, 010h, 0DBh, 044h, 024h, 010h, 07Dh, 006h, 0D8h, 005h, 058h
    db 053h, 007h, 001h, 08Bh, 016h, 0D8h, 00Dh, 0BCh, 00Bh, 008h, 001h, 0D9h, 05Ah, 01Ch, 08Bh, 00Dh
    db 000h, 016h, 02Fh, 001h, 08Bh, 001h, 08Dh, 054h, 024h, 018h, 052h, 057h, 0FFh, 090h, 05Ch, 001h
    db 000h, 000h, 085h, 0C0h, 00Fh, 085h, 097h, 000h, 000h, 000h, 08Bh, 00Eh, 0E8h, 080h, 0B9h, 0BFh
    db 0FFh, 08Bh, 00Eh, 08Bh, 0F8h, 0E8h, 06Eh, 072h, 0BFh, 0FFh, 08Bh, 00Dh, 000h, 016h, 02Fh, 001h
    db 08Bh, 0E8h, 08Bh, 001h, 0FFh, 090h, 03Ch, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 010h, 08Bh, 00Dh
    db 000h, 016h, 02Fh, 001h, 08Bh, 011h, 0FFh, 092h, 020h, 001h, 000h, 000h, 0D8h, 07Ch, 024h, 010h
    db 085h, 0FFh, 089h, 07Ch, 024h, 010h, 0DBh, 044h, 024h, 010h, 07Dh, 006h, 0D8h, 005h, 058h, 053h
    db 007h, 001h, 0D8h, 0C9h, 0E8h, 0BFh, 076h, 05Bh, 000h, 085h, 0EDh, 089h, 06Ch, 024h, 010h, 0DBh
    db 044h, 024h, 010h, 08Bh, 0F8h, 07Dh, 006h, 0D8h, 005h, 058h, 053h, 007h, 001h, 0D8h, 0C9h, 0E8h
    db 0A4h, 076h, 05Bh, 000h, 0DDh, 0D8h, 08Bh, 04Ch, 024h, 018h, 08Bh, 0D7h, 0D1h, 0EAh, 02Bh, 0CAh
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 0E8h, 050h, 0D1h, 0EDh, 02Bh, 0D5h, 057h, 052h, 089h, 04Ch, 024h
    db 024h, 089h, 054h, 024h, 028h, 051h, 08Bh, 00Eh, 0E8h, 0FCh, 015h, 0BFh, 0FFh, 08Bh, 06Ch, 024h
    db 014h, 08Bh, 01Bh, 03Bh, 09Dh, 0C0h, 012h, 000h, 000h, 00Fh, 085h, 091h, 0FEh, 0FFh, 0FFh, 05Fh
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 010h, 0C3h, 08Bh, 00Eh, 085h, 0C9h, 074h, 006h, 08Bh, 001h, 06Ah
    db 001h, 0FFh, 010h, 056h, 0E8h, 0C7h, 026h, 044h, 000h, 08Bh, 033h, 08Bh, 043h, 004h, 06Ah, 00Ch
    db 089h, 030h, 053h, 089h, 046h, 004h, 0E8h, 0F5h, 0EDh, 03Eh, 000h, 083h, 0C4h, 00Ch, 08Bh, 0DEh
    db 0EBh, 0C1h
?updateAndDrawWorldAnimations@InGameUI@@IAEXXZ ENDP
_TEXT ENDS
END
