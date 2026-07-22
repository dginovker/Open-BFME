.386
.model flat

; ?findMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z
; Exact 46 retail bytes @ 0x00673500 (queue 0x6734FE was 2x int3 pad before ENTRY).
; Walks m_first@+4; NetCommandRef command@+0 next@+4; calls isEqualCommandMsg via ILT 0x8963.
_TEXT SEGMENT
public ?findMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z
?findMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z PROC
    db 053h,056h,057h,08Bh,0F9h,08Bh,077h,004h
    db 085h,0F6h,074h,01Ah,08Bh,05Ch,024h,010h
    db 08Bh,006h,053h,050h,08Bh,0CFh,0E8h,048h
    db 054h,099h,0FFh,084h,0C0h,075h,00Fh,08Bh
    db 076h,004h,085h,0F6h,075h,0EAh,05Fh,05Eh
    db 033h,0C0h,05Bh,0C2h,004h,000h
?findMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z ENDP
_TEXT ENDS
END
