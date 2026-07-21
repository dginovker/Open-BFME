.386
.model flat

; ??0FloatingTextData@@QAE@XZ
; Retail @ 0x0043F4D0 size 101
; Proven via addFloatingText @ 0x004435A0: push 0x24; global operator new;
; call ILT 0xCD88 -> this body. Fills color/pos/text/dString/timeout into list+0x1298.
; Drift 0x009DB099 was INSIDE a subtitle parser (not this ctor).
_TEXT SEGMENT
public ??0FloatingTextData@@QAE@XZ
??0FloatingTextData@@QAE@XZ PROC
    db 6Ah,0FFh,68h,0Bh,2Ah,02h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh
    db 0F1h,8Dh,4Eh,08h,33h,0C0h,0C7h,06h
    db 0C8h,58h,0Fh,01h,89h,74h,24h,04h
    db 89h,01h,89h,46h,04h,89h,46h,20h
    db 89h,46h,1Ch,89h,44h,24h,10h,89h
    db 46h,10h,89h,46h,14h,89h,46h,18h
    db 0E8h,0BBh,8Ch,44h,00h,8Bh,0Dh,0CCh
    db 12h,2Fh,01h,8Bh,01h,0FFh,50h,24h
    db 8Bh,4Ch,24h,08h,89h,46h,0Ch,8Bh
    db 0C6h,5Eh,64h,89h,0Dh,00h,00h,00h
    db 00h,83h,0C4h,10h,0C3h
??0FloatingTextData@@QAE@XZ ENDP
_TEXT ENDS
END
