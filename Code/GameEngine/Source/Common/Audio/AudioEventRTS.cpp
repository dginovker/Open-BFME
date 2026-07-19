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

// FILE: AudioEventRTS.cpp 
/*---------------------------------------------------------------------------*/
/* EA Pacific                                                                */
/* Confidential Information	                                                 */
/* Copyright (C) 2001 - All Rights Reserved                                  */
/* DO NOT DISTRIBUTE                                                         */
/*---------------------------------------------------------------------------*/
/* Project:    RTS3                                                          */
/* File name:  AudioEventRTS.cpp                                             */
/* Created:    John K. McDonald, Jr., 3/21/2002                              */
/* Desc:       AudioEventRTS constructors and assignment operator, etc.      */
/* Revision History:                                                         */
/*		3/21/2002 : Initial creation                                           */
/*---------------------------------------------------------------------------*/
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/AudioEventRTS.h"

#include "Common/AudioEventInfo.h"
#include "Common/AudioRandomValue.h"
#include "Common/AudioSettings.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameSounds.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/Registry.h"

#include "GameLogic/GameLogic.h"	// For getObjectByID
#include "GameLogic/LogicRandomValue.h"
#include "GameLogic/Object.h"

#include "GameClient/Drawable.h"	// For getPosition
#include "GameClient/GameClient.h"	// For getDrawableByID

#ifdef _INTERNAL
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS()
									: m_eventName(AsciiString::TheEmptyString), 
										m_priority(AP_NORMAL), 
										m_volume(-1.0),
										m_timeOfDay(TIME_OF_DAY_AFTERNOON),
										m_ownerType(OT_INVALID),
										m_shouldFade(false),
										m_isLogicalAudio(false),
										m_filenameToLoad(AsciiString::TheEmptyString),
										m_eventInfo(NULL),
										m_playingHandle(0),
										m_killThisHandle(0),
										m_pitchShift(1.0),
										m_volumeShift(0.0),
										m_loopCount(1),
										m_playingAudioIndex(-1),
										m_allCount(0),
										m_playerIndex(-1),
										m_delay(0.0f),
										m_uninterruptable(FALSE)
{
	m_attackName.clear();
	m_decayName.clear();
	m_positionOfAudio.zero();
}

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS( const AsciiString& eventName )
									: m_eventName(eventName), 
										m_priority(AP_NORMAL), 
										m_volume(-1.0),
										m_timeOfDay(TIME_OF_DAY_AFTERNOON),
										m_ownerType(OT_INVALID),
										m_shouldFade(false),
										m_isLogicalAudio(false),
										m_filenameToLoad(AsciiString::TheEmptyString),
										m_eventInfo(NULL),
										m_playingHandle(0),
										m_killThisHandle(0),
										m_pitchShift(1.0),
										m_volumeShift(0.0),
										m_loopCount(1),
										m_playingAudioIndex(-1),
										m_allCount(0),
										m_playerIndex(-1),
										m_delay(0.0f),
										m_uninterruptable(FALSE)
{
	m_attackName.clear();
	m_decayName.clear();
	m_positionOfAudio.zero();
}

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS( const AsciiString& eventName, ObjectID ownerID )
									: m_eventName(eventName), 
										m_priority(AP_NORMAL), 
										m_volume(-1.0),
										m_timeOfDay(TIME_OF_DAY_AFTERNOON),
										m_objectID(ownerID),
										m_ownerType(OT_INVALID),
										m_shouldFade(false),
										m_isLogicalAudio(false),
										m_filenameToLoad(AsciiString::TheEmptyString),
										m_eventInfo(NULL),
										m_playingHandle(0),
										m_killThisHandle(0),
										m_pitchShift(1.0),
										m_volumeShift(0.0),
										m_loopCount(1),
										m_playingAudioIndex(-1),
										m_allCount(0),
										m_playerIndex(-1),
										m_delay(0.0f),
										m_uninterruptable(FALSE)
{						
	m_attackName.clear();
	m_decayName.clear();

	if(	m_objectID ) 
	{
		m_ownerType = OT_Object;
	} 
	else 
	{
		m_objectID = INVALID_ID;
	}
}

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS( const AsciiString& eventName, DrawableID drawableID )
									: m_eventName(eventName), 
										m_priority(AP_NORMAL), 
										m_volume(-1.0),
										m_timeOfDay(TIME_OF_DAY_AFTERNOON),
										m_drawableID(drawableID),
										m_ownerType(OT_INVALID),
										m_shouldFade(false),
										m_isLogicalAudio(false),
										m_filenameToLoad(AsciiString::TheEmptyString),
										m_eventInfo(NULL),
										m_playingHandle(0),
										m_killThisHandle(0),
										m_pitchShift(1.0),
										m_volumeShift(0.0),
										m_loopCount(1),
										m_playingAudioIndex(-1),
										m_allCount(0),
										m_playerIndex(-1),
										m_delay(0.0f),
										m_uninterruptable(FALSE)
{
	m_attackName.clear();
	m_decayName.clear();

	if( m_drawableID )
	{
		m_ownerType = OT_Drawable;
	} 
	else 
	{
		m_drawableID = INVALID_DRAWABLE_ID;
	}
}

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS( const AsciiString& eventName, const Coord3D *positionOfAudio )
									: m_eventName(eventName), 
										m_priority(AP_NORMAL), 
										m_volume(-1.0),
										m_timeOfDay(TIME_OF_DAY_AFTERNOON),
										m_ownerType(OT_Positional),
										m_shouldFade(false),
										m_isLogicalAudio(false),
										m_filenameToLoad(AsciiString::TheEmptyString),
										m_eventInfo(NULL),
										m_playingHandle(0),
										m_killThisHandle(0),
										m_pitchShift(1.0),
										m_volumeShift(0.0),
										m_loopCount(1),
										m_playingAudioIndex(-1),
										m_allCount(0),
										m_playerIndex(-1),
										m_delay(0.0f),
										m_uninterruptable(FALSE)
{
	m_positionOfAudio.set( positionOfAudio );
	m_attackName.clear();
	m_decayName.clear();
}

//-------------------------------------------------------------------------------------------------
// ??0AudioEventRTS@@ present-unmatched
AudioEventRTS::AudioEventRTS( const AudioEventRTS& right )
{
	m_filenameToLoad			= right.m_filenameToLoad;
	m_eventInfo						= right.m_eventInfo;
	m_playingHandle				= right.m_playingHandle;
	m_killThisHandle			= right.m_killThisHandle;
	m_eventName						= right.m_eventName;
	m_priority						= right.m_priority;
	m_volume							= right.m_volume;
	m_timeOfDay						= right.m_timeOfDay;
	m_ownerType						= right.m_ownerType;
	m_shouldFade					= right.m_shouldFade;
	m_isLogicalAudio			= right.m_isLogicalAudio;
	m_pitchShift					= right.m_pitchShift;
	m_volumeShift					= right.m_volumeShift;
	m_loopCount						= right.m_loopCount;
	m_playingAudioIndex		= right.m_playingAudioIndex;
	m_allCount						= right.m_allCount;
	m_playerIndex					= right.m_playerIndex;
	m_delay								= right.m_delay;
	m_attackName					= right.m_attackName;
	m_decayName						= right.m_decayName;
	m_portionToPlayNext		= right.m_portionToPlayNext;
	m_uninterruptable			= right.m_uninterruptable;

	if( m_ownerType == OT_Positional || m_ownerType == OT_Dead ) 
	{
		m_positionOfAudio.set( &right.m_positionOfAudio );
	} 
	else if( m_ownerType == OT_Drawable ) 
	{
		m_drawableID = right.m_drawableID;
	} 
	else if( m_ownerType == OT_Object ) 
	{
		m_objectID = right.m_objectID;
	}

}

//-------------------------------------------------------------------------------------------------
// ??4AudioEventRTS@@ present-unmatched
AudioEventRTS& AudioEventRTS::operator=( const AudioEventRTS& right )
{
	m_filenameToLoad			= right.m_filenameToLoad;
	m_eventInfo						= right.m_eventInfo;
	m_playingHandle				= right.m_playingHandle;
	m_killThisHandle			= right.m_killThisHandle;
	m_eventName						= right.m_eventName;
	m_priority						= right.m_priority;
	m_volume							= right.m_volume;
	m_timeOfDay						= right.m_timeOfDay;
	m_ownerType						= right.m_ownerType;
	m_shouldFade					= right.m_shouldFade;
	m_isLogicalAudio			= right.m_isLogicalAudio;
	m_pitchShift					= right.m_pitchShift;
	m_volumeShift					= right.m_volumeShift;
	m_loopCount						= right.m_loopCount;
	m_playingAudioIndex		= right.m_playingAudioIndex;
	m_allCount						= right.m_allCount;
	m_playerIndex					= right.m_playerIndex;
	m_delay								= right.m_delay;
	m_attackName					= right.m_attackName;
	m_decayName						= right.m_decayName;
	m_portionToPlayNext		= right.m_portionToPlayNext;
	m_uninterruptable			= right.m_uninterruptable;

	if( m_ownerType == OT_Positional || m_ownerType == OT_Dead ) 
	{
		m_positionOfAudio.set( &right.m_positionOfAudio );
	} 
	else if( m_ownerType == OT_Drawable ) 
	{
		m_drawableID = right.m_drawableID;
	} 
	else if( m_ownerType == OT_Object ) 
	{
		m_objectID = right.m_objectID;
	} 
	return *this;

}

//-------------------------------------------------------------------------------------------------
// ??1AudioEventRTS@@ present-unmatched
AudioEventRTS::~AudioEventRTS()
{
}

//-------------------------------------------------------------------------------------------------
// ?setEventName@AudioEventRTS@@ present-unmatched
void AudioEventRTS::setEventName( AsciiString name )
{
	if ((name != m_eventName) && m_eventInfo != NULL) {
		// Clear out the audio event info, cause its not valid for the new event.
		m_eventInfo = NULL;
	}

	m_eventName = name;
}

//-------------------------------------------------------------------------------------------------
// ?generateFilename@AudioEventRTS@@ present-unmatched
void AudioEventRTS::generateFilename( void )
{
	// A Logic Random Value is used because we may ask "How long will it take to play this sound?"
	// In that case, we need the same answer across all pcs.

	if (!m_eventInfo) {
		return;
	}
	
	m_filenameToLoad = generateFilenamePrefix(m_eventInfo->m_soundType, false);
	
	Int which = 0;

	if (m_eventInfo->m_soundType == AT_Music || m_eventInfo->m_soundType == AT_Streaming) {
		m_filenameToLoad.concat(m_eventInfo->m_filename);
		adjustForLocalization(m_filenameToLoad);
		return;
	} else {
		if (m_eventInfo->m_sounds.size() == 0) {
			m_filenameToLoad = AsciiString::TheEmptyString;
			return;
		}


		
		if (BitTest(m_eventInfo->m_control, AC_RANDOM)) 
		{ 
			if (m_isLogicalAudio) 
			{
				which = GameLogicRandomValue(0, m_eventInfo->m_sounds.size() - 1);
			} 
			else 
			{
				which = GameAudioRandomValue(0, m_eventInfo->m_sounds.size() - 1);
			}

			if (which == m_playingAudioIndex && m_eventInfo->m_sounds.size() > 2)
				which = ( which + 1 ) % m_eventInfo->m_sounds.size();

			m_playingAudioIndex = which;//caching random choice to compare next call

		}
		else
			which = (++m_playingAudioIndex) % m_eventInfo->m_sounds.size();
 

	}
	
	m_filenameToLoad.concat(m_eventInfo->m_sounds[which]);
	m_filenameToLoad.concat(generateFilenameExtension(m_eventInfo->m_soundType));
	adjustForLocalization(m_filenameToLoad);

	// Note: Also generate Delay when generating a filename, cause 
	// we want delay to apply between every loop of a sound.
	m_delay = GameAudioRandomValueReal(m_eventInfo->m_delayMin, m_eventInfo->m_delayMax);
}

//-------------------------------------------------------------------------------------------------
// ?getFilename@AudioEventRTS@@ present-unmatched
AsciiString AudioEventRTS::getFilename( void )
{
	return m_filenameToLoad;
}

//-------------------------------------------------------------------------------------------------
// ?generatePlayInfo@AudioEventRTS@@ present-unmatched
void AudioEventRTS::generatePlayInfo( void )
{
	m_pitchShift = GameAudioRandomValueReal(m_eventInfo->m_pitchShiftMin, m_eventInfo->m_pitchShiftMax);
	m_volumeShift = GameAudioRandomValueReal(1.0f + m_eventInfo->m_volumeShift, 1.0f);	// volume shifts are between 0 and 1
	m_loopCount = m_eventInfo->m_loopCount;
	
	m_portionToPlayNext = PP_Attack;
	Int attackSize = m_eventInfo->m_attackSounds.size();
	if (attackSize > 0) {
		m_attackName = generateFilenamePrefix(m_eventInfo->m_soundType, false);
		// needs to be logic because it needs to be the same on all systems.
		Int attackToPlay;
		if (m_isLogicalAudio) {
			attackToPlay = GameLogicRandomValue(0, attackSize - 1);
		} else {
			attackToPlay = GameAudioRandomValue(0, attackSize - 1);
		}
		
		m_attackName.concat(m_eventInfo->m_attackSounds[attackToPlay]);
		m_attackName.concat(generateFilenameExtension(m_eventInfo->m_soundType));
		adjustForLocalization(m_attackName);
	} else {
		m_portionToPlayNext = PP_Sound;
	}

	Int decaySize = m_eventInfo->m_decaySounds.size();
	if (decaySize > 0) {
		m_decayName = generateFilenamePrefix(m_eventInfo->m_soundType, false);
		// needs to be logic because it needs to be the same on all systems.
		Int decayToPlay;
		if (m_isLogicalAudio) {
			decayToPlay = GameLogicRandomValue(0, decaySize - 1);
		} else {
			decayToPlay = GameAudioRandomValue(0, decaySize - 1);
		}
		
		m_decayName.concat(m_eventInfo->m_decaySounds[decayToPlay]);
		m_decayName.concat(generateFilenameExtension(m_eventInfo->m_soundType));
		adjustForLocalization(m_decayName);
	}

	m_isLogicalAudio = FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?getPitchShift@AudioEventRTS@@ present-unmatched
Real AudioEventRTS::getPitchShift( void ) const
{
	return m_pitchShift;
}

//-------------------------------------------------------------------------------------------------
// ?getVolumeShift@AudioEventRTS@@ present-unmatched
Real AudioEventRTS::getVolumeShift( void ) const
{
	return m_volumeShift;
}

//-------------------------------------------------------------------------------------------------
// ?getAttackFilename@AudioEventRTS@@ present-unmatched
AsciiString AudioEventRTS::getAttackFilename( void ) const
{
	return m_attackName;
}

//-------------------------------------------------------------------------------------------------
// ?getDecayFilename@AudioEventRTS@@ present-unmatched
AsciiString AudioEventRTS::getDecayFilename( void ) const
{
	return m_decayName;
}

//-------------------------------------------------------------------------------------------------
// ?getDelay@AudioEventRTS@@ present-unmatched
Real AudioEventRTS::getDelay( void ) const
{
	return m_delay;
}

//-------------------------------------------------------------------------------------------------
// ?decrementDelay@AudioEventRTS@@ present-unmatched
void AudioEventRTS::decrementDelay( Real timeToDecrement )
{
	m_delay -= timeToDecrement;
}

//-------------------------------------------------------------------------------------------------
// ?getNextPlayPortion@AudioEventRTS@@ present-unmatched
PortionToPlay AudioEventRTS::getNextPlayPortion( void ) const
{
	return m_portionToPlayNext;
}

//-------------------------------------------------------------------------------------------------
// ?advanceNextPlayPortion@AudioEventRTS@@ present-unmatched
void AudioEventRTS::advanceNextPlayPortion( void )
{
	switch (m_portionToPlayNext) 
	{
		case PP_Attack:
			m_portionToPlayNext = PP_Sound;
			break;
		case PP_Sound:
			if (m_eventInfo && BitTest(m_eventInfo->m_control, AC_ALL)) 
			{
				if (m_allCount == m_eventInfo->m_sounds.size()) {
					m_portionToPlayNext = PP_Decay;
				}

				// Advance the all count so that we move to the next sound.
				++m_allCount;
			}
			if (!m_decayName.isEmpty()) {
				m_portionToPlayNext = PP_Decay;
			} else {
				m_portionToPlayNext = PP_Done;
			}
			break;
		case PP_Decay:
			m_portionToPlayNext = PP_Done;
			break;
	}
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setNextPlayPortion( PortionToPlay ptp )
{
	m_portionToPlayNext = ptp;
}

//-------------------------------------------------------------------------------------------------
// ?decreaseLoopCount@AudioEventRTS@@ present-unmatched
void AudioEventRTS::decreaseLoopCount( void )
{
	if (m_loopCount == 1) {
		m_loopCount = -1;
	} else if (m_loopCount > 1) {
		--m_loopCount;
	}
}

//-------------------------------------------------------------------------------------------------
// ?hasMoreLoops@AudioEventRTS@@ present-unmatched
Bool AudioEventRTS::hasMoreLoops( void ) const
{
	return (m_loopCount >= 0);
}

//-------------------------------------------------------------------------------------------------
// ?setAudioEventInfo@AudioEventRTS@@ present-unmatched
void AudioEventRTS::setAudioEventInfo( const AudioEventInfo *eventInfo ) const
{
	m_eventInfo = eventInfo;
}

//-------------------------------------------------------------------------------------------------
// ?getAudioEventInfo@AudioEventRTS@@ present-unmatched
const AudioEventInfo *AudioEventRTS::getAudioEventInfo( void ) const
{
	if (m_eventInfo) {
		if (m_eventInfo->m_audioName == m_eventName) {
			return m_eventInfo;
		} else {
			m_eventInfo = NULL;
		}
	}

	return m_eventInfo;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setPlayingHandle( AudioHandle handle )
{
	m_playingHandle = handle;
}

//-------------------------------------------------------------------------------------------------
// ?getPlayingHandle@AudioEventRTS@@ present-unmatched
AudioHandle AudioEventRTS::getPlayingHandle( void )
{
	return m_playingHandle;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setPosition( const Coord3D *pos )
{
	if (!pos) {
		return;
	}

	if (!(m_ownerType == OT_Positional || m_ownerType == OT_INVALID)) {
		return;
	}

	m_positionOfAudio = *pos;
	m_ownerType = OT_Positional;
}

//-------------------------------------------------------------------------------------------------
// ?getPosition@AudioEventRTS@@ present-unmatched
const Coord3D* AudioEventRTS::getPosition( void )
{
	if( m_ownerType != OT_INVALID ) 
	{
		return &m_positionOfAudio;
	}

	return NULL;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setObjectID( ObjectID objID )
{
	if (!(m_ownerType == OT_Object || m_ownerType == OT_INVALID)) {
		return;
	}

	m_objectID = objID;
	m_ownerType = OT_Object;
}

//-------------------------------------------------------------------------------------------------
ObjectID AudioEventRTS::getObjectID( void )
{
	const char *bfmeThis = (const char *)this;
	if (*(const OwnerType *)(bfmeThis + 0x30) == OT_Object) {
		return *(const ObjectID *)(bfmeThis + 0x2c);
	}

	return INVALID_ID;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setDrawableID( DrawableID drawID )
{
	if (!(m_ownerType == OT_Drawable || m_ownerType == OT_INVALID)) {
		return;
	}

	m_drawableID = drawID;
	m_ownerType = OT_Drawable;
}

//-------------------------------------------------------------------------------------------------
DrawableID AudioEventRTS::getDrawableID( void )
{
	if (m_ownerType == OT_Drawable) {
		return m_drawableID;
	}

	return INVALID_DRAWABLE_ID;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setTimeOfDay( TimeOfDay tod )
{
	m_timeOfDay = tod;
}

//-------------------------------------------------------------------------------------------------
// ?getTimeOfDay@AudioEventRTS@@ present-unmatched
TimeOfDay AudioEventRTS::getTimeOfDay( void ) const
{
	return m_timeOfDay;
}


//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setHandleToKill( AudioHandle handleToKill )
{
	m_killThisHandle = handleToKill;
}

//-------------------------------------------------------------------------------------------------
// ?getHandleToKill@AudioEventRTS@@ present-unmatched
AudioHandle AudioEventRTS::getHandleToKill( void ) const
{
	return m_killThisHandle;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setShouldFade( Bool shouldFade )
{
	m_shouldFade = shouldFade;
}

//-------------------------------------------------------------------------------------------------
// ?getShouldFade@AudioEventRTS@@ present-unmatched
Bool AudioEventRTS::getShouldFade( void ) const
{
	return m_shouldFade;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setIsLogicalAudio( Bool isLogicalAudio )
{
	m_isLogicalAudio = isLogicalAudio;
}

//-------------------------------------------------------------------------------------------------
// ?getIsLogicalAudio@AudioEventRTS@@ present-unmatched
Bool AudioEventRTS::getIsLogicalAudio( void ) const
{
	return m_isLogicalAudio;
}

//-------------------------------------------------------------------------------------------------
// ?isPositionalAudio@AudioEventRTS@@ present-unmatched
Bool AudioEventRTS::isPositionalAudio( void ) const
{
	if( m_eventInfo ) 
	{
		if( !BitTest( m_eventInfo->m_type, ST_WORLD ) ) 
		{
			return FALSE;
		}
	}
	if( m_ownerType != OT_INVALID )
	{
		if( m_drawableID != INVALID_DRAWABLE_ID || m_objectID != INVALID_ID || m_ownerType == OT_Positional )
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?isCurrentlyPlaying@AudioEventRTS@@ present-unmatched
Bool AudioEventRTS::isCurrentlyPlaying( void ) const
{
	return TheAudio->isCurrentlyPlaying(m_playingHandle);
}

//-------------------------------------------------------------------------------------------------
// ?getAudioPriority@AudioEventRTS@@ present-unmatched
AudioPriority AudioEventRTS::getAudioPriority( void ) const
{
	return m_priority;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setAudioPriority( AudioPriority newPriority )
{
	m_priority = newPriority;

}


//-------------------------------------------------------------------------------------------------
// ?getVolume@AudioEventRTS@@ present-unmatched
Real AudioEventRTS::getVolume( void ) const
{
	if (m_volume == -1.0f) {
		if (m_eventInfo) {
			return m_eventInfo->m_volume;
		}
		return 0.5;
	}
	
	return m_volume;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setVolume( Real vol )
{
	m_volume = vol;
}

//-------------------------------------------------------------------------------------------------
// ?getCurrentPosition@AudioEventRTS@@ present-unmatched
const Coord3D *AudioEventRTS::getCurrentPosition( void )
{
	if (m_ownerType == OT_Positional) 
	{
		return &m_positionOfAudio;
	} 
	else if (m_ownerType == OT_Object) 
	{
		Object *obj = TheGameLogic->findObjectByID(m_objectID);
		if (obj)
		{
			m_positionOfAudio.set( obj->getPosition() );
		}
		else
		{
			m_ownerType = OT_Dead;
		}
		return &m_positionOfAudio;
	} 
	else if (m_ownerType == OT_Drawable) 
	{
		Drawable *draw = TheGameClient->findDrawableByID(m_drawableID);
		if( draw )
		{
			m_positionOfAudio.set( draw->getPosition() );
		}
		else
		{
			m_ownerType = OT_Dead;
		}
		return &m_positionOfAudio;
	}
	else if( m_ownerType == OT_Dead )
	{
		return &m_positionOfAudio;
	}

	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?generateFilenamePrefix@AudioEventRTS@@ present-unmatched
AsciiString AudioEventRTS::generateFilenamePrefix( AudioType audioTypeToPlay, Bool localized )
{
	AsciiString retStr;
	retStr = TheAudio->getAudioSettings()->m_audioRoot;
	retStr.concat("\\");
	if (audioTypeToPlay == AT_Music) {
		retStr.concat(TheAudio->getAudioSettings()->m_musicFolder);
	} else if (audioTypeToPlay == AT_Streaming) {
		retStr.concat(TheAudio->getAudioSettings()->m_streamingFolder);
	} else {
		retStr.concat(TheAudio->getAudioSettings()->m_soundsFolder);
	}
	retStr.concat("\\");

	if (localized) {
		retStr.concat(GetRegistryLanguage());
		retStr.concat("\\");
	}

	return retStr;
}

//-------------------------------------------------------------------------------------------------
// ?generateFilenameExtension@AudioEventRTS@@ present-unmatched
AsciiString AudioEventRTS::generateFilenameExtension( AudioType audioTypeToPlay )
{
	AsciiString retStr = AsciiString::TheEmptyString;
	if (audioTypeToPlay != AT_Music) {
		retStr = ".";
		retStr.concat(TheAudio->getAudioSettings()->m_soundsExtension);
	}

	return retStr;
}

//-------------------------------------------------------------------------------------------------
// ?adjustForLocalization@AudioEventRTS@@ present-unmatched
void AudioEventRTS::adjustForLocalization(AsciiString &strToAdjust)
{
	const char *str = strToAdjust.reverseFind('\\');
	if (!str) {
		return;
	}

	// try the localized version first so that we're guarenteed to get it
	// even if the generic data directory holds a version of the file
	AsciiString localizedFilePath = generateFilenamePrefix(m_eventInfo->m_soundType, TRUE);
	AsciiString filename = str;
	localizedFilePath.concat(filename);

	if (TheFileSystem->doesFileExist(localizedFilePath.str())) {
		strToAdjust = localizedFilePath;
	}
	// else there was no localized version, so leave the path we received unchanged

	return;
}

//-------------------------------------------------------------------------------------------------
// ?getPlayerIndex@AudioEventRTS@@ present-unmatched
Int AudioEventRTS::getPlayerIndex( void ) const
{
	if (m_ownerType == OT_Object) {
		Object *obj = TheGameLogic->findObjectByID(m_objectID);
		if (obj) {
			return obj->getControllingPlayer()->getPlayerIndex();
		}
	} else if (m_ownerType == OT_Drawable) {
		Drawable *draw = TheGameClient->findDrawableByID(m_drawableID);
		if (draw) {
			Object *obj = draw->getObject();
			if (obj) {
				return obj->getControllingPlayer()->getPlayerIndex();
			}
		}
	}

	return m_playerIndex;
}

//-------------------------------------------------------------------------------------------------
void AudioEventRTS::setPlayerIndex( Int playerNdx )
{
	m_playerIndex = playerNdx;
}
