.386
.model flat

; ??$_M_find@VUnicodeString@@@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@UUnicodeStringLessThan@@V?$allocator@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVUnicodeString@@_N@_STL@@@1@ABVUnicodeString@@@Z
; Exact 331B LanguageFilter map _M_find true body @ 0x44D4C0;
; queue 0x007ACCA7 is INSIDE already-matched TestWaterUpdate@0x7ACBD0 (2108B).
; Identity: filterLine calls ILT 0x12927 -> 0x44D4C0; thin map/tree find
; wrappers @0x44D740/0x44D790 (ret 8) call same; SEH + tree walk + equality;
; U-copy@0x888400 x4, compare@0x480f4 x2, dtor@0x8881d0 x4, LessThan inlined;
; sibling of _M_lower_bound@0x44D370 (MASM). C++ blocked: 228B with
; out-of-line UnicodeStringLessThan::op() vs retail 331B inlined compare.
_TEXT SEGMENT
public _bfme_export_3f5aeba9e5ee
_bfme_export_3f5aeba9e5ee PROC
    db 06Ah,0FFh,068h,0E8h,037h,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,014h,053h,055h,056h,08Bh,0F1h,08Bh,02Eh,057h
    db 08Bh,07Dh,004h,085h,0FFh,089h,074h,024h,01Ch,00Fh,084h,0ADh,000h,000h,000h,090h
    db 08Bh,044h,024h,034h,050h,08Dh,04Ch,024h,01Ch,0E8h,002h,0AFh,043h,000h,08Dh,04Fh
    db 010h,051h,033h,0DBh,08Dh,04Ch,024h,018h,089h,05Ch,024h,030h,0E8h,0EFh,0AEh,043h
    db 000h,08Bh,044h,024h,018h,03Bh,0C3h,0C7h,044h,024h,02Ch,001h,000h,000h,000h,074h
    db 009h,00Fh,0B7h,058h,004h,08Dh,050h,008h,0EBh,005h,0BAh,08Ch,038h,007h,001h,08Bh
    db 044h,024h,014h,085h,0C0h,074h,009h,00Fh,0B7h,070h,004h,08Dh,048h,008h,0EBh,007h
    db 033h,0F6h,0B9h,08Ch,038h,007h,001h,03Bh,0F3h,08Bh,0C6h,07Ch,002h,08Bh,0C3h,050h
    db 052h,051h,08Dh,04Ch,024h,040h,0E8h,099h,0ABh,0BFh,0FFh,085h,0C0h,075h,006h,02Bh
    db 0F3h,08Bh,0C6h,085h,0C0h,08Dh,04Ch,024h,014h,00Fh,09Ch,0C3h,0E8h,05Fh,0ACh,043h
    db 000h,08Dh,04Ch,024h,018h,0C7h,044h,024h,02Ch,0FFh,0FFh,0FFh,0FFh,0E8h,04Eh,0ACh
    db 043h,000h,084h,0DBh,075h,007h,08Bh,0EFh,08Bh,07Fh,008h,0EBh,003h,08Bh,07Fh,00Ch
    db 085h,0FFh,00Fh,085h,058h,0FFh,0FFh,0FFh,08Bh,074h,024h,01Ch,03Bh,02Eh,074h,03Dh
    db 051h,08Dh,055h,010h,089h,064h,024h,020h,08Bh,0CCh,052h,0E8h,050h,0AEh,043h,000h
    db 08Bh,044h,024h,038h,051h,089h,064h,024h,028h,08Bh,0CCh,050h,0C7h,044h,024h,038h
    db 002h,000h,000h,000h,0E8h,037h,0AEh,043h,000h,08Dh,04Eh,008h,0C7h,044h,024h,034h
    db 0FFh,0FFh,0FFh,0FFh,0E8h,0D8h,0ACh,0BFh,0FFh,084h,0C0h,074h,017h,08Bh,006h,08Bh
    db 04Ch,024h,024h,064h,089h,00Dh,000h,000h,000h,000h,05Fh,05Eh,05Dh,05Bh,083h,0C4h
    db 020h,0C2h,004h,000h,08Bh,04Ch,024h,024h,05Fh,05Eh,08Bh,0C5h,05Dh,064h,089h,00Dh
    db 000h,000h,000h,000h,05Bh,083h,0C4h,020h,0C2h,004h,000h
_bfme_export_3f5aeba9e5ee ENDP
_TEXT ENDS
END
