.386
.model flat

; ??0?$pair@$$CBJVLadderPref@@@_STL@@QAE@ABJABVLadderPref@@@Z
; Exact 30 retail bytes @ 0x000A9D50 (ICF with other pair two-arg ctors).
; Structural queue RVA 0x0081D759 is 7x INT3 pad before an unrelated 74B
; multi-arg ctor (vtable store + ret 0x1c). True body proven via
; LadderPref copy thunk 0x48329 callers: two-arg pair loads key/value refs,
; stores *key, calls LadderPref copy into this+4, ret 8.
_TEXT SEGMENT
public ??0?$pair@$$CBJVLadderPref@@@_STL@@QAE@ABJABVLadderPref@@@Z
??0?$pair@$$CBJVLadderPref@@@_STL@@QAE@ABJABVLadderPref@@@Z PROC
    db 8Bh,44h,24h,04h,8Bh,54h,24h,08h
    db 56h,8Bh,0F1h,8Bh,08h,89h,0Eh,52h
    db 8Dh,4Eh,04h,0E8h,0C1h,0E5h,0F9h,0FFh
    db 8Bh,0C6h,5Eh,0C2h,08h,00h
??0?$pair@$$CBJVLadderPref@@@_STL@@QAE@ABJABVLadderPref@@@Z ENDP
_TEXT ENDS
END
