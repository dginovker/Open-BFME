.386
.model flat

; ?onEnter@AIMoveAwayFromRepulsorsState@@UAE?AW4StateReturnType@@XZ
; Exact 197B @ 0x00173D50. Drift candidate 0x00189924 is mid-body float math (not a
; function start). True body from AIMoveAwayFromRepulsorsState vtable @ 0xC9A368 slot4
; (ctor @ 0x17F450 stores that vtbl after StringBase("AIMoveAwayFromRepulsors") @
; 0x888BC0). Semantics: setAdjustsDestination(false); findClosestRepulsor +
; chooseLocomotorSet(PANIC=4); inline MODELCONDITION_PANICKING bit 0x1000 on
; Object+0x118; m_okToRepathTimes=1/m_checkForPath=1; removeGoal; requestSafePath;
; tail-jmp AIInternalMoveToState::onEnter @ 0x21E27. Failure returns STATE_FAILURE.
; ZH C++ shape diverges (setModelConditionState call, different AI vtable slots).
_TEXT SEGMENT
public ?onEnter@AIMoveAwayFromRepulsorsState@@UAE?AW4StateReturnType@@XZ
?onEnter@AIMoveAwayFromRepulsorsState@@UAE?AW4StateReturnType@@XZ PROC
    db 0A0h,039h,002h,02Fh,001h,084h,0C0h,053h,055h,056h,057h,08Bh,0F9h,074h,017h,0A1h
    db 0FCh,0D4h,02Eh,001h,085h,0C0h,074h,00Eh,068h,024h,091h,009h,001h,050h,0E8h,007h
    db 064h,0ECh,0FFh,083h,0C4h,008h,08Bh,047h,01Ch,0C6h,047h,04Ch,000h,08Bh,070h,010h
    db 08Bh,0CEh,0E8h,0C4h,00Dh,0EAh,0FFh,051h,08Bh,00Dh,014h,0F2h,02Eh,001h,0D9h,01Ch
    db 024h,056h,0E8h,01Dh,080h,0EBh,0FFh,08Bh,04Fh,01Ch,08Bh,051h,010h,08Bh,09Ah,004h
    db 002h,000h,000h,08Bh,0E8h,085h,0EDh,074h,062h,085h,0DBh,074h,05Eh,08Bh,003h,06Ah
    db 004h,08Bh,0CBh,0FFh,090h,0FCh,001h,000h,000h,085h,0F6h,074h,01Eh,08Bh,08Eh,018h
    db 001h,000h,000h,0B8h,000h,010h,000h,000h,085h,0C8h,075h,00Fh,00Bh,0C8h,089h,08Eh
    db 018h,001h,000h,000h,08Bh,0CEh,0E8h,042h,0DBh,0EAh,0FFh,0B8h,001h,000h,000h,000h
    db 089h,047h,050h,088h,047h,054h,08Bh,00Dh,014h,0F2h,02Eh,001h,08Bh,049h,00Ch,056h
    db 0E8h,00Dh,01Fh,0EAh,0FFh,08Bh,055h,074h,052h,08Bh,0CBh,0E8h,010h,0D6h,0E8h,0FFh
    db 08Bh,0CFh,05Fh,05Eh,05Dh,05Bh,0E9h,01Ch,0E0h,0EAh,0FFh,05Fh,05Eh,05Dh,0B8h,0FEh
    db 0FFh,0FFh,0FFh,05Bh,0C3h
?onEnter@AIMoveAwayFromRepulsorsState@@UAE?AW4StateReturnType@@XZ ENDP
_TEXT ENDS
END
