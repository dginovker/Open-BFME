.386
.model flat

; ??1StateMachine@@MAE@XZ
; Exact 224 retail bytes @ 0x000A1130. Identity: base dtor for StateMachine
; (MEMORY_POOL_GLUE). Proven via subclass complete-object dtors that call/jmp
; ILT 0x31D5E -> body 0xA1130: AIStateMachine@0x181DF0, SupplyTruck@0x2C59E0,
; Worker@0x2C8120. Semantics: set vtbl 0x1080710; onExit(EXIT_RESET) on
; m_currentState@+0x1c via vcall +0x14; walk map@+4 deleting States via
; scalar-deleting dtor; free tree nodes; clear id/state; ~map; restore MPO
; vtbl 0x1073744. Queue RVA 0x9F27BE was padding after ControlBar ctor
; (0x9F2730/146) before PartitionManager/TeamFactory ICF dtor @0x9F2800.
; C++ blocked by layout: retail single vptr (map@+4, current@+0x1c) vs ZH
; MemoryPoolObject+Snapshot (map@+8, current@+0x20) — systemic header.
_TEXT SEGMENT
public ??1StateMachine@@MAE@XZ
??1StateMachine@@MAE@XZ PROC
    db 06Ah,0FFh,068h,013h,06Dh,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,053h,055h,08Bh,0D9h,056h,057h,089h,05Ch,024h,010h
    db 0C7h,003h,010h,007h,008h,001h,08Bh,04Bh,01Ch,033h,0EDh,03Bh,0CDh,0C7h,044h,024h
    db 01Ch,001h,000h,000h,000h,074h,007h,08Bh,001h,06Ah,001h,0FFh,050h,014h,08Bh,043h
    db 004h,08Bh,070h,008h,03Bh,0F0h,08Dh,07Bh,004h,074h,023h,0EBh,003h,08Dh,049h,000h
    db 08Bh,04Eh,014h,03Bh,0CDh,074h,006h,08Bh,011h,06Ah,001h,0FFh,012h,056h,0E8h,0DDh
    db 0A6h,078h,000h,08Bh,0F0h,08Bh,007h,083h,0C4h,004h,03Bh,0F0h,075h,0E2h,039h,06Fh
    db 004h,074h,03Eh,08Bh,007h,08Bh,070h,004h,03Bh,0F5h,074h,023h,08Dh,064h,024h,000h
    db 08Bh,04Eh,00Ch,051h,08Bh,0CFh,0E8h,0D1h,066h,0F7h,0FFh,08Bh,06Eh,008h,06Ah,018h
    db 056h,0E8h,02Ah,0D4h,078h,000h,083h,0C4h,008h,085h,0EDh,08Bh,0F5h,075h,0E1h,08Bh
    db 007h,089h,040h,008h,08Bh,017h,089h,06Ah,004h,08Bh,007h,089h,040h,00Ch,089h,06Fh
    db 004h,08Bh,0CFh,0C7h,043h,018h,03Fh,042h,00Fh,000h,089h,06Bh,01Ch,0C6h,044h,024h
    db 01Ch,000h,0E8h,004h,06Eh,0F9h,0FFh,08Bh,04Ch,024h,014h,05Fh,05Eh,0C7h,003h,044h
    db 037h,007h,001h,05Dh,05Bh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,010h,0C3h
??1StateMachine@@MAE@XZ ENDP
_TEXT ENDS
END
