.386
.model flat
; ?Get_Render_Device_Desc@DX8Wrapper@@KAABVRenderDeviceDescClass@@H@Z
; Exact 41B @ 0x903E80; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?Get_Render_Device_Desc@DX8Wrapper@@KAABVRenderDeviceDescClass@@H@Z
?Get_Render_Device_Desc@DX8Wrapper@@KAABVRenderDeviceDescClass@@H@Z PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0F8h, 0FFh, 75h, 11h, 0A1h, 0B0h, 6Dh, 2Dh, 01h, 83h, 0F8h
    db 0FFh, 75h, 07h, 33h, 0C0h, 0A3h, 0B0h, 6Dh, 2Dh, 01h, 8Bh, 0Dh, 0ECh, 05h, 34h, 01h
    db 69h, 0C0h, 0B8h, 05h, 00h, 00h, 03h, 0C1h, 0C3h
?Get_Render_Device_Desc@DX8Wrapper@@KAABVRenderDeviceDescClass@@H@Z ENDP
_TEXT ENDS
END
