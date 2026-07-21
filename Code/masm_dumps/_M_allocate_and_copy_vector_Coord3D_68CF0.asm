.386
.model flat

; ??$_M_allocate_and_copy@PBUCoord3D@@@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEPAUCoord3D@@IPBU2@0@Z
; Exact 79B retail @ 0x00068CF0; true body (queue 0x853EBF was 1B before xfer@GarrisonContain@0x853EC0/72).
; sizeof Coord3D=0x0c; allocate (__node_alloc/op new) + __uninitialized_copy via ILT 0xC61C->0x68C50.
; Caller: vector::reserve @0x68FA0 (magic 0x2AAAAAAB /12) -> ILT 0x3611F -> this body.
; Cluster: __copy_ptrs@0x68C20, __uninitialized_copy@0x68C50, __uninitialized_fill_n@0x68CA0, push_back@0x69200.
_TEXT SEGMENT
public ??$_M_allocate_and_copy@PBUCoord3D@@@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEPAUCoord3D@@IPBU2@0@Z
??$_M_allocate_and_copy@PBUCoord3D@@@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEPAUCoord3D@@IPBU2@0@Z PROC
    db 8Bh,44h,24h,04h,85h,0C0h,56h,74h,26h,8Dh,04h,40h,0C1h,0E0h,02h,3Dh
    db 80h,00h,00h,00h,50h,76h,0Ch,0E8h,24h,92h,81h,00h,83h,0C4h,04h,8Bh
    db 0F0h,0EBh,0Eh,0E8h,28h,58h,7Ch,00h,83h,0C4h,04h,8Bh,0F0h,0EBh,02h,33h
    db 0F6h,8Bh,4Ch,24h,10h,8Bh,54h,24h,0Ch,8Dh,44h,24h,08h,50h,56h,51h
    db 52h,0E8h,0E6h,38h,0FAh,0FFh,83h,0C4h,10h,8Bh,0C6h,5Eh,0C2h,0Ch,00h
??$_M_allocate_and_copy@PBUCoord3D@@@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEPAUCoord3D@@IPBU2@0@Z ENDP
_TEXT ENDS
END
