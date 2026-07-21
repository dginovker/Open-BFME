.386
.model flat

; ??0AIAttackAreaState@@QAE@PAVStateMachine@@@Z
; Exact 54B @ 0x001718A0. Drift 0x1869EE was mid-insn inside AIStateMachine
; ctor (inlined newInstance sequence; c6 44 24 20 36 ...). True body is
; string-anchored on "AIAttackAreaState" @ VA 0x10983ec (xrefs 0x1718ab,
; 0x171910 getName-style, 0x1869fb inlined). Builds State debug-name via
; StringBase/AsciiString(char*) @ 0x888BC0, then base State ctor, stores own
; vtable + m_attackMachine=NULL at +0x24 + m_nextEnemyScanTime=0 at +0x28.
; Sibling: AIGuardRetaliateState_ctor.asm / AIDeadState_ctor.asm.
_TEXT SEGMENT
public ??0AIAttackAreaState@@QAE@PAVStateMachine@@@Z
??0AIAttackAreaState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0ECh,83h,09h,01h
    db 0E8h,0Bh,73h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0F1h,1Ch,0E9h
    db 0FFh,33h,0C0h,89h,46h,24h,89h,46h,28h,0C7h,06h,98h,83h,09h,01h,8Bh
    db 0C6h,5Eh,59h,0C2h,04h,00h
??0AIAttackAreaState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
