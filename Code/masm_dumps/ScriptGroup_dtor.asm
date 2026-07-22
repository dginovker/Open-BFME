.386
.model flat

; ??1ScriptGroup@@MAE@XZ
; Exact 71 retail bytes @ 0x00352950.
; Identity: class vtbl 0x10E855C (slots then "ScriptGroup" string @ 0x10E8570);
; ctor @ 0x352900 installs that vtbl; getName/getClass @ 0x352940 returns
; "ScriptGroup"; scalar-deleting dtor ILT 0x428718 -> body 0x355C30 calls this
; via ILT 0x4998B. BFME layout is 0x10 bytes (no ZH Script-list walk); retail
; frees owned ptrs at +8 then +4 then returns. Queue RVA 0x9F2799 is MISPLACED
; (INSIDE already-matched ??0ControlBar@@QAE@XZ @ 0x9F2730 size 146).
_TEXT SEGMENT
public ??1ScriptGroup@@MAE@XZ
??1ScriptGroup@@MAE@XZ PROC
    db 56h,8Bh,0F1h,57h,0C7h,06h,44h,37h
    db 07h,01h,8Bh,7Eh,08h,85h,0FFh,74h
    db 16h,8Bh,0Fh,85h,0C9h,74h,07h,6Ah
    db 01h,0E8h,0CAh,0F9h,0CAh,0FFh,57h,0E8h
    db 3Ch,0F5h,52h,00h,83h,0C4h,04h,8Bh
    db 76h,04h,85h,0F6h,74h,16h,8Bh,0Eh
    db 85h,0C9h,74h,07h,6Ah,01h,0E8h,0AEh
    db 0F6h,0CCh,0FFh,56h,0E8h,1Fh,0F5h,52h
    db 00h,83h,0C4h,04h,5Fh,5Eh,0C3h
??1ScriptGroup@@MAE@XZ ENDP
_TEXT ENDS
END
