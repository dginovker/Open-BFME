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

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

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

#define MB_OK					0x00000000L
#define MB_ICONHAND				0x00000010L
#define MB_ICONSTOP				MB_ICONHAND

extern "C" {

__declspec(dllimport) void __stdcall OutputDebugStringA(LPCSTR lpOutputString);
__declspec(dllimport) int __stdcall MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);


__declspec(dllimport) HANDLE __stdcall CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE hObject);
__declspec(dllimport) BOOL __stdcall ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
__declspec(dllimport) BOOL __stdcall WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
__declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
__declspec(dllimport) DWORD __stdcall SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
__declspec(dllimport) BOOL __stdcall DeleteFileA(LPCSTR lpFileName);
__declspec(dllimport) DWORD __stdcall GetLastError(void);
__declspec(dllimport) BOOL __stdcall GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
__declspec(dllimport) BOOL __stdcall FileTimeToDosDateTime(const FILETIME *lpFileTime, LPWORD lpFatDate, LPWORD lpFatTime);
__declspec(dllimport) BOOL __stdcall DosDateTimeToFileTime(WORD wFatDate, WORD wFatTime, LPFILETIME lpFileTime);
__declspec(dllimport) BOOL __stdcall SetFileTime(HANDLE hFile, const FILETIME *lpCreationTime, const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime);

}

#define DeleteFile	DeleteFileA
#define OutputDebugString	OutputDebugStringA
#define MessageBox			MessageBoxA

#endif // WIN_H
