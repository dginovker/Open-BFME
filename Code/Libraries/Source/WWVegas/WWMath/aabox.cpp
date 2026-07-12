// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include "aabox.h"
#include "colmath.h"
#include "colmathinlines.h"
#include <float.h>


void AABoxClass::Init_Random(float min_center,float max_center,float min_extent,float max_extent)
{
	Center.X = min_center + WWMath::Random_Float() * (max_center - min_center);
	Center.Y = min_center + WWMath::Random_Float() * (max_center - min_center);
	Center.Z = min_center + WWMath::Random_Float() * (max_center - min_center);

	Extent.X = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
	Extent.Y = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
	Extent.Z = min_extent + WWMath::Random_Float() * (max_extent - min_extent);
}


void AABoxClass::Transform(const Matrix3D & tm,const AABoxClass & in,AABoxClass * out)
{
	tm.Transform_Center_Extent_AABox(in.Center,in.Extent,&(out->Center),&(out->Extent));
}

void MinMaxAABoxClass::Init_Empty(void)
{
	MinCorner.Set(FLT_MAX,FLT_MAX,FLT_MAX);
	MaxCorner.Set(-FLT_MAX,-FLT_MAX,-FLT_MAX);
}

// These AABox/MinMaxAABox members are WWINLINE in aabox.h and live out-of-line in the
// retail image, but no committed translation unit uses them enough for MSVC to emit the
// COMDATs. External-linkage anchors force emission so the byte-matcher can pin them:
// taking a member's address (or, for the address-less ctor, constructing through it).
MinMaxAABoxClass								_AABox_Force_Seed;
AABoxClass										_AABox_Force_Ctor(_AABox_Force_Seed);
void (AABoxClass::*_AABox_Force_Init_Min_Max)(const Vector3 &,const Vector3 &) = &AABoxClass::Init_Min_Max;
void (MinMaxAABoxClass::*_MinMax_Force_Init)(const AABoxClass &) = &MinMaxAABoxClass::Init;
void (MinMaxAABoxClass::*_MinMax_Force_Add_Box)(const AABoxClass &) = &MinMaxAABoxClass::Add_Box;
