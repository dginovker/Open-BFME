.386
.model flat

; ?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z
; Exact 94 retail bytes @ 0x0066BAE0; skip untranslatedSlotPosition; m_playerVotes@+0x30
; Callees: getLocalPlayerID@0x4A291, sendVoteCommand@0x66B420, applyDisconnectVote@0x66B910
_TEXT SEGMENT
public ?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z
?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 55h, 56h, 8Bh, 74h, 24h, 14h, 57h, 8Bh, 0F9h, 8Bh, 0CEh
    db 8Dh, 2Ch, 0DDh, 00h, 00h, 00h, 00h, 0E8h, 95h, 0E7h, 9Dh, 0FFh, 03h, 0C5h, 8Ah, 4Ch
    db 0C7h, 30h, 84h, 0C9h, 75h, 31h, 8Bh, 0CEh, 0E8h, 84h, 0E7h, 9Dh, 0FFh, 56h, 03h, 0C5h
    db 53h, 8Bh, 0CFh, 0C6h, 44h, 0C7h, 30h, 01h, 0E8h, 5Ch, 33h, 9Ch, 0FFh, 0A1h, 98h, 08h
    db 2Fh, 01h, 8Bh, 68h, 3Ch, 56h, 8Bh, 0CEh, 0E8h, 64h, 0E7h, 9Dh, 0FFh, 50h, 55h, 53h
    db 8Bh, 0CFh, 0E8h, 76h, 5Ah, 9Bh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 08h, 00h
?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z ENDP
_TEXT ENDS
END
