.386
.model flat

; ?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
; True body @ 0x0048CAD0 size 204; queue 0x00B026CE was INSIDE scalar-deleting dtor @ 0xB026C0 (30B).
; Identity: parseHeaderTemplateDefinition@0x48CBD0 calls ILT 0x470E6 -> body 0x48CAD0;
;   new(0x14)=sizeof HeaderTemplate, ctor, m_name@+4 assign, list push_front via __new_alloc::allocate(0xC).
; C++ blocked: ZH push_front/STL emits 301B (ebx/ebp frame) vs retail 204B fully-inlined node link.
_TEXT SEGMENT
public ?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z PROC
    db 06Ah,0FFh,068h,003h,070h,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,056h,057h,08Bh,0F9h,06Ah,014h,0C7h,044h,024h,018h
    db 000h,000h,000h,000h,0E8h,037h,054h,03Fh,000h,083h,0C4h,004h,089h,044h,024h,008h
    db 085h,0C0h,0C6h,044h,024h,014h,001h,074h,00Bh,08Bh,0C8h,0E8h,039h,026h,0BAh,0FFh
    db 08Bh,0F0h,0EBh,002h,033h,0F6h,085h,0F6h,0C6h,044h,024h,014h,000h,075h,026h,08Dh
    db 04Ch,024h,01Ch,0C7h,044h,024h,014h,0FFh,0FFh,0FFh,0FFh,0E8h,010h,0AEh,03Fh,000h
    db 033h,0C0h,08Bh,04Ch,024h,00Ch,064h,089h,00Dh,000h,000h,000h,000h,05Fh,05Eh,083h
    db 0C4h,010h,0C2h,004h,000h,08Dh,044h,024h,01Ch,08Dh,04Eh,004h,050h,0E8h,03Eh,0B1h
    db 03Fh,000h,08Bh,00Fh,08Bh,039h,06Ah,00Ch,0E8h,0E3h,019h,03Ah,000h,08Dh,048h,008h
    db 083h,0C4h,004h,085h,0C9h,074h,002h,089h,031h,08Bh,04Fh,004h,089h,048h,004h,089h
    db 038h,089h,001h,08Dh,04Ch,024h,01Ch,089h,047h,004h,0C7h,044h,024h,014h,0FFh,0FFh
    db 0FFh,0FFh,0E8h,0B9h,0ADh,03Fh,000h,08Bh,04Ch,024h,00Ch,05Fh,08Bh,0C6h,064h,089h
    db 00Dh,000h,000h,000h,000h,05Eh,083h,0C4h,010h,0C2h,004h,000h
?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
