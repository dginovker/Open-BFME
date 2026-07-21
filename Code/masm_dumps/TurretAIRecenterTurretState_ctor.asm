.386
.model flat

; ??0TurretAIRecenterTurretState@@QAE@PAVTurretStateMachine@@@Z
; Exact 46B @ 0x0018DA80. Drift 0x18DD60 was INSIDE matched TurretStateMachine
; ctor (0x18DB84+658) — mid-instruction of the inlined newInstance sequence
; (shape ratio 38% was coincidence on surrounding defineState code). True body
; is string-anchored on "TurretAIRecenterTurretState" and builds the State
; debug-name via StringBase/AsciiString(char*) @ 0x888BC0. Sibling pattern:
; AIDeadState_ctor.asm / AIBusyState_ctor.asm / FailureState_ctor.asm.
_TEXT SEGMENT
public ??0TurretAIRecenterTurretState@@QAE@PAVTurretStateMachine@@@Z
??0TurretAIRecenterTurretState@@QAE@PAVTurretStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,14h,0BEh,09h,01h
    db 0E8h,2Bh,0B1h,6Fh,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0B6h,5Fh,0E8h
    db 0FFh,0C7h,06h,0C0h,0BDh,09h,01h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0TurretAIRecenterTurretState@@QAE@PAVTurretStateMachine@@@Z ENDP
_TEXT ENDS
END
