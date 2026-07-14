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

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright(C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: GameSounds.cpp
//
// Created:   5/02/01
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Lib/Basetype.h"
#include "Common/GameSounds.h"

#include "Common/AudioEventInfo.h"
#include "Common/AudioEventRTS.h"
#include "Common/AudioRequest.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"

#include "GameLogic/PartitionManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
// ??0SoundManager@@ present-unmatched
SoundManager::SoundManager()
{
	// nada to do
}

//-------------------------------------------------------------------------------------------------
// ??1SoundManager@@ present-unmatched
SoundManager::~SoundManager()
{
	// nada to do
}

//-------------------------------------------------------------------------------------------------
// ?init@SoundManager@@ present-unmatched
void SoundManager::init( void )
{

}

//-------------------------------------------------------------------------------------------------
// ?postProcessLoad@SoundManager@@ present-unmatched
void SoundManager::postProcessLoad()
{
	// The AudioManager should actually be live now, so go ahead and get the info we need from it 
	// here
}

//-------------------------------------------------------------------------------------------------
// ?update@SoundManager@@ present-unmatched
void SoundManager::update( void )
{

}

//-------------------------------------------------------------------------------------------------
// ?reset@SoundManager@@ present-unmatched
void SoundManager::reset( void )
{
	m_numPlaying2DSamples = 0;
	m_numPlaying3DSamples = 0;
}

//-------------------------------------------------------------------------------------------------
// ?loseFocus@SoundManager@@ present-unmatched
void SoundManager::loseFocus( void )
{

}

//-------------------------------------------------------------------------------------------------
// ?regainFocus@SoundManager@@ present-unmatched
void SoundManager::regainFocus( void )
{

}

//-------------------------------------------------------------------------------------------------
// ?setListenerPosition@SoundManager@@ present-unmatched
void SoundManager::setListenerPosition( const Coord3D *position )
{

}

//-------------------------------------------------------------------------------------------------
// ?setViewRadius@SoundManager@@ present-unmatched
void SoundManager::setViewRadius( Real viewRadius )
{

}

//-------------------------------------------------------------------------------------------------
// ?setCameraAudibleDistance@SoundManager@@ present-unmatched
void SoundManager::setCameraAudibleDistance( Real audibleDistance )
{

}

//-------------------------------------------------------------------------------------------------
// ?getCameraAudibleDistance@SoundManager@@ present-unmatched
Real SoundManager::getCameraAudibleDistance( void )
{
	return 1.0f;
}

//-------------------------------------------------------------------------------------------------
// ?addAudioEvent@SoundManager@@ present-unmatched
void SoundManager::addAudioEvent(AudioEventRTS *eventToAdd)
{
	if (m_num2DSamples == 0 && m_num3DSamples == 0) {
		m_num2DSamples = TheAudio->getNum2DSamples();
		m_num3DSamples = TheAudio->getNum3DSamples();
	}

	if (canPlayNow(eventToAdd)) {
#ifdef INTENSIVE_AUDIO_DEBUG
		DEBUG_LOG((" - appended to request list with handle '%d'.\n", (UnsignedInt) eventToAdd->getPlayingHandle()));
#endif
		AudioRequest *audioRequest = TheAudio->allocateAudioRequest( true );
		audioRequest->m_pendingEvent = eventToAdd;
		audioRequest->m_request = AR_Play;
		TheAudio->appendAudioRequest(audioRequest);
	} else {
		TheAudio->releaseAudioEventRTS(eventToAdd);
	}
}

//-------------------------------------------------------------------------------------------------
// ?notifyOf2DSampleStart@SoundManager@@ present-unmatched
void SoundManager::notifyOf2DSampleStart( void )
{
	++m_numPlaying2DSamples;
}

//-------------------------------------------------------------------------------------------------
// ?notifyOf3DSampleStart@SoundManager@@ present-unmatched
void SoundManager::notifyOf3DSampleStart( void )
{
	++m_numPlaying3DSamples;
}

//-------------------------------------------------------------------------------------------------
// ?notifyOf2DSampleCompletion@SoundManager@@ present-unmatched
void SoundManager::notifyOf2DSampleCompletion( void )
{
	if (m_numPlaying2DSamples > 0) {
		--m_numPlaying2DSamples;
	}
}

//-------------------------------------------------------------------------------------------------
// ?notifyOf3DSampleCompletion@SoundManager@@ present-unmatched
void SoundManager::notifyOf3DSampleCompletion( void )
{
	if (m_numPlaying3DSamples > 0) {
		--m_numPlaying3DSamples;
	}
}

//-------------------------------------------------------------------------------------------------
// ?getAvailableSamples@SoundManager@@ present-unmatched
Int SoundManager::getAvailableSamples( void )
{
	return (m_num2DSamples - m_numPlaying2DSamples);
}

//-------------------------------------------------------------------------------------------------
// ?getAvailable3DSamples@SoundManager@@ present-unmatched
Int SoundManager::getAvailable3DSamples( void )
{
	return (m_num3DSamples - m_numPlaying3DSamples);
}

//-------------------------------------------------------------------------------------------------
// ?getFilenameForPlayFromAudioEvent@SoundManager@@ present-unmatched
AsciiString SoundManager::getFilenameForPlayFromAudioEvent( const AudioEventRTS *eventToGetFrom )
{
	return AsciiString::TheEmptyString;
}

//-------------------------------------------------------------------------------------------------
// ?canPlayNow@SoundManager@@ present-unmatched
Bool SoundManager::canPlayNow( AudioEventRTS *event )
{
	Bool retVal = false;
	// 1) Are we muted because we're beyond our maximum distance?
	// 2) Are we shrouded and this is a shroud sound?
	// 3) Are we violating our voice count or are we playing above the limit? (If so, stop now)
	// 4) is there an avaiable channel open?
	// 5) if not, then determine if there is anything of lower priority that we can kill
	// 6) if not, are we an interrupt-sound type?
	// if so, are there any sounds of our type playing right now that we can interrupt?
	// potentially here: Are there any sounds that are playing that are now beyond their distance?
	// if so, kill them and start our sound
	// if not, we're done. Can't play dude.
	
	if( event->isPositionalAudio() && !BitTest( event->getAudioEventInfo()->m_type, ST_GLOBAL) && event->getAudioEventInfo()->m_priority != AP_CRITICAL ) 
	{
		Coord3D distance = *TheAudio->getListenerPosition();
		const Coord3D *pos = event->getCurrentPosition();
		if (pos) 
		{
			distance.sub(pos);
			if (distance.length() >= event->getAudioEventInfo()->m_maxDistance) 
			{
#ifdef INTENSIVE_AUDIO_DEBUG
				DEBUG_LOG(("- culled due to distance (%.2f).\n", distance.length()));
#endif
				return false;
			}
			
			Int localPlayerNdx = ThePlayerList->getLocalPlayer()->getPlayerIndex();
			if( (event->getAudioEventInfo()->m_type & ST_SHROUDED) && 
					 ThePartitionManager->getShroudStatusForPlayer(localPlayerNdx, pos) != CELLSHROUD_CLEAR ) 
			{
#ifdef INTENSIVE_AUDIO_DEBUG
				DEBUG_LOG(("- culled due to shroud.\n"));
#endif
				return false;
			}
		} 
	}

	if (violatesVoice(event)) 
	{
		retVal = isInterrupting(event);
		if (retVal) 
		{
			return true;
		} 
		else 
		{
#ifdef INTENSIVE_AUDIO_DEBUG
		DEBUG_LOG(("- culled due to voice.\n"));
#endif
			return false;
		}
	}
	
	if( TheAudio->doesViolateLimit( event ) )
	{
#ifdef INTENSIVE_AUDIO_DEBUG
		DEBUG_LOG(("- culled due to limit.\n" ));
#endif
		return false;
	}
	else if( isInterrupting( event ) )
	{
		return true;
	}

	if (event->isPositionalAudio()) 
	{
		if (m_numPlaying3DSamples < m_num3DSamples) 
		{
			return true;
		}
#ifdef INTENSIVE_AUDIO_DEBUG
		DEBUG_LOG(("- %d samples playing, %d samples available", m_numPlaying3DSamples, m_num3DSamples));
#endif
	} 
	else 
	{
		// its a UI sound (and thus, 2-D)
		if (m_numPlaying2DSamples < m_num2DSamples) 
		{
			return true;
		}
	}

	if (TheAudio->isPlayingLowerPriority(event)) 
	{
		return true;
	}

	if (isInterrupting(event)) 
	{
		retVal = TheAudio->isPlayingAlready(event);
		if (retVal) 
		{
			return true;
		} 
		else 
		{
#ifdef INTENSIVE_AUDIO_DEBUG
			DEBUG_LOG(("- culled due to no channels available and non-interrupting.\n" ));
#endif
			return false;
		}
	}
#ifdef INTENSIVE_AUDIO_DEBUG
	DEBUG_LOG(("culled due to unavailable channels"));
#endif
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?violatesVoice@SoundManager@@ present-unmatched
Bool SoundManager::violatesVoice( AudioEventRTS *event )
{
	if (event->getAudioEventInfo()->m_type & ST_VOICE) {
		return (event->getObjectID() && TheAudio->isObjectPlayingVoice(event->getObjectID()));
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?isInterrupting@SoundManager@@ present-unmatched
Bool SoundManager::isInterrupting( AudioEventRTS *event )
{
	return event->getAudioEventInfo()->m_control & AC_INTERRUPT;
}