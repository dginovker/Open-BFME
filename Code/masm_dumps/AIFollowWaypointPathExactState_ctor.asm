.386
.model flat

; ??0AIFollowWaypointPathExactState@@QAE@PAVStateMachine@@_N@Z
; Exact 60B @ 0x0017FA90. Drift 0x00185E7A was mid-instruction inside
; AIStateMachine ctor (0x185A20+4930, already matched) — inlined
; newInstance path (team/individual) after operator new, not standalone.
; True body is string-anchored on "AIFollowWaypointPathExactState" @
; 0x109A880: thin StringBase/AsciiString(char*) @ 0x888BC0,
; AIInternalMoveToState @ 0x32182, vtbl 0x109A828, m_*(0)@+0x50,
; m_moveAsGroup@+0x54 from Bool arg. Sibling: AIMoveToState_ctor.asm.
_TEXT SEGMENT
public ??0AIFollowWaypointPathExactState@@QAE@PAVStateMachine@@_N@Z
??0AIFollowWaypointPathExactState@@QAE@PAVStateMachine@@_N@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,80h,0A8h,09h,01h
    db 0E8h,1Bh,91h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0D1h,26h,0EBh
    db 0FFh,8Ah,4Ch,24h,10h,0C7h,06h,28h,0A8h,09h,01h,0C7h,46h,50h,00h,00h
    db 00h,00h,88h,4Eh,54h,8Bh,0C6h,5Eh,59h,0C2h,08h,00h
??0AIFollowWaypointPathExactState@@QAE@PAVStateMachine@@_N@Z ENDP
_TEXT ENDS
END
