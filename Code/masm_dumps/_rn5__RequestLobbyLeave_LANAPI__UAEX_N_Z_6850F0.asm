.386
.model flat
; ?RequestLobbyLeave@LANAPI@@UAEX_N@Z
; Exact 75B @ 0x6850F0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?RequestLobbyLeave@LANAPI@@UAEX_N@Z
?RequestLobbyLeave@LANAPI@@UAEX_N@Z PROC
    db 81h, 0ECh, 0DCh, 01h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h
    db 8Bh, 0CEh, 0C7h, 44h, 24h, 08h, 07h, 00h, 00h, 00h, 0FFh, 90h, 0C4h, 00h, 00h, 00h
    db 6Ah, 00h, 8Dh, 54h, 24h, 08h, 52h, 8Bh, 0CEh, 0E8h, 7Bh, 64h, 9Ah, 0FFh, 8Ah, 84h
    db 24h, 0E4h, 01h, 00h, 00h, 84h, 0C0h, 74h, 08h, 8Bh, 4Eh, 4Ch, 0E8h, 93h, 0CDh, 97h
    db 0FFh, 5Eh, 81h, 0C4h, 0DCh, 01h, 00h, 00h, 0C2h, 04h, 00h
?RequestLobbyLeave@LANAPI@@UAEX_N@Z ENDP
_TEXT ENDS
END
