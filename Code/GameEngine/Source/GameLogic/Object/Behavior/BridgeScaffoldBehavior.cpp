// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: BridgeScaffoldBehavior.cpp ///////////////////////////////////////////////////////////////
// Author: Colin Day, September 2002
// Desc:   Bridge scaffold
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"
#include "Common/Xfer.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
BridgeScaffoldBehavior::BridgeScaffoldBehavior( Thing *thing, const ModuleData *moduleData )
											: UpdateModule( thing, moduleData )
{

	m_targetMotion = STM_STILL;
	m_createPos.zero();
	m_riseToPos.zero();
	m_buildPos.zero();
	m_targetPos.zero();
	m_lateralSpeed = 1.0f;
	m_verticalSpeed = 1.0f;

}  // end BridgeScaffoldBehavior

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1BridgeScaffoldBehavior@@MAE@XZ present-unmatched
BridgeScaffoldBehavior::~BridgeScaffoldBehavior( void )
{

}  // end ~BridgeScaffoldBehavior

// ------------------------------------------------------------------------------------------------
/** Set all of the target positions that we're care about as a moving scaffold object */
// ------------------------------------------------------------------------------------------------
void BridgeScaffoldBehavior::setPositions( const Coord3D *createPos,
																					 const Coord3D *riseToPos,
																					 const Coord3D *buildPos )
{

	m_createPos = *createPos;
	m_riseToPos = *riseToPos;
	m_buildPos = *buildPos;

}  // end setPositions

// ------------------------------------------------------------------------------------------------
/** Set us moving to the right target position for the requested motion type */
// ------------------------------------------------------------------------------------------------
void BridgeScaffoldBehavior::setMotion( ScaffoldTargetMotion targetMotion ) 
{

	// save the target motion type
	m_targetMotion = targetMotion;

	// given the target motion, pick a destination target
	switch( m_targetMotion )
	{

		// --------------------------------------------------------------------------------------------
		case STM_RISE: 
		case STM_TEAR_DOWN_ACROSS:
			m_targetPos = m_riseToPos; 
			break;

		// --------------------------------------------------------------------------------------------
		case STM_BUILD_ACROSS:
			m_targetPos = m_buildPos;
			break;

		// --------------------------------------------------------------------------------------------
		case STM_SINK:
			m_targetPos = m_createPos;
			break;

	}  // end switch

}  // end setMotion

// ------------------------------------------------------------------------------------------------
/** Whatever our current state of motion is, reverse it */
// ------------------------------------------------------------------------------------------------
void BridgeScaffoldBehavior::reverseMotion( void )
{

	switch( m_targetMotion )
	{

		case STM_STILL:
			setMotion( STM_TEAR_DOWN_ACROSS );
			break;

		case STM_RISE:
			setMotion( STM_SINK );
			break;

		case STM_BUILD_ACROSS:
			setMotion( STM_TEAR_DOWN_ACROSS );
			break;

		case STM_TEAR_DOWN_ACROSS:
			setMotion( STM_BUILD_ACROSS );
			break;

		case STM_SINK:
			setMotion( STM_RISE );
			break;

	}  // end switch

}  // end reverseMotion

// ------------------------------------------------------------------------------------------------
/** The update method */
// ------------------------------------------------------------------------------------------------
// ?update@BridgeScaffoldBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Body in BridgeScaffoldBehavior_update.asm (exact 580B retail).

// ------------------------------------------------------------------------------------------------
/** STATIC MEMBER:
	* Helper function to retrieve a bridge scaffold interface from an object if one is present */
// ------------------------------------------------------------------------------------------------
// ?getBridgeScaffoldBehaviorInterfaceFromObject@BridgeScaffoldBehavior@@SAPAVBridgeScaffoldBehaviorInterface@@PAVObject@@@Z present-unmatched
BridgeScaffoldBehaviorInterface *BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject( Object *obj )
{

	// santiy
	if( obj == NULL )
		return NULL;

	// get the bridge tower behavior interface
	BridgeScaffoldBehaviorInterface *bridgeScaffoldInterface = NULL;
	BehaviorModule **bmi;
	for( bmi = obj->getBehaviorModules(); *bmi; ++bmi )
	{

		bridgeScaffoldInterface = (*bmi)->getBridgeScaffoldBehaviorInterface();
		if( bridgeScaffoldInterface )
			return bridgeScaffoldInterface;

	}  // end for bmi

	// interface not found
	return NULL;

}  // end getBridgeScaffoldBehaviorInterfaceFromObject

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BridgeScaffoldBehavior@@MAEXPAVXfer@@@Z present-unmatched
void BridgeScaffoldBehavior::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@BridgeScaffoldBehavior@@MAEXPAVXfer@@@Z present-unmatched
void BridgeScaffoldBehavior::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// target motion
	xfer->xferUser( &m_targetMotion, sizeof( ScaffoldTargetMotion ) );

	// create pos
	xfer->xferCoord3D( &m_createPos );

	// rise to pos
	xfer->xferCoord3D( &m_riseToPos );

	// build pos
	xfer->xferCoord3D( &m_buildPos );

	// lateral speed
	xfer->xferReal( &m_lateralSpeed );

	// vertical speed
	xfer->xferReal( &m_verticalSpeed );

	// current target pos
	xfer->xferCoord3D( &m_targetPos );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BridgeScaffoldBehavior@@MAEXXZ present-unmatched
void BridgeScaffoldBehavior::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
