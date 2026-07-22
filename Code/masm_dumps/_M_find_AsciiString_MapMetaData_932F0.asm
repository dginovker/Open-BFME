.386
.model flat

; ??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@1@ABVAsciiString@@@Z
; Exact 167B Rb_tree<AsciiString, pair<const AsciiString, MapMetaData>>::_M_find
; true body @ 0x932F0; ICF twin also @ 0x195EC0 (identical).
; Queue 0x64E638 is INSIDE already-matched createNewMessageQueue@0x64E620 (86B)
; (offset +0x18 = call operator new after push 0x78) — not _M_find.
; Shape: Header* m_data walk (movzx len at m_data+4, lea chars at m_data+8,
; empty 0x107388B), memcmp via IAT [0x1359310], node value at +0x10, final
; thiscall compareNoCase@StringBase ILT 0x27471->0x90570 (int, jge).
; C++ blocked: ZH AsciiStringData chars@+4 + inline strcmp + operator< vs
; BFME ref+ushort len/cap chars@+8 + memcmp + compareNoCase (systemic header).
_TEXT SEGMENT
public _bfme_export_mfind_as_mapmeta
_bfme_export_mfind_as_mapmeta PROC
    db 51h,53h,55h,56h,8Bh,0F1h,8Bh,2Eh,8Bh,5Dh,04h,85h,0DBh,89h,74h,24h
    db 0Ch,74h,6Dh,57h,8Bh,44h,24h,18h,8Bh,00h,85h,0C0h,74h,06h,0Fh,0B7h
    db 78h,04h,0EBh,02h,33h,0FFh,85h,0C0h,8Dh,50h,08h,75h,05h,0BAh,8Bh,38h
    db 07h,01h,8Bh,43h,10h,85h,0C0h,74h,06h,0Fh,0B7h,70h,04h,0EBh,02h,33h
    db 0F6h,85h,0C0h,8Dh,48h,08h,75h,05h,0B9h,8Bh,38h,07h,01h,3Bh,0F7h,8Bh
    db 0C6h,7Ch,02h,8Bh,0C7h,50h,52h,51h,0FFh,15h,10h,93h,35h,01h,83h,0C4h
    db 0Ch,85h,0C0h,75h,06h,2Bh,0F7h,8Bh,0C6h,85h,0C0h,7Ch,07h,8Bh,0EBh,8Bh
    db 5Bh,08h,0EBh,03h,8Bh,5Bh,0Ch,85h,0DBh,75h,99h,8Bh,74h,24h,10h,5Fh
    db 3Bh,2Eh,74h,11h,8Dh,4Dh,10h,51h,8Bh,4Ch,24h,18h,0E8h,0F0h,40h,0F9h
    db 0FFh,85h,0C0h,7Dh,09h,8Bh,06h,5Eh,5Dh,5Bh,59h,0C2h,04h,00h,5Eh,8Bh
    db 0C5h,5Dh,5Bh,59h,0C2h,04h,00h
_bfme_export_mfind_as_mapmeta ENDP
_TEXT ENDS
END
