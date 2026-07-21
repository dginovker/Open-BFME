.386
.model flat

; ?isObjectShroudedForAction@@YA_NPBVObject@@0W4CommandSourceType@@@Z
; Exact 90B @ 0xC3F80; true ENTRY (queue 0xC3F94 was mid jle imm of BFME early-out).
; 10 ActionManager callers push only commandSource with edi=source esi=target.
; BFME early-out: if target+0x74 in [0x05F5E0FC,0x05F5E0FF] return false; then ZH shroud checks.
_TEXT SEGMENT
public ?isObjectShroudedForAction@@YA_NPBVObject@@0W4CommandSourceType@@@Z
?isObjectShroudedForAction@@YA_NPBVObject@@0W4CommandSourceType@@@Z PROC
    db 085h,0F6h,074h,011h,08Bh,046h,074h,03Dh,0FCh,0E0h,0F5h,005h,07Ch,007h,03Dh,0FFh
    db 0E0h,0F5h,005h,07Eh,042h,085h,0FFh,074h,03Eh,085h,0F6h,074h,03Ah,08Bh,0CFh,0E8h
    db 080h,0C8h,0F5h,0FFh,085h,0C0h,074h,02Fh,08Bh,0CFh,0E8h,075h,0C8h,0F5h,0FFh,08Bh
    db 048h,02Ch,085h,0C9h,075h,021h,083h,07Ch,024h,004h,001h,074h,01Ah,08Bh,0CFh,0E8h
    db 060h,0C8h,0F5h,0FFh,08Bh,040h,024h,050h,08Bh,0CEh,0E8h,04Fh,078h,0F6h,0FFh,083h
    db 0F8h,003h,07Ch,003h,0B0h,001h,0C3h,032h,0C0h,0C3h
?isObjectShroudedForAction@@YA_NPBVObject@@0W4CommandSourceType@@@Z ENDP
_TEXT ENDS
END
