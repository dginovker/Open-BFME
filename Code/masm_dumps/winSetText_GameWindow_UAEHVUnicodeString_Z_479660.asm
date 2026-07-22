.386
.model flat

; ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
; Exact 114 retail bytes @ 0x00479660
; True body: SEH + UnicodeString copy + setText@WinInstanceData (m_instData+0x30)
; + optional BFME notify via [this+4] vtbl slot +0xC; ret 0 / ret 4.
; Queue 0x006EF270 was INSIDE mega-fn ending 0x6EF2DF (not this symbol).
; Prior drift 0x43E537 was mid UnicodeString thunk. winGetInstanceData proves
; m_instData@+0x30 (0x478C60). Sibling winSetTooltip@0x4796F0 calls setTooltipText.
; C++ blocked: ZH lacks [this+4] notify; m_instData offset +0x30 vs ZH +0x2c
; (header layout systemic); setText itself is MASM due to DisplayString vtbl.
_TEXT SEGMENT
public ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
?winSetText@GameWindow@@UAEHVUnicodeString@@@Z PROC
    db 6Ah,0FFh,68h,58h,64h,02h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh,0F1h,51h,8Dh,44h,24h,1Ch,89h,64h
    db 24h,08h,8Bh,0CCh,50h,0C7h,44h,24h,18h,00h,00h,00h,00h,0E8h,6Eh,0EDh
    db 40h,00h,8Dh,4Eh,30h,0E8h,6Bh,0ABh,0B8h,0FFh,8Bh,46h,04h,85h,0C0h,74h
    db 0Ch,8Bh,0C8h,8Bh,11h,8Dh,44h,24h,18h,50h,0FFh,52h,0Ch,8Dh,4Ch,24h
    db 18h,0C7h,44h,24h,10h,0FFh,0FFh,0FFh,0FFh,0E8h,12h,0EBh,40h,00h,8Bh,4Ch
    db 24h,08h,33h,0C0h,64h,89h,0Dh,00h,00h,00h,00h,5Eh,83h,0C4h,10h,0C2h
    db 04h,00h
?winSetText@GameWindow@@UAEHVUnicodeString@@@Z ENDP
_TEXT ENDS
END
