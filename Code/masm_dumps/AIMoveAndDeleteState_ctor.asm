.386
.model flat

; ??0AIMoveAndDeleteState@@QAE@PAVStateMachine@@@Z
; Exact 50B @ 0x0017FD70. Drift 0x001860A1 was mid-instruction inside
; AIStateMachine ctor (inlined newInstance sequence after operator new).
; True body is string-anchored on "AIMoveAndDeleteState" and builds the
; debug-name via StringBase/AsciiString(char*) @ 0x888BC0, then
; AIInternalMoveToState(StateMachine*, AsciiString) @ 0x32182, stores
; vtable @ 0x109AAD8, and clears m_appendGoalPosition at this+0x50.
_TEXT SEGMENT
public ??0AIMoveAndDeleteState@@QAE@PAVStateMachine@@@Z
??0AIMoveAndDeleteState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,30h,0ABh,09h,01h
    db 0E8h,3Bh,8Eh,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0F1h,23h,0EBh
    db 0FFh,0C7h,06h,0D8h,0AAh,09h,01h,0C6h,46h,50h,00h,8Bh,0C6h,5Eh,59h,0C2h
    db 04h,00h
??0AIMoveAndDeleteState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
