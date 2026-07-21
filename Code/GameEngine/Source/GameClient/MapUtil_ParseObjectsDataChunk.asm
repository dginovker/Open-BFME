.386
.model flat

; ?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
; Exact 124 retail bytes @ 0x00454A60
; Identity: loadMap @0x454CF6 pushes ObjectsList + callback 0x854A60;
; body: m_currentObject=NULL, thin AsciiString("Object")@0x888BC0,
; registerParser(ParseObjectDataChunk@0x454760), parse, SEH frame.
; Queue 0x00AF9ADC was mid jump-table (misplaced); compiled 155B was fat AsciiString.
_TEXT SEGMENT
public ?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,08h,3Fh,02h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,56h,8Bh,74h
    db 24h,14h,68h,0C0h,38h,08h,01h,8Dh
    db 4Ch,24h,18h,0C7h,46h,20h,00h,00h
    db 00h,00h,0E8h,31h,41h,43h,00h,8Bh
    db 44h,24h,18h,6Ah,00h,68h,60h,47h
    db 85h,00h,50h,8Dh,4Ch,24h,20h,51h
    db 8Bh,0CEh,0C7h,44h,24h,1Ch,00h,00h
    db 00h,00h,0E8h,22h,11h,0BCh,0FFh,8Dh
    db 4Ch,24h,14h,0C7h,44h,24h,0Ch,0FFh
    db 0FFh,0FFh,0FFh,0E8h,80h,2Eh,43h,00h
    db 8Bh,54h,24h,1Ch,52h,8Bh,0CEh,0E8h
    db 2Eh,41h,0BDh,0FFh,8Bh,4Ch,24h,04h
    db 64h,89h,0Dh,00h,00h,00h,00h,5Eh
    db 83h,0C4h,0Ch,0C3h
?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z ENDP
_TEXT ENDS
END
