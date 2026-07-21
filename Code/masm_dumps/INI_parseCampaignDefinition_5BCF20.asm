.386
.model flat

; ?parseCampaignDefinition@INI@@SAXPAV1@@Z
; Retail body @ 0x005BCF20 size 172
; Public thunk @ 0x00018F6B -> body; INI theTypeTable "Campaign" entry @ 0xEB8A84
; Drift 0x005EE360 was a 7B vtable-store stub + unrelated float parse — misplaced.
_TEXT SEGMENT
public ?parseCampaignDefinition@INI@@SAXPAV1@@Z
?parseCampaignDefinition@INI@@SAXPAV1@@Z PROC
    db 6Ah,0FFh,68h,0E8h,97h,03h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h
    db 56h,57h,0C7h,44h,24h,08h,00h,00h
    db 00h,00h,8Bh,7Ch,24h,20h,6Ah,00h
    db 8Bh,0CFh,0C7h,44h,24h,1Ch,00h,00h
    db 00h,00h,0E8h,19h,3Ah,29h,00h,85h
    db 0C0h,74h,10h,8Bh,0C8h,8Dh,71h,01h
    db 8Ah,11h,41h,84h,0D2h,75h,0F9h,2Bh
    db 0CEh,0EBh,02h,33h,0C9h,51h,50h,8Dh
    db 4Ch,24h,10h,0E8h,0A8h,0ADh,2Ch,00h
    db 0A1h,0B0h,4Ch,2Fh,01h,85h,0C0h,74h
    db 29h,51h,8Dh,44h,24h,0Ch,89h,64h
    db 24h,10h,8Bh,0CCh,50h,0E8h,0CEh,0ABh
    db 2Ch,00h,8Bh,0Dh,0B0h,4Ch,2Fh,01h
    db 0E8h,80h,40h,0A5h,0FFh,68h,90h,0F5h
    db 10h,01h,50h,8Bh,0CFh,0E8h,0F6h,50h
    db 29h,00h,8Dh,4Ch,24h,08h,0C7h,44h
    db 24h,18h,0FFh,0FFh,0FFh,0FFh,0E8h,85h
    db 0A9h,2Ch,00h,8Bh,4Ch,24h,10h,5Fh
    db 64h,89h,0Dh,00h,00h,00h,00h,5Eh
    db 83h,0C4h,14h,0C3h
?parseCampaignDefinition@INI@@SAXPAV1@@Z ENDP
_TEXT ENDS
END
