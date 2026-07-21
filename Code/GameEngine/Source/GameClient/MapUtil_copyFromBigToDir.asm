.386
.model flat

; ?copyFromBigToDir@@YAXABVAsciiString@@0@Z
; Exact 303 retail bytes @ 0x004508D0 (after int3 pad; ret@0x4509DE + throw tail).
; Drift queue 0x00ABFB2C is INSIDE an unrelated W3D/allocator body (starts with
; or [ecx+24],-1 / pop es garbage) — not this helper. Identity: unique
; openFile(READ|BINARY=0x41) then openFile(WRITE|CREATE|BINARY=0x4A) pair,
; seek END/START, new[]/read/close/write/close/delete[]. C++ blocked by
; File vtable seek@+0x14 vs ZH +0x18, AsciiString::str +8 vs ZH +4, and
; throw-helper shape (0x9d6220+0x9f6d00).
_TEXT SEGMENT
public ?copyFromBigToDir@@YAXABVAsciiString@@0@Z
?copyFromBigToDir@@YAXABVAsciiString@@0@Z PROC
    db 8Bh,00h,83h,0ECh,08h,85h,0C0h,74h
    db 05h,83h,0C0h,08h,0EBh,05h,0B8h,8Bh
    db 38h,07h,01h,8Bh,0Dh,48h,0CBh,34h
    db 01h,56h,6Ah,41h,50h,0E8h,6Eh,7Fh
    db 57h,00h,8Bh,0F0h,85h,0F6h,75h,1Fh
    db 50h,8Dh,4Ch,24h,08h,6Ah,05h,51h
    db 0E8h,1Bh,59h,58h,00h,83h,0C4h,0Ch
    db 68h,5Ch,0FEh,1Dh,01h,8Dh,54h,24h
    db 08h,52h,0E8h,0E9h,63h,5Ah,00h,8Bh
    db 06h,53h,57h,6Ah,02h,6Ah,00h,8Bh
    db 0CEh,0FFh,50h,14h,8Bh,16h,6Ah,00h
    db 6Ah,00h,8Bh,0CEh,8Bh,0F8h,0FFh,52h
    db 14h,57h,0E8h,39h,16h,43h,00h,8Bh
    db 0D8h,83h,0C4h,04h,85h,0DBh,75h,1Fh
    db 50h,8Dh,44h,24h,10h,6Ah,05h,50h
    db 0E8h,0D3h,58h,58h,00h,83h,0C4h,0Ch
    db 68h,5Ch,0FEh,1Dh,01h,8Dh,4Ch,24h
    db 10h,51h,0E8h,0A1h,63h,5Ah,00h,8Bh
    db 16h,57h,53h,8Bh,0CEh,0FFh,52h,0Ch
    db 3Bh,0C7h,7Dh,20h,6Ah,00h,8Dh,44h
    db 24h,10h,6Ah,05h,50h,0E8h,0A6h,58h
    db 58h,00h,83h,0C4h,0Ch,68h,5Ch,0FEh
    db 1Dh,01h,8Dh,4Ch,24h,10h,51h,0E8h
    db 74h,63h,5Ah,00h,8Bh,16h,8Bh,0CEh
    db 0FFh,52h,08h,8Bh,44h,24h,18h,8Bh
    db 00h,85h,0C0h,74h,05h,83h,0C0h,08h
    db 0EBh,05h,0B8h,8Bh,38h,07h,01h,8Bh
    db 0Dh,48h,0CBh,34h,01h,6Ah,4Ah,50h
    db 0E8h,0ABh,7Eh,57h,00h,8Bh,0F0h,85h
    db 0F6h,74h,24h,8Bh,16h,57h,53h,8Bh
    db 0CEh,0FFh,52h,10h,3Bh,0C7h,7Ch,17h
    db 8Bh,06h,8Bh,0CEh,0FFh,50h,08h,53h
    db 0E8h,1Bh,15h,43h,00h,83h,0C4h,04h
    db 5Fh,5Bh,5Eh,83h,0C4h,08h,0C3h,6Ah
    db 00h,8Dh,4Ch,24h,10h,6Ah,05h,51h
    db 0E8h,33h,58h,58h,00h,83h,0C4h,0Ch
    db 68h,5Ch,0FEh,1Dh,01h,8Dh,54h,24h
    db 10h,52h,0E8h,01h,63h,5Ah,00h
?copyFromBigToDir@@YAXABVAsciiString@@0@Z ENDP
_TEXT ENDS
END
