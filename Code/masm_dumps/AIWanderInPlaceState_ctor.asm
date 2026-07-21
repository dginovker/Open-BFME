.386
.model flat

; ??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z
; Exact 63B @ 0x0017FB80. Drift 0x00185CB5 is INSIDE the already-matched
; AIStateMachine ctor (4930B @ 0x00185A20; inlined newInstance SEH path after
; operator new) — same mis-vote family as AIBusyState/AIDeadState/AIMoveOutOfTheWay.
; True body is string-anchored on "AIWanderInPlaceState" @ 0x109A968 (push at
; 0x17FB8B; getName-style mov eax,str;ret @ 0x17FBD0). Shape: thin
; StringBase/AsciiString(char*) @ 0x888BC0 + AIInternalMoveToState @ 0x32182
; (ILT), store vtbl 0x109A910, zero m_origin/m_waitFrames/m_timer at this+0x50..0x60.
; Sibling: AIBusyState_ctor.asm / AIDeadState_ctor.asm / AIWanderState_ctor.asm.
_TEXT SEGMENT
public ??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z
??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,68h,0A9h,09h,01h
    db 0E8h,2Bh,90h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0E1h,25h,0EBh
    db 0FFh,33h,0C0h,0C7h,06h,10h,0A9h,09h,01h,89h,46h,50h,89h,46h,54h,89h
    db 46h,58h,89h,46h,5Ch,89h,46h,60h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
