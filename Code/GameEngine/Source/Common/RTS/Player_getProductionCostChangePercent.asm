.386
.model flat

; ?getProductionCostChangePercent@Player@@QBEMVAsciiString@@@Z
; Exact 91 retail bytes @ 0x000D47F0
; Identity: NAMEKEY(buildTemplateName) then map<NameKey,Real>::find at this+0x1CC;
; found -> fld [node+0x14]; miss -> fld 0.0f; ret 4. Sibling getProductionVeterancyLevel
; @ 0xD4870 (this+0x214, int return). Queue RVA 0x79CED4 is INSIDE MOTDSystem (misplaced).
; C++ blocked: SEH+AsciiString dtor shape (230B) and Player layout (ZH +0x12C vs retail +0x1CC).
_TEXT SEGMENT
public ?getProductionCostChangePercent@Player@@QBEMVAsciiString@@@Z
?getProductionCostChangePercent@Player@@QBEMVAsciiString@@@Z PROC
    db 051h,08Bh,044h,024h,008h,08Bh,000h,085h,0C0h,056h,08Bh,0F1h,074h,005h,083h,0C0h
    db 008h,0EBh,005h,0B8h,08Bh,038h,007h,001h,08Bh,00Dh,000h,0D6h,02Eh,001h,050h,0E8h
    db 0C3h,065h,0F6h,0FFh,08Dh,04Ch,024h,00Ch,051h,08Dh,054h,024h,008h,081h,0C6h,0CCh
    db 001h,000h,000h,052h,08Bh,0CEh,089h,044h,024h,014h,0E8h,051h,091h,0F4h,0FFh,08Bh
    db 00Eh,08Bh,044h,024h,004h,03Bh,0C1h,05Eh,074h,007h,0D9h,040h,014h,059h,0C2h,004h
    db 000h,0D9h,005h,050h,053h,007h,001h,059h,0C2h,004h,000h
?getProductionCostChangePercent@Player@@QBEMVAsciiString@@@Z ENDP
_TEXT ENDS
END
