.386
.model flat
; ?onExit@DozerPrimaryIdleState@@UAEXW4StateExitType@@@Z
; Exact 50B @ 0x2B6350; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?onExit@DozerPrimaryIdleState@@UAEXW4StateExitType@@@Z
?onExit@DozerPrimaryIdleState@@UAEXW4StateExitType@@@Z PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 2Ch, 84h, 0C0h, 74h, 24h, 8Bh, 56h, 28h, 8Bh, 0Dh, 8Ch
    db 14h, 2Fh, 01h, 8Bh, 01h, 52h, 8Bh, 56h, 1Ch, 8Bh, 52h, 10h, 52h, 0FFh, 90h, 80h
    db 01h, 00h, 00h, 0C7h, 46h, 28h, 0FFh, 0FFh, 0FFh, 0FFh, 0C6h, 46h, 2Ch, 00h, 5Eh, 0C2h
    db 04h, 00h
?onExit@DozerPrimaryIdleState@@UAEXW4StateExitType@@@Z ENDP
_TEXT ENDS
END
