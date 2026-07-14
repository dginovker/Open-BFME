// Minimal stand-in for the Win32 <windows.h> that the original win.h pulls in.
// The decompilation toolchain ships only the VC7.1 CRT headers, not the Platform
// SDK, so the handful of kernel32 imports RawFileClass touches are declared here.
// They are __declspec(dllimport) __stdcall so calls compile to the exact
// `call dword ptr [__imp__X]` shape the original used (the IAT slot is a masked
// DIR32 relocation), and the constants/struct layout match the SDK verbatim.
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef WIN_H
#define WIN_H

#define MAX_PATH				260
#define FILE_ATTRIBUTE_DIRECTORY	0x00000010

typedef unsigned long	DWORD;
typedef unsigned short	WORD;
typedef int				BOOL;
typedef void *			HANDLE;
typedef const char *	LPCSTR;
typedef void *			LPVOID;
typedef const void *	LPCVOID;
typedef long			LONG;
typedef DWORD *			LPDWORD;
typedef LONG *			PLONG;
typedef WORD *			LPWORD;
typedef unsigned int	UINT;
typedef void *			HWND;
typedef void *			HACCEL;
typedef void *			HMODULE;
typedef unsigned short	WCHAR;
typedef WCHAR *			LPWSTR;   // = VC7.1 default wchar_t; needed by widestring.h (same as shim windows.h)

#ifndef _LARGE_INTEGER_DEFINED
#define _LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
	struct { DWORD LowPart; LONG HighPart; };
	struct { DWORD LowPart; LONG HighPart; } u;
	__int64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
#endif

#ifndef _FILETIME_DEFINED
#define _FILETIME_DEFINED
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#endif

#ifndef _WIN32_FIND_DATAA_DEFINED
#define _WIN32_FIND_DATAA_DEFINED
typedef struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
	DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;
	char cFileName[MAX_PATH];
	char cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
#endif

typedef struct _BY_HANDLE_FILE_INFORMATION {
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		dwVolumeSerialNumber;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		nNumberOfLinks;
	DWORD		nFileIndexHigh;
	DWORD		nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

typedef struct _SECURITY_ATTRIBUTES *	LPSECURITY_ATTRIBUTES;
typedef struct _OVERLAPPED *			LPOVERLAPPED;
typedef void *			HGLOBAL;
typedef void *			HRSRC;
typedef void *			HINSTANCE;
typedef char *			LPSTR;
typedef unsigned int	WPARAM;
typedef long			LPARAM;
typedef unsigned int	MMRESULT;

#ifndef _TAGPOINT_DEFINED
#define _TAGPOINT_DEFINED
typedef struct tagPOINT { LONG x; LONG y; } POINT, *LPPOINT;
#endif

#ifndef _TAGRECT_DEFINED
#define _TAGRECT_DEFINED
typedef struct tagRECT { LONG left, top, right, bottom; } RECT, *LPRECT;
#endif

#ifndef _MSG_DEFINED
#define _MSG_DEFINED
typedef struct tagMSG {
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	POINT pt;
} MSG, *LPMSG;
#endif

#ifndef CALLBACK
#define CALLBACK	__stdcall
#endif
#define PM_NOREMOVE	0x0000
#define NORMAL_PRIORITY_CLASS	0x00000020
#define REALTIME_PRIORITY_CLASS	0x00000100

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#define INVALID_HANDLE_VALUE	((HANDLE)-1)

#define GENERIC_READ			(0x80000000L)
#define GENERIC_WRITE			(0x40000000L)
#define FILE_SHARE_READ			0x00000001
#define CREATE_ALWAYS			2
#define OPEN_EXISTING			3
#define OPEN_ALWAYS				4
#define FILE_ATTRIBUTE_NORMAL	0x00000080

#define FILE_BEGIN				0
#define FILE_CURRENT			1
#define FILE_END				2

#define CP_ACP				0

#define MB_OK					0x00000000L
#define MB_ICONHAND				0x00000010L
#define MB_ICONSTOP				MB_ICONHAND

extern "C" {

__declspec(dllimport) void __stdcall OutputDebugStringA(LPCSTR lpOutputString);
__declspec(dllimport) int __stdcall MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);


#ifndef _CREATEFILEA_DECLARED
#define _CREATEFILEA_DECLARED
__declspec(dllimport) HANDLE __stdcall CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
#endif
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE hObject);
__declspec(dllimport) BOOL __stdcall ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
__declspec(dllimport) BOOL __stdcall WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
__declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
__declspec(dllimport) DWORD __stdcall SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
__declspec(dllimport) BOOL __stdcall DeleteFileA(LPCSTR lpFileName);
__declspec(dllimport) BOOL __stdcall MoveFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName);
__declspec(dllimport) DWORD __stdcall GetFileAttributesA(LPCSTR lpFileName);
__declspec(dllimport) HANDLE __stdcall FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
__declspec(dllimport) BOOL __stdcall FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
__declspec(dllimport) BOOL __stdcall FindClose(HANDLE hFindFile);
__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
__declspec(dllimport) DWORD __stdcall GetLastError(void);
__declspec(dllimport) BOOL __stdcall GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
__declspec(dllimport) BOOL __stdcall FileTimeToDosDateTime(const FILETIME *lpFileTime, LPWORD lpFatDate, LPWORD lpFatTime);
__declspec(dllimport) BOOL __stdcall DosDateTimeToFileTime(WORD wFatDate, WORD wFatTime, LPFILETIME lpFileTime);
__declspec(dllimport) BOOL __stdcall SetFileTime(HANDLE hFile, const FILETIME *lpCreationTime, const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime);

__declspec(dllimport) BOOL __stdcall PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
__declspec(dllimport) BOOL __stdcall GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
__declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG *lpMsg);
__declspec(dllimport) LONG __stdcall DispatchMessageA(const MSG *lpMsg);
__declspec(dllimport) HRSRC __stdcall FindResourceA(HINSTANCE hModule, LPCSTR lpName, LPCSTR lpType);
__declspec(dllimport) HGLOBAL __stdcall LoadResource(HINSTANCE hModule, HRSRC hResInfo);
__declspec(dllimport) LPVOID __stdcall LockResource(HGLOBAL hResData);
__declspec(dllimport) DWORD __stdcall SizeofResource(HINSTANCE hModule, HRSRC hResInfo);
__declspec(dllimport) BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
__declspec(dllimport) BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
__declspec(dllimport) HANDLE __stdcall GetCurrentProcess(void);
__declspec(dllimport) DWORD __stdcall GetPriorityClass(HANDLE hProcess);
__declspec(dllimport) BOOL __stdcall SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass);
__declspec(dllimport) BOOL __stdcall GetDiskFreeSpaceA(LPCSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters);
__declspec(dllimport) BOOL __stdcall GetComputerNameA(LPSTR lpBuffer, LPDWORD lpnSize);
__declspec(dllimport) BOOL __stdcall GetUserNameA(LPSTR lpBuffer, LPDWORD lpnSize);
__declspec(dllimport) DWORD __stdcall GetTickCount(void);
__declspec(dllimport) int __stdcall LoadStringA(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int nBufferMax);
__declspec(dllimport) BOOL __stdcall TranslateAcceleratorA(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg);
__declspec(dllimport) BOOL __stdcall IsDialogMessageA(HWND hDlg, LPMSG lpMsg);
__declspec(dllimport) HANDLE __stdcall GetCurrentThread(void);
__declspec(dllimport) int __stdcall GetThreadPriority(HANDLE hThread);
__declspec(dllimport) BOOL __stdcall SetThreadPriority(HANDLE hThread, int nPriority);
__declspec(dllimport) LONG __stdcall InterlockedIncrement(LONG volatile *);
__declspec(dllimport) LONG __stdcall InterlockedDecrement(LONG volatile *);
__declspec(dllimport) MMRESULT __stdcall timeSetEvent(UINT uDelay, UINT uResolution, void (CALLBACK *lpTimeProc)(UINT, UINT, DWORD, DWORD, DWORD), DWORD dwUser, UINT fuEvent);
__declspec(dllimport) MMRESULT __stdcall timeKillEvent(UINT uTimerID);
__declspec(dllimport) BOOL __stdcall GetClientRect(HWND hWnd, LPRECT lpRect);
__declspec(dllimport) BOOL __stdcall ClientToScreen(HWND hWnd, LPPOINT lpPoint);
__declspec(dllimport) int __stdcall ShowCursor(BOOL bShow);
__declspec(dllimport) BOOL __stdcall GetCursorPos(LPPOINT lpPoint);
__declspec(dllimport) BOOL __stdcall SetCursorPos(int X, int Y);
__declspec(dllimport) char * __cdecl strdup(const char *);
void * __cdecl memcpy(void *, const void *, unsigned int);
__declspec(dllimport) void * __cdecl memmove(void *, const void *, unsigned int);

extern HINSTANCE	ProgramInstance;

}

#define DeleteFile	DeleteFileA
#define MoveFile	MoveFileA
#define GetFileAttributes	GetFileAttributesA
#define FindFirstFile		FindFirstFileA
#define FindNextFile		FindNextFileA
#define WIN32_FIND_DATA		WIN32_FIND_DATAA
#define OutputDebugString	OutputDebugStringA
#define MessageBox			MessageBoxA
#define PeekMessage			PeekMessageA
#define GetMessage			GetMessageA
#define DispatchMessage		DispatchMessageA
#define FindResource		FindResourceA
#define GetDiskFreeSpace	GetDiskFreeSpaceA
#define GetComputerName		GetComputerNameA
#define GetUserName			GetUserNameA
#define LoadString			LoadStringA
#define TranslateAccelerator	TranslateAcceleratorA
#define IsDialogMessage		IsDialogMessageA
#define THREAD_PRIORITY_NORMAL			0
#define THREAD_PRIORITY_TIME_CRITICAL	15
#define TIME_PERIODIC	1

#endif // WIN_H
