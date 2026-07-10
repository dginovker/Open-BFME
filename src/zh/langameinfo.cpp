// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: LANGameInfo.cpp //////////////////////////////////////////////////////
// LAN game setup state info
// Author: Matthew D. Campbell, December 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/GameInfoWindow.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetListBox.h"
#include "GameNetwork/LANGameInfo.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "Common/MultiplayerSettings.h"
#include "strtok_r.h"
/*
#include "GameNetwork/LAN.h"
#include "GameNetwork/LANGame.h"
#include "GameNetwork/LANPing.h"
#include "GameNetwork/LANusers.h"
#include "GameNetwork/LANmenus.h"
*/

// Singleton ------------------------------------------

LANGameInfo *TheLANGameInfo = NULL;

// LANGameSlot ----------------------------------------

// ??0LANGameSlot@@QAE@XZ present-unmatched
LANGameSlot::LANGameSlot()
{
	m_lastHeard = 0;
}


// ?getUser@LANGameSlot@@QAEPAVLANPlayer@@XZ present-unmatched
LANPlayer * LANGameSlot::getUser( void )
{
	if (isHuman())
	{
		m_user.setIP(getIP());
		m_user.setLastHeard(getLastHeard());
		m_user.setName(getName());
		m_user.setNext(NULL);
		return &m_user;
	}
	return NULL;
}

// Various tests
// ?isUser@LANGameSlot@@ present-unmatched
Bool LANGameSlot::isUser( LANPlayer *user )
{
	return (user && m_state == SLOT_PLAYER && user->getIP() == getIP());
}

// ?isUser@LANGameSlot@@ present-unmatched
Bool LANGameSlot::isUser( UnicodeString userName )
{
	return (m_state == SLOT_PLAYER && !userName.compareNoCase(getName()));
}

// ?isLocalPlayer@LANGameSlot@@QBE_NXZ present-unmatched
Bool LANGameSlot::isLocalPlayer( void ) const
{
	return isHuman() && TheLAN && TheLAN->GetLocalIP() == getIP();
}

// LANGameInfo ----------------------------------------

// ??0LANGameInfo@@QAE@XZ present-unmatched
LANGameInfo::LANGameInfo()
{
	//Added By Sadullah Nader
	//Initializtions missing and needed
	m_lastHeard = 0;
	m_next = NULL;
	//
	for (Int i = 0; i< MAX_SLOTS; ++i)
		setSlotPointer(i, &m_LANSlot[i]);

	setLocalIP(TheLAN->GetLocalIP());
}

// ?setSlot@LANGameInfo@@QAEXHVLANGameSlot@@@Z present-unmatched
void LANGameInfo::setSlot( Int slotNum, LANGameSlot slotInfo )
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("LANGameInfo::setSlot - Invalid slot number"));
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return;

	m_LANSlot[slotNum] = slotInfo;
	
	if (slotNum == 0)
	{
		m_LANSlot[slotNum].setAccept();
		m_LANSlot[slotNum].setMapAvailability(true);
	}
}

// ?getLANSlot@LANGameInfo@@QAEPAVLANGameSlot@@H@Z present-unmatched
LANGameSlot* LANGameInfo::getLANSlot( Int slotNum )
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("LANGameInfo::getLANSlot - Invalid slot number"));
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return NULL;

	return &m_LANSlot[slotNum];
}

// ?getConstLANSlot@LANGameInfo@@QBEPBVLANGameSlot@@H@Z present-unmatched
const LANGameSlot* LANGameInfo::getConstLANSlot( Int slotNum ) const
{
	DEBUG_ASSERTCRASH( slotNum >= 0 && slotNum < MAX_SLOTS, ("LANGameInfo::getConstLANSlot - Invalid slot number"));
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return NULL;

	return &m_LANSlot[slotNum];
}

// ?getLocalSlotNum@LANGameInfo@@UBEHXZ present-unmatched
Int LANGameInfo::getLocalSlotNum( void ) const
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for local game slot while not in game"));
	if (!m_inGame)
		return -1;

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const LANGameSlot *slot = getConstLANSlot(i);
		if (slot->isLocalPlayer())
			return i;
	}
	return -1;
}

// ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z present-unmatched
Int LANGameInfo::getSlotNum( UnicodeString userName )
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for game slot while not in game"));
	if (!m_inGame)
		return -1;

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		LANGameSlot *slot = getLANSlot(i);
		if (slot->isUser( userName ))
			return i;
	}
	return -1;
}

// ?amIHost@LANGameInfo@@QAE_NXZ present-unmatched
Bool LANGameInfo::amIHost( void )
{
	DEBUG_ASSERTCRASH(m_inGame, ("Looking for game slot while not in game"));
	if (!m_inGame)
		return false;

	return getLANSlot(0)->isLocalPlayer();
}

// ?setMap@LANGameInfo@@QAEXVAsciiString@@@Z present-unmatched
void LANGameInfo::setMap( AsciiString mapName )
{
	GameInfo::setMap(mapName);
}

// ?setSeed@LANGameInfo@@QAEXH@Z present-unmatched
void LANGameInfo::setSeed( Int seed )
{
	GameInfo::setSeed(seed);
}

// ?resetAccepted@LANGameInfo@@UAEXXZ present-unmatched
void LANGameInfo::resetAccepted( void )
{
	if (TheLAN)
	{
		TheLAN->ResetGameStartTimer();
		if (TheLAN->GetMyGame() == this && TheLAN->AmIHost())
			LANEnableStartButton(true);
	}
	for(int i = 0; i< MAX_SLOTS; i++)
	{
		m_LANSlot[i].unAccept();
	}
}
// Misc game-related functionality --------------------


void LANDisplayGameList( GameWindow *gameListbox, LANGameInfo *gameList )
{
	LANGameInfo *selectedPtr = NULL;
	Int selectedIndex = -1;
	Int indexToSelect = -1;
	if (gameListbox)
	{
		GadgetListBoxGetSelected(gameListbox, &selectedIndex);
		
		if (selectedIndex != -1 )
		{
			selectedPtr = (LANGameInfo *)GadgetListBoxGetItemData(gameListbox, selectedIndex, 0);
		}

		GadgetListBoxReset(gameListbox);
		
		while (gameList)
		{
			UnicodeString txtGName;
			txtGName = L"";
			if( gameList->isGameInProgress() )
			{
				txtGName.concat(L"[");
			}
			txtGName.concat(gameList->getPlayerName(0));
			if( gameList->isGameInProgress() )
			{
				txtGName.concat(L"]");
			}
			Int addedIndex = GadgetListBoxAddEntryText(gameListbox, txtGName, (gameList->isGameInProgress())?gameInProgressColor:gameColor, -1, -1);
			GadgetListBoxSetItemData(gameListbox, (void *)gameList, addedIndex, 0 );

			if (selectedPtr == gameList)
				indexToSelect = addedIndex;

			gameList = gameList->getNext();
		}

		if (indexToSelect >= 0)
			GadgetListBoxSetSelected(gameListbox, indexToSelect);
		else
			HideGameInfoWindow(TRUE);
	}
}

AsciiString GenerateGameOptionsString( void )
{
	if(!TheLAN->GetMyGame() || !TheLAN->GetMyGame()->amIHost())
		return AsciiString.TheEmptyString;

	return GameInfoToAsciiString(TheLAN->GetMyGame());
}

Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options)
{
	if (!TheLAN || !game)
		return false;

	Int oldLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
	Bool wasInGame = oldLocalSlotNum >= 0;
//	Int hadMap = wasInGame && game->getSlot(oldLocalSlotNum)->hasMap();
	AsciiString oldMap = game->getMap();
	UnsignedInt oldMapCRC, newMapCRC;
	oldMapCRC = game->getMapCRC();

	std::map<UnicodeString, UnicodeString> oldLogins, oldMachines;
	std::map<UnicodeString, UnicodeString>::iterator mapIt;
	Int i;
	for (i=0; i<MAX_SLOTS; ++i)
	{
		LANGameSlot *slot = game->getLANSlot(i);
		if (slot && slot->isHuman())
		{
			//DEBUG_LOG(("Saving off %ls@%ls for %ls\n", slot->getUser()->getLogin().str(), slot->getUser()->getHost().str(), slot->getName().str()));
			oldLogins[slot->getName()] = slot->getUser()->getLogin();
			oldMachines[slot->getName()] = slot->getUser()->getHost();
		}
	}

	if (ParseAsciiStringToGameInfo(game, options))
	{
		Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
		Bool isInGame = newLocalSlotNum >= 0;
		if (!TheLAN->AmIHost() && isInGame)
		{
//			Int hasMap = game->getSlot(newLocalSlotNum)->hasMap();
			newMapCRC = game->getMapCRC();
			//DEBUG_LOG(("wasInGame:%d isInGame:%d hadMap:%d hasMap:%d oldMap:%s newMap:%s\n", wasInGame, isInGame, hadMap, hasMap, oldMap.str(), game->getMap().str()));
			if ( (oldMapCRC ^ newMapCRC)/*(hasMap ^ hadMap)*/ || (!wasInGame && isInGame) )
			{
				// it changed.  send it
				TheLAN->RequestHasMap();
				lanUpdateSlotList();
				updateGameOptions();
			}
		}
		// clean up LAN users, etc.
		UnsignedInt now = timeGetTime();
		for (i=0; i<MAX_SLOTS; ++i)
		{
			LANGameSlot *slot = game->getLANSlot(i);

			if (slot->isHuman())
			{
				slot->setLastHeard(now);
				mapIt = oldLogins.find(slot->getName());
				if (mapIt != oldLogins.end())
					slot->setLogin(mapIt->second);
				mapIt = oldMachines.find(slot->getName());
				if (mapIt != oldMachines.end())
					slot->setHost(mapIt->second);
				//DEBUG_LOG(("Restored %ls@%ls for %ls\n", slot->getUser()->getLogin().str(), slot->getUser()->getHost().str(), slot->getName().str()));
			}
		}

		return true;
	}

	return false;
}

