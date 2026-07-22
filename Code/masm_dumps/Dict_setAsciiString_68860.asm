.386
.model flat

; ?setAsciiString@Dict@@QAEXW4NameKeyType@@ABVAsciiString@@@Z
; Exact 41 retail bytes @ 0x00068860; DICT_ASCIISTRING (push 3);
; sibling of matched setUnicodeString@0x688A0 (push 4); calls StringBase<char>::set
_TEXT SEGMENT
public ?setAsciiString@Dict@@QAEXW4NameKeyType@@ABVAsciiString@@@Z
?setAsciiString@Dict@@QAEXW4NameKeyType@@ABVAsciiString@@@Z PROC
    db 8Bh,44h,24h,04h,56h,6Ah,03h,50h,8Bh,0F1h,0E8h,0DAh,9Eh,0FDh,0FFh,8Bh
    db 4Ch,24h,0Ch,83h,0C0h,04h,51h,8Bh,0C8h,0E8h,12h,0F4h,81h,00h,8Bh,0CEh
    db 0E8h,45h,70h,0FBh,0FFh,5Eh,0C2h,08h,00h
?setAsciiString@Dict@@QAEXW4NameKeyType@@ABVAsciiString@@@Z ENDP
_TEXT ENDS
END
