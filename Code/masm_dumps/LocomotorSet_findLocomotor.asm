.386
.model flat

; ?findLocomotor@LocomotorSet@@QAEPAVLocomotor@@H@Z
; Exact 73 retail bytes @ 0x001B5CF0
; Queue RVA 0x0077B169 was INSIDE a large unrelated cleanup/dtor (mid-function).
; True body unique-prologue scan: push ebx; vector end/begin [ecx+8]/[ecx+4];
; walk *it, m_template@Locomotor+4 (not ZH +8), getFinalOverride@0x22BB,
; test surfaces [tmpl+0x10] & mask. C++ blocked by Locomotor m_template layout
; (MemoryPoolObject+Snapshot => +8; retail single vptr => +4) - same root as
; getRollDamping MASM (m_template@+4).
_TEXT SEGMENT
public ?findLocomotor@LocomotorSet@@QAEPAVLocomotor@@H@Z
?findLocomotor@LocomotorSet@@QAEPAVLocomotor@@H@Z PROC
    db 53h,8Bh,59h,08h,55h,56h,8Bh,71h,04h,3Bh,0F3h,57h,74h,29h,8Bh,6Ch
    db 24h,14h,8Bh,3Eh,85h,0FFh,74h,18h,8Bh,47h,04h,85h,0C0h,74h,0Ch,8Bh
    db 48h,04h,85h,0C9h,74h,05h,0E8h,0A0h,0C5h,0E4h,0FFh,85h,68h,10h,75h,10h
    db 83h,0C6h,04h,3Bh,0F3h,75h,0DBh,5Fh,5Eh,5Dh,33h,0C0h,5Bh,0C2h,04h,00h
    db 8Bh,0C7h,5Fh,5Eh,5Dh,5Bh,0C2h,04h,00h
?findLocomotor@LocomotorSet@@QAEPAVLocomotor@@H@Z ENDP
_TEXT ENDS
END
