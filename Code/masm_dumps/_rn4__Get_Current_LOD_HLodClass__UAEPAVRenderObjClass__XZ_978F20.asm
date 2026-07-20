.386
.model flat
; ?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ
; Exact 47B @ 0x978F20; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ
?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 8Eh, 28h, 01h, 00h, 00h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 90h
    db 28h, 02h, 00h, 00h, 85h, 0C0h, 75h, 02h, 5Eh, 0C3h, 8Bh, 86h, 28h, 01h, 00h, 00h
    db 8Bh, 16h, 6Ah, 00h, 50h, 8Bh, 0CEh, 0FFh, 92h, 30h, 02h, 00h, 00h, 5Eh, 0C3h
?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ ENDP
_TEXT ENDS
END
