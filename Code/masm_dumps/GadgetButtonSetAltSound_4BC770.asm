.386
.model flat

; ?GadgetButtonSetAltSound@@YAXPAVGameWindow@@VAsciiString@@@Z
; True body @ 0x004BC770 size 90 (ILT 0xA3F3 from ControlBar GUIGenShortcutClick
; and GUICommandBarClick call sites). Queue RVA 0x009D2371 was a mid-function
; ret 0x10 epilogue (misplaced). C++ blocked: ZH AsciiString inline releaseBuffer
; expands param dtor at the call site; retail calls out-of-line CS-locked
; ??1AsciiString@@QAE@XZ @ 0x887940 and ??4AsciiString @ 0x887C90.
_TEXT SEGMENT
public ?GadgetButtonSetAltSound@@YAXPAVGameWindow@@VAsciiString@@@Z
?GadgetButtonSetAltSound@@YAXPAVGameWindow@@VAsciiString@@@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0D8h, 8Dh, 02h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h, 0C7h, 44h, 24h, 08h, 00h
    db 00h, 00h, 00h, 74h, 16h, 0E8h, 9Eh, 9Dh, 0B8h, 0FFh, 85h, 0C0h, 74h, 0Dh, 8Dh, 48h
    db 1Ch, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 0E5h, 0B4h, 3Ch, 00h, 8Dh, 4Ch, 24h, 14h, 0C7h
    db 44h, 24h, 08h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 84h, 0B1h, 3Ch, 00h, 8Bh, 0Ch, 24h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?GadgetButtonSetAltSound@@YAXPAVGameWindow@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
