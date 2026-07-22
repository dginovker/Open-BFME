.386
.model flat

; ?createWindow@@YAPAVGameWindow@@PADHHHHHHPAVWinInstanceData@@PAXP6A?AW4WindowMsgHandledType@@PAV1@III@Z4P6AX31I@ZP6AX31@Z@Z
; Exact 320 retail bytes @ 0x004874A0.
; True body after queue 0x009D2256 (int3 pad / wrong region).
; Identity: parseWindow calls @ 0x488379 and 0x48849F; USER@0x10F9204 +
; TABPANE@0x10F91D8 strcmp; inlined peekWindow; createGadget via 0x3107F;
; setWindowText @ 0x4864E0; TheWindowManager winCreate/winSendInputMsg.
; C++ blocked: 485B vs 320B (inlined peekWindow + thin GameWindow thunks
; + GWM vtable shape); same MASM route as createGadget/setWindowText.
_TEXT SEGMENT
public ?createWindow@@YAPAVGameWindow@@PADHHHHHHPAVWinInstanceData@@PAXP6A?AW4WindowMsgHandledType@@PAV1@III@Z4P6AX31I@ZP6AX31@Z@Z
?createWindow@@YAPAVGameWindow@@PADHHHHHHPAVWinInstanceData@@PAXP6A?AW4WindowMsgHandledType@@PAV1@III@Z4P6AX31I@ZP6AX31@Z@Z PROC
    db 0A1h, 0F4h, 024h, 02Fh, 001h, 083h, 0ECh, 008h, 03Dh, 0F8h, 024h, 02Fh, 001h, 055h, 08Bh, 06Ch
    db 024h, 010h, 056h, 057h, 075h, 00Ah, 0C7h, 044h, 024h, 00Ch, 000h, 000h, 000h, 000h, 0EBh, 007h
    db 08Bh, 040h, 0FCh, 089h, 044h, 024h, 00Ch, 0BFh, 004h, 092h, 00Fh, 001h, 08Bh, 0F2h, 0B9h, 005h
    db 000h, 000h, 000h, 033h, 0C0h, 0F3h, 0A6h, 075h, 022h, 08Bh, 00Dh, 040h, 01Bh, 02Fh, 001h, 08Bh
    db 011h, 053h, 0FFh, 052h, 074h, 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 0E8h, 000h, 000h, 000h, 08Bh
    db 043h, 030h, 081h, 048h, 00Ch, 000h, 002h, 000h, 000h, 0EBh, 05Ah, 0BFh, 0D8h, 091h, 00Fh, 001h
    db 08Bh, 0F2h, 0B9h, 008h, 000h, 000h, 000h, 033h, 0C0h, 0F3h, 0A6h, 075h, 02Dh, 08Bh, 00Dh, 040h
    db 01Bh, 02Fh, 001h, 08Bh, 011h, 053h, 0FFh, 052h, 074h, 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 0B4h
    db 000h, 000h, 000h, 08Bh, 043h, 030h, 081h, 048h, 00Ch, 000h, 040h, 000h, 000h, 08Bh, 043h, 030h
    db 050h, 08Bh, 0CEh, 0E8h, 0BDh, 01Bh, 0BAh, 0FFh, 0EBh, 01Bh, 08Bh, 04Ch, 024h, 01Ch, 06Ah, 000h
    db 053h, 051h, 052h, 0E8h, 037h, 09Bh, 0BAh, 0FFh, 08Bh, 0F0h, 083h, 0C4h, 010h, 085h, 0F6h, 00Fh
    db 084h, 082h, 000h, 000h, 000h, 08Bh, 0CEh, 055h, 0E8h, 0C7h, 01Ah, 0B9h, 0FFh, 08Bh, 0CEh, 0E8h
    db 04Ah, 02Bh, 0BAh, 0FFh, 08Bh, 0F8h, 085h, 0FFh, 074h, 033h, 068h, 070h, 025h, 02Fh, 001h, 08Bh
    db 0CFh, 0E8h, 01Ah, 007h, 040h, 000h, 068h, 074h, 025h, 02Fh, 001h, 08Dh, 04Fh, 004h, 0E8h, 00Dh
    db 007h, 040h, 000h, 068h, 078h, 025h, 02Fh, 001h, 08Dh, 04Fh, 008h, 0E8h, 000h, 007h, 040h, 000h
    db 068h, 07Ch, 025h, 02Fh, 001h, 08Dh, 04Fh, 00Ch, 0E8h, 0F3h, 006h, 040h, 000h, 08Bh, 053h, 030h
    db 051h, 081h, 0C2h, 088h, 001h, 000h, 000h, 089h, 064h, 024h, 014h, 08Bh, 0CCh, 052h, 0E8h, 0ADh
    db 005h, 040h, 000h, 0E8h, 028h, 0EFh, 0FFh, 0FFh, 08Bh, 044h, 024h, 010h, 083h, 0C4h, 004h, 085h
    db 0C0h, 074h, 014h, 08Bh, 00Dh, 040h, 01Bh, 02Fh, 001h, 08Bh, 011h, 06Ah, 000h, 055h, 06Ah, 016h
    db 050h, 0FFh, 092h, 0D8h, 000h, 000h, 000h, 05Fh, 08Bh, 0C6h, 05Eh, 05Dh, 083h, 0C4h, 008h, 0C3h
?createWindow@@YAPAVGameWindow@@PADHHHHHHPAVWinInstanceData@@PAXP6A?AW4WindowMsgHandledType@@PAV1@III@Z4P6AX31I@ZP6AX31@Z@Z ENDP
_TEXT ENDS
END
