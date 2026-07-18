.386
.model flat

; ??0MetaMapRec@@QAE@XZ
; Exact 11 retail bytes @ 0x009B7020; initializes the two UnicodeString handles in the 0x24-byte record.
_TEXT SEGMENT
public ??0MetaMapRec@@QAE@XZ
??0MetaMapRec@@QAE@XZ PROC
    db 8Bh,0C1h,33h,0C9h,89h,48h,1Ch,89h
    db 48h,20h,0C3h
??0MetaMapRec@@QAE@XZ ENDP
_TEXT ENDS
END
