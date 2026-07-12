// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "systimer.h"

SysTimeClass SystemTime;


SysTimeClass::SysTimeClass(void) :
	StartTime(0),
	WrapAdd(0)
{
	//tell windows we need single ms precision.
	timeBeginPeriod(1);
}

SysTimeClass::~SysTimeClass(void)
{
	//tell windows we need single ms precision.
	timeEndPeriod(1);
}

void SysTimeClass::Reset(void)
{
	StartTime = timeGetTime();
	WrapAdd = 0 - StartTime;
}


bool SysTimeClass::Is_Getting_Late(void)
{
	/*
	** Even though the timers are all unsigned so we have a max time of 0xffffffff the game casts it to int in various places
	** so it's safer to assume a signed max value.
	*/
	if (Get() > 0x6fffffff) {
		return(true);
	}
	return(false);
}


