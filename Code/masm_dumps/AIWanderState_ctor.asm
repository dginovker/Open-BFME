.386
.model flat

; ??0AIWanderState@@QAE@PAVStateMachine@@@Z
; Exact 82B @ 0x0017FB00. Drift 0x00183CA5 is INSIDE the already-matched
; AIAttackFollowWaypointPathState ctor (201B @ 0x00183C90; string
; "AIFollowWaypointPathState" @ 0x109A808) — same mis-vote family as
; AIPanicState (drift 0x183CA7). True body sits immediately before the
; getNameKey-style mov eax,"AIWanderState";ret @ 0x17FB70 and stores vtable
; 0x109A8A8. Inlines AIFollowWaypointPathState(machine,false) via
; StringBase/AsciiString(char*) @ 0x888BC0 + AIInternalMoveToState @ 0x32182
; with asGroup=false, zeros FollowWaypoint fields + m_waitFrames/m_timer at
; this+0x6c/0x70. Sibling: AIPanicState_ctor.asm (identical shape, vtbl/string).
_TEXT SEGMENT
public ??0AIWanderState@@QAE@PAVStateMachine@@@Z
??0AIWanderState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,08h,0A8h,09h,01h
    db 0E8h,0ABh,90h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,61h,26h,0EBh
    db 0FFh,33h,0C0h,89h,46h,50h,89h,46h,54h,89h,46h,58h,89h,46h,5Ch,89h
    db 46h,60h,89h,46h,64h,88h,46h,68h,88h,46h,69h,89h,46h,6Ch,89h,46h
    db 70h,0C6h,46h,6Ah,01h,0C7h,06h,0A8h,0A8h,09h,01h,8Bh,0C6h,5Eh,59h,0C2h
    db 04h,00h
??0AIWanderState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
