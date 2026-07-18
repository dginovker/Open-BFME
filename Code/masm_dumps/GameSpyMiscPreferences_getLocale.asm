.386
.model flat

; ?getLocale@GameSpyMiscPreferences@@QAEHXZ
; Exact 33 retail bytes @ 0x004A99A0; reads the Locale preference with a zero default.
_TEXT SEGMENT
public ?getLocale@GameSpyMiscPreferences@@QAEHXZ
?getLocale@GameSpyMiscPreferences@@QAEHXZ PROC
    db 051h,056h,06Ah,000h,051h,08Bh,0F1h,089h,064h,024h,00Ch,08Bh,0CCh,068h,06Ch,00Fh
    db 008h,001h,0E8h,009h,0F2h,07Dh,000h,08Bh,0CEh,0E8h,0FBh,0A9h,0F9h,0FFh,05Eh,059h
    db 0C3h
?getLocale@GameSpyMiscPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
