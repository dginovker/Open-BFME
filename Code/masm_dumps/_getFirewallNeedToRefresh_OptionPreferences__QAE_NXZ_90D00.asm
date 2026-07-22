.386
.model flat
; ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ
; Exact 113B @ 0x90D00; string-anchor FirewallNeedToRefresh true body (queue 0x67003D was write-path interior)
_TEXT SEGMENT
public ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ
?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ PROC
    db 83h, 0ECh, 8h, 56h, 57h, 8Bh, 0F1h, 68h, 60h, 0FAh, 7h, 1h, 8Dh, 4Ch, 24h, 0Ch
    db 0E8h, 0ABh, 7Eh, 7Fh, 0h, 8Dh, 44h, 24h, 8h, 83h, 0C6h, 4h, 50h, 8Bh, 0CEh, 0E8h
    db 88h, 0A1h, 0F7h, 0FFh, 8Dh, 4Ch, 24h, 8h, 8Bh, 0F8h, 0E8h, 11h, 6Ch, 7Fh, 0h, 3Bh
    db 3Eh, 75h, 8h, 5Fh, 32h, 0C0h, 5Eh, 83h, 0C4h, 8h, 0C3h, 53h, 83h, 0C7h, 14h, 57h
    db 8Dh, 4Ch, 24h, 14h, 32h, 0DBh, 0E8h, 15h, 6Eh, 7Fh, 0h, 68h, 58h, 0FAh, 7h, 1h
    db 8Dh, 4Ch, 24h, 14h, 0E8h, 8Fh, 0F8h, 0FAh, 0FFh, 85h, 0C0h, 75h, 2h, 0B3h, 1h, 8Dh
    db 4Ch, 24h, 10h, 0E8h, 0D8h, 6Bh, 7Fh, 0h, 8Ah, 0C3h, 5Bh, 5Fh, 5Eh, 83h, 0C4h, 8h
    db 0C3h
?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ ENDP
_TEXT ENDS
END
