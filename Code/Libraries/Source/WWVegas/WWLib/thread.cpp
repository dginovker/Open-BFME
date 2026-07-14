// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _WIN32_WINNT 0x0400

#include "thread.h"
#include "except.h"
#include "wwdebug.h"
#include <process.h>
#include <windows.h>
#pragma warning ( push )
#pragma warning ( disable : 4201 )
#include "systimer.h"
#pragma warning ( pop )


// ??0ThreadClass@@ present-unmatched
ThreadClass::ThreadClass(const char *thread_name, ExceptionHandlerType exception_handler) : handle(0), running(false), thread_priority(0)
{
	if (thread_name) {
		assert(strlen(thread_name) < sizeof(ThreadName) - 1);
		strcpy(ThreadName, thread_name);
	} else {
		strcpy(ThreadName, "No name");;
	}

	ExceptionHandler = exception_handler;
}

// ??1ThreadClass@@ present-unmatched
ThreadClass::~ThreadClass()
{
	Stop();
}

// ?Internal_Thread_Function@ThreadClass@@ present-unmatched
void __cdecl ThreadClass::Internal_Thread_Function(void* params)
{
	ThreadClass* tc=reinterpret_cast<ThreadClass*>(params);
	tc->running=true;
	tc->ThreadID = GetCurrentThreadId();

#ifdef _WIN32
	Register_Thread_ID(tc->ThreadID, tc->ThreadName);

	if (tc->ExceptionHandler != NULL) {
		__try {
			tc->Thread_Function();
		} __except(tc->ExceptionHandler(GetExceptionCode(), GetExceptionInformation())) {};
	} else {
		tc->Thread_Function();
	}

#else //_WIN32
	tc->Thread_Function();
#endif //_WIN32

#ifdef _WIN32
	Unregister_Thread_ID(tc->ThreadID, tc->ThreadName);
#endif // _WIN32
	tc->handle=0;
	tc->ThreadID = 0;
}

// ?Execute@ThreadClass@@ present-unmatched
void ThreadClass::Execute()
{
	WWASSERT(!handle);	// Only one thread at a time!
	#ifdef _UNIX
		// assert(0);
		return;
	#else
		handle=_beginthread(&Internal_Thread_Function,0,this);
		SetThreadPriority((HANDLE)handle,THREAD_PRIORITY_NORMAL+thread_priority);
		WWDEBUG_SAY(("ThreadClass::Execute: Started thread %s, thread ID is %X\n", ThreadName, handle));
	#endif
}

// ?Set_Priority@ThreadClass@@ present-unmatched
void ThreadClass::Set_Priority(int priority)
{
	#ifdef _UNIX
		// assert(0);
		return;
	#else
		thread_priority=priority;
		if (handle) SetThreadPriority((HANDLE)handle,THREAD_PRIORITY_NORMAL+thread_priority);
	#endif
}

// ?Stop@ThreadClass@@ present-unmatched
void ThreadClass::Stop(unsigned ms)
{
	#ifdef _UNIX
		// assert(0);
		return;
	#else
		running=false;
		unsigned time=TIMEGETTIME();
		while (handle) {
			if ((TIMEGETTIME()-time)>ms) {
				int res=TerminateThread((HANDLE)handle,0);
				res;	// just to silence compiler warnings
				WWASSERT(res);	// Thread still not killed!
				handle=0;
			}
			Sleep(0);
		}
	#endif
}

// ?Sleep_Ms@ThreadClass@@ present-unmatched
void ThreadClass::Sleep_Ms(unsigned ms)
{
	Sleep(ms);
}

#ifndef _UNIX
HANDLE test_event = ::CreateEvent (NULL, FALSE, FALSE, "");
#endif

// ?Switch_Thread@ThreadClass@@ present-unmatched
void ThreadClass::Switch_Thread()
{
	#ifdef _UNIX
		return;
	#else
		//	::SwitchToThread ();
		::WaitForSingleObject (test_event, 1);
		//	Sleep(1);	// Note! Parameter can not be 0 (or the thread switch doesn't occur)
	#endif
}

// Return calling thread's unique thread id
// ?_Get_Current_Thread_ID@ThreadClass@@ present-unmatched
unsigned ThreadClass::_Get_Current_Thread_ID()
{
	#ifdef _UNIX
		return 0;
	#else
		return GetCurrentThreadId();
	#endif
}

// ?Is_Running@ThreadClass@@ present-unmatched
bool ThreadClass::Is_Running()
{
	return !!handle;
}