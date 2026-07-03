// Minimal stand-in for the Win32 <mmsystem.h> that the original mmsys.h pulls in.
// The build toolchain ships no Platform SDK, so we declare only the winmm timer
// entry points systimer.cpp actually uses. They are __stdcall dllimports from
// winmm.dll, so calls compile to the same indirect `call [__imp__...]` the retail
// binary uses.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MMSYS_H
#define MMSYS_H

extern "C" {
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int uPeriod);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int uPeriod);
}

#endif
