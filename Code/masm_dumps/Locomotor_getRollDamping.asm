.386
.model flat

; ?getRollDamping@Locomotor@@QBEMXZ
; Exact 33 retail bytes @ 0x00413180
; Contiguous OVERRIDE Real-getter COMDAT cluster (BounceKick/PitchStiff/RollStiff/
; PitchDamp/RollDamp): m_template@+4, getFinalOverride@0x22BB, m_rollDamping@+0x98
; (INI FieldParse "RollDamping" offset 152). Queue RVA 0x77B17D was mid-instruction.
_TEXT SEGMENT
public ?getRollDamping@Locomotor@@QBEMXZ
?getRollDamping@Locomotor@@QBEMXZ PROC
    db 8Bh,41h,04h,85h,0C0h,75h,07h,0D9h,80h,98h,00h,00h,00h,0C3h,8Bh,48h
    db 04h,85h,0C9h,74h,05h,0E8h,21h,0F1h,0BEh,0FFh,0D9h,80h,98h,00h,00h,00h
    db 0C3h
?getRollDamping@Locomotor@@QBEMXZ ENDP
_TEXT ENDS
END
