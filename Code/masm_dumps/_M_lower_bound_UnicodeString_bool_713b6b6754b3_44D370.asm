.386
.model flat

; ?_M_lower_bound@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@UUnicodeStringLessThan@@V?$allocator@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVUnicodeString@@_N@_STL@@@2@ABVUnicodeString@@@Z
; Exact 247B LanguageFilter map _M_lower_bound true body @ 0x44D370;
; queue 0x57D6C8 was mid-function of unrelated LanguageFilter path
; (starts 00 mid-imm; pushes TheLanguageFilter-style globals).
; Identity: symbols.csv pin ILT 0x21B16 -> 0x44D370; SEH + tree walk;
; UnicodeString copy@0x888400 x2, compare@0x480f4, dtor@0x8881d0 x2;
; left/right via setl; ret 4; sibling pair/_Construct cluster.
; C++ blocked: compile calls UnicodeStringLessThan::op() (141B) vs
; retail inlined compare (247B) — same shape-class as filterLine MASM.
_TEXT SEGMENT
public _bfme_export_713b6b6754b3
_bfme_export_713b6b6754b3 PROC
    db 06Ah,0FFh,068h,0C0h,037h,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,010h,08Bh,001h,053h,055h,08Bh,068h,004h,085h
    db 0EDh,056h,057h,089h,044h,024h,01Ch,00Fh,084h,0B5h,000h,000h,000h,08Dh,049h,000h
    db 08Bh,044h,024h,030h,050h,08Dh,04Ch,024h,01Ch,0E8h,052h,0B0h,043h,000h,08Dh,04Dh
    db 010h,051h,08Dh,04Ch,024h,018h,0C7h,044h,024h,02Ch,000h,000h,000h,000h,0E8h,03Dh
    db 0B0h,043h,000h,08Bh,044h,024h,018h,085h,0C0h,0C7h,044h,024h,028h,001h,000h,000h
    db 000h,074h,009h,00Fh,0B7h,078h,004h,08Dh,050h,008h,0EBh,007h,033h,0FFh,0BAh,08Ch
    db 038h,007h,001h,08Bh,044h,024h,014h,085h,0C0h,074h,009h,00Fh,0B7h,070h,004h,08Dh
    db 048h,008h,0EBh,007h,033h,0F6h,0B9h,08Ch,038h,007h,001h,03Bh,0F7h,08Bh,0C6h,07Ch
    db 002h,08Bh,0C7h,050h,052h,051h,08Dh,04Ch,024h,03Ch,0E8h,0E5h,0ACh,0BFh,0FFh,085h
    db 0C0h,075h,006h,02Bh,0F7h,08Bh,0C6h,085h,0C0h,08Dh,04Ch,024h,014h,00Fh,09Ch,0C3h
    db 0E8h,0ABh,0ADh,043h,000h,08Dh,04Ch,024h,018h,0C7h,044h,024h,028h,0FFh,0FFh,0FFh
    db 0FFh,0E8h,09Ah,0ADh,043h,000h,084h,0DBh,075h,009h,089h,06Ch,024h,01Ch,08Bh,06Dh
    db 008h,0EBh,003h,08Bh,06Dh,00Ch,085h,0EDh,00Fh,085h,052h,0FFh,0FFh,0FFh,08Bh,044h
    db 024h,01Ch,08Bh,04Ch,024h,020h,05Fh,05Eh,05Dh,064h,089h,00Dh,000h,000h,000h,000h
    db 05Bh,083h,0C4h,01Ch,0C2h,004h,000h
_bfme_export_713b6b6754b3 ENDP
_TEXT ENDS
END
