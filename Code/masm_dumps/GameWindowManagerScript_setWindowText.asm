.386
.model flat

; ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z
; Exact 416 retail bytes @ 0x004864E0 (queue 0x004864C7 was int3 pad).
; Identity: sole caller @ 0x4875B3 (createWindow) does AsciiString copy
; then call; body is fetch + GWS bit tests + Gadget*SetText/winSetText.
; C++ blocked: BFME AsciiString isEmpty is cmp word [m_data+4],0 and
; str is m_data+8; ZH GameEngine AsciiString peeks first char / +4 data.
_TEXT SEGMENT
public ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z
?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z PROC
    db 6Ah, 0FFh, 68h, 40h, 6Ah, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 57h, 8Bh, 44h, 24h, 24h, 33h, 0D2h, 3Bh
    db 0C2h, 89h, 54h, 24h, 1Ch, 0Fh, 84h, 54h, 01h, 00h, 00h, 66h, 39h, 50h, 04h, 0Fh
    db 84h, 4Ah, 01h, 00h, 00h, 89h, 54h, 24h, 04h, 89h, 54h, 24h, 08h, 8Bh, 0Dh, 7Ch
    db 14h, 2Fh, 01h, 8Bh, 39h, 83h, 0C0h, 08h, 52h, 50h, 8Dh, 44h, 24h, 14h, 50h, 0C6h
    db 44h, 24h, 28h, 02h, 0FFh, 57h, 28h, 50h, 8Dh, 4Ch, 24h, 08h, 0C6h, 44h, 24h, 20h
    db 03h, 0E8h, 0EAh, 1Fh, 40h, 00h, 8Dh, 4Ch, 24h, 0Ch, 0C6h, 44h, 24h, 1Ch, 02h, 0E8h
    db 7Ch, 1Ch, 40h, 00h, 8Bh, 0CEh, 0E8h, 0F7h, 25h, 0B8h, 0FFh, 0A8h, 01h, 74h, 1Fh, 51h
    db 8Dh, 54h, 24h, 08h, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 52h, 0E8h, 90h, 1Eh, 40h, 00h
    db 56h, 0E8h, 7Bh, 0BFh, 0BBh, 0FFh, 83h, 0C4h, 08h, 0E9h, 0C5h, 00h, 00h, 00h, 8Bh, 0CEh
    db 0E8h, 0CDh, 25h, 0B8h, 0FFh, 0A8h, 02h, 74h, 1Fh, 51h, 8Dh, 44h, 24h, 08h, 89h, 64h
    db 24h, 14h, 8Bh, 0CCh, 50h, 0E8h, 66h, 1Eh, 40h, 00h, 56h, 0E8h, 8Bh, 3Fh, 0BBh, 0FFh
    db 83h, 0C4h, 08h, 0E9h, 9Bh, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0A3h, 25h, 0B8h, 0FFh, 0A8h
    db 04h, 74h, 1Ch, 51h, 8Dh, 54h, 24h, 08h, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 52h, 0E8h
    db 3Ch, 1Eh, 40h, 00h, 56h, 0E8h, 77h, 1Ch, 0B9h, 0FFh, 83h, 0C4h, 08h, 0EBh, 74h, 8Bh
    db 0CEh, 0E8h, 7Ch, 25h, 0B8h, 0FFh, 84h, 0C0h, 79h, 1Ch, 51h, 8Dh, 44h, 24h, 08h, 89h
    db 64h, 24h, 14h, 8Bh, 0CCh, 50h, 0E8h, 15h, 1Eh, 40h, 00h, 56h, 0E8h, 7Eh, 5Bh, 0BAh
    db 0FFh, 83h, 0C4h, 08h, 0EBh, 4Dh, 8Bh, 0CEh, 0E8h, 55h, 25h, 0B8h, 0FFh, 0A8h, 40h, 74h
    db 2Ah, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0E1h, 2Bh, 40h, 00h, 51h
    db 8Dh, 54h, 24h, 0Ch, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 52h, 0E8h, 0E0h, 1Dh, 40h, 00h
    db 56h, 0E8h, 4Eh, 62h, 0B8h, 0FFh, 83h, 0C4h, 08h, 0EBh, 18h, 51h, 8Dh, 44h, 24h, 08h
    db 89h, 64h, 24h, 14h, 8Bh, 0CCh, 50h, 0E8h, 0C4h, 1Dh, 40h, 00h, 8Bh, 0CEh, 0E8h, 0F0h
    db 35h, 0BCh, 0FFh, 8Dh, 4Ch, 24h, 08h, 0C6h, 44h, 24h, 1Ch, 01h, 0E8h, 7Fh, 1Bh, 40h
    db 00h, 8Dh, 4Ch, 24h, 04h, 0C6h, 44h, 24h, 1Ch, 00h, 0E8h, 71h, 1Bh, 40h, 00h, 8Dh
    db 4Ch, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D0h, 12h, 40h, 00h
    db 8Bh, 4Ch, 24h, 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 83h, 0C4h, 1Ch, 0C3h
?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
