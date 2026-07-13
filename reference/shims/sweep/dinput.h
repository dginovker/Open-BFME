#pragma once
// DirectInput stand-in: the engine needs the DIK_* keyboard scancodes — standard,
// fixed values across SDK versions, so comparisons/switches compile to identical bytes.
// Interfaces use the exact dinput.h vtable order (virtual-call offsets must match retail).
#ifndef SWEEP_DINPUT_SHIM_H
#define SWEEP_DINPUT_SHIM_H

#include <objbase.h>

struct IDirectInput8;
struct IDirectInputDevice8;
typedef IDirectInput8 *LPDIRECTINPUT8;
typedef IDirectInputDevice8 *LPDIRECTINPUTDEVICE8;

// IDirectInput8 — dinput.h vtable order
struct IDirectInput8 : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE CreateDevice(REFGUID, LPDIRECTINPUTDEVICE8 *, IUnknown *) = 0;
	virtual HRESULT STDMETHODCALLTYPE EnumDevices(DWORD, void *, void *, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE FindDevice(REFGUID, const char *, GUID *) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetDeviceStatus(REFGUID) = 0;
	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND, DWORD) = 0;
	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE, DWORD) = 0;
};

// IDirectInputDevice8 — dinput.h vtable order (slots 3..31 after IUnknown)
struct IDirectInputDevice8 : public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(void *) = 0;						// 3 DIDEVCAPS*
	virtual HRESULT STDMETHODCALLTYPE EnumObjects(void *, void *, DWORD) = 0;			// 4
	virtual HRESULT STDMETHODCALLTYPE GetProperty(REFGUID, void *) = 0;					// 5 DIPROPHEADER*
	virtual HRESULT STDMETHODCALLTYPE SetProperty(REFGUID, const void *) = 0;			// 6
	virtual HRESULT STDMETHODCALLTYPE Acquire(void) = 0;								// 7
	virtual HRESULT STDMETHODCALLTYPE Unacquire(void) = 0;								// 8
	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD, void *) = 0;				// 9
	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD, void *, DWORD *, DWORD) = 0;	// 10
	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(const void *) = 0;					// 11 DIDATAFORMAT*
	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE) = 0;					// 12
	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND, DWORD) = 0;				// 13
	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(void *, DWORD, DWORD) = 0;			// 14
	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(void *) = 0;						// 15
	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND, DWORD) = 0;					// 16
	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE, DWORD, REFGUID) = 0;		// 17
	virtual HRESULT STDMETHODCALLTYPE CreateEffect(REFGUID, const void *, void *, IUnknown *) = 0;	// 18
	virtual HRESULT STDMETHODCALLTYPE EnumEffects(void *, void *, DWORD) = 0;			// 19
	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(void *, REFGUID) = 0;				// 20
	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(DWORD *) = 0;				// 21
	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD) = 0;				// 22
	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(void *, void *, DWORD) = 0;	// 23
	virtual HRESULT STDMETHODCALLTYPE Escape(void *) = 0;								// 24
	virtual HRESULT STDMETHODCALLTYPE Poll(void) = 0;									// 25
	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD, const void *, DWORD *, DWORD) = 0;	// 26
	virtual HRESULT STDMETHODCALLTYPE EnumObjectsInFile(const char *, void *, void *, DWORD) = 0;	// 27
	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(const char *, DWORD, void *, DWORD) = 0;	// 28
	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(void *, const char *, DWORD) = 0;	// 29
	virtual HRESULT STDMETHODCALLTYPE SetActionMap(void *, const char *, DWORD) = 0;	// 30
	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(void *) = 0;							// 31
};

__declspec(dllimport) HRESULT WINAPI DirectInput8Create(HINSTANCE, DWORD, REFIID, void **, IUnknown *);
extern "C" const IID IID_IDirectInput8;
extern "C" const GUID GUID_SysKeyboard;
extern "C" const GUID GUID_SysMouse;
extern "C" const struct _DIDATAFORMAT c_dfDIKeyboard;
extern "C" const struct _DIDATAFORMAT c_dfDIMouse;


// winuser.h cursor/capture decls — kept OUT of windows.h: their presence in the
// global shim deterministically perturbs cl's regalloc for an unrelated template
// instantiation in wwmemlog.cpp (VectorClass<ActiveCategoryStackClass>::Resize
// load-swap); dinput.h is only seen by the DI device TUs that need these.
__declspec(dllimport) BOOL WINAPI ClipCursor(const RECT *);
__declspec(dllimport) BOOL WINAPI GetWindowRect(HWND, LPRECT);
__declspec(dllimport) HCURSOR WINAPI LoadCursorA(HINSTANCE, LPCTSTR);
__declspec(dllimport) BOOL WINAPI ReleaseCapture(void);
__declspec(dllimport) HWND WINAPI SetCapture(HWND);
#define LoadCursor LoadCursorA
#define IDC_ARROW       ((LPCTSTR)32512)
#define IDC_CROSS       ((LPCTSTR)32515)
#define IDC_SIZEALL     ((LPCTSTR)32646)

// property GUIDs are small integers cast to GUID pointers (push imm in codegen)
// RTM cl rejects (const GUID &)1 (C2101 '&' on constant) — deref form binds fine
#define DIPROP_BUFFERSIZE       (*(const GUID *)(1))
#define DIPROP_AXISMODE         (*(const GUID *)(2))
#define DIPROP_GRANULARITY      (*(const GUID *)(3))
#define DIPROP_DEADZONE         (*(const GUID *)(5))
#define DIPROP_SATURATION       (*(const GUID *)(6))
#define DIPROP_AUTOCENTER       (*(const GUID *)(9))
#define DIPH_DEVICE             0
#define DIPH_BYOFFSET           1
#define DIPH_BYID               2
#define DIPH_BYUSAGE            3

typedef struct _DIPROPHEADER {
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
} DIPROPHEADER, *LPDIPROPHEADER;
typedef struct _DIPROPDWORD {
	DIPROPHEADER diph;
	DWORD dwData;
} DIPROPDWORD, *LPDIPROPDWORD;

typedef struct _DIOBJECTDATAFORMAT {
	const GUID *pguid;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
} DIOBJECTDATAFORMAT, *LPDIOBJECTDATAFORMAT;
typedef struct _DIDATAFORMAT {
	DWORD dwSize;
	DWORD dwObjSize;
	DWORD dwFlags;
	DWORD dwDataSize;
	DWORD dwNumObjs;
	LPDIOBJECTDATAFORMAT rgodf;
} DIDATAFORMAT, *LPDIDATAFORMAT;
#define DIDF_ABSAXIS 0x00000001
#define DIDF_RELAXIS 0x00000002

typedef struct _DIDEVCAPS {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwDevType;
	DWORD dwAxes;
	DWORD dwButtons;
	DWORD dwPOVs;
	DWORD dwFFSamplePeriod;
	DWORD dwFFMinTimeResolution;
	DWORD dwFirmwareRevision;
	DWORD dwHardwareRevision;
	DWORD dwFFDriverVersion;
} DIDEVCAPS, *LPDIDEVCAPS;

#define DIK_ESCAPE 0x01
#define DIK_1 0x02
#define DIK_2 0x03
#define DIK_3 0x04
#define DIK_4 0x05
#define DIK_5 0x06
#define DIK_6 0x07
#define DIK_7 0x08
#define DIK_8 0x09
#define DIK_9 0x0A
#define DIK_0 0x0B
#define DIK_MINUS 0x0C
#define DIK_EQUALS 0x0D
#define DIK_BACK 0x0E
#define DIK_TAB 0x0F
#define DIK_Q 0x10
#define DIK_W 0x11
#define DIK_E 0x12
#define DIK_R 0x13
#define DIK_T 0x14
#define DIK_Y 0x15
#define DIK_U 0x16
#define DIK_I 0x17
#define DIK_O 0x18
#define DIK_P 0x19
#define DIK_LBRACKET 0x1A
#define DIK_RBRACKET 0x1B
#define DIK_RETURN 0x1C
#define DIK_LCONTROL 0x1D
#define DIK_A 0x1E
#define DIK_S 0x1F
#define DIK_D 0x20
#define DIK_F 0x21
#define DIK_G 0x22
#define DIK_H 0x23
#define DIK_J 0x24
#define DIK_K 0x25
#define DIK_L 0x26
#define DIK_SEMICOLON 0x27
#define DIK_APOSTROPHE 0x28
#define DIK_GRAVE 0x29
#define DIK_LSHIFT 0x2A
#define DIK_BACKSLASH 0x2B
#define DIK_Z 0x2C
#define DIK_X 0x2D
#define DIK_C 0x2E
#define DIK_V 0x2F
#define DIK_B 0x30
#define DIK_N 0x31
#define DIK_M 0x32
#define DIK_COMMA 0x33
#define DIK_PERIOD 0x34
#define DIK_SLASH 0x35
#define DIK_RSHIFT 0x36
#define DIK_MULTIPLY 0x37
#define DIK_LMENU 0x38
#define DIK_SPACE 0x39
#define DIK_CAPITAL 0x3A
#define DIK_F1 0x3B
#define DIK_F2 0x3C
#define DIK_F3 0x3D
#define DIK_F4 0x3E
#define DIK_F5 0x3F
#define DIK_F6 0x40
#define DIK_F7 0x41
#define DIK_F8 0x42
#define DIK_F9 0x43
#define DIK_F10 0x44
#define DIK_NUMLOCK 0x45
#define DIK_SCROLL 0x46
#define DIK_NUMPAD7 0x47
#define DIK_NUMPAD8 0x48
#define DIK_NUMPAD9 0x49
#define DIK_SUBTRACT 0x4A
#define DIK_NUMPAD4 0x4B
#define DIK_NUMPAD5 0x4C
#define DIK_NUMPAD6 0x4D
#define DIK_ADD 0x4E
#define DIK_NUMPAD1 0x4F
#define DIK_NUMPAD2 0x50
#define DIK_NUMPAD3 0x51
#define DIK_NUMPAD0 0x52
#define DIK_DECIMAL 0x53
#define DIK_OEM_102 0x56
#define DIK_F11 0x57
#define DIK_F12 0x58
#define DIK_F13 0x64
#define DIK_F14 0x65
#define DIK_F15 0x66
#define DIK_KANA 0x70
#define DIK_ABNT_C1 0x73
#define DIK_CONVERT 0x79
#define DIK_NOCONVERT 0x7B
#define DIK_YEN 0x7D
#define DIK_ABNT_C2 0x7E
#define DIK_NUMPADEQUALS 0x8D
#define DIK_PREVTRACK 0x90
#define DIK_AT 0x91
#define DIK_COLON 0x92
#define DIK_UNDERLINE 0x93
#define DIK_KANJI 0x94
#define DIK_STOP 0x95
#define DIK_AX 0x96
#define DIK_UNLABELED 0x97
#define DIK_NEXTTRACK 0x99
#define DIK_NUMPADENTER 0x9C
#define DIK_RCONTROL 0x9D
#define DIK_MUTE 0xA0
#define DIK_CALCULATOR 0xA1
#define DIK_PLAYPAUSE 0xA2
#define DIK_MEDIASTOP 0xA4
#define DIK_VOLUMEDOWN 0xAE
#define DIK_VOLUMEUP 0xB0
#define DIK_WEBHOME 0xB2
#define DIK_NUMPADCOMMA 0xB3
#define DIK_DIVIDE 0xB5
#define DIK_SYSRQ 0xB7
#define DIK_RMENU 0xB8
#define DIK_PAUSE 0xC5
#define DIK_HOME 0xC7
#define DIK_UP 0xC8
#define DIK_PRIOR 0xC9
#define DIK_LEFT 0xCB
#define DIK_RIGHT 0xCD
#define DIK_END 0xCF
#define DIK_DOWN 0xD0
#define DIK_NEXT 0xD1
#define DIK_INSERT 0xD2
#define DIK_DELETE 0xD3
#define DIK_LWIN 0xDB
#define DIK_RWIN 0xDC
#define DIK_APPS 0xDD
#define DIK_POWER 0xDE
#define DIK_SLEEP 0xDF
#define DIK_WAKE 0xE3
#define DIK_WEBSEARCH 0xE5
#define DIK_WEBFAVORITES 0xE6
#define DIK_WEBREFRESH 0xE7
#define DIK_WEBSTOP 0xE8
#define DIK_WEBFORWARD 0xE9
#define DIK_WEBBACK 0xEA
#define DIK_MYCOMPUTER 0xEB
#define DIK_MAIL 0xEC
#define DIK_MEDIASELECT 0xED

// engine-used aliases
#define DIK_BACKSPACE DIK_BACK
#define DIK_NUMPADSTAR DIK_MULTIPLY
#define DIK_LALT DIK_LMENU
#define DIK_CAPSLOCK DIK_CAPITAL
#define DIK_NUMPADMINUS DIK_SUBTRACT
#define DIK_NUMPADPLUS DIK_ADD
#define DIK_NUMPADPERIOD DIK_DECIMAL
#define DIK_NUMPADSLASH DIK_DIVIDE
#define DIK_RALT DIK_RMENU
#define DIK_UPARROW DIK_UP
#define DIK_PGUP DIK_PRIOR
#define DIK_LEFTARROW DIK_LEFT
#define DIK_RIGHTARROW DIK_RIGHT
#define DIK_DOWNARROW DIK_DOWN
#define DIK_PGDN DIK_NEXT

typedef struct _DIDEVICEOBJECTDATA {
	DWORD dwOfs;
	DWORD dwData;
	DWORD dwTimeStamp;
	DWORD dwSequence;
	DWORD uAppData;
} DIDEVICEOBJECTDATA;

// SetCooperativeLevel flags (dinput.h, fixed SDK values)
#define DISCL_EXCLUSIVE     0x00000001
#define DISCL_NONEXCLUSIVE  0x00000002
#define DISCL_FOREGROUND    0x00000004
#define DISCL_BACKGROUND    0x00000008
#define DISCL_NOWINKEY      0x00000010

// device capabilities flags
#define DIDC_FORCEFEEDBACK  0x00000001

// DIMOUSESTATE field offsets (lX, lY, lZ, rgbButtons[4])
#define DIMOFS_X        0
#define DIMOFS_Y        4
#define DIMOFS_Z        8
#define DIMOFS_BUTTON0  12
#define DIMOFS_BUTTON1  13
#define DIMOFS_BUTTON2  14
#define DIMOFS_BUTTON3  15

// DI HRESULTs (dinput.h, fixed SDK values)
#define DI_OK                       0x00000000L
#define DIERR_OLDDIRECTINPUTVERSION  0x8007047BL
#define DIERR_BETADIRECTINPUTVERSION 0x80070481L
#define DIERR_BADDRIVERVER           0x80070077L
#define DIERR_DEVICENOTREG           0x80040154L
#define DIERR_NOTFOUND               0x80070002L
#define DIERR_OBJECTNOTFOUND         0x80070002L
#define DIERR_INVALIDPARAM           0x80070057L
#define DIERR_NOINTERFACE            0x80004002L
#define DIERR_GENERIC                0x80004005L
#define DIERR_OUTOFMEMORY            0x8007000EL
#define DIERR_UNSUPPORTED            0x80070032L
#define DIERR_NOTINITIALIZED         0x80070015L
#define DIERR_ALREADYINITIALIZED     0x800704DFL
#define DIERR_NOAGGREGATION          0x80040110L
#define DIERR_OTHERAPPHASPRIO        0x80070005L
#define DIERR_INPUTLOST              0x8007001EL
#define DIERR_ACQUIRED               0x80070266L
#define DIERR_NOTACQUIRED            0x8007001AL
#define DIERR_READONLY               0x80070005L
#define DIERR_HANDLEEXISTS           0x80070039L
#define DIERR_HASEFFECTS             0x8007029CL
#define DIERR_DEVICEFULL             0x80070297L
#define DIERR_MOREDATA               0x80070296L
#define DIERR_NOTDOWNLOADED          0x8007029AL
#define DIERR_EFFECTPLAYING          0x8007029BL
#define DIERR_INCOMPLETEEFFECT       0x80070298L
#define DIERR_NOTBUFFERED            0x80070299L
#define DIERR_NOTEXCLUSIVEACQUIRED   0x8007029DL
#define DIERR_MAPFILEFAIL            0x80070006L
#define DIERR_UNPLUGGED              0x80070483L
#define DIERR_REPORTFULL             0x80070484L

#endif
