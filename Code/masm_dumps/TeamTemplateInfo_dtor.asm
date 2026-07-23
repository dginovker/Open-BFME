.386
.model flat

; ??1TeamTemplateInfo@@QAE@XZ
; Exact 251 retail bytes @ 0x000ED580.
; Identity: TeamPrototype dtor @ 0xF6E40 passes member this+0x12C through
; ILT thunk 0x422B97; the same member is constructed by TeamTemplateInfo ctor.
; Destroys 32 generic-script AsciiStrings, ten named AsciiStrings, seven
; TCreateUnitsInfo AsciiStrings, then restores the Snapshot vtable.
_TEXT SEGMENT
public ??1TeamTemplateInfo@@QAE@XZ
??1TeamTemplateInfo@@QAE@XZ PROC
    db 6Ah,0FFh,68h,0AEh,0B6h,0FFh,00h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,51h,56h,8Bh,0F1h,89h,74h,24h,04h,68h,28h,0D8h
    db 40h,00h,6Ah,20h,6Ah,04h,8Dh,86h,0C4h,00h,00h,00h,50h,0C7h,44h,24h
    db 20h,0Bh,00h,00h,00h,0E8h,0BCh,97h,90h,00h,8Dh,8Eh,0BCh,00h,00h,00h
    db 0C6h,44h,24h,10h,0Ah,0E8h,76h,0A3h,79h,00h,8Dh,8Eh,0B0h,00h,00h,00h
    db 0C6h,44h,24h,10h,09h,0E8h,66h,0A3h,79h,00h,8Dh,8Eh,0ACh,00h,00h,00h
    db 0C6h,44h,24h,10h,08h,0E8h,56h,0A3h,79h,00h,8Dh,8Eh,88h,00h,00h,00h
    db 0C6h,44h,24h,10h,07h,0E8h,46h,0A3h,79h,00h,8Dh,8Eh,84h,00h,00h,00h
    db 0C6h,44h,24h,10h,06h,0E8h,36h,0A3h,79h,00h,8Dh,8Eh,80h,00h,00h,00h
    db 0C6h,44h,24h,10h,05h,0E8h,26h,0A3h,79h,00h,8Dh,4Eh,7Ch,0C6h,44h,24h
    db 10h,04h,0E8h,19h,0A3h,79h,00h,8Dh,4Eh,74h,0C6h,44h,24h,10h,03h,0E8h
    db 0Ch,0A3h,79h,00h,8Dh,4Eh,70h,0C6h,44h,24h,10h,02h,0E8h,0FFh,0A2h,79h
    db 00h,8Dh,4Eh,6Ch,0C6h,44h,24h,10h,01h,0E8h,0F2h,0A2h,79h,00h,68h,51h
    db 02h,43h,00h,6Ah,07h,6Ah,0Ch,8Dh,4Eh,04h,51h,0C6h,44h,24h,20h,00h
    db 0E8h,11h,97h,90h,00h,8Bh,4Ch,24h,08h,0C7h,06h,44h,37h,07h,01h,5Eh
    db 64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,10h,0C3h
??1TeamTemplateInfo@@QAE@XZ ENDP
_TEXT ENDS
END
