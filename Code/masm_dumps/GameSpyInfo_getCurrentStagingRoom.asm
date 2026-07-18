.386
.model flat

; ?getCurrentStagingRoom@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@XZ
; Exact 72 retail bytes @ 0x00A327B0; returns the BFME-layout current staging room.
_TEXT SEGMENT
public ?getCurrentStagingRoom@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@XZ
?getCurrentStagingRoom@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@XZ PROC
    db 051h,08Ah,081h,058h,002h,000h,000h,084h,0C0h,075h,035h,08Bh,091h,054h,002h,000h
    db 000h,085h,0D2h,08Dh,081h,054h,002h,000h,000h,075h,025h,056h,050h,08Dh,071h,024h
    db 08Dh,044h,024h,008h,050h,08Bh,0CEh,0E8h,030h,071h,09Eh,0FFh,08Bh,00Eh,08Bh,044h
    db 024h,004h,03Bh,0C1h,05Eh,074h,005h,08Bh,040h,014h,059h,0C3h,033h,0C0h,059h,0C3h
    db 08Dh,081h,05Ch,002h,000h,000h,059h,0C3h
?getCurrentStagingRoom@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@XZ ENDP
_TEXT ENDS
END
