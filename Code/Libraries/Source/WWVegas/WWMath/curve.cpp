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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWMath                                                       *
 *                                                                                             *
 *                     $Archive:: /VSS_Sync/wwmath/curve.cpp                                  $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Vss_sync                                                    $*
 *                                                                                             *
 *                     $Modtime:: 6/13/01 2:18p                                               $*
 *                                                                                             *
 *                    $Revision:: 9                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "curve.h"
#include "wwdebug.h"
#include "persistfactory.h"
#include "wwmathids.h"
#include "wwhack.h"

/*
** Force-Link this module because the linker can't detect that we actually need it...
*/
DECLARE_FORCE_LINK(curve);

/*
** Persist factories and chunk-id's used to save and load.
*/
SimplePersistFactoryClass<LinearCurve3DClass,WWMATH_CHUNKID_LINEARCURVE3D>	_LinearCurve3DFactory;
SimplePersistFactoryClass<LinearCurve1DClass,WWMATH_CHUNKID_LINEARCURVE1D>	_LinearCurve1DFactory;

enum 
{
	// ID's used by Curve3D
	CURVE3D_CHUNK_VARIABLES					= 0x00020651,			
	CURVE3D_CHUNK_KEYS,			

	CURVE3D_VARIABLE_ISLOOPING				= 0x00,
	CURVE3D_VARIABLE_KEYCOUNT,

	// ID's used by LinearCurve3D
	LINEARCURVE3D_CHUNK_CURVE3D			= 0x00020653,

	// ID's used by Curve1D
	CURVE1D_CHUNK_VARIABLES					= 0x00020655,			
	CURVE1D_CHUNK_KEYS,			

	CURVE1D_VARIABLE_ISLOOPING				= 0x00,
	CURVE1D_VARIABLE_KEYCOUNT,

	// ID's used by LinearCurve1D
	LINEARCURVE1D_CHUNK_CURVE1D			= 0x00020657,

};


/***********************************************************************************************
**
** Curve3DCLass Implementation
**
***********************************************************************************************/
// ??0Curve3DClass@@ present-unmatched
Curve3DClass::Curve3DClass(void) :
	IsLooping(false)
{
}

// ??0Curve3DClass@@ present-unmatched
Curve3DClass::Curve3DClass(const Curve3DClass & that)
{
	*this = that;
}

// ??1Curve3DClass@@ present-unmatched
Curve3DClass::~Curve3DClass(void)
{
}

// ??4Curve3DClass@@ present-unmatched
Curve3DClass & Curve3DClass::operator = (const Curve3DClass & that)
{
	IsLooping = that.IsLooping;
	Keys = that.Keys;
	return *this;
}

// ?Is_Looping@Curve3DClass@@ present-unmatched
bool Curve3DClass::Is_Looping(void)
{
	return IsLooping;
}

void Curve3DClass::Set_Looping(bool onoff)
{
	IsLooping = onoff;
}

// ?Get_Start_Time@Curve3DClass@@ present-unmatched
float Curve3DClass::Get_Start_Time(void)
{
	if (Keys.Count() > 0) {
		return Keys[0].Time;
	} else {
		return 0.0f;
	}
}

// ?Get_End_Time@Curve3DClass@@ present-unmatched
float Curve3DClass::Get_End_Time(void)
{
	if (Keys.Count() > 0) {
		return Keys[Keys.Count() - 1].Time;
	} else {
		return 0.0f;
	}
}

// ?Key_Count@Curve3DClass@@ present-unmatched
int Curve3DClass::Key_Count(void)
{
	return Keys.Count();
}

// ?Get_Key@Curve3DClass@@ present-unmatched
void Curve3DClass::Get_Key(int i,Vector3 * set_point,float * set_t)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	if (set_point != NULL) {
		*set_point = Keys[i].Point;
	}
	if (set_t != NULL) {
		*set_t = Keys[i].Time;
	}
}

// ?Set_Key@Curve3DClass@@ present-unmatched
void Curve3DClass::Set_Key(int i,const Vector3 & point)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	Keys[i].Point = point;
}	


// ?Add_Key@Curve3DClass@@ present-unmatched
int Curve3DClass::Add_Key(const Vector3 & point,float t)
{
	int idx = 0;
	while (idx < Keys.Count() && Keys[idx].Time < t) {
		idx++;
	}

	KeyClass newkey;
	newkey.Point = point;
	newkey.Time = t;

	Keys.Insert(idx,newkey);
	return idx;
}	

// ?Remove_Key@Curve3DClass@@ present-unmatched
void Curve3DClass::Remove_Key(int i)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	Keys.Delete(i);	
}

// ?Clear_Keys@Curve3DClass@@ present-unmatched
void Curve3DClass::Clear_Keys(void)
{
	Keys.Clear();
}

// ?Find_Interval@Curve3DClass@@ present-unmatched
void Curve3DClass::Find_Interval(float time,int * i0,int * i1,float * t)
{
	WWASSERT(time >= Keys[0].Time);
	WWASSERT(time <= Keys[Keys.Count()-1].Time);

	int i=0;
	while (time > Keys[i+1].Time) {
		i++;
	}
	*i0 = i;
	*i1 = i+1;
	*t = (time - Keys[i].Time) / (Keys[i+1].Time - Keys[i].Time);
}

// ?Save@Curve3DClass@@ present-unmatched
bool Curve3DClass::Save(ChunkSaveClass & csave)
{
	int keycount = Keys.Count();
	csave.Begin_Chunk(CURVE3D_CHUNK_VARIABLES);
	WRITE_MICRO_CHUNK(csave,CURVE3D_VARIABLE_ISLOOPING,IsLooping);
	WRITE_MICRO_CHUNK(csave,CURVE3D_VARIABLE_KEYCOUNT,keycount);
	csave.End_Chunk();

	// Saving the keys, Note that if the format of a key changes we'll
	// need a new chunk. (I didn't wrap each variable in its own chunk)
	csave.Begin_Chunk(CURVE3D_CHUNK_KEYS);			
	for (int i=0; i<keycount; i++) {
		csave.Write(&(Keys[i].Point),sizeof(Keys[i].Point));
		csave.Write(&(Keys[i].Time),sizeof(Keys[i].Time));
	}
	csave.End_Chunk();
	return true;
}

// ?Load@Curve3DClass@@ present-unmatched
bool Curve3DClass::Load(ChunkLoadClass & cload)
{
	int i;
	int keycount = 0;
	KeyClass newkey;

	// reset the curve
	Keys.Delete_All();

	// read in the chunks
	while (cload.Open_Chunk()) {
		
		switch(cload.Cur_Chunk_ID()) 
		{
			case CURVE3D_CHUNK_VARIABLES:
			
				while (cload.Open_Micro_Chunk()) {
					switch(cload.Cur_Micro_Chunk_ID()) {
						READ_MICRO_CHUNK(cload,CURVE3D_VARIABLE_ISLOOPING,IsLooping);
						READ_MICRO_CHUNK(cload,CURVE3D_VARIABLE_KEYCOUNT,keycount);
					}
					cload.Close_Micro_Chunk();	
				}
				break;

			case CURVE3D_CHUNK_KEYS:
				for (i=0; i<keycount; i++) {
					cload.Read(&(newkey.Point),sizeof(newkey.Point));
					cload.Read(&(newkey.Time),sizeof(newkey.Time));
					Keys.Add(newkey);
				}
				break;

			default:
				WWDEBUG_SAY(("Unhandled Chunk: 0x%X File: %s Line: %d\r\n",__FILE__,__LINE__));
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}



/***********************************************************************************************
**
** LinearCurve3DClass Implementation
** Linear curve, linearly interpolates the keys
**
***********************************************************************************************/
// ?Evaluate@LinearCurve3DClass@@ present-unmatched
void LinearCurve3DClass::Evaluate(float time,Vector3 * set_val)
{
	if (time < Keys[0].Time) {
		*set_val = Keys[0].Point;
		return;
	}

	if (time >= Keys[Keys.Count() - 1].Time) {
		*set_val = Keys[Keys.Count() - 1].Point;
		return;
	}

	int i0,i1;
	float t;
	Find_Interval(time,&i0,&i1,&t);

	*set_val = Keys[i0].Point + t * (Keys[i1].Point - Keys[i0].Point);
}

// ?Get_Factory@LinearCurve3DClass@@ present-unmatched
const PersistFactoryClass & LinearCurve3DClass::Get_Factory(void) const
{
	return _LinearCurve3DFactory;
}

// ?Save@LinearCurve3DClass@@ present-unmatched
bool LinearCurve3DClass::Save(ChunkSaveClass & csave)
{
	csave.Begin_Chunk(LINEARCURVE3D_CHUNK_CURVE3D);
	Curve3DClass::Save(csave);
	csave.End_Chunk();
	return true;
}

// ?Load@LinearCurve3DClass@@ present-unmatched
bool LinearCurve3DClass::Load(ChunkLoadClass & cload)
{
	while (cload.Open_Chunk()) {
		
		switch(cload.Cur_Chunk_ID()) 
		{
			case LINEARCURVE3D_CHUNK_CURVE3D:
				Curve3DClass::Load(cload);
				break;

			default:
				WWDEBUG_SAY(("Unhandled Chunk: 0x%X File: %s Line: %d\r\n",__FILE__,__LINE__));
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}


/***********************************************************************************************
**
** Curve1DClass
**
***********************************************************************************************/
// ??0Curve1DClass@@ present-unmatched
Curve1DClass::Curve1DClass(void) :
	IsLooping(false)
{
}

// ??0Curve1DClass@@ present-unmatched
Curve1DClass::Curve1DClass(const Curve1DClass & that)
{
	*this = that;
}

// ??1Curve1DClass@@ present-unmatched
Curve1DClass::~Curve1DClass(void)
{
}

// ??4Curve1DClass@@ present-unmatched
Curve1DClass & Curve1DClass::operator = (const Curve1DClass & that)
{
	IsLooping = that.IsLooping;
	Keys = that.Keys;
	return *this;
}

// ?Is_Looping@Curve1DClass@@ present-unmatched
bool Curve1DClass::Is_Looping(void)
{
	return IsLooping;
}

void Curve1DClass::Set_Looping(bool onoff)
{
	IsLooping = onoff;
}

// ?Get_Start_Time@Curve1DClass@@ present-unmatched
float Curve1DClass::Get_Start_Time(void)
{
	if (Keys.Count() > 0) {
		return Keys[0].Time;
	} else {
		return 0.0f;
	}
}

// ?Get_End_Time@Curve1DClass@@ present-unmatched
float Curve1DClass::Get_End_Time(void)
{
	if (Keys.Count() > 0) {
		return Keys[Keys.Count() - 1].Time;
	} else {
		return 0.0f;
	}
}

// ?Key_Count@Curve1DClass@@ present-unmatched
int Curve1DClass::Key_Count(void)
{
	return Keys.Count();
}

// ?Get_Key@Curve1DClass@@ present-unmatched
void Curve1DClass::Get_Key(int i,float * set_point,float * set_t,unsigned int * extra)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	if (set_point != NULL) {
		*set_point = Keys[i].Point;
	}
	if (set_t != NULL) {
		*set_t = Keys[i].Time;
	}
	if (extra != NULL) {
		*extra = Keys[i].Extra;
	}
}

// ?Set_Key@Curve1DClass@@ present-unmatched
void Curve1DClass::Set_Key(int i,float point,unsigned int extra)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	Keys[i].Point = point;
	Keys[i].Extra = extra;
}	


// ?Add_Key@Curve1DClass@@ present-unmatched
int Curve1DClass::Add_Key(float point,float t,unsigned int extra)
{
	int idx = 0;
	while (idx < Keys.Count() && Keys[idx].Time < t) {
		idx++;
	}

	KeyClass newkey;
	newkey.Point = point;
	newkey.Time = t;
	newkey.Extra = extra;

	Keys.Insert(idx,newkey);
	return idx;
}	

// ?Remove_Key@Curve1DClass@@ present-unmatched
void Curve1DClass::Remove_Key(int i)
{
	assert(i >= 0);
	assert(i < Keys.Count());
	Keys.Delete(i);	
}

// ?Clear_Keys@Curve1DClass@@ present-unmatched
void Curve1DClass::Clear_Keys(void)
{
	Keys.Clear();
}

// ?Find_Interval@Curve1DClass@@ present-unmatched
void Curve1DClass::Find_Interval(float time,int * i0,int * i1,float * t)
{
	if (IsLooping) {
		if (time < Keys[0].Time) {
			*i0 = Keys.Count() - 1;
			*i1 = 0;
			float interval = 1.0f - Keys[*i0].Time + Keys[*i1].Time;
			*t = (1.0f - Keys[*i0].Time + time) / interval;
			return;
		}
		else if (time > Keys[Keys.Count() - 1].Time) {
			*i0 = Keys.Count() - 1;
			*i1 = 0;
			float interval = 1.0f - Keys[*i0].Time + Keys[*i1].Time;
			*t = (time - Keys[*i0].Time) / interval;
			return;
		}
	}
	else {
		WWASSERT(time >= Keys[0].Time);
		WWASSERT(time <= Keys[Keys.Count()-1].Time);
	}

	int i=0;
	while (time > Keys[i+1].Time) {
		i++;
	}
	*i0 = i;
	*i1 = i+1;
	*t = (time - Keys[i].Time) / (Keys[i+1].Time - Keys[i].Time);
}

// ?Save@Curve1DClass@@ present-unmatched
bool Curve1DClass::Save(ChunkSaveClass & csave)
{
	int keycount = Keys.Count();
	csave.Begin_Chunk(CURVE1D_CHUNK_VARIABLES);
	WRITE_MICRO_CHUNK(csave,CURVE1D_VARIABLE_ISLOOPING,IsLooping);
	WRITE_MICRO_CHUNK(csave,CURVE1D_VARIABLE_KEYCOUNT,keycount);
	csave.End_Chunk();

	// Saving the keys, Note that if the format of a key changes we'll
	// need a new chunk. (I didn't wrap each variable in its own chunk)
	csave.Begin_Chunk(CURVE1D_CHUNK_KEYS);
	for (int i=0; i<keycount; i++) {
		csave.Write(&(Keys[i].Point),sizeof(Keys[i].Point));
		csave.Write(&(Keys[i].Time),sizeof(Keys[i].Time));
		csave.Write(&(Keys[i].Extra),sizeof(Keys[i].Extra));
	}
	csave.End_Chunk();
	return true;
}

// ?Load@Curve1DClass@@ present-unmatched
bool Curve1DClass::Load(ChunkLoadClass & cload)
{
	int i;
	int keycount = 0;
	KeyClass newkey;

	// reset the curve
	Keys.Delete_All();

	// read in the chunks
	while (cload.Open_Chunk()) {
		
		switch(cload.Cur_Chunk_ID()) 
		{
			case CURVE1D_CHUNK_VARIABLES:
			
				while (cload.Open_Micro_Chunk()) {
					switch(cload.Cur_Micro_Chunk_ID()) {
						READ_MICRO_CHUNK(cload,CURVE1D_VARIABLE_ISLOOPING,IsLooping);
						READ_MICRO_CHUNK(cload,CURVE1D_VARIABLE_KEYCOUNT,keycount);
					}
					cload.Close_Micro_Chunk();	
				}
				break;

			case CURVE1D_CHUNK_KEYS:
				for (i=0; i<keycount; i++) {
					cload.Read(&(newkey.Point),sizeof(newkey.Point));
					cload.Read(&(newkey.Time),sizeof(newkey.Time));
					cload.Read(&(newkey.Extra),sizeof(newkey.Extra));
					Keys.Add(newkey);
				}
				break;

			default:
				WWDEBUG_SAY(("Unhandled Chunk: 0x%X File: %s Line: %d\r\n",__FILE__,__LINE__));
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}

/***********************************************************************************************
**
** LinearCurve1DClass, linearly interpolates the keys
**
***********************************************************************************************/
// ?Evaluate@LinearCurve1DClass@@ present-unmatched
void LinearCurve1DClass::Evaluate(float time,float * set_val)
{
	if (!IsLooping) {
		if (time < Keys[0].Time) {
			*set_val = Keys[0].Point;
			return;
		}

		if (time >= Keys[Keys.Count() - 1].Time) {
			*set_val = Keys[Keys.Count() - 1].Point;
			return;
		}
	}

	int i0,i1;
	float t;
	Find_Interval(time,&i0,&i1,&t);

	*set_val = Keys[i0].Point + t * (Keys[i1].Point - Keys[i0].Point);
}

// ?Get_Factory@LinearCurve1DClass@@ present-unmatched
const PersistFactoryClass & LinearCurve1DClass::Get_Factory(void) const
{
	return _LinearCurve1DFactory;
}

// ?Save@LinearCurve1DClass@@ present-unmatched
bool LinearCurve1DClass::Save(ChunkSaveClass & csave)
{
	csave.Begin_Chunk(LINEARCURVE1D_CHUNK_CURVE1D);
	Curve1DClass::Save(csave);
	csave.End_Chunk();
	return true;
}

// ?Load@LinearCurve1DClass@@ present-unmatched
bool LinearCurve1DClass::Load(ChunkLoadClass & cload)
{
	while (cload.Open_Chunk()) {
		
		switch(cload.Cur_Chunk_ID()) 
		{
			case LINEARCURVE1D_CHUNK_CURVE1D:
				Curve1DClass::Load(cload);
				break;

			default:
				WWDEBUG_SAY(("Unhandled Chunk: 0x%X File: %s Line: %d\r\n",__FILE__,__LINE__));
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}


