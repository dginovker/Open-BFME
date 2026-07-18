.386
.model flat

; ?getMaxMessagesPerUpdate@GameSpyMiscPreferences@@QAEHXZ
; Exact 33 retail bytes @ 0x004A9B30; reads MaxMessagesPerUpdate with a 100-message default.
_TEXT SEGMENT
public ?getMaxMessagesPerUpdate@GameSpyMiscPreferences@@QAEHXZ
?getMaxMessagesPerUpdate@GameSpyMiscPreferences@@QAEHXZ PROC
    db 051h,056h,06Ah,064h,051h,08Bh,0F1h,089h,064h,024h,00Ch,08Bh,0CCh,068h,084h,00Fh
    db 008h,001h,0E8h,079h,0F0h,07Dh,000h,08Bh,0CEh,0E8h,06Bh,0A8h,0F9h,0FFh,05Eh,059h
    db 0C3h
?getMaxMessagesPerUpdate@GameSpyMiscPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
