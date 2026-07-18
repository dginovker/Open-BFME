.386
.model flat

; ?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z
; Exact 160 retail bytes @ 0x007513F0; writes the BFME script-action list.
_TEXT SEGMENT
public ?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z
?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z PROC
    db 056h,08Bh,074h,024h,00Ch,085h,0F6h,00Fh,084h,091h,000h,000h,000h,053h,055h,057h
    db 08Bh,07Ch,024h,014h,06Ah,002h,068h,0D0h,07Ch,00Eh,001h,08Bh,0CFh,0E8h,044h,08Eh
    db 0CEh,0FFh,08Bh,046h,004h,050h,08Bh,0CFh,0E8h,097h,07Eh,0CBh,0FFh,08Bh,00Dh,06Ch
    db 007h,02Fh,001h,08Bh,046h,004h,08Bh,011h,050h,0FFh,052h,028h,085h,0C0h,074h,006h
    db 08Bh,048h,00Ch,051h,0EBh,011h,08Bh,00Dh,000h,0D6h,02Eh,001h,068h,018h,085h,00Eh
    db 001h,0E8h,091h,099h,0CEh,0FFh,050h,08Bh,0CFh,0E8h,03Eh,078h,0CCh,0FFh,08Bh,056h
    db 008h,052h,08Bh,0CFh,0E8h,05Bh,07Eh,0CBh,0FFh,08Bh,046h,008h,033h,0DBh,085h,0C0h
    db 07Eh,017h,08Dh,06Eh,00Ch,08Bh,04Dh,000h,057h,0E8h,011h,0E5h,0CBh,0FFh,08Bh,046h
    db 008h,043h,083h,0C5h,004h,03Bh,0D8h,07Ch,0ECh,08Bh,0CFh,0E8h,0C2h,036h,0CBh,0FFh
    db 08Bh,076h,03Ch,085h,0F6h,00Fh,085h,079h,0FFh,0FFh,0FFh,05Fh,05Dh,05Bh,05Eh,0C3h
?WriteActionDataChunk@ScriptAction@@SAXAAVDataChunkOutput@@PAV1@@Z ENDP
_TEXT ENDS
END
