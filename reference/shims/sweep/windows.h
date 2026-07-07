#pragma once
// <windows.h> stand-in for sweeping GeneralsMD reference files: the vendored
// VS2003 toolchain has no PlatformSDK. Declarations mirror the real SDK
// (dllimport + __stdcall, exact struct layouts) so codegen is byte-identical.
// Grown empirically: the sweep's error histogram drives what gets added.
#ifndef SWEEP_WINDOWS_SHIM_H
#define SWEEP_WINDOWS_SHIM_H

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *HANDLE;
typedef void *HGLOBAL;
typedef void *HLOCAL;
typedef void *HMODULE;
typedef void *HINSTANCE;
typedef void *HWND;
typedef void *HDC;
typedef void *HKEY;
typedef void *HICON;
typedef void *HCURSOR;
typedef unsigned long DWORD;
typedef unsigned long *LPDWORD;
typedef unsigned long ULONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef unsigned char BYTE;
typedef long LONG;
typedef unsigned __int64 ULONGLONG;
typedef __int64 LONGLONG;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned short WCHAR;   // = VC7.1 default wchar_t (unsigned short), mangles as G like retail
typedef WCHAR *PWCHAR, *LPWSTR;
typedef const unsigned short *LPCWSTR;
typedef unsigned long SIZE_T;
typedef unsigned long ULONG_PTR;
typedef long *LPLONG;
typedef int (__stdcall *FARPROC)();

#define WINAPI __stdcall
#define WINAPIV __cdecl
#define CALLBACK __stdcall
#define VOID void
#define CONST const

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#define MAX_PATH 260

typedef struct _SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

typedef union _LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; };
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef struct _RTL_CRITICAL_SECTION {
    void *DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
} CRITICAL_SECTION, *LPCRITICAL_SECTION;

typedef struct _MEMORYSTATUS {
    DWORD dwLength, dwMemoryLoad;
    SIZE_T dwTotalPhys, dwAvailPhys, dwTotalPageFile, dwAvailPageFile, dwTotalVirtual, dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct tagRECT { LONG left, top, right, bottom; } RECT, *LPRECT;
typedef struct tagPOINT { LONG x, y; } POINT, *LPPOINT;

typedef struct _FILETIME { DWORD dwLowDateTime, dwHighDateTime; } FILETIME, *LPFILETIME;
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;
    char cFileName[MAX_PATH];
    char cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

struct _EXCEPTION_POINTERS;

#define MB_OK 0x00000000L
#define MB_OKCANCEL 0x00000001L
#define MB_ABORTRETRYIGNORE 0x00000002L
#define MB_YESNO 0x00000004L
#define MB_ICONSTOP 0x00000010L
#define MB_ICONERROR 0x00000010L
#define MB_ICONWARNING 0x00000030L
#define MB_ICONINFORMATION 0x00000040L
#define MB_TASKMODAL 0x00002000L
#define MB_SETFOREGROUND 0x00010000L
#define MB_SYSTEMMODAL 0x00001000L
#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7
#define GMEM_FIXED 0x0000
#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define CREATE_ALWAYS 2
#define CREATE_NEW 1
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_FLAG_WRITE_THROUGH 0x80000000
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define INFINITE 0xFFFFFFFF
#define WAIT_OBJECT_0 0

extern "C" {
__declspec(dllimport) int WINAPIV wsprintfA(LPSTR, LPCSTR, ...);
__declspec(dllimport) int WINAPI MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
__declspec(dllimport) BOOL WINAPI TerminateProcess(HANDLE, UINT);
__declspec(dllimport) HANDLE WINAPI GetCurrentProcess(void);
__declspec(dllimport) DWORD WINAPI GetCurrentProcessId(void);
__declspec(dllimport) DWORD WINAPI GetCurrentThreadId(void);
__declspec(dllimport) HANDLE WINAPI GetCurrentThread(void);
__declspec(dllimport) HGLOBAL WINAPI GlobalAlloc(UINT, SIZE_T);
__declspec(dllimport) HGLOBAL WINAPI GlobalReAlloc(HGLOBAL, SIZE_T, UINT);
__declspec(dllimport) HGLOBAL WINAPI GlobalFree(HGLOBAL);
__declspec(dllimport) SIZE_T WINAPI GlobalSize(HGLOBAL);
__declspec(dllimport) void WINAPI GlobalMemoryStatus(LPMEMORYSTATUS);
__declspec(dllimport) HANDLE WINAPI CreateFileA(LPCSTR, DWORD, DWORD, void *, DWORD, DWORD, HANDLE);
__declspec(dllimport) BOOL WINAPI WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, void *);
__declspec(dllimport) BOOL WINAPI ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, void *);
__declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE);
__declspec(dllimport) DWORD WINAPI SetFilePointer(HANDLE, LONG, LONG *, DWORD);
__declspec(dllimport) DWORD WINAPI GetFileSize(HANDLE, LPDWORD);
__declspec(dllimport) BOOL WINAPI FlushFileBuffers(HANDLE);
__declspec(dllimport) BOOL WINAPI DeleteFileA(LPCSTR);
__declspec(dllimport) BOOL WINAPI CopyFileA(LPCSTR, LPCSTR, BOOL);
__declspec(dllimport) BOOL WINAPI MoveFileA(LPCSTR, LPCSTR);
__declspec(dllimport) DWORD WINAPI GetFileAttributesA(LPCSTR);
__declspec(dllimport) BOOL WINAPI CreateDirectoryA(LPCSTR, void *);
__declspec(dllimport) HANDLE WINAPI FindFirstFileA(LPCSTR, LPWIN32_FIND_DATAA);
__declspec(dllimport) BOOL WINAPI FindNextFileA(HANDLE, LPWIN32_FIND_DATAA);
__declspec(dllimport) BOOL WINAPI FindClose(HANDLE);
__declspec(dllimport) void WINAPI GetLocalTime(LPSYSTEMTIME);
__declspec(dllimport) void WINAPI GetSystemTime(LPSYSTEMTIME);
__declspec(dllimport) DWORD WINAPI GetLastError(void);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameA(HMODULE, LPSTR, DWORD);
__declspec(dllimport) HMODULE WINAPI GetModuleHandleA(LPCSTR);
__declspec(dllimport) void WINAPI OutputDebugStringA(LPCSTR);
__declspec(dllimport) HMODULE WINAPI LoadLibraryA(LPCSTR);
__declspec(dllimport) FARPROC WINAPI GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) BOOL WINAPI FreeLibrary(HMODULE);
__declspec(dllimport) void WINAPI Sleep(DWORD);
__declspec(dllimport) DWORD WINAPI GetTickCount(void);
__declspec(dllimport) BOOL WINAPI QueryPerformanceCounter(PLARGE_INTEGER);
__declspec(dllimport) BOOL WINAPI QueryPerformanceFrequency(PLARGE_INTEGER);
__declspec(dllimport) void WINAPI InitializeCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void WINAPI DeleteCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void WINAPI EnterCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void WINAPI LeaveCriticalSection(LPCRITICAL_SECTION);
// exact 2003-era PSDK signatures — STLport's _threads.h re-declares these under
// extern "C", so any deviation (e.g. missing volatile) is a C2733 overload error
__declspec(dllimport) LONG WINAPI InterlockedIncrement(LONG volatile *);
__declspec(dllimport) LONG WINAPI InterlockedDecrement(LONG volatile *);
__declspec(dllimport) LONG WINAPI InterlockedExchange(LONG volatile *, LONG);
__declspec(dllimport) HANDLE WINAPI CreateEventA(void *, BOOL, BOOL, LPCSTR);
__declspec(dllimport) BOOL WINAPI SetEvent(HANDLE);
__declspec(dllimport) BOOL WINAPI ResetEvent(HANDLE);
__declspec(dllimport) HANDLE WINAPI CreateMutexA(void *, BOOL, LPCSTR);
__declspec(dllimport) BOOL WINAPI ReleaseMutex(HANDLE);
__declspec(dllimport) DWORD WINAPI WaitForSingleObject(HANDLE, DWORD);
__declspec(dllimport) UINT WINAPI SetErrorMode(UINT);
__declspec(dllimport) BOOL WINAPI IsDebuggerPresent(void);
__declspec(dllimport) void WINAPI DebugBreak(void);
__declspec(dllimport) LPSTR WINAPI GetCommandLineA(void);
__declspec(dllimport) DWORD WINAPI GetEnvironmentVariableA(LPCSTR, LPSTR, DWORD);
__declspec(dllimport) void WINAPI ExitProcess(UINT);
}

#define wsprintf wsprintfA
#define MessageBox MessageBoxA
#define CreateFile CreateFileA
#define DeleteFile DeleteFileA
#define CopyFile CopyFileA
#define MoveFile MoveFileA
#define GetFileAttributes GetFileAttributesA
#define CreateDirectory CreateDirectoryA
#define FindFirstFile FindFirstFileA
#define FindNextFile FindNextFileA
#define WIN32_FIND_DATA WIN32_FIND_DATAA
#define GetModuleFileName GetModuleFileNameA
#define GetModuleHandle GetModuleHandleA
#define OutputDebugString OutputDebugStringA
#define LoadLibrary LoadLibraryA
#define CreateEvent CreateEventA
#define CreateMutex CreateMutexA
#define GetCommandLine GetCommandLineA
#define GetEnvironmentVariable GetEnvironmentVariableA

#endif
