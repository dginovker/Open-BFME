.386
.model flat

; ??0AIAttackThenIdleStateMachine@@QAE@PAVObject@@VAsciiString@@@Z
; Exact 347B retail @ 0x00184A40. Queue 0x002C1093 was INSIDE already-matched
; ??0AIAttackMoveStateMachine @0x2C1061/501. True body via factory at 0x184C00
; (mislabeled onExit@AIAttackState) which newInstance-s this class with string
; "AIAttackThenIdleStateMachine" and calls ILT 0x298F2 -> 0x184A40. SEH prologue +
; StateMachine base + defineState(AIAttack/PickUpCrate/Idle) matches source ctor.
_TEXT SEGMENT
public ??0AIAttackThenIdleStateMachine@@QAE@PAVObject@@VAsciiString@@@Z
??0AIAttackThenIdleStateMachine@@QAE@PAVObject@@VAsciiString@@@Z PROC
    db 6Ah,0FFh,68h,0F1h,63h,00h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h,53h,56h,8Bh,0F1h,57h,89h,74h,24h
    db 0Ch,33h,0DBh,53h,51h,8Dh,44h,24h,30h,89h,64h,24h,18h,8Bh,0CCh,50h
    db 89h,5Ch,24h,28h,0E8h,0E7h,30h,70h,00h,8Bh,4Ch,24h,2Ch,51h,8Bh,0CEh
    db 0E8h,9Eh,0A6h,0E8h,0FFh,6Ah,54h,0C6h,44h,24h,20h,01h,0C7h,06h,0F8h,76h
    db 09h,01h,0E8h,99h,0D4h,6Fh,00h,83h,0C4h,04h,89h,44h,24h,24h,3Bh,0C3h
    db 0C6h,44h,24h,1Ch,02h,74h,0Fh,53h,53h,6Ah,01h,53h,56h,8Bh,0C8h,0E8h
    db 88h,74h,0E8h,0FFh,0EBh,02h,33h,0C0h,53h,53h,53h,50h,6Ah,0Ah,8Bh,0CEh
    db 0C6h,44h,24h,30h,01h,0E8h,0E9h,86h,0EBh,0FFh,6Ah,54h,0E8h,5Fh,0D4h,6Fh
    db 00h,8Bh,0F8h,83h,0C4h,04h,89h,7Ch,24h,24h,3Bh,0FBh,0C6h,44h,24h,1Ch
    db 03h,74h,24h,51h,89h,64h,24h,14h,8Bh,0CCh,68h,28h,61h,09h,01h,0E8h
    db 0CCh,40h,70h,00h,56h,8Bh,0CFh,0E8h,86h,0D6h,0EAh,0FFh,0C7h,07h,0D0h,60h
    db 09h,01h,89h,5Fh,50h,0EBh,02h,33h,0FFh,53h,53h,53h,57h,6Ah,27h,8Bh
    db 0CEh,0C6h,44h,24h,30h,01h,0E8h,98h,86h,0EBh,0FFh,6Ah,28h,0E8h,0Eh,0D4h
    db 6Fh,00h,8Bh,0F8h,83h,0C4h,04h,89h,7Ch,24h,24h,3Bh,0FBh,0C6h,44h,24h
    db 1Ch,04h,74h,2Dh,51h,89h,64h,24h,14h,8Bh,0CCh,68h,04h,86h,09h,01h
    db 0E8h,7Bh,40h,70h,00h,56h,8Bh,0CFh,0E8h,65h,0EAh,0E7h,0FFh,0C7h,07h,0B0h
    db 85h,09h,01h,88h,5Fh,26h,88h,5Fh,27h,66h,0C7h,47h,24h,0FFh,0FFh,0EBh
    db 02h,33h,0FFh,53h,53h,53h,57h,53h,8Bh,0CEh,0C6h,44h,24h,30h,01h,0E8h
    db 3Fh,86h,0EBh,0FFh,8Dh,4Ch,24h,28h,0C7h,44h,24h,1Ch,0FFh,0FFh,0FFh,0FFh
    db 0E8h,0BBh,2Dh,70h,00h,8Bh,4Ch,24h,14h,5Fh,8Bh,0C6h,5Eh,64h,89h,0Dh
    db 00h,00h,00h,00h,5Bh,83h,0C4h,14h,0C2h,08h,00h
??0AIAttackThenIdleStateMachine@@QAE@PAVObject@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
