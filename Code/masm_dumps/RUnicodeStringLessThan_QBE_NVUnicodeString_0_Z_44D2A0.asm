.386
.model flat

; ??RUnicodeStringLessThan@@QBE_NVUnicodeString@@0@Z
; Exact 95 retail bytes @ 0x0044D2A0; queue 0x00791C16 was mid-function
; of unrelated float path (00 00 00 mid-imm, ends ret @ 0x791C93).
; True body sits in LanguageFilter map COMDAT cluster between
; pair copy-ctor @ 0x44D270 and _M_lower_bound @ 0x44D370.
; Identity: SEH + a.compareNoCase(b) via ILT 0x1609F -> StringBase@G
; 0x9EFE0; setl; UnicodeString dtor@0x8881D0 x2; ret 8.
; C++ blocked: header-inline compareNoCase inlines to 126B _wcsicmp
; path (data+4) vs retail 95B out-of-line StringBase call (data+8).
_TEXT SEGMENT
public ??RUnicodeStringLessThan@@QBE_NVUnicodeString@@0@Z
??RUnicodeStringLessThan@@QBE_NVUnicodeString@@0@Z PROC
    db 064h,0A1h,000h,000h,000h,000h,06Ah,0FFh,068h,098h,037h,002h,001h,050h,064h,089h
    db 025h,000h,000h,000h,000h,053h,08Dh,044h,024h,018h,050h,08Dh,04Ch,024h,018h,0C7h
    db 044h,024h,010h,000h,000h,000h,000h,0E8h,0D3h,08Dh,0BCh,0FFh,085h,0C0h,08Dh,04Ch
    db 024h,014h,00Fh,09Ch,0C3h,0E8h,0F6h,0AEh,043h,000h,08Dh,04Ch,024h,018h,0C7h,044h
    db 024h,00Ch,0FFh,0FFh,0FFh,0FFh,0E8h,0E5h,0AEh,043h,000h,08Bh,04Ch,024h,004h,08Ah
    db 0C3h,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,00Ch,0C2h,008h,000h
??RUnicodeStringLessThan@@QBE_NVUnicodeString@@0@Z ENDP
_TEXT ENDS
END
