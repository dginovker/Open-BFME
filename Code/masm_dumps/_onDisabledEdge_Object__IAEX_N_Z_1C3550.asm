.386
.model flat

; ?onDisabledEdge@Object@@IAEX_N@Z
; Exact 259 retail bytes @ 0x001C3550
; Identity: setDisabledUntil edge call via ILT 0x45430; RadarUpgrade NAMEKEY;
; Team::getControllingPlayer + findModule + add/removeRadar + Energy::adjustPower.
; Queue RVA 0x76D8A9 was INSIDE unrelated fn @ 0x76D850 (misplaced drift vote).
_TEXT SEGMENT
public ?onDisabledEdge@Object@@IAEX_N@Z
?onDisabledEdge@Object@@IAEX_N@Z PROC
    db 064h,0A1h,000h,000h,000h,000h,06Ah,0FFh,068h,05Eh,08Eh,000h,001h,050h,064h,089h
    db 025h,000h,000h,000h,000h,053h,08Ah,05Ch,024h,014h,055h,056h,057h,08Bh,0F9h,08Bh
    db 08Fh,03Ch,002h,000h,000h,085h,0C9h,074h,07Eh,0E8h,01Dh,001h,0E6h,0FFh,08Bh,0E8h
    db 085h,0EDh,00Fh,084h,083h,000h,000h,000h,08Ah,00Dh,068h,0F5h,02Eh,001h,0B8h,001h
    db 000h,000h,000h,084h,0C8h,075h,02Bh,009h,005h,068h,0F5h,02Eh,001h,08Bh,00Dh,000h
    db 0D6h,02Eh,001h,068h,050h,0FFh,008h,001h,0C7h,044h,024h,01Ch,000h,000h,000h,000h
    db 0E8h,022h,078h,0E7h,0FFh,0A3h,064h,0F5h,02Eh,001h,0C7h,044h,024h,018h,0FFh,0FFh
    db 0FFh,0FFh,0A1h,064h,0F5h,02Eh,001h,050h,08Bh,0CFh,0E8h,054h,078h,0E6h,0FFh,08Bh
    db 0F0h,085h,0F6h,074h,036h,08Bh,056h,010h,08Dh,04Eh,010h,0FFh,012h,084h,0C0h,074h
    db 02Ah,084h,0DBh,074h,016h,08Bh,046h,004h,033h,0C9h,08Ah,048h,070h,051h,08Bh,0CDh
    db 0E8h,025h,0FCh,0E3h,0FFh,0EBh,014h,033h,0EDh,0EBh,010h,08Bh,056h,004h,033h,0C0h
    db 08Ah,042h,070h,08Bh,0CDh,050h,0E8h,0F3h,043h,0E5h,0FFh,08Bh,047h,004h,085h,0C0h
    db 074h,00Ch,08Bh,048h,004h,085h,0C9h,074h,005h,0E8h,09Dh,0ECh,0E3h,0FFh,08Bh,080h
    db 018h,004h,000h,000h,085h,0C0h,07Eh,016h,085h,0EDh,074h,012h,084h,0DBh,00Fh,094h
    db 0C1h,051h,050h,08Dh,08Dh,0A4h,000h,000h,000h,0E8h,018h,0E4h,0E7h,0FFh,08Bh,04Ch
    db 024h,010h,05Fh,05Eh,05Dh,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,00Ch
    db 0C2h,004h,000h
?onDisabledEdge@Object@@IAEX_N@Z ENDP
_TEXT ENDS
END
