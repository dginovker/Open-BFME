// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: ScriptActions.cpp /////////////////////////////////////////////////////////////////////////
// The game scripting engine.  Interprets scripts.
// Author: John Ahlquist, Nov. 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/AudioAffect.h"
#include "Common/AudioHandleSpecialValues.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MapObject.h"							// For MAP_XY_FACTOR
#include "Common/PartitionSolver.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/Radar.h"									// For TheRadar
#include "Common/SpecialPower.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Team.h"
#include "Common/Upgrade.h"

#include "GameClient/Anim2D.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/MessageBox.h"
#include "GameClient/Mouse.h"
#include "GameClient/View.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/Snow.h"

#include "GameLogic/AI.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/Module/CommandButtonHuntUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/Module/MobNexusContain.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/ObjectTypes.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/AIPathfind.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Kind of hacky, but we need to dance on the guts of the terrain.
extern void oversizeTheTerrain(Int amount);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// when you set controlling player or merge teams, we don't always update all the upgrade stuff
// or the indicator color. this allows us to force the situation. (srj)
static void updateTeamAndPlayerStuff( Object *obj, void *userData )
{
	if (obj)
	{
		obj->updateUpgradeModules();
		
		// srj sez: apparently we have to do this too, since Team::setControllingPlayer
		// does not. Might make more sense to do it there, but am scared to at this point.
		Drawable* draw = obj->getDrawable();
		if (draw)
		{
			if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
				draw->setIndicatorColor(obj->getNightIndicatorColor());
			else
				draw->setIndicatorColor(obj->getIndicatorColor());
		}
	}
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// STATICS ////////////////////////////////////////////////////////////////////////////////////////

// DEFINES ////////////////////////////////////////////////////////////////////////////////////////
#define REALLY_FAR	(100000 * MAP_XY_FACTOR)

// GLOBALS ////////////////////////////////////////////////////////////////////////////////////////
ScriptActionsInterface *TheScriptActions = NULL;
GameWindow *ScriptActions::m_messageWindow = NULL;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ScriptActions@@QAE@XZ present-unmatched
ScriptActions::ScriptActions()
{
	m_suppressNewWindows = FALSE;
	m_unnamedUnit = AsciiString::TheEmptyString;

}  // end ScriptActions

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ScriptActions@@UAE@XZ present-unmatched
ScriptActions::~ScriptActions()
{
	reset(); // just in case.
}  // end ~ScriptActions

//-------------------------------------------------------------------------------------------------
/** Init */
//-------------------------------------------------------------------------------------------------
// ?init@ScriptActions@@UAEXXZ present-unmatched
void ScriptActions::init( void )
{

	reset();

}  // end init

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// ?reset@ScriptActions@@UAEXXZ present-unmatched
void ScriptActions::reset( void )
{
	m_suppressNewWindows = FALSE;
	closeWindows(FALSE); // Close victory or defeat windows.

}  // end reset

//-------------------------------------------------------------------------------------------------
/** Update */
//-------------------------------------------------------------------------------------------------
// ?update@ScriptActions@@UAEXXZ present-unmatched
void ScriptActions::update( void )
{
	// Empty for now.  jba.
}  // end update


//-------------------------------------------------------------------------------------------------
/** closeWindows */
//-------------------------------------------------------------------------------------------------
// ?closeWindows@ScriptActions@@UAEX_N@Z present-unmatched
void ScriptActions::closeWindows( Bool suppressNewWindows )
{
	m_suppressNewWindows = suppressNewWindows;

	if (m_messageWindow) {
		TheWindowManager->winDestroy(m_messageWindow);
		m_messageWindow = NULL;
	}
}  

//-------------------------------------------------------------------------------------------------
/** doQuickVictory */
//-------------------------------------------------------------------------------------------------
// ?doQuickVictory@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doQuickVictory( void )
{
	closeWindows(FALSE);
	TheGameLogic->closeWindows();
	doDisableInput();
	if(TheCampaignManager)
		TheCampaignManager->SetVictorious(TRUE);
	TheScriptEngine->startQuickEndGameTimer();
}

//-------------------------------------------------------------------------------------------------
/** doSetInfantryLightingOverride */
//-------------------------------------------------------------------------------------------------
// BFME packs m_scriptOverrideInfantryLightScale at GlobalData+0xdc8.
struct BfmeGlobalDataInfantryLight {
	UnsignedByte _pad[0xdc8];
	Real m_scriptOverrideInfantryLightScale;
};

void ScriptActions::doSetInfantryLightingOverride(Real setting)
{
	((BfmeGlobalDataInfantryLight *)TheWritableGlobalData)->m_scriptOverrideInfantryLightScale = setting;
}

//-------------------------------------------------------------------------------------------------
/** doVictory */
//-------------------------------------------------------------------------------------------------
// ?doVictory@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doVictory( void )
{
	closeWindows(FALSE);
	TheGameLogic->closeWindows();
	doDisableInput();
	if (!m_suppressNewWindows)
	{
		const Player *localPlayer = ThePlayerList->getLocalPlayer();
		Bool showObserverWindow = localPlayer->isPlayerObserver() || TheScriptEngine->hasShownMPLocalDefeatWindow();
		if(showObserverWindow)
			m_messageWindow = TheWindowManager->winCreateFromScript("Menus/ObserverQuit.wnd");
		else
		{
			m_messageWindow = TheWindowManager->winCreateFromScript("Menus/Victorious.wnd");
		}
	}	
	if(TheCampaignManager)
		TheCampaignManager->SetVictorious(TRUE);
	TheScriptEngine->startEndGameTimer();
}

//-------------------------------------------------------------------------------------------------
/** doDefeat */
//-------------------------------------------------------------------------------------------------
// ?doDefeat@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doDefeat( void )
{
	closeWindows(FALSE);
	TheGameLogic->closeWindows();
	doDisableInput();
	if (!m_suppressNewWindows)
	{
		const Player *localPlayer = ThePlayerList->getLocalPlayer();
		Bool showObserverWindow = localPlayer->isPlayerObserver() || TheScriptEngine->hasShownMPLocalDefeatWindow();
		if(showObserverWindow)
			m_messageWindow = TheWindowManager->winCreateFromScript("Menus/ObserverQuit.wnd");
		else
		{
			m_messageWindow = TheWindowManager->winCreateFromScript("Menus/Defeat.wnd");
		}
	}
	if(TheCampaignManager)
		TheCampaignManager->SetVictorious(FALSE);
	TheScriptEngine->startEndGameTimer();
}

//-------------------------------------------------------------------------------------------------
/** doLocalDefeat */
//-------------------------------------------------------------------------------------------------
// ?doLocalDefeat@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doLocalDefeat( void )
{
	TheScriptEngine->markMPLocalDefeatWindowShown();
	closeWindows(FALSE);
	TheGameLogic->closeWindows();
	if (!m_suppressNewWindows)
	{
		if(!TheVictoryConditions->amIObserver())
			m_messageWindow = TheWindowManager->winCreateFromScript("Menus/LocalDefeat.wnd");
	}
	if(TheCampaignManager)
		TheCampaignManager->SetVictorious(FALSE);
	TheScriptEngine->startCloseWindowTimer();
}

//-------------------------------------------------------------------------------------------------
/** changeObjectPanelFlagForSingleObject */
//-------------------------------------------------------------------------------------------------
// ?changeObjectPanelFlagForSingleObject@ScriptActions@@IAEXPAVObject@@ABVAsciiString@@_N@Z present-unmatched
void ScriptActions::changeObjectPanelFlagForSingleObject(Object *obj, const AsciiString& flagToChange, Bool newVal )
{
	// Enabled flag
	if (flagToChange == TheObjectFlagsNames[0])
	{
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !newVal);
		return;
	}

	// Powered flag
	if (flagToChange == TheObjectFlagsNames[1])
	{
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNPOWERED, !newVal);
		return;
	}

	// Indestructible flag
	if (flagToChange == TheObjectFlagsNames[2])
	{
		BodyModuleInterface* body = obj->getBodyModule();
		if (body)	{
			body->setIndestructible(newVal);
		}
		return;
	}

	// Unsellable flag
	if (flagToChange == TheObjectFlagsNames[3])
	{
		obj->setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, newVal);
		return;
	}

	// Selectable flag
	if (flagToChange == TheObjectFlagsNames[4])
	{
		if (obj->isSelectable() != newVal) {
			obj->setSelectable(newVal);
		}
		return;
	}

	// AI Recruitable flag
	if (flagToChange == TheObjectFlagsNames[5])
	{
		if (obj->getAIUpdateInterface()) {
			obj->getAIUpdateInterface()->setIsRecruitable(newVal);
		}

		return;
	}

	// Player targetable flag
	if( flagToChange == TheObjectFlagsNames[6] )
	{
		obj->setScriptStatus( OBJECT_STATUS_SCRIPT_TARGETABLE, newVal );
		return;
	}

}

//-------------------------------------------------------------------------------------------------
/** doDebugMessage */
//-------------------------------------------------------------------------------------------------
// ?doDebugMessage@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doDebugMessage(const AsciiString& msg, Bool pause )
{
	TheScriptEngine->AppendDebugMessage(msg, pause);
}  

//-------------------------------------------------------------------------------------------------
/** doPlaySoundEffect */
//-------------------------------------------------------------------------------------------------
// ?doPlaySoundEffect@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlaySoundEffect(const AsciiString& sound)
{
	AudioEventRTS audioEvent(sound);
	audioEvent.setIsLogicalAudio(true);
	audioEvent.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent( &audioEvent );
}  


//-------------------------------------------------------------------------------------------------
/** doPlaySoundEffectAt */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doPlaySoundEffectAt(const AsciiString& sound, const AsciiString& waypoint)
{	
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	if (!way) {
		return;
	}

	AudioEventRTS audioEvent(sound, way->getLocation());
	audioEvent.setIsLogicalAudio(true);
	audioEvent.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent( &audioEvent );
}  

//-------------------------------------------------------------------------------------------------
/** doEnableObjectSound */
//-------------------------------------------------------------------------------------------------
// ?doEnableObjectSound@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doEnableObjectSound(const AsciiString& objectName, Bool enable )
{	
	Object *object = TheScriptEngine->getUnitNamed(objectName);
	if (!object)
	{
		return;
	}

	Drawable *drawable = object->getDrawable();
	if ( !drawable )
	{
		return;
	}

  drawable->enableAmbientSoundFromScript( enable );
}	


//-------------------------------------------------------------------------------------------------
/** doDamageTeamMembers */
//-------------------------------------------------------------------------------------------------
// ?doDamageTeamMembers@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doDamageTeamMembers(const AsciiString& team, Real amount)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (theTeam) {
		theTeam->damageTeamMembers(amount);
	}
}  

//-------------------------------------------------------------------------------------------------
/** doMoveToWaypoint */
//-------------------------------------------------------------------------------------------------
// ?doMoveToWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doMoveToWaypoint(const AsciiString& team, const AsciiString& waypoint)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );

	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (theTeam) {
		AIGroup* theGroup = TheAI->createGroup();
		if (!theGroup) {
			return;
		}

		theTeam->getTeamAsAIGroup(theGroup);
		Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
		if (way) {
			Coord3D destination = *way->getLocation();
			//DEBUG_LOG(("Moving team to waypoint %f, %f, %f\n", destination.x, destination.y, destination.z));
 			theGroup->groupMoveToPosition( &destination, false, CMD_FROM_SCRIPT );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedMoveToWaypoint */
//-------------------------------------------------------------------------------------------------
// ?doNamedMoveToWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedMoveToWaypoint(const AsciiString& unit, const AsciiString& waypoint)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj) 
	{
		Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
		if (!way) {
			return;
		}

		Coord3D destination = *way->getLocation();

		AIUpdateInterface *aiUpdate = theObj->getAIUpdateInterface();
		if (!aiUpdate) {
			return;
		}
		
		aiUpdate->clearWaypointQueue();
		theObj->leaveGroup();
		aiUpdate->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
		aiUpdate->aiMoveToPosition( &destination, CMD_FROM_SCRIPT );

	}
}

//-------------------------------------------------------------------------------------------------
/** doCameraFollowNamed */
//-------------------------------------------------------------------------------------------------
// ?doCameraFollowNamed@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doCameraFollowNamed(const AsciiString& unit, Bool snapToUnit)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj) 
	{	
		TheTacticalView->setCameraLock(theObj->getID());
		if (snapToUnit)
			TheTacticalView->snapToCameraLock();

		TheTacticalView->setSnapMode( View::LOCK_FOLLOW, 0.0f );
	}
}

//-------------------------------------------------------------------------------------------------
/** doStopCameraFollowUnit */
//-------------------------------------------------------------------------------------------------
// BFME View void stop-follow at +0x19c.
class BfmeViewStopFollow {
public:
	virtual void _vsf_0() = 0;
	virtual void _vsf_1() = 0;
	virtual void _vsf_2() = 0;
	virtual void _vsf_3() = 0;
	virtual void _vsf_4() = 0;
	virtual void _vsf_5() = 0;
	virtual void _vsf_6() = 0;
	virtual void _vsf_7() = 0;
	virtual void _vsf_8() = 0;
	virtual void _vsf_9() = 0;
	virtual void _vsf_10() = 0;
	virtual void _vsf_11() = 0;
	virtual void _vsf_12() = 0;
	virtual void _vsf_13() = 0;
	virtual void _vsf_14() = 0;
	virtual void _vsf_15() = 0;
	virtual void _vsf_16() = 0;
	virtual void _vsf_17() = 0;
	virtual void _vsf_18() = 0;
	virtual void _vsf_19() = 0;
	virtual void _vsf_20() = 0;
	virtual void _vsf_21() = 0;
	virtual void _vsf_22() = 0;
	virtual void _vsf_23() = 0;
	virtual void _vsf_24() = 0;
	virtual void _vsf_25() = 0;
	virtual void _vsf_26() = 0;
	virtual void _vsf_27() = 0;
	virtual void _vsf_28() = 0;
	virtual void _vsf_29() = 0;
	virtual void _vsf_30() = 0;
	virtual void _vsf_31() = 0;
	virtual void _vsf_32() = 0;
	virtual void _vsf_33() = 0;
	virtual void _vsf_34() = 0;
	virtual void _vsf_35() = 0;
	virtual void _vsf_36() = 0;
	virtual void _vsf_37() = 0;
	virtual void _vsf_38() = 0;
	virtual void _vsf_39() = 0;
	virtual void _vsf_40() = 0;
	virtual void _vsf_41() = 0;
	virtual void _vsf_42() = 0;
	virtual void _vsf_43() = 0;
	virtual void _vsf_44() = 0;
	virtual void _vsf_45() = 0;
	virtual void _vsf_46() = 0;
	virtual void _vsf_47() = 0;
	virtual void _vsf_48() = 0;
	virtual void _vsf_49() = 0;
	virtual void _vsf_50() = 0;
	virtual void _vsf_51() = 0;
	virtual void _vsf_52() = 0;
	virtual void _vsf_53() = 0;
	virtual void _vsf_54() = 0;
	virtual void _vsf_55() = 0;
	virtual void _vsf_56() = 0;
	virtual void _vsf_57() = 0;
	virtual void _vsf_58() = 0;
	virtual void _vsf_59() = 0;
	virtual void _vsf_60() = 0;
	virtual void _vsf_61() = 0;
	virtual void _vsf_62() = 0;
	virtual void _vsf_63() = 0;
	virtual void _vsf_64() = 0;
	virtual void _vsf_65() = 0;
	virtual void _vsf_66() = 0;
	virtual void _vsf_67() = 0;
	virtual void _vsf_68() = 0;
	virtual void _vsf_69() = 0;
	virtual void _vsf_70() = 0;
	virtual void _vsf_71() = 0;
	virtual void _vsf_72() = 0;
	virtual void _vsf_73() = 0;
	virtual void _vsf_74() = 0;
	virtual void _vsf_75() = 0;
	virtual void _vsf_76() = 0;
	virtual void _vsf_77() = 0;
	virtual void _vsf_78() = 0;
	virtual void _vsf_79() = 0;
	virtual void _vsf_80() = 0;
	virtual void _vsf_81() = 0;
	virtual void _vsf_82() = 0;
	virtual void _vsf_83() = 0;
	virtual void _vsf_84() = 0;
	virtual void _vsf_85() = 0;
	virtual void _vsf_86() = 0;
	virtual void _vsf_87() = 0;
	virtual void _vsf_88() = 0;
	virtual void _vsf_89() = 0;
	virtual void _vsf_90() = 0;
	virtual void _vsf_91() = 0;
	virtual void _vsf_92() = 0;
	virtual void _vsf_93() = 0;
	virtual void _vsf_94() = 0;
	virtual void _vsf_95() = 0;
	virtual void _vsf_96() = 0;
	virtual void _vsf_97() = 0;
	virtual void _vsf_98() = 0;
	virtual void _vsf_99() = 0;
	virtual void _vsf_100() = 0;
	virtual void _vsf_101() = 0;
	virtual void _vsf_102() = 0;
	virtual void stopFollow(void) = 0;
};

void ScriptActions::doStopCameraFollowUnit(void)
{
	((BfmeViewStopFollow *)TheTacticalView)->stopFollow();
}

//-------------------------------------------------------------------------------------------------
/** doSetTeamState */
//-------------------------------------------------------------------------------------------------
// ?doSetTeamState@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doSetTeamState(const AsciiString& team, const AsciiString& state)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (theTeam) {
		theTeam->setState(state);
	}
}	

/** doCreateReinforcements */
//-------------------------------------------------------------------------------------------------
// ?doCreateReinforcements@ScriptActions@@ present-unmatched
void ScriptActions::doCreateReinforcements(const AsciiString& team, const AsciiString& waypoint)
{
	TeamPrototype *theTeamProto = TheTeamFactory->findTeamPrototype( team );
	Coord3D destination;


	Bool needToMoveToDestination = false;
	//Validate the waypoint
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint); 
	if (way==NULL) 
	{
		return;
	}

	destination = *way->getLocation();
	if (!theTeamProto) {
		DEBUG_LOG(("***WARNING - Team %s not found.\n", team));
		return;
	}
	const TeamTemplateInfo *pInfo = theTeamProto->getTemplateInfo();
	Coord3D origin = destination;
	way = TheTerrainLogic->getWaypointByName(pInfo->m_startReinforceWaypoint);
	if (way) {
		origin = *way->getLocation();
		if (origin.x != destination.x || origin.y != destination.y) {
			needToMoveToDestination = true;
		}
	}

	//Create the team (not the units inside team).
	Team *theTeam = TheTeamFactory->createInactiveTeam( team );
	if (theTeam==NULL) {
		return;
	}
	const ThingTemplate *transportTemplate;
	const ThingTemplate *unitTemplate;

	//Create the transport first (if applicable), so we can determine if it has paradrop capabilities.
	//If so, we'll be doing a lot of things differently!
	Object *transport=NULL;
	ContainModuleInterface *contain = NULL;
	transportTemplate = TheThingFactory->findTemplate( pInfo->m_transportUnitType );
	if( transportTemplate ) 
	{
		transport = TheThingFactory->newObject( transportTemplate, theTeam );
		transport->setPosition( &origin );
		transport->setOrientation( 0.0f );
		if( transport ) 
		{
			contain = transport->getContain();
		}
	}
	Int transportCount = 1;

	//Check to see if we have a transport, and if our transport has paradrop capabilities. If this is the
	//case, we'll need to create each unit inside "parachute containers".
	static NameKeyType key_DeliverPayloadAIUpdate = NAMEKEY("DeliverPayloadAIUpdate");
	DeliverPayloadAIUpdate *dp = NULL;
	if( transport )
	{
		dp = (DeliverPayloadAIUpdate*)transport->findUpdateModule(key_DeliverPayloadAIUpdate);
	}

	//Our tranport has a deliverPayload update module. This means it'll do airborned drops.

	const ThingTemplate* putInContainerTemplate  = NULL;
	if( dp )
	{
		//Check to see if we are packaging our units
		putInContainerTemplate = dp->getPutInContainerTemplateViaModuleData();
	}

	//Now create the units that make up the team.
	Int i, j;
	for (i=0; i<pInfo->m_numUnitsInfo; i++) 
	{
		// get thing template based from map object name
		unitTemplate = TheThingFactory->findTemplate(pInfo->m_unitsInfo[i].unitThingName);
		Coord3D pos = origin;
		if (unitTemplate && theTeam) 
		{
			Object *obj = NULL;
			for (j=0; j<pInfo->m_unitsInfo[i].maxUnits; j++) 
			{
				// create new object in the world
				obj = TheThingFactory->newObject( unitTemplate, theTeam );
				if( obj )
				{
					/// @todo - have better positioning for reinforcement units.
					pos.x = origin.x + 2.25*(j)*obj->getGeometryInfo().getMajorRadius();
					pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
					obj->setPosition( &pos );
					obj->setOrientation(0.0f);
          

				}  // end if
			}
			if (obj) pos.y += 2*obj->getGeometryInfo().getMajorRadius();
		}
		origin.y = pos.y;
	}
	origin = destination;
	if (pInfo->m_teamStartsFull) 
	{
		// Have them load into transports in the team.
		EntriesVec vecOfUnits;
		SpacesVec vecOfTransports;
		
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj) {
				continue;
			}
			if (obj==transport) {
				continue; // Skip the one we created.  The team loads into the transports on the team for team starts full. jba
			}
			if (obj->isKindOf(KINDOF_TRANSPORT)) 
			{
				ContainModuleInterface *contain = obj->getContain();
				if( contain )
				{
					vecOfTransports.push_back(std::make_pair(obj->getID(), ((TransportContain*)contain)->getContainMax()));
				}
				else
				{
					DEBUG_CRASH( ("doCreateReinforcement script -- transport doesn't have contain to hold guys.") );
				}
			} 
			else 
			{
				Int slots = obj->getTransportSlotCount();
				if (slots==0) slots = 0x7fffff; // 0 means lots.
				vecOfUnits.push_back(std::make_pair(obj->getID(), slots));
			}
		}

		// we've now built the necessary stuff. Partition the units.

		PartitionSolver partition(vecOfUnits, vecOfTransports, PREFER_FAST_SOLUTION);
		partition.solve();
		SolutionVec solution = partition.getSolution();
		for (int i = 0; i < solution.size(); ++i) {
			Object *unit = TheGameLogic->findObjectByID(solution[i].first);
			Object *trans = TheGameLogic->findObjectByID(solution[i].second);
			if (!unit || !trans) {
				continue;
			}
			ContainModuleInterface *contain = trans->getContain();
			if (contain) 
			{
				contain->addToContain(unit);
			}
		}		

	}
	contain = NULL;
	if( transport )
	{
		contain = transport->getContain();
	}
	if (contain) 
	{
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj) 
			{
				continue;
			}
			if (obj->getTemplate()->isEquivalentTo(transport->getTemplate()) ) 
			{
				// it's our transport.
				continue;
			}
			if (obj->getContainedBy() != NULL) 
			{
				continue;
			}
			//Check to see if it's a valid transport for this unit, even if it's full.

			Coord3D pos = origin;
			pos.x += transportCount*transport->getGeometryInfo().getMajorRadius();
			pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
			
			if (contain && contain->isValidContainerFor(obj, false)) 
			{
				//Now that we know it fits in the transport, check to see if it's full. If it is,
				//then we'll create a new transport.
				if (!contain->isValidContainerFor(obj, true)) 
				{
					// full, try building another.
					transport = TheThingFactory->newObject( transportTemplate, theTeam );
					transport->setPosition( &pos );
					transportCount++;
					transport->setOrientation(0.0f);
					if (transport) 
					{
						contain = transport->getContain();
					}
				}
				//If our unit is going to be put in another container (such as infantry being contained by a parachute)
				//do so now.
				if( putInContainerTemplate )
				{
					Object* container = TheThingFactory->newObject( putInContainerTemplate, theTeam );
					container->setPosition( &pos );

					//Make sure this is valid.
					if( container->getContain() && container->getContain()->isValidContainerFor( obj, true ) )
					{
						container->getContain()->addToContain( obj );
						obj = container;
					}
					else
					{
						DEBUG_CRASH( ("doCreateReinforcements: PutInContainer %s is full, or not valid for the payload %s!", putInContainerTemplate->getName().str(), obj->getTemplate()->getName().str() ) );
					}
				}

				//Add our unit to the transport.
				contain->addToContain( obj );
			}
		}
	}


	if (theTeam) 
	{
		if (transport) 
		{
			for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
			{
				Object *obj = iter.cur();
				if (!obj) 
				{
					continue;
				}
				AIUpdateInterface *ai = obj->getAIUpdateInterface();
				if (obj->getTemplate()->isEquivalentTo(transport->getTemplate()) ) 
				{
					if( dp )
					{
						dp->deliverPayloadViaModuleData( &destination );
					}
					// it's our transport.
					else if( pInfo->m_transportsExit )
					{
						if( ai )
						{
							ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
							ai->aiMoveToAndEvacuateAndExit(&destination, CMD_FROM_SCRIPT);
						}
					}
					else
					{
						if( ai )
						{
							ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
							ai->aiMoveToAndEvacuate( &destination, CMD_FROM_SCRIPT );
						}
					}
				}	
				else 
				{
					// If there are any units that aren't transportable, move them to the goal.
					if( !obj->isDisabledByType( DISABLED_HELD ) ) 
					{
						if( ai )
						{
							ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
							ai->aiMoveToPosition(&destination, CMD_FROM_SCRIPT);
						}
					}
				}
			}
		} 
		else 
		{
			theTeam->setActive();
			if (needToMoveToDestination) 
			{
				AIGroup* theGroup = TheAI->createGroup();
				if (!theGroup) 
				{
					return;
				}
				theTeam->getTeamAsAIGroup(theGroup);
				theGroup->groupMoveToPosition( &destination, false, CMD_FROM_SCRIPT );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doMoveCameraTo */
//-------------------------------------------------------------------------------------------------
// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z present-unmatched
void ScriptActions::doMoveCameraTo(const AsciiString& waypoint, Real sec, Real cameraStutterSec, Real easeIn, Real easeOut)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			Coord3D destination = *way->getLocation();
			TheTacticalView->moveCameraTo(&destination, sec*1000, cameraStutterSec*1000, true, easeIn*1000.0f, easeOut*1000.0f);			
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doZoomCamera */
//-------------------------------------------------------------------------------------------------
// BFME View vtable +0xe8: zoomCamera(Real, Int, Real, Real). True body 0x2EDC20
// (queue RVA 0x9DE809 was mid-instruction inside an unrelated fn).
class BfmeViewVtbl_e8 {
public:
	virtual void _ve8_0() = 0;
	virtual void _ve8_1() = 0;
	virtual void _ve8_2() = 0;
	virtual void _ve8_3() = 0;
	virtual void _ve8_4() = 0;
	virtual void _ve8_5() = 0;
	virtual void _ve8_6() = 0;
	virtual void _ve8_7() = 0;
	virtual void _ve8_8() = 0;
	virtual void _ve8_9() = 0;
	virtual void _ve8_10() = 0;
	virtual void _ve8_11() = 0;
	virtual void _ve8_12() = 0;
	virtual void _ve8_13() = 0;
	virtual void _ve8_14() = 0;
	virtual void _ve8_15() = 0;
	virtual void _ve8_16() = 0;
	virtual void _ve8_17() = 0;
	virtual void _ve8_18() = 0;
	virtual void _ve8_19() = 0;
	virtual void _ve8_20() = 0;
	virtual void _ve8_21() = 0;
	virtual void _ve8_22() = 0;
	virtual void _ve8_23() = 0;
	virtual void _ve8_24() = 0;
	virtual void _ve8_25() = 0;
	virtual void _ve8_26() = 0;
	virtual void _ve8_27() = 0;
	virtual void _ve8_28() = 0;
	virtual void _ve8_29() = 0;
	virtual void _ve8_30() = 0;
	virtual void _ve8_31() = 0;
	virtual void _ve8_32() = 0;
	virtual void _ve8_33() = 0;
	virtual void _ve8_34() = 0;
	virtual void _ve8_35() = 0;
	virtual void _ve8_36() = 0;
	virtual void _ve8_37() = 0;
	virtual void _ve8_38() = 0;
	virtual void _ve8_39() = 0;
	virtual void _ve8_40() = 0;
	virtual void _ve8_41() = 0;
	virtual void _ve8_42() = 0;
	virtual void _ve8_43() = 0;
	virtual void _ve8_44() = 0;
	virtual void _ve8_45() = 0;
	virtual void _ve8_46() = 0;
	virtual void _ve8_47() = 0;
	virtual void _ve8_48() = 0;
	virtual void _ve8_49() = 0;
	virtual void _ve8_50() = 0;
	virtual void _ve8_51() = 0;
	virtual void _ve8_52() = 0;
	virtual void _ve8_53() = 0;
	virtual void _ve8_54() = 0;
	virtual void _ve8_55() = 0;
	virtual void _ve8_56() = 0;
	virtual void _ve8_57() = 0;
	virtual void zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut) = 0;
};

void ScriptActions::doZoomCamera(Real zoom, Real sec, Real easeIn, Real easeOut)
{
	((BfmeViewVtbl_e8 *)TheTacticalView)->zoomCamera(zoom, sec*1000.0f, easeIn*1000.0f, easeOut*1000.0f);
}

//-------------------------------------------------------------------------------------------------
/** doPitchCamera */
//-------------------------------------------------------------------------------------------------
// ?doPitchCamera@ScriptActions@@IAEXMMMM@Z present-unmatched
void ScriptActions::doPitchCamera(Real pitch, Real sec, Real easeIn, Real easeOut)
{
	TheTacticalView->pitchCamera(pitch, sec*1000.0f, easeIn*1000.0f, easeOut*1000.0f);
}

//-------------------------------------------------------------------------------------------------
/** doOversizeTheTerrain */
//-------------------------------------------------------------------------------------------------
// ?doOversizeTheTerrain@ScriptActions@@IAEXH@Z present-unmatched
void ScriptActions::doOversizeTheTerrain(Int amount)
{
	oversizeTheTerrain(amount);
	Coord2D offset;
	offset.x = 0.0001f;
	offset.y = 0.0001f;
	TheTacticalView->scrollBy(&offset);
	offset.x = -0.0001f;
	offset.y = -0.0001f;
	TheTacticalView->scrollBy(&offset);
}

//-------------------------------------------------------------------------------------------------
/** doSetupCamera */
//-------------------------------------------------------------------------------------------------
// ?doSetupCamera@ScriptActions@@IAEXABVAsciiString@@MM0@Z present-unmatched
void ScriptActions::doSetupCamera(const AsciiString& waypoint, Real zoom, Real pitch, const AsciiString& lookAtWaypoint)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	if (way==NULL) return;
	Coord3D	pos = *way->getLocation();
	Waypoint *lookat = TheTerrainLogic->getWaypointByName(lookAtWaypoint); 
	if (lookat==NULL) return;
	Coord3D destination = *lookat->getLocation();
	TheTacticalView->moveCameraTo(&pos, 0, 0, true, 0.0f, 0.0f);			
	TheTacticalView->cameraModLookToward(&destination);			
	TheTacticalView->cameraModFinalPitch(pitch, 0.0f, 0.0f);
	TheTacticalView->cameraModFinalZoom(zoom, 0.0f, 0.0f);
}

//-------------------------------------------------------------------------------------------------
/** doModCameraLookToward */
//-------------------------------------------------------------------------------------------------
// ?doModCameraLookToward@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doModCameraLookToward(const AsciiString& waypoint)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			Coord3D destination = *way->getLocation();
			TheTacticalView->cameraModLookToward(&destination);			
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doModCameraFinalLookToward */
//-------------------------------------------------------------------------------------------------
// ?doModCameraFinalLookToward@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doModCameraFinalLookToward(const AsciiString& waypoint)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			Coord3D destination = *way->getLocation();
			TheTacticalView->cameraModFinalLookToward(&destination);			
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doModCameraMoveToSelection */
//-------------------------------------------------------------------------------------------------
// ?doModCameraMoveToSelection@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doModCameraMoveToSelection(void)
{
	Int count=0;
	Coord3D destination;
	destination.x=destination.y=destination.z = 0;

	for (Drawable *d = TheGameClient->firstDrawable(); d; d = d->getNextDrawable())
	{
		if (d->isSelected())
		{	
			Coord3D pos = *d->getPosition();
			destination.x += pos.x;
			destination.y += pos.y;
			destination.z += pos.z;
			count++;
		}
	}
	if (count) {
		destination.z /= count;
		destination.x /= count;
		destination.y /= count;
		TheTacticalView->cameraModFinalMoveTo(&destination);			
	}

}

//-------------------------------------------------------------------------------------------------
/** doResetCamera */
//-------------------------------------------------------------------------------------------------
// ?doResetCamera@ScriptActions@@IAEXABVAsciiString@@MMM@Z present-unmatched
void ScriptActions::doResetCamera(const AsciiString& waypoint, Real sec, Real easeIn, Real easeOut)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			Coord3D destination = *way->getLocation();
			TheTacticalView->resetCamera(&destination, sec*1000, easeIn*1000.0f, easeOut*1000.0f);			
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doRotateCamera around the object we are looking at. */
//-------------------------------------------------------------------------------------------------
// ?doRotateCamera@ScriptActions@@IAEXMMMM@Z present-unmatched
void ScriptActions::doRotateCamera(Real rotations, Real sec, Real easeIn, Real easeOut)
{
	TheTacticalView->rotateCamera(rotations, sec*1000.0f, easeIn*1000.0f, easeOut*1000.0f);			
}

//-------------------------------------------------------------------------------------------------
/** doRotateCameraTowardObject */
//-------------------------------------------------------------------------------------------------
// ?doRotateCameraTowardObject@ScriptActions@@IAEXABVAsciiString@@MMMM@Z present-unmatched
void ScriptActions::doRotateCameraTowardObject(const AsciiString& unitName, Real sec, Real holdSec, Real easeIn, Real easeOut)
{
	const Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;
	TheTacticalView->rotateCameraTowardObject(unit->getID(), sec*1000.0f, holdSec*1000.0f, easeIn*1000.0f, easeOut*1000.0f);			
}

//-------------------------------------------------------------------------------------------------
/** doRotateCameraTowardWaypoint */
//-------------------------------------------------------------------------------------------------
// ?doRotateCameraTowardWaypoint@ScriptActions@@IAEXABVAsciiString@@MMM_N@Z present-unmatched
void ScriptActions::doRotateCameraTowardWaypoint(const AsciiString& waypointName, Real sec, Real easeIn, Real easeOut, Bool reverseRotation)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (way==NULL) return;
	TheTacticalView->rotateCameraTowardPosition(way->getLocation(), sec*1000.0f, easeIn*1000.0f, easeOut*1000.0f, reverseRotation);			
}

//-------------------------------------------------------------------------------------------------
/** doMoveAlongWaypointPath */
//-------------------------------------------------------------------------------------------------
// ?doMoveCameraAlongWaypointPath@ScriptActions@@IAEXABVAsciiString@@MMMM@Z present-unmatched
void ScriptActions::doMoveCameraAlongWaypointPath(const AsciiString& waypoint, Real sec, Real cameraStutterSec, Real easeIn, Real easeOut)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (way->getName() == waypoint) {
			TheTacticalView->moveCameraAlongWaypointPath(way, sec*1000, cameraStutterSec*1000, true, easeIn*1000.0f, easeOut*1000.0f);			
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doCreateObject */
//-------------------------------------------------------------------------------------------------
// ?doCreateObject@ScriptActions@@IAEXABVAsciiString@@00PAUCoord3D@@M@Z present-unmatched
void ScriptActions::doCreateObject(const AsciiString& objectName, const AsciiString& thingName, const AsciiString& teamName, Coord3D *pos, Real angle )
{
	Object* pOldObj = NULL;

	if (objectName != m_unnamedUnit) {
		 pOldObj = TheScriptEngine->getUnitNamed(objectName);

		if (pOldObj && !pOldObj->isEffectivelyDead()) {
			AsciiString str = "WARNING - Object with name ";
			str.concat(objectName);
			str.concat(" already exists. Failed Create.");
			TheScriptEngine->AppendDebugMessage(str, false);
				// Unit by that name already exists
			return;
		}
	}

	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (theTeam==NULL) {
		// We may need to create the team.
		theTeam = TheTeamFactory->createTeam( teamName );
	}
	if (!theTeam) {
		TheScriptEngine->AppendDebugMessage("***WARNING - Team not found:***", false);
		TheScriptEngine->AppendDebugMessage(teamName, true);
		DEBUG_LOG(("WARNING - Team %s not found.\n", teamName.str()));
		return;
	}
	const ThingTemplate *thingTemplate;
	// get thing template based from map object name
	thingTemplate = TheThingFactory->findTemplate(thingName);
	if (thingTemplate) {
		// create new object in the world
		Object *obj = TheThingFactory->newObject( thingTemplate, theTeam );
		if( obj )
		{
			if (objectName != m_unnamedUnit) {
				obj->setName(objectName);
				if (pOldObj || TheScriptEngine->didUnitExist(objectName)) {
					TheScriptEngine->transferObjectName(objectName, obj);
				} else {
					TheScriptEngine->addObjectToCache(obj);
				}
			}

			obj->setOrientation(angle);
			obj->setPosition( pos );
      
      if ( obj->isKindOf( KINDOF_BLAST_CRATER ) ) // since these footprints are permanent
      {
        TheTerrainLogic->createCraterInTerrain( obj );
        TheAI->pathfinder()->addObjectToPathfindMap( obj );
      }


		}  // end if
	} else {
		DEBUG_LOG(("WARNING - ThingTemplate '%s' not found.\n", thingName.str()));
	}
}

//-------------------------------------------------------------------------------------------------
/** doAttack */
//-------------------------------------------------------------------------------------------------
// ?doAttack@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doAttack(const AsciiString& attackerName, const AsciiString& victimName)
{
	Team *attackingTeam = TheScriptEngine->getTeamNamed( attackerName );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	const Team *victimTeam = TheScriptEngine->getTeamNamed( victimName );
	
	// sanity
	if( attackingTeam == NULL || victimTeam == NULL )
		return;

	AIGroup *aiGroup = TheAI->createGroup();
	if (!aiGroup) {
		return;
	}

	attackingTeam->getTeamAsAIGroup(aiGroup);
	aiGroup->groupAttackTeam(victimTeam, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT);

}

//-------------------------------------------------------------------------------------------------
/** doNamedAttack */
//-------------------------------------------------------------------------------------------------
// ?doNamedAttack@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedAttack(const AsciiString& attackerName, const AsciiString& victimName)
{
	/// @todo Implement me (MSB)

	Object *attackingObj = TheScriptEngine->getUnitNamed( attackerName );
	Object *victimObj = TheScriptEngine->getUnitNamed( victimName );

	if (!attackingObj || !victimObj) {
		return;
	}
	// tell every member of attacking team to attack a random member of victim team

	{
		AIUpdateInterface *aiUpdate = attackingObj->getAIUpdateInterface();

		if (aiUpdate)
		{
			/// @todo Teams should have a method that returns the number of members in the team (MSB)
			attackingObj->leaveGroup();
			aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
			aiUpdate->aiForceAttackObject( victimObj, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doBuildBuilding */
//-------------------------------------------------------------------------------------------------
// ?doBuildBuilding@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doBuildBuilding(const AsciiString& buildingType)
{
	// This action ALWAYS occur on the current player.
	Player *thePlayer = TheScriptEngine->getCurrentPlayer();
	if (thePlayer) {
		thePlayer->buildSpecificBuilding(buildingType);
	}
}

//-------------------------------------------------------------------------------------------------
/** doBuildSupplyCenter */
//-------------------------------------------------------------------------------------------------
// ?doBuildSupplyCenter@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doBuildSupplyCenter(const AsciiString& player, const AsciiString& buildingType, Int cash)
{
	Player* thePlayer = TheScriptEngine->getPlayerFromAsciiString(player);
	if (thePlayer) {
		thePlayer->buildBySupplies(cash, buildingType);
	}
}

//-------------------------------------------------------------------------------------------------
/** doBuildObjectNearestTeam */
//-------------------------------------------------------------------------------------------------
// ?doBuildObjectNearestTeam@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doBuildObjectNearestTeam( const AsciiString& playerName, const AsciiString& buildingType, const AsciiString& teamName )
{
	Player *thePlayer = TheScriptEngine->getPlayerFromAsciiString( playerName );
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if( thePlayer && theTeam ) 
	{
		thePlayer->buildSpecificBuildingNearestTeam( buildingType, theTeam );
	}
}

//-------------------------------------------------------------------------------------------------
/** doBuildUpgrade */
//-------------------------------------------------------------------------------------------------
// ?doBuildUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doBuildUpgrade(const AsciiString& player, const AsciiString& upgrade)
{
	Player* thePlayer = TheScriptEngine->getPlayerFromAsciiString(player);
	if (thePlayer) {
		thePlayer->buildUpgrade(upgrade);
	}
}


//-------------------------------------------------------------------------------------------------
/** doBuildBaseDefense */
//-------------------------------------------------------------------------------------------------
// ?doBuildBaseDefense@ScriptActions@@IAEX_N@Z present-unmatched
void ScriptActions::doBuildBaseDefense(Bool flank)
{
	// This action ALWAYS occur on the current player.
	Player *thePlayer = TheScriptEngine->getCurrentPlayer();
	if (thePlayer) {
		thePlayer->buildBaseDefense(flank);
	}
}

//-------------------------------------------------------------------------------------------------
/** doBuildBuilding */
//-------------------------------------------------------------------------------------------------
// ?doBuildBaseStructure@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doBuildBaseStructure(const AsciiString& buildingType, Bool flank)
{
	// This action ALWAYS occur on the current player.
	Player *thePlayer = TheScriptEngine->getCurrentPlayer();
	if (thePlayer) {
		thePlayer->buildBaseDefenseStructure(buildingType, flank);
	}
}


//-------------------------------------------------------------------------------------------------
/** createUnitOnTeamAt */
//-------------------------------------------------------------------------------------------------
// ?createUnitOnTeamAt@ScriptActions@@IAEXABVAsciiString@@000@Z
// Body in ScriptActions_createUnitOnTeamAt.asm (exact 604B retail).

//-------------------------------------------------------------------------------------------------
/** updateNamedAttackPrioritySet */
//-------------------------------------------------------------------------------------------------
// ?updateNamedAttackPrioritySet@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::updateNamedAttackPrioritySet(const AsciiString& unitName, const AsciiString& attackPrioritySet)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}

	AIUpdateInterface *pInterface = theSrcUnit->getAIUpdateInterface();
	if (!pInterface) {
		return;
	}
	
	const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(attackPrioritySet);

	pInterface->setAttackInfo(info);

}

//-------------------------------------------------------------------------------------------------
/** updateTeamAttackPrioritySet */
//-------------------------------------------------------------------------------------------------
// ?updateTeamAttackPrioritySet@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::updateTeamAttackPrioritySet(const AsciiString& teamName, const AsciiString& attackPrioritySet)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(attackPrioritySet);
	
	if (info->getName().isNotEmpty()) {
		team->setAttackPriorityName(info->getName());
	}

	// Set team member's attack priority.
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		ai->setAttackInfo(info);
	}
}

//-------------------------------------------------------------------------------------------------
/** updateBaseConstructionSpeed */
//-------------------------------------------------------------------------------------------------
// ?updateBaseConstructionSpeed@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::updateBaseConstructionSpeed(const AsciiString& playerName, Int delayInSeconds)
{
	Player* thePlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (thePlayer) {
		thePlayer->setTeamDelaySeconds(delayInSeconds);
	}
}

//-------------------------------------------------------------------------------------------------
/** updateNamedSetAttitude */
//-------------------------------------------------------------------------------------------------
// ?updateNamedSetAttitude@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::updateNamedSetAttitude(const AsciiString& unitName, Int attitude)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}

	AIUpdateInterface *pInterface = theSrcUnit->getAIUpdateInterface();
	if (!pInterface) {
		return;
	}
	
	pInterface->setAttitude((AttitudeType) attitude);
}

//-------------------------------------------------------------------------------------------------
/** updateTeamSetAttitude */
//-------------------------------------------------------------------------------------------------
// ?updateTeamSetAttitude@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::updateTeamSetAttitude(const AsciiString& teamName, Int attitude)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theSrcTeam) {
		return;
	}

	AIGroup *pAIGroup = TheAI->createGroup();
	if (!pAIGroup) {
		return;
	}

	theSrcTeam->getTeamAsAIGroup(pAIGroup);
	pAIGroup->setAttitude((AttitudeType) attitude);
}

//-------------------------------------------------------------------------------------------------
/** doNamedSetRepulsor */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doNamedSetRepulsor(const AsciiString& unitName, Bool repulsor)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}
	theSrcUnit->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_REPULSOR ), repulsor);
}

//-------------------------------------------------------------------------------------------------
/** doTeamSetRepulsor */
//-------------------------------------------------------------------------------------------------
// ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamSetRepulsor(const AsciiString& teamName, Bool repulsor)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theSrcTeam) {
		return;
	}

	if (theSrcTeam) 
	{
		for (DLINK_ITERATOR<Object> iter = theSrcTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj) 
			{
				continue;
			}
			obj->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_REPULSOR ), repulsor );
		}
	}

}

//-------------------------------------------------------------------------------------------------
/** doNamedAttackArea */
//-------------------------------------------------------------------------------------------------
// ?doNamedAttackArea@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedAttackArea(const AsciiString& unitName, const AsciiString& areaName)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theSrcUnit) {
		return;
	}
	
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	if (!pTrig) {
		return;
	}


	AIUpdateInterface* aiUpdate = theSrcUnit->getAIUpdateInterface();
	if( !aiUpdate )
	{
		return;
	}
	theSrcUnit->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiAttackArea(pTrig, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doNamedAttackTeam */
//-------------------------------------------------------------------------------------------------
// ?doNamedAttackTeam@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedAttackTeam(const AsciiString& unitName, const AsciiString& teamName)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theSrcUnit) {
		return;
	}
	
	const Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIUpdateInterface* aiUpdate = theSrcUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}

	theSrcUnit->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiAttackTeam(theTeam, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamAttackArea */
//-------------------------------------------------------------------------------------------------
// ?doTeamAttackArea@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamAttackArea(const AsciiString& teamName, const AsciiString& areaName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	if (!pTrig) {
		return;
	}

	theGroup->groupAttackArea(pTrig, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamAttackNamed */
//-------------------------------------------------------------------------------------------------
// ?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
// Body in ScriptActions_doTeamAttackNamed.asm (exact 144B retail @ 0x2F95A0).
// Queue RVA 0x3992C6 was INSIDE already-matched logicMessageDispatcher (misplaced drift).


//-------------------------------------------------------------------------------------------------
/** doLoadAllTransports */
//-------------------------------------------------------------------------------------------------
// ?doLoadAllTransports@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doLoadAllTransports(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if (!theTeam) {
		return;
	}

	EntriesVec vecOfUnits;
	SpacesVec vecOfTransports;
	
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj) {
			continue;
		}

		if( obj->isKindOf(KINDOF_TRANSPORT) ) 
		{
			ContainModuleInterface *contain = obj->getContain();
			if( contain )
			{
				vecOfTransports.push_back(std::make_pair(obj->getID(), ((TransportContain*)obj->getContain())->getContainMax()));
			}
			else
			{
				DEBUG_CRASH( ("doLoadAllTransports script -- transport doesn't have a container!") );
			}
		} 
		else 
		{
			vecOfUnits.push_back(std::make_pair(obj->getID(), obj->getTransportSlotCount()));
		}
	}

	// we've now built the necessary stuff. Partition the units.

	PartitionSolver partition(vecOfUnits, vecOfTransports, PREFER_FAST_SOLUTION);
	partition.solve();
	SolutionVec solution = partition.getSolution();
	for (int i = 0; i < solution.size(); ++i) {
		Object *unit = TheGameLogic->findObjectByID(solution[i].first);
		Object *trans = TheGameLogic->findObjectByID(solution[i].second);
		if (!unit || !trans) {
			continue;
		}
		if( unit->getAIUpdateInterface() )
		{
			unit->getAIUpdateInterface()->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
			unit->getAIUpdateInterface()->aiEnter(trans, CMD_FROM_SCRIPT);
		}
	}		
}

//-------------------------------------------------------------------------------------------------
/** doNamedEnterNamed */
//-------------------------------------------------------------------------------------------------
// ?doNamedEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedEnterNamed(const AsciiString& unitSrcName, const AsciiString& unitDestName)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed( unitSrcName );
	if (!theSrcUnit) {
		return;
	}
	
	Object *theTransport = TheScriptEngine->getUnitNamed( unitDestName );
	if (!theTransport) {
		return;
	}

	AIUpdateInterface* aiUpdate = theSrcUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}
	theSrcUnit->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiEnter(theTransport, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamEnterNamed */
//-------------------------------------------------------------------------------------------------
// ?doTeamEnterNamed@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamEnterNamed(const AsciiString& teamName, const AsciiString& unitDestName)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theSrcTeam) {
		return;
	}
	
	Object *theTransport = TheScriptEngine->getUnitNamed( unitDestName );
	if (!theTransport) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	theSrcTeam->getTeamAsAIGroup(theGroup);

	theGroup->groupEnter(theTransport, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doNamedExitAll */
//-------------------------------------------------------------------------------------------------
// ?doNamedExitAll@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedExitAll(const AsciiString& unitName)
{
	Object *theTransport = TheScriptEngine->getUnitNamed( unitName );
	if (!theTransport) {
		return;
	}

	AIUpdateInterface* aiUpdate = theTransport->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}

	theTransport->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiEvacuate( FALSE, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doTeamExitAll */
//-------------------------------------------------------------------------------------------------
// ?doTeamExitAll@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamExitAll(const AsciiString& teamName)
{
	Team *theTeamOfTransports = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeamOfTransports) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	theTeamOfTransports->getTeamAsAIGroup(theGroup);

	theGroup->groupEvacuate( CMD_FROM_SCRIPT );
}


//-------------------------------------------------------------------------------------------------
/** doNamedSetGarrisonEvacDisposition */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetGarrisonEvacDisposition@ScriptActions@@IAEXABVAsciiString@@I@Z present-unmatched
void ScriptActions::doNamedSetGarrisonEvacDisposition(const AsciiString& unitName, UnsignedInt disp )
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	ContainModuleInterface *contain = theUnit->getContain();
  if( contain )
		contain->setEvacDisposition( (EvacDisposition)disp ); 
    // should be safe to cast any-old int to this enum, 
    // since only 1(EVAC_TO_LEFT) and 2(EVAC_TO_RIGHT) differ from default case

}




//-------------------------------------------------------------------------------------------------
/** doNamedFollowWaypoints */
//-------------------------------------------------------------------------------------------------
// ?doNamedFollowWaypoints@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedFollowWaypoints(const AsciiString& unitName, const AsciiString& waypointPathLabel)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}
	Coord3D pos = *theUnit->getPosition();
	AIUpdateInterface* aiUpdate = theUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
	if (!way) {
		return;
	}

	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, waypointPathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	
	theUnit->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiFollowWaypointPath(way, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doNamedFollowWaypointsExact */
//-------------------------------------------------------------------------------------------------
// ?doNamedFollowWaypointsExact@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedFollowWaypointsExact(const AsciiString& unitName, const AsciiString& waypointPathLabel)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}
	Coord3D pos = *theUnit->getPosition();
	AIUpdateInterface* aiUpdate = theUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
	if (!way) {
		return;
	}

	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, waypointPathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	
	theUnit->leaveGroup();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiFollowWaypointPathExact(way, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamFollowSkirmishApproachPath */
//-------------------------------------------------------------------------------------------------
// ?doTeamFollowSkirmishApproachPath@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doTeamFollowSkirmishApproachPath(const AsciiString& teamName, const AsciiString& waypointPathLabel, Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x=pos.y=pos.z=0;

	Object *firstUnit=NULL;
	// Get the center point for the team
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z; // Not actually used by getClosestWaypointOnPath, but hey, might as well be correct.
		count++;
		if (firstUnit==NULL) {
			firstUnit = obj;
		}
	}
	if (count==0) return; // empty team.
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemyPlayer==NULL) return;
	Int mpNdx = enemyPlayer->getMpStartIndex()+1;

	AsciiString pathLabel;
	pathLabel.format("%s%d", waypointPathLabel.str(), mpNdx);
	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, pathLabel );
	if (!way) {
		return;
	}

	Player *aiPlayer = TheScriptEngine->getCurrentPlayer();
	if (aiPlayer && firstUnit) {
		aiPlayer->checkBridges(firstUnit, way);
	}

	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, pathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	if (asTeam) 
	{
		theGroup->groupFollowWaypointPathAsTeam(way, CMD_FROM_SCRIPT);
	}	else {
		theGroup->groupFollowWaypointPath(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamFollowSkirmishApproachPath */
//-------------------------------------------------------------------------------------------------
// ?doTeamMoveToSkirmishApproachPath@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamMoveToSkirmishApproachPath(const AsciiString& teamName, const AsciiString& waypointPathLabel)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x=pos.y=pos.z=0;

	// Get the center point for the team
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z; // Not actually used by getClosestWaypointOnPath, but hey, might as well be correct.
		count++;
	}
	if (count==0) return; // empty team.
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemyPlayer==NULL) return;
	Int mpNdx = enemyPlayer->getMpStartIndex()+1;

	AsciiString pathLabel;
	pathLabel.format("%s%d", waypointPathLabel.str(), mpNdx);
	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, pathLabel );
	if (!way) {
		return;
	}
	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, pathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	theGroup->groupMoveToPosition(way->getLocation(), false, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamFollowWaypoints */
//-------------------------------------------------------------------------------------------------
// ?doTeamFollowWaypoints@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doTeamFollowWaypoints(const AsciiString& teamName, const AsciiString& waypointPathLabel, Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x=pos.y=pos.z=0;

	// Get the center point for the team
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z; // Not actually used by getClosestWaypointOnPath, but hey, might as well be correct.
		count++;
	}
	if (count==0) return; // empty team.
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
	if (!way) {
		return;
	}
	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, waypointPathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	if (asTeam) 
	{
		theGroup->groupFollowWaypointPathAsTeam(way, CMD_FROM_SCRIPT);
	}	else {
		theGroup->groupFollowWaypointPath(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamFollowWaypointsExact */
//-------------------------------------------------------------------------------------------------
// ?doTeamFollowWaypointsExact@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doTeamFollowWaypointsExact(const AsciiString& teamName, const AsciiString& waypointPathLabel, Bool asTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);
	Int count = 0;
	Coord3D pos;
	pos.x=pos.y=pos.z=0;

	// Get the center point for the team
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z; // Not actually used by getClosestWaypointOnPath, but hey, might as well be correct.
		count++;
	}
	if (count==0) return; // empty team.
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
	if (!way) {
		return;
	}
	DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, waypointPathLabel), ("***Wrong waypoint purpose. Make jba fix this.\n"));
	if (asTeam) 
	{
		theGroup->groupFollowWaypointPathAsTeamExact(way, CMD_FROM_SCRIPT);
	}	else {
		theGroup->groupFollowWaypointPathExact(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedGuard */
//-------------------------------------------------------------------------------------------------
// ?doNamedGuard@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedGuard(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	AIUpdateInterface* aiUpdate = theUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}
	
	theUnit->leaveGroup();
	Coord3D position = *theUnit->getPosition();
	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamGuard */
//-------------------------------------------------------------------------------------------------
// ?doTeamGuard@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamGuard(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	// Have all the members of the team guard at their current pos.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		Coord3D pos = *obj->getPosition();
		ai->aiGuardPosition(&pos, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamGuardPosition */
//-------------------------------------------------------------------------------------------------
// ?doTeamGuardPosition@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamGuardPosition(const AsciiString& teamName, const AsciiString& waypointName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName); 
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam || !way) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);
	Coord3D position = *way->getLocation();

	theGroup->groupGuardPosition( &position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doTeamGuardObject */
//-------------------------------------------------------------------------------------------------
// ?doTeamGuardObject@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamGuardObject(const AsciiString& teamName, const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam || !theUnit) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);

	theGroup->groupGuardObject( theUnit, GUARDMODE_NORMAL, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doTeamGuardArea */
//-------------------------------------------------------------------------------------------------
// ?doTeamGuardArea@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamGuardArea(const AsciiString& teamName, const AsciiString& areaName)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam || !pTrig) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);

	theGroup->groupGuardArea( pTrig, GUARDMODE_NORMAL, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doNamedHunt */
//-------------------------------------------------------------------------------------------------
// ?doNamedHunt@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedHunt(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	AIUpdateInterface* aiUpdate = theUnit->getAIUpdateInterface();
	if (!aiUpdate) {
		return;
	}

	aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	aiUpdate->aiHunt( CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doTeamHunt */
//-------------------------------------------------------------------------------------------------
// ?doTeamHunt@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamHunt(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	theTeam->getTeamAsAIGroup(theGroup);

	theGroup->groupHunt( CMD_FROM_SCRIPT );
}
//-------------------------------------------------------------------------------------------------
/** doTeamHunt */
//-------------------------------------------------------------------------------------------------
// ?doTeamHuntWithCommandButton@ScriptActions@@ present-unmatched
void ScriptActions::doTeamHuntWithCommandButton(const AsciiString& teamName, const AsciiString& ability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}


	const CommandButton *commandButton = TheControlBar->findCommandButton( ability );
	if( !commandButton )
	{
		return;
	}

		switch( commandButton->getCommandType() )
		{

			case GUI_COMMAND_SPECIAL_POWER:
				if( commandButton->getSpecialPowerTemplate() )
				{
					if (BitTest( commandButton->getOptions(), COMMAND_OPTION_NEED_OBJECT_TARGET )) 
					{
						// OK, we can hunt with a power that targets an object.
						break;
					}
					AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
					msg.concat(ability);
					TheScriptEngine->AppendDebugMessage(msg, false);
					return;
				}
				return;
			case GUI_COMMAND_SWITCH_WEAPON:
			case GUI_COMMAND_FIRE_WEAPON:
				{
					// ok, we can hunt with a weapon.
					break;
				}
			
			case GUICOMMANDMODE_HIJACK_VEHICLE:
			case GUICOMMANDMODE_CONVERT_TO_CARBOMB:
			case GUICOMMANDMODE_SABOTAGE_BUILDING:
				//Various enter type hunts.
				break;

			case GUI_COMMAND_OBJECT_UPGRADE:
			case GUI_COMMAND_PLAYER_UPGRADE:
			case GUI_COMMAND_DOZER_CONSTRUCT:
			case GUI_COMMAND_DOZER_CONSTRUCT_CANCEL:
			case GUI_COMMAND_UNIT_BUILD:
			case GUI_COMMAND_CANCEL_UNIT_BUILD:
			case GUI_COMMAND_CANCEL_UPGRADE:
			case GUI_COMMAND_ATTACK_MOVE:
			case GUI_COMMAND_GUARD:
			case GUI_COMMAND_GUARD_WITHOUT_PURSUIT:
			case GUI_COMMAND_GUARD_FLYING_UNITS_ONLY:
			case GUI_COMMAND_WAYPOINTS:
			case GUI_COMMAND_EXIT_CONTAINER:
			case GUI_COMMAND_EVACUATE:
			case GUI_COMMAND_EXECUTE_RAILED_TRANSPORT:
			case GUI_COMMAND_BEACON_DELETE:
			case GUI_COMMAND_SET_RALLY_POINT:
			case GUI_COMMAND_SELL:
			case GUI_COMMAND_HACK_INTERNET:
			case GUI_COMMAND_TOGGLE_OVERCHARGE:
#ifdef ALLOW_SURRENDER
			case GUI_COMMAND_POW_RETURN_TO_PRISON:
#endif
#ifdef ALLOW_SURRENDER
			case GUICOMMANDMODE_PICK_UP_PRISONER:
#endif
			default:
				{
					AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
					msg.concat(ability);
					TheScriptEngine->AppendDebugMessage(msg, false);
					return;
				}
				break;
		}


	// Have all the members of the team do the command button.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		Bool foundCommand = false;
		const CommandSet *commandSet = TheControlBar->findCommandSet( obj->getCommandSetString( ) );
		if( commandSet )
		{
			for( int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
			{
				const CommandButton *aCommandButton = commandSet->getCommandButton(i);
				if( commandButton == aCommandButton )
				{
					//We found the matching command button so now order the unit to do what the button wants.
					foundCommand = true;
					break;
				}
			}
		}
		if (!foundCommand) {
			AsciiString msg = "Error - Team hunt with command button - unit type '";
			msg.concat(obj->getTemplate()->getName().str());
			msg.concat("' is not valid for ability ");
			msg.concat(ability);
			TheScriptEngine->AppendDebugMessage(msg, false);
			continue;

		}

		switch( commandButton->getCommandType() )
		{

			case GUI_COMMAND_FIRE_WEAPON:
			case GUI_COMMAND_SWITCH_WEAPON:
			case GUI_COMMAND_SPECIAL_POWER:
			case GUICOMMANDMODE_HIJACK_VEHICLE:
			case GUICOMMANDMODE_CONVERT_TO_CARBOMB:
			case GUICOMMANDMODE_SABOTAGE_BUILDING:
			{
					static NameKeyType key_CommandButtonHuntUpdate = NAMEKEY("CommandButtonHuntUpdate");

					CommandButtonHuntUpdate* huntUpdate = (CommandButtonHuntUpdate*)obj->findUpdateModule(key_CommandButtonHuntUpdate);
					if( huntUpdate  )
					{
						huntUpdate->setCommandButton(ability);
					} else {
						AsciiString msg = "Error - Team hunt with command button - unit type '";
						msg.concat(obj->getTemplate()->getName().str());
						msg.concat("' requires CommandButtonHuntUpdate in .ini definition to hunt with ");
						msg.concat(ability);
						TheScriptEngine->AppendDebugMessage(msg, false);
					}  // end if
				}
				break;
				
		}
			
	}

}
								
//-------------------------------------------------------------------------------------------------
/** doTeamHunt */
//-------------------------------------------------------------------------------------------------
// ?doPlayerHunt@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerHunt(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->setUnitsShouldHunt(true, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerSellEverything */
//-------------------------------------------------------------------------------------------------
// ?doPlayerSellEverything@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerSellEverything(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->sellEverythingUnderTheSun();
}

//-------------------------------------------------------------------------------------------------
/** doPlayerDisableBaseConstruction */
//-------------------------------------------------------------------------------------------------
// ?doPlayerDisableBaseConstruction@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerDisableBaseConstruction(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->setCanBuildBase(false);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerDisableFactories */
//-------------------------------------------------------------------------------------------------
// ?doPlayerDisableFactories@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doPlayerDisableFactories(const AsciiString& playerName, const AsciiString& objectName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->setObjectsEnabled(objectName, false);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerDisableUnitConstruction */
//-------------------------------------------------------------------------------------------------
// ?doPlayerDisableUnitConstruction@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerDisableUnitConstruction(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
 
	if (!pPlayer) {
		return;
	}
	pPlayer->setCanBuildUnits(false);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerEnableBaseConstruction */
//-------------------------------------------------------------------------------------------------
// ?doPlayerEnableBaseConstruction@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerEnableBaseConstruction(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}

	pPlayer->setCanBuildBase(true);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerEnableFactories */
//-------------------------------------------------------------------------------------------------
// ?doPlayerEnableFactories@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doPlayerEnableFactories(const AsciiString& playerName, const AsciiString& objectName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->setObjectsEnabled(objectName, true);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerRepairStructure */
//-------------------------------------------------------------------------------------------------
// ?doPlayerRepairStructure@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doPlayerRepairStructure(const AsciiString& playerName, const AsciiString& structureName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	Object *pStructure = TheScriptEngine->getUnitNamed(structureName);

	if (!pStructure) {
		return;
	}
	pPlayer->repairStructure(pStructure->getID());
}

//-------------------------------------------------------------------------------------------------
/** doPlayerEnableUnitConstruction */
//-------------------------------------------------------------------------------------------------
// ?doPlayerEnableUnitConstruction@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerEnableUnitConstruction(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}

	pPlayer->setCanBuildUnits(true);
}

//-------------------------------------------------------------------------------------------------
/** doCameraMoveHome */
//-------------------------------------------------------------------------------------------------
// ?doCameraMoveHome@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doCameraMoveHome(void)
{

}

//-------------------------------------------------------------------------------------------------
/** doBuildTeam */
//-------------------------------------------------------------------------------------------------
// ?doBuildTeam@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doBuildTeam(const AsciiString& teamName)
{
	TeamPrototype *theTeamProto = TheTeamFactory->findTeamPrototype( teamName );
	if (theTeamProto) {
		Player *player = theTeamProto->getControllingPlayer();
		if (player) {
			player->buildSpecificTeam(theTeamProto);
		}
	}	
}

//-------------------------------------------------------------------------------------------------
/** doRecruitTeam */
//-------------------------------------------------------------------------------------------------
// ?doRecruitTeam@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doRecruitTeam(const AsciiString& teamName, Real recruitRadius)
{
	TeamPrototype *theTeamProto = TheTeamFactory->findTeamPrototype( teamName );
	if (theTeamProto) {
		Player *player = theTeamProto->getControllingPlayer();
		if (player) {
			player->recruitSpecificTeam(theTeamProto, recruitRadius);
		}
	}	
}

//-------------------------------------------------------------------------------------------------
/** doNamedDamage */
//-------------------------------------------------------------------------------------------------
// ?doNamedDamage@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doNamedDamage(const AsciiString& unitName, Int damageAmt)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(unitName);

	if (!pUnit) {
		return;
	}
	DamageInfo damageInfo;
	damageInfo.in.m_damageType = DAMAGE_UNRESISTABLE;
	damageInfo.in.m_deathType = DEATH_NORMAL;
	damageInfo.in.m_sourceID = INVALID_ID;
	damageInfo.in.m_amount = damageAmt;
	pUnit->attemptDamage( &damageInfo );
}

//-------------------------------------------------------------------------------------------------
/** doNamedDelete */
//-------------------------------------------------------------------------------------------------
// ?doNamedDelete@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedDelete(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	TheGameLogic->destroyObject(theUnit);
}

//-------------------------------------------------------------------------------------------------
/** doTeamDelete */
//-------------------------------------------------------------------------------------------------
// ?doTeamDelete@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamDelete(const AsciiString& teamName, Bool ignoreDead)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	team->deleteTeam(ignoreDead);
}

//-------------------------------------------------------------------------------------------------
/** doTeamWander */
//-------------------------------------------------------------------------------------------------
// ?doTeamWander@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamWander(const AsciiString& teamName, const AsciiString& waypointPathLabel)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	// Have all the members of the team wander.
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		Coord3D pos = *obj->getPosition();
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
		if (!way) {
			return;
		}
		ai->chooseLocomotorSet(LOCOMOTORSET_WANDER);
		ai->aiWander(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamIncreasePriority */
//-------------------------------------------------------------------------------------------------
// ?doTeamIncreasePriority@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamIncreasePriority(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}
	const TeamPrototype *theTeamProto = team->getPrototype();

	if (!theTeamProto) {
		return;
	}
	theTeamProto->increaseAIPriorityForSuccess();
	AsciiString msg;
	msg.format("Team '%s' priority increased to %d for success.", teamName.str(), theTeamProto->getTemplateInfo()->m_productionPriority);
	TheScriptEngine->AppendDebugMessage(msg, false);

}

//-------------------------------------------------------------------------------------------------
/** doTeamDecreasePriority */
//-------------------------------------------------------------------------------------------------
// ?doTeamDecreasePriority@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamDecreasePriority(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}
	const TeamPrototype *theTeamProto = team->getPrototype();

	if (!theTeamProto) {
		return;
	}
	theTeamProto->decreaseAIPriorityForFailure();
	AsciiString msg;
	msg.format("Team '%s' priority decreased to %d for failure.", teamName.str(), theTeamProto->getTemplateInfo()->m_productionPriority);
	TheScriptEngine->AppendDebugMessage(msg, false);

}

//-------------------------------------------------------------------------------------------------
/** doTeamWanderInPlace */
//-------------------------------------------------------------------------------------------------
// ?doTeamWanderInPlace@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamWanderInPlace(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	// Have all the members of the team wander.
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		ai->chooseLocomotorSet(LOCOMOTORSET_WANDER);
		ai->aiWanderInPlace(CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamPanic */
//-------------------------------------------------------------------------------------------------
// ?doTeamPanic@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamPanic(const AsciiString& teamName, const AsciiString& waypointPathLabel)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	// Get the center point for the team
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		Coord3D pos = *obj->getPosition();
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPathLabel );
		if (!way) {
			return;
		}
		ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
		ai->aiPanic(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedKill */
//-------------------------------------------------------------------------------------------------
// ?doNamedKill@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedKill(const AsciiString& unitName)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(unitName);

	if (!pUnit) {
		return;
	}
	pUnit->kill();
}

//-------------------------------------------------------------------------------------------------
/** doTeamKill */
//-------------------------------------------------------------------------------------------------
// ?doTeamKill@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamKill(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);

	if (!team) {
		return;
	}

	team->killTeam();
}

//-------------------------------------------------------------------------------------------------
/** doPlayerKill */
//-------------------------------------------------------------------------------------------------
// ?doPlayerKill@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerKill(const AsciiString& playerName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!pPlayer) {
		return;
	}
	pPlayer->killPlayer();
}

//-------------------------------------------------------------------------------------------------
/** doDisplayText */
//-------------------------------------------------------------------------------------------------
// ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doDisplayText(const AsciiString& displayText)
{
	TheInGameUI->message(displayText);	
}

//-------------------------------------------------------------------------------------------------
/** doInGamePopupMessage */
//-------------------------------------------------------------------------------------------------
// ?doInGamePopupMessage@ScriptActions@@IAEXABVAsciiString@@HHH_N@Z present-unmatched
void ScriptActions::doInGamePopupMessage( const AsciiString& message, Int x, Int y, Int width, Bool pause )
{
	TheInGameUI->popupMessage(message, x,y,width, pause, FALSE);
}

//-------------------------------------------------------------------------------------------------
/** doDisplayCinematicText */
//-------------------------------------------------------------------------------------------------
// ?doDisplayCinematicText@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doDisplayCinematicText(const AsciiString& displayText, const AsciiString& fontType, Int timeInSeconds)
{
	// set the text
	UnicodeString uStr = TheGameText->fetch( displayText );
	AsciiString aStr;
	aStr.translate( uStr );
	TheDisplay->setCinematicText( aStr );

	// Gets the font info from parsing through fontType

	// get the font name
	AsciiString fontName = AsciiString::TheEmptyString;
	char buf[256];
	char *c;
	strcpy(buf, fontType.str());
	for( c = buf; c != '\0'; *c++ )
	{
		if( *c != ' ' && *c++ != '-' ) 
			fontName.concat(c);
		else
			break;
	}
	while( *c != ':' )
		*c++;
	*c++;  // eat through " - Size:"

	// get font size
	AsciiString fontSize = AsciiString::TheEmptyString;
	for( ; *c != '\0'; *c++ )
	{
		if( *c != '\0' && *c != ' ' )
		{
			fontSize.concat( *c );
		}
		else
		{
			break;
		}
	}
	Int size = atoi( fontSize.str() );

	// get font fold
	Bool bold = FALSE;
	if( fontType.endsWith( "[Bold]" ) )
		bold = TRUE;

	// phew, now set as new font
	GameFont *font = TheFontLibrary->getFont( fontName, 
		TheGlobalLanguageData->adjustFontSize(size), bold );
	TheDisplay->setCinematicFont( font );

	// set time
	Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;
	TheDisplay->setCinematicTextFrames( frames );
}
//-------------------------------------------------------------------------------------------------
/** doCameoFlash */
//-------------------------------------------------------------------------------------------------
// ?doCameoFlash@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doCameoFlash(const AsciiString& name, Int timeInSeconds)
{
	const CommandButton *button;

	//sanity
	button = TheControlBar->findCommandButton( name );
	if( button == NULL )
	{
		DEBUG_CRASH(( "ScriptActions::doCameoFlash can't find AsciiString cameoflash" ));
	}

	Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;
	// every time the framecount % 20 == 0,  controlbar:: update will do Cameo Flash
	Int count = frames / DRAWABLE_FRAMES_PER_FLASH;
	// make sure count is even, so the cameo will return to its original state
	if( count % 2 == 1 )
		count++;

	button->setFlashCount(count);
	TheControlBar->setFlash( TRUE );

}

//-------------------------------------------------------------------------------------------------
/** doNamedCustomColor */
//-------------------------------------------------------------------------------------------------
// ?doNamedCustomColor@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doNamedCustomColor(const AsciiString& unitName, Color c)
{
	//sanity
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if ( !obj )
	{
		return;
	}
	obj->setCustomIndicatorColor(c);
}

//-------------------------------------------------------------------------------------------------
/** doNamedFlash */
//-------------------------------------------------------------------------------------------------
// ?doNamedFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z present-unmatched
void ScriptActions::doNamedFlash(const AsciiString& unitName, Int timeInSeconds, const RGBColor *color)
{
	/** This is called the first time this unit is told by the script to flash. timeInSeconds will tell the drawable 
	how long to flash for.  Sets drawable to start flashing but only allows drawable's update to
	call the actual flash method */

	//sanity
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if ( !obj )
	{
		return;
	}
	Drawable *drawable = obj->getDrawable();
	if( !drawable )
	{
		return;
	}

	if( timeInSeconds > 0 )
	{
		// set count for drawable, but do not flash, allow drawable update to handle it

		/* The designer specifies how long he wants the unit to flash for.  We will
		convert this number into a count of how many times to call the doNamedFlash method */
		Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;
		// every time the framecount % 20 == 0, drawable::update will call doNamedFlash
		Int count = frames / DRAWABLE_FRAMES_PER_FLASH;
		Color flashy = (color == NULL) ? obj->getIndicatorColor() : color->getAsInt();
		drawable->setFlashColor( flashy );
		drawable->setFlashCount( count );
		return;
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamFlash */
//-------------------------------------------------------------------------------------------------
// ?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z present-unmatched
void ScriptActions::doTeamFlash(const AsciiString& teamName, Int timeInSeconds, const RGBColor *color)
{
	Team *team = TheScriptEngine->getTeamNamed( teamName );
	if (team == NULL || !team->hasAnyObjects())
		return;

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();

	while( !iter.done() ) {
		Object *nextObj = iter.cur();
		Object *obj = nextObj;
		if (!obj) {
			break;
		}

		iter.advance();
		Drawable *draw = obj->getDrawable();
		if( !draw )
			break;
		Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;

		Int count = frames / DRAWABLE_FRAMES_PER_FLASH;
		Color flashy = (color == NULL) ? obj->getIndicatorColor() : color->getAsInt();
		draw->setFlashColor( flashy );
		draw->setFlashCount( count );
	}

}

#define ARBITRARY_BUFFER_SIZE	128
//-------------------------------------------------------------------------------------------------
/** doMoviePlayFullScreen */
//-------------------------------------------------------------------------------------------------
// ?doMoviePlayFullScreen@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doMoviePlayFullScreen(const AsciiString& movieName)
{
	TheDisplay->playMovie(movieName);
}

//-------------------------------------------------------------------------------------------------
/** doMoviePlayRadar */
//-------------------------------------------------------------------------------------------------
// ?doMoviePlayRadar@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doMoviePlayRadar(const AsciiString& movieName)
{
	TheInGameUI->playMovie(movieName);
}

//-------------------------------------------------------------------------------------------------
/** doSoundPlayFromNamed */
//-------------------------------------------------------------------------------------------------
// ?doSoundPlayFromNamed@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doSoundPlayFromNamed(const AsciiString& soundName, const AsciiString& unitName)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(unitName);

	if (!pUnit) {
		return;
	}
	
	AudioEventRTS sfx(soundName, pUnit->getID());
	sfx.setIsLogicalAudio(true);
	TheAudio->addAudioEvent(&sfx);
}

//-------------------------------------------------------------------------------------------------
/** doSpeechPlay */
//-------------------------------------------------------------------------------------------------
enum
{
	SUBTITLE_DURATION = 8000
};
// ?doSpeechPlay@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doSpeechPlay(const AsciiString& speechName, Bool allowOverlap)
{	
	AudioEventRTS speech(speechName);
	speech.setIsLogicalAudio(true);
	speech.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	speech.setUninterruptable(!allowOverlap);
	TheAudio->addAudioEvent(&speech);
	
	
	AsciiString subtitleLabel("DIALOGEVENT:");
	subtitleLabel.concat(speechName);
	subtitleLabel.concat("Subtitle");
	
	// Found is important, because a failure will return a valid "Missing: 'Label'" string.
	Bool found = FALSE;
	UnicodeString subtitle = TheGameText->fetch(subtitleLabel, &found);
	if( found && !subtitle.isEmpty() && subtitle.getCharAt(0) != '*')
	{
		// Foreign versions can specify region specifc subtitle strings if they want.
		// English will have strings with / for easy translation, but they don't want to display.
		TheInGameUI->militarySubtitle( subtitleLabel, SUBTITLE_DURATION );
	}
}

//-------------------------------------------------------------------------------------------------
/** doPlayerTransferAssetsToPlayer */
//-------------------------------------------------------------------------------------------------
// ?doPlayerTransferAssetsToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doPlayerTransferAssetsToPlayer(const AsciiString& playerSrcName, const AsciiString& playerDstName)
{
	Player *pPlayerDest = TheScriptEngine->getPlayerFromAsciiString(playerDstName);
	Player *pPlayerSrc = TheScriptEngine->getPlayerFromAsciiString(playerSrcName);

	if (!pPlayerDest || !pPlayerSrc) {
		return;
	}
	
	pPlayerDest->transferAssetsFromThat(pPlayerSrc);
}

//-------------------------------------------------------------------------------------------------
/** doNamedTransferAssetsToPlayer */
//-------------------------------------------------------------------------------------------------
// ?doNamedTransferAssetsToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedTransferAssetsToPlayer(const AsciiString& unitName, const AsciiString& playerDstName)
{
	Object *pObj = TheScriptEngine->getUnitNamed(unitName);
	Player *pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerDstName);

	if (!pObj || !pPlayer) {
		return;
	}

	Team *playerTeam = pPlayer->getDefaultTeam();
	if (!playerTeam) {
		return;
	}

	pObj->setTeam(playerTeam);
	updateTeamAndPlayerStuff(pObj, NULL);
}

//-------------------------------------------------------------------------------------------------
/** excludePlayerFromScoreScreen */
//-------------------------------------------------------------------------------------------------
// ?excludePlayerFromScoreScreen@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::excludePlayerFromScoreScreen(const AsciiString& playerName)
{
	Player *pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (pPlayer == NULL) {
		return;
	}

	pPlayer->setListInScoreScreen(FALSE);
}

//-------------------------------------------------------------------------------------------------
/** excludePlayerFromScoreScreen */
//-------------------------------------------------------------------------------------------------
// BFME GameLogic script overrides (ZH packs these earlier in the object).
struct BfmeGameLogicScriptFields {
	UnsignedByte _pad[0x90];
	Bool m_isScoringEnabled;          // +0x90
	Bool m_showBehindBuildingMarkers; // +0x91
	Bool m_drawIconUI;                // +0x92
	Bool m_showDynamicLOD;            // +0x93
	Bool m_unknown94;                 // +0x94
	Bool m_unknown95;                 // +0x95
	Bool m_evaEnabled;                // +0x96 (ScriptActions::doEvaEnabledDisabled)
	Bool m_unknown97;                 // +0x97
	Int m_scriptHulkMaxLifetimeOverride; // +0x98
};

// ?enableScoring@ScriptActions@@IAEX_N@Z
void ScriptActions::enableScoring(Bool score)
{
	((BfmeGameLogicScriptFields *)TheGameLogic)->m_isScoringEnabled = score;
}

//-------------------------------------------------------------------------------------------------
/** updatePlayerRelationTowardPlayer */
//-------------------------------------------------------------------------------------------------
// ?updatePlayerRelationTowardPlayer@ScriptActions@@IAEXABVAsciiString@@H0@Z present-unmatched
void ScriptActions::updatePlayerRelationTowardPlayer(const AsciiString& playerSrcName, Int relationType, const AsciiString& playerDstName)
{
	Player *pPlayerDest = TheScriptEngine->getPlayerFromAsciiString(playerDstName);
	Player *pPlayerSrc = TheScriptEngine->getPlayerFromAsciiString(playerSrcName);

	if (!pPlayerDest || !pPlayerSrc) {
		return;
	}

	pPlayerSrc->setPlayerRelationship(pPlayerDest, (Relationship) relationType);
}

//-------------------------------------------------------------------------------------------------
/** doRadarCreateEvent */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doRadarCreateEvent(Coord3D *pos, Int eventType)
{
	TheRadar->createEvent(pos, (RadarEventType)eventType);
}

//-------------------------------------------------------------------------------------------------
/** doObjectRadarCreateEvent */
//-------------------------------------------------------------------------------------------------
// ?doObjectRadarCreateEvent@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doObjectRadarCreateEvent(const AsciiString& unitName, Int eventType)
{
	// get the building
	Object *theBuilding = TheScriptEngine->getUnitNamed( unitName );
	if (!theBuilding)
		return;
	
	// get building's position
	const Coord3D *pos = theBuilding->getPosition();
	if (!pos)
		return;
	
	// create event
	TheRadar->createEvent(pos, (RadarEventType)eventType);
}

//-------------------------------------------------------------------------------------------------
/** doTeamRadarCreateEvent */
//-------------------------------------------------------------------------------------------------
// ?doTeamRadarCreateEvent@ScriptActions@@IAEXABVAsciiString@@H@Z
// Body in ScriptActions_doTeamRadarCreateEvent.asm (exact 96B retail @ 0x2F4140;
// getTeamNamed by-value + Team::getEstimateTeamPosition(Coord3D*) out-param).

//-------------------------------------------------------------------------------------------------
/** doRadarDisable */
//-------------------------------------------------------------------------------------------------
// BFME Radar::hide/forceOn both store at +0x0d (ZH packs the hidden flag one byte earlier).
struct BfmeRadarHideField {
	UnsignedByte _pad[0x0d];
	Bool m_radarHidden;
};

// ?doRadarDisable@ScriptActions@@IAEXXZ
void ScriptActions::doRadarDisable(void)
{
	((BfmeRadarHideField *)TheRadar)->m_radarHidden = true;
}

//-------------------------------------------------------------------------------------------------
/** doRadarEnable */
//-------------------------------------------------------------------------------------------------
// ?doRadarEnable@ScriptActions@@IAEXXZ
void ScriptActions::doRadarEnable(void)
{
	((BfmeRadarHideField *)TheRadar)->m_radarHidden = false;
}

//-------------------------------------------------------------------------------------------------
/** doCameraMotionBlurJump - zoom in at the current location, jump to waypoint, and zoom out.*/
//-------------------------------------------------------------------------------------------------
// ?doCameraMotionBlurJump@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doCameraMotionBlurJump(const AsciiString& waypointName, Bool saturate)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way) {
		return;
	}

	Bool passed = FALSE;	//assume all filters were applied correctly.
	Coord3D pos = *way->getLocation();
	if (TheTacticalView->setViewFilter(FT_VIEW_MOTION_BLUR_FILTER))
	{
		passed = TRUE;
		if (saturate) {
			if (!TheTacticalView->setViewFilterMode(FM_VIEW_MB_IN_AND_OUT_SATURATE))
			{	//failed to set filter so restore default state
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				passed = FALSE;
			}
		} else {
			if (!TheTacticalView->setViewFilterMode(FM_VIEW_MB_IN_AND_OUT_ALPHA))
			{	//failed to set filter so restore default state
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				passed = FALSE;
			};
		}
		if (passed)
			TheTacticalView->setViewFilterPos(&pos);
	}
	if (!passed)
	{	//if we failed to apply the filter, we still need to get the camera to the target
		//so do it another way:
		TheTacticalView->lookAt(&pos);
	}
}

//-------------------------------------------------------------------------------------------------
/** doCameraMotionBlurJump - zoom in at the current location, jump to waypoint, and zoom out.*/
//-------------------------------------------------------------------------------------------------
// ?doCameraMotionBlur@ScriptActions@@IAEX_N0@Z present-unmatched
void ScriptActions::doCameraMotionBlur(Bool zoomIn, Bool saturate)
{
	if (TheTacticalView->setViewFilter(FT_VIEW_MOTION_BLUR_FILTER))
	{
		enum FilterModes mode;
		if (saturate) {
			if (zoomIn) {
				mode = FM_VIEW_MB_IN_SATURATE;
			} else {
				mode = FM_VIEW_MB_OUT_SATURATE;
			}
		} else {
			if (zoomIn) {
				mode = FM_VIEW_MB_IN_ALPHA;
			} else {
				mode = FM_VIEW_MB_OUT_ALPHA;
			}
		}
		if (!TheTacticalView->setViewFilterMode(mode))
		{	//failed to set the filter so restore everything to normal
			TheTacticalView->setViewFilter(FT_NULL_FILTER);
		}
	}
}

static PlayerMaskType getHumanPlayerMask( void )
{
	PlayerMaskType mask;
	for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
	{
		const Player *player = ThePlayerList->getNthPlayer(i);
		if (player->getPlayerType() == PLAYER_HUMAN)
			mask &= player->getPlayerMask();
	}

	//DEBUG_LOG(("getHumanPlayerMask(): mask was %4.4X\n", mask));
	return mask;
}

//-------------------------------------------------------------------------------------------------
/** doRevealMapAtWaypoint */
//-------------------------------------------------------------------------------------------------
// ?doRevealMapAtWaypoint@ScriptActions@@IAEXABVAsciiString@@M0@Z present-unmatched
void ScriptActions::doRevealMapAtWaypoint(const AsciiString& waypointName, Real radiusToReveal, const AsciiString& playerName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way) {
		return;
	}

	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	PlayerMaskType playerMask;
	if (player && playerName.isNotEmpty())
		playerMask = player->getPlayerMask();
	else
		playerMask = getHumanPlayerMask();

	Real positionX = way->getLocation()->x;
	Real positionY = way->getLocation()->y;

	// A reveal script is a quick look.  That way a Radar Jammer will still function correctly.
	ThePartitionManager->doShroudReveal(positionX, positionY, radiusToReveal, playerMask);
	ThePartitionManager->undoShroudReveal(positionX, positionY, radiusToReveal, playerMask);
}

//-------------------------------------------------------------------------------------------------
/** doRevealMapAtWaypoint */
//-------------------------------------------------------------------------------------------------
// ?doShroudMapAtWaypoint@ScriptActions@@IAEXABVAsciiString@@M0@Z present-unmatched
void ScriptActions::doShroudMapAtWaypoint(const AsciiString& waypointName, Real radiusToShroud, const AsciiString& playerName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way) {
		return;
	}

	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	PlayerMaskType playerMask;
	if (player && playerName.isNotEmpty())
		playerMask = player->getPlayerMask();
	else
		playerMask = getHumanPlayerMask();

	Real positionX = way->getLocation()->x;
	Real positionY = way->getLocation()->y;

	// Likewise, this script does a dollop of shroud.  Not permanent active shroud
	ThePartitionManager->doShroudCover(positionX, positionY, radiusToShroud, playerMask);
	ThePartitionManager->undoShroudCover(positionX, positionY, radiusToShroud, playerMask);
}

//-------------------------------------------------------------------------------------------------
/** doRevealMapEntire */
//-------------------------------------------------------------------------------------------------
// ?doRevealMapEntire@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doRevealMapEntire(const AsciiString& playerName)
{
	DEBUG_LOG(("ScriptActions::doRevealMapEntire() for player named '%s'\n", playerName.str()));
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (player && playerName.isNotEmpty())
	{
		DEBUG_LOG(("ScriptActions::doRevealMapEntire() for player named '%ls' in position %d\n", player->getPlayerDisplayName().str(), player->getPlayerIndex()));
		ThePartitionManager->revealMapForPlayer( player->getPlayerIndex() );
	}
	else
	{
		DEBUG_LOG(("ScriptActions::doRevealMapEntire() - no player, so doing all human players\n"));
		for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
			{
				DEBUG_LOG(("ScriptActions::doRevealMapEntire() for player %d\n", i));
				ThePartitionManager->revealMapForPlayer( i );
			}
		}
	}
}

// ?doRevealMapEntirePermanently@ScriptActions@@IAEX_NABVAsciiString@@@Z present-unmatched
void ScriptActions::doRevealMapEntirePermanently( Bool reveal, const AsciiString& playerName )
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (player && playerName.isNotEmpty())
	{
		if( reveal )
			ThePartitionManager->revealMapForPlayerPermanently( player->getPlayerIndex() );
		else
			ThePartitionManager->undoRevealMapForPlayerPermanently( player->getPlayerIndex() );
	}
	else
	{
		for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
			{
				DEBUG_LOG(("ScriptActions::doRevealMapEntirePermanently() for player %d\n", i));
				if( reveal )
					ThePartitionManager->revealMapForPlayerPermanently( i );
				else
					ThePartitionManager->undoRevealMapForPlayerPermanently( i );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doShroudMapEntire */
//-------------------------------------------------------------------------------------------------
// ?doShroudMapEntire@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doShroudMapEntire(const AsciiString& playerName)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (player && playerName.isNotEmpty())
	{
		ThePartitionManager->shroudMapForPlayer( player->getPlayerIndex() );
	}
	else
	{
		for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
			{
				DEBUG_LOG(("ScriptActions::doShroudMapEntire() for player %d\n", i));
				ThePartitionManager->shroudMapForPlayer( i );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamAvailableForRecruitment */
//-------------------------------------------------------------------------------------------------
// ?doTeamAvailableForRecruitment@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamAvailableForRecruitment(const AsciiString& teamName, Bool availability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theTeam) {
		return;
	}

	theTeam->setRecruitable(availability);
}

//-------------------------------------------------------------------------------------------------
/** doCollectNearbyForTeam */
//-------------------------------------------------------------------------------------------------
// ?doCollectNearbyForTeam@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doCollectNearbyForTeam(const AsciiString& teamName)
{
	DEBUG_CRASH(("You would think this has been implemented, but you'd be wrong. (doCollectNearbyForTeam)"));
}

//-------------------------------------------------------------------------------------------------
/** doMergeTeamIntoTeam */
//-------------------------------------------------------------------------------------------------
// ?doMergeTeamIntoTeam@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doMergeTeamIntoTeam(const AsciiString& teamSrcName, const AsciiString& teamDestName)
{
	Team *teamSrc = TheScriptEngine->getTeamNamed(teamSrcName);
	Team *teamDest = TheScriptEngine->getTeamNamed(teamDestName);
	if (teamDest==NULL) {
		teamDest = TheTeamFactory->findTeam( teamDestName );
	}
	if (!teamSrc || !teamDest) {
		return;
	}

//	Bool done = FALSE;
	
	DLINK_ITERATOR<Object> iter = teamSrc->iterate_TeamMemberList();
	Object *nextObj = iter.cur();

	while (!iter.done()) {
		Object *obj = nextObj;
		if (!obj) {
			break;
		}

		// this has to be done here, setting the team will screw up the iterator. total bummer dude. jkmcd
		nextObj = iter.cur();
		iter.advance();
		obj->setTeam(teamDest);
		updateTeamAndPlayerStuff(obj, NULL);
	}

	if (nextObj) {
		nextObj->setTeam(teamDest);
		updateTeamAndPlayerStuff(nextObj, NULL);
	}

	teamSrc->deleteTeam();
	teamDest->setActive(); // in case we just created him.
}

//-------------------------------------------------------------------------------------------------
/** doDisableInput */
//-------------------------------------------------------------------------------------------------
// ?doDisableInput@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doDisableInput()
{
#if defined(_DEBUG) || defined(_INTERNAL)
	if (!TheGlobalData->m_disableScriptedInputDisabling)
#endif
	{
		TheInGameUI->setInputEnabled(false);
		TheMouse->setVisibility(false);
		TheInGameUI->deselectAllDrawables();
		TheInGameUI->clearAttackMoveToMode();
		TheInGameUI->setWaypointMode( FALSE );
		TheControlBar->deleteBuildTooltipLayout();
		TheLookAtTranslator->resetModes();
	}
}

//-------------------------------------------------------------------------------------------------
/** doEnableInput */
//-------------------------------------------------------------------------------------------------
// BFME: non-virtual calls into setInputEnabled / Mouse::setVisibility ILT thunks.
class BfmeInGameUI_setInputEnabled {
public:
	void setInputEnabled(Bool enable);
};
class BfmeMouse_setVisibility {
public:
	void setVisibility(Bool visible);
};

void ScriptActions::doEnableInput()
{
	((BfmeInGameUI_setInputEnabled *)TheInGameUI)->setInputEnabled(true);
	((BfmeMouse_setVisibility *)TheMouse)->setVisibility(true);
}

//-------------------------------------------------------------------------------------------------
/** doSetBorderShroud */
//-------------------------------------------------------------------------------------------------
// ?doSetBorderShroud@ScriptActions@@IAEX_N@Z present-unmatched
void ScriptActions::doSetBorderShroud( Bool setting )
{
	if( setting )
		TheDisplay->setBorderShroudLevel(TheGlobalData->m_shroudAlpha);
	else
		TheDisplay->setBorderShroudLevel(TheGlobalData->m_clearAlpha);
}

//-------------------------------------------------------------------------------------------------
/** doIdleAllPlayerUnits */
//-------------------------------------------------------------------------------------------------
// ?doIdleAllPlayerUnits@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doIdleAllPlayerUnits(const AsciiString& playerName)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (player && playerName.isNotEmpty())
	{
		player->setUnitsShouldIdleOrResume(true);
	}
	else
	{
		for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
			{
				DEBUG_LOG(("ScriptActions::doIdleAllPlayerUnits() for player %d\n", i));
				player->setUnitsShouldIdleOrResume(true);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doResumeSupplyTruckingForIdleUnits */
//-------------------------------------------------------------------------------------------------
// ?doResumeSupplyTruckingForIdleUnits@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doResumeSupplyTruckingForIdleUnits(const AsciiString& playerName)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (player && playerName.isNotEmpty())
	{
		player->setUnitsShouldIdleOrResume(false);
	}
	else
	{
		for (Int i=0; i<ThePlayerList->getPlayerCount(); ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
			{
				DEBUG_LOG(("ScriptActions::doResumeSupplyTruckingForIdleUnits() for player %d\n", i));
				player->setUnitsShouldIdleOrResume(false);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doAmbientSoundsPause */
//-------------------------------------------------------------------------------------------------
// ?doAmbientSoundsPause@ScriptActions@@IAEX_N@Z
// Body in Code/masm_dumps/ScriptActions_doAmbientSoundsPause.asm (exact 30B retail).


//-------------------------------------------------------------------------------------------------
/** doMusicTrackChange */
//-------------------------------------------------------------------------------------------------
// ?doMusicTrackChange@ScriptActions@@IAEXABVAsciiString@@_N1@Z present-unmatched
void ScriptActions::doMusicTrackChange(const AsciiString& newTrackName, Bool fadeout, Bool fadein)
{
	// Stop playing the music
	if (fadeout) {
		TheAudio->removeAudioEvent(AHSV_StopTheMusicFade);
	} else {
		TheAudio->removeAudioEvent(AHSV_StopTheMusic);
	}

	AudioEventRTS event(newTrackName);
	event.setShouldFade(fadein);
	event.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent(&event);

	TheScriptEngine->setCurrentTrackName(newTrackName);
}

//-------------------------------------------------------------------------------------------------
/** doTeamGarrisonSpecificBuilding */
//-------------------------------------------------------------------------------------------------
// ?doTeamGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamGarrisonSpecificBuilding(const AsciiString& teamName, const AsciiString& buildingName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}

	Object *theBuilding = TheScriptEngine->getUnitNamed(buildingName);
	if (!theBuilding) {
		return;
	}

	if( !theBuilding->getContain() )
	{
		DEBUG_CRASH( ("doTeamGarrisonSpecificBuilding script -- building doesn't have a container!" ) );
		return;
	}
	PlayerMaskType player = theBuilding->getContain()->getPlayerWhoEntered();

	if (!(theBuilding->isKindOf(KINDOF_STRUCTURE) && 
		(player == 0) || (player == theTeam->getControllingPlayer()->getPlayerMask()))) {
		return;
	}
	
	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}
	
	theTeam->getTeamAsAIGroup(theGroup);
	theGroup->groupEnter(theBuilding, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doExitSpecificBuilding */
//-------------------------------------------------------------------------------------------------
// ?doExitSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doExitSpecificBuilding(const AsciiString& buildingName)
{
	Object *theBuilding = TheScriptEngine->getUnitNamed(buildingName);
	if (!theBuilding) 
	{
		return;
	}
	
	if (!theBuilding->isKindOf(KINDOF_STRUCTURE)) 
	{
		return;
	}

	AIUpdateInterface *ai = theBuilding->getAIUpdateInterface();
	if (ai) 
	{
		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		ai->aiEvacuate( FALSE, CMD_FROM_SCRIPT );
		return;
	}

	ContainModuleInterface *contain = theBuilding->getContain();
	if (contain) 
	{
		contain->removeAllContained( FALSE );
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamGarrisonNearestBuilding */
//-------------------------------------------------------------------------------------------------
// ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamGarrisonNearestBuilding(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}
	
	DLINK_ITERATOR<Object> diter = theTeam->iterate_TeamMemberList();
	Object *leader = diter.cur();
	if (!leader) {
		return;
	}


	PartitionFilter *filters[16];
	Int count = 0;

	PartitionFilterAcceptByKindOf f1( MAKE_KINDOF_MASK( KINDOF_FS_INTERNET_CENTER ), KINDOFMASK_NONE );
	PartitionFilterGarrisonableByPlayer f2(theTeam->getControllingPlayer(), true, CMD_FROM_SCRIPT);

	if( leader->isKindOf( KINDOF_MONEY_HACKER ) )
	{
		//If the leader is a hacker, then look for an internet center instead of a normal building!
		filters[ count++ ] = &f1;
	}
	else
	{
		//If the leader ISN'T a hacker, then look for standard fare garrisonable buildings (internet centers won't show up)!
		filters[ count++ ] = &f2;
	}

	PartitionFilterSameMapStatus filterMapStatus(leader);
	filters[ count++ ] = &filterMapStatus;

	filters[count++] = NULL;

	ObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(leader, REALLY_FAR, FROM_CENTER_3D, filters, ITER_SORTED_NEAR_TO_FAR);
	MemoryPoolObjectHolder hold(iter);

	
	// here's what we do. Find out how many slots each building has open, and tell each unit individually to 
	// garrison a specific building. We won't use the partition solver because we've already done most of the work
	
	for (Object *theBuilding = iter->first(); theBuilding; theBuilding = iter->next()) {
		ContainModuleInterface *cmi = theBuilding->getContain();
		if (!cmi) {
			continue;
		}

		Int slotsAvailable = cmi->getContainMax() - cmi->getContainCount();
		for (int i = 0; i < slotsAvailable; ) {
			Object *obj = diter.cur();
			if (diter.done() || !obj) {
				return;
			}

			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai && obj->isKindOf(KINDOF_INFANTRY) && !obj->isKindOf(KINDOF_NO_GARRISON)) {
				ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
				++i;
			}
			diter.advance();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamExitAllBuildings */
//-------------------------------------------------------------------------------------------------
// ?doTeamExitAllBuildings@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamExitAllBuildings(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (!theTeam) {
		return;
	}
		
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj) {
			continue;
		}

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}

		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		ai->aiExit(NULL, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doUnitGarrisonSpecificBuilding */
//-------------------------------------------------------------------------------------------------
// ?doUnitGarrisonSpecificBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doUnitGarrisonSpecificBuilding(const AsciiString& unitName, const AsciiString& buildingName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	Object *theBuilding = TheScriptEngine->getUnitNamed(buildingName);
	if (!theBuilding) {
		return;
	}

	ContainModuleInterface *contain = theBuilding->getContain();
	if( !contain )
	{
		DEBUG_CRASH(("doUnitGarrisonSpecificBuilding script -- building doesn't have a container" ));
		return;
	}
	PlayerMaskType player = theBuilding->getContain()->getPlayerWhoEntered();

	if (!(theBuilding->isKindOf(KINDOF_STRUCTURE) && 
		(player == 0) || (player == theUnit->getControllingPlayer()->getPlayerMask()))) {
		return;
	}
	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doUnitGarrisonNearestBuilding */
//-------------------------------------------------------------------------------------------------
// ?doUnitGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doUnitGarrisonNearestBuilding(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai) {
		return;
	}


	PartitionFilter *filters[16];
	Int count = 0;

	PartitionFilterAcceptByKindOf f1(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	filters[ count++ ] = &f1;

	PartitionFilterSameMapStatus filterMapStatus(theUnit);
	filters[ count++ ] = &filterMapStatus;


	PartitionFilterAcceptByKindOf f2( MAKE_KINDOF_MASK( KINDOF_FS_INTERNET_CENTER ), KINDOFMASK_NONE );
	PartitionFilterRejectByKindOf f3( MAKE_KINDOF_MASK( KINDOF_FS_INTERNET_CENTER ), KINDOFMASK_NONE );
	
	if( theUnit->isKindOf( KINDOF_MONEY_HACKER ) )
	{
		//If the unit is a hacker, then look for an internet center instead of a normal building!
		filters[ count++ ] = &f2;
	}
	else
	{
		//If the unit ISN'T a hacker, then ignore internet centers!
		filters[ count++ ] = &f3;
	}

	filters[count++] = NULL;
	
	ObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(theUnit, REALLY_FAR, FROM_CENTER_3D, filters, ITER_SORTED_NEAR_TO_FAR);
	MemoryPoolObjectHolder hold(iter);

	for (Object *theBuilding = iter->first(); theBuilding; theBuilding = iter->next()) 
	{
		ContainModuleInterface *contain = theBuilding->getContain();
		if( !contain )
		{
			DEBUG_CRASH( ("doUnitGarrisonNearestBuilding script -- building doesn't have a container.") );
			continue;
		}
		PlayerMaskType player = theBuilding->getContain()->getPlayerWhoEntered();
		if (!((player == 0) || (player == theUnit->getControllingPlayer()->getPlayerMask()))) {
			continue;
		}

		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
		return;
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedEnableStealth */
//-------------------------------------------------------------------------------------------------
// ?doNamedEnableStealth@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doNamedEnableStealth( const AsciiString& unitName, Bool enabled )
{
	Object *self = TheScriptEngine->getUnitNamed( unitName );
	if( self )
	{
		self->setScriptStatus( OBJECT_STATUS_SCRIPT_UNSTEALTHED, !enabled );
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamEnableStealth */
//-------------------------------------------------------------------------------------------------
// ?doTeamEnableStealth@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamEnableStealth( const AsciiString& teamName, Bool enabled )
{
	Team *team = TheScriptEngine->getTeamNamed( teamName );
	if( !team ) 
	{
		return;
	}
		
	for( DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
	{
		Object *obj = iter.cur();
		if( obj ) 
		{
			obj->setScriptStatus( OBJECT_STATUS_SCRIPT_UNSTEALTHED, !enabled );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedSetUnmanned */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetUnmanned@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedSetUnmanned( const AsciiString& unitName )
{
	Object *self = TheScriptEngine->getUnitNamed( unitName );
	if( self )
	{
		self->setDisabled( DISABLED_UNMANNED );
		TheGameLogic->deselectObject( self, PLAYERMASK_ALL, TRUE );
		// Convert it to the neutral team so it renders gray giving visual representation that it is unmanned.
		self->setTeam( ThePlayerList->getNeutralPlayer()->getDefaultTeam() );
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamSetUnmanned */
//-------------------------------------------------------------------------------------------------
// ?doTeamSetUnmanned@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamSetUnmanned( const AsciiString& teamName )
{
	Team *team = TheScriptEngine->getTeamNamed( teamName );
	if( !team ) 
	{
		return;
	}
		
	for( DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); )
	{
		Object *obj = iter.cur();

		//Advance the iterator NOW because when we unman the object, the team gets nuked, and 
		//the iterator stops after the first iteration!
		iter.advance();
		//*************

		if( obj ) 
		{
			obj->setDisabled( DISABLED_UNMANNED );
			TheGameLogic->deselectObject( obj, PLAYERMASK_ALL, TRUE );
			// Convert it to the neutral team so it renders gray giving visual representation that it is unmanned.
			obj->setTeam( ThePlayerList->getNeutralPlayer()->getDefaultTeam() );
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedSetBoobytrapped@ScriptActions@@ present-unmatched
void ScriptActions::doNamedSetBoobytrapped( const AsciiString& thingTemplateName, const AsciiString& unitName )
{
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if( obj )
	{
		const ThingTemplate *thing = TheThingFactory->findTemplate( thingTemplateName );
		if( thing )
		{
			Object *boobytrap = TheThingFactory->newObject( thing, obj->getTeam() );
			if( boobytrap )
			{
				static NameKeyType key_StickyBombUpdate = NAMEKEY( "StickyBombUpdate" );
				StickyBombUpdate *update = (StickyBombUpdate*)boobytrap->findUpdateModule( key_StickyBombUpdate );
				if( update )
				{
					//The charge gets positioned randomly on the outside of the perimeter of the victim.
					Coord3D pos;
					obj->getGeometryInfo().makeRandomOffsetOnPerimeter( pos );

					//Get the angle and transform matrix from the obj... then transform the calculated
					//position 
					const Matrix3D *transform = obj->getTransformMatrix();
					transform->Transform_Vector( *transform, *(Vector3*)(&pos), (Vector3*)(&pos) );

					update->initStickyBomb( obj, NULL, &pos );
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doTeamSetBoobytrapped@ScriptActions@@ present-unmatched
void ScriptActions::doTeamSetBoobytrapped( const AsciiString& thingTemplateName, const AsciiString& teamName )
{
	Team *team = TheScriptEngine->getTeamNamed( teamName );
	if( !team ) 
	{
		return;
	}
		
	for( DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
	{
		Object *obj = iter.cur();

		const ThingTemplate *thing = TheThingFactory->findTemplate( thingTemplateName );
		if( thing )
		{
			Object *boobytrap = TheThingFactory->newObject( thing, obj->getTeam() );
			if( boobytrap )
			{
				static NameKeyType key_StickyBombUpdate = NAMEKEY( "StickyBombUpdate" );
				StickyBombUpdate *update = (StickyBombUpdate*)boobytrap->findUpdateModule( key_StickyBombUpdate );
				if( update )
				{
					//The charge gets positioned randomly on the outside of the perimeter of the victim.
					Coord3D pos;
					obj->getGeometryInfo().makeRandomOffsetOnPerimeter( pos );

					//Get the angle and transform matrix from the obj... then transform the calculated
					//position 
					const Matrix3D *transform = obj->getTransformMatrix();
					transform->Transform_Vector( *transform, *(Vector3*)(&pos), (Vector3*)(&pos) );

					update->initStickyBomb( obj, NULL, &pos );
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doUnitExitBuilding */
//-------------------------------------------------------------------------------------------------
// ?doUnitExitBuilding@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doUnitExitBuilding(const AsciiString& unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed( unitName );
	if (!theUnit) {
		return;
	}

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	ai->aiExit(NULL, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doPlayerGarrisonAllBuildings */
//-------------------------------------------------------------------------------------------------
// ?doPlayerGarrisonAllBuildings@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerGarrisonAllBuildings(const AsciiString& playerName)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	
	if (!player) {
		return;
	}

	player->garrisonAllUnits(CMD_FROM_SCRIPT);	
}

//-------------------------------------------------------------------------------------------------
/** doPlayerExitAllBuildings */
//-------------------------------------------------------------------------------------------------
// ?doPlayerExitAllBuildings@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doPlayerExitAllBuildings(const AsciiString& playerName)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	
	if (!player) {
		return;
	}

	player->ungarrisonAllUnits(CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doLetterBoxMode */
//-------------------------------------------------------------------------------------------------
// BFME Display enableLetterBox at vtable+0x130; Hide/ShowControlBar free funcs.
class BfmeDisplayLetterBox {
public:
	virtual void _disp_0() = 0;
	virtual void _disp_1() = 0;
	virtual void _disp_2() = 0;
	virtual void _disp_3() = 0;
	virtual void _disp_4() = 0;
	virtual void _disp_5() = 0;
	virtual void _disp_6() = 0;
	virtual void _disp_7() = 0;
	virtual void _disp_8() = 0;
	virtual void _disp_9() = 0;
	virtual void _disp_10() = 0;
	virtual void _disp_11() = 0;
	virtual void _disp_12() = 0;
	virtual void _disp_13() = 0;
	virtual void _disp_14() = 0;
	virtual void _disp_15() = 0;
	virtual void _disp_16() = 0;
	virtual void _disp_17() = 0;
	virtual void _disp_18() = 0;
	virtual void _disp_19() = 0;
	virtual void _disp_20() = 0;
	virtual void _disp_21() = 0;
	virtual void _disp_22() = 0;
	virtual void _disp_23() = 0;
	virtual void _disp_24() = 0;
	virtual void _disp_25() = 0;
	virtual void _disp_26() = 0;
	virtual void _disp_27() = 0;
	virtual void _disp_28() = 0;
	virtual void _disp_29() = 0;
	virtual void _disp_30() = 0;
	virtual void _disp_31() = 0;
	virtual void _disp_32() = 0;
	virtual void _disp_33() = 0;
	virtual void _disp_34() = 0;
	virtual void _disp_35() = 0;
	virtual void _disp_36() = 0;
	virtual void _disp_37() = 0;
	virtual void _disp_38() = 0;
	virtual void _disp_39() = 0;
	virtual void _disp_40() = 0;
	virtual void _disp_41() = 0;
	virtual void _disp_42() = 0;
	virtual void _disp_43() = 0;
	virtual void _disp_44() = 0;
	virtual void _disp_45() = 0;
	virtual void _disp_46() = 0;
	virtual void _disp_47() = 0;
	virtual void _disp_48() = 0;
	virtual void _disp_49() = 0;
	virtual void _disp_50() = 0;
	virtual void _disp_51() = 0;
	virtual void _disp_52() = 0;
	virtual void _disp_53() = 0;
	virtual void _disp_54() = 0;
	virtual void _disp_55() = 0;
	virtual void _disp_56() = 0;
	virtual void _disp_57() = 0;
	virtual void _disp_58() = 0;
	virtual void _disp_59() = 0;
	virtual void _disp_60() = 0;
	virtual void _disp_61() = 0;
	virtual void _disp_62() = 0;
	virtual void _disp_63() = 0;
	virtual void _disp_64() = 0;
	virtual void _disp_65() = 0;
	virtual void _disp_66() = 0;
	virtual void _disp_67() = 0;
	virtual void _disp_68() = 0;
	virtual void _disp_69() = 0;
	virtual void _disp_70() = 0;
	virtual void _disp_71() = 0;
	virtual void _disp_72() = 0;
	virtual void _disp_73() = 0;
	virtual void _disp_74() = 0;
	virtual void _disp_75() = 0;
	virtual void enableLetterBox(Bool enable) = 0;
};
void HideControlBar(Bool immediate);
void ShowControlBar(Bool immediate);

void ScriptActions::doLetterBoxMode(Bool startLetterbox)
{
	if (startLetterbox)
	{
		HideControlBar(TRUE);
		((BfmeDisplayLetterBox *)TheDisplay)->enableLetterBox(TRUE);
	}
	else
	{
		ShowControlBar(FALSE);
		((BfmeDisplayLetterBox *)TheDisplay)->enableLetterBox(FALSE);
	}
}

//-------------------------------------------------------------------------------------------------
/** doBlackWhiteMode */
//-------------------------------------------------------------------------------------------------
// ?doBlackWhiteMode@ScriptActions@@IAEX_NH@Z present-unmatched
void ScriptActions::doBlackWhiteMode(Bool startBWMode, Int frames)
{
	if (startBWMode)
	{
		TheTacticalView->setViewFilterMode(FM_VIEW_BW_BLACK_AND_WHITE);
		TheTacticalView->setViewFilter(FT_VIEW_BW_FILTER);
		TheTacticalView->setFadeParameters(frames, 1);
	}
	else
	{
		if ((TheTacticalView->getViewFilterType()) == FT_VIEW_BW_FILTER)
		{	//mode already set, turn it off
			TheTacticalView->setFadeParameters(frames, -1);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doSkyBox */
//-------------------------------------------------------------------------------------------------
extern void doSkyBoxSet(Bool startDraw);	//hack to avoid including globaldata here.

void ScriptActions::doSkyBox(Bool startDraw)
{
	if (startDraw)
	{
		doSkyBoxSet(1);
	}
	else
	{
		doSkyBoxSet(0);
	}
}

//-------------------------------------------------------------------------------------------------
/** doWeather */
//-------------------------------------------------------------------------------------------------

void ScriptActions::doWeather(Bool showWeather)
{
	TheSnowManager->setVisible(showWeather);
}

//-------------------------------------------------------------------------------------------------
/** Freeze time */
//-------------------------------------------------------------------------------------------------
// ?doFreezeTime@ScriptActions@@IAEXXZ
// Body in ScriptActions_doFreezeTime.asm (exact 11B @ 0x2EF680).


//-------------------------------------------------------------------------------------------------
/** Unfreeze time */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doUnfreezeTime(void)
{
	TheScriptEngine->doUnfreezeTime();
}

//-------------------------------------------------------------------------------------------------
/** Show a military briefing */
//-------------------------------------------------------------------------------------------------
// ?doMilitaryCaption@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doMilitaryCaption(const AsciiString& briefing, Int duration)
{
#if defined(_DEBUG) || defined(_INTERNAL)
	if (TheGlobalData->m_disableMilitaryCaption)
		duration = 1;
#endif

	TheInGameUI->militarySubtitle(briefing, duration);
}

//-------------------------------------------------------------------------------------------------
/** Set the audible distance for shots in which the camera is up, and is therefore the center */
//-------------------------------------------------------------------------------------------------
// ?doCameraSetAudibleDistance@ScriptActions@@IAEXM@Z present-unmatched
void ScriptActions::doCameraSetAudibleDistance(Real audibleDistance)
{
	// No-op
}

//-------------------------------------------------------------------------------------------------
/** doSetStoppingDistance */
//-------------------------------------------------------------------------------------------------
// ?doSetStoppingDistance@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doSetStoppingDistance(const AsciiString& team, Real stoppingDistance)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );

	if (theTeam)
	{
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();

			AIUpdateInterface *aiUpdate = obj->getAIUpdateInterface();
			if (!aiUpdate || !aiUpdate->getCurLocomotor()) {
				return;
			}
			
			if (stoppingDistance >= 0.5f)
			{
				aiUpdate->getCurLocomotor()->setCloseEnoughDist(stoppingDistance);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedSetHeld */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetHeld@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doNamedSetHeld(const AsciiString& unit, Bool held)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj) 
	{
		theObj->setDisabledUntil( DISABLED_HELD, held ? FOREVER : NEVER );
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedSetStoppingDistance */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetStoppingDistance@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doNamedSetStoppingDistance(const AsciiString& unit, Real stoppingDistance)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj) 
	{
		AIUpdateInterface *aiUpdate = theObj->getAIUpdateInterface();
		if (!aiUpdate || !aiUpdate->getCurLocomotor()) {
			return;
		}
		
		if (stoppingDistance >= 0.5f)
		{
			aiUpdate->getCurLocomotor()->setCloseEnoughDist(stoppingDistance);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doDisableSpecialPowerDisplay */
//-------------------------------------------------------------------------------------------------
// BFME InGameUI vtable: setSuperweaponDisplayEnabledByScript at +0x90.
class BfmeInGameUIVtableLayout {
public:
	virtual void _bfme_igui_slot_0() = 0;
	virtual void _bfme_igui_slot_1() = 0;
	virtual void _bfme_igui_slot_2() = 0;
	virtual void _bfme_igui_slot_3() = 0;
	virtual void _bfme_igui_slot_4() = 0;
	virtual void _bfme_igui_slot_5() = 0;
	virtual void _bfme_igui_slot_6() = 0;
	virtual void _bfme_igui_slot_7() = 0;
	virtual void _bfme_igui_slot_8() = 0;
	virtual void _bfme_igui_slot_9() = 0;
	virtual void _bfme_igui_slot_10() = 0;
	virtual void _bfme_igui_slot_11() = 0;
	virtual void _bfme_igui_slot_12() = 0;
	virtual void _bfme_igui_slot_13() = 0;
	virtual void _bfme_igui_slot_14() = 0;
	virtual void _bfme_igui_slot_15() = 0;
	virtual void _bfme_igui_slot_16() = 0;
	virtual void _bfme_igui_slot_17() = 0;
	virtual void _bfme_igui_slot_18() = 0;
	virtual void _bfme_igui_slot_19() = 0;
	virtual void _bfme_igui_slot_20() = 0;
	virtual void _bfme_igui_slot_21() = 0;
	virtual void _bfme_igui_slot_22() = 0;
	virtual void _bfme_igui_slot_23() = 0;
	virtual void _bfme_igui_slot_24() = 0;
	virtual void _bfme_igui_slot_25() = 0;
	virtual void _bfme_igui_slot_26() = 0;
	virtual void _bfme_igui_slot_27() = 0;
	virtual void _bfme_igui_slot_28() = 0;
	virtual void _bfme_igui_slot_29() = 0;
	virtual void _bfme_igui_slot_30() = 0;
	virtual void _bfme_igui_slot_31() = 0;
	virtual void _bfme_igui_slot_32() = 0;
	virtual void _bfme_igui_slot_33() = 0;
	virtual void _bfme_igui_slot_34() = 0;
	virtual void _bfme_igui_slot_35() = 0;
	virtual void setSuperweaponDisplayEnabledByScript(Bool enable) = 0;
};

void ScriptActions::doDisableSpecialPowerDisplay(void)
{
	((BfmeInGameUIVtableLayout *)TheInGameUI)->setSuperweaponDisplayEnabledByScript(false);
}

//-------------------------------------------------------------------------------------------------
/** doEnableSpecialPowerDisplay */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doEnableSpecialPowerDisplay(void)
{
	((BfmeInGameUIVtableLayout *)TheInGameUI)->setSuperweaponDisplayEnabledByScript(true);
}

//-------------------------------------------------------------------------------------------------
/** doNamedHideSpecialPowerDisplay */
//-------------------------------------------------------------------------------------------------
// ?doNamedHideSpecialPowerDisplay@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedHideSpecialPowerDisplay(const AsciiString& unit)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj)
	{
		TheInGameUI->hideObjectSuperweaponDisplayByScript(theObj);
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedShowSpecialPowerDisplay */
//-------------------------------------------------------------------------------------------------
// ?doNamedShowSpecialPowerDisplay@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedShowSpecialPowerDisplay(const AsciiString& unit)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj)
	{
		TheInGameUI->showObjectSuperweaponDisplayByScript(theObj);
	}
}

//-------------------------------------------------------------------------------------------------
/** doAudioSetVolume */
//-------------------------------------------------------------------------------------------------
// BFME Audio vtable +0xd4: setVolume(vol, which, 0).
class BfmeAudioVtbl_d4 {
public:
	virtual void _aD4_0() = 0;
	virtual void _aD4_1() = 0;
	virtual void _aD4_2() = 0;
	virtual void _aD4_3() = 0;
	virtual void _aD4_4() = 0;
	virtual void _aD4_5() = 0;
	virtual void _aD4_6() = 0;
	virtual void _aD4_7() = 0;
	virtual void _aD4_8() = 0;
	virtual void _aD4_9() = 0;
	virtual void _aD4_10() = 0;
	virtual void _aD4_11() = 0;
	virtual void _aD4_12() = 0;
	virtual void _aD4_13() = 0;
	virtual void _aD4_14() = 0;
	virtual void _aD4_15() = 0;
	virtual void _aD4_16() = 0;
	virtual void _aD4_17() = 0;
	virtual void _aD4_18() = 0;
	virtual void _aD4_19() = 0;
	virtual void _aD4_20() = 0;
	virtual void _aD4_21() = 0;
	virtual void _aD4_22() = 0;
	virtual void _aD4_23() = 0;
	virtual void _aD4_24() = 0;
	virtual void _aD4_25() = 0;
	virtual void _aD4_26() = 0;
	virtual void _aD4_27() = 0;
	virtual void _aD4_28() = 0;
	virtual void _aD4_29() = 0;
	virtual void _aD4_30() = 0;
	virtual void _aD4_31() = 0;
	virtual void _aD4_32() = 0;
	virtual void _aD4_33() = 0;
	virtual void _aD4_34() = 0;
	virtual void _aD4_35() = 0;
	virtual void _aD4_36() = 0;
	virtual void _aD4_37() = 0;
	virtual void _aD4_38() = 0;
	virtual void _aD4_39() = 0;
	virtual void _aD4_40() = 0;
	virtual void _aD4_41() = 0;
	virtual void _aD4_42() = 0;
	virtual void _aD4_43() = 0;
	virtual void _aD4_44() = 0;
	virtual void _aD4_45() = 0;
	virtual void _aD4_46() = 0;
	virtual void _aD4_47() = 0;
	virtual void _aD4_48() = 0;
	virtual void _aD4_49() = 0;
	virtual void _aD4_50() = 0;
	virtual void _aD4_51() = 0;
	virtual void _aD4_52() = 0;
	virtual void setVolume(Real volume, AudioAffect which, int unused) = 0;
};

void ScriptActions::doAudioSetVolume(AudioAffect whichToAffect, Real newVolumeLevel)
{
	newVolumeLevel /= 100.0f;
	if (newVolumeLevel < 0.0f) {
		newVolumeLevel = 0.0f;
	} else if (newVolumeLevel > 1.0f) {
		newVolumeLevel = 1.0f;
	}
	((BfmeAudioVtbl_d4 *)TheAudio)->setVolume(newVolumeLevel, whichToAffect, 0);
}

//-------------------------------------------------------------------------------------------------
/** doTransferTeamToPlayer */
//-------------------------------------------------------------------------------------------------
// ?doTransferTeamToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTransferTeamToPlayer(const AsciiString& teamName, const AsciiString& playerName)
{

	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	Player* playerDest = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!(theTeam && playerDest)) {
		return;
	}

	theTeam->setControllingPlayer(playerDest);

	// srj sez: ensure that all these guys get the upgrades that belong to the new player
	theTeam->iterateObjects(updateTeamAndPlayerStuff, NULL);
}

//-------------------------------------------------------------------------------------------------
/** doSetMoney */
//-------------------------------------------------------------------------------------------------
// ?doSetMoney@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doSetMoney(const AsciiString& playerName, Int money)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!player) {
		return;
	}

	Money *m = player->getMoney();
	if (!m)
		return;

	m->withdraw(m->countMoney());
	m->deposit(money);
}

//-------------------------------------------------------------------------------------------------
/** doGiveMoney */
//-------------------------------------------------------------------------------------------------
// ?doGiveMoney@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doGiveMoney(const AsciiString& playerName, Int money)
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!player) {
		return;
	}

	Money *m = player->getMoney();
	if (!m)
		return;

	if (money < 0)
		m->withdraw(-money);
	else
		m->deposit(money);
}

//-------------------------------------------------------------------------------------------------
/** doDisplayCounter */
//-------------------------------------------------------------------------------------------------
// ?doDisplayCounter@ScriptActions@@IAEXABVAsciiString@@0@Z
// Body in ScriptActions_doDisplayCounter.asm (exact 235B @ 0x2F9660).

//-------------------------------------------------------------------------------------------------
/** doHideCounter */
//-------------------------------------------------------------------------------------------------
// ?doHideCounter@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doHideCounter(const AsciiString& counterName)
{
	TheInGameUI->removeNamedTimer(counterName);
}

//-------------------------------------------------------------------------------------------------
/** doDisplayCountdownTimer */
//-------------------------------------------------------------------------------------------------
// ?doDisplayCountdownTimer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doDisplayCountdownTimer(const AsciiString& timerName, const AsciiString& timerText)
{
	TheInGameUI->addNamedTimer(timerName, TheGameText->fetch(timerText), true);
}

//-------------------------------------------------------------------------------------------------
/** doHideCountdownTimer */
//-------------------------------------------------------------------------------------------------
// ?doHideCountdownTimer@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doHideCountdownTimer(const AsciiString& timerName)
{
	TheInGameUI->removeNamedTimer(timerName);
}

//-------------------------------------------------------------------------------------------------
/** doDisableCountdownTimerDisplay */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doDisableCountdownTimerDisplay(void)
{
	TheInGameUI->showNamedTimerDisplay(FALSE);
}

//-------------------------------------------------------------------------------------------------
/** doEnableCountdownTimerDisplay */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doEnableCountdownTimerDisplay(void)
{
	TheInGameUI->showNamedTimerDisplay(TRUE);
}

//-------------------------------------------------------------------------------------------------
/** doNamedStopSpecialPowerCountdown */
//-------------------------------------------------------------------------------------------------
// ?doNamedStopSpecialPowerCountdown@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doNamedStopSpecialPowerCountdown(const AsciiString& unit, const AsciiString& specialPower, Bool stop)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (theObj && power)
	{
		SpecialPowerModuleInterface *mod = theObj->getSpecialPowerModule(power);
		if (mod)
		{
			mod->pauseCountdown(stop);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedSetSpecialPowerCountdown */
//-------------------------------------------------------------------------------------------------
// ?doNamedSetSpecialPowerCountdown@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doNamedSetSpecialPowerCountdown( const AsciiString& unit, const AsciiString& specialPower, Int seconds )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (theObj && power)
	{
		SpecialPowerModuleInterface *mod = theObj->getSpecialPowerModule(power);
		if (mod)
		{
			Int frames = LOGICFRAMES_PER_SECOND * seconds;
			mod->setReadyFrame(TheGameLogic->getFrame() + frames);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedAddSpecialPowerCountdown */
//-------------------------------------------------------------------------------------------------
// ?doNamedAddSpecialPowerCountdown@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doNamedAddSpecialPowerCountdown( const AsciiString& unit, const AsciiString& specialPower, Int seconds )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (theObj && power)
	{
		SpecialPowerModuleInterface *mod = theObj->getSpecialPowerModule(power);
		if (mod)
		{
			Int frames = LOGICFRAMES_PER_SECOND * seconds;
			mod->setReadyFrame(mod->getReadyFrame() + frames);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedFireSpecialPowerAtArea */
//-------------------------------------------------------------------------------------------------
// ?doNamedFireSpecialPowerAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doNamedFireSpecialPowerAtWaypoint( const AsciiString& unit, const AsciiString& specialPower, const AsciiString& waypoint )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (theObj && power)
	{
		SpecialPowerModuleInterface *mod = theObj->getSpecialPowerModule(power);
		if (mod)
		{
			Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
			if (!way) {
				return;
			}
			mod->doSpecialPowerAtLocation(way->getLocation(), INVALID_ANGLE, COMMAND_FIRED_BY_SCRIPT );
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedFireSpecialPowerAtArea */
//-------------------------------------------------------------------------------------------------
// ?doSkirmishFireSpecialPowerAtMostCost@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doSkirmishFireSpecialPowerAtMostCost( const AsciiString &player, const AsciiString& specialPower )
{
	Int enemyNdx;
	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemyPlayer == NULL) return;
	enemyNdx = enemyPlayer->getPlayerIndex();

	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (power==NULL) 
		return;
	Real radius = 50.0f;
	if (power->getRadiusCursorRadius()>radius) {
		radius = power->getRadiusCursorRadius();
	}
	
	Player::PlayerTeamList::const_iterator it;
	
	Player *pPlayer = TheScriptEngine->getPlayerFromAsciiString(player);
	if (pPlayer==NULL) 
		return;


	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) 
	{
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) 
		{
			Team *team = iter.cur();
			if (!team) 
				continue;

			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) 
			{
				Object *pObj = iter.cur();
				if (!pObj) 
					continue;

				SpecialPowerModuleInterface *mod = pObj->getSpecialPowerModule(power);
				if (mod)
				{
					if( !mod->isReady() )
						continue;
					
          
	        Coord3D location;
          Bool locationFound = FALSE;

					locationFound = pPlayer->computeSuperweaponTarget(power, &location, enemyNdx, radius);

					if( locationFound && power->getSpecialPowerType() == SPECIAL_SNEAK_ATTACK )
					{
						//We need to modify the location. We're already calculated the sweet spot, but we need to modify that
						//position if we can't place it in the current location.
						const ThingTemplate *sneakAttackTemplate = mod->getReferenceThingTemplate();
						if( sneakAttackTemplate )
						{
							locationFound = pPlayer->calcClosestConstructionZoneLocation( sneakAttackTemplate, &location );
						}
					}

          DEBUG_ASSERTCRASH( locationFound, ("ScriptActions::doSkirmishFireSpecialPowerAtMostCost() could not find a valid (costly) location.") );

					if( locationFound && location.lengthSqr() > 0.0f )
					{
						mod->doSpecialPowerAtLocation( &location, INVALID_ANGLE, COMMAND_FIRED_BY_SCRIPT );
					}
					break;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** doNamedFireSpecialPowerAtNamed */
//-------------------------------------------------------------------------------------------------
// ?doNamedFireSpecialPowerAtNamed@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doNamedFireSpecialPowerAtNamed( const AsciiString& unit, const AsciiString& specialPower, const AsciiString& target )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	Object *theTarget = TheScriptEngine->getUnitNamed( target );
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(specialPower);
	if (theObj && power && theTarget)
	{
		SpecialPowerModuleInterface *mod = theObj->getSpecialPowerModule(power);
		if (mod)
		{
			mod->doSpecialPowerAtObject(theTarget, COMMAND_FIRED_BY_SCRIPT );
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedUseCommandButtonAbility( const AsciiString& unit, const AsciiString& ability )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	
	//Sanity check
	if( !theObj )
	{
		return;
	}

	const CommandSet *commandSet = TheControlBar->findCommandSet( theObj->getCommandSetString() );
	if( commandSet )
	{
		for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
		{
			//Get the command button.
			const CommandButton *commandButton = commandSet->getCommandButton(i);

			if( commandButton )
			{
				if( !commandButton->getName().isEmpty() )
				{
					if( commandButton->getName() == ability )
					{
						theObj->doCommandButton( commandButton, CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedUseCommandButtonAbilityOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doNamedUseCommandButtonAbilityOnNamed( const AsciiString& unit, const AsciiString& ability, const AsciiString& target )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	Object *theTarget = TheScriptEngine->getUnitNamed( target );
	
	//Sanity check
	if( !theObj || !theTarget )
	{
		return;
	}

	const CommandSet *commandSet = TheControlBar->findCommandSet( theObj->getCommandSetString() );
	if( commandSet )
	{
		for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
		{
			//Get the command button.
			const CommandButton *commandButton = commandSet->getCommandButton(i);

			if( commandButton )
			{
				if( !commandButton->getName().isEmpty() )
				{
					if( commandButton->getName() == ability )
					{
						theObj->doCommandButtonAtObject( commandButton, theTarget, CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doNamedUseCommandButtonAbilityAtWaypoint( const AsciiString& unit, const AsciiString& ability, const AsciiString& waypoint )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	Waypoint *pWaypoint = TheTerrainLogic->getWaypointByName( waypoint );
	
	//Sanity check
	if( !theObj || !pWaypoint )
	{
		return;
	}

	const CommandSet *commandSet = TheControlBar->findCommandSet( theObj->getCommandSetString() );
	if( commandSet )
	{
		for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
		{
			//Get the command button.
			const CommandButton *commandButton = commandSet->getCommandButton(i);

			if( commandButton )
			{
				if( !commandButton->getName().isEmpty() )
				{
					if( commandButton->getName() == ability )
					{
						theObj->doCommandButtonAtPosition( commandButton, pWaypoint->getLocation(), CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedUseCommandButtonAbilityUsingWaypointPath@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doNamedUseCommandButtonAbilityUsingWaypointPath( const AsciiString& unit, const AsciiString& ability, const AsciiString& waypointPath )
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if( !theObj )
	{
		return;
	}

	Waypoint *pWaypoint = TheTerrainLogic->getClosestWaypointOnPath( theObj->getPosition(), waypointPath );
	
	//Sanity check
	if( !pWaypoint )
	{
		return;
	}

	const CommandSet *commandSet = TheControlBar->findCommandSet( theObj->getCommandSetString() );
	if( commandSet )
	{
		for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
		{
			//Get the command button.
			const CommandButton *commandButton = commandSet->getCommandButton(i);

			if( commandButton )
			{
				if( !commandButton->getName().isEmpty() )
				{
					if( commandButton->getName() == ability )
					{
						theObj->doCommandButtonUsingWaypoints( commandButton, pWaypoint, CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonAbility@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonAbility( const AsciiString& team, const AsciiString& ability )
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if( !theTeam ) 
	{
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton( ability );
	if( !commandButton )
	{
		return;
	}


	AIGroup* theGroup = TheAI->createGroup();
	if( !theGroup ) 
	{
		return;
	}

	theTeam->getTeamAsAIGroup( theGroup );
	
	theGroup->groupDoCommandButton( commandButton, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonAbilityOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonAbilityOnNamed( const AsciiString& team, const AsciiString& ability, const AsciiString& target )
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if( !theTeam ) 
	{
		return;
	}

	Object *theObj = TheScriptEngine->getUnitNamed( target );
	if( !theObj )
	{
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton( ability );
	if( !commandButton )
	{
		return;
	}


	AIGroup* theGroup = TheAI->createGroup();
	if( !theGroup ) 
	{
		return;
	}

	theTeam->getTeamAsAIGroup( theGroup );
	
	theGroup->groupDoCommandButtonAtObject( commandButton, theObj, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonAbilityAtWaypoint( const AsciiString& team, const AsciiString& ability, const AsciiString& waypoint )
{
	Team *theTeam = TheScriptEngine->getTeamNamed( team );
	// The team is the team based on the name, and the calling team (if any) and the team that
	// triggered the condition.  jba. :)
	if( !theTeam ) 
	{
		return;
	}

	Waypoint *pWaypoint = TheTerrainLogic->getWaypointByName( waypoint );
	if( !pWaypoint )
	{
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton( ability );
	if( !commandButton )
	{
		return;
	}


	AIGroup* theGroup = TheAI->createGroup();
	if( !theGroup ) 
	{
		return;
	}

	theTeam->getTeamAsAIGroup( theGroup );
	
	theGroup->groupDoCommandButtonAtPosition( commandButton, pWaypoint->getLocation(), CMD_FROM_SCRIPT );
}

		



//-------------------------------------------------------------------------------------------------
/** doRadarRefresh */
//-------------------------------------------------------------------------------------------------
// BFME Radar vtable: refreshTerrain at +0x10.
class BfmeRadarVtableLayout {
public:
	virtual void _bfme_radar_slot_0() = 0;
	virtual void _bfme_radar_slot_1() = 0;
	virtual void _bfme_radar_slot_2() = 0;
	virtual void _bfme_radar_slot_3() = 0;
	virtual void refreshTerrain(TerrainLogic *terrain) = 0;
};

void ScriptActions::doRadarRefresh( void )
{
	((BfmeRadarVtableLayout *)TheRadar)->refreshTerrain(TheTerrainLogic);
}


//-------------------------------------------------------------------------------------------------
/** doCameraTetherNamed */
//-------------------------------------------------------------------------------------------------
// ?doCameraTetherNamed@ScriptActions@@IAEXABVAsciiString@@_NM@Z present-unmatched
void ScriptActions::doCameraTetherNamed(const AsciiString& unit, Bool snapToUnit, Real play)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unit );
	if (theObj) 
	{	
		TheTacticalView->setCameraLock(theObj->getID());
		if (snapToUnit)
			TheTacticalView->snapToCameraLock();

		TheTacticalView->setSnapMode( View::LOCK_TETHER, play );
	}
}

//-------------------------------------------------------------------------------------------------
/** doCameraStopTetherNamed */
//-------------------------------------------------------------------------------------------------
// ?doCameraStopTetherNamed@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::doCameraStopTetherNamed(void)
{
	TheTacticalView->setCameraLock(INVALID_ID);
}

//-------------------------------------------------------------------------------------------------
/** doCameraSetDefault */
//-------------------------------------------------------------------------------------------------
// ?doCameraSetDefault@ScriptActions@@IAEXMMM@Z present-unmatched
void ScriptActions::doCameraSetDefault(Real pitch, Real angle, Real maxHeight)
{
	TheTacticalView->setDefaultView(pitch, angle, maxHeight);
}

//-------------------------------------------------------------------------------------------------
/** doNamedStop */
//-------------------------------------------------------------------------------------------------
// ?doNamedStop@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doNamedStop(const AsciiString& unitName)
{
	Object *theObj = TheScriptEngine->getUnitNamed( unitName );
	if (!theObj) {
		return;
	}

	AIUpdateInterface *ai = theObj->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	ai->aiIdle(CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamStop */
//-------------------------------------------------------------------------------------------------
// ?doTeamStop@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doTeamStop(const AsciiString& teamName, Bool shouldDisband)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);
	theGroup->groupIdle(CMD_FROM_SCRIPT);

	if (shouldDisband) {
		Team *playerDefaultTeam = theTeam->getControllingPlayer()->getDefaultTeam();
		
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();

			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (!ai) {
				continue;
			}

			ai->setIsRecruitable(TRUE);
		}

		doMergeTeamIntoTeam(teamName, playerDefaultTeam->getName());
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamSetOverrideRelationToTeam */
//-------------------------------------------------------------------------------------------------
// ?doTeamSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doTeamSetOverrideRelationToTeam(const AsciiString& teamName, const AsciiString& otherTeam, Int relation)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	Team *theOtherTeam = TheScriptEngine->getTeamNamed( otherTeam );
	if (theTeam && theOtherTeam) {
		theTeam->setOverrideTeamRelationship(theOtherTeam->getID(), (Relationship)relation);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamRemoveOverrideRelationToTeam */
//-------------------------------------------------------------------------------------------------
// ?doTeamRemoveOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamRemoveOverrideRelationToTeam(const AsciiString& teamName, const AsciiString& otherTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	Team *theOtherTeam = TheScriptEngine->getTeamNamed( otherTeam );
	if (theTeam && theOtherTeam) {
		theTeam->removeOverrideTeamRelationship(theOtherTeam->getID());
	}
}

//-------------------------------------------------------------------------------------------------
/** doPlayerSetOverrideRelationToTeam */
//-------------------------------------------------------------------------------------------------
// ?doPlayerSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doPlayerSetOverrideRelationToTeam(const AsciiString& playerName, const AsciiString& otherTeam, Int relation)
{
	Player *thePlayer = ThePlayerList->findPlayerWithNameKey(NAMEKEY(playerName));
	Team *theOtherTeam = TheScriptEngine->getTeamNamed( otherTeam );
	if (thePlayer && theOtherTeam) {
		thePlayer->setTeamRelationship(theOtherTeam, (Relationship)relation);
	}
}

//-------------------------------------------------------------------------------------------------
/** doPlayerRemoveOverrideRelationToTeam */
//-------------------------------------------------------------------------------------------------
// ?doPlayerRemoveOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doPlayerRemoveOverrideRelationToTeam(const AsciiString& playerName, const AsciiString& otherTeam)
{
	Player *thePlayer = ThePlayerList->findPlayerWithNameKey(NAMEKEY(playerName));
	Team *theOtherTeam = TheScriptEngine->getTeamNamed( otherTeam );
	if (thePlayer && theOtherTeam) {
		thePlayer->removeTeamRelationship(theOtherTeam);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamSetOverrideRelationToPlayer */
//-------------------------------------------------------------------------------------------------
// ?doTeamSetOverrideRelationToPlayer@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doTeamSetOverrideRelationToPlayer(const AsciiString& teamName, const AsciiString& otherPlayer, Int relation)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	Player *theOtherPlayer = ThePlayerList->findPlayerWithNameKey(NAMEKEY(otherPlayer));
	if (theTeam && theOtherPlayer) {
		theTeam->setOverridePlayerRelationship(theOtherPlayer->getPlayerIndex(), (Relationship)relation);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamRemoveOverrideRelationToTeam */
//-------------------------------------------------------------------------------------------------
// ?doTeamRemoveOverrideRelationToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamRemoveOverrideRelationToPlayer(const AsciiString& teamName, const AsciiString& otherPlayer)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	Player *theOtherPlayer = ThePlayerList->findPlayerWithNameKey(NAMEKEY(otherPlayer));
	if (theTeam && theOtherPlayer) {
		theTeam->removeOverridePlayerRelationship(theOtherPlayer->getPlayerIndex());
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamRemoveAllOverrideRelations */
//-------------------------------------------------------------------------------------------------
// ?doTeamRemoveAllOverrideRelations@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamRemoveAllOverrideRelations(const AsciiString& teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if (theTeam) {
		// invalid ID is OK -- it removes all relationships
		theTeam->removeOverrideTeamRelationship( NULL );
		theTeam->removeOverridePlayerRelationship( NULL );
	}
}
//-------------------------------------------------------------------------------------------------
/** doUnitStartSequentialScript */
//-------------------------------------------------------------------------------------------------
// ?doUnitStartSequentialScript@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doUnitStartSequentialScript(const AsciiString& unitName, const AsciiString& scriptName, Int loopVal)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	Script *script = const_cast<Script*>(TheScriptEngine->findScriptByName(scriptName));
	if (!script) {
		return;
	}

	SequentialScript* seqScript = newInstance(SequentialScript);
	seqScript->m_objectID = obj->getID();
	seqScript->m_scriptToExecuteSequentially = script;
	seqScript->m_timesToLoop = loopVal;
	
	TheScriptEngine->appendSequentialScript(seqScript);

	seqScript->deleteInstance();
}

//-------------------------------------------------------------------------------------------------
/** doUnitStopSequentialScript */
//-------------------------------------------------------------------------------------------------
// ?doUnitStopSequentialScript@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doUnitStopSequentialScript(const AsciiString& unitName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	TheScriptEngine->removeAllSequentialScripts(obj);
}

//-------------------------------------------------------------------------------------------------
/** doTeamStartSequentialScript */
//-------------------------------------------------------------------------------------------------
/** doNamedFireWeaponFollowingWaypointPath -- Kris
		Orders unit to fire a waypoint following capable weapon to follow a waypoint and attack the
		final waypoint position. */
//-------------------------------------------------------------------------------------------------
// ?doNamedFireWeaponFollowingWaypointPath@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedFireWeaponFollowingWaypointPath( const AsciiString& unit, const AsciiString& waypointPath )
{
	//Get the unit... if it fails, abort.
	Object *theUnit = TheScriptEngine->getUnitNamed( unit );
	if( !theUnit ) 
	{
		return;
	}
	
	Coord3D pos = *theUnit->getPosition();


	//Find the closest waypoint on the path.
	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath( &pos, waypointPath );
	if( !way )
	{
		return;
	}
	//We have to do special checking to make sure our unit even has a waypoint following capable weapon.
	Weapon *weapon = theUnit->findWaypointFollowingCapableWeapon();
	if( !weapon )
	{
		return;
	}

	Object *projectile = weapon->forceFireWeapon( theUnit, &pos );
	if( projectile )
	{
		//Get the AIUpdateInterface... if it fails, abort.
		AIUpdateInterface* aiUpdate = projectile->getAIUpdateInterface();
		if( !aiUpdate )
		{
			return;
		}
		DEBUG_ASSERTLOG(TheTerrainLogic->isPurposeOfPath(way, waypointPath), ("***Wrong waypoint purpose. Make jba fix this.\n"));
		
		projectile->leaveGroup();
		aiUpdate->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		aiUpdate->aiFollowWaypointPath(way, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamStartSequentialScript */
//-------------------------------------------------------------------------------------------------
// ?doTeamStartSequentialScript@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doTeamStartSequentialScript(const AsciiString& teamName, const AsciiString& scriptName, Int loopVal)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	Script *script = const_cast<Script*>(TheScriptEngine->findScriptByName(scriptName));
	if (!script) {
		return;
	}

	// Idle the team so the seq script will start executing. jba.
	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	team->getTeamAsAIGroup(theGroup);
	theGroup->groupIdle(CMD_FROM_SCRIPT);


	SequentialScript* seqScript = newInstance(SequentialScript);
	seqScript->m_teamToExecOn = team;
	seqScript->m_scriptToExecuteSequentially = script;
	seqScript->m_timesToLoop = loopVal;
	
	TheScriptEngine->appendSequentialScript(seqScript);

	seqScript->deleteInstance();
}

//-------------------------------------------------------------------------------------------------
/** doTeamStopSequentialScript */
//-------------------------------------------------------------------------------------------------
// ?doTeamStopSequentialScript@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamStopSequentialScript(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	TheScriptEngine->removeAllSequentialScripts(team);
}


//-------------------------------------------------------------------------------------------------
/** doUnitGuardForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doUnitGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doUnitGuardForFramecount(const AsciiString& unitName, Int framecount)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	Coord3D pos = *obj->getPosition();
	ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	ai->aiGuardPosition(&pos, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
	TheScriptEngine->setSequentialTimer(obj, framecount);
}

//-------------------------------------------------------------------------------------------------
/** doUnitIdleForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doUnitIdleForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doUnitIdleForFramecount(const AsciiString& unitName, Int framecount)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	ai->aiIdle(CMD_FROM_SCRIPT);
	TheScriptEngine->setSequentialTimer(obj, framecount);
}

//-------------------------------------------------------------------------------------------------
/** doTeamGuardForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doTeamGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doTeamGuardForFramecount(const AsciiString& teamName, Int framecount)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theTeam) {
		return;
	}

	// Have all the members of the team guard at their current pos.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		Coord3D pos = *obj->getPosition();
		ai->aiGuardPosition(&pos, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
	}
	TheScriptEngine->setSequentialTimer(theTeam, framecount);
}

//-------------------------------------------------------------------------------------------------
/** doTeamIdleForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doTeamIdleForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doTeamIdleForFramecount(const AsciiString& teamName, Int framecount)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName);
	if (!theTeam) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);
	Coord3D center;
	theGroup->getCenter(&center);

	theGroup->groupIdle(CMD_FROM_SCRIPT);
	TheScriptEngine->setSequentialTimer(theTeam, framecount);
}

//-------------------------------------------------------------------------------------------------
/** doWaterChangeHeight */
//-------------------------------------------------------------------------------------------------
// ?doWaterChangeHeight@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doWaterChangeHeight(const AsciiString& waterName, Real newHeight)
{
	const WaterHandle *water = TheTerrainLogic->getWaterHandleByName(waterName);
	if (!water) {
		return;
	}

	TheTerrainLogic->setWaterHeight(water, newHeight, 999999.9f, TRUE );
}

//-------------------------------------------------------------------------------------------------
/** doWaterChangeHeightOverTime */
//-------------------------------------------------------------------------------------------------
// ?doWaterChangeHeightOverTime@ScriptActions@@IAEXABVAsciiString@@MMM@Z present-unmatched
void ScriptActions::doWaterChangeHeightOverTime( const AsciiString& waterName, Real newHeight, Real time, Real damage )
{
	const WaterHandle *water = TheTerrainLogic->getWaterHandleByName( waterName );
	if( water )
	{
		TheTerrainLogic->changeWaterHeightOverTime( water, newHeight, time, damage );
	}
}

//-------------------------------------------------------------------------------------------------
/** doBorderSwitch */
//-------------------------------------------------------------------------------------------------
// ?doBorderSwitch@ScriptActions@@IAEXH@Z present-unmatched
void ScriptActions::doBorderSwitch(Int borderToUse)
{
	/*
	 *	The observer player always has to have the map completely revealed for him.
	 *	Border switching doesn't play nice with the permanent map reveal so for the
	 *	observer player we need to undo the old permanent reveal, switch map borders,
	 *	and re-reveal the map. BGC
	*/
	Int observerPlayerIndex = -1;
	if (ThePlayerList != NULL)
	{
		Player *observer = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("ReplayObserver"));

		if (observer != NULL) {
			observerPlayerIndex = observer->getPlayerIndex();
		}
	}

	if (observerPlayerIndex != -1)
	{
		ThePartitionManager->undoRevealMapForPlayerPermanently( observerPlayerIndex );
	}

	TheTerrainLogic->setActiveBoundary(borderToUse);

	if (observerPlayerIndex != -1)
	{
		ThePartitionManager->revealMapForPlayerPermanently( observerPlayerIndex );
	}
	
	ThePartitionManager->refreshShroudForLocalPlayer();
}

//-------------------------------------------------------------------------------------------------
/** doForceObjectSelection */
//-------------------------------------------------------------------------------------------------
// ?doForceObjectSelection@ScriptActions@@IAEXABVAsciiString@@0_N0@Z present-unmatched
void ScriptActions::doForceObjectSelection(const AsciiString& teamName, const AsciiString& objectType, Bool centerInView, const AsciiString& audioToPlay)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	
	if (!team) {
		return;
	}

	Object *bestGuess = NULL;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj) {
			continue;
		}
		
		if (obj->getTemplate() && obj->getTemplate()->getName() == objectType) {
			if (bestGuess == NULL || obj->getID() < bestGuess->getID()) { // lower ID means its newer
				bestGuess = obj;				
			}
		}
	}
	
	if (!(bestGuess && bestGuess->getDrawable())) {
		return;
	}

	TheInGameUI->deselectAllDrawables();
	TheInGameUI->selectDrawable(bestGuess->getDrawable());
	// play the sound
	AudioEventRTS audioEvent(audioToPlay);
	audioEvent.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent(&audioEvent);

	if (centerInView) {
		Coord3D pos = *bestGuess->getPosition();
		TheTacticalView->moveCameraTo(&pos, 0, 0, FALSE, 0.0f, 0.0f);
	}
}

void* __cdecl killTheObject( Object *obj, void* userObj )
{
	userObj;
	if (obj)
		obj->kill();
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** doForceObjectSelection */
//-------------------------------------------------------------------------------------------------
// ?doDestroyAllContained@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doDestroyAllContained(const AsciiString& unitName, Int damageType )
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	ContainModuleInterface *cmi = obj->getContain();
	if( !cmi || cmi->getContainCount() == 0 ) 
	{
		return;
	}

	cmi->iterateContained((ContainIterateFunc)killTheObject, NULL, false);
}

//-------------------------------------------------------------------------------------------------
/** doRadarForceEnable */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doRadarForceEnable(void)
{
	TheRadar->forceOn(true);
}

//-------------------------------------------------------------------------------------------------
/** doRadarRevertNormal */
//-------------------------------------------------------------------------------------------------
void ScriptActions::doRadarRevertNormal(void)
{
	TheRadar->forceOn(false);
}

//-------------------------------------------------------------------------------------------------
/** doScreenShake */
//-------------------------------------------------------------------------------------------------
// ?doScreenShake@ScriptActions@@IAEXI@Z present-unmatched
void ScriptActions::doScreenShake( UnsignedInt intensity )
{
	Coord3D pos;
	TheTacticalView->getPosition( &pos );
	TheTacticalView->shake( &pos, (View::CameraShakeType)intensity );
}

//-------------------------------------------------------------------------------------------------
/** doModifyBuildableStatus */
//-------------------------------------------------------------------------------------------------
// ?doModifyBuildableStatus@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doModifyBuildableStatus( const AsciiString& objectType, Int buildableStatus )
{
	const ThingTemplate *templ = TheThingFactory->findTemplate(objectType);
	if (!templ) 
	{
		return;
	}

	TheGameLogic->setBuildableStatusOverride(templ, (BuildableStatus) buildableStatus);
}

//-------------------------------------------------------------------------------------------------
static CaveInterface* findCave(Object* obj)
{
	for (BehaviorModule** i = obj->getBehaviorModules(); *i; ++i)
	{
		CaveInterface* c = (*i)->getCaveInterface();
		if (c != NULL)
			return c;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** doSetCaveIndex */
//-------------------------------------------------------------------------------------------------
// ?doSetCaveIndex@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doSetCaveIndex( const AsciiString& caveName, Int caveIndex )
{
	Object *obj = TheScriptEngine->getUnitNamed(caveName);
	if (!obj) 
	{
		return;
	}

	CaveInterface *caveModule = findCave(obj);
	if( caveModule == NULL )
		return;

	caveModule->tryToSetCaveIndex( caveIndex );
}

//-------------------------------------------------------------------------------------------------
/** doSetWarehouseValue */
//-------------------------------------------------------------------------------------------------
// ?doSetWarehouseValue@ScriptActions@@ present-unmatched
void ScriptActions::doSetWarehouseValue( const AsciiString& warehouseName, Int cashValue )
{
	Object *obj = TheScriptEngine->getUnitNamed(warehouseName);
	if (!obj) 
	{
		return;
	}

	static const NameKeyType warehouseModuleKey = TheNameKeyGenerator->nameToKey( "SupplyWarehouseDockUpdate" );
	SupplyWarehouseDockUpdate *warehouseModule = (SupplyWarehouseDockUpdate *)obj->findUpdateModule( warehouseModuleKey );
	if( warehouseModule == NULL )
		return;

	warehouseModule->setCashValue( cashValue );
}

//-------------------------------------------------------------------------------------------------
/** doSoundEnableType */
//-------------------------------------------------------------------------------------------------
// ?doSoundEnableType@ScriptActions@@IAEXABVAsciiString@@_N@Z present-unmatched
void ScriptActions::doSoundEnableType( const AsciiString& soundEventName, Bool enable )
{
	TheAudio->setAudioEventEnabled(soundEventName, enable);
}

//-------------------------------------------------------------------------------------------------
// BFME Audio vtable: removeDisabledEvents-like at +0x9c with extra 0 arg.
class BfmeAudioVtableLayout9c {
public:
	virtual void _bfme_audio_slot_0() = 0;
	virtual void _bfme_audio_slot_1() = 0;
	virtual void _bfme_audio_slot_2() = 0;
	virtual void _bfme_audio_slot_3() = 0;
	virtual void _bfme_audio_slot_4() = 0;
	virtual void _bfme_audio_slot_5() = 0;
	virtual void _bfme_audio_slot_6() = 0;
	virtual void _bfme_audio_slot_7() = 0;
	virtual void _bfme_audio_slot_8() = 0;
	virtual void _bfme_audio_slot_9() = 0;
	virtual void _bfme_audio_slot_10() = 0;
	virtual void _bfme_audio_slot_11() = 0;
	virtual void _bfme_audio_slot_12() = 0;
	virtual void _bfme_audio_slot_13() = 0;
	virtual void _bfme_audio_slot_14() = 0;
	virtual void _bfme_audio_slot_15() = 0;
	virtual void _bfme_audio_slot_16() = 0;
	virtual void _bfme_audio_slot_17() = 0;
	virtual void _bfme_audio_slot_18() = 0;
	virtual void _bfme_audio_slot_19() = 0;
	virtual void _bfme_audio_slot_20() = 0;
	virtual void _bfme_audio_slot_21() = 0;
	virtual void _bfme_audio_slot_22() = 0;
	virtual void _bfme_audio_slot_23() = 0;
	virtual void _bfme_audio_slot_24() = 0;
	virtual void _bfme_audio_slot_25() = 0;
	virtual void _bfme_audio_slot_26() = 0;
	virtual void _bfme_audio_slot_27() = 0;
	virtual void _bfme_audio_slot_28() = 0;
	virtual void _bfme_audio_slot_29() = 0;
	virtual void _bfme_audio_slot_30() = 0;
	virtual void _bfme_audio_slot_31() = 0;
	virtual void _bfme_audio_slot_32() = 0;
	virtual void _bfme_audio_slot_33() = 0;
	virtual void _bfme_audio_slot_34() = 0;
	virtual void _bfme_audio_slot_35() = 0;
	virtual void _bfme_audio_slot_36() = 0;
	virtual void _bfme_audio_slot_37() = 0;
	virtual void _bfme_audio_slot_38() = 0;
	virtual void removeDisabledEvents(int unused) = 0;
};

void ScriptActions::doSoundRemoveAllDisabled()
{
	((BfmeAudioVtableLayout9c *)TheAudio)->removeDisabledEvents(0);
}

//-------------------------------------------------------------------------------------------------
// BFME Audio vtable +0x48: removeAudioEvent(name, 0).
class BfmeAudioVtbl_48 {
public:
	virtual void _a48_0() = 0;
	virtual void _a48_1() = 0;
	virtual void _a48_2() = 0;
	virtual void _a48_3() = 0;
	virtual void _a48_4() = 0;
	virtual void _a48_5() = 0;
	virtual void _a48_6() = 0;
	virtual void _a48_7() = 0;
	virtual void _a48_8() = 0;
	virtual void _a48_9() = 0;
	virtual void _a48_10() = 0;
	virtual void _a48_11() = 0;
	virtual void _a48_12() = 0;
	virtual void _a48_13() = 0;
	virtual void _a48_14() = 0;
	virtual void _a48_15() = 0;
	virtual void _a48_16() = 0;
	virtual void _a48_17() = 0;
	virtual void removeAudioEvent(const AsciiString& name, int unused) = 0;
};

void ScriptActions::doSoundRemoveType( const AsciiString& soundEventName )
{
	((BfmeAudioVtbl_48 *)TheAudio)->removeAudioEvent(soundEventName, 0);
}

//-------------------------------------------------------------------------------------------------
/** doSoundOverrideVolume */
//-------------------------------------------------------------------------------------------------
// BFME Audio vtable +0xa0: setAudioEventVolumeOverride(name, vol, 0).
class BfmeAudioVtbl_a0 {
public:
	virtual void _aA0_0() = 0;
	virtual void _aA0_1() = 0;
	virtual void _aA0_2() = 0;
	virtual void _aA0_3() = 0;
	virtual void _aA0_4() = 0;
	virtual void _aA0_5() = 0;
	virtual void _aA0_6() = 0;
	virtual void _aA0_7() = 0;
	virtual void _aA0_8() = 0;
	virtual void _aA0_9() = 0;
	virtual void _aA0_10() = 0;
	virtual void _aA0_11() = 0;
	virtual void _aA0_12() = 0;
	virtual void _aA0_13() = 0;
	virtual void _aA0_14() = 0;
	virtual void _aA0_15() = 0;
	virtual void _aA0_16() = 0;
	virtual void _aA0_17() = 0;
	virtual void _aA0_18() = 0;
	virtual void _aA0_19() = 0;
	virtual void _aA0_20() = 0;
	virtual void _aA0_21() = 0;
	virtual void _aA0_22() = 0;
	virtual void _aA0_23() = 0;
	virtual void _aA0_24() = 0;
	virtual void _aA0_25() = 0;
	virtual void _aA0_26() = 0;
	virtual void _aA0_27() = 0;
	virtual void _aA0_28() = 0;
	virtual void _aA0_29() = 0;
	virtual void _aA0_30() = 0;
	virtual void _aA0_31() = 0;
	virtual void _aA0_32() = 0;
	virtual void _aA0_33() = 0;
	virtual void _aA0_34() = 0;
	virtual void _aA0_35() = 0;
	virtual void _aA0_36() = 0;
	virtual void _aA0_37() = 0;
	virtual void _aA0_38() = 0;
	virtual void _aA0_39() = 0;
	virtual void setAudioEventVolumeOverride(const AsciiString& name, Real vol, int unused) = 0;
};

void ScriptActions::doSoundOverrideVolume( const AsciiString& soundEventName, Real newVolume )
{
	((BfmeAudioVtbl_a0 *)TheAudio)->setAudioEventVolumeOverride(soundEventName, newVolume / 100.0f, 0);
}

//-------------------------------------------------------------------------------------------------
/** doSetToppleDirection */
//-------------------------------------------------------------------------------------------------
// ?doSetToppleDirection@ScriptActions@@IAEXABVAsciiString@@PBUCoord3D@@@Z present-unmatched
void ScriptActions::doSetToppleDirection( const AsciiString& unitName, const Coord3D *dir )
{
	TheScriptEngine->setToppleDirection(unitName, dir);
}

//-------------------------------------------------------------------------------------------------
/** doMoveTeamTowardsNearest */
//-------------------------------------------------------------------------------------------------
// ?doMoveUnitTowardsNearest@ScriptActions@@IAEXABVAsciiString@@0V2@@Z present-unmatched
void ScriptActions::doMoveUnitTowardsNearest( const AsciiString& unitName, const AsciiString& objectType, AsciiString triggerName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) 
	{
		return;
	}

	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai) 
	{
		return;
	}
	
	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trig) 
	{
		return;
	}

	Object *bestObj = NULL;

	const ThingTemplate *templ = TheThingFactory->findTemplate( objectType, FALSE );
	if( templ ) 
	{
		PartitionFilterThing thingsToAccept(templ, true);
		PartitionFilterPolygonTrigger acceptWithin(trig);
		PartitionFilterSameMapStatus filterMapStatus(obj);

		PartitionFilter *filters[] = { &thingsToAccept, &acceptWithin, &filterMapStatus, NULL };

		bestObj = ThePartitionManager->getClosestObject( obj->getPosition(), REALLY_FAR, FROM_CENTER_2D, filters );
		if( !bestObj ) 
		{
			return;
		}
	}
	else
	{
		ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes( objectType );
		if( objectTypes )
		{
			PartitionFilterPolygonTrigger acceptWithin( trig );
			PartitionFilterSameMapStatus filterMapStatus( obj );

			Coord3D pos = *obj->getPosition();
			Real closestDist;
			Real dist;

			for( Int typeIndex = 0; typeIndex < objectTypes->getListSize(); typeIndex++ )
			{
				AsciiString thisTypeName = objectTypes->getNthInList( typeIndex );
				const ThingTemplate *thisType = TheThingFactory->findTemplate( thisTypeName );
				if( thisType )
				{
					PartitionFilterThing f2( thisType, true );
					PartitionFilter *filters[] = { &f2, &acceptWithin, &filterMapStatus, 0 };

					Object *obj = ThePartitionManager->getClosestObject( &pos, REALLY_FAR, FROM_CENTER_2D, filters, &dist );
					if( obj )
					{
						if( !bestObj || dist < closestDist )
						{
							bestObj = obj;
							closestDist = dist;
						}
					}
				}
			}
		}
	}
	
	ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
	ai->aiMoveToObject( bestObj, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doMoveTeamTowardsNearest */
//-------------------------------------------------------------------------------------------------
// ?doMoveTeamTowardsNearest@ScriptActions@@IAEXABVAsciiString@@0V2@@Z present-unmatched
void ScriptActions::doMoveTeamTowardsNearest( const AsciiString& teamName, const AsciiString& objectType, AsciiString triggerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) 
	{
		return;
	}
	
	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trig) 
	{
		return;
	}

	//Get the first object (to use in the partition filter checks).
	Object *teamObj = NULL;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		teamObj = iter.cur();
		if( teamObj ) 
		{
			AIUpdateInterface *ai = teamObj->getAIUpdateInterface();
			if( ai )
			{
				break;
			}
		}
	}
	if( !teamObj )
	{
		return;
	}

	Coord3D teamPos = *team->getEstimateTeamPosition();
	PartitionFilterSameMapStatus filterMapStatus( teamObj );
	PartitionFilterPolygonTrigger acceptWithin( trig );
	Object *bestObj = NULL;

	const ThingTemplate *templ = TheThingFactory->findTemplate( objectType, FALSE );
	if( templ )
	{
		//Find the closest specified template.
		PartitionFilterThing thingsToAccept( templ, true );
		PartitionFilter *filters[] = { &thingsToAccept, &acceptWithin, &filterMapStatus, NULL };
		bestObj = ThePartitionManager->getClosestObject( &teamPos, REALLY_FAR, FROM_CENTER_2D, filters );
		if (!bestObj) 
		{
			return;
		}
	}
	else
	{
		//Find the closest object within the object template list.
		ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes( objectType );
		if( objectTypes )
		{
			Real closestDist;
			Real dist;
			for( Int typeIndex = 0; typeIndex < objectTypes->getListSize(); typeIndex++ )
			{
				AsciiString thisTypeName = objectTypes->getNthInList( typeIndex );
				const ThingTemplate *thisType = TheThingFactory->findTemplate( thisTypeName );
				if( thisType )
				{
					PartitionFilterThing thingToAccept( thisType, true );
					PartitionFilter *filters[] = { &thingToAccept, &acceptWithin, &filterMapStatus, NULL };
						
					Object *obj = ThePartitionManager->getClosestObject( &teamPos, REALLY_FAR, FROM_CENTER_2D, filters, &dist );
					if( obj )
					{
						if( !bestObj || dist < closestDist )
						{
							bestObj = obj;
							closestDist = dist;
						}
					}
				}
			}
		}
	}
	for( iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
	{
		Object *obj = iter.cur();
		if( !obj )
		{
			return;
		}
		AIUpdateInterface *ai = obj->getAI();
		if( !ai )
		{
			return;
		}
		ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
		ai->aiMoveToObject( bestObj, CMD_FROM_SCRIPT );
	}
}

//-------------------------------------------------------------------------------------------------
/** doUnitReceiveUpgrade */
//-------------------------------------------------------------------------------------------------
// ?doUnitReceiveUpgrade@ScriptActions@@IAEXABVAsciiString@@0@Z
// Body in Code/masm_dumps/ScriptActions_doUnitReceiveUpgrade.asm (exact 117B @ 0x2FE070).

//-------------------------------------------------------------------------------------------------
/** doSkirmishAttackNearestGroupWithValue */
//-------------------------------------------------------------------------------------------------
// ?doSkirmishAttackNearestGroupWithValue@ScriptActions@@IAEXABVAsciiString@@HH@Z present-unmatched
void ScriptActions::doSkirmishAttackNearestGroupWithValue( const AsciiString& teamName, Int comparison, Int value )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();

	if (!player)
		return;

	Coord3D loc;
	Coord3D groupLoc;
	theGroup->getCenter(&groupLoc);
	if (comparison == Parameter::GREATER_EQUAL || comparison == Parameter::GREATER) {
		ThePartitionManager->getNearestGroupWithValue(player->getPlayerIndex(), ALLOW_ENEMIES, VOT_CashValue, 
			&groupLoc, value, true, &loc);
	}

	theGroup->groupAttackMoveToPosition( &loc, NO_MAX_SHOTS_LIMIT, CMD_FROM_SCRIPT );
}

//-------------------------------------------------------------------------------------------------
/** doSkirmishCommandButtonOnMostValuable */
//-------------------------------------------------------------------------------------------------
// ?doSkirmishCommandButtonOnMostValuable@ScriptActions@@IAEXABVAsciiString@@0M_N@Z present-unmatched
void ScriptActions::doSkirmishCommandButtonOnMostValuable( const AsciiString& teamName, const AsciiString& ability, Real range, Bool allTeamMembers)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();
	if (!player)
		return;

	const CommandButton *commandButton = TheControlBar->findCommandButton( ability );
	if( !commandButton ) {
		return;
	}

	Object *srcObj = NULL;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if ( !srcObj ) {
		return;
	}

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES, true);
	PartitionFilterValidCommandButtonTarget f2(srcObj, commandButton, true, CMD_FROM_SCRIPT);
	PartitionFilterSameMapStatus filterMapStatus(srcObj);

	PartitionFilter *filters[] = { &f1, &f2, &filterMapStatus, 0 };
	// @todo: Should we add the group's radius to the range? Seems like a possibility.
	SimpleObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(&pos, range, FROM_CENTER_2D, filters, ITER_SORTED_EXPENSIVE_TO_CHEAP);
	MemoryPoolObjectHolder hold(iter);

	if (iter && iter->first()) {
		theGroup->groupDoCommandButtonAtObject(commandButton, iter->first(), CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamSpinForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doTeamSpinForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doTeamSpinForFramecount( const AsciiString& teamName, Int waitForFrames )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	TheScriptEngine->setSequentialTimer(team, waitForFrames);
}

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNamed */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
// Body in ScriptActions_doTeamUseCommandButtonOnNamed.asm (exact 204B retail @ 0x2F54C0).
// Queue RVA 0x614F9B was INSIDE mislocated NearestKindof MASM claim (INI parser).

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestEnemy */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestEnemy@ScriptActions@@IAEXABVAsciiString@@0@Z
// Body in ScriptActions_doTeamUseCommandButtonOnNearestEnemy.asm (exact 713B retail @ 0x2FB170).
// Queue RVA 0x614F94 was INSIDE mislocated 0x614F8E NearestKindof/INI claim; true body via
// executeAction case order after Named (ILT 0x3085A).

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestGarrisonedBuilding */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestGarrisonedBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonOnNearestGarrisonedBuilding( const AsciiString& teamName, const AsciiString& commandAbility )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if(!commandButton) {
		return;
	}

	Object *srcObj = NULL;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES, true);
	PartitionFilterAcceptByKindOf f2(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	PartitionFilterGarrisonable f3(true);
	PartitionFilterValidCommandButtonTarget f4(srcObj, commandButton, true, CMD_FROM_SCRIPT);
	PartitionFilterSameMapStatus filterMapStatus(srcObj);

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilter *filters[] = { &f1, &f2, &f3, &f4, &filterMapStatus, 0 };
	Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters);
	if (!obj) {
		return;
	}

	// already been checked for validity
	theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestKindof */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestKindof@ScriptActions@@IAEXABVAsciiString@@0H@Z
// Body in ScriptActions_doTeamUseCommandButtonOnNearestKindof.asm (exact 496B retail).

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestBuilding */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestBuilding@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonOnNearestBuilding( const AsciiString& teamName, const AsciiString& commandAbility )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = NULL;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES, true);
	PartitionFilterAcceptByKindOf f2(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	PartitionFilterValidCommandButtonTarget f3(srcObj, commandButton, true, CMD_FROM_SCRIPT);
	PartitionFilterSameMapStatus filterMapStatus(srcObj);

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilter *filters[] = { &f1, &f2, &f3, &filterMapStatus, 0 };
	Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters);
	if (!obj) {
		return;
	}

	// already been checked for validity
	theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestBuildingClass */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestBuildingClass@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonOnNearestBuildingClass( const AsciiString& teamName, const AsciiString& commandAbility, Int kindofBit )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = NULL;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES, true);
	PartitionFilterAcceptByKindOf f2(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	PartitionFilterAcceptByKindOf f3(MAKE_KINDOF_MASK(kindofBit), KINDOFMASK_NONE);
	PartitionFilterValidCommandButtonTarget f4(srcObj, commandButton, true, CMD_FROM_SCRIPT);
	PartitionFilterSameMapStatus filterMapStatus(srcObj);

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilter *filters[] = { &f1, &f2, &f3, &f4, &filterMapStatus, 0 };
	Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters);
	if (!obj) {
		return;
	}

	// already been checked for validity
	theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamUseCommandButtonOnNearestObjectType */
//-------------------------------------------------------------------------------------------------
// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z present-unmatched
void ScriptActions::doTeamUseCommandButtonOnNearestObjectType( const AsciiString& teamName, const AsciiString& commandAbility, const AsciiString& objectType )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = NULL;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	Object *bestObj = NULL;

	//First look for a specific object type (object lists will fail)
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate( objectType, FALSE );
	if( thingTemplate ) 
	{
		PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES | ALLOW_NEUTRAL, true);
		PartitionFilterThing f2(thingTemplate, true);
		PartitionFilterValidCommandButtonTarget f3(srcObj, commandButton, true, CMD_FROM_SCRIPT);
		PartitionFilterSameMapStatus filterMapStatus(srcObj);
		PartitionFilter *filters[] = { &f1, &f2, &f3, &filterMapStatus, 0 };

		Coord3D pos;
		theGroup->getCenter(&pos);

		bestObj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters);
		if( !bestObj ) 
		{
			return;
		}
	}
	else
	{
		ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes( objectType );
		if( objectTypes )
		{
			PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES | ALLOW_NEUTRAL, true);
			PartitionFilterValidCommandButtonTarget f3(srcObj, commandButton, true, CMD_FROM_SCRIPT);
			PartitionFilterSameMapStatus f4(srcObj);

			Coord3D pos;
			theGroup->getCenter(&pos);
			Real closestDist;
			Real dist;

			for( Int typeIndex = 0; typeIndex < objectTypes->getListSize(); typeIndex++ )
			{
				AsciiString thisTypeName = objectTypes->getNthInList( typeIndex );
				const ThingTemplate *thisType = TheThingFactory->findTemplate( thisTypeName );
				if( thisType )
				{
					PartitionFilterThing f2( thisType, true );
					PartitionFilter *filters[] = { &f1, &f2, &f3, &f4, 0 };

					Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters, &dist );
					if( obj )
					{
						if( !bestObj || dist < closestDist )
						{
							bestObj = obj;
							closestDist = dist;
						}
					}
				}
			}
		}
	}

	// already been checked for validity
	theGroup->groupDoCommandButtonAtObject(commandButton, bestObj, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doTeamPartialUseCommandButton */
//-------------------------------------------------------------------------------------------------
// ?doTeamPartialUseCommandButton@ScriptActions@@IAEXMABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamPartialUseCommandButton( Real percentage, const AsciiString& teamName, const AsciiString& commandAbility )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	std::vector<Object *> objList;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();

	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (commandButton->isValidToUseOn(obj, NULL, NULL, CMD_FROM_SCRIPT)) {	
			objList.push_back(obj);
		}
	}
	
	Int numObjs = /*REAL_TO_INT_CEIL*/(percentage / 100.0f * objList.size());
	Int count = 0;
	for (std::vector<Object*>::const_iterator it = objList.begin(); it != objList.end(); ++it)
	{
		Object *obj = (*it);

		if (count >= numObjs) 
			return;

		obj->doCommandButton(commandButton, CMD_FROM_SCRIPT);
		++count;
	}
}

//-------------------------------------------------------------------------------------------------
/** doTeamCaptureNearestUnownedFactionUnit */
//-------------------------------------------------------------------------------------------------
// ?doTeamCaptureNearestUnownedFactionUnit@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamCaptureNearestUnownedFactionUnit( const AsciiString& teamName )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	PartitionFilterPlayerAffiliation f1(team->getControllingPlayer(), ALLOW_ENEMIES | ALLOW_NEUTRAL, true);
	PartitionFilterUnmannedObject f2(true);
	PartitionFilterOnMap filterMapStatus;

	Coord3D pos;
	theGroup->getCenter(&pos);

	PartitionFilter *filters[] = { &f1, &f2, &filterMapStatus, 0 };
	Object *obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, FROM_CENTER_2D, filters);
	if (!obj) {
		return;
	}

	theGroup->groupEnter(obj, CMD_FROM_SCRIPT);
}

//-------------------------------------------------------------------------------------------------
/** doCreateTeamFromCapturedUnits */
//-------------------------------------------------------------------------------------------------
// ?doCreateTeamFromCapturedUnits@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doCreateTeamFromCapturedUnits( const AsciiString& playerName, const AsciiString& teamName )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

}

//-------------------------------------------------------------------------------------------------
// ?doPlayerAddSkillPoints@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doPlayerAddSkillPoints(const AsciiString& playerName, Int delta)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!pPlayer)
		return;
	pPlayer->addSkillPoints(delta);
}

//-------------------------------------------------------------------------------------------------
// ?doPlayerAddRankLevels@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doPlayerAddRankLevels(const AsciiString& playerName, Int delta)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!pPlayer)
		return;
	pPlayer->setRankLevel(pPlayer->getRankLevel() + delta);
}

//-------------------------------------------------------------------------------------------------
// ?doPlayerSetRankLevel@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doPlayerSetRankLevel(const AsciiString& playerName, Int level)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!pPlayer)
		return;
	pPlayer->setRankLevel(level);
}

//-------------------------------------------------------------------------------------------------
// ?doMapSetRankLevelLimit@ScriptActions@@IAEXH@Z
void ScriptActions::doMapSetRankLevelLimit(Int level)
{
	// BFME m_rankLevelLimit at GameLogic+0x110 (ZH packs it earlier).
	struct BfmeGameLogicRankLimit {
		UnsignedByte _pad[0x110];
		Int m_rankLevelLimit;
	};
	if (TheGameLogic)
	{
		if (level < 1)
			level = 1;
		((BfmeGameLogicRankLimit *)TheGameLogic)->m_rankLevelLimit = level;
	}
}

//-------------------------------------------------------------------------------------------------
void ScriptActions::doPlayerGrantScience(const AsciiString& playerName, const AsciiString& scienceName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!pPlayer)
		return;
	ScienceType science = TheScienceStore->getScienceFromInternalName(scienceName);
	if (science == SCIENCE_INVALID)
		return;
	pPlayer->grantScience(science);
}

//-------------------------------------------------------------------------------------------------
void ScriptActions::doPlayerPurchaseScience(const AsciiString& playerName, const AsciiString& scienceName)
{
	Player* pPlayer = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!pPlayer)
		return;
	ScienceType science = TheScienceStore->getScienceFromInternalName(scienceName);
	if (science == SCIENCE_INVALID)
		return;
	pPlayer->attemptToPurchaseScience(science);
}

//-------------------------------------------------------------------------------------------------
void ScriptActions::doPlayerSetScienceAvailability( const AsciiString& playerName, const AsciiString& scienceName, const AsciiString& scienceAvailability )
{
	Player* player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if( player )
	{
		ScienceAvailabilityType saType = player->getScienceAvailabilityTypeFromString( scienceAvailability );
		if( saType != SCIENCE_AVAILABILITY_INVALID )
		{
			ScienceType science = TheScienceStore->getScienceFromInternalName( scienceName );
			if( science != SCIENCE_INVALID )
			{
				player->setScienceAvailability( science, saType );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doTeamEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z present-unmatched
void ScriptActions::doTeamEmoticon(const AsciiString& teamName, const AsciiString& emoticonName, Real duration)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( teamName );
	if( !theTeam ) 
	{
		return;
	}

	AIGroup* theGroup = TheAI->createGroup();
	if( !theGroup ) 
	{
		return;
	}
	theTeam->getTeamAsAIGroup( theGroup );
	
	Int frames = (Int)( duration * LOGICFRAMES_PER_SECOND );
	theGroup->groupSetEmoticon( emoticonName, frames );
}

//-------------------------------------------------------------------------------------------------
// ?doNamedEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z
// Body in Code/masm_dumps/ScriptActions_doNamedEmoticon.asm (exact 66B retail @ 0x2F04F0;
// queue 0x9DE812 was profiler FUN float math, not this action).


//-------------------------------------------------------------------------------------------------
// if addObject, we're adding an object to a list. If not addObject, we're removing the associated 
// object.
//-------------------------------------------------------------------------------------------------
// ?doObjectTypeListMaintenance@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doObjectTypeListMaintenance(const AsciiString& objectList, const AsciiString& objectType, Bool addObject)
{
	TheScriptEngine->doObjectTypeListMaintenance( objectList, objectType, addObject );
}

//-------------------------------------------------------------------------------------------------
void ScriptActions::doRevealMapAtWaypointPermanent(const AsciiString& waypointName, Real radiusToReveal, const AsciiString& playerName, const AsciiString& lookName)
{
	TheScriptEngine->createNamedMapReveal(lookName, waypointName, radiusToReveal, playerName);
	TheScriptEngine->doNamedMapReveal(lookName);
}

//-------------------------------------------------------------------------------------------------
void ScriptActions::doUndoRevealMapAtWaypointPermanent(const AsciiString& lookName)
{
	TheScriptEngine->undoNamedMapReveal(lookName);
	TheScriptEngine->removeNamedMapReveal(lookName);
}

//-------------------------------------------------------------------------------------------------
// ?doEvaEnabledDisabled@ScriptActions@@IAEX_N@Z
void ScriptActions::doEvaEnabledDisabled(Bool setEnabled)
{
	// BFME stores the EVA enabled flag on GameLogic at +0x96 (not TheEva).
	((BfmeGameLogicScriptFields *)TheGameLogic)->m_evaEnabled = setEnabled;
}

//-------------------------------------------------------------------------------------------------
// ?doSetOcclusionMode@ScriptActions@@IAEX_N@Z
void ScriptActions::doSetOcclusionMode(Bool setEnabled)
{
	((BfmeGameLogicScriptFields *)TheGameLogic)->m_showBehindBuildingMarkers = setEnabled;
}

//-------------------------------------------------------------------------------------------------
// ?doSetDrawIconUIMode@ScriptActions@@IAEX_N@Z
void ScriptActions::doSetDrawIconUIMode(Bool setEnabled)
{
	((BfmeGameLogicScriptFields *)TheGameLogic)->m_drawIconUI = setEnabled;
}

//-------------------------------------------------------------------------------------------------
// ?doSetDynamicLODMode@ScriptActions@@IAEX_N@Z
void ScriptActions::doSetDynamicLODMode(Bool setEnabled)
{
	((BfmeGameLogicScriptFields *)TheGameLogic)->m_showDynamicLOD = setEnabled;
}

//-------------------------------------------------------------------------------------------------

// Keep header-inline setter COMDATs alive for existing ledger rows after the
// do* wrappers stopped calling them (address-of forces MSVC 7.1 emission).
static void (GameLogic::* const s_bfmeForceHulkSetterEmit)(Int) =
	&GameLogic::setHulkMaxLifetimeOverride;
static void (GameLogic::* const s_bfmeForceBehindMarkersEmit)(Bool) =
	&GameLogic::setShowBehindBuildingMarkers;
static void (GameLogic::* const s_bfmeForceDrawIconEmit)(Bool) =
	&GameLogic::setDrawIconUI;
static void (GameLogic::* const s_bfmeForceDynamicLODEmit)(Bool) =
	&GameLogic::setShowDynamicLOD;
static void (Radar::* const s_bfmeForceRadarHideEmit)(Bool) = &Radar::hide;
static void (Radar::* const s_bfmeForceRadarForceOnEmit)(Bool) = &Radar::forceOn;
// doTeamAttackNamed moved to MASM — keep AIGroup::groupAttackObject COMDAT
// (matched row claims this TU as its only emitter).
static void (AIGroup::* const s_bfmeForceGroupAttackObjectEmit)(Object *, Int, CommandSourceType) =
	&AIGroup::groupAttackObject;

// ?doOverrideHulkLifetime@ScriptActions@@IAEXM@Z
void ScriptActions::doOverrideHulkLifetime( Real seconds )
{
	// Reload TheGameLogic each arm — retail uses eax then ecx, no cached reg.
	if( seconds < 0.0f )
	{
		// Turn it off.
		((BfmeGameLogicScriptFields *)TheGameLogic)->m_scriptHulkMaxLifetimeOverride = -1;
	}
	else
	{
		// Convert real seconds into frames.
		Int frames = (Int)(seconds * LOGICFRAMES_PER_SECOND);
		((BfmeGameLogicScriptFields *)TheGameLogic)->m_scriptHulkMaxLifetimeOverride = frames;
	}
}

//-------------------------------------------------------------------------------------------------
// MBL CNC3 INCURSION - This is to Have Max camera animation playback
//
void ScriptActions::doC3CameraEnableSlaveMode
(
	const AsciiString& thingTemplateName, 
	const AsciiString& boneName 
)
{
	TheTacticalView->cameraEnableSlaveMode( thingTemplateName, boneName );
}

//-------------------------------------------------------------------------------------------------
// BFME View vtable +0x9c: cameraDisableSlaveMode.
class BfmeViewVtbl_9c {
public:
	virtual void _v9c_0() = 0;
	virtual void _v9c_1() = 0;
	virtual void _v9c_2() = 0;
	virtual void _v9c_3() = 0;
	virtual void _v9c_4() = 0;
	virtual void _v9c_5() = 0;
	virtual void _v9c_6() = 0;
	virtual void _v9c_7() = 0;
	virtual void _v9c_8() = 0;
	virtual void _v9c_9() = 0;
	virtual void _v9c_10() = 0;
	virtual void _v9c_11() = 0;
	virtual void _v9c_12() = 0;
	virtual void _v9c_13() = 0;
	virtual void _v9c_14() = 0;
	virtual void _v9c_15() = 0;
	virtual void _v9c_16() = 0;
	virtual void _v9c_17() = 0;
	virtual void _v9c_18() = 0;
	virtual void _v9c_19() = 0;
	virtual void _v9c_20() = 0;
	virtual void _v9c_21() = 0;
	virtual void _v9c_22() = 0;
	virtual void _v9c_23() = 0;
	virtual void _v9c_24() = 0;
	virtual void _v9c_25() = 0;
	virtual void _v9c_26() = 0;
	virtual void _v9c_27() = 0;
	virtual void _v9c_28() = 0;
	virtual void _v9c_29() = 0;
	virtual void _v9c_30() = 0;
	virtual void _v9c_31() = 0;
	virtual void _v9c_32() = 0;
	virtual void _v9c_33() = 0;
	virtual void _v9c_34() = 0;
	virtual void _v9c_35() = 0;
	virtual void _v9c_36() = 0;
	virtual void _v9c_37() = 0;
	virtual void _v9c_38() = 0;
	virtual void cameraDisableSlaveMode(void) = 0;
};

void ScriptActions::doC3CameraDisableSlaveMode( void )
{
	((BfmeViewVtbl_9c *)TheTacticalView)->cameraDisableSlaveMode();
}

//-------------------------------------------------------------------------------------------------
// WST 11.12.2002 CNC3 INCURSION - This is for New Camera Shake
//
void ScriptActions::doC3CameraShake
( 
	const AsciiString &waypointName, 
	const Real amplitude, 
	const Real duration_seconds, 
	const Real radius 
)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	DEBUG_ASSERTLOG( (way != NULL), ("Camera shake with No Valid Waypoint\n") );
	Coord3D pos = *way->getLocation();

	TheTacticalView->Add_Camera_Shake(pos, radius, duration_seconds, amplitude);
}

//-------------------------------------------------------------------------------------------------
// ?doNamedFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedFaceNamed( const AsciiString &unitName, const AsciiString &faceUnitName )
{
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if( obj ) 
	{
		Object *faceObj = TheScriptEngine->getUnitNamed( faceUnitName );
		if( faceObj )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->clearWaypointQueue();
				obj->leaveGroup();
				ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
				ai->aiFaceObject( faceObj, CMD_FROM_SCRIPT );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doNamedFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doNamedFaceWaypoint( const AsciiString &unitName, const AsciiString &faceWaypointName )
{
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if( obj ) 
	{
		Waypoint *way = TheTerrainLogic->getWaypointByName( faceWaypointName );
		if( way )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->clearWaypointQueue();
				obj->leaveGroup();
				ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
				ai->aiFacePosition( way->getLocation(), CMD_FROM_SCRIPT );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doTeamFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamFaceNamed( const AsciiString &teamName, const AsciiString &faceUnitName )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if( team )
	{
		Object *faceObj = TheScriptEngine->getUnitNamed( faceUnitName );
		if( faceObj )
		{
			DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
			for( iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
			{
				Object *obj = iter.cur();
				if( obj )
				{
					AIUpdateInterface *ai = obj->getAI();
					if( ai )
					{
						ai->clearWaypointQueue();
						obj->leaveGroup();
						ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
						ai->aiFaceObject( faceObj, CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doTeamFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
void ScriptActions::doTeamFaceWaypoint( const AsciiString &teamName, const AsciiString &faceWaypointName )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if( team )
	{
		Waypoint *way = TheTerrainLogic->getWaypointByName( faceWaypointName );
		if( way )
		{
			DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
			for( iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
			{
				Object *obj = iter.cur();
				if( obj )
				{
					AIUpdateInterface *ai = obj->getAI();
					if( ai )
					{
						ai->clearWaypointQueue();
						obj->leaveGroup();
						ai->chooseLocomotorSet( LOCOMOTORSET_NORMAL );
						ai->aiFacePosition( way->getLocation(), CMD_FROM_SCRIPT );
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?doAffectObjectPanelFlagsUnit@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doAffectObjectPanelFlagsUnit(const AsciiString& unitName, const AsciiString& flagName, Bool enable)
{
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if (!obj) {
		return;
	}

	changeObjectPanelFlagForSingleObject(obj, flagName, enable);
}

//-------------------------------------------------------------------------------------------------
// ?doAffectObjectPanelFlagsTeam@ScriptActions@@IAEXABVAsciiString@@0_N@Z present-unmatched
void ScriptActions::doAffectObjectPanelFlagsTeam(const AsciiString& teamName, const AsciiString& flagName, Bool enable)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		changeObjectPanelFlagForSingleObject(obj, flagName, enable);
	}
}

//-------------------------------------------------------------------------------------------------
// ?doAffectPlayerSkillset@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doAffectPlayerSkillset(const AsciiString& playerName, Int skillset)
{
	Player *player = TheScriptEngine->getPlayerFromAsciiString(playerName);
	if (!player) {
		return;
	}

	--skillset;
	player->friend_setSkillset(skillset);
}

//-------------------------------------------------------------------------------------------------
// ?doGuardSupplyCenter@ScriptActions@@IAEXABVAsciiString@@H@Z present-unmatched
void ScriptActions::doGuardSupplyCenter(const AsciiString& teamName, Int supplies)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}
	Player *player = team->getControllingPlayer();
	if (!player) {
		return;
	}

	player->guardSupplyCenter(team, supplies);
}

//-------------------------------------------------------------------------------------------------
// ?doTeamGuardInTunnelNetwork@ScriptActions@@IAEXABVAsciiString@@@Z present-unmatched
void ScriptActions::doTeamGuardInTunnelNetwork(const AsciiString& teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}
	// Have all the members of the team guard at a tunnel network.
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}
		ai->aiGuardTunnelNetwork(GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
	}
}

//-------------------------------------------------------------------------------------------------
// ?doRemoveCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0@Z
// Body in Code/masm_dumps/ScriptActions_doRemoveCommandBarButton.asm
// (exact 463B @ 0x2FC570). Queue RVA 0x2FC632 was INSIDE this function.
// BFME expands ZH: primary CommandSet pass + ThingTemplate+0x294 related sets.

//-------------------------------------------------------------------------------------------------
// ?doAddCommandBarButton@ScriptActions@@IAEXABVAsciiString@@0H@Z present-unmatched
void ScriptActions::doAddCommandBarButton(const AsciiString& buttonName, const AsciiString& objectType, Int slotNum)
{
	const ThingTemplate *templ = TheThingFactory->findTemplate(objectType);
	if (!templ) {
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton( buttonName );
	if (commandButton == NULL)
	{
		// not here. use doRemoveCommandBarButton to remove one.
		return;
	}

	// decrement it, so we can present it as 1-12 for the designers.
	--slotNum;

	if (slotNum < 0 || slotNum >= MAX_COMMANDS_PER_SET)
		return;

	TheGameLogic->setControlBarOverride(templ->friend_getCommandSetString(), slotNum, commandButton);
}

//-------------------------------------------------------------------------------------------------
// ?doAffectSkillPointsModifier@ScriptActions@@IAEXABVAsciiString@@M@Z present-unmatched
void ScriptActions::doAffectSkillPointsModifier(const AsciiString& playerName, Real newModifier)
{
	Player *playerDst = TheScriptEngine->getPlayerFromAsciiString(playerName);

	if (!playerDst) {
		return;
	}

	playerDst->setSkillPointsModifier(newModifier);
		
}

//-------------------------------------------------------------------------------------------------
// BFME View vtable +0x1b8: setGuardBandBias.
class BfmeViewVtbl_1b8 {
public:
	virtual void _v1b8_0() = 0;
	virtual void _v1b8_1() = 0;
	virtual void _v1b8_2() = 0;
	virtual void _v1b8_3() = 0;
	virtual void _v1b8_4() = 0;
	virtual void _v1b8_5() = 0;
	virtual void _v1b8_6() = 0;
	virtual void _v1b8_7() = 0;
	virtual void _v1b8_8() = 0;
	virtual void _v1b8_9() = 0;
	virtual void _v1b8_10() = 0;
	virtual void _v1b8_11() = 0;
	virtual void _v1b8_12() = 0;
	virtual void _v1b8_13() = 0;
	virtual void _v1b8_14() = 0;
	virtual void _v1b8_15() = 0;
	virtual void _v1b8_16() = 0;
	virtual void _v1b8_17() = 0;
	virtual void _v1b8_18() = 0;
	virtual void _v1b8_19() = 0;
	virtual void _v1b8_20() = 0;
	virtual void _v1b8_21() = 0;
	virtual void _v1b8_22() = 0;
	virtual void _v1b8_23() = 0;
	virtual void _v1b8_24() = 0;
	virtual void _v1b8_25() = 0;
	virtual void _v1b8_26() = 0;
	virtual void _v1b8_27() = 0;
	virtual void _v1b8_28() = 0;
	virtual void _v1b8_29() = 0;
	virtual void _v1b8_30() = 0;
	virtual void _v1b8_31() = 0;
	virtual void _v1b8_32() = 0;
	virtual void _v1b8_33() = 0;
	virtual void _v1b8_34() = 0;
	virtual void _v1b8_35() = 0;
	virtual void _v1b8_36() = 0;
	virtual void _v1b8_37() = 0;
	virtual void _v1b8_38() = 0;
	virtual void _v1b8_39() = 0;
	virtual void _v1b8_40() = 0;
	virtual void _v1b8_41() = 0;
	virtual void _v1b8_42() = 0;
	virtual void _v1b8_43() = 0;
	virtual void _v1b8_44() = 0;
	virtual void _v1b8_45() = 0;
	virtual void _v1b8_46() = 0;
	virtual void _v1b8_47() = 0;
	virtual void _v1b8_48() = 0;
	virtual void _v1b8_49() = 0;
	virtual void _v1b8_50() = 0;
	virtual void _v1b8_51() = 0;
	virtual void _v1b8_52() = 0;
	virtual void _v1b8_53() = 0;
	virtual void _v1b8_54() = 0;
	virtual void _v1b8_55() = 0;
	virtual void _v1b8_56() = 0;
	virtual void _v1b8_57() = 0;
	virtual void _v1b8_58() = 0;
	virtual void _v1b8_59() = 0;
	virtual void _v1b8_60() = 0;
	virtual void _v1b8_61() = 0;
	virtual void _v1b8_62() = 0;
	virtual void _v1b8_63() = 0;
	virtual void _v1b8_64() = 0;
	virtual void _v1b8_65() = 0;
	virtual void _v1b8_66() = 0;
	virtual void _v1b8_67() = 0;
	virtual void _v1b8_68() = 0;
	virtual void _v1b8_69() = 0;
	virtual void _v1b8_70() = 0;
	virtual void _v1b8_71() = 0;
	virtual void _v1b8_72() = 0;
	virtual void _v1b8_73() = 0;
	virtual void _v1b8_74() = 0;
	virtual void _v1b8_75() = 0;
	virtual void _v1b8_76() = 0;
	virtual void _v1b8_77() = 0;
	virtual void _v1b8_78() = 0;
	virtual void _v1b8_79() = 0;
	virtual void _v1b8_80() = 0;
	virtual void _v1b8_81() = 0;
	virtual void _v1b8_82() = 0;
	virtual void _v1b8_83() = 0;
	virtual void _v1b8_84() = 0;
	virtual void _v1b8_85() = 0;
	virtual void _v1b8_86() = 0;
	virtual void _v1b8_87() = 0;
	virtual void _v1b8_88() = 0;
	virtual void _v1b8_89() = 0;
	virtual void _v1b8_90() = 0;
	virtual void _v1b8_91() = 0;
	virtual void _v1b8_92() = 0;
	virtual void _v1b8_93() = 0;
	virtual void _v1b8_94() = 0;
	virtual void _v1b8_95() = 0;
	virtual void _v1b8_96() = 0;
	virtual void _v1b8_97() = 0;
	virtual void _v1b8_98() = 0;
	virtual void _v1b8_99() = 0;
	virtual void _v1b8_100() = 0;
	virtual void _v1b8_101() = 0;
	virtual void _v1b8_102() = 0;
	virtual void _v1b8_103() = 0;
	virtual void _v1b8_104() = 0;
	virtual void _v1b8_105() = 0;
	virtual void _v1b8_106() = 0;
	virtual void _v1b8_107() = 0;
	virtual void _v1b8_108() = 0;
	virtual void _v1b8_109() = 0;
	virtual void setGuardBandBias(const Coord2D *gb) = 0;
};

void ScriptActions::doResizeViewGuardband(const Real gbx, const Real gby)
{
	Coord2D newGuardBand;
	newGuardBand.x = gbx;
	newGuardBand.y = gby;
	((BfmeViewVtbl_1b8 *)TheTacticalView)->setGuardBandBias(&newGuardBand);
}

//-------------------------------------------------------------------------------------------------
// ?deleteAllUnmanned@ScriptActions@@IAEXXZ present-unmatched
void ScriptActions::deleteAllUnmanned()
{
	Object *obj = TheGameLogic->getFirstObject();
	while (obj) {
		if (obj->isDisabledByType(DISABLED_UNMANNED))
			TheGameLogic->destroyObject(obj);
		obj = obj->getNextObject();
	}
}

//-------------------------------------------------------------------------------------------------
// ?doEnableOrDisableObjectDifficultyBonuses@ScriptActions@@UAEX_N@Z present-unmatched
void ScriptActions::doEnableOrDisableObjectDifficultyBonuses(Bool enableBonuses)
{
	// Loops over every object in the game, applying bonuses or not.
	Object *obj = TheGameLogic->getFirstObject();
	while (obj) {
		obj->setReceivingDifficultyBonus(enableBonuses);
		obj = obj->getNextObject();
	}

	// notify the script engine of our decision
	TheScriptEngine->setObjectsShouldReceiveDifficultyBonus(enableBonuses);
}

//-------------------------------------------------------------------------------------------------
// BFME packs m_ChooseVictimAlwaysUsesNormal at ScriptEngine+0x17635.
struct BfmeScriptEngineChooseVictim {
	UnsignedByte _pad[0x17635];
	Bool m_ChooseVictimAlwaysUsesNormal;
};

void ScriptActions::doChooseVictimAlwaysUsesNormal(Bool enable)
{
	((BfmeScriptEngineChooseVictim *)TheScriptEngine)->m_ChooseVictimAlwaysUsesNormal = enable;
}



//-------------------------------------------------------------------------------------------------
// ?doNamedSetTrainHeld@ScriptActions@@ present-unmatched
void ScriptActions::doNamedSetTrainHeld( const AsciiString &locoName, const Bool set )
{
	Object *obj = TheScriptEngine->getUnitNamed( locoName );
	if( obj ) 
	{

		static const NameKeyType rrkey = NAMEKEY( "RailroadBehavior" );
		RailroadBehavior *rBehavior = (RailroadBehavior*)obj->findUpdateModule( rrkey );

    if ( rBehavior )
    {
      rBehavior->RailroadBehavior::setHeld( set );
    }
    
	}
}


//-------------------------------------------------------------------------------------------------
/** Execute an action */
//-------------------------------------------------------------------------------------------------
// ?executeAction@ScriptActions@@UAEXPAVScriptAction@@@Z present-unmatched
void ScriptActions::executeAction( ScriptAction *pAction )
{
	switch (pAction->getActionType()) {
		default: 
			DEBUG_CRASH(("Unknown ScriptAction type %d", pAction->getActionType())); return;
		case ScriptAction::DEBUG_MESSAGE_BOX: 
			doDebugMessage(pAction->getParameter(0)->getString(), true);
			return;
		case ScriptAction::DEBUG_STRING: 
			doDebugMessage(pAction->getParameter(0)->getString(), false);
			return;
		case ScriptAction::DAMAGE_MEMBERS_OF_TEAM: 
			doDamageTeamMembers(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;
		case ScriptAction::MOVE_TEAM_TO: 
			doMoveToWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::MOVE_NAMED_UNIT_TO: 
			doNamedMoveToWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_SET_STATE: 
			doSetTeamState(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_FOLLOW_WAYPOINTS: 
			doTeamFollowWaypoints(pAction->getParameter(0)->getString(), 
				pAction->getParameter(1)->getString(), 
				pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::TEAM_FOLLOW_WAYPOINTS_EXACT: 
			doTeamFollowWaypointsExact(pAction->getParameter(0)->getString(), 
				pAction->getParameter(1)->getString(), 
				pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::NAMED_FOLLOW_WAYPOINTS_EXACT: 
			doNamedFollowWaypointsExact(pAction->getParameter(0)->getString(), 
				pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SKIRMISH_FOLLOW_APPROACH_PATH: 
			doTeamFollowSkirmishApproachPath(pAction->getParameter(0)->getString(), 
				pAction->getParameter(1)->getString(), 
				pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::SKIRMISH_MOVE_TO_APPROACH_PATH: 
			doTeamMoveToSkirmishApproachPath(pAction->getParameter(0)->getString(), 
				pAction->getParameter(1)->getString());
			return;
		case ScriptAction::CREATE_REINFORCEMENT_TEAM: 
			doCreateReinforcements(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SKIRMISH_BUILD_BUILDING: 
			doBuildBuilding(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::AI_PLAYER_BUILD_SUPPLY_CENTER: 
			doBuildSupplyCenter(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::AI_PLAYER_BUILD_TYPE_NEAREST_TEAM:
			doBuildObjectNearestTeam( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;
		case ScriptAction::AI_PLAYER_BUILD_UPGRADE: 
			doBuildUpgrade(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SKIRMISH_BUILD_BASE_DEFENSE_FRONT: 
			doBuildBaseDefense(false);
			return;
		case ScriptAction::SKIRMISH_BUILD_BASE_DEFENSE_FLANK: 
			doBuildBaseDefense(true);
			return;
		case ScriptAction::SKIRMISH_BUILD_STRUCTURE_FRONT: 
			doBuildBaseStructure(pAction->getParameter(0)->getString(), false);
			return;
		case ScriptAction::SKIRMISH_BUILD_STRUCTURE_FLANK: 
			doBuildBaseStructure(pAction->getParameter(0)->getString(), true);
			return;
		case ScriptAction::RECRUIT_TEAM: 
			doRecruitTeam(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;
		case ScriptAction::PLAY_SOUND_EFFECT: 
			doPlaySoundEffect(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MOVE_CAMERA_TO: 
			doMoveCameraTo(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal(), pAction->getParameter(4)->getReal());
			return;
		case ScriptAction::SETUP_CAMERA: 
			doSetupCamera(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getString());
			return;
		case ScriptAction::ZOOM_CAMERA: 
			doZoomCamera(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal());
			return;
		case ScriptAction::PITCH_CAMERA:
			doPitchCamera(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal());
			return;
		case ScriptAction::CAMERA_FOLLOW_NAMED:
			doCameraFollowNamed(pAction->getParameter(0)->getString(), (pAction->getParameter(1) && pAction->getParameter(1)->getInt() != 0));
			return;
		case ScriptAction::CAMERA_STOP_FOLLOW:
			doStopCameraFollowUnit();
			return;
		case ScriptAction::OVERSIZE_TERRAIN:  
			doOversizeTheTerrain(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::CAMERA_MOD_LOOK_TOWARD: 
			doModCameraLookToward(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::CAMERA_MOD_FINAL_LOOK_TOWARD: 
			doModCameraFinalLookToward(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MOVE_CAMERA_ALONG_WAYPOINT_PATH: 
			doMoveCameraAlongWaypointPath(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal(), pAction->getParameter(4)->getReal());
			return;
		case ScriptAction::ROTATE_CAMERA: 
			doRotateCamera(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal());
			return;
		case ScriptAction::CAMERA_LOOK_TOWARD_OBJECT:
			doRotateCameraTowardObject(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal(), pAction->getParameter(4)->getReal());
			return;
		case ScriptAction::CAMERA_LOOK_TOWARD_WAYPOINT:
			doRotateCameraTowardWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal(), pAction->getParameter(4)->getInt());
			return;
		case ScriptAction::RESET_CAMERA: 
			doResetCamera(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal());
			return;
		case ScriptAction::MOVE_CAMERA_TO_SELECTION: 
			doModCameraMoveToSelection();
			return;
		case ScriptAction::CAMERA_MOD_FREEZE_TIME: 
			TheTacticalView->cameraModFreezeTime();
			return;
		case ScriptAction::CAMERA_MOD_FREEZE_ANGLE: 
			TheTacticalView->cameraModFreezeAngle();
			return;
		case ScriptAction::CAMERA_MOD_SET_FINAL_ZOOM: 
			TheTacticalView->cameraModFinalZoom(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal());
			return;
		case ScriptAction::CAMERA_MOD_SET_FINAL_PITCH: 
			TheTacticalView->cameraModFinalPitch(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal());
			return;
		case ScriptAction::CAMERA_MOD_SET_FINAL_SPEED_MULTIPLIER: 
			TheTacticalView->cameraModFinalTimeMultiplier(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::CAMERA_MOD_SET_ROLLING_AVERAGE: 
			TheTacticalView->cameraModRollingAverage(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::SET_VISUAL_SPEED_MULTIPLIER: 
			TheTacticalView->setTimeMultiplier(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::SUSPEND_BACKGROUND_SOUNDS:
			TheAudio->pauseAudio(AudioAffect_Sound);
			return;
		case ScriptAction::RESUME_BACKGROUND_SOUNDS: 
			TheAudio->resumeAudio(AudioAffect_Sound);
			return;
		case ScriptAction::PLAY_SOUND_EFFECT_AT: 
			doPlaySoundEffectAt(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SET_INFANTRY_LIGHTING_OVERRIDE:
			doSetInfantryLightingOverride(pAction->getParameter(0)->getReal());
			return;
		case ScriptAction::RESET_INFANTRY_LIGHTING_OVERRIDE:
			doSetInfantryLightingOverride(-1.0f);
			return;
		case ScriptAction::QUICKVICTORY:
			doQuickVictory();
			return;
		case ScriptAction::VICTORY:
			doVictory();
			return;
		case ScriptAction::DEFEAT:
			doDefeat();
			return;
		case ScriptAction::LOCALDEFEAT:
			doLocalDefeat();
			return;
		case ScriptAction::CREATE_OBJECT:
		{
			Coord3D pos;
			pAction->getParameter(2)->getCoord3D(&pos);
			doCreateObject( m_unnamedUnit, pAction->getParameter(0)->getString(),  pAction->getParameter(1)->getString(), &pos, pAction->getParameter(3)->getReal() );
			return;
		}

		case ScriptAction::TEAM_ATTACK_TEAM:
			doAttack( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::NAMED_ATTACK_NAMED:
			doNamedAttack( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::CREATE_NAMED_ON_TEAM_AT_WAYPOINT:
			createUnitOnTeamAt( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString(), pAction->getParameter(3)->getString());
			return;
		case ScriptAction::CREATE_UNNAMED_ON_TEAM_AT_WAYPOINT:
			createUnitOnTeamAt( AsciiString::TheEmptyString, pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case ScriptAction::NAMED_APPLY_ATTACK_PRIORITY_SET:
			updateNamedAttackPrioritySet(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_APPLY_ATTACK_PRIORITY_SET:
			updateTeamAttackPrioritySet(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SET_BASE_CONSTRUCTION_SPEED:
			updateBaseConstructionSpeed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_SET_ATTITUDE:
			updateNamedSetAttitude(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::TEAM_SET_ATTITUDE:
			updateTeamSetAttitude(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_SET_REPULSOR:
			doNamedSetRepulsor(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::TEAM_SET_REPULSOR:
			doTeamSetRepulsor(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_ATTACK_AREA:
			doNamedAttackArea(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_ATTACK_TEAM:
			doNamedAttackTeam(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ATTACK_AREA:
			doTeamAttackArea(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ATTACK_NAMED:
			doTeamAttackNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_LOAD_TRANSPORTS:
			doLoadAllTransports(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::NAMED_ENTER_NAMED:
			doNamedEnterNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ENTER_NAMED:
			doTeamEnterNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_EXIT_ALL:
			doNamedExitAll(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_EXIT_ALL:
			doTeamExitAll(pAction->getParameter(0)->getString());
			return;
    case ScriptAction::NAMED_SET_EVAC_LEFT_OR_RIGHT:
      doNamedSetGarrisonEvacDisposition(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
      return;
		case ScriptAction::NAMED_FOLLOW_WAYPOINTS:
			doNamedFollowWaypoints(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_GUARD:
			doNamedGuard(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_GUARD:
			doTeamGuard(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_GUARD_POSITION:
			doTeamGuardPosition(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_GUARD_OBJECT:
			doTeamGuardObject(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_GUARD_AREA:
			doTeamGuardArea(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_HUNT:
			doNamedHunt(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_HUNT:
			doTeamHunt(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_HUNT_WITH_COMMAND_BUTTON:
			doTeamHuntWithCommandButton(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_HUNT:
			doPlayerHunt(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_SELL_EVERYTHING:
			doPlayerSellEverything(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_DISABLE_BASE_CONSTRUCTION:
			doPlayerDisableBaseConstruction(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_DISABLE_FACTORIES:
			doPlayerDisableFactories(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_DISABLE_UNIT_CONSTRUCTION:
			doPlayerDisableUnitConstruction(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_ENABLE_BASE_CONSTRUCTION:
			doPlayerEnableBaseConstruction(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_ENABLE_FACTORIES:
			doPlayerEnableFactories(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::PLAYER_REPAIR_NAMED_STRUCTURE:
			doPlayerRepairStructure(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::PLAYER_ENABLE_UNIT_CONSTRUCTION:
			doPlayerEnableUnitConstruction(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::CAMERA_MOVE_HOME:
			doCameraMoveHome();
			return;
		case ScriptAction::BUILD_TEAM:
			doBuildTeam(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::NAMED_DAMAGE:
			doNamedDamage(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_DELETE:
			doNamedDelete(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_DELETE:
			doTeamDelete(pAction->getParameter(0)->getString(), FALSE);
			return;
		case ScriptAction::TEAM_DELETE_LIVING:
			doTeamDelete(pAction->getParameter(0)->getString(), TRUE);
			return;
		case ScriptAction::TEAM_WANDER:
			doTeamWander(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_WANDER_IN_PLACE:
			doTeamWanderInPlace(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_INCREASE_PRIORITY:
			doTeamIncreasePriority(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_DECREASE_PRIORITY:
			doTeamDecreasePriority(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_PANIC:
			doTeamPanic(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_KILL:
			doNamedKill(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_KILL:
			doTeamKill(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_KILL:
			doPlayerKill(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::DISPLAY_TEXT:
			doDisplayText(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::DISPLAY_CINEMATIC_TEXT:
			doDisplayCinematicText(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(),
				                     pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::DEBUG_CRASH_BOX:
#if defined(_DEBUG) || defined(_INTERNAL)
			{
				const char* MSG = "Your Script requested the following message be displayed:\n\n";
				const char* MSG2 = "\n\nTHIS IS NOT A BUG. DO NOT REPORT IT.";
				DEBUG_CRASH(("%s%s%s\n",MSG,pAction->getParameter(0)->getString().str(),MSG2));
			}
#endif
			return;
		case ScriptAction::INGAME_POPUP_MESSAGE:
			doInGamePopupMessage(pAction->getParameter(0)->getString(),pAction->getParameter(1)->getInt(),
													pAction->getParameter(2)->getInt(), pAction->getParameter(3)->getInt(),
													pAction->getParameter(4)->getInt() );
			return;
		case ScriptAction::CAMEO_FLASH:
			doCameoFlash(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_FLASH:
			doNamedFlash(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), NULL);
			return;
		case ScriptAction::TEAM_FLASH:
			doTeamFlash(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), NULL);
			return;
		case ScriptAction::NAMED_FLASH_WHITE:
			{
				RGBColor c;
				c.red = c.green = c.blue = 1.0f;
				doNamedFlash(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), &c);
			}
			return;
		case ScriptAction::NAMED_CUSTOM_COLOR:
			{
				doNamedCustomColor(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			}
			return;
		case ScriptAction::TEAM_FLASH_WHITE:
			{
				RGBColor c;
				c.red = c.green = c.blue = 1.0f;
				doTeamFlash(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), &c);
			}
			return;
		case ScriptAction::MOVIE_PLAY_FULLSCREEN:
			doMoviePlayFullScreen(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MOVIE_PLAY_RADAR:
			doMoviePlayRadar(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::SOUND_PLAY_NAMED:
			doSoundPlayFromNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::SPEECH_PLAY:
			doSpeechPlay(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::PLAYER_TRANSFER_OWNERSHIP_PLAYER:
			doPlayerTransferAssetsToPlayer(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_TRANSFER_OWNERSHIP_PLAYER:
			doNamedTransferAssetsToPlayer(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_EXCLUDE_FROM_SCORE_SCREEN:
			excludePlayerFromScoreScreen(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::ENABLE_SCORING:
			enableScoring(TRUE);
			return;
		case ScriptAction::DISABLE_SCORING:
			enableScoring(FALSE);
			return;
		case ScriptAction::PLAYER_RELATES_PLAYER:
			updatePlayerRelationTowardPlayer(pAction->getParameter(0)->getString(), pAction->getParameter(2)->getInt(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::RADAR_CREATE_EVENT:
		{
			Coord3D pos;
			pAction->getParameter(0)->getCoord3D(&pos);
			doRadarCreateEvent(&pos, pAction->getParameter(1)->getInt());
			return;
		}
		case ScriptAction::OBJECT_CREATE_RADAR_EVENT:
			doObjectRadarCreateEvent(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::TEAM_CREATE_RADAR_EVENT:
			doTeamRadarCreateEvent(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::RADAR_DISABLE:
			doRadarDisable();
			return;
		case ScriptAction::RADAR_ENABLE:
			doRadarEnable();
			return;
		case ScriptAction::NAMED_SET_STEALTH_ENABLED:
			doNamedEnableStealth(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::TEAM_SET_STEALTH_ENABLED:
			doTeamEnableStealth(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::NAMED_SET_UNMANNED_STATUS:
			doNamedSetUnmanned(pAction->getParameter(0)->getString() );
			return;
		case ScriptAction::TEAM_SET_UNMANNED_STATUS:
			doTeamSetUnmanned(pAction->getParameter(0)->getString() );
			return;
		case ScriptAction::NAMED_SET_BOOBYTRAPPED:
			doNamedSetBoobytrapped( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::TEAM_SET_BOOBYTRAPPED:
			doTeamSetBoobytrapped( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;
		case ScriptAction::MAP_REVEAL_AT_WAYPOINT:
			doRevealMapAtWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::MAP_SHROUD_AT_WAYPOINT:
			doShroudMapAtWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::MAP_REVEAL_ALL:
			doRevealMapEntire(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MAP_REVEAL_ALL_PERM:
			doRevealMapEntirePermanently(TRUE, pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MAP_REVEAL_ALL_UNDO_PERM:
			doRevealMapEntirePermanently(FALSE, pAction->getParameter(0)->getString());
			return;
		case ScriptAction::MAP_SHROUD_ALL:
			doShroudMapEntire(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_AVAILABLE_FOR_RECRUITMENT:
			doTeamAvailableForRecruitment(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::TEAM_COLLECT_NEARBY_FOR_TEAM:
			doCollectNearbyForTeam(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_MERGE_INTO_TEAM:
			doMergeTeamIntoTeam(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::IDLE_ALL_UNITS:
			doIdleAllPlayerUnits(AsciiString::TheEmptyString);
			return;
		case ScriptAction::RESUME_SUPPLY_TRUCKING:
			doResumeSupplyTruckingForIdleUnits(AsciiString::TheEmptyString);
			return;
		case ScriptAction::DISABLE_INPUT:
			doDisableInput();
			return;
		case ScriptAction::ENABLE_INPUT:
			doEnableInput();
			return;
		case ScriptAction::DISABLE_BORDER_SHROUD:
			doSetBorderShroud(FALSE);
			return;
		case ScriptAction::ENABLE_BORDER_SHROUD:
			doSetBorderShroud(TRUE);
			return;
		case ScriptAction::SOUND_AMBIENT_PAUSE:
			doAmbientSoundsPause(true);
			return;
		case ScriptAction::SOUND_AMBIENT_RESUME:
			doAmbientSoundsPause(false);
			return;
		case ScriptAction::MUSIC_SET_TRACK:
			doMusicTrackChange(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::TEAM_GARRISON_SPECIFIC_BUILDING:
			doTeamGarrisonSpecificBuilding(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::EXIT_SPECIFIC_BUILDING:
			doExitSpecificBuilding(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_GARRISON_NEAREST_BUILDING:
			doTeamGarrisonNearestBuilding(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::TEAM_EXIT_ALL_BUILDINGS:
			doTeamExitAllBuildings(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::NAMED_GARRISON_SPECIFIC_BUILDING:
			doUnitGarrisonSpecificBuilding(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::NAMED_GARRISON_NEAREST_BUILDING:
			doUnitGarrisonNearestBuilding(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::NAMED_EXIT_BUILDING:
			doUnitExitBuilding(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_GARRISON_ALL_BUILDINGS:
			doPlayerGarrisonAllBuildings(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_EXIT_ALL_BUILDINGS:
			doPlayerExitAllBuildings(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::CAMERA_LETTERBOX_BEGIN:
			doLetterBoxMode(true);
			return;
		case ScriptAction::CAMERA_LETTERBOX_END:
			doLetterBoxMode(false);
			return;
		case ScriptAction::CAMERA_BW_MODE_BEGIN:
			doBlackWhiteMode(true, pAction->getParameter(0) ? pAction->getParameter(0)->getInt() : 0);
			return;
		case ScriptAction::CAMERA_BW_MODE_END:
			doBlackWhiteMode(false, pAction->getParameter(0) ? pAction->getParameter(0)->getInt() : 0);
			return;
		case ScriptAction::DRAW_SKYBOX_BEGIN:
			doSkyBox(true);
			return;
		case ScriptAction::DRAW_SKYBOX_END:
			doSkyBox(false);
			return;
		case ScriptAction::SHOW_WEATHER:
			doWeather(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::CAMERA_MOTION_BLUR:
			doCameraMotionBlur(pAction->getParameter(0)->getInt(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::CAMERA_MOTION_BLUR_JUMP:
			doCameraMotionBlurJump(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::CAMERA_MOTION_BLUR_FOLLOW:
			TheTacticalView->setViewFilterMode((enum FilterModes)(FM_VIEW_MB_PAN_ALPHA+pAction->getParameter(0)->getInt())); 						 
			TheTacticalView->setViewFilter(FT_VIEW_MOTION_BLUR_FILTER);
			return;
		case ScriptAction::CAMERA_MOTION_BLUR_END_FOLLOW:
			TheTacticalView->setViewFilterMode(FM_VIEW_MB_END_PAN_ALPHA); 						 
			TheTacticalView->setViewFilter(FT_VIEW_MOTION_BLUR_FILTER);
			return;
		case ScriptAction::FREEZE_TIME:
			doFreezeTime();
			return;
		case ScriptAction::UNFREEZE_TIME:
			doUnfreezeTime();
			return;
		case ScriptAction::SHOW_MILITARY_CAPTION:
			doMilitaryCaption(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::CAMERA_SET_AUDIBLE_DISTANCE:
			doCameraSetAudibleDistance(pAction->getParameter(0)->getReal());
			return;
		case ScriptAction::SET_STOPPING_DISTANCE:
			doSetStoppingDistance(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;
		case ScriptAction::SET_FPS_LIMIT:
			if (!pAction->getParameter(0)->getInt())
			{
				TheGameEngine->setFramesPerSecondLimit(TheGlobalData->m_framesPerSecondLimit);
			}
			else
			{
				TheGameEngine->setFramesPerSecondLimit(pAction->getParameter(0)->getInt());
			}
			// Setting the fps limit doesn't do much good if we don't use it.  jba.
			TheWritableGlobalData->m_useFpsLimit = true; 
			return;
			
		case ScriptAction::DISABLE_SPECIAL_POWER_DISPLAY:
			doDisableSpecialPowerDisplay();
			return;

		case ScriptAction::ENABLE_SPECIAL_POWER_DISPLAY:
			doEnableSpecialPowerDisplay();
			return;

		case ScriptAction::NAMED_HIDE_SPECIAL_POWER_DISPLAY:
			doNamedHideSpecialPowerDisplay(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::NAMED_SHOW_SPECIAL_POWER_DISPLAY:
			doNamedShowSpecialPowerDisplay(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::NAMED_SET_STOPPING_DISTANCE:
			doNamedSetStoppingDistance(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;

		case ScriptAction::NAMED_SET_HELD:
			doNamedSetHeld(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::MUSIC_SET_VOLUME:
			doAudioSetVolume(AudioAffect_Music, pAction->getParameter(0)->getReal());
			return;

		case ScriptAction::SOUND_SET_VOLUME:
			doAudioSetVolume((AudioAffect)(AudioAffect_Sound | AudioAffect_Sound3D), pAction->getParameter(0)->getReal());
			return;

		case ScriptAction::SPEECH_SET_VOLUME:
			doAudioSetVolume(AudioAffect_Speech, pAction->getParameter(0)->getReal());
			return;

		case ScriptAction::TEAM_TRANSFER_TO_PLAYER:
			doTransferTeamToPlayer(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_SET_MONEY:
			doSetMoney(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::PLAYER_GIVE_MONEY:
			doGiveMoney(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::DISPLAY_COUNTDOWN_TIMER:
			doDisplayCountdownTimer(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;

		case ScriptAction::HIDE_COUNTDOWN_TIMER:
			doHideCountdownTimer(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::DISPLAY_COUNTER:
			doDisplayCounter(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;

		case ScriptAction::HIDE_COUNTER:
			doHideCounter(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::DISABLE_COUNTDOWN_TIMER_DISPLAY:
			doDisableCountdownTimerDisplay();
			return;

		case ScriptAction::ENABLE_COUNTDOWN_TIMER_DISPLAY:
			doEnableCountdownTimerDisplay();
			return;

		case ScriptAction::NAMED_STOP_SPECIAL_POWER_COUNTDOWN:
			doNamedStopSpecialPowerCountdown(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), TRUE);
			return;

		case ScriptAction::NAMED_START_SPECIAL_POWER_COUNTDOWN:
			doNamedStopSpecialPowerCountdown(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), FALSE);
			return;

		case ScriptAction::NAMED_SET_SPECIAL_POWER_COUNTDOWN:
			doNamedSetSpecialPowerCountdown(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::NAMED_ADD_SPECIAL_POWER_COUNTDOWN:
			doNamedAddSpecialPowerCountdown(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::NAMED_FIRE_SPECIAL_POWER_AT_WAYPOINT:
			doNamedFireSpecialPowerAtWaypoint(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;

		case ScriptAction::SKIRMISH_FIRE_SPECIAL_POWER_AT_MOST_COST:
			doSkirmishFireSpecialPowerAtMostCost(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;

		case ScriptAction::NAMED_FIRE_SPECIAL_POWER_AT_NAMED:
			doNamedFireSpecialPowerAtNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;

		case ScriptAction::REFRESH_RADAR:
			doRadarRefresh();
			return;
		
		case ScriptAction::NAMED_STOP:
			doNamedStop(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::TEAM_STOP:
			doTeamStop(pAction->getParameter(0)->getString(), FALSE);
			return;

		case ScriptAction::TEAM_STOP_AND_DISBAND:
			doTeamStop(pAction->getParameter(0)->getString(), TRUE);
			return;

		case ScriptAction::CAMERA_TETHER_NAMED: 
			doCameraTetherNamed(pAction->getParameter(0)->getString(), (Bool)(pAction->getParameter(1)->getInt()), pAction->getParameter(2)->getReal());
			return;

		case ScriptAction::CAMERA_STOP_TETHER_NAMED: 
			doCameraStopTetherNamed();
			return;

		case ScriptAction::CAMERA_SET_DEFAULT: 
			doCameraSetDefault(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getReal());
			return;

		case ScriptAction::TEAM_SET_OVERRIDE_RELATION_TO_TEAM:
			doTeamSetOverrideRelationToTeam(pAction->getParameter(0)->getString(),		// first team
									pAction->getParameter(1)->getString(),		// second team
									pAction->getParameter(2)->getInt());				// relation (ENEMIES, etc) 
			return;

		case ScriptAction::TEAM_REMOVE_OVERRIDE_RELATION_TO_TEAM:
			doTeamRemoveOverrideRelationToTeam(pAction->getParameter(0)->getString(),		// first team
									pAction->getParameter(1)->getString());		// second team
			return;

		case ScriptAction::TEAM_REMOVE_ALL_OVERRIDE_RELATIONS:
			doTeamRemoveAllOverrideRelations(pAction->getParameter(0)->getString());		// first team
			return;

		case ScriptAction::TEAM_SET_OVERRIDE_RELATION_TO_PLAYER:
			doTeamSetOverrideRelationToPlayer(pAction->getParameter(0)->getString(),		// first team
									pAction->getParameter(1)->getString(),			// second player
									pAction->getParameter(2)->getInt());				// relation (ENEMIES, etc) 
			return;

		case ScriptAction::TEAM_REMOVE_OVERRIDE_RELATION_TO_PLAYER:
			doTeamRemoveOverrideRelationToPlayer(pAction->getParameter(0)->getString(),		// first team
									pAction->getParameter(1)->getString());		// second player
			return;

		case ScriptAction::PLAYER_SET_OVERRIDE_RELATION_TO_TEAM:
			doPlayerSetOverrideRelationToTeam(pAction->getParameter(0)->getString(),		// first player
									pAction->getParameter(1)->getString(),		// second team
									pAction->getParameter(2)->getInt());				// relation (ENEMIES, etc) 
			return;

		case ScriptAction::PLAYER_REMOVE_OVERRIDE_RELATION_TO_TEAM:
			doPlayerRemoveOverrideRelationToTeam(pAction->getParameter(0)->getString(),		// first player
									pAction->getParameter(1)->getString());		// second team
			return;

		case ScriptAction::NAMED_FIRE_WEAPON_FOLLOWING_WAYPOINT_PATH:
			doNamedFireWeaponFollowingWaypointPath(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;

		case ScriptAction::NAMED_USE_COMMANDBUTTON_ABILITY:
			doNamedUseCommandButtonAbility( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;

		case ScriptAction::NAMED_USE_COMMANDBUTTON_ABILITY_ON_NAMED:
			doNamedUseCommandButtonAbilityOnNamed( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;

		case ScriptAction::NAMED_USE_COMMANDBUTTON_ABILITY_AT_WAYPOINT:
			doNamedUseCommandButtonAbilityAtWaypoint( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;
		
		case ScriptAction::NAMED_USE_COMMANDBUTTON_ABILITY_USING_WAYPOINT_PATH:
			doNamedUseCommandButtonAbilityUsingWaypointPath( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;
		
		case ScriptAction::TEAM_USE_COMMANDBUTTON_ABILITY:
			doTeamUseCommandButtonAbility( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString() );
			return;

		case ScriptAction::TEAM_USE_COMMANDBUTTON_ABILITY_ON_NAMED:
			doTeamUseCommandButtonAbilityOnNamed( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;

		case ScriptAction::TEAM_USE_COMMANDBUTTON_ABILITY_AT_WAYPOINT:
			doTeamUseCommandButtonAbilityAtWaypoint( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString() );
			return;
		
		case ScriptAction::UNIT_EXECUTE_SEQUENTIAL_SCRIPT:
			doUnitStartSequentialScript(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), 0);
			return;

		case ScriptAction::UNIT_EXECUTE_SEQUENTIAL_SCRIPT_LOOPING:
			doUnitStartSequentialScript(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt() - 1);
			return;

		case ScriptAction::UNIT_STOP_SEQUENTIAL_SCRIPT:
			doUnitStopSequentialScript(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::TEAM_EXECUTE_SEQUENTIAL_SCRIPT:
			doTeamStartSequentialScript(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), 0);
			return;

		case ScriptAction::TEAM_EXECUTE_SEQUENTIAL_SCRIPT_LOOPING:
			doTeamStartSequentialScript(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt() - 1);
			return;

		case ScriptAction::TEAM_STOP_SEQUENTIAL_SCRIPT:
			doTeamStopSequentialScript(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::UNIT_GUARD_FOR_FRAMECOUNT:
			doUnitGuardForFramecount(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::UNIT_IDLE_FOR_FRAMECOUNT:
			doUnitIdleForFramecount(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		
		case ScriptAction::TEAM_GUARD_FOR_FRAMECOUNT:
			doTeamIdleForFramecount(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		
		case ScriptAction::TEAM_IDLE_FOR_FRAMECOUNT:
			doTeamIdleForFramecount(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::WATER_CHANGE_HEIGHT:
			doWaterChangeHeight(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;

		case ScriptAction::WATER_CHANGE_HEIGHT_OVER_TIME:
			doWaterChangeHeightOverTime( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(),
																	 pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getReal() );
			return;

		case ScriptAction::MAP_SWITCH_BORDER:
			doBorderSwitch(pAction->getParameter(0)->getInt());
			return;
			
		case ScriptAction::OBJECT_FORCE_SELECT:
			doForceObjectSelection(pAction->getParameter(0)->getString(),
														 pAction->getParameter(1)->getString(),
														 pAction->getParameter(2)->getInt(),
														 pAction->getParameter(3)->getString());
			return;
		case ScriptAction::UNIT_DESTROY_ALL_CONTAINED:
			doDestroyAllContained(pAction->getParameter(0)->getString(), 0);
			return;

		case ScriptAction::RADAR_FORCE_ENABLE:
			doRadarForceEnable();
			return;

		case ScriptAction::RADAR_REVERT_TO_NORMAL:
			doRadarRevertNormal();
			return;

		case ScriptAction::SCREEN_SHAKE:
			doScreenShake( (View::CameraShakeType)pAction->getParameter( 0 )->getInt() );
			return;

		case ScriptAction::TECHTREE_MODIFY_BUILDABILITY_OBJECT:
			doModifyBuildableStatus(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;


		case ScriptAction::SET_CAVE_INDEX:
			doSetCaveIndex(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::WAREHOUSE_SET_VALUE:
			doSetWarehouseValue(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::SOUND_DISABLE_TYPE:
			doSoundEnableType(pAction->getParameter(0)->getString(), false);
			return;

		case ScriptAction::SOUND_ENABLE_TYPE:
			doSoundEnableType(pAction->getParameter(0)->getString(), true);
			return;

		case ScriptAction::SOUND_ENABLE_ALL:
			doSoundEnableType(AsciiString::TheEmptyString, true);
			return;
			
		case ScriptAction::SOUND_REMOVE_ALL_DISABLED:
			doSoundRemoveAllDisabled();
			return;

		case ScriptAction::SOUND_REMOVE_TYPE:
			doSoundRemoveType(pAction->getParameter(0)->getString());
			return;

		case ScriptAction::AUDIO_OVERRIDE_VOLUME_TYPE:
			doSoundOverrideVolume(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;
		case ScriptAction::AUDIO_RESTORE_VOLUME_TYPE:
			doSoundOverrideVolume(pAction->getParameter(0)->getString(), -100.0);
			return;
		case ScriptAction::AUDIO_RESTORE_VOLUME_ALL_TYPE:
			doSoundOverrideVolume(AsciiString::TheEmptyString, -100.0);
			return;

		case ScriptAction::NAMED_SET_TOPPLE_DIRECTION:
		{
			Coord3D dir;
			pAction->getParameter(1)->getCoord3D(&dir);

			doSetToppleDirection(pAction->getParameter(0)->getString(), &dir);
			return;
		}

		case ScriptAction::UNIT_MOVE_TOWARDS_NEAREST_OBJECT_TYPE:
			doMoveUnitTowardsNearest(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;

		case ScriptAction::TEAM_MOVE_TOWARDS_NEAREST_OBJECT_TYPE:
			doMoveTeamTowardsNearest(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;

		case ScriptAction::NAMED_RECEIVE_UPGRADE:
			doUnitReceiveUpgrade(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;

		case ScriptAction::SKIRMISH_ATTACK_NEAREST_GROUP_WITH_VALUE:
			doSkirmishAttackNearestGroupWithValue(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::SKIRMISH_PERFORM_COMMANDBUTTON_ON_MOST_VALUABLE_OBJECT:
			doSkirmishCommandButtonOnMostValuable(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getReal(), pAction->getParameter(3)->getInt());
			return;

		case ScriptAction::SKIRMISH_WAIT_FOR_COMMANDBUTTON_AVAILABLE_ALL:
			// We should never get here.
			DEBUG_CRASH(("\"[Skirmish] Wait for command button available - all\" should never be used outside of Sequential scripts. - jkmcd"));
			return;

		case ScriptAction::SKIRMISH_WAIT_FOR_COMMANDBUTTON_AVAILABLE_PARTIAL:
			// We should never get here.
			DEBUG_CRASH(("\"[Skirmish] Wait for command button available - partial\" should never be used outside of Sequential scripts. - jkmcd"));
			return;

		case ScriptAction::TEAM_WAIT_FOR_NOT_CONTAINED_ALL:
			// We should never get here.
			DEBUG_CRASH(("\"[Team] Wait for team no longer contained - all\" should never be used outside of Sequential scripts. - jkmcd"));
			return;

		case ScriptAction::TEAM_WAIT_FOR_NOT_CONTAINED_PARTIAL:
			// We should never get here.
			DEBUG_CRASH(("\"[Team] Wait for team no longer contained - partial\" should never be used outside of Sequential scripts. - jkmcd"));
			return;

		case ScriptAction::TEAM_SPIN_FOR_FRAMECOUNT:
			doTeamSpinForFramecount( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt() );
			return;

		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NAMED:
			doTeamUseCommandButtonOnNamed(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_UNIT:
			doTeamUseCommandButtonOnNearestEnemy(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_GARRISONED_BUILDING:
			doTeamUseCommandButtonOnNearestGarrisonedBuilding(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_KINDOF:
			doTeamUseCommandButtonOnNearestKindof(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_BUILDING:
			doTeamUseCommandButtonOnNearestBuilding(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_BUILDING_CLASS:
			doTeamUseCommandButtonOnNearestBuildingClass(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;
		case ScriptAction::TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE:
			doTeamUseCommandButtonOnNearestObjectType(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::TEAM_PARTIAL_USE_COMMANDBUTTON:
			doTeamPartialUseCommandButton(pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::TEAM_CAPTURE_NEAREST_UNOWNED_FACTION_UNIT:
			doTeamCaptureNearestUnownedFactionUnit(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::PLAYER_CREATE_TEAM_FROM_CAPTURED_UNITS:
			doCreateTeamFromCapturedUnits(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_ADD_SKILLPOINTS:
			doPlayerAddSkillPoints(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::PLAYER_ADD_RANKLEVEL:
			doPlayerAddRankLevels(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::PLAYER_SET_RANKLEVEL:
			doPlayerSetRankLevel(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;
		case ScriptAction::PLAYER_SET_RANKLEVELLIMIT:
			doMapSetRankLevelLimit(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::PLAYER_GRANT_SCIENCE:
			doPlayerGrantScience(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_PURCHASE_SCIENCE:
			doPlayerPurchaseScience(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;
		case ScriptAction::PLAYER_SCIENCE_AVAILABILITY:
			doPlayerSetScienceAvailability(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString());
			return;
		case ScriptAction::TEAM_SET_EMOTICON:
			doTeamEmoticon( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getReal() );
			return;
		case ScriptAction::NAMED_SET_EMOTICON:
			doNamedEmoticon( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getReal() );
			return;
		case ScriptAction::OBJECTLIST_ADDOBJECTTYPE:
			doObjectTypeListMaintenance(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), TRUE);
			return;
		case ScriptAction::OBJECTLIST_REMOVEOBJECTTYPE:
			doObjectTypeListMaintenance(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), FALSE);
			return;
		case ScriptAction::MAP_REVEAL_PERMANENTLY_AT_WAYPOINT:
			doRevealMapAtWaypointPermanent(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal(), pAction->getParameter(2)->getString(), pAction->getParameter(3)->getString());
			return;
		case ScriptAction::MAP_UNDO_REVEAL_PERMANENTLY_AT_WAYPOINT:
			doUndoRevealMapAtWaypointPermanent(pAction->getParameter(0)->getString());
			return;
		case ScriptAction::EVA_SET_ENABLED_DISABLED:
			doEvaEnabledDisabled(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::OPTIONS_SET_OCCLUSION_MODE:
			doSetOcclusionMode(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::OPTIONS_SET_DRAWICON_UI_MODE:
			doSetDrawIconUIMode(pAction->getParameter(0)->getInt());
			return;
		case ScriptAction::CAMERA_ENABLE_SLAVE_MODE:
			{
				doC3CameraEnableSlaveMode
				(
					pAction->getParameter(0)->getString(),
					pAction->getParameter(1)->getString()
				);
			}
			return;
		case ScriptAction::CAMERA_DISABLE_SLAVE_MODE:
			{
				doC3CameraDisableSlaveMode();
			}
			return;
		case ScriptAction::CAMERA_ADD_SHAKER_AT: // WST 11.12.2002 (MBL)
			{
				doC3CameraShake
				(
					pAction->getParameter(0)->getString(),	// Waypoint name
					pAction->getParameter(1)->getReal(),	// Amplitude
					pAction->getParameter(2)->getReal(),	// Duration in seconds
					pAction->getParameter(3)->getReal()		// Radius
				);
			}
			return;
		case ScriptAction::OPTIONS_SET_PARTICLE_CAP_MODE:
			doSetDynamicLODMode(pAction->getParameter(0)->getInt());
			return;

		case ScriptAction::SCRIPTING_OVERRIDE_HULK_LIFETIME:
			doOverrideHulkLifetime( pAction->getParameter( 0 )->getReal() );
			return;

		case ScriptAction::NAMED_FACE_NAMED:
			doNamedFaceNamed( pAction->getParameter( 0 )->getString(), pAction->getParameter( 1 )->getString() );
			return;

		case ScriptAction::NAMED_FACE_WAYPOINT:
			doNamedFaceWaypoint( pAction->getParameter( 0 )->getString(), pAction->getParameter( 1 )->getString() );
			return;

		case ScriptAction::TEAM_FACE_NAMED:
			doTeamFaceNamed( pAction->getParameter( 0 )->getString(), pAction->getParameter( 1 )->getString() );
			return;

		case ScriptAction::TEAM_FACE_WAYPOINT:
			doTeamFaceWaypoint( pAction->getParameter( 0 )->getString(), pAction->getParameter( 1 )->getString() );
			return;
			
		case ScriptAction::UNIT_AFFECT_OBJECT_PANEL_FLAGS:
			doAffectObjectPanelFlagsUnit(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::TEAM_AFFECT_OBJECT_PANEL_FLAGS:
			doAffectObjectPanelFlagsTeam(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::PLAYER_SELECT_SKILLSET:
			doAffectPlayerSkillset(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::COMMANDBAR_REMOVE_BUTTON_OBJECTTYPE:
			doRemoveCommandBarButton(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString());
			return;

		case ScriptAction::COMMANDBAR_ADD_BUTTON_OBJECTTYPE_SLOT:
			doAddCommandBarButton(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getInt());
			return;

		case ScriptAction::UNIT_SPAWN_NAMED_LOCATION_ORIENTATION:
		{
			Coord3D pos;
			pAction->getParameter(3)->getCoord3D(&pos);
			doCreateObject( pAction->getParameter(0)->getString(), pAction->getParameter(1)->getString(), pAction->getParameter(2)->getString(), &pos, pAction->getParameter(4)->getReal() );
			return;
		}
		
		case ScriptAction::PLAYER_AFFECT_RECEIVING_EXPERIENCE:
			doAffectSkillPointsModifier(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getReal());
			return;

		case ScriptAction::TEAM_GUARD_SUPPLY_CENTER:
			doGuardSupplyCenter(pAction->getParameter(0)->getString(), pAction->getParameter(1)->getInt());
			return;

		case ScriptAction::OBJECT_ALLOW_BONUSES:
			doEnableOrDisableObjectDifficultyBonuses(pAction->getParameter(0)->getInt());
			return;

		case ScriptAction::TEAM_GUARD_IN_TUNNEL_NETWORK:
			doTeamGuardInTunnelNetwork(pAction->getParameter(0)->getString());
			return;
			
		case ScriptAction::RESIZE_VIEW_GUARDBAND:
			doResizeViewGuardband( pAction->getParameter(0)->getReal(), pAction->getParameter(1)->getReal() );
			return;

		case ScriptAction::DELETE_ALL_UNMANNED:
			deleteAllUnmanned();
			return;

		case ScriptAction::CHOOSE_VICTIM_ALWAYS_USES_NORMAL:
			doChooseVictimAlwaysUsesNormal(pAction->getParameter(0)->getInt());
			return;

		case ScriptAction::SET_TRAIN_HELD:
			doNamedSetTrainHeld( pAction->getParameter( 0 )->getString(), (Bool)pAction->getParameter( 1 )->getInt() );
			return;

  	case ScriptAction::ENABLE_OBJECT_SOUND:
 			doEnableObjectSound(pAction->getParameter(0)->getString(), true);
			return;

		case ScriptAction::DISABLE_OBJECT_SOUND:
			doEnableObjectSound(pAction->getParameter(0)->getString(), false);
			return;			

	}  
}
