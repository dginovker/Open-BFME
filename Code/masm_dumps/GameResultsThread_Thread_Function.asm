.386
.model flat

; ?Thread_Function@GameResultsThreadClass@@UAEXXZ
; Exact 387 retail bytes @ 0x00641E70; WSA loop and sendGameResults call prove ownership.
_TEXT SEGMENT
public ?Thread_Function@GameResultsThreadClass@@UAEXXZ
?Thread_Function@GameResultsThreadClass@@UAEXXZ PROC
    db 055h, 08Bh, 0ECh, 06Ah, 0FFh, 068h, 070h, 01Ch, 004h, 001h, 064h, 0A1h, 000h, 000h, 000h, 000h
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 0D0h, 001h, 000h, 000h, 053h, 056h
    db 057h, 089h, 04Dh, 0E8h, 08Dh, 04Dh, 0C4h, 089h, 065h, 0F0h, 0C7h, 045h, 0FCh, 000h, 000h, 000h
    db 000h, 0E8h, 0E4h, 0E5h, 09Fh, 0FFh, 08Dh, 04Dh, 0D4h, 0C6h, 045h, 0FCh, 001h, 0E8h, 0D8h, 0E5h
    db 09Fh, 0FFh, 08Dh, 085h, 024h, 0FEh, 0FFh, 0FFh, 050h, 068h, 001h, 001h, 000h, 000h, 0C6h, 045h
    db 0FCh, 002h, 0FFh, 015h, 0F0h, 096h, 035h, 001h, 08Bh, 03Dh, 008h, 097h, 035h, 001h, 0B3h, 003h
    db 08Bh, 04Dh, 0E8h, 08Bh, 051h, 050h, 06Ah, 001h, 052h, 08Dh, 04Dh, 0E0h, 0E8h, 0CFh, 094h, 039h
    db 000h, 08Ah, 045h, 0E4h, 084h, 0C0h, 088h, 05Dh, 0FCh, 075h, 02Fh, 08Dh, 04Dh, 0E0h, 0C6h, 045h
    db 0FCh, 002h, 0E8h, 009h, 095h, 039h, 000h, 0FFh, 015h, 0E8h, 096h, 035h, 001h, 08Dh, 04Dh, 0C4h
    db 0C6h, 045h, 0FCh, 000h, 0E8h, 07Fh, 073h, 0A0h, 0FFh, 08Bh, 04Dh, 0F4h, 05Fh, 05Eh, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 05Bh, 08Bh, 0E5h, 05Dh, 0C3h, 08Bh, 00Dh, 0C4h, 071h, 02Fh, 001h
    db 085h, 0C9h, 00Fh, 084h, 0BAh, 000h, 000h, 000h, 08Bh, 001h, 08Dh, 055h, 0C4h, 052h, 0FFh, 050h
    db 034h, 084h, 0C0h, 00Fh, 084h, 0A9h, 000h, 000h, 000h, 08Bh, 075h, 0C4h, 00Fh, 0BEh, 006h, 050h
    db 0FFh, 015h, 010h, 094h, 035h, 001h, 083h, 0C4h, 004h, 085h, 0C0h, 056h, 074h, 008h, 0FFh, 015h
    db 01Ch, 097h, 035h, 001h, 0EBh, 009h, 0FFh, 0D7h, 08Bh, 048h, 00Ch, 08Bh, 001h, 08Bh, 000h, 08Bh
    db 04Dh, 0D0h, 08Dh, 055h, 0D4h, 052h, 051h, 08Bh, 04Dh, 0E8h, 050h, 0E8h, 04Bh, 0FBh, 09Eh, 0FFh
    db 08Dh, 04Dh, 0B4h, 08Bh, 0F0h, 0E8h, 010h, 0E5h, 09Fh, 0FFh, 08Bh, 045h, 0C8h, 08Bh, 04Dh, 0C4h
    db 08Dh, 055h, 0EFh, 052h, 050h, 051h, 08Dh, 04Dh, 0B4h, 0C6h, 045h, 0FCh, 004h, 0E8h, 0C6h, 0FAh
    db 09Dh, 0FFh, 066h, 08Bh, 055h, 0D0h, 08Bh, 045h, 0D8h, 066h, 089h, 055h, 0C0h, 02Bh, 045h, 0D4h
    db 03Bh, 0F0h, 08Bh, 045h, 0BCh, 00Fh, 094h, 0C1h, 088h, 04Dh, 0C2h, 08Bh, 04Dh, 0B4h, 02Bh, 0C1h
    db 085h, 0C9h, 088h, 05Dh, 0FCh, 074h, 02Bh, 03Dh, 080h, 000h, 000h, 000h, 076h, 01Ah, 051h, 0E8h
    db 0ECh, 0FEh, 023h, 000h, 083h, 0C4h, 004h, 08Dh, 04Dh, 0E0h, 0C6h, 045h, 0FCh, 002h, 0E8h, 02Dh
    db 094h, 039h, 000h, 0E9h, 0F8h, 0FEh, 0FFh, 0FFh, 050h, 051h, 0E8h, 011h, 0C6h, 01Eh, 000h, 083h
    db 0C4h, 008h, 08Dh, 04Dh, 0E0h, 0C6h, 045h, 0FCh, 002h, 0E8h, 012h, 094h, 039h, 000h, 0E9h, 0DDh
    db 0FEh, 0FFh, 0FFh
?Thread_Function@GameResultsThreadClass@@UAEXXZ ENDP
_TEXT ENDS
END
