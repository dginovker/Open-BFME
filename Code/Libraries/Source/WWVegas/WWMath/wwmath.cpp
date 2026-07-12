// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep


#include "wwmath.h"
#include "wwhack.h"
#include <stdlib.h>
#include "wwdebug.h"
#include "wwprofile.h"

// TODO: convert to use loouptablemanager...
float _FastAcosTable[ARC_TABLE_SIZE];
float _FastAsinTable[ARC_TABLE_SIZE];
float _FastSinTable[SIN_TABLE_SIZE];
float _FastInvSinTable[SIN_TABLE_SIZE];

void		WWMath::Init(void)
{
	// BFME drift: the retail build's WWMath::Init has no LookupTableMgrClass::Init()
	// call (present in the Generals reference); omitting it matches the shipped bytes.

	for (int a=0;a<ARC_TABLE_SIZE;++a) {
		float cv=float(a-ARC_TABLE_SIZE/2)*(1.0f/(ARC_TABLE_SIZE/2));
		_FastAcosTable[a]=acos(cv);
		_FastAsinTable[a]=asin(cv);
	}

	for (a=0;a<SIN_TABLE_SIZE;++a) {
		float cv= (float)a * 2.0f * WWMATH_PI / SIN_TABLE_SIZE; //float(a-SIN_TABLE_SIZE/2)*(1.0f/(SIN_TABLE_SIZE/2));
		_FastSinTable[a]=sin(cv);

		if (a>0) {
			_FastInvSinTable[a]=1.0f/_FastSinTable[a];
		} else {
			_FastInvSinTable[a]=WWMATH_FLOAT_MAX;
		}
	}
}

void		WWMath::Shutdown(void)
{
	// BFME drift: like Init, the retail WWMath::Shutdown drops the
	// LookupTableMgrClass::Shutdown() call, leaving an empty body.
}

float		WWMath::Random_Float(void)
{
	return ((float)(rand() & 0xFFF)) / (float)(0xFFF);
}


/*
** Force link some modules from this library.
*/
void Do_Force_Links(void)
{
	FORCE_LINK(curve);
	FORCE_LINK(hermitespline);
	FORCE_LINK(catmullromspline);
	FORCE_LINK(cardinalspline);
	FORCE_LINK(tcbspline);
}


/*
** The table-driven WWMath::Fast_Sin/Fast_Cos/Fast_Acos helpers are declared inline in
** wwmath.h, but the retail image carries them as standalone out-of-line functions.
** Taking their addresses here forces MSVC to emit those COMDAT bodies in this translation
** unit so the byte-matcher can anchor them to WWMath (their natural home). This forcing
** table itself is not present in the shipped binary -- it exists only to pin the emission.
*/
float (* _WWMath_Forced_Fast_Trig[])(float) = {
	&WWMath::Fast_Sin,
	&WWMath::Fast_Cos,
	&WWMath::Fast_Acos,
};
