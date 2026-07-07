#pragma once
// Minimal <windows.h> stand-in for the ZH debug library bring-up. The vendored
// VS2003 toolchain ships no PlatformSDK, so we declare exactly what the lib uses.
// Signatures mirror the real SDK (dllimport + __stdcall) so codegen — stdcall
// IAT calls, argument sizes — is byte-identical to retail.
#ifndef DEBUG_WINDOWS_SHIM_H
#define DEBUG_WINDOWS_SHIM_H

// the real windows.h chain exposes the CRT basics the lib leans on
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

typedef void *HANDLE;
typedef void *HGLOBAL;
typedef void *HMODULE;
typedef void *HINSTANCE;
typedef void *HWND;
typedef unsigned long DWORD;
typedef unsigned long *LPDWORD;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned long SIZE_T;
typedef int (__stdcall *FARPROC)();

#define WINAPI __stdcall
#define WINAPIV __cdecl
#define CALLBACK __stdcall

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

struct _EXCEPTION_POINTERS;

#define MB_OK 0x00000000L
#define MB_ICONSTOP 0x00000010L
#define MB_TASKMODAL 0x00002000L
#define MB_SETFOREGROUND 0x00010000L
#define GMEM_FIXED 0x0000
#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define FILE_SHARE_READ 0x00000001
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG)-1)
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2

extern "C" {
__declspec(dllimport) int WINAPIV wsprintfA(LPSTR, LPCSTR, ...);
__declspec(dllimport) int WINAPI MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
__declspec(dllimport) BOOL WINAPI TerminateProcess(HANDLE, UINT);
__declspec(dllimport) HANDLE WINAPI GetCurrentProcess(void);
__declspec(dllimport) DWORD WINAPI GetCurrentThreadId(void);
__declspec(dllimport) HGLOBAL WINAPI GlobalAlloc(UINT, SIZE_T);
__declspec(dllimport) HGLOBAL WINAPI GlobalReAlloc(HGLOBAL, SIZE_T, UINT);
__declspec(dllimport) HGLOBAL WINAPI GlobalFree(HGLOBAL);
__declspec(dllimport) SIZE_T WINAPI GlobalSize(HGLOBAL);
__declspec(dllimport) HANDLE WINAPI CreateFileA(LPCSTR, DWORD, DWORD, void *, DWORD, DWORD, HANDLE);
__declspec(dllimport) BOOL WINAPI WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, void *);
__declspec(dllimport) BOOL WINAPI ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, void *);
__declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE);
__declspec(dllimport) DWORD WINAPI SetFilePointer(HANDLE, LONG, LONG *, DWORD);
__declspec(dllimport) BOOL WINAPI FlushFileBuffers(HANDLE);
__declspec(dllimport) BOOL WINAPI DeleteFileA(LPCSTR);
__declspec(dllimport) void WINAPI GetLocalTime(LPSYSTEMTIME);
__declspec(dllimport) DWORD WINAPI GetLastError(void);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameA(HMODULE, LPSTR, DWORD);
__declspec(dllimport) HMODULE WINAPI GetModuleHandleA(LPCSTR);
__declspec(dllimport) void WINAPI OutputDebugStringA(LPCSTR);
__declspec(dllimport) HMODULE WINAPI LoadLibraryA(LPCSTR);
__declspec(dllimport) FARPROC WINAPI GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) BOOL WINAPI FreeLibrary(HMODULE);
}

#define wsprintf wsprintfA
#define MessageBox MessageBoxA
#define CreateFile CreateFileA
#define DeleteFile DeleteFileA
#define GetModuleFileName GetModuleFileNameA
#define GetModuleHandle GetModuleHandleA
#define OutputDebugString OutputDebugStringA
#define LoadLibrary LoadLibraryA

#endif
