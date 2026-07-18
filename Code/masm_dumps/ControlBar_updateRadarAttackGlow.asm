.386
.model flat

; ?updateRadarAttackGlow@ControlBar@@IAEXXZ
; Exact 102 retail bytes @ RVA 0x0049D370; radar-attack glow update
_TEXT SEGMENT
public ?updateRadarAttackGlow@ControlBar@@IAEXXZ
?updateRadarAttackGlow@ControlBar@@IAEXXZ PROC
    db 056h,08Bh,0F1h,08Ah,086h,0E0h,002h,000h,000h,084h,0C0h,074h,057h,08Bh,08Eh,0E8h
    db 002h,000h,000h,085h,0C9h,074h,04Dh,057h,08Bh,0BEh,0E4h,002h,000h,000h,04Fh,08Bh
    db 0C7h,085h,0C0h,089h,0BEh,0E4h,002h,000h,000h,07Fh,011h,06Ah,001h,0C6h,086h,0E0h
    db 002h,000h,000h,000h,0E8h,052h,0CEh,0BAh,0FFh,05Fh,05Eh,0C3h,099h,0BFh,00Fh,000h
    db 000h,000h,0F7h,0FFh,085h,0D2h,075h,01Bh,0E8h,01Dh,06Ah,0B8h,0FFh,08Bh,08Eh,0E8h
    db 002h,000h,000h,0C1h,0E8h,003h,0F6h,0D0h,025h,001h,0FFh,0FFh,0FFh,050h,0E8h,028h
    db 0CEh,0BAh,0FFh,05Fh,05Eh,0C3h
?updateRadarAttackGlow@ControlBar@@IAEXXZ ENDP
_TEXT ENDS
END
