.386
.model flat
; ??0DozerActionState@@QAE@PAVStateMachine@@W4DozerTask@@@Z
; Exact 160B @ 0x2B76F0; misidentified as update@DozerPrimaryIdleState by a prior agent (pushes string "DozerActionState", calls State ctor + operator new(0x48) + virtual initDefaultState -- ctor shape, not a 0-arg update() override) -- corrected identity, same verified bytes; Open-BFME4+Grok
_TEXT SEGMENT
public ??0DozerActionState@@QAE@PAVStateMachine@@W4DozerTask@@@Z
??0DozerActionState@@QAE@PAVStateMachine@@W4DozerTask@@@Z PROC
    db 6Ah, 0FFh, 68h, 0A3h, 33h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 57h, 51h, 8Bh, 0F1h, 89h, 64h, 24h
    db 10h, 8Bh, 0CCh, 68h, 0C4h, 6Fh, 0Ch, 01h, 89h, 74h, 24h, 10h, 0E8h, 9Fh, 14h, 5Dh
    db 00h, 8Bh, 44h, 24h, 24h, 50h, 8Bh, 0CEh, 0E8h, 85h, 0BEh, 0D4h, 0FFh, 8Bh, 7Ch, 24h
    db 24h, 6Ah, 48h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 06h, 70h, 6Fh, 0Ch
    db 01h, 89h, 7Eh, 24h, 0E8h, 0E7h, 0A7h, 5Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h
    db 85h, 0C0h, 0C6h, 44h, 24h, 18h, 01h, 74h, 11h, 8Bh, 4Eh, 1Ch, 8Bh, 49h, 10h, 57h
    db 51h, 8Bh, 0C8h, 0E8h, 65h, 22h, 0D8h, 0FFh, 0EBh, 02h, 33h, 0C0h, 89h, 46h, 28h, 8Bh
    db 10h, 8Bh, 0C8h, 0C6h, 44h, 24h, 18h, 00h, 0FFh, 52h, 1Ch, 8Bh, 4Ch, 24h, 10h, 5Fh
    db 8Bh, 0C6h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 08h, 00h
??0DozerActionState@@QAE@PAVStateMachine@@W4DozerTask@@@Z ENDP
_TEXT ENDS
END
