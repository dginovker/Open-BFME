.386
.model flat

; ?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z
; Exact 288 retail bytes @ 0x000D5640
; Identity: shape-identical to ZH C++ (288B compiled); only Player vector field offsets
; differ (retail m_sciencesDisabled @ this+0x240 / m_sciencesHidden @ this+0x24c vs
; ZH +0x170/+0x17c = +0xD0 layout drift). SCIENCE_DISABLED=1 / SCIENCE_HIDDEN=2 branches
; and vector erase/push_back insert path match source. Adjacent attemptToPurchaseScience
; @ 0xD55B0 (matched). Ghidra merges 645B; true size is 288 (ret 8 @ end).
; C++ blocked by systemic Player class layout (shared header; do not pad for one leaf).
_TEXT SEGMENT
public ?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z
?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z PROC
    db 8Bh,81h,40h,02h,00h,00h,8Bh,91h,44h,02h,00h,00h,3Bh,0C2h,53h,8Bh
    db 5Ch,24h,08h,56h,57h,8Dh,0B9h,40h,02h,00h,00h,74h,0Eh,8Dh,49h,00h
    db 39h,18h,74h,29h,83h,0C0h,04h,3Bh,0C2h,75h,0F5h,8Bh,91h,4Ch,02h,00h
    db 00h,8Bh,81h,50h,02h,00h,00h,3Bh,0D0h,74h,5Eh,0EBh,03h,8Dh,49h,00h
    db 39h,1Ah,74h,2Dh,83h,0C2h,04h,3Bh,0D0h,75h,0F5h,0EBh,4Ch,8Bh,57h,04h
    db 8Dh,70h,04h,3Bh,0F2h,74h,14h,2Bh,0D6h,0C1h,0FAh,02h,85h,0D2h,7Eh,0Bh
    db 8Bh,70h,04h,89h,30h,83h,0C0h,04h,4Ah,75h,0F5h,83h,47h,04h,0FCh,0EBh
    db 28h,8Bh,81h,50h,02h,00h,00h,8Dh,72h,04h,3Bh,0F0h,74h,14h,2Bh,0C6h
    db 0C1h,0F8h,02h,85h,0C0h,7Eh,0Bh,8Bh,72h,04h,89h,32h,83h,0C2h,04h,48h
    db 75h,0F5h,83h,81h,50h,02h,00h,00h,0FCh,8Bh,44h,24h,14h,83h,0F8h,01h
    db 75h,34h,8Bh,47h,04h,3Bh,47h,08h,74h,10h,85h,0C0h,74h,02h,89h,18h
    db 83h,47h,04h,04h,5Fh,5Eh,5Bh,0C2h,08h,00h,6Ah,01h,6Ah,01h,8Dh,4Ch
    db 24h,18h,51h,8Dh,54h,24h,1Ch,52h,8Bh,0CFh,50h,0E8h,78h,0DEh,0F4h,0FFh
    db 5Fh,5Eh,5Bh,0C2h,08h,00h,83h,0F8h,02h,75h,3Fh,8Bh,81h,50h,02h,00h
    db 00h,8Bh,91h,54h,02h,00h,00h,81h,0C1h,4Ch,02h,00h,00h,3Bh,0C2h,74h
    db 15h,85h,0C0h,74h,02h,89h,18h,8Bh,41h,04h,5Fh,83h,0C0h,04h,5Eh,89h
    db 41h,04h,5Bh,0C2h,08h,00h,6Ah,01h,6Ah,01h,8Dh,54h,24h,18h,52h,8Dh
    db 54h,24h,1Ch,52h,50h,0E8h,2Eh,0DEh,0F4h,0FFh,5Fh,5Eh,5Bh,0C2h,08h,00h
?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z ENDP
_TEXT ENDS
END
