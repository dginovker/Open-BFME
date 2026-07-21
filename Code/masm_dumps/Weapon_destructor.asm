.386
.model flat

; ??1Weapon@@MAE@XZ
; Exact 111 retail bytes @ 0x001E5490.
; Identity: allocateNewWeapon (0x1BDD90) -> ctor 0x1E52D0 stores vtbl 0x10A13F4;
; vtbl slot0 scalar-deleting dtor 0x1E6900 calls this body; m_scatterTargets at +0x40.
_TEXT SEGMENT
public ??1Weapon@@MAE@XZ
??1Weapon@@MAE@XZ PROC
    db 6Ah,0FFh,68h,0A8h,0A1h,00h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh
    db 0F1h,89h,74h,24h,04h,0C7h,06h,0F4h
    db 13h,0Ah,01h,8Bh,4Eh,40h,85h,0C9h
    db 0C7h,44h,24h,10h,00h,00h,00h,00h
    db 74h,27h,8Bh,46h,48h,2Bh,0C1h,0C1h
    db 0F8h,02h,0C1h,0E0h,02h,3Dh,80h,00h
    db 00h,00h,76h,0Bh,51h,0E8h,0D6h,0C9h
    db 69h,00h,83h,0C4h,04h,0EBh,0Ah,50h
    db 51h,0E8h,0Ah,91h,64h,00h,83h,0C4h
    db 08h,8Bh,4Ch,24h,08h,0C7h,06h,44h
    db 37h,07h,01h,5Eh,64h,89h,0Dh,00h
    db 00h,00h,00h,83h,0C4h,10h,0C3h
??1Weapon@@MAE@XZ ENDP
_TEXT ENDS
END
