.386
.model flat

; ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
; Retail body @ 0x00581790 size 171
; Public thunk @ 0x000181E2 -> body; INI typeTable "ShellMenuScheme" @ 0xEB8138
; Queue RVA 0x0007D46F/0x7D470 is already-matched parseDynamicGameLODDefinition
; (VeryLow..VeryHigh + MinimumFPS FieldParse) — wrong symbol. Identity via ImagePart/LinePart
; FieldParse @ 0xD0B5F0 + TheShell+0x60 newShellMenuScheme + initFromINI.
; C++ blocked: ZH AsciiString::set(const char*) vs retail inlined strlen + StringBase::set(s,len).
_TEXT SEGMENT
public ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z PROC
    db 6Ah,0FFh,68h,18h,6Ah,03h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h
    db 56h,57h,0C7h,44h,24h,08h,00h,00h
    db 00h,00h,8Bh,7Ch,24h,20h,6Ah,00h
    db 8Bh,0CFh,0C7h,44h,24h,1Ch,00h,00h
    db 00h,00h,0E8h,0A9h,0F1h,2Ch,00h,85h
    db 0C0h,74h,10h,8Bh,0C8h,8Dh,71h,01h
    db 8Ah,11h,41h,84h,0D2h,75h,0F9h,2Bh
    db 0CEh,0EBh,02h,33h,0C9h,51h,50h,8Dh
    db 4Ch,24h,10h,0E8h,38h,65h,30h,00h
    db 0A1h,58h,4Bh,2Fh,01h,8Bh,70h,60h
    db 85h,0F6h,74h,25h,51h,8Dh,54h,24h
    db 0Ch,89h,64h,24h,10h,8Bh,0CCh,52h
    db 0E8h,5Bh,63h,30h,00h,8Bh,0CEh,0E8h
    db 64h,0DCh,0A8h,0FFh,68h,0F0h,0B5h,10h
    db 01h,50h,8Bh,0CFh,0E8h,87h,08h,2Dh
    db 00h,8Dh,4Ch,24h,08h,0C7h,44h,24h
    db 18h,0FFh,0FFh,0FFh,0FFh,0E8h,16h,61h
    db 30h,00h,8Bh,4Ch,24h,10h,5Fh,64h
    db 89h,0Dh,00h,00h,00h,00h,5Eh,83h
    db 0C4h,14h,0C3h
?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z ENDP
_TEXT ENDS
END
