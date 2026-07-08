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
#include <ctype.h>
#include <errno.h>

// GameMemory.h defines the ARRAY placement new/delete itself; keep VC7.1's <new>
// from also defining them. Lives here (not just the PreRTS shim) because device-side
// TUs include <windows.h> + engine headers directly, never PreRTS.
#ifndef __PLACEMENT_VEC_NEW_INLINE
#define __PLACEMENT_VEC_NEW_INLINE
#endif

typedef void *HANDLE;
typedef void *HGLOBAL;
typedef void *HLOCAL;
typedef void *HMODULE;
typedef void *HINSTANCE;
typedef void *HWND;
typedef void *HDC;
typedef void *HFONT;
typedef void *HBITMAP;
typedef void *HGDIOBJ;
typedef void *HPEN;
typedef void *HBRUSH;
typedef void *HKEY;
#define HKEY_LOCAL_MACHINE ((HKEY)(ULONG_PTR)0x80000002)
#define HKEY_CURRENT_USER ((HKEY)(ULONG_PTR)0x80000001)
#define REG_OPTION_NON_VOLATILE 0
#define KEY_WRITE 0x00020006
#define KEY_READ 0x00020019
#define KEY_ALL_ACCESS 0x000F003F
#define REG_SZ 1
#define REG_DWORD 4
typedef void *HICON;
typedef void *HCURSOR;
typedef void *HRSRC;
typedef void *HKL;
typedef unsigned long DWORD;
typedef unsigned long *LPDWORD;
typedef unsigned long ULONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef short SHORT;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef HKEY *PHKEY;
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
typedef long LONG_PTR;
typedef unsigned int UINT_PTR;
typedef long *LPLONG;
typedef BOOL *LPBOOL;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
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
#define MAX_COMPUTERNAME_LENGTH 31
#define LOWORD(l) ((WORD)((DWORD)(l) & 0xFFFF))
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#ifndef MAKEWORD
#define MAKEWORD(a,b) ((WORD)(((BYTE)((a) & 0xFF)) | ((WORD)((BYTE)((b) & 0xFF))) << 8))
#endif
#define UNLEN 256
#define LOBYTE(w) ((BYTE)((w) & 0xFF))
#define HIBYTE(w) ((BYTE)(((w) >> 8) & 0xFF))

typedef LONG HRESULT;
#define S_OK ((HRESULT)0)
#define S_FALSE ((HRESULT)1)
#define E_FAIL ((HRESULT)0x80004005)
#define E_INVALIDARG ((HRESULT)0x80070057)
#define E_OUTOFMEMORY ((HRESULT)0x8007000E)
#define E_UNEXPECTED ((HRESULT)0x8000FFFF)

struct _EXCEPTION_POINTERS; // fwd-declare for Minidump handlers / crash reporters
typedef struct _ITEMIDLIST { BYTE abID[1]; } ITEMIDLIST, *LPITEMIDLIST;
#define LOCALE_SYSTEM_DEFAULT 0x0800
#define DATE_SHORTDATE 0x00000001
#define DATE_LONGDATE 0x00000002
#define TIME_NOSECONDS 0x00000002
#define TIME_NOTIMEMARKER 0x00000004
#define TIME_FORCE24HOURFORMAT 0x00000008

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

typedef struct _OSVERSIONINFOA {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    char szCSDVersion[128];
} OSVERSIONINFOA, *LPOSVERSIONINFOA;

typedef struct _STARTUPINFOA {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX, dwY, dwXSize, dwYSize;
    DWORD dwXCountChars, dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput, hStdOutput, hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;
#define OSVERSIONINFO OSVERSIONINFOA
#define VER_PLATFORM_WIN32_WINDOWS 1
#define VER_PLATFORM_WIN32_NT 2

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
#define MB_ICONHAND 0x00000010L
#define MB_ICONQUESTION 0x00000020L
#define MB_ICONWARNING 0x00000030L
#define MB_ICONEXCLAMATION 0x00000030L
#define MB_ICONINFORMATION 0x00000040L
#define MB_ICONASTERISK 0x00000040L
#define MB_TASKMODAL 0x00002000L
#define MB_SETFOREGROUND 0x00010000L
#define MB_SYSTEMMODAL 0x00001000L
#define IDOK 1
#define MB_APPLMODAL 0x00000000L
#define MB_DEFBUTTON3 0x00000200L
#define VK_RETURN 0x0D
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define ERROR_SUCCESS 0L
#define CP_ACP 0
#define CP_UTF8 65001
#define EINVAL 22
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200
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
#define HWND_TOP ((HWND)0)
#define HWND_BOTTOM ((HWND)1)
#define HWND_TOPMOST ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SW_HIDE 0
#define SW_SHOW 1
#define SW_SHOWNORMAL 1
#define DRIVE_CDROM 5
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_MOUSEWHEEL 0x020A
#define STARTF_USESHOWWINDOW 0x00000001
#define STARTF_USESTDHANDLES 0x00000100

extern "C" {
__declspec(dllimport) int WINAPIV wsprintfA(LPSTR, LPCSTR, ...);
__declspec(dllimport) int WINAPI lstrcmpA(LPCSTR, LPCSTR);
__declspec(dllimport) int WINAPI lstrcmpW(LPCWSTR, LPCWSTR);
__declspec(dllimport) int WINAPI lstrcmpiA(LPCSTR, LPCSTR);
__declspec(dllimport) int WINAPI lstrcmpiW(LPCWSTR, LPCWSTR);
#define lstrcmp lstrcmpA
#define lstrcmpi lstrcmpiA
__declspec(dllimport) int WINAPI MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
__declspec(dllimport) int WINAPI MessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);
__declspec(dllimport) BOOL WINAPI SetWindowPos(HWND, HWND, int, int, int, int, UINT);
__declspec(dllimport) BOOL WINAPI ShowWindow(HWND, int);
__declspec(dllimport) BOOL WINAPI CreateProcessA(LPCSTR, LPSTR, void *, void *, BOOL, DWORD, void *, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
__declspec(dllimport) UINT WINAPI GetTempFileNameA(LPCSTR, LPCSTR, UINT, LPSTR);
__declspec(dllimport) HINSTANCE WINAPI FindExecutableA(LPCSTR, LPCSTR, LPSTR);
__declspec(dllimport) BOOL WINAPI ScreenToClient(HWND, LPPOINT);
__declspec(dllimport) HCURSOR WINAPI LoadCursorFromFileA(LPCSTR);
__declspec(dllimport) HCURSOR WINAPI SetCursor(HCURSOR);
__declspec(dllimport) BOOL WINAPI GetCursorPos(LPPOINT);
__declspec(dllimport) SHORT WINAPI GetAsyncKeyState(int);
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
__declspec(dllimport) DWORD WINAPI timeGetTime(void);
__declspec(dllimport) UINT WINAPI GetDoubleClickTime(void);
__declspec(dllimport) BOOL WINAPI RemoveFontResourceA(LPCSTR);
#define RemoveFontResource RemoveFontResourceA
__declspec(dllimport) int WINAPI AddFontResourceA(LPCSTR);
#define AddFontResource AddFontResourceA
__declspec(dllimport) BOOL WINAPI GetVersionExA(LPOSVERSIONINFOA);
#define GetVersionEx GetVersionExA
#define GetDateFormat GetDateFormatA
#define GetTimeFormat GetTimeFormatA
#define GetCurrentDirectory GetCurrentDirectoryA
#define SetCurrentDirectory SetCurrentDirectoryA
#define GetWindowsDirectory GetWindowsDirectoryA
#define LoadString LoadStringA
#define FormatMessage FormatMessageA
#define FindResource FindResourceA
#define CreateProcess CreateProcessA
#define GetTempFileName GetTempFileNameA
#define FindExecutable FindExecutableA
#define STARTUPINFO STARTUPINFOA
#define LoadCursorFromFile LoadCursorFromFileA
#define GetVolumeInformation GetVolumeInformationA
#define GetDriveType GetDriveTypeA
#define GetDiskFreeSpace GetDiskFreeSpaceA
#define GetComputerName GetComputerNameA
#define GetUserName GetUserNameA
#define RegOpenKeyEx RegOpenKeyExA
#define RegCreateKeyEx RegCreateKeyExA
#define RegSetValueEx RegSetValueExA
#define RegQueryValueEx RegQueryValueExA
__declspec(dllimport) int WINAPI GetDateFormatA(DWORD, DWORD, const SYSTEMTIME *, LPCSTR, LPSTR, int);
__declspec(dllimport) int WINAPI GetDateFormatW(DWORD, DWORD, const SYSTEMTIME *, LPCWSTR, LPWSTR, int);
__declspec(dllimport) int WINAPI GetTimeFormatA(DWORD, DWORD, const SYSTEMTIME *, LPCSTR, LPSTR, int);
__declspec(dllimport) int WINAPI GetTimeFormatW(DWORD, DWORD, const SYSTEMTIME *, LPCWSTR, LPWSTR, int);
__declspec(dllimport) DWORD WINAPI GetCurrentDirectoryA(DWORD, LPSTR);
__declspec(dllimport) BOOL WINAPI SetCurrentDirectoryA(LPCSTR);
__declspec(dllimport) int __cdecl _access(LPCSTR, int);
__declspec(dllimport) UINT WINAPI GetWindowsDirectoryA(LPSTR, UINT);
__declspec(dllimport) BOOL WINAPI GetDiskFreeSpaceA(LPCSTR, LPDWORD, LPDWORD, LPDWORD, LPDWORD);
__declspec(dllimport) BOOL WINAPI GetVolumeInformationA(LPCSTR, LPSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPSTR, DWORD);
__declspec(dllimport) UINT WINAPI GetDriveTypeA(LPCSTR);
__declspec(dllimport) BOOL WINAPI GetComputerNameA(LPSTR, LPDWORD);
__declspec(dllimport) BOOL WINAPI GetUserNameA(LPSTR, LPDWORD);
__declspec(dllimport) HKL WINAPI GetKeyboardLayout(DWORD);
__declspec(dllimport) LONG WINAPI RegOpenKeyExA(HKEY, LPCSTR, DWORD, DWORD, PHKEY);
__declspec(dllimport) LONG WINAPI RegCreateKeyExA(HKEY, LPCSTR, DWORD, LPSTR, DWORD, DWORD, void *, PHKEY, LPDWORD);
__declspec(dllimport) LONG WINAPI RegSetValueExA(HKEY, LPCSTR, DWORD, DWORD, const BYTE *, DWORD);
__declspec(dllimport) LONG WINAPI RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
__declspec(dllimport) LONG WINAPI RegCloseKey(HKEY);
__declspec(dllimport) int WINAPI LoadStringA(HINSTANCE, UINT, LPSTR, int);
__declspec(dllimport) int WINAPI LoadStringW(HINSTANCE, UINT, LPWSTR, int);
__declspec(dllimport) HRSRC WINAPI FindResourceA(HINSTANCE, LPCSTR, LPCSTR);
__declspec(dllimport) HGLOBAL WINAPI LoadResource(HINSTANCE, HRSRC);
__declspec(dllimport) LPVOID WINAPI LockResource(HGLOBAL);
__declspec(dllimport) DWORD WINAPI SizeofResource(HINSTANCE, HRSRC);
__declspec(dllimport) int WINAPI MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int);
__declspec(dllimport) int WINAPI WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int, LPCSTR, LPBOOL);
__declspec(dllimport) DWORD WINAPI FormatMessageA(DWORD, LPCVOID, DWORD, DWORD, LPSTR, DWORD, va_list *);
__declspec(dllimport) DWORD WINAPI FormatMessageW(DWORD, LPCVOID, DWORD, DWORD, LPWSTR, DWORD, va_list *);
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
#ifndef __max
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif
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
