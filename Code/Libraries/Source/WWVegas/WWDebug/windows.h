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
typedef void *HACCEL;
typedef void *HMENU;
typedef int INT;
typedef int *LPINT;
typedef unsigned long DWORD;
typedef unsigned long *LPDWORD;
typedef DWORD *PDWORD;
typedef unsigned long ULONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef short SHORT;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef BYTE *PBYTE;
typedef HKEY *PHKEY;
typedef long LONG;
typedef unsigned __int64 ULONGLONG;
typedef __int64 LONGLONG;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef const char *PCSTR;
typedef unsigned short WCHAR;   // = VC7.1 default wchar_t (unsigned short), mangles as G like retail
typedef WCHAR *PWCHAR, *LPWSTR;
typedef const unsigned short *LPCWSTR;
typedef unsigned long SIZE_T;
typedef unsigned long ULONG_PTR;
typedef long LONG_PTR;
typedef unsigned int UINT_PTR;
typedef long *LPLONG;
typedef LONG_PTR LRESULT;
typedef WORD *LPWORD;
typedef BOOL *LPBOOL;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef int (__stdcall *FARPROC)();

#define WINAPI __stdcall
#define WINAPIV __cdecl
#define CALLBACK __stdcall
#define VOID void
#define CONST const

#ifndef _GUID_DEFINED
#define _GUID_DEFINED
typedef struct _GUID {
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
} GUID;
#endif

__inline int operator==(const GUID& a, const GUID& b) {
	return a.Data1 == b.Data1 && a.Data2 == b.Data2 && a.Data3 == b.Data3 &&
		*(unsigned int*)(&a.Data4[0]) == *(unsigned int*)(&b.Data4[0]) &&
		*(unsigned int*)(&a.Data4[4]) == *(unsigned int*)(&b.Data4[4]);
}

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#define MAX_PATH 260
#ifndef ZeroMemory
#define ZeroMemory(dst, len) memset((dst), 0, (len))
#endif
#define MAX_COMPUTERNAME_LENGTH 31
#define LOWORD(l) ((WORD)((DWORD)(l) & 0xFFFF))
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#ifndef MAKEWORD
#define MAKEWORD(a,b) ((WORD)(((BYTE)((a) & 0xFF)) | ((WORD)((BYTE)((b) & 0xFF))) << 8))
#endif
#define MAKELPARAM(l,h) ((LPARAM)((WORD)(l) | ((DWORD)((WORD)(h))) << 16))
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

struct _EXCEPTION_POINTERS;
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

typedef struct _TIME_ZONE_INFORMATION {
    LONG Bias;
    WCHAR StandardName[32];
    SYSTEMTIME StandardDate;
    LONG StandardBias;
    WCHAR DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG DaylightBias;
} TIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;

typedef struct tagPOINT { LONG x; LONG y; } POINT, *LPPOINT;
typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG, *LPMSG;

#ifndef _LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; };
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
#define _LARGE_INTEGER_DEFINED
#endif

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
#define VER_PLATFORM_WIN32s 0

typedef struct tagRECT { LONG left, top, right, bottom; } RECT, *LPRECT;
typedef struct tagSIZE { LONG cx, cy; } SIZE, *LPSIZE;
typedef struct tagTEXTMETRICA {
    LONG tmHeight, tmAscent, tmDescent, tmInternalLeading, tmExternalLeading, tmAveCharWidth, tmMaxCharWidth, tmWeight;
    LONG tmOverhang, tmDigitizedAspectX, tmDigitizedAspectY;
    BYTE tmFirstChar, tmLastChar, tmDefaultChar, tmBreakChar;
    BYTE tmItalic, tmUnderlined, tmStruckOut, tmPitchAndFamily, tmCharSet;
} TEXTMETRIC, *LPTEXTMETRIC;
typedef struct tagRGBQUAD { BYTE rgbBlue, rgbGreen, rgbRed, rgbReserved; } RGBQUAD;
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize; LONG biWidth, biHeight; WORD biPlanes, biBitCount;
    DWORD biCompression, biSizeImage; LONG biXPelsPerMeter, biYPelsPerMeter;
    DWORD biClrUsed, biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER;
typedef struct tagBITMAPINFO { BITMAPINFOHEADER bmiHeader; RGBQUAD bmiColors[1]; } BITMAPINFO, *LPBITMAPINFO;
#define RGB(r,g,b) ((DWORD)(((BYTE)(r) | ((WORD)(g) << 8)) | (((DWORD)(BYTE)(b)) << 16)))
#define FW_NORMAL 400
#define FW_BOLD 700
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define ANTIALIASED_QUALITY 4
#define VARIABLE_PITCH 2
#define BI_RGB 0L
#define DIB_RGB_COLORS 0

typedef struct _FILETIME { DWORD dwLowDateTime, dwHighDateTime; } FILETIME, *LPFILETIME;
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;
    char cFileName[MAX_PATH];
    char cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

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
#define GWL_STYLE (-16)
#define WS_CAPTION 0x00C00000L
#define GWL_EXSTYLE (-20)
#define WS_EX_TOOLWINDOW 0x00000080L
#define SW_SHOWMINNOACTIVE 7
#define SW_RESTORE 9
#define FW_NORMAL 400
#define FF_MODERN 48
#define FIXED_PITCH 1
#define DEFAULT_PITCH 0
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define DEFAULT_QUALITY 0
#define ANTIALIASED_QUALITY 4
#define DEFAULT_CHARSET 1
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
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_MOUSEWHEEL 0x020A
#define WM_SETFONT 0x0030
#define STARTF_USESHOWWINDOW 0x00000001
#define STARTF_USESTDHANDLES 0x00000100
#define PM_NOREMOVE 0x0000
#define PM_REMOVE 0x0001
#define MAPVK_VK_TO_CHAR 2

typedef struct _CHAR_UNION {
    union {
        WCHAR UnicodeChar;
        char AsciiChar;
    };
} CHAR_UNION;

typedef struct _KEY_EVENT_RECORD {
    BOOL bKeyDown;
    WORD wRepeatCount;
    WORD wVirtualKeyCode;
    WORD wVirtualScanCode;
    CHAR_UNION uChar;
    DWORD dwControlKeyState;
} KEY_EVENT_RECORD, *PKEY_EVENT_RECORD;

typedef struct _INPUT_RECORD {
    WORD EventType;
    union {
        KEY_EVENT_RECORD KeyEvent;
    } Event;
} INPUT_RECORD, *PINPUT_RECORD;
#define KEY_EVENT 0x0001
#define BACKGROUND_RED 0x0040
#define BACKGROUND_GREEN 0x0020
#define BACKGROUND_BLUE 0x0010
#define BACKGROUND_INTENSITY 0x0080
#define FOREGROUND_BLUE 0x0001
#define FOREGROUND_GREEN 0x0002
#define FOREGROUND_RED 0x0004
#define FOREGROUND_INTENSITY 0x0008

typedef struct _COORD { SHORT X; SHORT Y; } COORD, *PCOORD;
typedef struct _SMALL_RECT { SHORT Left, Top, Right, Bottom; } SMALL_RECT, *PSMALL_RECT;

typedef struct _CHAR_INFO {
    CHAR_UNION Char;
    WORD Attributes;
} CHAR_INFO, *PCHAR_INFO;

typedef struct _FLOATING_SAVE_AREA {
    DWORD ControlWord, StatusWord, TagWord, ErrorOffset, ErrorSelector, DataOffset, DataSelector;
    BYTE RegisterArea[80];
    DWORD Cr0NpxState;
} FLOATING_SAVE_AREA;

#define CONTEXT_i386 0x00010000
#define CONTEXT_CONTROL (CONTEXT_i386 | 0x00000001)
#define CONTEXT_INTEGER (CONTEXT_i386 | 0x00000002)
#define CONTEXT_SEGMENTS (CONTEXT_i386 | 0x00000004)
#define CONTEXT_FLOATING_POINT (CONTEXT_i386 | 0x00000008)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_i386 | 0x00000010)
#define CONTEXT_EXTENDED_REGISTERS (CONTEXT_i386 | 0x00000020)
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS)

#define MAXIMUM_SUPPORTED_EXTENSION 512

typedef struct _CONTEXT {
    DWORD ContextFlags;
    DWORD Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    FLOATING_SAVE_AREA FloatSave;
    DWORD SegGs;
    DWORD SegFs;
    DWORD SegEs;
    DWORD SegDs;
    DWORD Edi;
    DWORD Esi;
    DWORD Ebx;
    DWORD Edx;
    DWORD Ecx;
    DWORD Eax;
    DWORD Ebp;
    DWORD Eip;
    DWORD SegCs;
    DWORD EFlags;
    DWORD Esp;
    DWORD SegSs;
    BYTE ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];
} CONTEXT, *PCONTEXT, *LPCONTEXT;

typedef struct _EXCEPTION_RECORD {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    void *ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[15];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;

typedef struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD ExceptionRecord;
    PCONTEXT ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

#define EXCEPTION_ACCESS_VIOLATION 0xC0000005L
#define EXCEPTION_STACK_OVERFLOW 0xC00000FDL
#define EXCEPTION_BREAKPOINT 0x80000003L
#define EXCEPTION_IN_PAGE_ERROR 0xC0000006L
#define STATUS_INVALID_PARAMETER 0xC000000DL
#define STATUS_NO_MEMORY 0xC0000017L

extern "C" {
__declspec(dllimport) BOOL WINAPI ReadConsoleInputA(HANDLE, PINPUT_RECORD, DWORD, LPDWORD);
#define ReadConsoleInput ReadConsoleInputA
__declspec(dllimport) BOOL WINAPI WriteConsoleOutputA(HANDLE, CHAR_INFO *, COORD, COORD, PSMALL_RECT);
#define WriteConsoleOutput WriteConsoleOutputA
__declspec(dllimport) BOOL WINAPI SetConsoleWindowInfo(HANDLE, BOOL, const SMALL_RECT *);
__declspec(dllimport) BOOL WINAPI SetConsoleScreenBufferSize(HANDLE, COORD);
__declspec(dllimport) BOOL WINAPI AllocConsole(void);
__declspec(dllimport) BOOL WINAPI FreeConsole(void);
__declspec(dllimport) BOOL WINAPI SetConsoleCtrlHandler(void *, BOOL);
__declspec(dllimport) BOOL WINAPI SetConsoleTitleA(LPCSTR);
#define SetConsoleTitle SetConsoleTitleA

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD dwSize;
    COORD dwCursorPosition;
    WORD wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

__declspec(dllimport) BOOL WINAPI GetConsoleScreenBufferInfo(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO);
__declspec(dllimport) BOOL WINAPI SetConsoleMode(HANDLE, DWORD);
__declspec(dllimport) BOOL WINAPI GetConsoleMode(HANDLE, LPDWORD);
__declspec(dllimport) BOOL WINAPI GetNumberOfConsoleInputEvents(HANDLE, LPDWORD);
typedef struct _CONSOLE_CURSOR_INFO {
    DWORD dwSize;
    BOOL bVisible;
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;

__declspec(dllimport) BOOL WINAPI GetConsoleCursorInfo(HANDLE, PCONSOLE_CURSOR_INFO);
__declspec(dllimport) BOOL WINAPI SetConsoleCursorInfo(HANDLE, const CONSOLE_CURSOR_INFO *);
__declspec(dllimport) COORD WINAPI GetLargestConsoleWindowSize(HANDLE);
__declspec(dllimport) HANDLE WINAPI GetStdHandle(DWORD);
#define STD_INPUT_HANDLE ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE ((DWORD)-12)
__declspec(dllimport) int WINAPIV wsprintfA(LPSTR, LPCSTR, ...);
__declspec(dllimport) int WINAPI lstrcmpA(LPCSTR, LPCSTR);
__declspec(dllimport) int WINAPI lstrcmpW(LPCWSTR, LPCWSTR);
__declspec(dllimport) int WINAPI lstrcmpiA(LPCSTR, LPCSTR);
__declspec(dllimport) int WINAPI lstrcmpiW(LPCWSTR, LPCWSTR);
#define lstrcmp lstrcmpA
#define lstrcmpi lstrcmpiA
__declspec(dllimport) int WINAPI lstrlenA(LPCSTR);
__declspec(dllimport) int WINAPI lstrlenW(LPCWSTR);
#define lstrlen lstrlenA
__declspec(dllimport) LPSTR WINAPI lstrcatA(LPSTR, LPCSTR);
__declspec(dllimport) LPWSTR WINAPI lstrcatW(LPWSTR, LPCWSTR);
#define lstrcat lstrcatA
__declspec(dllimport) LPSTR WINAPI lstrcpyA(LPSTR, LPCSTR);
__declspec(dllimport) LPWSTR WINAPI lstrcpyW(LPWSTR, LPCWSTR);
#define lstrcpy lstrcpyA
__declspec(dllimport) LPSTR WINAPI lstrcpynA(LPSTR, LPCSTR, int);
__declspec(dllimport) LPWSTR WINAPI lstrcpynW(LPWSTR, LPCWSTR, int);
#define lstrcpyn lstrcpynA
__declspec(dllimport) int WINAPI MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
__declspec(dllimport) int WINAPI MessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);
__declspec(dllimport) HWND WINAPI GetDlgItem(HWND, int);
__declspec(dllimport) LRESULT WINAPI SendDlgItemMessageA(HWND, int, UINT, WPARAM, LPARAM);
#define SendDlgItemMessage SendDlgItemMessageA
__declspec(dllimport) HWND WINAPI CreateWindowExA(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
__declspec(dllimport) void * WINAPI CreateFontA(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
__declspec(dllimport) LRESULT WINAPI SendMessageA(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) LRESULT WINAPI DefWindowProcA(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) BOOL WINAPI SetWindowPos(HWND, HWND, int, int, int, int, UINT);
__declspec(dllimport) BOOL WINAPI ShowWindow(HWND, int);
__declspec(dllimport) BOOL WINAPI SetWindowTextA(HWND, LPCSTR);
__declspec(dllimport) BOOL WINAPI SetWindowTextW(HWND, LPCWSTR);
#define SetWindowText SetWindowTextA
__declspec(dllimport) BOOL WINAPI CreateProcessA(LPCSTR, LPSTR, void *, void *, BOOL, DWORD, void *, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
__declspec(dllimport) UINT WINAPI GetTempFileNameA(LPCSTR, LPCSTR, UINT, LPSTR);
__declspec(dllimport) HINSTANCE WINAPI FindExecutableA(LPCSTR, LPCSTR, LPSTR);
__declspec(dllimport) BOOL WINAPI ScreenToClient(HWND, LPPOINT);
__declspec(dllimport) HCURSOR WINAPI LoadCursorFromFileA(LPCSTR);
__declspec(dllimport) HCURSOR WINAPI SetCursor(HCURSOR);
__declspec(dllimport) BOOL WINAPI GetCursorPos(LPPOINT);
__declspec(dllimport) BOOL WINAPI PeekMessageA(LPMSG, HWND, UINT, UINT, UINT);
__declspec(dllimport) BOOL WINAPI GetMessageA(LPMSG, HWND, UINT, UINT);
__declspec(dllimport) BOOL WINAPI TranslateMessage(const MSG *);
__declspec(dllimport) LONG WINAPI DispatchMessageA(const MSG *);
__declspec(dllimport) SHORT WINAPI GetKeyState(int);
__declspec(dllimport) UINT WINAPI MapVirtualKeyA(UINT, UINT);
__declspec(dllimport) int WINAPI ToAscii(UINT, UINT, PBYTE, LPWORD, UINT);
__declspec(dllimport) int WINAPI ToUnicode(UINT, UINT, PBYTE, LPWSTR, int, UINT);
__declspec(dllimport) BOOL WINAPI ClientToScreen(HWND, LPPOINT);
__declspec(dllimport) LRESULT WINAPI DefWindowProcA(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) int WINAPI TranslateAcceleratorA(HWND, HACCEL, LPMSG);
__declspec(dllimport) BOOL WINAPI IsDialogMessageA(HWND, LPMSG);
__declspec(dllimport) DWORD WINAPI GetTimeZoneInformation(LPTIME_ZONE_INFORMATION);
#define PeekMessage PeekMessageA
#define GetMessage GetMessageA
#define DispatchMessage DispatchMessageA
#define MapVirtualKey MapVirtualKeyA
#define DefWindowProc DefWindowProcA
#define TranslateAccelerator TranslateAcceleratorA
#define IsDialogMessage IsDialogMessageA
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
__declspec(dllimport) DWORD WINAPI SetTextColor(HDC, DWORD);
__declspec(dllimport) DWORD WINAPI SetBkColor(HDC, DWORD);
__declspec(dllimport) int WINAPI SetBkMode(HDC, int);
__declspec(dllimport) BOOL WINAPI TextOutA(HDC, int, int, LPCSTR, int);
#define TextOut TextOutA
__declspec(dllimport) HDC WINAPI CreateCompatibleDC(HDC);
__declspec(dllimport) HFONT WINAPI CreateFontA(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
#define CreateFont CreateFontA
__declspec(dllimport) HGDIOBJ WINAPI SelectObject(HDC, HGDIOBJ);
__declspec(dllimport) BOOL WINAPI GetTextMetricsA(HDC, LPTEXTMETRIC);
#define GetTextMetrics GetTextMetricsA
__declspec(dllimport) BOOL WINAPI GetTextExtentPoint32A(HDC, LPCSTR, int, LPSIZE);
__declspec(dllimport) BOOL WINAPI GetTextExtentPoint32W(HDC, LPCWSTR, int, LPSIZE);
#define GetTextExtentPoint32 GetTextExtentPoint32A
__declspec(dllimport) BOOL WINAPI ExtTextOutA(HDC, int, int, UINT, const RECT *, LPCSTR, UINT, const INT *);
__declspec(dllimport) BOOL WINAPI ExtTextOutW(HDC, int, int, UINT, const RECT *, LPCWSTR, UINT, const INT *);
#define ExtTextOut ExtTextOutA
#define ETO_OPAQUE 0x0002
__declspec(dllimport) BOOL WINAPI DeleteObject(HGDIOBJ);
__declspec(dllimport) BOOL WINAPI DeleteDC(HDC);
__declspec(dllimport) HDC WINAPI GetDC(HWND);
__declspec(dllimport) int WINAPI ReleaseDC(HWND, HDC);
__declspec(dllimport) HBITMAP WINAPI CreateDIBSection(HDC, const BITMAPINFO *, UINT, void **, HANDLE, DWORD);
__declspec(dllimport) int WINAPI MulDiv(int, int, int);
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
#define CSIDL_APPDATA 0x001a
#define CSIDL_LOCAL_APPDATA 0x001c
#define CSIDL_PERSONAL 0x0005
#define CSIDL_DESKTOPDIRECTORY 0x0010
#define CSIDL_FONTS 0x0014
#define CSIDL_FLAG_CREATE 0x8000
__declspec(dllimport) BOOL WINAPI SHGetSpecialFolderPathA(HWND, LPSTR, int, BOOL);
__declspec(dllimport) BOOL WINAPI SHGetSpecialFolderPathW(HWND, LPWSTR, int, BOOL);
#define SHGetSpecialFolderPath SHGetSpecialFolderPathA
typedef const ITEMIDLIST *LPCITEMIDLIST;
__declspec(dllimport) HRESULT WINAPI SHGetSpecialFolderLocation(HWND, int, LPITEMIDLIST *);
__declspec(dllimport) BOOL WINAPI SHGetPathFromIDListA(LPCITEMIDLIST, LPSTR);
__declspec(dllimport) BOOL WINAPI SHGetPathFromIDListW(LPCITEMIDLIST, LPWSTR);
#define SHGetPathFromIDList SHGetPathFromIDListA
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
__declspec(dllimport) void WINAPI SetUnhandledExceptionFilter(void *);
__declspec(dllimport) BOOL WINAPI IsBadReadPtr(const void *, UINT_PTR);
__declspec(dllimport) BOOL WINAPI IsBadCodePtr(FARPROC);
__declspec(dllimport) LONG WINAPI GetWindowLongA(HWND, int);
__declspec(dllimport) LONG WINAPI SetWindowLongA(HWND, int, LONG);
#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA
__declspec(dllimport) int __cdecl wvsprintfA(LPSTR, LPCSTR, void *);
__declspec(dllimport) int __cdecl wvsprintfW(LPWSTR, LPCWSTR, void *);
#define wvsprintf wvsprintfA
__declspec(dllimport) BOOL WINAPI SetNamedPipeHandleState(HANDLE, LPDWORD, LPDWORD, LPDWORD);
__declspec(dllimport) BOOL WINAPI EnumThreadWindows(DWORD, void *, LPARAM);
__declspec(dllimport) BOOL WINAPI IsWindow(HWND);
__declspec(dllimport) HANDLE WINAPI CreateNamedPipeA(LPCSTR, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, void *);
#define CreateNamedPipe CreateNamedPipeA
}
#define ERROR_FILE_EXISTS 80L
#define PIPE_READMODE_MESSAGE 2
#define PIPE_NOWAIT 1
#define PIPE_WAIT 0
#define PIPE_ACCESS_DUPLEX 3
#define PIPE_TYPE_MESSAGE 4
#define PIPE_UNLIMITED_INSTANCES 255

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

// VC7.1 <math.h> exposes float/long-double sqrt overloads, so integer args become
// ambiguous. Forward-declare the double variant and provide integer overloads that
// route to it (matches retail codegen where only double sqrt existed).
extern "C" double __cdecl sqrt(double);
inline double sqrt(int x) { return sqrt((double)x); }
inline double sqrt(unsigned int x) { return sqrt((double)x); }
inline double sqrt(long x) { return sqrt((double)x); }
inline double sqrt(unsigned long x) { return sqrt((double)x); }

#endif
