.386
.model flat
; ?addDynamicLight@RTS3DScene@@QAEXPAVW3DDynamicLight@@@Z
; Exact 74B @ 0x00712030; queue 0x7124C0 was INSIDE getADynamicLight@0x712420
; Identity: dual RefMultiList Add this+0x110 (m_dynamicLightList) + this+0x74 (UpdateList);
; sibling getADynamicLight inlines same pair; W3DDisplay callers need standalone body.
_TEXT SEGMENT
public ?addDynamicLight@RTS3DScene@@QAEXPAVW3DDynamicLight@@@Z
?addDynamicLight@RTS3DScene@@QAEXPAVW3DDynamicLight@@@Z PROC
    db 056h,08Bh,074h,024h,008h,085h,0F6h,057h,08Bh,0F9h,074h,005h,08Dh,046h,008h,0EBh
    db 002h,033h,0C0h,06Ah,001h,050h,08Dh,08Fh,010h,001h,000h,000h,0E8h,00Fh,09Fh,02Ch
    db 000h,03Ch,001h,075h,003h,0FFh,046h,004h,085h,0F6h,074h,005h,08Dh,046h,008h,0EBh
    db 002h,033h,0C0h,06Ah,001h,050h,08Dh,04Fh,074h,0E8h,0F2h,09Eh,02Ch,000h,03Ch,001h
    db 075h,003h,0FFh,046h,004h,05Fh,05Eh,0C2h,004h,000h
?addDynamicLight@RTS3DScene@@QAEXPAVW3DDynamicLight@@@Z ENDP
_TEXT ENDS
END
