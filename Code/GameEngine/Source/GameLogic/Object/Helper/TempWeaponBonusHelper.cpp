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

// FILE: TempWeaponBonusHelper.h ////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, June 2003
// Desc:   Object helper - Clears Temporary weapon bonus effects
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"
#include "Common/Xfer.h"

#include "GameLogic/Module/TempWeaponBonusHelper.h"

#include "GameClient/Drawable.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Weapon.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0TempWeaponBonusHelper@@ present-unmatched
TempWeaponBonusHelper::TempWeaponBonusHelper( Thing *thing, const ModuleData *modData ) : ObjectHelper( thing, modData ) 
{ 
	m_currentBonus = WEAPONBONUSCONDITION_INVALID;
	m_frameToRemove = 0;

	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1TempWeaponBonusHelper@@ present-unmatched
TempWeaponBonusHelper::~TempWeaponBonusHelper( void )
{

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?update@TempWeaponBonusHelper@@ present-unmatched
UpdateSleepTime TempWeaponBonusHelper::update()
{
	DEBUG_ASSERTCRASH(m_frameToRemove <= TheGameLogic->getFrame(), ("TempWeaponBonusHelper woke up too soon.") );

	clearTempWeaponBonus(); // We are sleep driven, so seeing an update means our timer is ready implicitly
	return UPDATE_SLEEP_FOREVER;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?clearTempWeaponBonus@TempWeaponBonusHelper@@ present-unmatched
void TempWeaponBonusHelper::clearTempWeaponBonus()
{
	if( m_currentBonus != WEAPONBONUSCONDITION_INVALID )
	{
		getObject()->clearWeaponBonusCondition(m_currentBonus);
		m_currentBonus = WEAPONBONUSCONDITION_INVALID;
		m_frameToRemove = 0;

		if( getObject()->getDrawable() )
    {
			getObject()->getDrawable()->clearTintStatus(TINT_STATUS_FRENZY);
//      if (getObject()->isKindOf(KINDOF_INFANTRY))
//        getObject()->getDrawable()->setSecondMaterialPassOpacity( 0.0f );
    }
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?doTempWeaponBonus@TempWeaponBonusHelper@@ present-unmatched
void TempWeaponBonusHelper::doTempWeaponBonus( WeaponBonusConditionType status, UnsignedInt duration )
{
	// Clear any different status we may have.  Re-getting the same status will just reset the timer
	if( m_currentBonus != status )
		clearTempWeaponBonus();

	getObject()->setWeaponBonusCondition(status);
	m_currentBonus = status;
	m_frameToRemove = TheGameLogic->getFrame() + duration;

	if( getObject()->getDrawable() )
  {
		getObject()->getDrawable()->setTintStatus(TINT_STATUS_FRENZY);
//    if (getObject()->isKindOf(KINDOF_INFANTRY))
//      getObject()->getDrawable()->setSecondMaterialPassOpacity( 1.0f );
  }

	setWakeFrame( getObject(), UPDATE_SLEEP(duration) );
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@TempWeaponBonusHelper@@ present-unmatched
void TempWeaponBonusHelper::crc( Xfer *xfer )
{

	// object helper crc
	ObjectHelper::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info;
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@TempWeaponBonusHelper@@ present-unmatched
void TempWeaponBonusHelper::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// object helper base class
	ObjectHelper::xfer( xfer );

	xfer->xferUser( &m_currentBonus, sizeof(WeaponBonusConditionType) );// an enum
	xfer->xferUnsignedInt( &m_frameToRemove );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@TempWeaponBonusHelper@@ present-unmatched
void TempWeaponBonusHelper::loadPostProcess( void )
{

	// object helper base class
	ObjectHelper::loadPostProcess();

}  // end loadPostProcess

