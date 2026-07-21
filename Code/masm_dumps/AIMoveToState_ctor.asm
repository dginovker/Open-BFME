.386
.model flat

; ??0AIMoveToState@@QAE@PAVStateMachine@@@Z
; Exact 50B @ 0x00173430. Drift 0x00186CB1 was mid-instruction inside
; AIStateMachine ctor (0x185A20+4930, already matched MASM) — inlined
; newInstance path after operator new(0x54), SEH state 0x3e is a
; different class (AIMoveToPositionAndEnterState vtbl 0x109B370).
; True body is string-anchored on "AIMoveToState" @ 0x1098F60:
;   thin StringBase/AsciiString(char*) @ 0x888BC0, AIInternalMoveToState
;   @ 0x32182, vtbl 0x1098F08, m_isMoveTo=1 at this+0x50.
; Sibling pattern: AIMoveAndDeleteState_ctor.asm / AIMoveOutOfTheWayState_ctor.asm.
_TEXT SEGMENT
public ??0AIMoveToState@@QAE@PAVStateMachine@@@Z
??0AIMoveToState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,60h,8Fh,09h,01h
    db 0E8h,7Bh,57h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,31h,0EDh,0EBh
    db 0FFh,0C7h,06h,08h,8Fh,09h,01h,0C6h,46h,50h,01h,8Bh,0C6h,5Eh,59h,0C2h
    db 04h,00h
??0AIMoveToState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
