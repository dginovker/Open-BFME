.386
.model flat

; ?parseCSF@GameTextManager@@IAE_NPBD@Z
; Exact 672 retail bytes @ RVA 0x00437570; BFME memory-buffer CSF parse (SEH);
; queue RVA 0x009D2189 was mid-epilogue/misplaced; true body via CSF_LABEL/STR/STRW + ILT 0x3EA77
_TEXT SEGMENT
public ?parseCSF@GameTextManager@@IAE_NPBD@Z
?parseCSF@GameTextManager@@IAE_NPBD@Z PROC
    db 6Ah,0FFh,68h,2Bh,22h,02h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,18h,55h,56h,8Bh,0F1h,8Bh,86h,0Ch,78h
    db 00h,00h,33h,0EDh,3Bh,0C5h,89h,6Ch,24h,08h,75h,08h,8Bh,44h,24h,30h
    db 3Bh,0C5h,75h,15h,5Eh,32h,0C0h,5Dh,8Bh,4Ch,24h,18h,64h,89h,0Dh,00h
    db 00h,00h,00h,83h,0C4h,24h,0C2h,04h,00h,81h,38h,20h,46h,53h,43h,57h
    db 8Dh,78h,18h,74h,16h,5Fh,5Eh,32h,0C0h,5Dh,8Bh,4Ch,24h,18h,64h,89h
    db 0Dh,00h,00h,00h,00h,83h,0C4h,24h,0C2h,04h,00h,53h,8Bh,58h,08h,8Dh
    db 04h,0DDh,04h,00h,00h,00h,50h,0E8h,84h,0A9h,44h,00h,83h,0C4h,04h,89h
    db 44h,24h,38h,3Bh,0C5h,89h,6Ch,24h,30h,74h,18h,68h,0Eh,51h,41h,00h
    db 68h,04h,66h,40h,00h,53h,8Dh,68h,04h,6Ah,08h,55h,89h,18h,0E8h,0D1h
    db 0F8h,5Bh,00h,85h,0DBh,0C7h,44h,24h,30h,0FFh,0FFh,0FFh,0FFh,89h,0AEh,0Ch
    db 78h,00h,00h,75h,2Bh,8Bh,54h,24h,10h,89h,56h,08h,8Bh,4Ch,24h,10h
    db 5Bh,33h,0C0h,5Fh,85h,0C9h,8Bh,4Ch,24h,20h,5Eh,0Fh,9Fh,0C0h,5Dh,64h
    db 89h,0Dh,00h,00h,00h,00h,83h,0C4h,24h,0C2h,04h,00h,8Bh,5Ch,24h,18h
    db 4Bh,89h,5Ch,24h,18h,8Bh,0DFh,8Bh,03h,83h,0C7h,0Ch,3Dh,20h,4Ch,42h
    db 4Ch,89h,5Ch,24h,20h,75h,0C5h,8Bh,43h,08h,85h,0C0h,74h,14h,50h,8Dh
    db 4Eh,0Ch,57h,51h,0FFh,15h,0C0h,94h,35h,01h,8Bh,43h,08h,83h,0C4h,0Ch
    db 03h,0F8h,0C6h,44h,30h,0Ch,00h,8Bh,43h,04h,85h,0C0h,0C7h,44h,24h,14h
    db 00h,00h,00h,00h,0Fh,8Eh,26h,01h,00h,00h,8Dh,9Bh,00h,00h,00h,00h
    db 8Bh,0EFh,8Bh,45h,00h,83h,0C7h,08h,3Dh,20h,52h,54h,53h,89h,6Ch,24h
    db 24h,89h,7Ch,24h,38h,74h,0Bh,3Dh,57h,52h,54h,53h,0Fh,85h,18h,01h
    db 00h,00h,8Bh,45h,04h,85h,0C0h,74h,21h,8Dh,14h,00h,52h,8Dh,86h,0Ch
    db 28h,00h,00h,57h,50h,0FFh,15h,28h,95h,35h,01h,8Bh,45h,04h,8Dh,0Ch
    db 47h,83h,0C4h,0Ch,89h,4Ch,24h,38h,8Bh,0F9h,8Bh,4Ch,24h,14h,85h,0C9h
    db 0Fh,85h,0A1h,00h,00h,00h,66h,0C7h,84h,46h,0Ch,28h,00h,00h,00h,00h
    db 8Dh,0BEh,0Ch,28h,00h,00h,8Bh,0C7h,66h,83h,38h,00h,74h,14h,8Bh,0FFh
    db 66h,8Bh,10h,66h,0F7h,0D2h,66h,89h,10h,83h,0C0h,02h,66h,83h,38h,00h
    db 75h,0EEh,57h,8Bh,0CEh,0E8h,94h,0B4h,0BFh,0FFh,8Bh,5Ch,24h,10h,8Bh,8Eh
    db 0Ch,78h,00h,00h,0C1h,0E3h,03h,8Dh,6Eh,0Ch,03h,0CBh,85h,0EDh,74h,1Dh
    db 8Bh,0C5h,8Dh,50h,01h,89h,54h,24h,1Ch,8Dh,0A4h,24h,00h,00h,00h,00h
    db 8Ah,10h,40h,84h,0D2h,75h,0F9h,2Bh,44h,24h,1Ch,0EBh,02h,33h,0C0h,50h
    db 55h,0E8h,0BAh,05h,45h,00h,85h,0FFh,8Bh,86h,0Ch,78h,00h,00h,8Dh,5Ch
    db 03h,04h,74h,0Ch,57h,0FFh,15h,24h,95h,35h,01h,83h,0C4h,04h,0EBh,02h
    db 33h,0C0h,50h,57h,8Bh,0CBh,0E8h,35h,0Eh,45h,00h,8Bh,7Ch,24h,38h,8Bh
    db 5Ch,24h,20h,8Bh,6Ch,24h,24h,81h,7Dh,00h,57h,52h,54h,53h,75h,0Ch
    db 8Bh,0Fh,8Dh,54h,0Fh,04h,89h,54h,24h,38h,8Bh,0FAh,8Bh,44h,24h,14h
    db 8Bh,4Bh,04h,40h,3Bh,0C1h,89h,44h,24h,14h,0Fh,8Ch,0E0h,0FEh,0FFh,0FFh
    db 8Bh,4Ch,24h,10h,8Bh,44h,24h,18h,41h,85h,0C0h,89h,4Ch,24h,10h,0Fh
    db 85h,77h,0FEh,0FFh,0FFh,0E9h,4Bh,0FEh,0FFh,0FFh,8Bh,86h,0Ch,78h,00h,00h
    db 85h,0C0h,74h,1Dh,8Bh,48h,0FCh,8Dh,78h,0FCh,68h,0Eh,51h,41h,00h,51h
    db 6Ah,08h,50h,0E8h,7Eh,0F5h,5Bh,00h,57h,0E8h,0F2h,0A6h,44h,00h,83h,0C4h
    db 04h,0C7h,86h,0Ch,78h,00h,00h,00h,00h,00h,00h,0E9h,1Ch,0FEh,0FFh,0FFh
?parseCSF@GameTextManager@@IAE_NPBD@Z ENDP
_TEXT ENDS
END
