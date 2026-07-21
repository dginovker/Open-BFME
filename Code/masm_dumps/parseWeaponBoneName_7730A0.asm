.386
.model flat

; ?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z
; Exact 161 retail bytes @ 0x007730A0
; FieldParse table WeaponFireFXBone/WeaponLaunchBone/... all point here (VA 0xB730A0).
; Drift queue 0x880440 was a different 59B thiscall; true body is 161B here.
_TEXT SEGMENT
public ?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z
?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z PROC
    db 06Ah,0FFh,068h,068h,0F9h,004h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,056h,08Bh,074h,024h,018h,057h,068h,078h,0D6h,02Ah
    db 001h,06Ah,000h,08Bh,0CEh,0E8h,0A6h,0D8h,00Dh,000h,050h,0E8h,010h,0D9h,00Dh,000h
    db 08Bh,0F8h,083h,0C4h,008h,08Dh,044h,024h,008h,050h,08Bh,0CEh,0E8h,0FFh,0E5h,00Dh
    db 000h,08Bh,04Ch,024h,024h,08Dh,034h,0B9h,050h,08Bh,0CEh,0C7h,044h,024h,018h,000h
    db 000h,000h,000h,0E8h,098h,04Bh,011h,000h,08Dh,04Ch,024h,008h,0C7h,044h,024h,014h
    db 0FFh,0FFh,0FFh,0FFh,0E8h,037h,048h,011h,000h,08Bh,0CEh,0E8h,090h,04Ch,011h,000h
    db 08Bh,0CEh,0E8h,089h,050h,011h,000h,084h,0C0h,074h,007h,08Bh,0CEh,0E8h,01Eh,048h
    db 011h,000h,08Bh,04Ch,024h,020h,085h,0C9h,074h,006h,056h,0E8h,09Dh,02Ah,089h,0FFh
    db 08Bh,04Ch,024h,00Ch,05Fh,05Eh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,010h
    db 0C3h
?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
