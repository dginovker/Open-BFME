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
	DDPIXELFORMAT ddpfPixelFormat;
} DDSURFACEDESC, *LPDDSURFACEDESC;

// DDSCAPS
typedef struct _DDSCAPS { DWORD dwCaps; } DDSCAPS, *LPDDSCAPS;

// DDBLTFX
typedef struct _DDBLTFX {
	DWORD dwSize;
	DWORD dwDDFX;
	DWORD dwROP;
} DDBLTFX, *LPDDBLTFX;

// IDirectDrawSurface interface (partial)
struct IDirectDrawSurface : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE __pad1() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad2() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad3() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad4() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad5() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad6() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad7() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad8() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad9() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad10() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad11() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad12() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad13() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad14() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad15() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad16() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad17() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad18() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad19() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad20() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad21() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad22() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad23() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad24() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad25() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad26() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad27() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad28() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad29() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad30() = 0;
	virtual HRESULT STDMETHODCALLTYPE GetDC(HDC*) = 0;
	virtual HRESULT STDMETHODCALLTYPE ReleaseDC(HDC) = 0;
};

struct IDirectDrawPalette : public IUnknown {};

// IDirectDraw interface (partial)
struct IDirectDraw : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetDisplayMode(DWORD, DWORD, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad3() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad4() = 0;
	virtual HRESULT STDMETHODCALLTYPE CreateSurface(LPDDSURFACEDESC, LPDIRECTDRAWSURFACE*, IUnknown*) = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad6() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad7() = 0;
	virtual HRESULT STDMETHODCALLTYPE __pad8() = 0;
	virtual HRESULT STDMETHODCALLTYPE CreatePalette(DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE*, IUnknown*) = 0;
};

// IDirectDraw2 inherits from IDirectDraw (extends vtable past it)
struct IDirectDraw2 : public IDirectDraw {};

typedef IDirectDraw* LPDIRECTDRAW;
typedef IDirectDraw2* LPDIRECTDRAW2;
typedef IDirectDrawSurface* LPDIRECTDRAWSURFACE;
typedef IDirectDrawPalette* LPDIRECTDRAWPALETTE;

typedef PALETTEENTRY* LPPALETTEENTRY;

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

#endif
