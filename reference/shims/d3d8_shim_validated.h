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
#define D3D_SDK_VERSION 220  // verbatim DX8.1 d3d8.h
typedef struct _D3DVECTOR { float x, y, z; } D3DVECTOR;  // verbatim d3d8types.h
typedef unsigned char BYTE;
#ifndef PALETTEENTRY_DEFINED
#define PALETTEENTRY_DEFINED
typedef struct tagPALETTEENTRY { BYTE peRed, peGreen, peBlue, peFlags; } PALETTEENTRY;
#endif
typedef int BOOL;
typedef void* HWND;
typedef unsigned short WORD;
typedef const void* LPCVOID;
typedef void* LPVOID;
typedef unsigned long D3DCOLOR;
#ifndef _GUID_DEFINED
#define _GUID_DEFINED
typedef struct _GUID { DWORD Data1; WORD Data2; WORD Data3; BYTE Data4[8]; } GUID;
#endif
#ifndef IID_DEFINED
typedef GUID IID;
#define IID_DEFINED
#endif
#ifndef REFIID_DEFINED
typedef const IID& REFIID;
#define REFIID_DEFINED
#endif
#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define FAILED(hr)    ((HRESULT)(hr) < 0)
#define D3D_OK 0
#define CONST const

#ifndef BFME_WIN_GEOM_DEFINED
#define BFME_WIN_GEOM_DEFINED
typedef struct tagRECT { long left, top, right, bottom; } RECT, *LPRECT;
typedef struct tagPOINT { long x; long y; } POINT, *LPPOINT;
#endif
#define D3DRS_AMBIENT 139
#define D3DRS_FOGSTART 36
#define D3DRS_FOGEND 37
#define D3DRS_FOGCOLOR 34
typedef struct _D3DRECT { long x1,y1,x2,y2; } D3DRECT;
typedef struct _D3DPOINT { long x,y; } D3DPOINT;

// --- FVF flags ---
#define D3DFVF_XYZ            0x002
#define D3DFVF_XYZRHW        0x004
#define D3DFVF_XYZB1         0x006
#define D3DFVF_XYZB2         0x007
#define D3DFVF_XYZB3         0x008
#define D3DFVF_XYZB4         0x009
#define D3DFVF_XYZB5         0x00a
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
#define D3DFVF_LASTBETA_UBYTE4   0x00001000L
#define D3DFVF_LASTBETA_D3DCOLOR 0x00008000L
#define D3DFVF_TEXCOUNT_SHIFT 8
#define D3DFVF_TEXCOORDSIZE3(idx) (1 << (idx*2 + 16))
#define D3DFVF_TEXCOORDSIZE2(idx) 0
#define D3DFVF_TEXCOORDSIZE4(idx) (2 << (idx*2 + 16))
#define D3DFVF_TEXCOORDSIZE1(idx) (3 << (idx*2 + 16))

// --- Vertex shader declaration tokens (D3D8 SDK d3d8types.h, value-exact) ---
#define D3DVSD_TOKEN_STREAM        1
#define D3DVSD_TOKEN_STREAMDATA    2
#define D3DVSD_TOKEN_TESSELLATOR   3
#define D3DVSD_TOKEN_CONSTMEM      4
#define D3DVSD_TOKENTYPE_SHIFT     29
#define D3DVSD_TOKENTYPE_MASK      (7 << D3DVSD_TOKENTYPE_SHIFT)
#define D3DVSD_STREAMNUMBER_SHIFT  0
#define D3DVSD_STREAMNUMBER_MASK   (0xF << D3DVSD_STREAMNUMBER_SHIFT)
#define D3DVSD_DATALOADTYPE_SHIFT  28
#define D3DVSD_DATALOADTYPE_MASK   (0x1 << D3DVSD_DATALOADTYPE_SHIFT)
#define D3DVSD_DATATYPE_SHIFT      16
#define D3DVSD_DATATYPE_MASK       (0xF << D3DVSD_DATATYPE_SHIFT)
#define D3DVSD_SKIPCOUNT_SHIFT     16
#define D3DVSD_SKIPCOUNT_MASK      (0xF << D3DVSD_SKIPCOUNT_SHIFT)
#define D3DVSD_VERTEXREG_SHIFT     0
#define D3DVSD_VERTEXREG_MASK      (0x1F << D3DVSD_VERTEXREG_SHIFT)
#define D3DVSD_VERTEXREGIN_SHIFT   20
#define D3DVSD_VERTEXREGIN_MASK    (0xF << D3DVSD_VERTEXREGIN_SHIFT)
#define D3DVSD_CONSTCOUNT_SHIFT    25
#define D3DVSD_CONSTCOUNT_MASK     (0xF << D3DVSD_CONSTCOUNT_SHIFT)
#define D3DVSD_CONSTADDRESS_SHIFT  0
#define D3DVSD_CONSTADDRESS_MASK   (0x7F << D3DVSD_CONSTADDRESS_SHIFT)
#define D3DVSD_CONSTRS_SHIFT       20
#define D3DVSD_CONSTRS_MASK        (0x1FFF << D3DVSD_CONSTRS_SHIFT)
#define D3DVSD_MAKETOKENTYPE(tokenType) ((tokenType << D3DVSD_TOKENTYPE_SHIFT) & D3DVSD_TOKENTYPE_MASK)
#define D3DVSD_STREAM(StreamNumber) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAM) | (StreamNumber))
#define D3DVSD_STREAMTESS() (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAM) | (1 << D3DVSD_DATALOADTYPE_SHIFT))
#define D3DVSD_REG(VertexRegister, DataType) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAMDATA) | ((DataType) << D3DVSD_DATATYPE_SHIFT) | (VertexRegister))
#define D3DVSD_SKIP(DWORDCount) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAMDATA) | (1 << D3DVSD_DATALOADTYPE_SHIFT) | ((DWORDCount) << D3DVSD_SKIPCOUNT_SHIFT))
#define D3DVSD_CONST(ConstantAddress, Count) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_CONSTMEM) | ((Count) << D3DVSD_CONSTCOUNT_SHIFT) | (ConstantAddress))
#define D3DVSD_TESSNORMAL(RegIn, RegOut) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_TESSELLATOR) | ((RegIn) << D3DVSD_VERTEXREGIN_SHIFT) | ((0x02) << D3DVSD_DATATYPE_SHIFT) | (RegOut))
#define D3DVSD_TESSUV(Register) (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_TESSELLATOR) | 0x1000000 | ((0x01) << D3DVSD_DATATYPE_SHIFT) | (Register))
#define D3DVSD_END() 0xFFFFFFFF

typedef enum _D3DVSDT_TYPE {
    D3DVSDT_FLOAT1    = 0x00,
    D3DVSDT_FLOAT2    = 0x01,
    D3DVSDT_FLOAT3    = 0x02,
    D3DVSDT_FLOAT4    = 0x03,
    D3DVSDT_D3DCOLOR  = 0x04,
    D3DVSDT_UBYTE4    = 0x05,
    D3DVSDT_SHORT2    = 0x06,
    D3DVSDT_SHORT4    = 0x07,
    D3DVSDT_UBYTE4N   = 0x08,
    D3DVSDT_SHORT2N   = 0x09,
    D3DVSDT_SHORT4N   = 0x0A,
    D3DVSDT_USHORT2N  = 0x0B,
    D3DVSDT_USHORT4N  = 0x0C,
    D3DVSDT_UDEC3     = 0x0E,
    D3DVSDT_DEC3N     = 0x0F,
    D3DVSDT_FLOAT16_2 = 0x10,
    D3DVSDT_FLOAT16_4 = 0x11,
    D3DVSDT_UNUSED    = 0xFF,
} D3DVSDT_TYPE;

extern "C" UINT __stdcall D3DXGetFVFVertexSize(DWORD FVF);

// IDirect3DDevice8::ShowCursor flags
#define D3DCURSOR_IMMEDIATE_UPDATE 0x00000001L

#define D3DADAPTER_DEFAULT 0

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
enum _D3DFORMAT { D3DFMT_UNKNOWN=0, D3DFMT_R8G8B8=20, D3DFMT_A8R8G8B8=21, D3DFMT_X8R8G8B8=22,
	D3DFMT_R5G6B5=23, D3DFMT_X1R5G5B5=24, D3DFMT_A1R5G5B5=25, D3DFMT_A4R4G4B4=26,
	D3DFMT_X4R4G4B4=27, D3DFMT_A8=28, D3DFMT_L8=50, D3DFMT_A8L8=51, D3DFMT_V8U8=60,
	D3DFMT_R3G3B2=30, D3DFMT_A8R3G3B2=29, D3DFMT_P8=41, D3DFMT_A8P8=40,
	D3DFMT_A4L4=52, D3DFMT_L6V5U5=61,
	D3DFMT_X8L8V8U8=62, D3DFMT_Q8W8V8U8=63, D3DFMT_V16U16=64, D3DFMT_W11V11U10=65,
	D3DFMT_D16=80, D3DFMT_D24S8=75, D3DFMT_D24X8=77, D3DFMT_D24X4S4=79,
	D3DFMT_DXT1=827611204, D3DFMT_DXT2=844388420, D3DFMT_DXT3=861165636,
	D3DFMT_DXT4=877942852, D3DFMT_DXT5=894720068,
	D3DFMT_D16_LOCKABLE=70, D3DFMT_D32=71, D3DFMT_D15S1=73,
	D3DFMT_UYVY=1498831189, D3DFMT_YUY2=844715353,
	D3DFMT_INDEX16=101, D3DFMT_INDEX32=102 };
enum _D3DRESOURCETYPE { D3DRTYPE_SURFACE=1, D3DRTYPE_VOLUME=2, D3DRTYPE_TEXTURE=3,
	D3DRTYPE_VOLUMETEXTURE=4, D3DRTYPE_CUBETEXTURE=5, D3DRTYPE_VERTEXBUFFER=6,
	D3DRTYPE_INDEXBUFFER=7, D3DRTYPE_FORCE_DWORD=0x7fffffff };
typedef enum _D3DRESOURCETYPE D3DRESOURCETYPE;
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
struct IDirect3DTexture8 : IDirect3DBaseTexture8 {
	virtual HRESULT __stdcall GetLevelDesc(UINT, void*) = 0;
	virtual HRESULT __stdcall GetSurfaceLevel(UINT, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall LockRect(UINT, void*, const void*, DWORD) = 0;
	virtual HRESULT __stdcall UnlockRect(UINT) = 0;
	virtual HRESULT __stdcall AddDirtyRect(const void*) = 0;
};
struct IDirect3DCubeTexture8 : IDirect3DBaseTexture8 {
	virtual HRESULT __stdcall GetLevelDesc(UINT, void*) = 0;
	virtual HRESULT __stdcall GetCubeMapSurface(DWORD, UINT, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall LockRect(DWORD, UINT, void*, const void*, DWORD) = 0;
	virtual HRESULT __stdcall UnlockRect(DWORD, UINT) = 0;
	virtual HRESULT __stdcall AddDirtyRect(DWORD, const void*) = 0;
};
enum _D3DCUBEMAP_FACES {
    D3DCUBEMAP_FACE_POSITIVE_X = 0,
    D3DCUBEMAP_FACE_NEGATIVE_X = 1,
    D3DCUBEMAP_FACE_POSITIVE_Y = 2,
    D3DCUBEMAP_FACE_NEGATIVE_Y = 3,
    D3DCUBEMAP_FACE_POSITIVE_Z = 4,
    D3DCUBEMAP_FACE_NEGATIVE_Z = 5
};
typedef enum _D3DCUBEMAP_FACES D3DCUBEMAP_FACES;
typedef struct _D3DVOLUME_DESC { D3DFORMAT Format; D3DRESOURCETYPE Type; DWORD Usage; D3DPOOL Pool; UINT Size; UINT Width; UINT Height; UINT Depth; } D3DVOLUME_DESC;
struct IDirect3DVolumeTexture8 : IDirect3DBaseTexture8 {
	virtual HRESULT __stdcall GetLevelDesc(UINT, void*) = 0;
	virtual HRESULT __stdcall GetVolumeLevel(UINT, void**) = 0;
	virtual HRESULT __stdcall LockBox(UINT, void*, const void*, DWORD) = 0;
	virtual HRESULT __stdcall UnlockBox(UINT) = 0;
	virtual HRESULT __stdcall AddDirtyBox(const void*) = 0;
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
	virtual HRESULT __stdcall CreateAdditionalSwapChain(struct _D3DPRESENT_PARAMETERS*, IDirect3DSwapChain8**) = 0;
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
	// Retail BFME device vtable is SDK + 7 slots from SetTransform onward: retail
	// calls SetTransform at +0xb0 (SDK +0x94), GetTransform +0xb4 (SDK +0x98),
	// SetRenderState +0xe4 (SDK +0xc8). Seven pure-virtuals occupied these slots
	// in BFME's d3d8 header; their signatures are unknown and unused by our
	// sources, but the slots must exist so every later method lands on the
	// retail vtable offset.
	virtual HRESULT __stdcall DevReserved37(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved38(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved39(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved40(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved41(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved42(DWORD) = 0;
	virtual HRESULT __stdcall DevReserved43(DWORD) = 0;
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

extern "C" HRESULT __stdcall D3DXFilterTexture(LPDIRECT3DTEXTURE8 pTexture, const PALETTEENTRY *pPalette, UINT SrcLevel, DWORD Filter);
// Verbatim DX8.1 d3dx8tex.h
extern "C" HRESULT __stdcall D3DXCreateTexture(LPDIRECT3DDEVICE8 pDevice, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE8 *ppTexture);
extern "C" HRESULT __stdcall D3DXCreateCubeTexture(LPDIRECT3DDEVICE8 pDevice, UINT Size, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8 **ppCubeTexture);
extern "C" HRESULT __stdcall D3DXCreateVolumeTexture(LPDIRECT3DDEVICE8 pDevice, UINT Width, UINT Height, UINT Depth, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8 **ppVolumeTexture);
extern "C" HRESULT __stdcall D3DXCreateTextureFromFileExA(LPDIRECT3DDEVICE8 pDevice, const char *pSrcFile, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, D3DCOLOR ColorKey, void *pSrcInfo, PALETTEENTRY *pPalette, LPDIRECT3DTEXTURE8 *ppTexture);
extern "C" HRESULT __stdcall D3DXCreateTextureFromFileA(LPDIRECT3DDEVICE8 pDevice, const char *pSrcFile, LPDIRECT3DTEXTURE8 *ppTexture);


// State/type enums — values become immediates at call sites so must match SDK.
typedef DWORD D3DRENDERSTATETYPE;
#define D3DRS_ZBIAS 47
#define D3DRS_ZENABLE 7
#define D3DRS_POINTSPRITEENABLE 156
#define D3DRS_POINTSCALEENABLE 157
#define D3DRS_POINTSIZE 154
#define D3DRS_POINTSIZE_MIN 155
#define D3DRS_POINTSCALE_A 158
#define D3DRS_POINTSCALE_B 159
#define D3DRS_POINTSCALE_C 160
#define D3DRS_POINTSIZE_MAX 166
#define D3DRS_SPECULARENABLE 29
#define D3DRS_DITHERENABLE 26
#define D3DRS_PATCHSEGMENTS 164

typedef int D3DCMPFUNC;	// ABI: enum = int; values are the D3DCMP_* defines

// D3DTEXOPCAPS_* texture-operation capability bits (d3d8caps.h)
#define D3DTEXOPCAPS_DISABLE 0x00000001L
#define D3DTEXOPCAPS_SELECTARG1 0x00000002L
#define D3DTEXOPCAPS_SELECTARG2 0x00000004L
#define D3DTEXOPCAPS_MODULATE 0x00000008L
#define D3DTEXOPCAPS_MODULATE2X 0x00000010L
#define D3DTEXOPCAPS_MODULATE4X 0x00000020L
#define D3DTEXOPCAPS_ADD 0x00000040L
#define D3DTEXOPCAPS_ADDSIGNED 0x00000080L
#define D3DTEXOPCAPS_ADDSIGNED2X 0x00000100L
#define D3DTEXOPCAPS_SUBTRACT 0x00000200L
#define D3DTEXOPCAPS_ADDSMOOTH 0x00000400L
#define D3DTEXOPCAPS_BLENDDIFFUSEALPHA 0x00000800L
#define D3DTEXOPCAPS_BLENDTEXTUREALPHA 0x00001000L
#define D3DTEXOPCAPS_BLENDFACTORALPHA 0x00002000L
#define D3DTEXOPCAPS_BLENDTEXTUREALPHAPM 0x00004000L
#define D3DTEXOPCAPS_BLENDCURRENTALPHA 0x00008000L
#define D3DTEXOPCAPS_PREMODULATE 0x00010000L
#define D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR 0x00020000L
#define D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA 0x00040000L
#define D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR 0x00080000L
#define D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA 0x00100000L
#define D3DTEXOPCAPS_BUMPENVMAP 0x00200000L
#define D3DTEXOPCAPS_BUMPENVMAPLUMINANCE 0x00400000L
#define D3DTEXOPCAPS_DOTPRODUCT3 0x00800000L
#define D3DTEXOPCAPS_MULTIPLYADD 0x01000000L
#define D3DTEXOPCAPS_LERP 0x02000000L
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
#define D3DRS_NORMALIZENORMALS 143
#define D3DRS_ALPHABLENDENABLE 27
#define D3DRS_SOFTWAREVERTEXPROCESSING 153
#define D3DRS_DIFFUSEMATERIALSOURCE 145
#define D3DRS_SPECULARMATERIALSOURCE 146
#define D3DRS_AMBIENTMATERIALSOURCE 147
#define D3DRS_EMISSIVEMATERIALSOURCE 148
#define D3DRS_VERTEXBLEND 151
#define D3DRS_CLIPPLANEENABLE 152
#define D3DRS_MULTISAMPLEANTIALIAS 161
#define D3DRS_MULTISAMPLEMASK 162
#define D3DRS_PATCHEDGESTYLE 163
#define D3DRS_DEBUGMONITORTOKEN 165
#define D3DRS_INDEXEDVERTEXBLENDENABLE 167
#define D3DRS_TWEENFACTOR 170
#define D3DDMT_ENABLE 0
#define D3DDMT_DISABLE 1
#define D3DFOG_EXP 1
#define D3DFOG_EXP2 2
#define D3DPATCHEDGE_DISCRETE 0
#define D3DPATCHEDGE_CONTINUOUS 1
#define D3DTEXF_FLATCUBIC 4
#define D3DTEXF_GAUSSIANCUBIC 5
#define D3DTOP_BLENDTEXTUREALPHAPM 15
#define D3DTOP_PREMODULATE 17
#define D3DTOP_MODULATECOLOR_ADDALPHA 19
#define D3DTOP_MODULATEINVALPHA_ADDCOLOR 20
#define D3DTOP_MODULATEINVCOLOR_ADDALPHA 21
#define D3DTOP_LERP 26
#define D3DTSS_MIPMAPLODBIAS 19
#define D3DTSS_MAXMIPLEVEL 20
#define D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR 0x30000L
#define D3DTA_SELECTMASK 0x0000000fL
#define D3DVBF_DISABLE 0
#define D3DVBF_1WEIGHTS 1
#define D3DVBF_2WEIGHTS 2
#define D3DVBF_3WEIGHTS 3
#define D3DVBF_TWEENING 255
#define D3DVBF_0WEIGHTS 256
#define D3DZB_FALSE 0
#define D3DZB_TRUE 1
#define D3DZB_USEW 2
#define D3DWRAP_U 1
#define D3DWRAP_V 2
#define D3DWRAP_W 4
#define D3DCOLORWRITEENABLE_RED 1
#define D3DCOLORWRITEENABLE_GREEN 2
#define D3DCOLORWRITEENABLE_BLUE 4
#define D3DCOLORWRITEENABLE_ALPHA 8
enum _D3DSHADEMODE { D3DSHADE_FLAT=1, D3DSHADE_GOURAUD=2, D3DSHADE_PHONG=3 };
typedef enum _D3DSHADEMODE D3DSHADEMODE;
enum _D3DCULL { D3DCULL_NONE=1, D3DCULL_CW=2, D3DCULL_CCW=3 };
typedef enum _D3DCULL D3DCULL;
enum _D3DMATERIALCOLORSOURCE { D3DMCS_MATERIAL=0, D3DMCS_COLOR1=1, D3DMCS_COLOR2=2 };
typedef enum _D3DMATERIALCOLORSOURCE D3DMATERIALCOLORSOURCE;
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
#define D3DTSS_COLORARG0 26
#define D3DTSS_ALPHAARG0 27
#define D3DTSS_RESULTARG 28
#define D3DTSS_MAXANISOTROPY 21
#define D3DTA_DIFFUSE 0
#define D3DTA_CURRENT 1
#define D3DTA_TEXTURE 2
#define D3DTA_TFACTOR 3
#define D3DTA_SPECULAR 4
#define D3DTA_TEMP 5
#define D3DTA_COMPLEMENT 0x10
#define D3DTA_ALPHAREPLICATE 0x20
#define D3DTSS_TCI_PASSTHRU 0x00000000
#define D3DTSS_TCI_CAMERASPACEPOSITION 0x00020000
#define D3DTSS_TCI_CAMERASPACENORMAL 0x00010000
#define D3DTOP_DISABLE 1
typedef int D3DTEXTUREOP;	// ABI: enum = int; values are the D3DTOP_* defines
#define D3DTOP_SELECTARG1 2
#define D3DTOP_SELECTARG2 3
#define D3DTOP_MODULATE 4
#define D3DTOP_MODULATE2X 5
#define D3DTOP_MODULATE4X 6
#define D3DTOP_ADD 7
#define D3DTOP_ADDSIGNED 8
#define D3DTOP_ADDSIGNED2X 9
#define D3DTOP_MODULATEALPHA_ADDCOLOR 18
#define D3DTOP_SUBTRACT 10
#define D3DTOP_ADDSMOOTH 11
#define D3DTOP_BLENDDIFFUSEALPHA 12
#define D3DTOP_MULTIPLYADD 25
#define D3DTOP_DOTPRODUCT3 24
#define D3DTOP_BUMPENVMAP 22
#define D3DTOP_BUMPENVMAPLUMINANCE 23
typedef enum _D3DBLEND {
	D3DBLEND_ZERO=1, D3DBLEND_ONE=2, D3DBLEND_SRCCOLOR=3, D3DBLEND_INVSRCCOLOR=4,
	D3DBLEND_SRCALPHA=5, D3DBLEND_INVSRCALPHA=6, D3DBLEND_DESTALPHA=7,
	D3DBLEND_INVDESTALPHA=8, D3DBLEND_DESTCOLOR=9, D3DBLEND_INVDESTCOLOR=10,
	D3DBLEND_SRCALPHASAT=11, D3DBLEND_BOTHSRCALPHA=12, D3DBLEND_BOTHINVSRCALPHA=13,
	D3DBLEND_FORCE_DWORD=0x7fffffff
} D3DBLEND;
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
#define D3DTADDRESS_WRAP 1
#define D3DTADDRESS_MIRROR 2
#define D3DTADDRESS_CLAMP 3
#define D3DTADDRESS_BORDER 4
#define D3DTADDRESS_MIRRORONCE 5
#define D3DTTFF_DISABLE 0
#define D3DTTFF_COUNT1 1
#define D3DTTFF_COUNT2 2
#define D3DTTFF_COUNT3 3
#define D3DTTFF_COUNT4 4
#define D3DTTFF_PROJECTED 256
#define D3DTOP_BLENDTEXTUREALPHA 13
#define D3DTOP_BLENDFACTORALPHA 14
#define D3DTOP_BLENDCURRENTALPHA 16
enum _D3DTRANSFORMSTATETYPE { D3DTS_VIEW=2, D3DTS_PROJECTION=3, D3DTS_WORLD=256,
	D3DTS_TEXTURE0=16, D3DTS_TEXTURE1=17, D3DTS_TEXTURE2=18, D3DTS_TEXTURE3=19,
	D3DTS_TEXTURE4=20, D3DTS_TEXTURE5=21, D3DTS_TEXTURE6=22, D3DTS_TEXTURE7=23 };
typedef enum _D3DTRANSFORMSTATETYPE D3DTRANSFORMSTATETYPE;
// D3DMATRIX: 4x4 float (64 bytes) — layout-bearing member of DX8Wrapper.
typedef struct _D3DMATRIX { float m[4][4]; } D3DMATRIX;
typedef struct _D3DXVECTOR2 { float x, y; } D3DXVECTOR2;
typedef struct _D3DXVECTOR3 { float x, y, z; } D3DXVECTOR3;
typedef struct _D3DXVECTOR4 {
    float x, y, z, w;
    _D3DXVECTOR4() {}
    _D3DXVECTOR4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    float operator[](int i) const { return (&x)[i]; }
    float& operator[](int i) { return (&x)[i]; }
} D3DXVECTOR4;
#ifndef BFME_D3DXMATRIX_DEFINED
#define BFME_D3DXMATRIX_DEFINED
typedef struct _D3DXMATRIX {
    union {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
    _D3DXMATRIX() {}
    _D3DXMATRIX(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33) {
        m[0][0]=m00; m[0][1]=m01; m[0][2]=m02; m[0][3]=m03;
        m[1][0]=m10; m[1][1]=m11; m[1][2]=m12; m[1][3]=m13;
        m[2][0]=m20; m[2][1]=m21; m[2][2]=m22; m[2][3]=m23;
        m[3][0]=m30; m[3][1]=m31; m[3][2]=m32; m[3][3]=m33;
    }
    _D3DXMATRIX operator*(const _D3DXMATRIX& o) const {
        _D3DXMATRIX r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.m[i][j] = m[i][0]*o.m[0][j] + m[i][1]*o.m[1][j] + m[i][2]*o.m[2][j] + m[i][3]*o.m[3][j];
        return r;
    }
} D3DXMATRIX;
#endif // BFME_D3DXMATRIX_DEFINED
typedef struct _D3DXPLANE { float a, b, c, d; } D3DXPLANE;
typedef struct _D3DXQUATERNION { float x, y, z, w; } D3DXQUATERNION;
#define D3DX_PI 3.141592654f
extern "C" D3DXMATRIX* __stdcall D3DXMatrixIdentity(D3DXMATRIX *pOut);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixInverse(D3DXMATRIX *pOut, float *pDeterminant, const D3DXMATRIX *pM);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixRotationX(D3DXMATRIX *pOut, float Angle);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixRotationY(D3DXMATRIX *pOut, float Angle);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixRotationZ(D3DXMATRIX *pOut, float Angle);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixTranslation(D3DXMATRIX *pOut, float x, float y, float z);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixScaling(D3DXMATRIX *pOut, float x, float y, float z);
extern "C" D3DXMATRIX* __stdcall D3DXMatrixTranspose(D3DXMATRIX *pOut, const D3DXMATRIX *pM);
extern "C" D3DXVECTOR4* __stdcall D3DXVec3Transform(D3DXVECTOR4 *pOut, const D3DXVECTOR3 *pV, const D3DXMATRIX *pM);
extern "C" D3DXVECTOR4* __stdcall D3DXVec4Transform(D3DXVECTOR4 *pOut, const D3DXVECTOR4 *pV, const D3DXMATRIX *pM);
extern "C" D3DXVECTOR3* __stdcall D3DXVec3Normalize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV);
extern "C" D3DXVECTOR3* __stdcall D3DXVec3Cross(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2);
extern "C" float __stdcall D3DXVec3Dot(const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2);
extern "C" float __stdcall D3DXVec4Dot(const D3DXVECTOR4 *pV1, const D3DXVECTOR4 *pV2);
extern "C" D3DXPLANE* __stdcall D3DXPlaneNormalize(D3DXPLANE *pOut, const D3DXPLANE *pP);
extern "C" D3DXQUATERNION* __stdcall D3DXQuaternionRotationMatrix(D3DXQUATERNION *pOut, const D3DXMATRIX *pM);
extern "C" D3DXQUATERNION* __stdcall D3DXQuaternionSlerp(D3DXQUATERNION *pOut, const D3DXQUATERNION *pQ1, const D3DXQUATERNION *pQ2, float t);
#define D3DX_FILTER_NONE (1 << 0)
#define D3DX_FILTER_POINT (2 << 0)
#define D3DX_FILTER_BOX (3 << 0)
#define D3DX_FILTER_TRIANGLE (4 << 0)
extern "C" HRESULT __stdcall D3DXLoadSurfaceFromSurface(IDirect3DSurface8 *pDestSurface, const void *pDestPalette, const void *pDestRect, IDirect3DSurface8 *pSrcSurface, const void *pSrcPalette, const void *pSrcRect, DWORD Filter, D3DCOLOR ColorKey);
typedef struct _D3DVIEWPORT8 { DWORD X,Y,Width,Height; float MinZ,MaxZ; } D3DVIEWPORT8;
typedef struct _D3DLOCKED_RECT { long Pitch; void *pBits; } D3DLOCKED_RECT;
typedef struct _D3DLOCKED_BOX { int RowPitch; int SlicePitch; void *pBits; } D3DLOCKED_BOX;
typedef struct _D3DSURFACE_DESC { D3DFORMAT Format; D3DRESOURCETYPE Type; DWORD Usage; D3DPOOL Pool; UINT Size; UINT Width; UINT Height; } D3DSURFACE_DESC;
#define D3DFILL_POINT 1
#define D3DFILL_WIREFRAME 2
#define D3DFILL_SOLID 3
#ifndef S_OK
#define S_OK 0
#endif
#ifndef _LARGE_INTEGER_DEFINED
#define _LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
    struct { DWORD LowPart; long HighPart; };
    __int64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
#endif

typedef struct _D3DADAPTER_IDENTIFIER8 {
	char Driver[512]; char Description[512];
	LARGE_INTEGER DriverVersion; DWORD VendorId, DeviceId, SubSysId, Revision;
	GUID DeviceIdentifier; DWORD WHQLLevel;
} D3DADAPTER_IDENTIFIER8;
enum _D3DDEVTYPE { D3DDEVTYPE_HAL=1, D3DDEVTYPE_REF=2, D3DDEVTYPE_SW=3, D3DDEVTYPE_FORCE_DWORD=0x7fffffff };
typedef enum _D3DDEVTYPE D3DDEVTYPE;
typedef struct _D3DCAPS8 {
    D3DDEVTYPE DeviceType;
    UINT AdapterOrdinal;
    DWORD Caps, Caps2, Caps3, PresentationIntervals;
    DWORD CursorCaps;
    DWORD DevCaps;
    DWORD PrimitiveMiscCaps, RasterCaps, ZCmpCaps, SrcBlendCaps, DestBlendCaps, AlphaCmpCaps;
    DWORD ShadeCaps, TextureCaps, TextureFilterCaps, CubeTextureFilterCaps, VolumeTextureFilterCaps;
    DWORD TextureAddressCaps, VolumeTextureAddressCaps;
    DWORD LineCaps;
    DWORD MaxTextureWidth, MaxTextureHeight, MaxVolumeExtent;
    DWORD MaxTextureRepeat, MaxTextureAspectRatio, MaxAnisotropy;
    float MaxVertexW;
    float GuardBandLeft, GuardBandTop, GuardBandRight, GuardBandBottom;
    float ExtentsAdjust;
    DWORD StencilCaps;
    DWORD FVFCaps, TextureOpCaps, MaxTextureBlendStages, MaxSimultaneousTextures;
    DWORD VertexProcessingCaps, MaxActiveLights, MaxUserClipPlanes, MaxVertexBlendMatrices, MaxVertexBlendMatrixIndex;
    float MaxPointSize;
    DWORD MaxPrimitiveCount, MaxVertexIndex, MaxStreams, MaxStreamStride;
    DWORD VertexShaderVersion, MaxVertexShaderConst;
    DWORD PixelShaderVersion;
    float MaxPixelShaderValue;
} D3DCAPS8;
#define D3DPMISCCAPS_COLORWRITEENABLE 0x00000080L
#define D3DPTEXTURECAPS_CUBEMAP 0x00000400L
#define D3DDEVCAPS_HWTRANSFORMANDLIGHT 0x00010000L
#define D3DDEVCAPS_NPATCHES 0x01000000L
#define D3DPRASTERCAPS_ZBIAS 0x00004000L
#define D3DPRASTERCAPS_FOGRANGE 0x00010000L
#define D3DRS_LINEPATTERN 10
#define D3DRS_LASTPIXEL 16
#define D3DRS_ZVISIBLE 30
#define D3DRS_FOGDENSITY 38
#define D3DRS_EDGEANTIALIAS 40
#define D3DRS_CLIPPING 136
#define D3DRS_WRAP0 128
#define D3DRS_WRAP1 129
#define D3DRS_WRAP2 130
#define D3DRS_WRAP3 131
#define D3DRS_WRAP4 132
#define D3DRS_WRAP5 133
#define D3DRS_WRAP6 134
#define D3DRS_WRAP7 135
#define D3DTSS_BORDERCOLOR 15
#define D3DBACKBUFFER_TYPE_MONO 0
#define D3DSGR_NO_CALIBRATION 0
#define D3DSGR_CALIBRATE 1
#define D3DSWAPEFFECT_COPY_VSYNC 4
typedef struct _D3DGAMMARAMP { WORD red[256], green[256], blue[256]; } D3DGAMMARAMP;
// Verbatim DX8.1 SDK constants (d3d8.h / d3d8types.h)
#define D3DCLEAR_TARGET 0x00000001L
#define D3DCLEAR_ZBUFFER 0x00000002L
#define D3DCLEAR_STENCIL 0x00000004L
#define D3DCREATE_FPU_PRESERVE 0x00000002L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING 0x00000020L
#define D3DCREATE_MIXED_VERTEXPROCESSING 0x00000080L
#define D3DENUM_NO_WHQL_LEVEL 0x00000002L
#define D3DERR_DEVICELOST 0x88760868L
#define D3DERR_DEVICENOTRESET 0x88760869L
#define D3DERR_WRONGTEXTUREFORMAT 0x88760872L
#define D3DERR_UNSUPPORTEDCOLOROPERATION 0x88760873L
#define D3DERR_UNSUPPORTEDCOLORARG 0x88760874L
#define D3DERR_UNSUPPORTEDALPHAOPERATION 0x88760875L
#define D3DERR_UNSUPPORTEDALPHAARG 0x88760876L
#define D3DERR_TOOMANYOPERATIONS 0x88760877L
#define D3DERR_CONFLICTINGTEXTUREFILTER 0x88760878L
#define D3DERR_UNSUPPORTEDFACTORVALUE 0x88760879L
#define D3DERR_UNSUPPORTEDTEXTUREFILTER 0x8876087BL
#define D3DERR_CONFLICTINGTEXTUREPALETTE 0x8876087CL
#define D3DFOG_NONE 0
#define D3DFOG_LINEAR 3
#define D3DMULTISAMPLE_NONE 0
#define D3DPRESENT_INTERVAL_DEFAULT 0x00000000L
#define D3DPRESENT_INTERVAL_ONE 0x00000001L
#define D3DPRESENT_INTERVAL_TWO 0x00000002L
#define D3DPRESENT_INTERVAL_THREE 0x00000004L
#define D3DPRESENT_INTERVAL_IMMEDIATE 0x80000000L
#define D3DPRESENT_RATE_DEFAULT 0x00000000L
#define D3DRS_FOGTABLEMODE 35
#define D3DRS_RANGEFOGENABLE 48
#define D3DRS_FOGVERTEXMODE 140
#define D3DRS_COLORVERTEX 141
#define D3DRS_LOCALVIEWER 142
#define D3DSWAPEFFECT_DISCARD 1
#define D3DERR_NOTAVAILABLE 0x8876086AL
#define D3DERR_OUTOFVIDEOMEMORY 0x8876017CL
#define D3DLIGHT_POINT 1
#define D3DLIGHT_SPOT 2
#define D3DLIGHT_DIRECTIONAL 3
#define D3DX_DEFAULT ((UINT)-1)
#define SWP_NOZORDER 0x0004
#define D3DCAPS2_FULLSCREENGAMMA 0x00020000L
#define D3DTEXOPCAPS_BUMPENVMAP 0x00000080L
#define D3DTEXOPCAPS_BUMPENVMAPLUMINANCE 0x00400000L
#define D3DTEXOPCAPS_DOTPRODUCT3 0x00000800L
#define D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR 0x00020000L
#define D3DPTFILTERCAPS_MINFLINEAR 0x00000200L
#define D3DPTFILTERCAPS_MINFPOINT 0x00000100L
#define D3DPTFILTERCAPS_MINFANISOTROPIC 0x00000400L
#define D3DPTFILTERCAPS_MIPFLINEAR 0x00020000L
#define D3DPTFILTERCAPS_MIPFPOINT 0x00010000L
#define D3DPTFILTERCAPS_MAGFLINEAR 0x02000000L
#define D3DPTFILTERCAPS_MAGFPOINT 0x01000000L
#define D3DPTFILTERCAPS_MAGFANISOTROPIC 0x04000000L
#define D3DTEXOPCAPS_BUMPENVMAPLUMINANCE 0x00400000L
typedef struct _D3DCOLORVALUE { float r, g, b, a; } D3DCOLORVALUE;
typedef struct _D3DLIGHT8 {  // verbatim DX8.1 d3d8types.h
    DWORD Type;  // D3DLIGHTTYPE
    D3DCOLORVALUE Diffuse, Specular, Ambient;
    D3DVECTOR Position, Direction;
    float Range, Falloff;
    float Attenuation0, Attenuation1, Attenuation2;
    float Theta, Phi;
} D3DLIGHT8;
typedef struct _D3DMATERIAL8 {
    D3DCOLORVALUE Diffuse, Ambient, Specular, Emissive;
    float Power;
} D3DMATERIAL8;
typedef struct _D3DDISPLAYMODE { UINT Width, Height, RefreshRate; D3DFORMAT Format; } D3DDISPLAYMODE;
typedef struct _D3DPRESENT_PARAMETERS {  // verbatim DX8.1 d3d8types.h
    UINT BackBufferWidth, BackBufferHeight;
    D3DFORMAT BackBufferFormat;
    UINT BackBufferCount;
    DWORD MultiSampleType;
    DWORD SwapEffect;
    HWND hDeviceWindow;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    D3DFORMAT AutoDepthStencilFormat;
    DWORD Flags;
    UINT FullScreen_RefreshRateInHz;
    UINT FullScreen_PresentationInterval;
} D3DPRESENT_PARAMETERS;
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
// Verbatim DX8.1 IDirect3DSwapChain8 vtable
typedef struct _D3DRASTER_STATUS { BOOL InVBlank; UINT ScanLine; } D3DRASTER_STATUS;
struct IDirect3DSwapChain8 {
	virtual HRESULT __stdcall QueryInterface(REFIID, void**) = 0;
	virtual DWORD __stdcall AddRef() = 0;
	virtual DWORD __stdcall Release() = 0;
	virtual HRESULT __stdcall Present(const RECT*, const RECT*, HWND, const void*) = 0;
	virtual HRESULT __stdcall GetBackBuffer(UINT, DWORD, IDirect3DSurface8**) = 0;
	virtual HRESULT __stdcall GetRasterStatus(D3DRASTER_STATUS*) = 0;
	virtual HRESULT __stdcall GetDisplayMode(D3DDISPLAYMODE*) = 0;
	virtual HRESULT __stdcall GetDevice(IDirect3DDevice8**) = 0;
	virtual HRESULT __stdcall GetPresentParameters(D3DPRESENT_PARAMETERS*) = 0;
};
typedef struct IDirect3DSwapChain8 *LPDIRECT3DSWAPCHAIN8;
#endif
