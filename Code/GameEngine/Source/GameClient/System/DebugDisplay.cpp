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
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    Debug
//
// File name: DebugDisplay.cpp
//
// Created:   11/13/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/DebugDisplay.h"

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
// DebugDisplay::DebugDisplay
//============================================================================

// ??0DebugDisplay@@ present-unmatched
DebugDisplay::DebugDisplay()
: m_width(0),
	m_height(0)
{
	reset();
}

//============================================================================
// DebugDisplay::reset
//============================================================================

// ?reset@DebugDisplay@@ present-unmatched
void DebugDisplay::reset( void )
{
	setCursorPos( 0, 0 );
	setTextColor( WHITE );
	setRightMargin( 0 );
	setLeftMargin( getWidth() );
}
//============================================================================
// DebugDisplay::setCursorPos
//============================================================================

void	DebugDisplay::setCursorPos( Int x, Int y )
{
	m_xPos = x;
	m_yPos = y;
}

//============================================================================
// DebugDisplay::getCursorXPos
//============================================================================

// ?getCursorXPos@DebugDisplay@@ present-unmatched
Int		DebugDisplay::getCursorXPos( void )
{
	return m_xPos;
}

//============================================================================
// DebugDisplay::getCursorYPos
//============================================================================

// ?getCursorYPos@DebugDisplay@@ present-unmatched
Int		DebugDisplay::getCursorYPos( void )
{
	return m_yPos;
}

//============================================================================
// DebugDisplay::getWidth
//============================================================================

// ?getWidth@DebugDisplay@@ present-unmatched
Int		DebugDisplay::getWidth( void )
{
	return m_width;
}

//============================================================================
// DebugDisplay::getHeight
//============================================================================

// ?getHeight@DebugDisplay@@ present-unmatched
Int		DebugDisplay::getHeight( void )
{
	return m_height;
}

//============================================================================
// DebugDisplay::setTextColor
//============================================================================

// ?setTextColor@DebugDisplay@@ present-unmatched
void	DebugDisplay::setTextColor( Color color )
{
	m_textColor = color;
}	

//============================================================================
// DebugDisplay::setRightMargin
//============================================================================

// ?setRightMargin@DebugDisplay@@ present-unmatched
void	DebugDisplay::setRightMargin( Int rightPos )
{
	m_rightMargin = rightPos;
}

//============================================================================
// DebugDisplay::setLeftMargin
//============================================================================

// ?setLeftMargin@DebugDisplay@@ present-unmatched
void	DebugDisplay::setLeftMargin( Int leftPos )
{
	m_leftMargin = leftPos;
}

//============================================================================
// DebugDisplay::printf
//============================================================================

// ?printf@DebugDisplay@@ present-unmatched
void	DebugDisplay::printf( Char *format, ...)
{
	va_list args;
	int result;
	static char text[5*1024];

  va_start( args, format );
	result = vsprintf( text, format, args );
  va_end( args );

	if ( result < 0 )
	{
		// error while printing string
		return;
	}

	DEBUG_ASSERTCRASH( result < sizeof(text), ("text overflow in DebugDisplay::printf() - string too long"));

	// find every line and print it
	Char *ptr = text;;
	Char *lineStart = ptr;
	Int lineLen = 0;
	Char ch;

	while ( (ch = *ptr++) != 0 )
	{
		switch ( ch )
		{
			case '\n':
			{
				if ( lineLen > 0 )
				{
					*(ptr -1) = 0; // replace '/n' with null
					drawText( m_rightMargin + m_xPos, m_yPos, lineStart );
					lineLen = 0;
				}
				lineStart = ptr;
				m_yPos++;
				m_xPos = 0;
				break;
			}

			default:
			{
				lineLen++;
				break;
			}
		}
	}

	if ( lineLen > 0 )
	{
		drawText( m_rightMargin + m_xPos, m_yPos, lineStart );
		m_xPos += lineLen;
	}
}
