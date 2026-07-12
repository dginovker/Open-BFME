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

// FILE: CampaignManager.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	CampaignManager.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The flow of the campaigns are stored up in here!
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/CampaignManager.h"

#include "Common/INI.h"
#include "Common/Xfer.h"
#include "GameClient/ChallengeGenerals.h"//For TheChallengeGenerals, so I can save it too.
#include "GameClient/GameClient.h"
#include "GameNetwork/GameInfo.h" //For Challenge Info.  It and Skirmish info are in the wrong place it seems.

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
CampaignManager *TheCampaignManager = NULL;


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


const FieldParse CampaignManager::m_campaignFieldParseTable[] = 
{

	{ "Mission",						CampaignManager::parseMissionPart,	NULL, NULL },
	{ "FirstMission",				INI::parseAsciiString,							NULL,	offsetof( Campaign, m_firstMission )  },
	{ "CampaignNameLabel",	INI::parseAsciiString,							NULL, offsetof( Campaign, m_campaignNameLabel ) },
	{ "FinalVictoryMovie",	INI::parseAsciiString,							NULL, offsetof( Campaign, m_finalMovieName ) },
	{ "IsChallengeCampaign",			INI::parseBool,				NULL, offsetof( Campaign, m_isChallengeCampaign ) },
	{ "PlayerFaction",		INI::parseAsciiString,					NULL, offsetof( Campaign, m_playerFactionName ) },

	{ NULL,										NULL,													NULL, 0 }  // keep this last

};

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ?parseCampaignDefinition@INI@@SAXPAV1@@Z present-unmatched
void INI::parseCampaignDefinition( INI *ini )
{
	AsciiString name;
	Campaign *campaign;

	// read the name
	const char* c = ini->getNextToken();
	name.set( c );	

	// find existing item if present
	DEBUG_ASSERTCRASH( TheCampaignManager, ("parseCampaignDefinition: Unable to Get TheCampaignManager\n") );
	if( !TheCampaignManager )
		return;

	// If we have a previously allocated Campaign
	campaign = TheCampaignManager->newCampaign( name );

	// sanity
	DEBUG_ASSERTCRASH( campaign, ("parseCampaignDefinition: Unable to allocate campaign '%s'\n", name.str()) );

	// parse the ini definition
	ini->initFromINI( campaign, TheCampaignManager->getFieldParse() );

}  // end parseCampaignDefinition

//-----------------------------------------------------------------------------
// ??0Campaign@@QAE@XZ present-unmatched
Campaign::Campaign( void ):
	m_isChallengeCampaign(FALSE)
{
	m_missions.clear();
	m_firstMission.clear();
	m_name.clear();
	m_finalMovieName.clear();
}

//-----------------------------------------------------------------------------
// ??1Campaign@@MAE@XZ present-unmatched
Campaign::~Campaign( void )
{
	MissionListIt it = m_missions.begin();
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		it = m_missions.erase( it );
		if(mission)
			mission->deleteInstance();
	}
}

// ?getFinalVictoryMovie@Campaign@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString Campaign::getFinalVictoryMovie( void )
{
	return m_finalMovieName;
}

//-----------------------------------------------------------------------------
// ?newMission@Campaign@@QAEPAVMission@@VAsciiString@@@Z present-unmatched
Mission *Campaign::newMission( AsciiString name )
{
	MissionListIt it;
	it = m_missions.begin();
	name.toLower();
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(name) == 0)
		{
			m_missions.erase( it );
			mission->deleteInstance();
			break;
		}
		else
			++it;
	}
	Mission *newMission = newInstance(Mission);	
	newMission->m_name.set(name);
	m_missions.push_back(newMission);
	return newMission;
}

//-----------------------------------------------------------------------------
// ?getMission@Campaign@@QAEPAVMission@@VAsciiString@@@Z present-unmatched
Mission *Campaign::getMission( AsciiString missionName )
{
	if(missionName.isEmpty())
		return NULL;
	MissionListIt it;
	it = m_missions.begin();	
	// we've reached the end of the campaign
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(missionName) == 0)
			return mission;
		++it;
	}
	DEBUG_ASSERTCRASH(FALSE, ("getMission couldn't find %s", missionName.str()));
	return NULL;
}

//-----------------------------------------------------------------------------
// ?getNextMission@Campaign@@QAEPAVMission@@PAV2@@Z present-unmatched
Mission *Campaign::getNextMission( Mission *current)
{
	AsciiString name;
	//if passed a Null pointer, load the first mission
	if(!current)
	{
		name = m_firstMission;
	}
	else
		name = current->m_nextMission;
	name.toLower();
	MissionListIt it;
	it = m_missions.begin();	
	// we've reached the end of the campaign
	if(name.isEmpty())
		return NULL;
	while(it != m_missions.end())
	{
		Mission *mission = *it;
		if(mission->m_name.compare(name) == 0)
			return mission;
		++it;
	}
//	DEBUG_ASSERTCRASH(FALSE, ("GetNextMission couldn't find %s", current->m_nextMission.str()));
	return NULL;
}


//-----------------------------------------------------------------------------
// ??0CampaignManager@@QAE@XZ present-unmatched
CampaignManager::CampaignManager( void )
{
	m_campaignList.clear();
	m_currentCampaign = NULL;
	m_currentMission = NULL;
	m_victorious = FALSE;
	m_currentRankPoints = 0;
	m_difficulty = DIFFICULTY_NORMAL;
	m_xferChallengeGeneralsPlayerTemplateNum = 0;
}

//-----------------------------------------------------------------------------
// ??1CampaignManager@@QAE@XZ present-unmatched
CampaignManager::~CampaignManager( void )
{
	m_currentCampaign = NULL;
	m_currentMission = NULL;

	CampaignListIt it = m_campaignList.begin();

	while(it != m_campaignList.end())
	{
		Campaign *campaign = *it;
		it = m_campaignList.erase( it );
		if(campaign)
			campaign->deleteInstance();
	}
}

//-----------------------------------------------------------------------------
// ?init@CampaignManager@@QAEXXZ present-unmatched
void CampaignManager::init( void )
{
	INI ini;
	// Read from INI all the CampaignManager
	ini.load( AsciiString( "Data\\INI\\Campaign.ini" ), INI_LOAD_OVERWRITE, NULL );
}

//-----------------------------------------------------------------------------
// ?getCurrentCampaign@CampaignManager@@QAEPAVCampaign@@XZ present-unmatched
Campaign *CampaignManager::getCurrentCampaign( void )
{
	return m_currentCampaign;
}

//-----------------------------------------------------------------------------
// ?getCurrentMission@CampaignManager@@QAEPAVMission@@XZ present-unmatched
Mission *CampaignManager::getCurrentMission( void )
{
	return m_currentMission;
}

//-----------------------------------------------------------------------------
Mission *CampaignManager::gotoNextMission( void )
{
	if (!m_currentCampaign || !m_currentMission)
		return NULL;
	m_currentMission = m_currentCampaign->getNextMission(m_currentMission);
	return m_currentMission;
	
}

//-----------------------------------------------------------------------------
// ?setCampaignAndMission@CampaignManager@@QAEXVAsciiString@@0@Z present-unmatched
void CampaignManager::setCampaignAndMission( AsciiString campaign, AsciiString mission )
{
	if(mission.isEmpty())
	{
		setCampaign(campaign);
		return;
	}
	CampaignListIt it;
	it = m_campaignList.begin();
	campaign.toLower();
	while	( it != m_campaignList.end())
	{
		Campaign *camp = *it;
		if(camp->m_name.compare(campaign) == 0)
		{
			m_currentCampaign = camp;
			m_currentMission = camp->getMission( mission );
			return;
		}
		++it;
	}
}	

//-----------------------------------------------------------------------------
// ?setCampaign@CampaignManager@@QAEXVAsciiString@@@Z present-unmatched
void CampaignManager::setCampaign( AsciiString campaign )
{
	CampaignListIt it;
	it = m_campaignList.begin();
	campaign.toLower();
	while	( it != m_campaignList.end())
	{
		Campaign *camp = *it;
		if(camp->m_name.compare(campaign) == 0)
		{
			m_currentCampaign = camp;
			m_currentMission = camp->getNextMission( NULL );
			return;
		}
		++it;
	}
	// could not find the mission. we are resetting the missions to nothing.
	m_currentCampaign = NULL;
	m_currentMission = NULL;
	m_currentRankPoints = 0;
	m_difficulty = DIFFICULTY_NORMAL;
}

//-----------------------------------------------------------------------------
// ?getCurrentMap@CampaignManager@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString CampaignManager::getCurrentMap( void )
{
	if(!m_currentMission)
		return AsciiString::TheEmptyString;
	
	return m_currentMission->m_mapName;
}

// ------------------------------------------------------------------------------------------------
/** Return the 0 based mission number */
// ------------------------------------------------------------------------------------------------
Int CampaignManager::getCurrentMissionNumber( void )
{
	Int number = INVALID_MISSION_NUMBER;

	if( m_currentCampaign )
	{
		Campaign::MissionListIt it;

		for( it = m_currentCampaign->m_missions.begin(); 
				 it != m_currentCampaign->m_missions.end(); 
				 ++it )
		{

			number++;
			if( *it == m_currentMission )
				return number;
		}
		
	}
	
	return number;

}

//-----------------------------------------------------------------------------
// ?parseMissionPart@CampaignManager@@ present-unmatched
void CampaignManager::parseMissionPart( INI* ini, void *instance, void *store, const void *userData )
{
	static const FieldParse myFieldParse[] = 
		{
			{ "Map",							INI::parseAsciiString,				NULL, offsetof( Mission, m_mapName ) },
			{ "NextMission",			INI::parseAsciiString,				NULL, offsetof( Mission, m_nextMission ) },
			{ "IntroMovie",				INI::parseAsciiString,				NULL, offsetof( Mission, m_movieLabel ) },
			{ "ObjectiveLine0",		INI::parseAsciiString,				NULL, offsetof( Mission, m_missionObjectivesLabel[0] ) },
      { "ObjectiveLine1",		INI::parseAsciiString,				NULL, offsetof( Mission, m_missionObjectivesLabel[1] ) },
			{ "ObjectiveLine2",		INI::parseAsciiString,				NULL, offsetof( Mission, m_missionObjectivesLabel[2] ) },
			{ "ObjectiveLine3",		INI::parseAsciiString,				NULL, offsetof( Mission, m_missionObjectivesLabel[3] ) },
			{ "ObjectiveLine4",		INI::parseAsciiString,				NULL, offsetof( Mission, m_missionObjectivesLabel[4] ) },
			{ "BriefingVoice",		INI::parseAudioEventRTS,			NULL, offsetof( Mission, m_briefingVoice ) },
			{ "UnitNames0",				INI::parseAsciiString,				NULL, offsetof( Mission, m_unitNames[0] ) },
			{ "UnitNames1",				INI::parseAsciiString,				NULL, offsetof( Mission, m_unitNames[1] ) },
			{ "UnitNames2",				INI::parseAsciiString,				NULL, offsetof( Mission, m_unitNames[2] ) },
			{ "GeneralName",			INI::parseAsciiString,			NULL, offsetof( Mission, m_generalName)	},
			{ "LocationNameLabel",INI::parseAsciiString,				NULL, offsetof( Mission, m_locationNameLabel ) },
			{ "VoiceLength",			INI::parseInt ,								NULL, offsetof( Mission, m_voiceLength ) },

			{ NULL,							NULL,											NULL, 0 }  // keep this last
		};
	AsciiString name;
	const char* c = ini->getNextToken();
	name.set( c );	

	Mission *mission = ((Campaign*)instance)->newMission(name );
	ini->initFromINI(mission, myFieldParse);
}
	

//-----------------------------------------------------------------------------
// ?newCampaign@CampaignManager@@QAEPAVCampaign@@VAsciiString@@@Z present-unmatched
Campaign *CampaignManager::newCampaign(AsciiString name)
{
	CampaignListIt it;
	it = m_campaignList.begin();
	name.toLower();
	while(it != m_campaignList.end())
	{
		Campaign *campaign = *it;
		if(campaign->m_name.compare(name) == 0)
		{
			m_campaignList.erase( it );
			campaign->deleteInstance();
			break;
		}
		else
			++it;
	}
	Campaign *newCampaign = newInstance(Campaign);
	newCampaign->m_name.set(name);
	m_campaignList.push_back(newCampaign);
	return newCampaign;
}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info
	* 1: Initial version 
	* 2: Added RankPoints Saving
	* 4: Need to have Challenge info in Mission saves as well as normal saves
*/
// ------------------------------------------------------------------------------------------------
// ?xfer@CampaignManager@@UAEXPAVXfer@@@Z present-unmatched
void CampaignManager::xfer( Xfer *xfer )
{

	// version
	const XferVersion currentVersion = 5;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// current campaign
	AsciiString currentCampaign;
	if( m_currentCampaign )
		currentCampaign = m_currentCampaign->m_name;
	xfer->xferAsciiString( &currentCampaign );
	
	// current mission
	AsciiString currentMission;
	if( m_currentMission )
		currentMission = m_currentMission->m_name;
	xfer->xferAsciiString( &currentMission );

	// version 2 and above has rank points!
	if(version >= 2)
		xfer->xferInt( &m_currentRankPoints );

	if(version >= 3)
		xfer->xferUser( &m_difficulty, sizeof(m_difficulty) );

	// when loading, need to set the current campaign and mission
	if( xfer->getXferMode() == XFER_LOAD )
		setCampaignAndMission( currentCampaign, currentMission );

	if( version >= 4 )
	{
		// The saving of SkirmishInfo in GameStateMap is in the "wrong" place, but I can't move it.
		// We need to ensure this is saved in a mission save as well as a normal save.
		// Singletons are bad.  THis is here because a) it is one of two blocks in a Mission Save
		// b) It is not the block that is loaded for every save to get desc's in populating the saveload window.
		// So it is here.  <sob> I've got nowhere else to go!
		Bool isChallengeCampaign = m_currentCampaign ? m_currentCampaign->m_isChallengeCampaign : FALSE;
		xfer->xferBool(&isChallengeCampaign);

		if( isChallengeCampaign ) 
		{
			if( TheChallengeGameInfo==NULL ) 
			{
				TheChallengeGameInfo = NEW SkirmishGameInfo;
				TheChallengeGameInfo->init();  
				TheChallengeGameInfo->clearSlotList();
				TheChallengeGameInfo->reset();
			}
			xfer->xferSnapshot(TheChallengeGameInfo);
		} 
		else 
		{
			if( TheChallengeGameInfo ) 
			{
				delete TheChallengeGameInfo;
				TheChallengeGameInfo = NULL;
			}
		}
	}

	if( version >= 5 )
	{
		// Even more singleton goodness. TheChallengeGenerals is not a subsystem, nor even a snapshot.
		// I need to know what side I am for use by The Continue and Play Again buttons.  I can only just
		// reach in and save it here.
		Int playerTemplateNum = TheChallengeGenerals->getCurrentPlayerTemplateNum();
		xfer->xferInt(&playerTemplateNum);
		m_xferChallengeGeneralsPlayerTemplateNum = playerTemplateNum;
	}

}  // end xfer

// ?loadPostProcess@CampaignManager@@UAEXXZ present-unmatched
void CampaignManager::loadPostProcess( void )
{
	if(TheChallengeGenerals == NULL)
	{
		DEBUG_CRASH(("TheChallengeGenerals singleton does not exist. This loaded game will not have a working Continue button for GC mode."));
		return;
	}

	TheChallengeGenerals->setCurrentPlayerTemplateNum(m_xferChallengeGeneralsPlayerTemplateNum);
}

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// ??0Mission@@QAE@XZ present-unmatched
Mission::Mission( void )
{
	m_voiceLength = 0;
}

//-----------------------------------------------------------------------------
// ??1Mission@@MAE@XZ present-unmatched
Mission::~Mission( void )
{

}
	
