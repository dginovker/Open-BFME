.386
.model flat

; ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z
; Retail @ 0x0010B010 size 156
; Identity: sole UpgradeTemplate caller of getVetUpgradeName@0x10AD90 (Upgrade_Veterancy_);
; sets m_type=OBJECT, m_name, nameToKey, clear displayName, zero buildTime/cost.
; Queue RVA 0x79CE61 was unrelated SEH epilogue+int3 (size 242 mis-vote).
_TEXT SEGMENT
public ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z
?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh
    db 68h,0F8h,0D3h,0FFh,00h,50h,8Bh,44h
    db 24h,10h,64h,89h,25h,00h,00h,00h
    db 00h,56h,57h,8Bh,0F1h,50h,8Dh,4Ch
    db 24h,1Ch,51h,0C7h,46h,04h,01h,00h
    db 00h,00h,0E8h,51h,0FDh,0FFh,0FFh,83h
    db 0C4h,08h,8Dh,7Eh,08h,50h,8Bh,0CFh
    db 0C7h,44h,24h,14h,00h,00h,00h,00h
    db 0E8h,3Bh,0CCh,77h,00h,8Dh,4Ch,24h
    db 18h,0C7h,44h,24h,10h,0FFh,0FFh,0FFh
    db 0FFh,0E8h,0DAh,0C8h,77h,00h,8Bh,3Fh
    db 85h,0FFh,8Dh,47h,08h,75h,05h,0B8h
    db 8Bh,38h,07h,01h,8Bh,0Dh,00h,0D6h
    db 2Eh,01h,50h,0E8h,57h,0FDh,0F2h,0FFh
    db 8Dh,4Eh,10h,89h,46h,0Ch,0E8h,0B5h
    db 0C8h,77h,00h,8Bh,4Ch,24h,08h,0C7h
    db 46h,18h,00h,00h,00h,00h,0C7h,46h
    db 1Ch,00h,00h,00h,00h,5Fh,64h,89h
    db 0Dh,00h,00h,00h,00h,5Eh,83h,0C4h
    db 0Ch,0C2h,04h,00h
?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z ENDP
_TEXT ENDS
END
