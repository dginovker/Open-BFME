/*
**  Minimal wmsdk.h shim — provides the Win32 wave/WM types needed by
**  simpleplayer.h so the sweep build can proceed.
*/

#pragma once

#ifndef WMSDK_H
#define WMSDK_H

// Standard Win32 wave types
typedef void VOID;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef int BOOL;
typedef void* HANDLE;
typedef wchar_t WCHAR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef long LONG;
typedef unsigned __int64 QWORD;

#ifndef REFIID_DEFINED
typedef void* REFIID;
#define REFIID_DEFINED
#endif

#ifndef IID_DEFINED
struct IID {};
#define IID_DEFINED
#endif

typedef long HRESULT;
#define S_OK ((HRESULT)0L)
#define E_FAIL ((HRESULT)0x80004005L)
#define E_UNEXPECTED ((HRESULT)0x8000FFFFL)

#define MAX_PATH 260

extern const wchar_t* wcsstr(const wchar_t*, const unsigned short*);
extern int memcmp(const void*, const void*, unsigned int);

// Wave types
typedef struct _WAVEFORMATEX {
    WORD  wFormatTag;
    WORD  nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD  nBlockAlign;
    WORD  wBitsPerSample;
    WORD  cbSize;
} WAVEFORMATEX, *LPWAVEFORMATEX;

typedef struct wavehdr_tag {
    LPSTR  lpData;
    DWORD  dwBufferLength;
    DWORD  dwBytesRecorded;
    DWORD_PTR dwUser;
    DWORD  dwFlags;
    DWORD  dwLoops;
    struct wavehdr_tag* lpNext;
    DWORD_PTR reserved;
} WAVEHDR, *LPWAVEHDR;

typedef void* HWAVEOUT;
typedef void* HMMIO;

#define CALLBACK __stdcall
#define STDMETHODCALLTYPE __stdcall

typedef unsigned long ULONG;
typedef unsigned int UINT;
#define __RPC_FAR

// Critical section
struct CRITICAL_SECTION { void* DebugInfo; long LockCount; long RecursionCount; void* OwningThread; void* LockSemaphore; unsigned long SpinCount; };

// WM reader types (forward declarations — sweep doesn't instantiate these)
struct IWMReaderCallback { virtual ~IWMReaderCallback() {} };
struct IWMReader {};
struct IWMHeaderInfo {};
struct INSSBuffer {};

typedef enum tagWMT_STATUS { WMT_ERROR=1, WMT_OPENED, WMT_BUFFERING_START, WMT_BUFFERING_STOP, WMT_EOF } WMT_STATUS;
typedef enum tagWMT_ATTR_DATATYPE { WMT_TYPE_DWORD=0, WMT_TYPE_STRING, WMT_TYPE_BINARY, WMT_TYPE_BOOL, WMT_TYPE_QWORD, WMT_TYPE_WORD, WMT_TYPE_GUID } WMT_ATTR_DATATYPE;

// IID constants referenced by simpleplayer.cpp
extern const IID IID_IWMReader;
extern const IID IID_IWMHeaderInfo;

#endif // WMSDK_H
