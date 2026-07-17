// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: MaxHealthUpgrade.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, September 2002
// Desc:	 UpgradeModule that adds a scalar to the object's experience gain.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_MAXHEALTHCHANGETYPE_NAMES
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Module/MaxHealthUpgrade.h"
#include "GameLogic/Module/BodyModule.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0MaxHealthUpgradeModuleData@@QAE@XZ present-unmatched
MaxHealthUpgradeModuleData::MaxHealthUpgradeModuleData( void )
{
	m_addMaxHealth = 0.0f;
	m_maxHealthChangeType = SAME_CURRENTHEALTH;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void MaxHealthUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p) 
{

  UpgradeModuleData::buildFieldParse( p );

	static const FieldParse dataFieldParse[] = 
	{
		{ "AddMaxHealth",					INI::parseReal,					NULL,										offsetof( MaxHealthUpgradeModuleData, m_addMaxHealth ) },
		{ "ChangeType",						INI::parseIndexList,		TheMaxHealthChangeTypeNames, offsetof( MaxHealthUpgradeModuleData, m_maxHealthChangeType ) },
		{ 0, 0, 0, 0 }
	};

  p.add(dataFieldParse);

}  // end buildFieldParse

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0MaxHealthUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
MaxHealthUpgrade::MaxHealthUpgrade( Thing *thing, const ModuleData* moduleData ) : UpgradeModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1MaxHealthUpgrade@@MAE@XZ present-unmatched
MaxHealthUpgrade::~MaxHealthUpgrade( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?upgradeImplementation@MaxHealthUpgrade@@MAEXXZ present-unmatched
void MaxHealthUpgrade::upgradeImplementation( )
{
	const MaxHealthUpgradeModuleData *data = getMaxHealthUpgradeModuleData();

	//Simply add the xp scalar to the xp tracker!
	Object *obj = getObject();

	BodyModuleInterface *body = obj->getBodyModule();
	if( body )
	{
		body->setMaxHealth( body->getMaxHealth() + data->m_addMaxHealth, data->m_maxHealthChangeType );
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@MaxHealthUpgrade@@MAEXPAVXfer@@@Z present-unmatched
void MaxHealthUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@MaxHealthUpgrade@@MAEXPAVXfer@@@Z present-unmatched
void MaxHealthUpgrade::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpgradeModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@MaxHealthUpgrade@@MAEXXZ present-unmatched
void MaxHealthUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}  // end loadPostProcess
