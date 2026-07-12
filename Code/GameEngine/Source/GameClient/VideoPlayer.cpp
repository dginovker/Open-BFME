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

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    GameClient
//
// File name: VideoPlayer.cpp
//
// Created:   10/22/01	TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Lib/BaseType.h"
#include "GameClient/VideoPlayer.h"

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Data                                                      
//----------------------------------------------------------------------------

VideoPlayerInterface *TheVideoPlayer = NULL;

//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------

//============================================================================
// VideoBuffer::VideoBuffer
//============================================================================

// ??0VideoBuffer@@QAE@W4Type@0@@Z present-unmatched
VideoBuffer::VideoBuffer( Type format)
: m_width(0),
	m_height(0),
	m_textureWidth(0),
	m_textureHeight(0),
	m_format(format),
	m_pitch(0),
	m_xPos(0),
	m_yPos(0)
{

	if ( m_format >= NUM_TYPES || m_format < 0 )
	{
		m_format = TYPE_UNKNOWN;
	}

}

//============================================================================
// VideoBuffer::Rect
//============================================================================

// ?Rect@VideoBuffer@@QAE?AVRectClass@@MMMM@Z present-unmatched
RectClass VideoBuffer::Rect( Real x1, Real y1, Real x2, Real y2 )
{
	RectClass rect(0,0,0,0);

	if ( valid() )
	{
		rect.Set( 
						((Real)m_width/(Real)m_textureWidth)*x1, ((Real)m_height/(Real)m_textureHeight)*y1, 
						((Real)m_width/(Real)m_textureWidth)*x2, ((Real)m_height/(Real)m_textureHeight)*y2
					);
	}

	return rect;

}

//============================================================================
// VideoBuffer::free
//============================================================================

// ?free@VideoBuffer@@UAEXXZ present-unmatched
void	VideoBuffer::free( void )
{
	m_width = 0;
	m_height = 0;
	m_textureWidth = 0;
	m_textureHeight = 0;
}

//============================================================================
// VideoPlayer::VideoPlayer
//============================================================================

// ??0VideoPlayer@@QAE@XZ present-unmatched
VideoPlayer::VideoPlayer()
: m_firstStream(NULL)
{

}

//============================================================================
// VideoPlayer::~VideoPlayer
//============================================================================

// ??1VideoPlayer@@UAE@XZ present-unmatched
VideoPlayer::~VideoPlayer()
{
	deinit();
	// Set the video player to null if its us. (WB requires this.)
	if (this == TheVideoPlayer) {
		TheVideoPlayer = NULL;
	}
}

//============================================================================
// VideoPlayer::init
//============================================================================

// ?init@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::init( void )
{
	// Load this here so that WB doesn't have to link to BinkLib, costing us (potentially)
	// an extra license.
	INI ini;
	ini.load( AsciiString( "Data\\INI\\Default\\Video.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Video.ini" ), INI_LOAD_OVERWRITE, NULL );
}

//============================================================================
// VideoPlayer::deinit
//============================================================================

// ?deinit@VideoPlayer@@UAEXXZ present-unmatched
void VideoPlayer::deinit( void )
{
}

//============================================================================
// VideoPlayer::reset
//============================================================================

// ?reset@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::reset( void )
{
	closeAllStreams();
}

//============================================================================
// VideoPlayer::update
//============================================================================

// ?update@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::update( void )
{

	VideoStreamInterface *stream = firstStream();

	while ( stream )
	{
		stream->update();
		stream = stream->next();
	}

}

//============================================================================
// VideoPlayer::loseFocus
//============================================================================

// ?loseFocus@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::loseFocus( void )
{

}

//============================================================================
// VideoPlayer::regainFocus
//============================================================================

// ?regainFocus@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::regainFocus( void )
{

}

//============================================================================
// VideoPlayer::open
//============================================================================

// ?open@VideoPlayer@@UAEPAVVideoStreamInterface@@VAsciiString@@@Z present-unmatched
VideoStreamInterface*	VideoPlayer::open( AsciiString movieTitle )
{
	return NULL;
}

//============================================================================
// VideoPlayer::load
//============================================================================

// ?load@VideoPlayer@@UAEPAVVideoStreamInterface@@VAsciiString@@@Z present-unmatched
VideoStreamInterface*	VideoPlayer::load( AsciiString movieTitle )
{
	return NULL;
}

//============================================================================
// VideoPlayer::firstStream
//============================================================================

// ?firstStream@VideoPlayer@@UAEPAVVideoStreamInterface@@XZ present-unmatched
VideoStreamInterface* VideoPlayer::firstStream( void )
{
	return m_firstStream;
}

//============================================================================
// VideoPlayer::closeAllStreams
//============================================================================

// ?closeAllStreams@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::closeAllStreams( void )
{
	VideoStreamInterface *stream ;

	while ( (stream = firstStream()) != 0 )
	{
		stream->close();
	}
}

//============================================================================
// VideoPlayer::remove
//============================================================================

// ?remove@VideoPlayer@@QAEXPAVVideoStream@@@Z present-unmatched
void VideoPlayer::remove( VideoStream *stream_to_remove )
{
	VideoStream *last = NULL;
	VideoStream *stream = (VideoStream*) firstStream();

	while ( stream != NULL && stream != stream_to_remove )
	{
		last = stream;
		stream = (VideoStream*) stream->next();
	}

	if ( stream )
	{
		if ( last )
		{
			last->m_next = stream->m_next;
		}
		else
		{
			m_firstStream = stream->m_next;
		}
	}
}

//============================================================================
// VideoPlayer::addVideo
//============================================================================
// ?addVideo@VideoPlayer@@UAEXPAUVideo@@@Z present-unmatched
void VideoPlayer::addVideo( Video* videoToAdd )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == videoToAdd->m_internalName) {
			(*it) = (*videoToAdd);
			return;
		}
	}

	// That internal name hasn't been used, so push a new entry on the back
	mVideosAvailableForPlay.push_back(*videoToAdd);
}

//============================================================================
// VideoPlayer::removeVideo
//============================================================================
// ?removeVideo@VideoPlayer@@UAEXPAUVideo@@@Z present-unmatched
void VideoPlayer::removeVideo( Video* videoToRemove )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == videoToRemove->m_internalName) {
			mVideosAvailableForPlay.erase(it);
			return;
		}
	}
}

//============================================================================
// VideoPlayer::getNumVideos
//============================================================================
// ?getNumVideos@VideoPlayer@@UAEHXZ present-unmatched
Int VideoPlayer::getNumVideos( void )
{
	return mVideosAvailableForPlay.size();
}

//============================================================================
// VideoPlayer::removeVideo
//============================================================================
// ?getVideo@VideoPlayer@@ present-unmatched
const Video* VideoPlayer::getVideo( AsciiString movieTitle )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == movieTitle) {
			return &(*it);
		}
	}
	return NULL;
}

//============================================================================
// VideoPlayer::getVideo
//============================================================================
// ?getVideo@VideoPlayer@@ present-unmatched
const Video* VideoPlayer::getVideo( Int index )
{
	if (index < 0 || index >= mVideosAvailableForPlay.size()) {
		return NULL;
	}

	return &mVideosAvailableForPlay[index];
}

//============================================================================
// VideoStream::VideoStream
//============================================================================

// ??0VideoStream@@IAE@XZ present-unmatched
VideoStream::VideoStream()
: m_next(NULL),
	m_player(NULL)
{

}

//============================================================================
// VideoStream::~VideoStream
//============================================================================

// ??1VideoStream@@MAE@XZ present-unmatched
VideoStream::~VideoStream()
{

	if ( m_player )
	{
		m_player->remove( this );
		m_player = NULL;
	}

}

//============================================================================
// VideoStream::next
//============================================================================

// ?next@VideoStream@@UAEPAVVideoStreamInterface@@XZ present-unmatched
VideoStreamInterface* VideoStream::next( void )
{
	return m_next;
}

//============================================================================
// VideoStream::update
//============================================================================

// ?update@VideoStream@@UAEXXZ present-unmatched
void VideoStream::update( void )
{
}

//============================================================================
// VideoStream::close
//============================================================================

// ?close@VideoStream@@UAEXXZ present-unmatched
void VideoStream::close( void )
{
	delete this;
}

//============================================================================
// VideoStream::isFrameReady
//============================================================================

// ?isFrameReady@VideoStream@@UAE_NXZ present-unmatched
Bool VideoStream::isFrameReady( void )
{
	return TRUE;
}

//============================================================================
// VideoStream::frameDecompress
//============================================================================

// ?frameDecompress@VideoStream@@UAEXXZ present-unmatched
void VideoStream::frameDecompress( void )
{

}

//============================================================================
// VideoStream::frameRender
//============================================================================

// ?frameRender@VideoStream@@UAEXPAVVideoBuffer@@@Z present-unmatched
void VideoStream::frameRender( VideoBuffer *buffer )
{

}

//============================================================================
// VideoStream::frameNext
//============================================================================

// ?frameNext@VideoStream@@UAEXXZ present-unmatched
void VideoStream::frameNext( void )
{

}

//============================================================================
// VideoStream::frameIndex
//============================================================================

// ?frameIndex@VideoStream@@UAEHXZ present-unmatched
Int VideoStream::frameIndex( void )
{
	return 0;
}

//============================================================================
// VideoStream::totalFrames
//============================================================================

// ?frameCount@VideoStream@@UAEHXZ present-unmatched
Int	VideoStream::frameCount( void )
{
	return 0;
}

//============================================================================
// VideoStream::frameGoto
//============================================================================

// ?frameGoto@VideoStream@@UAEXH@Z present-unmatched
void VideoStream::frameGoto( Int index )
{

}

//============================================================================
// VideoStream::height
//============================================================================

// ?height@VideoStream@@UAEHXZ present-unmatched
Int		VideoStream::height( void )
{
	return 0;
}

//============================================================================
// VideoStream::width
//============================================================================

// ?width@VideoStream@@UAEHXZ present-unmatched
Int		VideoStream::width( void )
{
	return 0;
}


const FieldParse VideoPlayer::m_videoFieldParseTable[] = 
{
	{ "Filename",								INI::parseAsciiString,							NULL, offsetof( Video, m_filename) },
	{ "Comment",								INI::parseAsciiString,							NULL, offsetof( Video, m_commentForWB) },
	{ NULL,											NULL,																NULL, 0 },
};

