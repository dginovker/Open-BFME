.386
.model flat

; ?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
; Exact 62 retail bytes @ 0x00799F20; FunctionLexicon {key,str,fn} entry.
; Drift 0x0079A72A was mid-body elsewhere; ILT 0x44099 -> 0x799F20 (NOT Cameo 0x3C213->0x799D00).
; BFME: if WIN_STATUS_IMAGE, call window+0x1E8 draw cb else GameWinDefaultDraw path via +0x218.
_TEXT SEGMENT
public ?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z PROC
    db 056h,08Bh,074h,024h,008h,08Bh,0CEh,0E8h,0AEh,09Eh,088h,0FFh,084h,0C0h,079h,02Ch
    db 08Bh,086h,0E8h,001h,000h,000h,085h,0C0h,074h,00Dh,08Bh,04Ch,024h,00Ch,051h,056h
    db 0FFh,0D0h,083h,0C4h,008h,05Eh,0C3h,08Bh,044h,024h,00Ch,08Bh,096h,018h,002h,000h
    db 000h,08Dh,08Eh,018h,002h,000h,000h,050h,056h,0FFh,052h,004h,05Eh,0C3h
?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z ENDP
_TEXT ENDS
END
