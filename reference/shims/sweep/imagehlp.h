#pragma once
// Minimal imagehlp.h — 1998-era PSDK types (runtime-linked via GetProcAddress;
// declarations only, no dllimport symbols).

typedef enum {
	AddrMode1616,
	AddrMode1632,
	AddrModeReal,
	AddrModeFlat
} ADDRESS_MODE;

typedef struct _ADDRESS {
	DWORD Offset;
	WORD Segment;
	ADDRESS_MODE Mode;
} ADDRESS, *LPADDRESS;

typedef struct _KDHELP {
	DWORD Thread;
	DWORD ThCallbackStack;
	DWORD NextCallback;
	DWORD FramePointer;
	DWORD KiCallUserMode;
	DWORD KeUserCallbackDispatcher;
	DWORD SystemRangeStart;
} KDHELP, *PKDHELP;

typedef struct _STACKFRAME {
	ADDRESS AddrPC;
	ADDRESS AddrReturn;
	ADDRESS AddrFrame;
	ADDRESS AddrStack;
	LPVOID FuncTableEntry;
	DWORD Params[4];
	BOOL Far;
	BOOL Virtual;
	DWORD Reserved[3];
	KDHELP KdHelp;
} STACKFRAME, *LPSTACKFRAME;

typedef struct _IMAGEHLP_SYMBOL {
	DWORD SizeOfStruct;
	DWORD Address;
	DWORD Size;
	DWORD Flags;
	DWORD MaxNameLength;
	char Name[1];
} IMAGEHLP_SYMBOL, *PIMAGEHLP_SYMBOL;

#define SYMOPT_UNDNAME 0x00000002
#define SYMOPT_DEFERRED_LOADS 0x00000004
#define IMAGE_FILE_MACHINE_I386 0x014c

typedef BOOL (CALLBACK *PREAD_PROCESS_MEMORY_ROUTINE)(HANDLE hProcess, DWORD lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
typedef LPVOID (CALLBACK *PFUNCTION_TABLE_ACCESS_ROUTINE)(HANDLE hProcess, DWORD AddrBase);
typedef DWORD (CALLBACK *PGET_MODULE_BASE_ROUTINE)(HANDLE hProcess, DWORD dwAddress);
typedef DWORD (CALLBACK *PTRANSLATE_ADDRESS_ROUTINE)(HANDLE hProcess, HANDLE hThread, LPADDRESS lpAddress);
