.386
.model flat

; ?amIHost@GameSpyInfo@@UAE_NXZ
; Exact 7 retail bytes @ 0x00A30690; returns the BFME-layout host flag at offset 0x258.
_TEXT SEGMENT
public ?amIHost@GameSpyInfo@@UAE_NXZ
?amIHost@GameSpyInfo@@UAE_NXZ PROC
    db 08Ah,081h,058h,002h,000h,000h,0C3h
?amIHost@GameSpyInfo@@UAE_NXZ ENDP
_TEXT ENDS
END
