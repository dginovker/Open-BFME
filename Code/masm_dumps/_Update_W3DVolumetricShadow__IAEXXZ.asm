.386
.model flat

; ?Update@W3DVolumetricShadow@@IAEXXZ
; Retail @ 0x007BF7D0 size 758; BFME Update(Bool) body (ret 4);
; proved via updateVolumes@0x7BF3C0 -> updateMeshVolume@0x7BE000 -> constructVolume@0x7B82A0;
; call sites push 0/1; queue RVA 0x98B1BC was INSIDE ParticleBufferClass::Render_Line
_TEXT SEGMENT
public ?Update@W3DVolumetricShadow@@IAEXXZ
?Update@W3DVolumetricShadow@@IAEXXZ PROC
    db 0A0h,74h,71h,30h,01h,83h,0ECh,1Ch,0A8h,01h,56h,8Bh,0F1h,75h,25h,83h
    db 0Dh,74h,71h,30h,01h,01h,0C7h,05h,64h,71h,30h,01h,00h,00h,00h,00h
    db 0C7h,05h,68h,71h,30h,01h,00h,00h,00h,00h,0C7h,05h,6Ch,71h,30h,01h
    db 00h,00h,00h,00h,8Bh,46h,6Ch,85h,0C0h,0Fh,84h,97h,02h,00h,00h,0A1h
    db 1Ch,6Fh,30h,01h,85h,0C0h,0Fh,84h,91h,02h,00h,00h,0A1h,20h,6Fh,30h
    db 01h,85h,0C0h,0Fh,84h,84h,02h,00h,00h,8Ah,96h,00h,49h,00h,00h,8Bh
    db 4Eh,70h,53h,8Ah,5Ch,24h,28h,8Dh,44h,24h,18h,50h,0Ah,0DAh,0C6h,86h
    db 00h,49h,00h,00h,00h,0E8h,76h,0Ah,16h,00h,0D9h,05h,64h,71h,30h,01h
    db 8Bh,08h,8Bh,50h,04h,8Bh,40h,08h,89h,4Ch,24h,0Ch,0D9h,44h,24h,0Ch
    db 0DAh,0E9h,89h,44h,24h,14h,89h,54h,24h,10h,0DFh,0E0h,0F6h,0C4h,44h,7Ah
    db 2Ah,0D9h,05h,68h,71h,30h,01h,0D9h,44h,24h,10h,0DAh,0E9h,0DFh,0E0h,0F6h
    db 0C4h,44h,7Ah,17h,0D9h,05h,6Ch,71h,30h,01h,0D9h,44h,24h,14h,0DAh,0E9h
    db 0DFh,0E0h,0F6h,0C4h,44h,0Fh,8Bh,0Ah,02h,00h,00h,8Bh,44h,24h,10h,8Bh
    db 0Dh,0CCh,0F4h,2Eh,01h,85h,0C9h,6Ah,00h,50h,8Bh,44h,24h,14h,50h,74h
    db 07h,8Bh,11h,0FFh,52h,18h,0EBh,0Eh,8Bh,0Dh,0E0h,7Fh,2Fh,01h,8Bh,11h
    db 0FFh,92h,48h,02h,00h,00h,0D8h,6Ch,24h,14h,0B9h,0FFh,0FFh,0FFh,7Fh,0D9h
    db 0E1h,0D8h,1Dh,30h,88h,08h,01h,0DFh,0E0h,0F6h,0C4h,01h,0Fh,85h,0C1h,00h
    db 00h,00h,0D9h,46h,78h,0D8h,0Dh,6Ch,0B4h,09h,01h,0D9h,5Ch,24h,08h,0D9h
    db 44h,24h,0Ch,0D8h,25h,14h,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh,44h,24h
    db 28h,0D9h,05h,08h,6Fh,30h,01h,0D8h,44h,24h,08h,23h,0C1h,89h,44h,24h
    db 28h,0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,0Fh,8Bh,85h,01h,00h,00h
    db 0D9h,44h,24h,10h,0D8h,25h,10h,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh,44h
    db 24h,28h,0D9h,05h,04h,6Fh,30h,01h,0D8h,44h,24h,08h,23h,0C1h,89h,44h
    db 24h,28h,0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,0Fh,8Bh,54h,01h,00h
    db 00h,0D9h,44h,24h,14h,0D8h,25h,0Ch,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh
    db 44h,24h,28h,0D9h,05h,00h,6Fh,30h,01h,0D8h,44h,24h,08h,23h,0C1h,89h
    db 44h,24h,28h,0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,0Fh,8Bh,23h,01h
    db 00h,00h,8Bh,0Dh,0E0h,7Fh,2Fh,01h,0D9h,44h,24h,14h,0D8h,0A1h,0Ch,30h
    db 00h,00h,51h,0D9h,0E1h,0D8h,05h,70h,5Ch,07h,01h,0D9h,1Ch,24h,0E9h,0B5h
    db 00h,00h,00h,8Bh,56h,6Ch,83h,0BAh,94h,20h,00h,00h,01h,7Eh,30h,0D9h
    db 44h,24h,0Ch,0D8h,25h,14h,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh,44h,24h
    db 28h,0D9h,05h,08h,6Fh,30h,01h,0D8h,46h,78h,23h,0C1h,89h,44h,24h,28h
    db 0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,0Fh,8Bh,0C6h,00h,00h,00h,0D9h
    db 44h,24h,10h,0D8h,25h,10h,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh,44h,24h
    db 28h,0D9h,05h,04h,6Fh,30h,01h,0D8h,46h,78h,23h,0C1h,89h,44h,24h,28h
    db 0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,0Fh,8Bh,96h,00h,00h,00h,0D9h
    db 44h,24h,14h,0D8h,25h,0Ch,6Fh,30h,01h,0D9h,5Ch,24h,28h,8Bh,44h,24h
    db 28h,0D9h,05h,00h,6Fh,30h,01h,0D8h,46h,78h,23h,0C1h,89h,44h,24h,28h
    db 0D8h,5Ch,24h,28h,0DFh,0E0h,0F6h,0C4h,05h,7Bh,6Ah,0D9h,05h,50h,53h,07h
    db 01h,0D9h,46h,7Ch,0DAh,0E9h,0DFh,0E0h,0F6h,0C4h,44h,7Ah,07h,8Bh,0CEh,0E8h
    db 0D3h,26h,88h,0FFh,8Bh,46h,7Ch,50h,8Bh,0CEh,0E8h,0D6h,0A0h,87h,0FFh,84h
    db 0DBh,74h,36h,8Bh,0Dh,0E8h,6Dh,30h,01h,8Bh,81h,00h,90h,00h,00h,85h
    db 0C0h,74h,26h,0EBh,0Bh,8Dh,0A4h,24h,00h,00h,00h,00h,8Dh,64h,24h,00h
    db 6Ah,00h,0C7h,40h,18h,00h,00h,00h,00h,8Bh,0Dh,0E8h,6Dh,30h,01h,50h
    db 0E8h,21h,83h,88h,0FFh,85h,0C0h,75h,0E7h,8Bh,15h,60h,71h,30h,01h,89h
    db 15h,5Ch,71h,30h,01h,5Bh,5Eh,83h,0C4h,1Ch,0C2h,04h,00h,8Ah,8Eh,00h
    db 49h,00h,00h,8Ah,44h,24h,24h,0Ah,0C8h,88h,8Eh,00h,49h,00h,00h,5Eh
    db 83h,0C4h,1Ch,0C2h,04h,00h
?Update@W3DVolumetricShadow@@IAEXXZ ENDP
_TEXT ENDS
END
