.386
.model flat

; ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
; Exact 124 retail bytes @ 0x005BAD80; C++ blocked because BFME's AsciiString
; copy-ctor/dtor are out-of-line (TheEmptyString guard static), ours inline.
_TEXT SEGMENT
public ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
??0Anim2DTemplate@@QAE@VAsciiString@@@Z PROC
    db 06Ah,0FFh,068h,093h,093h,003h,001h,064h
    db 0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,053h,056h
    db 08Bh,0F1h,089h,074h,024h,008h,033h,0DBh
    db 08Dh,04Eh,008h,0C7h,006h,0B8h,0F2h,010h
    db 001h,089h,05Ch,024h,014h,089h,019h,08Dh
    db 044h,024h,01Ch,050h,0C6h,044h,024h,018h
    db 001h,0E8h,0D2h,0CEh,02Ch,000h,08Dh,04Ch
    db 024h,01Ch,089h,05Eh,00Ch,066h,089h,05Eh
    db 010h,066h,089h,05Eh,012h,0C7h,046h,014h
    db 003h,000h,000h,000h,088h,05Eh,018h,089h
    db 05Eh,004h,0C7h,044h,024h,014h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,059h,0CBh,02Ch,000h,08Bh
    db 04Ch,024h,00Ch,08Bh,0C6h,05Eh,05Bh,064h
    db 089h,00Dh,000h,000h,000h,000h,083h,0C4h
    db 010h,0C2h,004h,000h
??0Anim2DTemplate@@QAE@VAsciiString@@@Z ENDP
_TEXT ENDS

; ??1Anim2DTemplate@@UAE@XZ
; Exact 34 retail bytes @ 0x005BAE20; same AsciiString wall as the ctor.
_TEXT SEGMENT
public ??1Anim2DTemplate@@UAE@XZ
??1Anim2DTemplate@@UAE@XZ PROC
    db 056h,08Bh,0F1h,08Bh,046h,00Ch,085h,0C0h
    db 0C7h,006h,0B8h,0F2h,010h,001h,074h,009h
    db 050h,0E8h,0BAh,070h,02Ch,000h,083h,0C4h
    db 004h,08Dh,04Eh,008h,05Eh,0E9h,0FEh,0CAh
    db 02Ch,000h
??1Anim2DTemplate@@UAE@XZ ENDP
_TEXT ENDS

END
