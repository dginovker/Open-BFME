.386
.model flat

; ?PopupReplayUpdate@@YAXPAVWindowLayout@@PAX@Z
; Exact 90 retail bytes @ 0x004DE180; BFME uses virtual WindowLayout::hide.
_TEXT SEGMENT
public ?PopupReplayUpdate@@YAXPAVWindowLayout@@PAX@Z
?PopupReplayUpdate@@YAXPAVWindowLayout@@PAX@Z PROC
    db 0A1h,064h,040h,02Fh,001h,085h,0C0h,074h
    db 050h,0FFh,015h,044h,095h,035h,001h,02Bh
    db 005h,064h,040h,02Fh,001h,03Dh,0E8h,003h
    db 000h,000h,072h,03Dh,08Bh,00Dh,060h,040h
    db 02Fh,001h,085h,0C9h,074h,007h,06Ah,001h
    db 0E8h,07Dh,09Dh,0B4h,0FFh,08Bh,00Dh,05Ch
    db 040h,02Fh,001h,0E8h,03Dh,021h,0B6h,0FFh
    db 085h,0C0h,074h,009h,08Bh,010h,06Ah,001h
    db 08Bh,0C8h,0FFh,052h,010h,06Ah,001h,0E8h
    db 057h,098h,0B6h,0FFh,083h,0C4h,004h,0C7h
    db 005h,064h,040h,02Fh,001h,000h,000h,000h
    db 000h,0C3h
?PopupReplayUpdate@@YAXPAVWindowLayout@@PAX@Z ENDP
_TEXT ENDS
END
