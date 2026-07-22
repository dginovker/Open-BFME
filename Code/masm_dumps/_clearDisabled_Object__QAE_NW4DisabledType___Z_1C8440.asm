.386
.model flat

; ?clearDisabled@Object@@QAE_NW4DisabledType@@@Z
; Exact 492 retail bytes @ 0x001C8440
; Identity: immediately after setDisabledUntil body @ 0x1C81C0; ret 4 Bool;
; DISABLED_COUNT=0x0B range check; inline m_disabledMask bit test @+0x1a4;
; EMP/UNDERPOWERED re-enable audio; pauseAllSpecialPowers; contain rider clear;
; clear frame@+0x1a8 + mask; tint exceptions 0x228; checkDisabledStatus;
; onDisabledEdge(false) via ILT 0x45430. Queue RVA 0xFB36E was misplaced (wrong TU).
_TEXT SEGMENT
public ?clearDisabled@Object@@QAE_NW4DisabledType@@@Z
?clearDisabled@Object@@QAE_NW4DisabledType@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,68h,90h,00h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,78h,56h,57h,8Bh,0BCh,24h,90h,00h,00h
    db 00h,85h,0FFh,8Bh,0F1h,0Fh,8Ch,0BAh,01h,00h,00h,83h,0FFh,0Bh,0Fh,8Dh
    db 0B1h,01h,00h,00h,8Bh,86h,0A4h,01h,00h,00h,53h,8Bh,0CFh,83h,0E1h,1Fh
    db 0BBh,01h,00h,00h,00h,0D3h,0E3h,85h,0D8h,75h,1Ch,32h,0C0h,5Bh,8Bh,8Ch
    db 24h,80h,00h,00h,00h,5Fh,5Eh,64h,89h,0Dh,00h,00h,00h,00h,81h,0C4h
    db 84h,00h,00h,00h,0C2h,04h,00h,83h,0FFh,06h,74h,09h,83h,0FFh,02h,0Fh
    db 85h,0C2h,00h,00h,00h,6Ah,00h,68h,50h,6Eh,33h,01h,8Dh,4Ch,24h,1Ch
    db 0E8h,41h,0CEh,0E5h,0FFh,8Bh,86h,0A4h,01h,00h,00h,0A8h,40h,0C7h,84h,24h
    db 8Ch,00h,00h,00h,00h,00h,00h,00h,74h,09h,83h,0FFh,06h,0Fh,85h,80h
    db 00h,00h,00h,0A8h,04h,74h,05h,83h,0FFh,02h,75h,77h,6Ah,07h,8Bh,0CEh
    db 0E8h,2Ah,0A0h,0E6h,0FFh,84h,0C0h,74h,23h,8Bh,0Dh,68h,0D6h,2Eh,01h,8Bh
    db 01h,0FFh,90h,24h,01h,00h,00h,05h,90h,06h,00h,00h,50h,8Dh,4Ch,24h
    db 18h,0E8h,3Dh,72h,0E5h,0FFh,8Dh,4Eh,38h,51h,0EBh,2Eh,6Ah,09h,8Bh,0CEh
    db 0E8h,0FAh,9Fh,0E6h,0FFh,84h,0C0h,74h,3Ah,8Bh,0Dh,68h,0D6h,2Eh,01h,8Bh
    db 11h,0FFh,92h,24h,01h,00h,00h,05h,70h,07h,00h,00h,50h,8Dh,4Ch,24h
    db 18h,0E8h,0Dh,72h,0E5h,0FFh,8Dh,46h,38h,50h,8Dh,4Ch,24h,18h,0E8h,35h
    db 99h,0E3h,0FFh,8Bh,0Dh,68h,0D6h,2Eh,01h,8Bh,11h,8Dh,44h,24h,14h,50h
    db 0FFh,52h,44h,8Dh,4Ch,24h,14h,0C7h,84h,24h,8Ch,00h,00h,00h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,0BEh,0E9h,0E5h,0FFh,83h,0FFh,03h,74h,11h,85h,9Eh,0A4h,01h
    db 00h,00h,74h,09h,6Ah,00h,8Bh,0CEh,0E8h,84h,0B8h,0E5h,0FFh,8Bh,8Eh,0FCh
    db 01h,00h,00h,85h,0C9h,74h,21h,8Bh,11h,0FFh,92h,0Ch,01h,00h,00h,85h
    db 0C0h,74h,15h,81h,0BCh,0BEh,0A8h,01h,00h,00h,0FFh,0FFh,0FFh,3Fh,75h,08h
    db 57h,8Bh,0C8h,0E8h,0B2h,3Ah,0E7h,0FFh,0C7h,84h,0BEh,0A8h,01h,00h,00h,00h
    db 00h,00h,00h,8Bh,86h,0A4h,01h,00h,00h,0F7h,0D3h,23h,0C3h,89h,86h,0A4h
    db 01h,00h,00h,0C7h,44h,24h,0Ch,28h,02h,00h,00h,74h,16h,89h,44h,24h
    db 10h,8Dh,44h,24h,0Ch,50h,8Dh,4Ch,24h,14h,0E8h,03h,83h,0E4h,0FFh,85h
    db 0C0h,75h,11h,8Bh,8Eh,80h,00h,00h,00h,85h,0C9h,74h,07h,6Ah,01h,0E8h
    db 8Ah,0B6h,0E7h,0FFh,8Bh,0CEh,0E8h,54h,42h,0E5h,0FFh,8Bh,86h,0A4h,01h,00h
    db 00h,85h,0C0h,75h,09h,6Ah,00h,8Bh,0CEh,0E8h,12h,0CEh,0E7h,0FFh,0B0h,01h
    db 0E9h,68h,0FEh,0FFh,0FFh,32h,0C0h,0E9h,62h,0FEh,0FFh,0FFh
?clearDisabled@Object@@QAE_NW4DisabledType@@@Z ENDP
_TEXT ENDS
END
