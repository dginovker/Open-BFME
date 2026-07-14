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

// FILE: DisplayString.cpp ////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:    RTS3
//
// File name:  DisplayString.cpp
//
// Created:    Colin Day, July 2001
//
// Desc:       Contstuct for holding double byte game string data and being
//						 able to draw that text to the screen.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Debug.h"
#include "Common/Language.h"
#include "GameClient/DisplayString.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// DisplayString::DisplayString ===============================================
/** */
//=============================================================================
DisplayString::DisplayString( void )
{
	// m_textString = "";	// not necessary, done by default
	m_font = NULL;

	m_next = NULL;
	m_prev = NULL;

}  // end DisplayString

// DisplayString::~DisplayString ==============================================
/** */
//=============================================================================
// ??1DisplayString@@ present-unmatched
DisplayString::~DisplayString( void )
{

	// free any data
	reset();

}  // end ~DisplayString

// DisplayString::setText =====================================================
/** Copy the text to this instance */
//=============================================================================
// ?setText@DisplayString@@ present-unmatched
void DisplayString::setText( UnicodeString text )
{
	if (text == m_textString) 
		return;

	m_textString = text;

	// our text has now changed
	notifyTextChanged();

}  // end setText

// DisplayString::reset =======================================================
/** Free and reset all the data for this string, effectively making this
	* instance like brand new */
//=============================================================================
void DisplayString::reset( void )
{

	m_textString.clear();

	// no font
	m_font = NULL;

}  // end reset

// DisplayString::removeLastChar ==============================================
/** Remove the last character from the string text */
//=============================================================================
// ?removeLastChar@DisplayString@@ present-unmatched
void DisplayString::removeLastChar( void )
{
	m_textString.removeLastChar();

	// our text has now changed
	notifyTextChanged();

}  // end removeLastChar

// DisplayString::appendChar ==================================================
/** Append character to the end of the string */
//=============================================================================
// ?appendChar@DisplayString@@ present-unmatched
void DisplayString::appendChar( WideChar c )
{
	m_textString.concat(c);

	// text has now changed
	notifyTextChanged();

}  // end appendchar

