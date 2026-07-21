.386
.model flat

; ??1ScriptConditions@@UAE@XZ
; Exact 106 retail bytes @ 0x003244B0.
; Identity: ctor @ 0x324490 (empty derived SubsystemInterface + vtbl 0x10E1F44)
; allocated size 8 next to ScriptActions in ScriptEngine init; vtable slot0
; scalar-deleting dtor @ 0x324570 calls this body; cleans s_transportStatuses
; global @ 0x12F06AC then base SubsystemInterface dtor @ 0x9A1A40.
; Queue RVA 0x9F27F1 was misplaced (PartitionManager getName stub + pad +
; already-matched PartitionManager dtor @ 0x9F2800).
_TEXT SEGMENT
public ??1ScriptConditions@@UAE@XZ
??1ScriptConditions@@UAE@XZ PROC
    db 6Ah,0FFh,68h,0A8h,6Eh,01h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh
    db 0F1h,89h,74h,24h,04h,0C7h,06h,44h
    db 1Fh,0Eh,01h,8Bh,0Dh,0ACh,06h,2Fh
    db 01h,85h,0C9h,0C7h,44h,24h,10h,00h
    db 00h,00h,00h,74h,06h,8Bh,01h,6Ah
    db 01h,0FFh,10h,8Bh,0CEh,0C7h,05h,0ACh
    db 06h,2Fh,01h,00h,00h,00h,00h,0C7h
    db 44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0C7h
    db 06h,0FCh,1Eh,0Eh,01h,0E8h,36h,0D5h
    db 67h,00h,8Bh,4Ch,24h,08h,5Eh,64h
    db 89h,0Dh,00h,00h,00h,00h,83h,0C4h
    db 10h,0C3h
??1ScriptConditions@@UAE@XZ ENDP
_TEXT ENDS
END
