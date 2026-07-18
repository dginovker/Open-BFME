.386
.model flat

; ?clearAdditionalDisconnects@GameSpyInfo@@UAEXXZ
; Exact 11 retail bytes @ 0x00A30680; clears the BFME-layout count at offset 0x6F8.
_TEXT SEGMENT
public ?clearAdditionalDisconnects@GameSpyInfo@@UAEXXZ
?clearAdditionalDisconnects@GameSpyInfo@@UAEXXZ PROC
    db 0C7h,081h,0F8h,006h,000h,000h,000h,000h,000h,000h,0C3h
?clearAdditionalDisconnects@GameSpyInfo@@UAEXXZ ENDP
_TEXT ENDS
END
