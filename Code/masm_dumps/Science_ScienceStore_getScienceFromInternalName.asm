.386
.model flat

; ?getScienceFromInternalName@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z
; Exact 41 retail bytes @ 0x000E7460; ILT thunk 0x4B36C; queue 0x79CEEC was mid-handler.
; Empty AsciiString -> SCIENCE_INVALID (-1); else tail-jmp nameToKey(m_data+8).
_TEXT SEGMENT
public ?getScienceFromInternalName@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z
?getScienceFromInternalName@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z PROC
    db 08Bh,044h,024h,004h,08Bh,000h,085h,0C0h
    db 074h,007h,066h,083h,078h,004h,000h,075h
    db 006h,083h,0C8h,0FFh,0C2h,004h,000h,08Bh
    db 00Dh,000h,0D6h,02Eh,001h,083h,0C0h,008h
    db 089h,044h,024h,004h,0E9h,04Eh,039h,0F5h
    db 0FFh
?getScienceFromInternalName@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z ENDP
_TEXT ENDS
END
