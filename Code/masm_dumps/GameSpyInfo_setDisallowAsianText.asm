.386
.model flat

; ?setDisallowAsianText@GameSpyInfo@@UAEX_N@Z
; Exact 13 retail bytes @ 0x00A30760; stores the BFME-layout flag at offset 0x244.
_TEXT SEGMENT
public ?setDisallowAsianText@GameSpyInfo@@UAEX_N@Z
?setDisallowAsianText@GameSpyInfo@@UAEX_N@Z PROC
    db 08Ah,044h,024h,004h,088h,081h,044h,002h,000h,000h,0C2h,004h,000h
?setDisallowAsianText@GameSpyInfo@@UAEX_N@Z ENDP
_TEXT ENDS
END
