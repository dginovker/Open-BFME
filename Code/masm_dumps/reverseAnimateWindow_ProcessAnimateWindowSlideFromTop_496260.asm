.386
.model flat

; ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
; Exact 263 retail bytes @ 0x00496260
; Identity: SlideFromTop ctor @0x495F30 stores vtbl 0x10FA28C; slot4 ILT 0x2AD29 -> this body.
; Semantics: reverse y-slide (startTime/timeGetTime, getVel, curPos.y+=vel.y, clamp to startPos.y,
;   winSetPosition, speedUp/maxVel clamp, setVel). Queue 0x4965AC was int3 pad before a different
;   238B body @0x4965B0 (not this vtbl slot). C++ blocked: 249B near-match, startPos.y/x load-spill
;   order + x87 fcom-mem vs fcomp-st clamp + setVel store order (y-then-x with dead stack temp).
_TEXT SEGMENT
public ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z PROC
    db 83h,0ECh,14h,56h,8Bh,74h,24h,1Ch,85h,0F6h,89h,4Ch,24h,04h,74h,07h
    db 8Ah,46h,41h,84h,0C0h,74h,09h,0B0h,01h,5Eh,83h,0C4h,14h,0C2h,04h,00h
    db 57h,8Bh,7Eh,34h,0E8h,5Bh,1Fh,0BBh,0FFh,3Bh,0C7h,73h,0Ah,5Fh,32h,0C0h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h,55h,8Bh,6Eh,28h,85h,0EDh,75h,0Bh,5Dh
    db 5Fh,0B0h,01h,5Eh,83h,0C4h,14h,0C2h,04h,00h,8Bh,4Eh,0Ch,8Bh,46h,08h
    db 8Bh,7Eh,1Ch,53h,8Bh,5Eh,18h,8Dh,54h,24h,14h,89h,4Ch,24h,20h,52h
    db 8Bh,0CEh,89h,44h,24h,20h,0E8h,7Dh,82h,0B7h,0FFh,0D9h,44h,24h,18h,0E8h
    db 64h,0Bh,56h,00h,03h,0F8h,8Bh,44h,24h,20h,3Bh,0F8h,8Bh,0CDh,7Dh,17h
    db 50h,53h,0C6h,46h,41h,01h,0E8h,0B2h,31h,0B8h,0FFh,5Bh,5Dh,5Fh,0B0h,01h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h,57h,53h,0E8h,9Fh,31h,0B8h,0FFh,8Bh,46h
    db 10h,8Bh,4Ch,24h,10h,89h,44h,24h,1Ch,8Bh,46h,14h,89h,5Eh,18h,89h
    db 7Eh,1Ch,8Bh,51h,0Ch,2Bh,0C7h,3Bh,0C2h,7Fh,09h,0D9h,44h,24h,18h,0D8h
    db 49h,14h,0EBh,05h,0D9h,41h,08h,0D9h,0E0h,0D9h,41h,08h,0D9h,0E0h,0D9h,5Ch
    db 24h,28h,0D8h,54h,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,7Ah,06h,0DDh,0D8h,0D9h
    db 44h,24h,28h,8Bh,4Ch,24h,14h,0D9h,5Ch,24h,18h,8Bh,44h,24h,18h,5Bh
    db 5Dh,8Bh,0D1h,89h,46h,30h,5Fh,89h,56h,2Ch,89h,4Ch,24h,08h,32h,0C0h
    db 5Eh,83h,0C4h,14h,0C2h,04h,00h
?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z ENDP
_TEXT ENDS
END
