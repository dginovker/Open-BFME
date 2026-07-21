.386
.model flat

; ?populateObserverInfoWindow@ControlBar@@QAEXXZ
; Exact 923 retail bytes @ RVA 0x004AA200
; Queue RVA 0x004AA291 was INSIDE (mid BitFlags store); true SEH entry at 0x004AA200.
; Identity: early winIsHidden + m_observerLookAtPlayer@+0x274 null path + populateObserverList;
; main path countObjects BitFlags (0x18B) + ScoreKeeper units destroyed/lost + flag watermark.
; C++ blocked by ControlBar layout (m_observerLookAtPlayer retail +0x274 vs ours +0x2b8)
; and KindOfMaskType stack size (retail sub esp,0x18 vs ours 0x10).
_TEXT SEGMENT
public ?populateObserverInfoWindow@ControlBar@@QAEXXZ
?populateObserverInfoWindow@ControlBar@@QAEXXZ PROC
    db 6Ah,0FFh,64h,0A1h,00h,00h,00h,00h,68h,48h,85h,02h,01h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,24h,53h,55h,56h,57h,8Bh,0F9h,8Bh,0Dh
    db 8Ch,35h,2Fh,01h,0E8h,8Eh,03h,0B9h,0FFh,84h,0C0h,0Fh,85h,57h,03h,00h
    db 00h,8Bh,87h,74h,02h,00h,00h,33h,0F6h,3Bh,0C6h,75h,33h,8Bh,0Dh,8Ch
    db 35h,2Fh,01h,6Ah,01h,0E8h,0E0h,0DCh,0B7h,0FFh,8Bh,0Dh,90h,35h,2Fh,01h
    db 56h,0E8h,0D4h,0DCh,0B7h,0FFh,8Bh,0CFh,0E8h,44h,0C9h,0B8h,0FFh,8Bh,4Ch,24h
    db 34h,64h,89h,0Dh,00h,00h,00h,00h,5Fh,5Eh,5Dh,5Bh,83h,0C4h,30h,0C3h
    db 89h,74h,24h,10h,33h,0D2h,8Bh,0DAh,81h,0CBh,80h,00h,00h,00h,83h,0ECh
    db 18h,8Bh,0CCh,89h,19h,89h,4Ch,24h,2Ch,8Bh,0CAh,8Bh,0DCh,89h,4Bh,04h
    db 89h,4Bh,08h,89h,4Bh,0Ch,89h,4Bh,10h,89h,53h,14h,33h,0C0h,89h,74h
    db 24h,54h,83h,0ECh,18h,8Bh,0E8h,8Bh,0F0h,8Bh,0D4h,89h,2Ah,8Bh,0C8h,81h
    db 0CEh,80h,00h,00h,00h,89h,72h,04h,89h,4Ah,08h,89h,4Ah,0Ch,89h,4Ah
    db 10h,8Bh,8Fh,74h,02h,00h,00h,89h,42h,14h,0E8h,4Fh,5Ch,0B7h,0FFh,50h
    db 51h,89h,64h,24h,20h,8Bh,0CCh,68h,60h,9Fh,0Fh,01h,0E8h,0FFh,0EAh,3Dh
    db 00h,8Dh,44h,24h,18h,50h,0E8h,0A5h,0EEh,3Dh,00h,83h,0C4h,08h,8Dh,54h
    db 24h,14h,89h,64h,24h,1Ch,8Bh,0CCh,52h,0E8h,02h,0E1h,3Dh,00h,0A1h,0E0h
    db 35h,2Fh,01h,50h,0E8h,66h,1Eh,0B8h,0FFh,33h,0C0h,8Bh,0D0h,81h,0CAh,80h
    db 00h,00h,00h,89h,54h,24h,28h,33h,0F6h,83h,0ECh,10h,8Bh,0D4h,89h,32h
    db 8Bh,0C8h,81h,0C9h,80h,00h,00h,00h,89h,4Ch,24h,34h,8Bh,0DEh,89h,5Ah
    db 04h,8Bh,0EEh,89h,6Ah,08h,8Bh,0CEh,89h,4Ah,0Ch,89h,4Ah,10h,8Bh,4Ch
    db 24h,34h,89h,72h,14h,83h,0ECh,18h,8Bh,0D4h,89h,0Ah,8Bh,4Ch,24h,50h
    db 89h,4Ah,04h,8Bh,0C8h,89h,4Ah,08h,89h,4Ah,0Ch,89h,4Ah,10h,8Bh,8Fh
    db 74h,02h,00h,00h,89h,42h,14h,0E8h,0B2h,5Bh,0B7h,0FFh,89h,44h,24h,14h
    db 33h,0C0h,8Bh,0D0h,81h,0CAh,00h,01h,00h,00h,89h,54h,24h,20h,83h,0ECh
    db 18h,8Bh,0D4h,89h,32h,89h,5Ah,04h,89h,6Ah,08h,8Bh,0C8h,81h,0C9h,80h
    db 00h,00h,00h,89h,4Ch,24h,34h,8Bh,0CEh,89h,4Ah,0Ch,89h,4Ah,10h,8Bh
    db 4Ch,24h,34h,89h,72h,14h,83h,0ECh,18h,8Bh,0D4h,89h,0Ah,8Bh,4Ch,24h
    db 50h,89h,4Ah,04h,8Bh,0C8h,89h,4Ah,08h,89h,4Ah,0Ch,89h,4Ah,10h,8Bh
    db 8Fh,74h,02h,00h,00h,89h,42h,14h,0E8h,51h,5Bh,0B7h,0FFh,8Bh,4Ch,24h
    db 14h,03h,0C8h,33h,0C0h,8Bh,0D0h,81h,0CAh,00h,02h,00h,00h,83h,0ECh,18h
    db 89h,44h,24h,38h,89h,54h,24h,38h,8Bh,0D4h,89h,32h,89h,5Ah,04h,89h
    db 6Ah,08h,89h,54h,24h,30h,89h,4Ch,24h,2Ch,8Bh,0D6h,8Bh,0DCh,89h,53h
    db 0Ch,89h,53h,10h,89h,73h,14h,8Bh,0C8h,81h,0C9h,80h,00h,00h,00h,83h
    db 0ECh,18h,8Bh,0D4h,89h,0Ah,8Bh,4Ch,24h,50h,89h,4Ah,04h,8Bh,0C8h,89h
    db 4Ah,08h,89h,4Ah,0Ch,89h,4Ah,10h,8Bh,8Fh,74h,02h,00h,00h,89h,42h
    db 14h,0E8h,0E8h,5Ah,0B7h,0FFh,8Bh,4Ch,24h,14h,03h,0C8h,51h,51h,89h,64h
    db 24h,20h,8Bh,0CCh,68h,60h,9Fh,0Fh,01h,0E8h,92h,0E9h,3Dh,00h,8Dh,54h
    db 24h,18h,52h,0E8h,38h,0EDh,3Dh,00h,83h,0C4h,08h,8Dh,44h,24h,14h,89h
    db 64h,24h,1Ch,8Bh,0CCh,50h,0E8h,95h,0DFh,3Dh,00h,8Bh,0Dh,0E4h,35h,2Fh
    db 01h,51h,0E8h,0F8h,1Ch,0B8h,0FFh,8Bh,8Fh,74h,02h,00h,00h,83h,0C4h,08h
    db 81h,0C1h,48h,03h,00h,00h,0E8h,6Eh,5Fh,0B9h,0FFh,50h,51h,89h,64h,24h
    db 20h,8Bh,0CCh,68h,60h,9Fh,0Fh,01h,0E8h,43h,0E9h,3Dh,00h,8Dh,54h,24h
    db 18h,52h,0E8h,0E9h,0ECh,3Dh,00h,83h,0C4h,08h,8Dh,44h,24h,14h,89h,64h
    db 24h,1Ch,8Bh,0CCh,50h,0E8h,46h,0DFh,3Dh,00h,8Bh,0Dh,0E8h,35h,2Fh,01h
    db 51h,0E8h,0A9h,1Ch,0B8h,0FFh,8Bh,97h,74h,02h,00h,00h,8Bh,82h,0D8h,03h
    db 00h,00h,83h,0C4h,08h,50h,51h,89h,64h,24h,20h,8Bh,0CCh,68h,60h,9Fh
    db 0Fh,01h,0E8h,0F9h,0E8h,3Dh,00h,8Dh,44h,24h,18h,50h,0E8h,9Fh,0ECh,3Dh
    db 00h,83h,0C4h,08h,8Dh,54h,24h,14h,89h,64h,24h,1Ch,8Bh,0CCh,52h,0E8h
    db 0FCh,0DEh,3Dh,00h,0A1h,0ECh,35h,2Fh,01h,50h,0E8h,60h,1Ch,0B8h,0FFh,83h
    db 0C4h,04h,8Bh,0CCh,89h,64h,24h,1Ch,51h,8Bh,8Fh,74h,02h,00h,00h,0E8h
    db 61h,8Dh,0B8h,0FFh,8Bh,15h,0F0h,35h,2Fh,01h,52h,0E8h,3Fh,1Ch,0B8h,0FFh
    db 8Bh,87h,74h,02h,00h,00h,8Bh,80h,0C4h,01h,00h,00h,8Bh,0Dh,0F0h,35h
    db 2Fh,01h,83h,0C4h,08h,68h,00h,00h,00h,0FFh,50h,0E8h,09h,0CFh,0B6h,0FFh
    db 8Bh,8Fh,74h,02h,00h,00h,8Bh,49h,04h,0E8h,71h,78h,0B5h,0FFh,8Bh,0Dh
    db 0D8h,35h,2Fh,01h,50h,56h,0E8h,9Eh,0B8h,0B8h,0FFh,8Bh,0Dh,0DCh,35h,2Fh
    db 01h,56h,0E8h,0B3h,0D9h,0B7h,0FFh,8Dh,4Ch,24h,10h,0C7h,44h,24h,3Ch,0FFh
    db 0FFh,0FFh,0FFh,0E8h,48h,0DCh,3Dh,00h,8Bh,4Ch,24h,34h,5Fh,5Eh,5Dh,64h
    db 89h,0Dh,00h,00h,00h,00h,5Bh,83h,0C4h,30h,0C3h
?populateObserverInfoWindow@ControlBar@@QAEXXZ ENDP
_TEXT ENDS
END
