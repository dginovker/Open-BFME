.386
.model flat
; ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
; Exact 88B @ 0x0013E210; FieldParse AddModule table@0xC91720 thunk@0x4FAC
; True body not drift 0x9A15E8 (misplaced AsciiString ctor). C++ blocked by
; m_moduleParsingMode layout +0x498 vs ZH +0x237 + throw/stack shape.
_TEXT SEGMENT
public ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 74h, 24h, 14h, 0Fh, 0BEh, 86h, 98h, 04h, 00h, 00h, 85h
    db 0C0h, 74h, 23h, 68h, 0B0h, 40h, 09h, 01h, 8Dh, 44h, 24h, 08h, 6Ah, 03h, 50h, 0E8h
    db 0CCh, 23h, 71h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 08h
    db 51h, 0E8h, 0BAh, 8Ah, 8Bh, 00h, 8Bh, 4Ch, 24h, 10h, 68h, 0A0h, 10h, 09h, 01h, 56h
    db 0C6h, 86h, 98h, 04h, 00h, 00h, 01h, 0E8h, 44h, 3Eh, 71h, 00h, 0C6h, 86h, 98h, 04h
    db 00h, 00h, 00h, 5Eh, 83h, 0C4h, 08h, 0C3h
?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
