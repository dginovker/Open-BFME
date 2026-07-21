.386
.model flat

; ?freeRoadBuffers@W3DRoadBuffer@@IAEXXZ
; Exact 166 retail bytes @ RVA 0x0070E9C0; Ghidra-corrected from misplaced drift 0xC5FF90
; Called from ~W3DRoadBuffer @ 0x70FAF0 via ILT 0x43469; DX8 thread lock + delete[] m_roads/m_roadTypes
_TEXT SEGMENT
public ?freeRoadBuffers@W3DRoadBuffer@@IAEXXZ
?freeRoadBuffers@W3DRoadBuffer@@IAEXXZ PROC
    db 06Ah,0FFh,068h,0D8h,0C5h,004h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,053h,056h,057h,08Bh,0F1h,0E8h,0B0h,046h,01Fh,000h
    db 08Bh,046h,004h,033h,0DBh,03Bh,0C3h,089h,05Ch,024h,018h,074h,023h,08Bh,048h,0FCh
    db 08Dh,078h,0FCh,068h,047h,049h,042h,000h,051h,068h,0BCh,000h,000h,000h,050h,0E8h
    db 072h,083h,02Eh,000h,057h,0E8h,0E6h,034h,017h,000h,083h,0C4h,004h,089h,05Eh,004h
    db 08Bh,006h,03Bh,0C3h,074h,01Fh,08Bh,050h,0FCh,08Dh,078h,0FCh,068h,049h,0DEh,041h
    db 000h,052h,06Ah,024h,050h,0E8h,04Ch,083h,02Eh,000h,057h,0E8h,0C0h,034h,017h,000h
    db 083h,0C4h,004h,089h,01Eh,08Bh,04Eh,054h,03Bh,0CBh,074h,008h,0E8h,05Fh,0CDh,02Dh
    db 000h,089h,05Eh,054h,088h,05Eh,00Ch,0C7h,044h,024h,018h,0FFh,0FFh,0FFh,0FFh,0E8h
    db 0BCh,070h,01Fh,000h,08Bh,04Ch,024h,010h,05Fh,05Eh,05Bh,064h,089h,00Dh,000h,000h
    db 000h,000h,083h,0C4h,010h,0C3h
?freeRoadBuffers@W3DRoadBuffer@@IAEXXZ ENDP
_TEXT ENDS
END
