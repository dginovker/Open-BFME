.386
.model flat

; ?getDefaultMap@@YA?AVAsciiString@@_N@Z
; Exact 361 retail bytes @ 0x00457FB0. Drift 0x457FDC was mid-body
; (je after null TheMapCache check). BFME rewrites the map walk via
; helper @ 0x453480 (vector collect) vs ZH inline begin/end loop; SEH
; + StringBase copy sret path not reproducible from current C++ shape.
_TEXT SEGMENT
public ?getDefaultMap@@YA?AVAsciiString@@_N@Z
?getDefaultMap@@YA?AVAsciiString@@_N@Z PROC
    db 6Ah,0FFh,68h,51h,43h,02h,01h,64h
    db 0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,14h
    db 53h,33h,0DBh,56h,89h,5Ch,24h,08h
    db 8Bh,35h,94h,15h,2Fh,01h,3Bh,0F3h
    db 57h,75h,24h,8Bh,74h,24h,30h,68h
    db 50h,6Eh,33h,01h,8Bh,0CEh,0E8h,75h
    db 0FBh,42h,00h,8Bh,0C6h,8Bh,4Ch,24h
    db 20h,64h,89h,0Dh,00h,00h,00h,00h
    db 5Fh,5Eh,5Bh,83h,0C4h,20h,0C3h,0E8h
    db 0BCh,44h,4Ah,00h,51h,8Bh,0C4h,89h
    db 64h,24h,14h,50h,8Bh,0CEh,0E8h,0D6h
    db 0B9h,0BBh,0FFh,8Bh,0Dh,48h,0CBh,34h
    db 01h,0E8h,0A2h,0Dh,57h,00h,8Bh,0CEh
    db 0E8h,0CCh,0Fh,0BDh,0FFh,84h,0C0h,74h
    db 09h,6Ah,01h,8Bh,0CEh,0E8h,82h,62h
    db 0BBh,0FFh,8Bh,0CEh,0E8h,0A2h,0D9h,0BDh
    db 0FFh,8Ah,4Ch,24h,34h,33h,0C0h,3Ah
    db 0CBh,0Fh,95h,0C0h,89h,5Ch,24h,14h
    db 89h,5Ch,24h,18h,89h,5Ch,24h,1Ch
    db 8Dh,04h,85h,04h,00h,00h,00h,83h
    db 0C8h,01h,8Dh,4Ch,24h,14h,51h,50h
    db 0C7h,44h,24h,30h,01h,00h,00h,00h
    db 0E8h,68h,3Ch,0BBh,0FFh,8Bh,7Ch,24h
    db 20h,8Bh,74h,24h,1Ch,88h,5Ch,24h
    db 18h,8Bh,54h,24h,18h,52h,57h,56h
    db 0E8h,0Eh,0AEh,0BDh,0FFh,2Bh,0FEh,83h
    db 0C4h,14h,0F7h,0C7h,0FCh,0FFh,0FFh,0FFh
    db 8Bh,7Ch,24h,30h,8Bh,0CFh,74h,47h
    db 8Bh,06h,83h,0C0h,50h,50h,0E8h,0BDh
    db 0FAh,42h,00h,0C7h,44h,24h,0Ch,01h
    db 00h,00h,00h,88h,5Ch,24h,28h,8Bh
    db 44h,24h,1Ch,2Bh,0C6h,0C1h,0F8h,02h
    db 0C1h,0E0h,02h,3Dh,80h,00h,00h,00h
    db 76h,39h,56h,0E8h,0E8h,9Dh,42h,00h
    db 83h,0C4h,04h,8Bh,0C7h,8Bh,4Ch,24h
    db 20h,64h,89h,0Dh,00h,00h,00h,00h
    db 5Fh,5Eh,5Bh,83h,0C4h,20h,0C3h,68h
    db 50h,6Eh,33h,01h,0E8h,77h,0FAh,42h
    db 00h,3Bh,0F3h,0C7h,44h,24h,0Ch,01h
    db 00h,00h,00h,88h,5Ch,24h,28h,74h
    db 0Ch,0EBh,0B4h,50h,56h,0E8h,0EEh,64h
    db 3Dh,00h,83h,0C4h,08h,8Bh,4Ch,24h
    db 20h,8Bh,0C7h,5Fh,5Eh,64h,89h,0Dh
    db 00h,00h,00h,00h,5Bh,83h,0C4h,20h
    db 0C3h
?getDefaultMap@@YA?AVAsciiString@@_N@Z ENDP
_TEXT ENDS
END
