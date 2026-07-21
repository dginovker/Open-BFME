.386
.model flat

; ?doNamedEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z
; Exact 66 retail bytes @ 0x002F04F0
; True body: getUnitNamed(vtbl+0x68) + getDrawable(vtbl+0x28) + setEmoticon@0x4149E0
; Queue 0x9DE812 was profiler float math (misplaced), not this action.
_TEXT SEGMENT
public ?doNamedEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z
?doNamedEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z PROC
    db 08Bh,00Dh,06Ch,007h,02Fh,001h,08Bh,054h,024h,004h,08Bh,001h,052h,0FFh,050h,068h
    db 085h,0C0h,074h,02Bh,08Bh,010h,056h,08Bh,0C8h,0FFh,052h,028h,08Bh,0F0h,085h,0F6h
    db 074h,01Ch,0D9h,044h,024h,010h,0D8h,00Dh,044h,053h,007h,001h,0E8h,017h,069h,070h
    db 000h,050h,08Bh,044h,024h,010h,050h,08Bh,0CEh,0E8h,00Eh,015h,0D1h,0FFh,05Eh,0C2h
    db 00Ch,000h
?doNamedEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z ENDP
_TEXT ENDS
END
