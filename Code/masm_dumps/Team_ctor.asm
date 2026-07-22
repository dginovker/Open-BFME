.386
.model flat

; ??0Team@@QAE@PAVTeamPrototype@@I@Z
; Exact 631 retail bytes @ 0x000F7790
; Identity: SEH ctor; stores Team vtbl 0x1085F88; m_proto@+4 m_id@+8;
; prependTo TeamInstanceList @ proto+0x274; newInstance maps @ +0xF0/+0xEC;
; AppendDebugMessage with " - creating team instance." @ 0x1085FA8;
; queue 0xF7849 was INSIDE body (mid-init at +0xB9). True start 0xF7790.
; Layout vs ZH blocks C++: BFME drops Snapshot subobject vptr (+4 shift),
; adds dword[32] @+0x64, larger relation/list tail @+0xE4..+0x108.
_TEXT SEGMENT
public ??0Team@@QAE@PAVTeamPrototype@@I@Z
??0Team@@QAE@PAVTeamPrototype@@I@Z PROC
    db 6Ah,0FFh,68h,93h,0BFh,0FFh,00h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,53h,55h
    db 56h,8Bh,0F1h,57h,89h,74h,24h,10h
    db 8Bh,7Ch,24h,24h,8Bh,44h,24h,28h
    db 33h,0DBh,0C7h,06h,88h,5Fh,08h,01h
    db 89h,7Eh,04h,89h,46h,08h,89h,5Eh
    db 0Ch,89h,5Eh,10h,89h,5Eh,14h,89h
    db 5Ch,24h,1Ch,89h,5Eh,18h,8Dh,6Eh
    db 1Ch,8Bh,0CDh,89h,59h,04h,89h,59h
    db 08h,89h,4Ch,24h,24h,89h,59h,0Ch
    db 6Ah,64h,0C6h,44h,24h,20h,02h,89h
    db 59h,10h,0E8h,0BEh,0FEh,0F2h,0FFh,88h
    db 5Eh,30h,88h,5Eh,31h,88h,5Eh,32h
    db 88h,5Eh,33h,88h,5Eh,34h,88h,5Eh
    db 35h,88h,5Eh,36h,88h,5Eh,37h,89h
    db 5Eh,38h,89h,5Eh,3Ch,89h,5Eh,40h
    db 88h,9Eh,0E4h,00h,00h,00h,88h,9Eh
    db 0E5h,00h,00h,00h,88h,9Eh,0E6h,00h
    db 00h,00h,88h,9Eh,0E7h,00h,00h,00h
    db 89h,9Eh,0F4h,00h,00h,00h,89h,9Eh
    db 0F8h,00h,00h,00h,88h,9Eh,0FCh,00h
    db 00h,00h,6Ah,0Ch,0C6h,44h,24h,20h
    db 03h,89h,9Eh,00h,01h,00h,00h,0E8h
    db 0ECh,6Ch,73h,00h,89h,00h,89h,40h
    db 04h,89h,86h,00h,01h,00h,00h,6Ah
    db 14h,0C6h,44h,24h,24h,04h,89h,9Eh
    db 04h,01h,00h,00h,0E8h,0CFh,6Ch,73h
    db 00h,89h,86h,04h,01h,00h,00h,89h
    db 9Eh,08h,01h,00h,00h,88h,18h,8Bh
    db 8Eh,04h,01h,00h,00h,89h,59h,04h
    db 8Bh,86h,04h,01h,00h,00h,89h,40h
    db 08h,8Bh,86h,04h,01h,00h,00h,89h
    db 40h,0Ch,6Ah,18h,0C6h,44h,24h,28h
    db 05h,89h,9Eh,0E8h,00h,00h,00h,0E8h
    db 84h,0A6h,78h,00h,83h,0C4h,0Ch,89h
    db 44h,24h,24h,3Bh,0C3h,0C6h,44h,24h
    db 1Ch,06h,74h,09h,8Bh,0C8h,0E8h,90h
    db 0B7h,0F0h,0FFh,0EBh,02h,33h,0C0h,6Ah
    db 18h,0C6h,44h,24h,20h,05h,89h,86h
    db 0F0h,00h,00h,00h,0E8h,57h,0A6h,78h
    db 00h,83h,0C4h,04h,89h,44h,24h,24h
    db 3Bh,0C3h,0C6h,44h,24h,1Ch,07h,74h
    db 09h,8Bh,0C8h,0E8h,01h,0C2h,0F2h,0FFh
    db 0EBh,02h,33h,0C0h,8Bh,0CDh,0C6h,44h
    db 24h,1Ch,05h,89h,86h,0ECh,00h,00h
    db 00h,0E8h,0B7h,78h,0F2h,0FFh,3Bh,0FBh
    db 0Fh,84h,0C9h,00h,00h,00h,39h,0B7h
    db 74h,02h,00h,00h,74h,26h,39h,5Eh
    db 10h,75h,21h,39h,5Eh,14h,75h,1Ch
    db 8Bh,97h,74h,02h,00h,00h,89h,56h
    db 14h,8Bh,87h,74h,02h,00h,00h,3Bh
    db 0C3h,74h,03h,89h,70h,10h,89h,0B7h
    db 74h,02h,00h,00h,8Bh,87h,0ACh,01h
    db 00h,00h,3Bh,0C3h,74h,06h,66h,39h
    db 58h,04h,75h,10h,8Bh,87h,0A8h,01h
    db 00h,00h,3Bh,0C3h,74h,0Ah,66h,39h
    db 58h,04h,74h,04h,0C6h,46h,34h,01h
    db 8Dh,47h,10h,50h,8Dh,4Ch,24h,28h
    db 0E8h,0F3h,01h,79h,00h,6Ah,01h,68h
    db 1Ch,53h,07h,01h,8Dh,4Ch,24h,2Ch
    db 0C6h,44h,24h,24h,08h,0E8h,0DEh,03h
    db 79h,00h,8Bh,7Fh,14h,3Bh,0FBh,74h
    db 06h,0Fh,0B7h,4Fh,04h,0EBh,02h,33h
    db 0C9h,3Bh,0FBh,8Dh,47h,08h,75h,05h
    db 0B8h,8Bh,38h,07h,01h,51h,50h,8Dh
    db 4Ch,24h,2Ch,0E8h,0B8h,03h,79h,00h
    db 6Ah,1Ah,68h,0A8h,5Fh,08h,01h,8Dh
    db 4Ch,24h,2Ch,0E8h,0A8h,03h,79h,00h
    db 53h,8Dh,4Ch,24h,28h,51h,8Bh,0Dh
    db 6Ch,07h,2Fh,01h,0E8h,17h,13h,0F3h
    db 0FFh,8Dh,4Ch,24h,24h,0C6h,44h,24h
    db 1Ch,05h,0E8h,69h,0FFh,78h,00h,33h
    db 0C0h,8Dh,4Eh,64h,8Dh,64h,24h,00h
    db 0C6h,44h,06h,44h,01h,89h,19h,40h
    db 83h,0C1h,04h,83h,0F8h,20h,7Ch,0F0h
    db 8Bh,4Ch,24h,14h,5Fh,8Bh,0C6h,5Eh
    db 5Dh,5Bh,64h,89h,0Dh,00h,00h,00h
    db 00h,83h,0C4h,10h,0C2h,08h,00h
??0Team@@QAE@PAVTeamPrototype@@I@Z ENDP
_TEXT ENDS
END
