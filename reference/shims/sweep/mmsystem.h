#pragma once
// Minimal winmm declarations — dllimport+stdcall so call-site codegen matches retail.
extern "C" {
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int period);
}

typedef unsigned int MMRESULT;
