.386
.model flat

; ?setControlBarSchemeByName@ControlBar@@QAEXABVAsciiString@@@Z
; Exact 68B retail @ 0x004A0090. Identity: ControlBar::setControlBarSchemeByName
; Prologue push ecx/esi; m_controlBarSchemeManager@+0x30; by-value AsciiString via
; ??0AsciiString@@QAE@ABV0@@Z @0x887B60; setControlBarScheme ILT 0xA196->0x4AD880;
; TheRecorder@0x12ED62C + getMode; setDefaultControlBarConfig thunk 0x43E73.
; C++ blocked: MSVC 7.1 inlines AsciiString by-value (addRef) vs retail out-of-line copy.
_TEXT SEGMENT
public ?setControlBarSchemeByName@ControlBar@@QAEXABVAsciiString@@@Z
?setControlBarSchemeByName@ControlBar@@QAEXABVAsciiString@@@Z PROC
    db 51h,56h,8Bh,0F1h,8Bh,46h,30h,85h,0C0h,74h,34h,8Bh,44h,24h,0Ch,51h
    db 89h,64h,24h,08h,8Bh,0CCh,50h,0E8h,0B4h,7Ah,3Eh,00h,8Bh,4Eh,30h,0E8h
    db 0E2h,0A0h,0B6h,0FFh,8Bh,0Dh,2Ch,0D6h,2Eh,01h,85h,0C9h,74h,0Ah,0E8h,28h
    db 3Eh,0BAh,0FFh,83h,0F8h,01h,74h,07h,8Bh,0CEh,0E8h,0A4h,3Dh,0BAh,0FFh,5Eh
    db 59h,0C2h,04h,00h
?setControlBarSchemeByName@ControlBar@@QAEXABVAsciiString@@@Z ENDP
_TEXT ENDS
END
