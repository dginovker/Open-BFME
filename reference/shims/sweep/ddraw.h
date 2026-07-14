/*
**  DirectDraw SDK shim — minimal declarations for sweep compilation
*/

#pragma once

#ifndef _DDRAW_H
#define _DDRAW_H

#include <windows.h>
#include <objbase.h>

// {6C14DB80-A733-11CE-A521-0020AF0BE560}
extern "C" const IID IID_IDirectDraw;

typedef unsigned long DWORD;
typedef DWORD* LPDWORD;
typedef long LONG;
typedef LONG* LPLONG;

// Pixel format
typedef struct _DDPIXELFORMAT {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	union {
		DWORD dwRGBBitCount;
		DWORD dwYUVBitCount;
		DWORD dwZBufferBitDepth;
		DWORD dwAlphaBitDepth;
	};
	union {
		DWORD dwRBitMask;
		DWORD dwYBitMask;
	};
	union {
		DWORD dwGBitMask;
		DWORD dwUBitMask;
	};
	union {
		DWORD dwBBitMask;
		DWORD dwVBitMask;
	};
	union {
		DWORD dwRGBAlphaBitMask;
		DWORD dwYUVAlphaBitMask;
	};
} DDPIXELFORMAT, *LPDDPIXELFORMAT;

// DirectDraw surface description
typedef struct _DDSCAPS { DWORD dwCaps; } DDSCAPS, *LPDDSCAPS;

typedef struct _DDCOLORKEY {
	DWORD dwColorSpaceLowValue;
	DWORD dwColorSpaceHighValue;
} DDCOLORKEY, *LPDDCOLORKEY;

typedef struct _DDSURFACEDESC {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwHeight;
	DWORD dwWidth;
	union {
		LONG lPitch;
		DWORD dwLinearSize;
	};
	DWORD dwBackBufferCount;
	union {
		DWORD dwMipMapCount;
		DWORD dwRefreshRate;
	};
	DWORD dwAlphaBitDepth;
	DWORD dwReserved;
	LPVOID lpSurface;
	DDCOLORKEY ddckCKDestOverlay;
	DDCOLORKEY ddckCKDestBlt;
	DDCOLORKEY ddckCKSrcOverlay;
	DDCOLORKEY ddckCKSrcBlt;
	DDPIXELFORMAT ddpfPixelFormat;
	DDSCAPS ddsCaps;
} DDSURFACEDESC, *LPDDSURFACEDESC;

// IDirectDrawSurface interface (partial)
struct IDirectDrawSurface;
struct IDirectDrawPalette;
struct IDirectDraw;
struct IDirectDraw2;
struct IDirectDrawClipper;
typedef IDirectDraw* LPDIRECTDRAW;
typedef IDirectDraw2* LPDIRECTDRAW2;
typedef IDirectDrawSurface* LPDIRECTDRAWSURFACE;
typedef IDirectDrawPalette* LPDIRECTDRAWPALETTE;
typedef IDirectDrawClipper* LPDIRECTDRAWCLIPPER;
typedef PALETTEENTRY* LPPALETTEENTRY;

// DDBLTFX
typedef struct _DDBLTFX {
	DWORD dwSize;
	DWORD dwDDFX;
	DWORD dwROP;
	DWORD dwDDROP;
	DWORD dwRotationAngle;
	DWORD dwZBufferOpCode;
	DWORD dwZBufferLow;
	DWORD dwZBufferHigh;
	DWORD dwZBufferBaseDest;
	DWORD dwZDestConstBitDepth;
	union { DWORD dwZDestConst; LPDIRECTDRAWSURFACE lpDDSZBufferDest; };
	DWORD dwZSrcConstBitDepth;
	union { DWORD dwZSrcConst; LPDIRECTDRAWSURFACE lpDDSZBufferSrc; };
	DWORD dwAlphaEdgeBlendBitDepth;
	DWORD dwAlphaEdgeBlend;
	DWORD dwReserved;
	DWORD dwAlphaDestConstBitDepth;
	union { DWORD dwAlphaDestConst; LPDIRECTDRAWSURFACE lpDDSAlphaDest; };
	DWORD dwAlphaSrcConstBitDepth;
	union { DWORD dwAlphaSrcConst; LPDIRECTDRAWSURFACE lpDDSAlphaSrc; };
	union { DWORD dwFillColor; DWORD dwFillDepth; DWORD dwFillPixel; LPDIRECTDRAWSURFACE lpDDSPattern; };
	DDCOLORKEY ddckDestColorkey;
	DDCOLORKEY ddckSrcColorkey;
} DDBLTFX, *LPDDBLTFX;

typedef struct _DDBLTBATCH *LPDDBLTBATCH;
typedef struct _DDOVERLAYFX *LPDDOVERLAYFX;
#define DD_ROP_SPACE (256/32)

typedef struct _DDCAPS_DX1
{
	DWORD dwSize;
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCKeyCaps;
	DWORD dwFXCaps;
	DWORD dwFXAlphaCaps;
	DWORD dwPalCaps;
	DWORD dwSVCaps;
	DWORD dwAlphaBltConstBitDepths;
	DWORD dwAlphaBltPixelBitDepths;
	DWORD dwAlphaBltSurfaceBitDepths;
	DWORD dwAlphaOverlayConstBitDepths;
	DWORD dwAlphaOverlayPixelBitDepths;
	DWORD dwAlphaOverlaySurfaceBitDepths;
	DWORD dwZBufferBitDepths;
	DWORD dwVidMemTotal;
	DWORD dwVidMemFree;
	DWORD dwMaxVisibleOverlays;
	DWORD dwCurrVisibleOverlays;
	DWORD dwNumFourCCCodes;
	DWORD dwAlignBoundarySrc;
	DWORD dwAlignSizeSrc;
	DWORD dwAlignBoundaryDest;
	DWORD dwAlignSizeDest;
	DWORD dwAlignStrideAlign;
	DWORD dwRops[DD_ROP_SPACE];
	DDSCAPS ddsCaps;
	DWORD dwMinOverlayStretch;
	DWORD dwMaxOverlayStretch;
	DWORD dwMinLiveVideoStretch;
	DWORD dwMaxLiveVideoStretch;
	DWORD dwMinHwCodecStretch;
	DWORD dwMaxHwCodecStretch;
	DWORD dwReserved1;
	DWORD dwReserved2;
	DWORD dwReserved3;
} DDCAPS_DX1, *LPDDCAPS_DX1;

typedef struct _DDCAPS_DX3
{
	DWORD dwSize;
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCKeyCaps;
	DWORD dwFXCaps;
	DWORD dwFXAlphaCaps;
	DWORD dwPalCaps;
	DWORD dwSVCaps;
	DWORD dwAlphaBltConstBitDepths;
	DWORD dwAlphaBltPixelBitDepths;
	DWORD dwAlphaBltSurfaceBitDepths;
	DWORD dwAlphaOverlayConstBitDepths;
	DWORD dwAlphaOverlayPixelBitDepths;
	DWORD dwAlphaOverlaySurfaceBitDepths;
	DWORD dwZBufferBitDepths;
	DWORD dwVidMemTotal;
	DWORD dwVidMemFree;
	DWORD dwMaxVisibleOverlays;
	DWORD dwCurrVisibleOverlays;
	DWORD dwNumFourCCCodes;
	DWORD dwAlignBoundarySrc;
	DWORD dwAlignSizeSrc;
	DWORD dwAlignBoundaryDest;
	DWORD dwAlignSizeDest;
	DWORD dwAlignStrideAlign;
	DWORD dwRops[DD_ROP_SPACE];
	DDSCAPS ddsCaps;
	DWORD dwMinOverlayStretch;
	DWORD dwMaxOverlayStretch;
	DWORD dwMinLiveVideoStretch;
	DWORD dwMaxLiveVideoStretch;
	DWORD dwMinHwCodecStretch;
	DWORD dwMaxHwCodecStretch;
	DWORD dwReserved1;
	DWORD dwReserved2;
	DWORD dwReserved3;
	DWORD dwSVBCaps;
	DWORD dwSVBCKeyCaps;
	DWORD dwSVBFXCaps;
	DWORD dwSVBRops[DD_ROP_SPACE];
	DWORD dwVSBCaps;
	DWORD dwVSBCKeyCaps;
	DWORD dwVSBFXCaps;
	DWORD dwVSBRops[DD_ROP_SPACE];
	DWORD dwSSBCaps;
	DWORD dwSSBCKeyCaps;
	DWORD dwSSBFXCaps;
	DWORD dwSSBRops[DD_ROP_SPACE];
	DWORD dwReserved4;
	DWORD dwReserved5;
	DWORD dwReserved6;
} DDCAPS_DX3, *LPDDCAPS_DX3;

typedef struct _DDCAPS_DX5
{
	DWORD dwSize;
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCKeyCaps;
	DWORD dwFXCaps;
	DWORD dwFXAlphaCaps;
	DWORD dwPalCaps;
	DWORD dwSVCaps;
	DWORD dwAlphaBltConstBitDepths;
	DWORD dwAlphaBltPixelBitDepths;
	DWORD dwAlphaBltSurfaceBitDepths;
	DWORD dwAlphaOverlayConstBitDepths;
	DWORD dwAlphaOverlayPixelBitDepths;
	DWORD dwAlphaOverlaySurfaceBitDepths;
	DWORD dwZBufferBitDepths;
	DWORD dwVidMemTotal;
	DWORD dwVidMemFree;
	DWORD dwMaxVisibleOverlays;
	DWORD dwCurrVisibleOverlays;
	DWORD dwNumFourCCCodes;
	DWORD dwAlignBoundarySrc;
	DWORD dwAlignSizeSrc;
	DWORD dwAlignBoundaryDest;
	DWORD dwAlignSizeDest;
	DWORD dwAlignStrideAlign;
	DWORD dwRops[DD_ROP_SPACE];
	DDSCAPS ddsCaps;
	DWORD dwMinOverlayStretch;
	DWORD dwMaxOverlayStretch;
	DWORD dwMinLiveVideoStretch;
	DWORD dwMaxLiveVideoStretch;
	DWORD dwMinHwCodecStretch;
	DWORD dwMaxHwCodecStretch;
	DWORD dwReserved1;
	DWORD dwReserved2;
	DWORD dwReserved3;
	DWORD dwSVBCaps;
	DWORD dwSVBCKeyCaps;
	DWORD dwSVBFXCaps;
	DWORD dwSVBRops[DD_ROP_SPACE];
	DWORD dwVSBCaps;
	DWORD dwVSBCKeyCaps;
	DWORD dwVSBFXCaps;
	DWORD dwVSBRops[DD_ROP_SPACE];
	DWORD dwSSBCaps;
	DWORD dwSSBCKeyCaps;
	DWORD dwSSBFXCaps;
	DWORD dwSSBRops[DD_ROP_SPACE];
	DWORD dwMaxVideoPorts;
	DWORD dwCurrVideoPorts;
	DWORD dwSVBCaps2;
	DWORD dwNLVBCaps;
	DWORD dwNLVBCaps2;
	DWORD dwNLVBCKeyCaps;
	DWORD dwNLVBFXCaps;
	DWORD dwNLVBRops[DD_ROP_SPACE];
} DDCAPS_DX5, *LPDDCAPS_DX5;

typedef DDCAPS_DX3 DDCAPS;
typedef DDCAPS *LPDDCAPS;
typedef struct _RGNDATA *LPRGNDATA;
typedef HRESULT (STDMETHODCALLTYPE *LPDDENUMSURFACESCALLBACK)(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC, LPVOID);
typedef HRESULT (STDMETHODCALLTYPE *LPDDENUMMODESCALLBACK)(LPDDSURFACEDESC, LPVOID);

struct IDirectDrawClipper : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE GetClipList(LPRECT, LPRGNDATA, DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetHWnd(HWND*) = 0;
	virtual HRESULT STDMETHODCALLTYPE Initialize(LPDIRECTDRAW, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetClipList(LPRGNDATA, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetHWnd(DWORD, HWND) = 0;
};

struct IDirectDrawSurface : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE AddAttachedSurface(LPDIRECTDRAWSURFACE) = 0;
	virtual HRESULT STDMETHODCALLTYPE AddOverlayDirtyRect(LPRECT) = 0;
	virtual HRESULT STDMETHODCALLTYPE Blt(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDBLTFX) = 0;
	virtual HRESULT STDMETHODCALLTYPE BltBatch(LPDDBLTBATCH, DWORD, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE BltFast(DWORD, DWORD, LPDIRECTDRAWSURFACE, LPRECT, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE DeleteAttachedSurface(DWORD, LPDIRECTDRAWSURFACE) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumAttachedSurfaces(LPVOID, LPDDENUMSURFACESCALLBACK) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumOverlayZOrders(DWORD, LPVOID, LPDDENUMSURFACESCALLBACK) = 0;
	virtual HRESULT STDMETHODCALLTYPE Flip(LPDIRECTDRAWSURFACE, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetAttachedSurface(LPDDSCAPS, LPDIRECTDRAWSURFACE*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetBltStatus(DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCaps(LPDDSCAPS) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetClipper(LPDIRECTDRAWCLIPPER*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetColorKey(DWORD, LPDDCOLORKEY) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetDC(HDC*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFlipStatus(DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetOverlayPosition(LPLONG, LPLONG) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetPalette(LPDIRECTDRAWPALETTE*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetPixelFormat(LPDDPIXELFORMAT) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetSurfaceDesc(LPDDSURFACEDESC) = 0;
	virtual HRESULT STDMETHODCALLTYPE Initialize(LPDIRECTDRAW, LPDDSURFACEDESC) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsLost() = 0;
	virtual HRESULT STDMETHODCALLTYPE Lock(LPRECT, LPDDSURFACEDESC, DWORD, HANDLE) = 0;
	virtual HRESULT STDMETHODCALLTYPE ReleaseDC(HDC) = 0;
	virtual HRESULT STDMETHODCALLTYPE Restore() = 0;
	virtual HRESULT STDMETHODCALLTYPE SetClipper(LPDIRECTDRAWCLIPPER) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetColorKey(DWORD, LPDDCOLORKEY) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetOverlayPosition(LONG, LONG) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetPalette(LPDIRECTDRAWPALETTE) = 0;
	virtual HRESULT STDMETHODCALLTYPE Unlock(LPVOID) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateOverlay(LPRECT, LPDIRECTDRAWSURFACE, LPRECT, DWORD, LPDDOVERLAYFX) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateOverlayDisplay(DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE UpdateOverlayZOrder(DWORD, LPDIRECTDRAWSURFACE) = 0;
};

struct IDirectDrawPalette : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE GetCaps(DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetEntries(DWORD, DWORD, DWORD, PALETTEENTRY*) = 0;
	virtual HRESULT STDMETHODCALLTYPE Initialize(LPDIRECTDRAW, DWORD, PALETTEENTRY*) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetEntries(DWORD, DWORD, DWORD, PALETTEENTRY*) = 0;
};

// IDirectDraw interface (partial)
struct IDirectDraw : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE Compact() = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateClipper(DWORD, LPDIRECTDRAWCLIPPER*, IUnknown*) = 0;
	virtual HRESULT STDMETHODCALLTYPE CreatePalette(DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE*, IUnknown*) = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateSurface(LPDDSURFACEDESC, LPDIRECTDRAWSURFACE*, IUnknown*) = 0;
	virtual HRESULT STDMETHODCALLTYPE DuplicateSurface(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE*) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumDisplayModes(DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumSurfaces(DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMSURFACESCALLBACK) = 0;
	virtual HRESULT STDMETHODCALLTYPE FlipToGDISurface() = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCaps(LPDDCAPS, LPDDCAPS) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetDisplayMode(LPDDSURFACEDESC) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetFourCCCodes(DWORD*, DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetGDISurface(LPDIRECTDRAWSURFACE*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetMonitorFrequency(DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetScanLine(DWORD*) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetVerticalBlankStatus(BOOL*) = 0;
	virtual HRESULT STDMETHODCALLTYPE Initialize(GUID*) = 0;
	virtual HRESULT STDMETHODCALLTYPE RestoreDisplayMode() = 0;
	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetDisplayMode(DWORD, DWORD, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE WaitForVerticalBlank(DWORD, HANDLE) = 0;
};

// IDirectDraw2 inherits from IDirectDraw (extends vtable past it)
struct IDirectDraw2 : public IDirectDraw {};

HRESULT WINAPI DirectDrawCreate(GUID* lpGUID, LPDIRECTDRAW* lplpDD, IUnknown* pUnkOuter);

// DD flags
#define DDSD_CAPS           0x00000001l
#define DDSD_HEIGHT         0x00000002l
#define DDSD_WIDTH          0x00000004l
#define DDSD_PITCH          0x00000008l
#define DDSD_BACKBUFFERCOUNT 0x00000020l
#define DDSD_PIXELFORMAT    0x00001000l
#define DDSCAPS_PRIMARYSURFACE 0x00000200l
#define DDSCAPS_COMPLEX     0x00000008l
#define DDSCAPS_FLIP        0x00000010l
#define DDSCAPS_BACKBUFFER  0x00000004l
#define DDSCAPS_SYSTEMMEMORY 0x00000800l
#define DDSCAPS2_CUBEMAP    0x00000200l
#define DDSCAPS2_VOLUME     0x00200000l
#define DDSCAPS2_CUBEMAP_POSITIVEX 0x00000400l
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0x00000800l
#define DDSCAPS2_CUBEMAP_POSITIVEY 0x00001000l
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x00002000l
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x00004000l
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x00008000l
#define DDSCAPS2_CUBEMAP_ALLFACES (DDSCAPS2_CUBEMAP_POSITIVEX|DDSCAPS2_CUBEMAP_NEGATIVEX|DDSCAPS2_CUBEMAP_POSITIVEY|DDSCAPS2_CUBEMAP_NEGATIVEY|DDSCAPS2_CUBEMAP_POSITIVEZ|DDSCAPS2_CUBEMAP_NEGATIVEZ)
#define DDSCAPS_VIDEOMEMORY 0x00004000l
#define DDSCAPS_OFFSCREENPLAIN 0x00000040l
#define DDSCAPS_LOCALVIDMEM  0x10000000l
#define DDERR_INVALIDDIRECTDRAWGUID 0x887600A0
#define DDERR_UNSUPPORTED           0x8876005B
#define DDERR_GENERIC               0x80004005
#define DDCAPS_BLTCOLORFILL         0x00000004l
#define DDSCL_NORMAL        0x00000008l
#define DDSCL_EXCLUSIVE     0x00000001l
#define DDSCL_FULLSCREEN    0x00000001l

#define DD_OK 0
#define DDERR_INVALIDDIRECTDRAWGUID 0x887600A0
#define DDERR_UNSUPPORTED           0x8876005B
#define DDERR_GENERIC               0x80004005
#define DDERR_SURFACELOST           0x887601C2

#define DDLOCK_SURFACEMEMORYPTR     0x00000000L
#define DDLOCK_WAIT                 0x00000001L
#define DDBLT_WAIT                  0x01000000L
#define DDBLT_COLORFILL             0x00000400L

#define DDCAPS_3D                   0x00000001L
#define DDCAPS_ALIGNBOUNDARYDEST    0x00000002L
#define DDCAPS_ALIGNSIZEDEST        0x00000004L
#define DDCAPS_ALIGNBOUNDARYSRC     0x00000008L
#define DDCAPS_ALIGNSIZESRC         0x00000010L
#define DDCAPS_ALIGNSTRIDE          0x00000020L
#define DDCAPS_BLT                  0x00000040L
#define DDCAPS_BLTQUEUE             0x00000080L
#define DDCAPS_BLTFOURCC            0x00000100L
#define DDCAPS_BLTSTRETCH           0x00000200L
#define DDCAPS_GDI                  0x00000400L
#define DDCAPS_OVERLAY              0x00000800L
#define DDCAPS_PALETTE              0x00008000L
#define DDCAPS_PALETTEVSYNC         0x00010000L
#define DDCAPS_READSCANLINE         0x00020000L
#define DDCAPS_VBI                  0x00080000L
#define DDCAPS_ZBLTS                0x00100000L
#define DDCAPS_ZOVERLAYS            0x00200000L
#define DDCAPS_COLORKEY             0x00400000L
#define DDCAPS_ALPHA                0x00800000L
#define DDCAPS_COLORKEYHWASSIST     0x01000000L
#define DDCAPS_NOHARDWARE           0x02000000L
#define DDCAPS_BLTCOLORFILL         0x04000000L
#define DDCAPS_BANKSWITCHED         0x08000000L
#define DDCAPS_BLTDEPTHFILL         0x10000000L
#define DDCAPS_CANCLIP              0x20000000L
#define DDCAPS_CANCLIPSTRETCHED     0x40000000L
#define DDCAPS_CANBLTSYSMEM         0x80000000L

#define DDWAITVB_BLOCKBEGIN         0x00000001L
#define DDWAITVB_BLOCKBEGINEVENT    0x00000002L
#define DDWAITVB_BLOCKEND           0x00000004L

#define DDGBS_CANBLT                0x00000001L
#define DDGBS_ISBLTDONE             0x00000002L

#ifndef E_NOTIMPL
#define E_NOTIMPL                   0x80004001L
#endif

#endif

#define DDPCAPS_4BIT 0x00000001L
#define DDPCAPS_8BITENTRIES 0x00000002L
#define DDPCAPS_8BIT 0x00000004L
#define DDPCAPS_ALLOW256 0x00000040L
