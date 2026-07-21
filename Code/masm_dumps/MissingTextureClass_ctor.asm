.386
.model flat
; ??0MissingTextureClass@@QAE@PBD@Z
; Exact 125B @ 0x007B1050; proven via registerMissing thunk 0x42C3A -> body;
; sibling of matched ??0MissingAnimClass@0x7BB710 (DIR32 vtable/SEH + REL32 only);
; queue RVA 0x9723C0 was wrong (3-arg StringClass+base body, ret 0xC)
_TEXT SEGMENT
public ??0MissingTextureClass@@QAE@PBD@Z
??0MissingTextureClass@@QAE@PBD@Z PROC
    db 6Ah, 0FFh, 68h, 88h, 27h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 46h, 04h, 00h, 00h, 00h, 00h, 8Bh, 5Ch, 24h, 20h, 85h, 0DBh, 0C7h, 06h, 60h, 84h
    db 12h, 01h, 0A1h, 24h, 91h, 2Dh, 01h, 8Dh, 7Eh, 08h, 0C7h, 44h, 24h, 18h, 00h, 00h
    db 00h, 00h, 89h, 07h, 74h, 19h, 53h, 0FFh, 15h, 0Ch, 93h, 35h, 01h, 83h, 0C4h, 04h
    db 85h, 0C0h, 7Eh, 0Bh, 6Ah, 00h, 40h, 50h, 8Bh, 0CFh, 0E8h, 0E1h, 0A7h, 22h, 00h, 53h
    db 8Bh, 0CFh, 0E8h, 2Ch, 0F2h, 86h, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
??0MissingTextureClass@@QAE@PBD@Z ENDP
_TEXT ENDS
END
