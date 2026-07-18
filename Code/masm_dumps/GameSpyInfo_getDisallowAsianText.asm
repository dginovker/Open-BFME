.386
.model flat

; ?getDisallowAsianText@GameSpyInfo@@UAE_NXZ
; Exact 7 retail bytes @ 0x00A30780; returns the BFME-layout flag at offset 0x244.
_TEXT SEGMENT
public ?getDisallowAsianText@GameSpyInfo@@UAE_NXZ
?getDisallowAsianText@GameSpyInfo@@UAE_NXZ PROC
    db 08Ah,081h,044h,002h,000h,000h,0C3h
?getDisallowAsianText@GameSpyInfo@@UAE_NXZ ENDP
_TEXT ENDS
END
