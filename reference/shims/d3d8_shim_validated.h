#pragma once
// BFME shim of the DirectX 8.0 d3d8.h. The WW3D2 DX8 layer calls D3D COM interfaces
// through their vtables (`call [vtbl + slot*4]`); reproducing the retail bytes only
// requires the *method order* (vtable slot offsets) to match the real SDK, not the
// bodies (which live in d3d8.dll). Interfaces below preserve the exact DX8.0 vtable
// order. Numeric #defines become immediates, so their values must match the SDK.
// Not the full SDK — extended as the build demands, but the interface method order
// is authoritative.
#ifndef D3D8_H_SHIM
#define D3D8_H_SHIM

#define D3DDP_MAXTEXCOORD 8  // SDK d3d8types.h

struct IDirect3DSwapChain8;  // pointer-only in W3D headers; full vtable added if a caller demands it
#include "winbase_shim.h"

typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long HRESULT;
typedef unsigned char BYTE;
typedef int BOOL;
typedef void* HWND;
typedef unsigned short WORD;
typedef const void* LPCVOID;
typedef void* LPVOID;
typedef unsigned long D3DCOLOR;
typedef void* REFIID;
typedef struct _GUID { DWORD a; WORD b, c; BYTE d[8]; } GUID, IID;
#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define FAILED(hr)    ((HRESULT)(hr) < 0)
#define D3D_OK 0
#define CONST const
#define D3DRS_AMBIENT 139
#define D3DRS_FOGSTART 36
#define D3DRS_FOGEND 37
#define D3DRS_FOGCOLOR 34
typedef struct _D3DRECT { long x1,y1,x2,y2; } D3DRECT;
typedef struct _D3DPOINT { long x,y; } D3DPOINT;

// --- FVF flags ---
#define D3DFVF_XYZ            0x002
#define D3DFVF_XYZRHW        0x004
#define D3DFVF_NORMAL        0x010
#define D3DFVF_DIFFUSE       0x040
#define D3DFVF_SPECULAR      0x080
#define D3DFVF_TEX0          0x000
#define D3DFVF_TEX1          0x100
#define D3DFVF_TEX2          0x200
#define D3DFVF_TEX3          0x300
#define D3DFVF_TEX4          0x400
#define D3DFVF_TEX5          0x500
#define D3DFVF_TEX6          0x600
#define D3DFVF_TEX7          0x700
#define D3DFVF_TEX8          0x800
#define D3DFVF_TEXCOUNT_SHIFT 8
#define D3DFVF_TEXCOORDSIZE3(idx) (1 << (idx*2 + 16))
#define D3DFVF_TEXCOORDSIZE2(idx) 0
#define D3DFVF_TEXCOORDSIZE4(idx) (2 << (idx*2 + 16))
#define D3DFVF_TEXCOORDSIZE1(idx) (3 << (idx*2 + 16))

// --- Usage flags ---
#define D3DUSAGE_RENDERTARGET        0x00000001L
#define D3DUSAGE_DEPTHSTENCIL        0x00000002L
#define D3DUSAGE_WRITEONLY           0x00000008L
#define D3DUSAGE_SOFTWAREPROCESSING  0x00000010L
#define D3DUSAGE_DONOTCLIP           0x00000020L
#define D3DUSAGE_POINTS              0x00000040L
#define D3DUSAGE_RTPATCHES           0x00000080L
#define D3DUSAGE_NPATCHES            0x00000100L
#define D3DUSAGE_DYNAMIC             0x00000200L

// --- Lock flags ---
#define D3DLOCK_READONLY        0x00000010L
#define D3DLOCK_DISCARD         0x00002000L
#define D3DLOCK_NOOVERWRITE     0x00001000L
#define D3DLOCK_NOSYSLOCK       0x00000800L

enum _D3DPOOL { D3DPOOL_DEFAULT=0, D3DPOOL_MANAGED=1, D3DPOOL_SYSTEMMEM=2, D3DPOOL_SCRATCH=3 };
typedef enum _D3DPOOL D3DPOOL;
enum _D3DPRIMITIVETYPE { D3DPT_POINTLIST=1, D3DPT_LINELIST=2, D3DPT_LINESTRIP=3,
	D3DPT_TRIANGLELIST=4, D3DPT_TRIANGLESTRIP=5, D3DPT_TRIANGLEFAN=6 };
typedef enum _D3DPRIMITIVETYPE D3DPRIMITIVETYPE;
enum _D3DFORMAT { D3DFMT_UNKNOWN=0, D3DFMT_A8R8G8B8=21, D3DFMT_X8R8G8B8=22,
	D3DFMT_R5G6B5=23, D3DFMT_A8=28, D3DFMT_L8=50, D3DFMT_A8L8=51, D3DFMT_V8U8=60,
	D3DFMT_X8L8V8U8=62, D3DFMT_Q8W8V8U8=63, D3DFMT_V16U16=64,
	D3DFMT_INDEX16=101, D3DFMT_INDEX32=102 };
typedef enum _D3DFORMAT D3DFORMAT;

// COM interface bases. The pure-virtual method order below is the authoritative
// DirectX 8.0 vtable; only slot offsets matter for matching call sites.
struct IDirect3DResource8;
struct IDirect3DBaseTexture8;

struct IUnknown_D3D {
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
};

// IDirect3DResource8 : IUnknown  (base for buffers/textures/surfaces)
#define D3DRESOURCE_METHODS \
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0; \
	virtual DWORD __stdcall AddRef() = 0; \
	virtual DWORD __stdcall Release() = 0; \
	virtual HRESULT __stdcall GetDevice(void**) = 0; \
	virtual HRESULT __stdcall SetPrivateData(REFIID, LPCVOID, DWORD, DWORD) = 0; \
	virtual HRESULT __stdcall GetPrivateData(REFIID, LPVOID, DWORD*) = 0; \
	virtual HRESULT __stdcall FreePrivateData(REFIID) = 0; \
	virtual DWORD __stdcall SetPriority(DWORD) = 0; \
	virtual DWORD __stdcall GetPriority() = 0; \
	virtual void __stdcall PreLoad() = 0; \
	virtual DWORD __stdcall GetType() = 0;

struct IDirect3DVertexBuffer8 {
	D3DRESOURCE_METHODS
	virtual HRESULT __stdcall Lock(UINT, UINT, BYTE**, DWORD) = 0;
	virtual HRESULT __stdcall Unlock() = 0;
	virtual HRESULT __stdcall GetDesc(void*) = 0;
};
struct IDirect3DIndexBuffer8 {
	D3DRESOURCE_METHODS
	virtual HRESULT __stdcall Lock(UINT, UINT, BYTE**, DWORD) = 0;
	virtual HRESULT __stdcall Unlock() = 0;
	virtual HRESULT __stdcall GetDesc(void*) = 0;
};
struct IDirect3DSurface8 {
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall GetDevice(void**) = 0;
	virtual HRESULT __stdcall SetPrivateData(REFIID, LPCVOID, DWORD, DWORD) = 0;
	virtual HRESULT __stdcall GetPrivateData(REFIID, LPVOID, DWORD*) = 0;
	virtual HRESULT __stdcall FreePrivateData(REFIID) = 0;
	virtual HRESULT __stdcall GetContainer(REFIID, void**) = 0;
	virtual HRESULT __stdcall GetDesc(void*) = 0;
	virtual HRESULT __stdcall LockRect(void*, const void*, DWORD) = 0;
	virtual HRESULT __stdcall UnlockRect() = 0;
};
struct IDirect3DBaseTexture8 {
	D3DRESOURCE_METHODS
	virtual DWORD __stdcall SetLOD(DWORD) = 0;
	virtual DWORD __stdcall GetLOD() = 0;
	virtual DWORD __stdcall GetLevelCount() = 0;
};
struct IDirect3DTexture8 {
	D3DRESOURCE_METHODS
	virtual DWORD __stdcall SetLOD(DWORD) = 0;
	virtual DWORD __stdcall GetLOD() = 0;
	virtual DWORD __stdcall GetLevelCount() = 0;
	virtual HRESULT __stdcall GetLevelDesc(UINT, void*) = 0;
	virtual HRESULT __stdcall GetSurfaceLevel(UINT, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall LockRect(UINT, void*, const void*, DWORD) = 0;
	virtual HRESULT __stdcall UnlockRect(UINT) = 0;
	virtual HRESULT __stdcall AddDirtyRect(const void*) = 0;
};

// IDirect3DDevice8 : IUnknown — full DX8.0 vtable order.
struct IDirect3DDevice8 {
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall TestCooperativeLevel() = 0;
	virtual UINT __stdcall GetAvailableTextureMem() = 0;
	virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD) = 0;
	virtual HRESULT __stdcall GetDirect3D(void**) = 0;
	virtual HRESULT __stdcall GetDeviceCaps(void*) = 0;
	virtual HRESULT __stdcall GetDisplayMode(void*) = 0;
	virtual HRESULT __stdcall GetCreationParameters(void*) = 0;
	virtual HRESULT __stdcall SetCursorProperties(UINT, UINT, IDirect3DSurface8*) = 0;
	virtual void __stdcall SetCursorPosition(int, int, DWORD) = 0;
	virtual BOOL __stdcall ShowCursor(BOOL) = 0;
	virtual HRESULT __stdcall CreateAdditionalSwapChain(void*, void**) = 0;
	virtual HRESULT __stdcall Reset(void*) = 0;
	virtual HRESULT __stdcall Present(const void*, const void*, HWND, const void*) = 0;
	virtual HRESULT __stdcall GetBackBuffer(UINT, DWORD, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall GetRasterStatus(void*) = 0;
	virtual void __stdcall SetGammaRamp(DWORD, const void*) = 0;
	virtual void __stdcall GetGammaRamp(void*) = 0;
	virtual HRESULT __stdcall CreateTexture(UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, IDirect3DTexture8**) = 0;
	virtual HRESULT __stdcall CreateVolumeTexture(UINT, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, void**) = 0;
	virtual HRESULT __stdcall CreateCubeTexture(UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, void**) = 0;
	virtual HRESULT __stdcall CreateVertexBuffer(UINT, DWORD, DWORD, D3DPOOL, IDirect3DVertexBuffer8**) = 0;
	virtual HRESULT __stdcall CreateIndexBuffer(UINT, DWORD, D3DFORMAT, D3DPOOL, IDirect3DIndexBuffer8**) = 0;
	virtual HRESULT __stdcall CreateRenderTarget(UINT, UINT, D3DFORMAT, DWORD, BOOL, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall CreateDepthStencilSurface(UINT, UINT, D3DFORMAT, DWORD, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall CreateImageSurface(UINT, UINT, D3DFORMAT, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall CopyRects(IDirect3DSurface8*, const void*, UINT, IDirect3DSurface8*, const void*) = 0;
	virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture8*, IDirect3DBaseTexture8*) = 0;
	virtual HRESULT __stdcall GetFrontBuffer(IDirect3DSurface8*) = 0;
	virtual HRESULT __stdcall SetRenderTarget(IDirect3DSurface8*, IDirect3DSurface8*) = 0;
	virtual HRESULT __stdcall GetRenderTarget(IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall BeginScene() = 0;
	virtual HRESULT __stdcall EndScene() = 0;
	virtual HRESULT __stdcall Clear(DWORD, const void*, DWORD, D3DCOLOR, float, DWORD) = 0;
	virtual HRESULT __stdcall SetTransform(DWORD, const void*) = 0;
	virtual HRESULT __stdcall GetTransform(DWORD, void*) = 0;
	virtual HRESULT __stdcall MultiplyTransform(DWORD, const void*) = 0;
	virtual HRESULT __stdcall SetViewport(const void*) = 0;
	virtual HRESULT __stdcall GetViewport(void*) = 0;
	virtual HRESULT __stdcall SetMaterial(const void*) = 0;
	virtual HRESULT __stdcall GetMaterial(void*) = 0;
	virtual HRESULT __stdcall SetLight(DWORD, const void*) = 0;
	virtual HRESULT __stdcall GetLight(DWORD, void*) = 0;
	virtual HRESULT __stdcall LightEnable(DWORD, BOOL) = 0;
	virtual HRESULT __stdcall GetLightEnable(DWORD, BOOL*) = 0;
	virtual HRESULT __stdcall SetClipPlane(DWORD, const float*) = 0;
	virtual HRESULT __stdcall GetClipPlane(DWORD, float*) = 0;
	virtual HRESULT __stdcall SetRenderState(DWORD, DWORD) = 0;
	virtual HRESULT __stdcall GetRenderState(DWORD, DWORD*) = 0;
	virtual HRESULT __stdcall BeginStateBlock() = 0;
	virtual HRESULT __stdcall EndStateBlock(DWORD*) = 0;
	virtual HRESULT __stdcall ApplyStateBlock(DWORD) = 0;
	virtual HRESULT __stdcall CaptureStateBlock(DWORD) = 0;
	virtual HRESULT __stdcall DeleteStateBlock(DWORD) = 0;
	virtual HRESULT __stdcall CreateStateBlock(DWORD, DWORD*) = 0;
	virtual HRESULT __stdcall SetClipStatus(const void*) = 0;
	virtual HRESULT __stdcall GetClipStatus(void*) = 0;
	virtual HRESULT __stdcall GetTexture(DWORD, IDirect3DBaseTexture8**) = 0;
	virtual HRESULT __stdcall SetTexture(DWORD, IDirect3DBaseTexture8*) = 0;
	virtual HRESULT __stdcall GetTextureStageState(DWORD, DWORD, DWORD*) = 0;
	virtual HRESULT __stdcall SetTextureStageState(DWORD, DWORD, DWORD) = 0;
	virtual HRESULT __stdcall ValidateDevice(DWORD*) = 0;
	virtual HRESULT __stdcall GetInfo(DWORD, void*, DWORD) = 0;
	virtual HRESULT __stdcall SetPaletteEntries(UINT, const void*) = 0;
	virtual HRESULT __stdcall GetPaletteEntries(UINT, void*) = 0;
	virtual HRESULT __stdcall SetCurrentTexturePalette(UINT) = 0;
	virtual HRESULT __stdcall GetCurrentTexturePalette(UINT*) = 0;
	virtual HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE, UINT, UINT) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE, UINT, UINT, UINT, UINT) = 0;
	virtual HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE, UINT, const void*, UINT) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE, UINT, UINT, UINT, const void*, D3DFORMAT, const void*, UINT) = 0;
	virtual HRESULT __stdcall ProcessVertices(UINT, UINT, UINT, IDirect3DVertexBuffer8*, DWORD) = 0;
	virtual HRESULT __stdcall CreateVertexShader(const DWORD*, const DWORD*, DWORD*, DWORD) = 0;
	virtual HRESULT __stdcall SetVertexShader(DWORD) = 0;
	virtual HRESULT __stdcall GetVertexShader(DWORD*) = 0;
	virtual HRESULT __stdcall DeleteVertexShader(DWORD) = 0;
	virtual HRESULT __stdcall SetVertexShaderConstant(DWORD, const void*, DWORD) = 0;
	virtual HRESULT __stdcall GetVertexShaderConstant(DWORD, void*, DWORD) = 0;
	virtual HRESULT __stdcall GetVertexShaderDeclaration(DWORD, void*, DWORD*) = 0;
	virtual HRESULT __stdcall GetVertexShaderFunction(DWORD, void*, DWORD*) = 0;
	virtual HRESULT __stdcall SetStreamSource(UINT, IDirect3DVertexBuffer8*, UINT) = 0;
	virtual HRESULT __stdcall GetStreamSource(UINT, IDirect3DVertexBuffer8**, UINT*) = 0;
	virtual HRESULT __stdcall SetIndices(IDirect3DIndexBuffer8*, UINT) = 0;
	virtual HRESULT __stdcall GetIndices(IDirect3DIndexBuffer8**, UINT*) = 0;
	virtual HRESULT __stdcall CreatePixelShader(const DWORD*, DWORD*) = 0;
	virtual HRESULT __stdcall SetPixelShader(DWORD) = 0;
	virtual HRESULT __stdcall GetPixelShader(DWORD*) = 0;
	virtual HRESULT __stdcall DeletePixelShader(DWORD) = 0;
	virtual HRESULT __stdcall SetPixelShaderConstant(DWORD, const void*, DWORD) = 0;
	virtual HRESULT __stdcall GetPixelShaderConstant(DWORD, void*, DWORD) = 0;
	virtual HRESULT __stdcall GetPixelShaderFunction(DWORD, void*, DWORD*) = 0;
	virtual HRESULT __stdcall DrawRectPatch(UINT, const float*, const void*) = 0;
	virtual HRESULT __stdcall DrawTriPatch(UINT, const float*, const void*) = 0;
	virtual HRESULT __stdcall DeletePatch(UINT) = 0;
};
typedef struct IDirect3DDevice8 *LPDIRECT3DDEVICE8;
typedef struct IDirect3DVertexBuffer8 *LPDIRECT3DVERTEXBUFFER8;
typedef struct IDirect3DIndexBuffer8 *LPDIRECT3DINDEXBUFFER8;
typedef struct IDirect3DTexture8 *LPDIRECT3DTEXTURE8;
typedef struct IDirect3DSurface8 *LPDIRECT3DSURFACE8;


// State/type enums — values become immediates at call sites so must match SDK.
typedef DWORD D3DRENDERSTATETYPE;
#define D3DRS_ZBIAS 47
#define D3DRS_ZENABLE 7
#define D3DRS_ZWRITEENABLE 14
#define D3DRS_FILLMODE 8
#define D3DRS_SHADEMODE 9
#define D3DRS_ALPHATESTENABLE 15
#define D3DRS_ALPHAFUNC 25
#define D3DRS_ALPHAREF 24
#define D3DRS_SRCBLEND 19
#define D3DRS_DESTBLEND 20
#define D3DRS_BLENDOP 171
#define D3DRS_CULLMODE 22
#define D3DRS_ZFUNC 23
#define D3DRS_STENCILENABLE 52
#define D3DRS_STENCILFAIL 53
#define D3DRS_STENCILZFAIL 54
#define D3DRS_STENCILPASS 55
#define D3DRS_STENCILFUNC 56
#define D3DRS_STENCILREF 57
#define D3DRS_STENCILMASK 58
#define D3DRS_STENCILWRITEMASK 59
#define D3DRS_TEXTUREFACTOR 60
#define D3DRS_COLORWRITEENABLE 168
#define D3DRS_FOGENABLE 28
#define D3DRS_LIGHTING 137
#define D3DRS_ALPHABLENDENABLE 27
#define D3DCOLORWRITEENABLE_RED 1
#define D3DCOLORWRITEENABLE_GREEN 2
#define D3DCOLORWRITEENABLE_BLUE 4
#define D3DCOLORWRITEENABLE_ALPHA 8
#define D3DLOCK_NO_DIRTY_UPDATE 0x00008000L
typedef DWORD D3DTEXTURESTAGESTATETYPE;
#define D3DTSS_COLOROP 1
#define D3DTSS_COLORARG1 2
#define D3DTSS_COLORARG2 3
#define D3DTSS_ALPHAOP 4
#define D3DTSS_ALPHAARG1 5
#define D3DTSS_ALPHAARG2 6
#define D3DTSS_TEXCOORDINDEX 11
#define D3DTSS_BUMPENVMAT00 7
#define D3DTSS_BUMPENVMAT01 8
#define D3DTSS_BUMPENVMAT10 9
#define D3DTSS_BUMPENVMAT11 10
#define D3DTSS_BUMPENVLSCALE 22
#define D3DTSS_BUMPENVLOFFSET 23
#define D3DTSS_TEXTURETRANSFORMFLAGS 24
#define D3DTSS_COLORARG0 25
#define D3DTSS_ALPHAARG0 26
#define D3DTSS_RESULTARG 27
#define D3DTA_DIFFUSE 0
#define D3DTA_CURRENT 1
#define D3DTA_TEXTURE 2
#define D3DTA_TFACTOR 3
#define D3DTA_SPECULAR 4
#define D3DTA_TEMP 5
#define D3DTA_COMPLEMENT 0x10
#define D3DTA_ALPHAREPLICATE 0x20
#define D3DTSS_TCI_CAMERASPACEPOSITION 0x00020000
#define D3DTOP_DISABLE 1
#define D3DTOP_SELECTARG1 2
#define D3DTOP_SELECTARG2 3
#define D3DTOP_MODULATE 4
#define D3DTOP_MODULATE2X 5
#define D3DTOP_MODULATE4X 6
#define D3DTOP_ADD 7
#define D3DTOP_ADDSIGNED 8
#define D3DTOP_SUBTRACT 10
#define D3DTOP_ADDSMOOTH 11
#define D3DTOP_BLENDDIFFUSEALPHA 12
#define D3DBLEND_ZERO 1
#define D3DBLEND_ONE 2
#define D3DBLEND_SRCCOLOR 3
#define D3DBLEND_INVSRCCOLOR 4
#define D3DBLEND_SRCALPHA 5
#define D3DBLEND_INVSRCALPHA 6
#define D3DBLEND_DESTALPHA 7
#define D3DBLEND_INVDESTALPHA 8
#define D3DBLEND_DESTCOLOR 9
#define D3DBLEND_INVDESTCOLOR 10
#define D3DBLEND_SRCALPHASAT 11
#define D3DBLEND_BOTHSRCALPHA 12
#define D3DBLEND_BOTHINVSRCALPHA 13
#define D3DBLENDOP_ADD 1
#define D3DBLENDOP_SUBTRACT 2
#define D3DBLENDOP_REVSUBTRACT 3
#define D3DBLENDOP_MIN 4
#define D3DBLENDOP_MAX 5
#define D3DCMP_NEVER 1
#define D3DCMP_LESS 2
#define D3DCMP_EQUAL 3
#define D3DCMP_LESSEQUAL 4
#define D3DCMP_GREATER 5
#define D3DCMP_NOTEQUAL 6
#define D3DCMP_GREATEREQUAL 7
#define D3DCMP_ALWAYS 8
#define D3DSTENCILOP_KEEP 1
#define D3DSTENCILOP_ZERO 2
#define D3DSTENCILOP_REPLACE 3
#define D3DSTENCILOP_INCRSAT 4
#define D3DSTENCILOP_DECRSAT 5
#define D3DSTENCILOP_INVERT 6
#define D3DSTENCILOP_INCR 7
#define D3DSTENCILOP_DECR 8
#define D3DTSS_ADDRESSU 13
#define D3DTSS_ADDRESSV 14
#define D3DTSS_ADDRESSW 25
#define D3DTSS_MAGFILTER 16
#define D3DTSS_MINFILTER 17
#define D3DTSS_MIPFILTER 18
#define D3DTEXF_NONE 0
#define D3DTEXF_POINT 1
#define D3DTEXF_LINEAR 2
#define D3DTEXF_ANISOTROPIC 3
#define D3DTOP_BLENDTEXTUREALPHA 13
#define D3DTOP_BLENDFACTORALPHA 14
#define D3DTOP_BLENDCURRENTALPHA 15
enum _D3DTRANSFORMSTATETYPE { D3DTS_VIEW=2, D3DTS_PROJECTION=3, D3DTS_WORLD=256 };
typedef enum _D3DTRANSFORMSTATETYPE D3DTRANSFORMSTATETYPE;
// D3DMATRIX: 4x4 float (64 bytes) — layout-bearing member of DX8Wrapper.
typedef struct _D3DMATRIX { float m[4][4]; } D3DMATRIX;
typedef struct _D3DVIEWPORT8 { DWORD X,Y,Width,Height; float MinZ,MaxZ; } D3DVIEWPORT8;
typedef struct _D3DLOCKED_RECT { long Pitch; void *pBits; } D3DLOCKED_RECT;
typedef struct _D3DLOCKED_BOX { int RowPitch; int SlicePitch; void *pBits; } D3DLOCKED_BOX;
typedef struct _D3DADAPTER_IDENTIFIER8 {
	char Driver[512]; char Description[512];
	long long DriverVersion; DWORD VendorId, DeviceId, SubSysId, Revision;
	GUID DeviceIdentifier; DWORD WHQLLevel;
} D3DADAPTER_IDENTIFIER8;
typedef struct _D3DCAPS8 { DWORD pad[228]; } D3DCAPS8;   // opaque, sized for member storage
typedef struct _D3DLIGHT8 { DWORD pad[26]; } D3DLIGHT8;
typedef struct _D3DMATERIAL8 { float pad[17]; } D3DMATERIAL8;
typedef struct _D3DDISPLAYMODE { UINT Width, Height, RefreshRate; D3DFORMAT Format; } D3DDISPLAYMODE;
typedef struct _D3DPRESENT_PARAMETERS { DWORD pad[16]; } D3DPRESENT_PARAMETERS;
typedef struct _D3DDEVICE_CREATION_PARAMETERS { UINT AdapterOrdinal; DWORD DeviceType; HWND hFocusWindow; DWORD BehaviorFlags; } D3DDEVICE_CREATION_PARAMETERS;
typedef D3DCOLOR* LPD3DCOLOR;
struct IDirect3D8 {
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall RegisterSoftwareDevice(void*) = 0;
	virtual UINT __stdcall GetAdapterCount() = 0;
	virtual HRESULT __stdcall GetAdapterIdentifier(UINT, DWORD, D3DADAPTER_IDENTIFIER8*) = 0;
	virtual UINT __stdcall GetAdapterModeCount(UINT) = 0;
	virtual HRESULT __stdcall EnumAdapterModes(UINT, UINT, D3DDISPLAYMODE*) = 0;
	virtual HRESULT __stdcall GetAdapterDisplayMode(UINT, D3DDISPLAYMODE*) = 0;
	virtual HRESULT __stdcall CheckDeviceType(UINT, DWORD, D3DFORMAT, D3DFORMAT, BOOL) = 0;
	virtual HRESULT __stdcall CheckDeviceFormat(UINT, DWORD, D3DFORMAT, DWORD, DWORD, D3DFORMAT) = 0;
	virtual HRESULT __stdcall CheckDeviceMultiSampleType(UINT, DWORD, D3DFORMAT, BOOL, DWORD) = 0;
	virtual HRESULT __stdcall CheckDepthStencilMatch(UINT, DWORD, D3DFORMAT, D3DFORMAT, D3DFORMAT) = 0;
	virtual HRESULT __stdcall GetDeviceCaps(UINT, DWORD, D3DCAPS8*) = 0;
	virtual HWND __stdcall GetAdapterMonitor(UINT) = 0;
	virtual HRESULT __stdcall CreateDevice(UINT, DWORD, HWND, DWORD, D3DPRESENT_PARAMETERS*, IDirect3DDevice8**) = 0;
};
typedef struct IDirect3D8 *LPDIRECT3D8;
#endif
