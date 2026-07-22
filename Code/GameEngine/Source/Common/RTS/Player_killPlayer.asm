.386
.model flat

; ?killPlayer@Player@@QAEXXZ
; Exact 184B @ 0xCE170. Queue 0x51CB26 was INSIDE a large SEH/namekey fn
; (FactionObserver static-init path), NOT killPlayer.
; Identity: dual m_playerTeamPrototypes walks (+0x288) with evacuateTeam
; (thunk 0xB582->0xF3250) then killTeam (0x341D0->0xF6490); m_isPlayerDead
; @+0x680; isInSinglePlayerGame@0x382B00 + PLAYER_COMPUTER@+0x2c early revive;
; Money::withdraw@0xC8610. C++ blocked by Player layout (teams 0x288 vs ZH 0x1a0,
; dead 0x680 vs 0x448) + BFME dropped isLocalPlayer/ControlBar/FactionObserver tail.
_TEXT SEGMENT
public ?killPlayer@Player@@QAEXXZ
?killPlayer@Player@@QAEXXZ PROC
    db 55h,8Bh,0E9h,8Bh,85h,88h,02h,00h,00h,56h,57h,8Bh,38h,3Bh,0F8h,74h
    db 2Bh,8Bh,47h,08h,8Bh,0B0h,74h,02h,00h,00h,85h,0F6h,74h,14h,8Bh,0CEh
    db 0E8h,0EDh,0D3h,0F3h,0FFh,8Bh,0CEh,0E8h,0D4h,48h,0F5h,0FFh,8Bh,0F0h,85h,0F6h
    db 75h,0ECh,8Bh,3Fh,3Bh,0BDh,88h,02h,00h,00h,75h,0D5h,8Bh,85h,88h,02h
    db 00h,00h,0C6h,85h,80h,06h,00h,00h,01h,8Bh,38h,3Bh,0F8h,74h,2Ch,90h
    db 8Bh,4Fh,08h,8Bh,0B1h,74h,02h,00h,00h,85h,0F6h,74h,14h,8Bh,0CEh,0E8h
    db 0FCh,5Fh,0F6h,0FFh,8Bh,0CEh,0E8h,95h,48h,0F5h,0FFh,8Bh,0F0h,85h,0F6h,75h
    db 0ECh,8Bh,3Fh,3Bh,0BDh,88h,02h,00h,00h,75h,0D5h,8Bh,0Dh,98h,08h,2Fh
    db 01h,0E8h,32h,0DCh,0F4h,0FFh,84h,0C0h,74h,11h,83h,7Dh,2Ch,01h,75h,0Bh
    db 5Fh,5Eh,0C6h,85h,80h,06h,00h,00h,00h,5Dh,0C3h,8Bh,0Dh,48h,0D7h,2Eh
    db 01h,8Bh,11h,0FFh,52h,2Ch,8Bh,45h,4Ch,6Ah,01h,50h,8Dh,4Dh,48h,0E8h
    db 70h,36h,0F7h,0FFh,5Fh,5Eh,5Dh,0C3h
?killPlayer@Player@@QAEXXZ ENDP
_TEXT ENDS
END
