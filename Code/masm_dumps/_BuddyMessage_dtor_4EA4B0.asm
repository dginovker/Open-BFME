.386
.model flat

; ??1BuddyMessage@@QAE@XZ
; Exact 90B retail @ 0x004EA4B0; true body via ??_GBuddyMessage@0x4EA8F0 -> ILT 0x21445.
; Queue 0x9DB0B4 was INSIDE unrelated fn (mid-instr 0x38 of mov eax,[esp+38]).
; Dtor: SEH + releaseBuffer@StringBase<wchar> @+0x14, Ascii @+0x10/@+0x8.
_TEXT SEGMENT
public ??1BuddyMessage@@QAE@XZ
??1BuddyMessage@@QAE@XZ PROC
    db 6Ah,0FFh,68h,36h,0BBh,02h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh,0F1h,89h,74h,24h,04h,8Dh,4Eh,14h
    db 0C7h,44h,24h,10h,01h,00h,00h,00h,0E8h,0F3h,0DCh,39h,00h,8Dh,4Eh,10h
    db 0C6h,44h,24h,10h,00h,0E8h,56h,0D4h,39h,00h,8Dh,4Eh,08h,0C7h,44h,24h
    db 10h,0FFh,0FFh,0FFh,0FFh,0E8h,46h,0D4h,39h,00h,8Bh,4Ch,24h,08h,5Eh,64h
    db 89h,0Dh,00h,00h,00h,00h,83h,0C4h,10h,0C3h
??1BuddyMessage@@QAE@XZ ENDP
_TEXT ENDS
END
