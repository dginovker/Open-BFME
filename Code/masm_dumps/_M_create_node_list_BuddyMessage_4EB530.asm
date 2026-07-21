.386
.model flat

; ?_M_create_node@?$list@VBuddyMessage@@V?$allocator@VBuddyMessage@@@_STL@@@_STL@@IAEPAU?$_List_node@VBuddyMessage@@@2@ABVBuddyMessage@@@Z
; Exact 33B retail @ 0x004EB530; true body (queue 0x853ECF was mid xfer@GarrisonContain).
; push 0x20 node; allocate@__new_alloc; _Construct via 0x20E69->BuddyMessage copy.
_TEXT SEGMENT
public ?_M_create_node@?$list@VBuddyMessage@@V?$allocator@VBuddyMessage@@@_STL@@@_STL@@IAEPAU?$_List_node@VBuddyMessage@@@2@ABVBuddyMessage@@@Z
?_M_create_node@?$list@VBuddyMessage@@V?$allocator@VBuddyMessage@@@_STL@@@_STL@@IAEPAU?$_List_node@VBuddyMessage@@@2@ABVBuddyMessage@@@Z PROC
    db 56h,6Ah,20h,0E8h,08h,30h,34h,00h,8Bh,0F0h,8Bh,44h,24h,0Ch,50h,8Dh
    db 4Eh,08h,51h,0E8h,21h,59h,0B3h,0FFh,83h,0C4h,0Ch,8Bh,0C6h,5Eh,0C2h,04h
    db 00h
?_M_create_node@?$list@VBuddyMessage@@V?$allocator@VBuddyMessage@@@_STL@@@_STL@@IAEPAU?$_List_node@VBuddyMessage@@@2@ABVBuddyMessage@@@Z ENDP
_TEXT ENDS
END
