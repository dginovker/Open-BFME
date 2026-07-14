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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DPropDraw.cpp ////////////////////////////////////////////////////////////////////////
// Author: John Ahlquist, June 2--3
// Desc:   Simple prop drawing code.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "W3DDevice/GameClient/Module/W3DPropDraw.h"
#include "W3DDevice/GameClient/BaseHeightMap.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
W3DPropDrawModuleData::W3DPropDrawModuleData() 
{
}

//-------------------------------------------------------------------------------------------------
// ??1W3DPropDrawModuleData@@ present-unmatched
W3DPropDrawModuleData::~W3DPropDrawModuleData()
{
}

//-------------------------------------------------------------------------------------------------
// ?buildFieldParse@W3DPropDrawModuleData@@ present-unmatched
void W3DPropDrawModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  ModuleData::buildFieldParse(p);
	static const FieldParse dataFieldParse[] = 
	{
		{ "ModelName", INI::parseAsciiString, NULL, offsetof(W3DPropDrawModuleData, m_modelName) },
		
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0W3DPropDraw@@ present-unmatched
W3DPropDraw::W3DPropDraw( Thing *thing, const ModuleData* moduleData ) : DrawModule( thing, moduleData ),
m_propAdded(false)
{

}  // end W3DPropDraw


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DPropDraw@@ present-unmatched
W3DPropDraw::~W3DPropDraw( void )
{
}

//-------------------------------------------------------------------------------------------------
// ?reactToTransformChange@W3DPropDraw@@ present-unmatched
void W3DPropDraw::reactToTransformChange( const Matrix3D *oldMtx, 
																							 const Coord3D *oldPos, 
																							 Real oldAngle )
{
	Drawable *draw = getDrawable();
	if (m_propAdded) {
		return;
	}
	if (draw->getPosition()->x==0.0f && draw->getPosition()->y == 0.0f) {
		return;
	}
	m_propAdded = true;
	const W3DPropDrawModuleData *moduleData = getW3DPropDrawModuleData();
	if (!moduleData) {
		return;
	}
	Real scale = draw->getScale();
	TheTerrainRenderObject->addProp((Int)draw->getID(), *draw->getPosition(),
		draw->getOrientation(), scale, moduleData->m_modelName);
	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doDrawModule@W3DPropDraw@@ present-unmatched
void W3DPropDraw::doDrawModule(const Matrix3D* transformMtx)
{

	return;

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DPropDraw@@ present-unmatched
void W3DPropDraw::crc( Xfer *xfer )
{

	// extend base class
	DrawModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DPropDraw@@ present-unmatched
void W3DPropDraw::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	DrawModule::xfer( xfer );

	// no data to save here, nobody will ever notice

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DPropDraw@@ present-unmatched
void W3DPropDraw::loadPostProcess( void )
{

	// extend base class
	DrawModule::loadPostProcess();

}  // end loadPostProcess
