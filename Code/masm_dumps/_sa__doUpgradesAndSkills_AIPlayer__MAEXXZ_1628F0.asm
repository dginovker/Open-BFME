.386
.model flat
; ?doUpgradesAndSkills@AIPlayer@@MAEXXZ
; Exact 740B @ 0x001628F0; string-anchor " purchases from SkillSet"; true body (queue 0x62E63 was int3 pad)
_TEXT SEGMENT
public ?doUpgradesAndSkills@AIPlayer@@MAEXXZ
?doUpgradesAndSkills@AIPlayer@@MAEXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h, 0C0h, 054h, 000h, 001h, 050h, 0A1h, 098h
    db 008h, 02Fh, 001h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 08Bh, 040h, 03Ch, 083h, 0ECh, 014h
    db 083h, 0F8h, 002h, 055h, 08Bh, 0E9h, 00Fh, 082h, 097h, 002h, 000h, 000h, 08Bh, 045h, 00Ch, 08Bh
    db 088h, 064h, 002h, 000h, 000h, 085h, 0C9h, 00Fh, 09Fh, 0C1h, 084h, 0C9h, 00Fh, 084h, 081h, 002h
    db 000h, 000h, 08Bh, 00Dh, 014h, 0F2h, 02Eh, 001h, 08Bh, 049h, 014h, 053h, 08Bh, 099h, 0ECh, 000h
    db 000h, 000h, 085h, 0DBh, 00Fh, 084h, 068h, 002h, 000h, 000h, 08Bh, 040h, 028h, 056h, 057h, 089h
    db 044h, 024h, 01Ch, 0EBh, 00Bh, 08Bh, 044h, 024h, 01Ch, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 085h, 0C0h, 074h, 00Dh, 00Fh, 0B7h, 048h, 004h, 089h, 04Ch, 024h, 014h, 08Dh, 078h, 008h, 0EBh
    db 011h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 014h, 0BFh, 08Bh, 038h
    db 007h, 001h, 08Bh, 043h, 004h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 050h, 004h, 0EBh, 002h, 033h
    db 0D2h, 085h, 0C0h, 08Dh, 070h, 008h, 075h, 005h, 0BEh, 08Bh, 038h, 007h, 001h, 03Bh, 0D1h, 07Dh
    db 002h, 08Bh, 0CAh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h, 083h, 0D8h, 0FFh, 085h, 0C0h
    db 075h, 00Ah, 02Bh, 054h, 024h, 014h, 08Bh, 0C2h, 085h, 0C0h, 074h, 01Dh, 08Bh, 09Bh, 0BCh, 001h
    db 000h, 000h, 085h, 0DBh, 075h, 08Fh, 05Fh, 05Eh, 05Bh, 05Dh, 08Bh, 04Ch, 024h, 014h, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 020h, 0C3h, 085h, 0DBh, 00Fh, 084h, 0CFh, 001h, 000h
    db 000h, 083h, 07Dh, 030h, 0FFh, 075h, 068h, 08Bh, 043h, 068h, 033h, 0F6h, 085h, 0C0h, 07Eh, 032h
    db 08Bh, 083h, 0BCh, 000h, 000h, 000h, 085h, 0C0h, 0BEh, 001h, 000h, 000h, 000h, 07Eh, 023h, 08Bh
    db 083h, 010h, 001h, 000h, 000h, 085h, 0C0h, 0BEh, 002h, 000h, 000h, 000h, 07Eh, 014h, 08Bh, 083h
    db 064h, 001h, 000h, 000h, 085h, 0C0h, 0BEh, 003h, 000h, 000h, 000h, 07Eh, 005h, 0BEh, 004h, 000h
    db 000h, 000h, 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 02Ch, 084h, 0C0h, 074h, 01Ah, 068h, 019h
    db 00Bh, 000h, 000h, 068h, 0ECh, 069h, 009h, 001h, 056h, 06Ah, 000h, 0E8h, 06Eh, 0F1h, 0E9h, 0FFh
    db 083h, 0C4h, 010h, 089h, 045h, 030h, 0EBh, 007h, 0C7h, 045h, 030h, 000h, 000h, 000h, 000h, 08Bh
    db 045h, 00Ch, 08Bh, 088h, 064h, 002h, 000h, 000h, 085h, 0C9h, 00Fh, 08Eh, 050h, 001h, 000h, 000h
    db 08Bh, 045h, 030h, 048h, 083h, 0F8h, 003h, 077h, 024h, 0FFh, 024h, 085h, 0C4h, 02Bh, 056h, 000h
    db 08Dh, 07Bh, 068h, 0EBh, 01Bh, 08Dh, 0BBh, 0BCh, 000h, 000h, 000h, 0EBh, 013h, 08Dh, 0BBh, 010h
    db 001h, 000h, 000h, 0EBh, 00Bh, 08Dh, 0BBh, 064h, 001h, 000h, 000h, 0EBh, 003h, 08Dh, 07Bh, 014h
    db 083h, 03Fh, 000h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 00Fh, 08Eh, 00Fh, 001h, 000h
    db 000h, 08Dh, 04Fh, 004h, 089h, 04Ch, 024h, 018h, 0B3h, 020h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 08Bh, 054h, 024h, 018h, 08Bh, 032h, 08Bh, 04Dh, 00Ch, 056h, 0E8h, 086h, 073h, 0EEh, 0FFh, 084h
    db 0C0h, 00Fh, 084h, 0CBh, 000h, 000h, 000h, 08Bh, 04Dh, 00Ch, 056h, 0E8h, 0F4h, 020h, 0EAh, 0FFh
    db 084h, 0C0h, 00Fh, 084h, 0BAh, 000h, 000h, 000h, 08Bh, 045h, 00Ch, 08Bh, 040h, 020h, 050h, 08Dh
    db 04Ch, 024h, 018h, 051h, 08Bh, 00Dh, 000h, 0D6h, 02Eh, 001h, 0E8h, 08Bh, 0C1h, 0EDh, 0FFh, 068h
    db 0CCh, 069h, 009h, 001h, 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 030h, 000h, 000h, 000h, 000h
    db 0E8h, 052h, 0F5h, 0EBh, 0FFh, 08Ah, 055h, 030h, 06Ah, 001h, 08Dh, 044h, 024h, 014h, 080h, 0C2h
    db 031h, 050h, 08Dh, 04Ch, 024h, 01Ch, 088h, 054h, 024h, 018h, 0E8h, 041h, 052h, 072h, 000h, 06Ah
    db 001h, 08Dh, 04Ch, 024h, 014h, 051h, 08Dh, 04Ch, 024h, 01Ch, 088h, 05Ch, 024h, 018h, 0E8h, 02Dh
    db 052h, 072h, 000h, 08Bh, 00Dh, 0ACh, 0D7h, 02Eh, 001h, 056h, 08Dh, 054h, 024h, 024h, 052h, 0E8h
    db 00Eh, 01Dh, 0ECh, 0FFh, 050h, 08Dh, 04Ch, 024h, 018h, 0C6h, 044h, 024h, 030h, 001h, 0E8h, 002h
    db 08Dh, 0ECh, 0FFh, 08Dh, 04Ch, 024h, 020h, 0C6h, 044h, 024h, 02Ch, 000h, 0E8h, 0DFh, 04Dh, 072h
    db 000h, 068h, 04Ch, 01Dh, 008h, 001h, 08Dh, 04Ch, 024h, 018h, 0E8h, 0E8h, 0F4h, 0EBh, 0FFh, 08Bh
    db 00Dh, 06Ch, 007h, 02Fh, 001h, 06Ah, 000h, 08Dh, 044h, 024h, 018h, 050h, 0E8h, 05Fh, 061h, 0ECh
    db 0FFh, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 02Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0AEh, 04Dh
    db 072h, 000h, 08Bh, 044h, 024h, 01Ch, 08Bh, 054h, 024h, 018h, 08Bh, 00Fh, 040h, 083h, 0C2h, 004h
    db 03Bh, 0C1h, 089h, 044h, 024h, 01Ch, 089h, 054h, 024h, 018h, 00Fh, 08Ch, 000h, 0FFh, 0FFh, 0FFh
    db 05Fh, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 018h, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 020h, 0C3h, 090h, 070h, 02Ah, 056h, 000h, 075h, 02Ah, 056h, 000h, 07Dh, 02Ah, 056h, 000h
    db 085h, 02Ah, 056h, 000h
?doUpgradesAndSkills@AIPlayer@@MAEXXZ ENDP
_TEXT ENDS
END
