// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: GameWindow.cpp ///////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: GameWindow.cpp
//
// Created:   Dean Iverson, March 1998
//						Colin Day, June 2001
//
// Desc:      Game window implementation
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/AudioEventRTS.h"
#include "Common/Language.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/Mouse.h"
#include "GameClient/SelectionXlat.h"
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////

// GameWindow::GameWindow =====================================================
//=============================================================================
// ??0GameWindow@@QAE@XZ present-unmatched
GameWindow::GameWindow( void )
{
	m_status = WIN_STATUS_NONE;

	m_size.x = 0;
	m_size.y = 0;

	m_region.lo.x = 0;
	m_region.lo.y = 0;
	m_region.hi.x = 0;
	m_region.hi.y = 0;

	m_cursorX = 0;
	m_cursorY = 0;

	m_userData = 0;

	m_inputData = NULL;

	winSetDrawFunc( TheWindowManager->getDefaultDraw() );
	winSetInputFunc( TheWindowManager->getDefaultInput() );
	winSetSystemFunc( TheWindowManager->getDefaultSystem() );
	// We use to set the default tooltip func to TheWindowManager->getDefaultTooltip()
	// but I removed this so that we can set in GUI edit a text string that will be the
	// default tool tip for a control.
	winSetTooltipFunc( NULL );

	m_next = NULL;
	m_prev = NULL;
	m_parent = NULL;
	m_child = NULL;

	m_nextLayout = NULL;
	m_prevLayout = NULL;
	m_layout = NULL;

	m_editData = NULL;

}  // end GameWindow

// GameWindow::~GameWindow ====================================================
//=============================================================================
// ??1GameWindow@@MAE@XZ present-unmatched
GameWindow::~GameWindow( void )
{

	if(	m_inputData )
		delete m_inputData;
	m_inputData = NULL;
	
	if( m_editData )
		delete m_editData;
	m_editData = NULL;

}  // end ~GameWindow

// GameWindow::normalizeWindowRegion ==========================================
/** Puts the upper left corner in the window's region.lo field */
//=============================================================================
// ?normalizeWindowRegion@GameWindow@@IAEXXZ present-unmatched
void GameWindow::normalizeWindowRegion( void )
{
	Int temp;

	if( m_region.lo.x > m_region.hi.x) 
	{

		temp = m_region.lo.x;
		m_region.lo.x = m_region.hi.x;
		m_region.hi.x = temp;

	}  // end if

	if( m_region.lo.y > m_region.hi.y ) 
	{

		temp = m_region.lo.y;
		m_region.lo.y = m_region.hi.y;
		m_region.hi.y = temp;

	}  // end if

}  // end normalizeWindowRegion

// GameWindow::findFirstLeaf ==================================================
/** Returns the first leaf of the branch */
//=============================================================================
// ?findFirstLeaf@GameWindow@@IAEPAV1@XZ present-unmatched
GameWindow *GameWindow::findFirstLeaf( void )
{
	GameWindow *leaf = this;

	// Find the root of this branch
	while( leaf->m_parent )
		leaf = leaf->m_parent;

	// Find the first leaf
	while( leaf->m_child )
		leaf = leaf->m_child;

	return leaf;

}  // end findFirstLeaf

// GameWindow::findLastLeaf ===================================================
/** Returns the last leaf of the branch */
//=============================================================================
// ?findLastLeaf@GameWindow@@IAEPAV1@XZ present-unmatched
GameWindow *GameWindow::findLastLeaf( void )
{
	GameWindow *leaf = this;

	// Find the root of this branch
	while( leaf->m_parent )
		leaf = leaf->m_parent;

	// Find the last leaf
	while( leaf->m_child ) 
	{

		leaf = leaf->m_child;

		while( leaf->m_next )
			leaf = leaf->m_next;

	}  // end while

	return leaf;

}  // end findLastLeaf

// GameWindow::findPrevLeaf ===================================================
/** Returns the prev leaf of the tree */
//=============================================================================
// ?findPrevLeaf@GameWindow@@IAEPAV1@XZ present-unmatched
GameWindow *GameWindow::findPrevLeaf( void )
{
	GameWindow *leaf = this;

	if( leaf->m_prev ) 
	{

		leaf = leaf->m_prev;

		while( leaf->m_child && 
					 BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) == FALSE ) 
		{

			leaf = leaf->m_child;

			while( leaf->m_next )
				leaf = leaf->m_next;

		}  // end while

		return leaf;

	}   // end if
	else 
	{

		while( leaf->m_parent ) 
		{

			leaf = leaf->m_parent;

			if( leaf->m_parent && leaf->m_prev ) 
			{

				leaf = leaf->m_prev;

				while( leaf->m_child && 
							 BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) == FALSE ) 
				{

					leaf = leaf->m_child;

					while( leaf->m_next )
						leaf = leaf->m_next;

				}  // end while

				return leaf;

			}  // end if

		}  // end while

		if( leaf )
			return leaf->findLastLeaf();
		else
			return NULL;

	}  // end else

	return NULL;

}  // end findPrevLeaf

// GameWindow::findNextLeaf ===================================================
/** Returns the next leaf of the tree */
//=============================================================================
// ?findNextLeaf@GameWindow@@IAEPAV1@XZ present-unmatched
GameWindow *GameWindow::findNextLeaf( void )
{
	GameWindow *leaf = this;

	if( leaf->m_next ) 
	{

		if( leaf->m_next->m_status & WIN_STATUS_TAB_STOP )
			return leaf->m_next;

		for( leaf = leaf->m_next; leaf; leaf = leaf->m_child )
			if( leaf->m_child == NULL || BitTest( leaf->m_status, 
																						WIN_STATUS_TAB_STOP ) )
				return leaf;

	}  // end if
	else 
	{

		while( leaf->m_parent ) 
		{

			leaf = leaf->m_parent;

			if( leaf->m_parent && leaf->m_next ) 
			{

				for( leaf = leaf->m_next; leaf; leaf = leaf->m_child )
					if( leaf->m_child == NULL || 
							BitTest( leaf->m_status, WIN_STATUS_TAB_STOP ) )
						return leaf;

			}  // end if

		}  // end while

		if( leaf )
			return leaf->findFirstLeaf();
		else
			return NULL;

	}  // end else

	return NULL;

}  // end findNextLeav

// GameWindow::winNextTab =====================================================
/** Go to next window in tab chain */
//=============================================================================
// ?winNextTab@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winNextTab( void )
{
/*
	GameWindow *newTab = this;
	Bool firstTry = TRUE;

	// Un-hilite the current window
	m_instData.m_state &= ~WIN_STATE_HILITED;

	do 
	{

		if( m_parent == NULL && firstTry ) 
		{

			newTab = findLastLeaf( newTab );
			firstTry = FALSE;

		} 
		else
			newTab = findPrevLeaf( newTab );
	} while( ( isEnabled( newTab ) == FALSE ) ||
					 ( isHidden( newTab ) ) );

	newTab->instData.state |= WIN_STATE_HILITED;
	WinSetFocus( newTab );

*/
	return WIN_ERR_OK;

}  // end WinNextTab

// GameWindow::winPrevTab =====================================================
/** Go to previous window in tab chain */
//=============================================================================
// ?winPrevTab@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winPrevTab( void )
{
/*
	GameWindow *newTab = this;
	Bool firstTry = TRUE;

	// Un-hilite the current window
	m_instData.m_state &= ~WIN_STATE_HILITED;

	do 
	{

		if( m_parent == NULL && firstTry ) 
		{

			newTab = findFirstLeaf( newTab );
			firstTry = FALSE;

		}  // end if
		else
			newTab = findNextLeaf( newTab );

	} while( ( isEnabled( newTab ) == FALSE ) ||
					 ( isHidden( newTab ) ) );

	newTab->instData.state |= WIN_STATE_HILITED;
	WinSetFocus( newTab );

*/

	return WIN_ERR_OK;

}  // end WinPrevTab

// GameWindow::winBringToTop ==================================================
/** Bring this window to the top of the window list, if we have a parent
	* we will go to the top of the child list for that parent */
//=============================================================================
// ?winBringToTop@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winBringToTop( void )
{
	GameWindow *current;
	GameWindow *parent = winGetParent();

	if( parent )
	{

		TheWindowManager->unlinkChildWindow( this );
		TheWindowManager->addWindowToParent( this, parent );
//		TheWindowManager->addWindowToParentAtEnd( this, parent );

	}  // end if
	else
	{

		// sanity, make sure this window is in the window list
		for( current = TheWindowManager->winGetWindowList(); 
				 current != this; 
				 current = current->m_next)
			if (current == NULL)
				return WIN_ERR_INVALID_PARAMETER;

		// move to head of windowList
		TheWindowManager->unlinkWindow( this );
		TheWindowManager->linkWindow( this );

	}  // end else

	//
	// if the window is part of a screen layout, move it to the top
	// of the screen layout to reflect the new position of the window
	// in the real window list (it's all about draw order :) )
	//
	if( m_layout )
	{
		WindowLayout *saveLayout = m_layout;

		//
		// note we must use saveScreen because removing the window from the
		// screen will clear the m_screen member (as it should for removing
		// a window from a screen)
		//
		saveLayout->removeWindow( this );
		saveLayout->addWindow( this );

	}  // end if

	return WIN_ERR_OK;

}  // end winBringToTop

// GameWindow::winActivate ====================================================
/** Pop window to top of window list AND activate it */
//=============================================================================
// ?winActivate@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winActivate( void )
{
	Int returnCode;

	// bring window to top
	returnCode = winBringToTop();
	if( returnCode != WIN_ERR_OK )
		return returnCode;

	// activate it and unhide
	BitSet( m_status, WIN_STATUS_ACTIVE );
	winHide( FALSE );

	return WIN_ERR_OK;

}  // end WinActivate

// GameWindow::winSetPosition =================================================
/** Set the window's position */
//=============================================================================
// ?winSetPosition@GameWindow@@QAEHHH@Z present-unmatched
Int GameWindow::winSetPosition( Int x, Int y )
{

	m_region.lo.x = x;
	m_region.lo.y = y;

	m_region.hi.x = x + m_size.x;
	m_region.hi.y = y + m_size.y;

	normalizeWindowRegion();

	return WIN_ERR_OK;

}  // end WinSetPosition

// WinGetPosition =============================================================
/** Get the window's postion */
//=============================================================================
// ?winGetPosition@GameWindow@@QAEHPAH0@Z present-unmatched
Int GameWindow::winGetPosition( Int *x, Int *y )
{
	
	// sanity
	if( x == NULL || y == NULL )
		return WIN_ERR_INVALID_PARAMETER;

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	return WIN_ERR_OK;

}  // end WinGetPosition

// WinSetCursorPosition =============================================================
/** Set the window's cursor postion */
//=============================================================================
// ?winSetCursorPosition@GameWindow@@QAEHHH@Z present-unmatched
Int GameWindow::winSetCursorPosition( Int x, Int y )
{
	m_cursorX = x;
	m_cursorY = y;

	return WIN_ERR_OK;

}  // end WinSetCursorPosition

// WinGetCursorPosition =============================================================
/** Get the window's cursor postion */
//=============================================================================
// ?winGetCursorPosition@GameWindow@@QAEHPAH0@Z present-unmatched
Int GameWindow::winGetCursorPosition( Int *x, Int *y )
{
	if ( x )
	{
		*x = m_cursorX;
	}
	
	if ( y )
	{
		*y = m_cursorY;
	}
	
	return WIN_ERR_OK;

}  // end WinGetPosition

// GameWindow::winGetScreenPosition ===========================================
/** Get the window's postion in screen coordinates */
//=============================================================================
// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z present-unmatched
Int GameWindow::winGetScreenPosition( Int *x, Int *y )
{
	GameWindow *parent = m_parent;

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	while( parent ) 
	{

		*x += parent->m_region.lo.x;
		*y += parent->m_region.lo.y;
		parent = parent->m_parent;

	}  // end while

	return WIN_ERR_OK;

}  // end WinGetScreenPosition

// GameWindow::winGetRegion ===================================================
/** Get the window region */
//=============================================================================
// ?winGetRegion@GameWindow@@QAEHPAUIRegion2D@@@Z present-unmatched
Int GameWindow::winGetRegion( IRegion2D *region )
{

	if( region )
		*region = m_region;

	return WIN_ERR_OK;

}  // end winGetRegion

// GameWindow::winPointInWindow ===============================================
/** Check to see if the given point is inside the window.  Will
	* still return true if the point is actually in a child. */
//=============================================================================
// ?winPointInWindow@GameWindow@@QAE_NHH@Z present-unmatched
Bool GameWindow::winPointInWindow( Int x, Int y )
{
	Int winX, winY, width, height;

	winGetScreenPosition( &winX, &winY );
	winGetSize( &width, &height );

	if (x >= winX && x <= winX + width &&
			y >= winY && y <= winY + height)
		return TRUE;

	return FALSE;

}  // end WinPointInWindow

// GameWindow::winSetSize =====================================================
/** Set the window's size */
//=============================================================================
// ?winSetSize@GameWindow@@QAEHHH@Z present-unmatched
Int GameWindow::winSetSize( Int width, Int height )
{

	m_size.x = width;
	m_size.y = height;
	m_region.hi.x = m_region.lo.x + width;
	m_region.hi.y = m_region.lo.y + height;

	TheWindowManager->winSendSystemMsg( this, 
																			GGM_RESIZED,
																			(WindowMsgData)width, 
																			(WindowMsgData)height );

	return WIN_ERR_OK;

}  // end WinSetSize

// GameWindow::winGetSize =====================================================
/** Get the window's size */
//=============================================================================
// ?winGetSize@GameWindow@@QAEHPAH0@Z present-unmatched
Int GameWindow::winGetSize( Int *width, Int *height )
{

	// sanity
	if( width == NULL || height == NULL )
		return WIN_ERR_INVALID_PARAMETER;

	*width  = m_size.x;
	*height = m_size.y;

	return WIN_ERR_OK;

}  // end WinGetSize

// GameWindow::winEnable ======================================================
/** Enable or disable a window based on the enable parameter.
	* A disabled window can be seen but accepts no input. */
//=============================================================================
// ?winEnable@GameWindow@@QAEH_N@Z present-unmatched
Int GameWindow::winEnable( Bool enable )
{
	GameWindow *child;

	if( enable )
		BitSet( m_status, WIN_STATUS_ENABLED );
	else
		BitClear( m_status, WIN_STATUS_ENABLED );

	if( m_child ) 
	{

		for( child = m_child; child; child = child->m_next)
			child->winEnable( enable );

	}  // end if

	return WIN_ERR_OK;

}  // end WinEnable

// GameWindow::winGetEnabled ======================================================
/** Enable or disable a window based on the enable parameter.
	* A disabled window can be seen but accepts no input. */
//=============================================================================
// ?winGetEnabled@GameWindow@@QAE_NXZ present-unmatched
Bool GameWindow::winGetEnabled( void )
{
  return BitTest( m_status, WIN_STATUS_ENABLED );

}  // end winGetEnabled

// GameWindow::winHide ========================================================
/** Hide or show a window based on the hide parameter.
	* A hidden window can't be seen and accepts no input. */
//=============================================================================
// ?winHide@GameWindow@@QAEH_N@Z present-unmatched
Int GameWindow::winHide( Bool hide )
{

	if( hide )
	{

		//
		// if we're running in small game window mode and this window becomes
		// invisible then there's a good chance that the black border around
		// the game window needs redrawing
		//
		if( !BitTest( m_status, WIN_STATUS_NO_FLUSH ) )
			freeImages();

		BitSet( m_status, WIN_STATUS_HIDDEN );

		// notify the window manger we are hiding
		TheWindowManager->windowHiding( this );

	}  // end if
	else
	{

		BitClear( m_status, WIN_STATUS_HIDDEN );

	}  // end else

	return WIN_ERR_OK;

}  // end WinHide

// GameWindow::winIsHidden ====================================================
/** Am I hidden? */
//=============================================================================
// ?winIsHidden@GameWindow@@QAE_NXZ present-unmatched
Bool GameWindow::winIsHidden( void )
{

	return BitTest( m_status, WIN_STATUS_HIDDEN );

}  // end WinIsHidden

// GameWindow::winSetStatus ===================================================
/** Allows the user to directly set a window's status flags. */
//=============================================================================
UnsignedInt GameWindow::winSetStatus( UnsignedInt status )
{
	UnsignedInt oldStatus;

	oldStatus = m_status;
	BitSet( m_status, status );
//	m_status = status;

	return oldStatus;

}  // end WinSetStatus

// GameWindow::winClearStatus =================================================
/** Allows the user to directly clear a window's status flags. */
//=============================================================================
// ?winClearStatus@GameWindow@@QAEII@Z present-unmatched
UnsignedInt GameWindow::winClearStatus( UnsignedInt status )
{
	UnsignedInt oldStatus;

	oldStatus = m_status;
	BitClear( m_status, status );

	return oldStatus;

}  // end WinClearStatus

// GameWindow::winGetStatus ===================================================
/** Returns a window's status flags. */
//=============================================================================
// ?winGetStatus@GameWindow@@QAEIXZ present-unmatched
UnsignedInt GameWindow::winGetStatus( void )
{

	return m_status;

}  // end WinGetStatus

// GameWindow::winGetStyle ====================================================
/** Returns a window's style flags. */
//=============================================================================
// ?winGetStyle@GameWindow@@QAEIXZ present-unmatched
UnsignedInt GameWindow::winGetStyle( void )
{

	return m_instData.m_style;

}  // end WinGetStyle

// GameWindow::winSetHiliteState ==============================================
/** Set whether window is highlighted or not */
//=============================================================================
// ?winSetHiliteState@GameWindow@@QAEX_N@Z present-unmatched
void GameWindow::winSetHiliteState( Bool state )
{

	if( state )
		BitSet( m_instData.m_state, WIN_STATE_HILITED );
	else
		BitClear( m_instData.m_state, WIN_STATE_HILITED );

}  // end WinSetHiliteState

// GameWindow::winSetDrawOffset ===============================================
/** Set offset for drawing images */
//=============================================================================
// ?winSetDrawOffset@GameWindow@@QAEXHH@Z present-unmatched
void GameWindow::winSetDrawOffset( Int x, Int y )
{

	m_instData.m_imageOffset.x = x;
	m_instData.m_imageOffset.y = y;

}  // end WinSetDrawOffset

// GameWindow::winGetDrawOffset ===============================================
/** Get offset for drawing images */
//=============================================================================
// ?winGetDrawOffset@GameWindow@@QAEXPAH0@Z present-unmatched
void GameWindow::winGetDrawOffset( Int *x, Int *y )
{

	// sanity
	if( x == NULL || y == NULL )
		return;

	*x = m_instData.m_imageOffset.x;
	*y = m_instData.m_imageOffset.y;

}  // end WinGetDrawOffset

// GameWindow::winSetText =====================================================
/** Sets the text in a window */
//=============================================================================
// Retail body matched via MASM: Code/masm_dumps/winSetText_GameWindow_UAEHVUnicodeString_Z_479660.asm
// (BFME: m_instData@+0x30 + optional [this+4] vtbl+0xC notify; not ZH-shaped.)
#if 0
Int GameWindow::winSetText( UnicodeString newText )
{
	// copy text over
	m_instData.setText( newText );

	return WIN_ERR_OK;

}  // end WinSetText
#endif

// GameWindow::winGetText =====================================================
/** Get text from a window ... this works for static text windows and 
	* edit boxes */
//=============================================================================
// ?winGetText@GameWindow@@QAE?AVUnicodeString@@XZ present-unmatched
UnicodeString GameWindow::winGetText( void )
{
	// return the contents of our text field
	return m_instData.getText();

}  // end WinGetText

// GameWindow::winGetTextLength =====================================================
//=============================================================================
// ?winGetTextLength@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winGetTextLength()
{
	// return the contents of our text field
	return m_instData.getTextLength();

}  // end WinGetText

// GameWindow::winGetFont =====================================================
/** Get the font being used by this window */
//=============================================================================
// ?winGetFont@GameWindow@@QAEPAVGameFont@@XZ present-unmatched
GameFont *GameWindow::winGetFont( void )
{

	return m_instData.getFont();

}  // end WinGetFont

// GameWindow::winSetFont =====================================================
/** Set font for text in this window */
//=============================================================================
// ?winSetFont@GameWindow@@UAEXPAVGameFont@@@Z present-unmatched
void GameWindow::winSetFont( GameFont *font )
{

	// set font in window member
	m_instData.m_font = font;

	// set font for other display strings in special gadget window controls
	if( BitTest( m_instData.getStyle(), GWS_SCROLL_LISTBOX ) )
		GadgetListBoxSetFont( this, font );
	else if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetFont( this, font );
	else if( BitTest( m_instData.getStyle(), GWS_ENTRY_FIELD ) )
		GadgetTextEntrySetFont( this, font );
	else if( BitTest( m_instData.getStyle(), GWS_STATIC_TEXT ) )
		GadgetStaticTextSetFont( this, font );
	else
	{
		DisplayString *dString;

		// set the font for the display strings all windows have
		dString = m_instData.getTextDisplayString();
		if( dString )
			dString->setFont( font );
		dString = m_instData.getTooltipDisplayString();
		if( dString )
			dString->setFont( font );

	}  // end else

}  // end WinSetFont

// GameWindow::winSetEnabledTextColors ========================================
/** Set the text colors for the enabled state */
//=============================================================================
// ?winSetEnabledTextColors@GameWindow@@QAEXHH@Z present-unmatched
void GameWindow::winSetEnabledTextColors( Color color, Color borderColor )
{
	m_instData.m_enabledText.color = color;
	m_instData.m_enabledText.borderColor = borderColor;
	
	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetEnabledTextColors(this,  color, borderColor );
	

}  // end winSetEnabledTextColors

// GameWindow::winSetDisabledTextColors =======================================
/** Set the text colors for the disabled state */
//=============================================================================
// ?winSetDisabledTextColors@GameWindow@@QAEXHH@Z present-unmatched
void GameWindow::winSetDisabledTextColors( Color color, Color borderColor )
{

	m_instData.m_disabledText.color = color;
	m_instData.m_disabledText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetDisabledTextColors( this, color, borderColor );

}  // end winSetDisabledTextColors

// GameWindow::winSetHiliteTextColors =========================================
/** Set the text colors for the Hilite state */
//=============================================================================
// ?winSetHiliteTextColors@GameWindow@@QAEXHH@Z present-unmatched
void GameWindow::winSetHiliteTextColors( Color color, Color borderColor )
{

	m_instData.m_hiliteText.color = color;
	m_instData.m_hiliteText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetHiliteTextColors( this, color, borderColor );

}  // end winSetHiliteTextColors

// GameWindow::winSetIMECompositeTextColors =========================================
/** Set the text colors for the IME Composite state */
//=============================================================================
// ?winSetIMECompositeTextColors@GameWindow@@QAEXHH@Z present-unmatched
void GameWindow::winSetIMECompositeTextColors( Color color, Color borderColor )
{

	m_instData.m_imeCompositeText.color = color;
	m_instData.m_imeCompositeText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetIMECompositeTextColors( this, color, borderColor );
}  // end winSetIMECompositeTextColors

// GameWindow::winGetEnabledTextColor =========================================
/** Get the enabled text color */
//=============================================================================
// ?winGetEnabledTextColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetEnabledTextColor( void )
{

	return m_instData.m_enabledText.color;

}  // end winGetEnabledTextColor

// GameWindow::winGetEnabledTextBorderColor ===================================
/** Get the enabled text color */
//=============================================================================
// ?winGetEnabledTextBorderColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetEnabledTextBorderColor( void )
{

	return m_instData.m_enabledText.borderColor;

}  // end winGetEnabledTextBorderColor

// GameWindow::winGetDisabledTextColor ========================================
/** Get the disabled text color */
//=============================================================================
// ?winGetDisabledTextColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetDisabledTextColor( void )
{

	return m_instData.m_disabledText.color;

}  // end winGetDisabledTextColor

// GameWindow::winGetDisabledTextBorderColor ==================================
/** Get the disabled text color */
//=============================================================================
// ?winGetDisabledTextBorderColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetDisabledTextBorderColor( void )
{

	return m_instData.m_disabledText.borderColor;

}  // end winGetEnabledTextBorderColor

// GameWindow::winGetIMECompositeTextColor ==========================================
/** Get the IME composite text color */
//=============================================================================
// ?winGetIMECompositeTextColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetIMECompositeTextColor( void )
{

	return m_instData.m_imeCompositeText.color;

}  // end winGetIMECompositeTextColor

// GameWindow::winGetIMECompositeBorderColor ==========================================
/** Get the IME composite border color */
//=============================================================================
// ?winGetIMECompositeBorderColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetIMECompositeBorderColor( void )
{

	return m_instData.m_imeCompositeText.borderColor;

}  // end winGetIMECompositeBorderColor

// GameWindow::winGetHiliteTextColor ==========================================
/** Get the hilite text color */
//=============================================================================
// ?winGetHiliteTextColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetHiliteTextColor( void )
{

	return m_instData.m_hiliteText.color;

}  // end winGetHiliteTextColor

// GameWindow::winGetHiliteTextBorderColor ====================================
/** Get the hilite text color */
//=============================================================================
// ?winGetHiliteTextBorderColor@GameWindow@@QAEHXZ present-unmatched
Color GameWindow::winGetHiliteTextBorderColor( void )
{

	return m_instData.m_hiliteText.borderColor;

}  // end winGetHiliteTextBorderColor

// GameWindow::winSetInstanceData =============================================
/** Sets the window's instance data which includes parameters
	* such as background color. */
//=============================================================================
// ?winSetInstanceData@GameWindow@@QAEHPAVWinInstanceData@@@Z present-unmatched
Int GameWindow::winSetInstanceData( WinInstanceData *data )
{
	DisplayString *text, *tooltipText;

	// save our own instance of text and tooltip text display strings
	text = m_instData.m_text;
	tooltipText = m_instData.m_tooltip;

	// copy over all values from the inst data passed in
	// using memcpy is VERY VERY bad here, since the strings
	// must be copied 'correctly' or bad things will ensue
	m_instData = *data;

	// put our text instance pointers back
	m_instData.m_text = text;
	m_instData.m_tooltip = tooltipText;

	// make sure we didn't try to copy over a video buffer.
	m_instData.m_videoBuffer = NULL;

	// set our text display instance text if present
	if( data->getTextLength() )
		m_instData.setText( data->getText() );
	if( data->getTooltipTextLength() )
		m_instData.setTooltipText( data->getTooltipText() );

	return WIN_ERR_OK;

}  // end WinSetInstanceData

// GameWindow::winGetInstanceData =============================================
/** Return pointer to the instance data for this window */
//=============================================================================
// ?winGetInstanceData@GameWindow@@QAEPAVWinInstanceData@@XZ present-unmatched
WinInstanceData *GameWindow::winGetInstanceData( void )
{

	return &m_instData;

}  // end WinGetInstanceData

// GameWindow::winGetUserData =================================================
/** Return the user data stored */
//=============================================================================
// ?winGetUserData@GameWindow@@QAEPAXXZ present-unmatched
void *GameWindow::winGetUserData( void )
{

	return m_userData;

}  // end WinGetUserData

// GameWindow::winSetUserData =================================================
/** Set the user data stored */
//=============================================================================
// ?winSetUserData@GameWindow@@QAEXPAX@Z present-unmatched
void GameWindow::winSetUserData( void *data )
{

	m_userData = data;

}  // end WinSetUserData

// GameWindow::winSetTooltip ==================================================
/** Sets the window's tooltip text */
//=============================================================================
// ?winSetTooltip@GameWindow@@QAEXVUnicodeString@@@Z present-unmatched
void GameWindow::winSetTooltip( UnicodeString tip )
{

	m_instData.setTooltipText( tip );

}  // end WinSetTooltip

// GameWindow::winSetWindowId =================================================
/** Sets the window's id */
//=============================================================================
// ?winSetWindowId@GameWindow@@QAEHH@Z present-unmatched
Int GameWindow::winSetWindowId( Int id )
{

	m_instData.m_id = id;

	return WIN_ERR_OK;

}  // end WinSetWindowId

// GameWindow::winGetWindowId =================================================
/** Gets the window's id */
//=============================================================================
// ?winGetWindowId@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winGetWindowId( void )
{

	return m_instData.m_id;

}  // end WinGetWindowId

// GameWindow::winSetParent ===================================================
/** Sets this window's parent */
//=============================================================================

// BFME GameWindowManager::addWindowToParent is vtable +0xcc (slot 51).
// ZH header places it one slot earlier (+0xc8).
class GameWindowManager_AddParentSlot {
public:
	virtual void _pad0(void) = 0;
	virtual void _pad1(void) = 0;
	virtual void _pad2(void) = 0;
	virtual void _pad3(void) = 0;
	virtual void _pad4(void) = 0;
	virtual void _pad5(void) = 0;
	virtual void _pad6(void) = 0;
	virtual void _pad7(void) = 0;
	virtual void _pad8(void) = 0;
	virtual void _pad9(void) = 0;
	virtual void _pad10(void) = 0;
	virtual void _pad11(void) = 0;
	virtual void _pad12(void) = 0;
	virtual void _pad13(void) = 0;
	virtual void _pad14(void) = 0;
	virtual void _pad15(void) = 0;
	virtual void _pad16(void) = 0;
	virtual void _pad17(void) = 0;
	virtual void _pad18(void) = 0;
	virtual void _pad19(void) = 0;
	virtual void _pad20(void) = 0;
	virtual void _pad21(void) = 0;
	virtual void _pad22(void) = 0;
	virtual void _pad23(void) = 0;
	virtual void _pad24(void) = 0;
	virtual void _pad25(void) = 0;
	virtual void _pad26(void) = 0;
	virtual void _pad27(void) = 0;
	virtual void _pad28(void) = 0;
	virtual void _pad29(void) = 0;
	virtual void _pad30(void) = 0;
	virtual void _pad31(void) = 0;
	virtual void _pad32(void) = 0;
	virtual void _pad33(void) = 0;
	virtual void _pad34(void) = 0;
	virtual void _pad35(void) = 0;
	virtual void _pad36(void) = 0;
	virtual void _pad37(void) = 0;
	virtual void _pad38(void) = 0;
	virtual void _pad39(void) = 0;
	virtual void _pad40(void) = 0;
	virtual void _pad41(void) = 0;
	virtual void _pad42(void) = 0;
	virtual void _pad43(void) = 0;
	virtual void _pad44(void) = 0;
	virtual void _pad45(void) = 0;
	virtual void _pad46(void) = 0;
	virtual void _pad47(void) = 0;
	virtual void _pad48(void) = 0;
	virtual void _pad49(void) = 0;
	virtual void _pad50(void) = 0;
	virtual void addWindowToParent( GameWindow *window, GameWindow *parent ) = 0;
};

// BFME m_parent at +0x200; addWindowToParent at WM vtable +0xcc.
Int GameWindow::winSetParent( GameWindow *parent )
{
	struct ParentField {
		unsigned char pad[0x200];
		GameWindow *parent;
	};
	ParentField *self = reinterpret_cast<ParentField *>(this);

	if( self->parent == NULL)
	{
		// Top level window so unlink it
		TheWindowManager->unlinkWindow( this );
	}
	else
	{
		// A child window
		TheWindowManager->unlinkChildWindow( this );
	}

	if( parent == NULL )
	{

		// Want to make it a top level window so add to window list
		TheWindowManager->linkWindow( this );
		self->parent = NULL;

	}
	else
	{

		// Set it's new parent (BFME vtable slot)
		reinterpret_cast<GameWindowManager_AddParentSlot *>(TheWindowManager)
			->addWindowToParent( this, parent );

	}

	return WIN_ERR_OK;

}  // end WinSetParent

// GameWindow::winGetParent ===================================================
/** Gets the window's parent */
//=============================================================================
// ?winGetParent@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetParent( void )
{

	return m_parent;

}  // end WinGetParent

// GameWindow::winIsChild =====================================================
/** Determins if a window is a child/grand-child of a parent */
//=============================================================================
// BFME m_parent at +0x200 (same as winSetParent).
Bool GameWindow::winIsChild( GameWindow *child )
{
	struct ParentField {
		unsigned char pad[0x200];
		GameWindow *parent;
	};

	while( child )
	{
		GameWindow *parent = reinterpret_cast<ParentField *>(child)->parent;
		if( this == parent )
			return TRUE;
		child = parent;
	}

	return FALSE;

}  // end WinIsChild

// GameWindow::winGetChild ====================================================
/** Get the child window of this window */
//=============================================================================
// ?winGetChild@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetChild( void )
{

	return m_child;

}  // end WinGetChild

// GameWindow::winSetOwner ====================================================
/** Sets the window's owner */
//=============================================================================
// ?winSetOwner@GameWindow@@QAEHPAV1@@Z present-unmatched
Int GameWindow::winSetOwner( GameWindow *owner )
{

	if( owner == NULL )
		m_instData.m_owner = this;
	else
		m_instData.m_owner = owner;

	return WIN_ERR_OK;

}  // end WinSetOwner

// GameWindow::winGetOwner ====================================================
/** Gets the window's owner */
//=============================================================================
// ?winGetOwner@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetOwner( void )
{

	return m_instData.getOwner();

}  // end winGetOwner

// GameWindow::winSetNext =====================================================
/** Set next pointer */
//=============================================================================
// ?winSetNext@GameWindow@@QAEXPAV1@@Z present-unmatched
void GameWindow::winSetNext( GameWindow *next )
{

	m_next = next;

}  // end winSetNext

// GameWindow::winGetNext =====================================================
/** Gets the next window */
//=============================================================================
// ?winGetNext@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetNext( void )
{

	return m_next;

}  // end winGetNext

// GameWindow::winSetPrev =====================================================
/** Set prev pointer */
//=============================================================================
// ?winSetPrev@GameWindow@@QAEXPAV1@@Z present-unmatched
void GameWindow::winSetPrev( GameWindow *prev )
{

	m_prev = prev;

}  // end winSetPrev

// GameWindow::winGetPrev =====================================================
/** Get the previous window */
//=============================================================================
// ?winGetPrev@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetPrev( void )
{

	return m_prev;

}  // end winGetPrev

// GameWindow::winSetNextInLayout =============================================
/** Set next window in layout */
//=============================================================================
void GameWindow::winSetNextInLayout( GameWindow *next )
{
	m_nextLayout = next;
}

// GameWindow::winSetPrevInLayout =============================================
/** Set previous window in layout pointer */
//=============================================================================
void GameWindow::winSetPrevInLayout( GameWindow *prev )
{
	m_prevLayout = prev;
}

// GameWindow::winSetLayout ===================================================
/** Set this window as belonging to layout 'layout' */
//=============================================================================
void GameWindow::winSetLayout( WindowLayout *layout )
{
	m_layout = layout;
}

// GameWindow::winGetLayout ===================================================
/** Get layout this window is a part of, if any */
//=============================================================================
// ?winGetLayout@GameWindow@@QAEPAVWindowLayout@@XZ present-unmatched
WindowLayout *GameWindow::winGetLayout( void )
{
	return m_layout;
}

// GameWindow::winGetNextInLayout =============================================
/** Get next window in layout list if any */
//=============================================================================
// ?winGetNextInLayout@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetNextInLayout( void )
{
	return m_nextLayout;
}

// GameWindow::winGetPrevInLayout =============================================
/** Get prev window in layout list if any */
//=============================================================================
// ?winGetPrevInLayout@GameWindow@@QAEPAV1@XZ present-unmatched
GameWindow *GameWindow::winGetPrevInLayout( void )
{
	return m_prevLayout;
}

// GameWindow::winSetSystemFunc ===============================================
/** Sets the window's input, system, and redraw callback functions. */
//=============================================================================
// ?winSetSystemFunc@GameWindow@@QAEHP6A?AW4WindowMsgHandledType@@PAV1@III@Z@Z present-unmatched
Int GameWindow::winSetSystemFunc( GameWinSystemFunc system )
{
	if( system )
		m_system = system;
	else
		m_system = TheWindowManager->getDefaultSystem();

	return WIN_ERR_OK;

}  // end WinSetSystemFunc

// GameWindow::winSetInputFunc ================================================
/** Sets the window's input callback functions. */
//=============================================================================
// ?winSetInputFunc@GameWindow@@QAEHP6A?AW4WindowMsgHandledType@@PAV1@III@Z@Z present-unmatched
Int GameWindow::winSetInputFunc( GameWinInputFunc input )
{

	if( input )
		m_input = input;
	else
		m_input = TheWindowManager->getDefaultInput();

	return WIN_ERR_OK;

}  // end WinSetInputFunc

// GameWindow::winSetDrawFunc =================================================
/** Sets the window's redraw callback functions. */
//=============================================================================
// ?winSetDrawFunc@GameWindow@@QAEHP6AXPAV1@PAVWinInstanceData@@@Z@Z present-unmatched
Int GameWindow::winSetDrawFunc( GameWinDrawFunc draw )
{

	if( draw )
		m_draw = draw;
	else
		m_draw = TheWindowManager->getDefaultDraw();

	return WIN_ERR_OK;

}  // end WinSetDrawFunc

// GameWindow::winSetTooltipFunc ==============================================
/** Sets a window's tooltip callback */
//=============================================================================
// ?winSetTooltipFunc@GameWindow@@QAEHP6AXPAV1@PAVWinInstanceData@@I@Z@Z present-unmatched
Int GameWindow::winSetTooltipFunc( GameWinTooltipFunc tooltip )
{

	m_tooltip = tooltip;
	
	return WIN_ERR_OK;

}  // end WinSetTooltipFunc

// GameWindow::winSetCallbacks ================================================
/** Sets the window's input, tooltip, and redraw callback functions. */
//=============================================================================
// ?winSetCallbacks@GameWindow@@QAEHP6A?AW4WindowMsgHandledType@@PAV1@III@ZP6AX0PAVWinInstanceData@@@ZP6AX02I@Z@Z present-unmatched
Int GameWindow::winSetCallbacks( GameWinInputFunc input,
																 GameWinDrawFunc draw,
																 GameWinTooltipFunc tooltip )
{

	winSetInputFunc( input );
	winSetDrawFunc( draw );
	winSetTooltipFunc( tooltip );

	return WIN_ERR_OK;

}  // end WinSetCallbacks

// GameWindow::winDrawWindow ==================================================
/** Draws the default background for the specified window. */
//=============================================================================
// ?winDrawWindow@GameWindow@@QAEHXZ present-unmatched
Int GameWindow::winDrawWindow( void )
{

	if( BitTest( m_status, WIN_STATUS_HIDDEN ) == FALSE && m_draw )
		m_draw( this, &m_instData );

	return WIN_ERR_OK;

}  // end WinDrawWindow

// GameWindow::winPointInChild ================================================
/** Given a window and the mouse coordinates, return the child
	* window which contains the mouse pointer.  Child windows are
	* relative to their parents */
//=============================================================================
// ?winPointInChild@GameWindow@@QAEPAV1@HH_N0@Z present-unmatched
GameWindow *GameWindow::winPointInChild( Int x, Int y, Bool ignoreEnableCheck, Bool playDisabledSound )
{
	GameWindow *parent;
	GameWindow *child;
	ICoord2D origin;

	for( child = m_child; child; child = child->m_next ) 
	{

		origin = child->m_region.lo;
		parent = child->winGetParent();

		while( parent ) 
		{

			origin.x += parent->m_region.lo.x;
			origin.y += parent->m_region.lo.y;
			parent = parent->m_parent;

		}  // end while

		if( x >= origin.x && x <= origin.x + child->m_size.x &&
				y >= origin.y && y <= origin.y + child->m_size.y )
		{
			Bool enabled = ignoreEnableCheck || BitTest( child->m_status, WIN_STATUS_ENABLED );
			Bool hidden = BitTest( child->m_status, WIN_STATUS_HIDDEN );
			if( !hidden )
			{
				if( enabled )
				{
					return child->winPointInChild( x, y, ignoreEnableCheck, playDisabledSound );
				}
				else if( playDisabledSound )
				{
					AudioEventRTS disabledClick( "GUIClickDisabled" );
					if( TheAudio )
					{
						TheAudio->addAudioEvent( &disabledClick );
					}
				}
			}
		}

	}  // end for child

	// not in any children, must be in parent
	return this;

}  // end WinPointInChild

// GameWindow::winPointInAnyChild =============================================
/** Find the child in which the cursor resides; regardless of
	* whether or not the window is actually enabled */
//=============================================================================
// ?winPointInAnyChild@GameWindow@@QAEPAV1@HH_N0@Z present-unmatched
GameWindow *GameWindow::winPointInAnyChild( Int x, Int y, Bool ignoreHidden, Bool ignoreEnableCheck )
{
	GameWindow *parent;
	GameWindow *child;
	ICoord2D origin;

	for( child = m_child; child; child = child->m_next ) 
	{

		origin = child->m_region.lo;
		parent = child->m_parent;

		while( parent ) 
		{

			origin.x += parent->m_region.lo.x;
			origin.y += parent->m_region.lo.y;
			parent = parent->m_parent;

		}  // end while

		if( x >= origin.x && x <= origin.x + child->m_size.x &&
				y >= origin.y && y <= origin.y + child->m_size.y )
		{

			if( !(ignoreHidden == TRUE &&	BitTest( child->m_status, WIN_STATUS_HIDDEN )) )
				return child->winPointInChild( x, y, ignoreEnableCheck );

		}  // end if

	}  // end for child

	// not in any children, must be in parent
	return this;

}  // end WinPointInAnyChild

//
// In release builds the default input and system functions are optimized
// to the same address since they take the same input and have the same
// body.  Rather than fill them with bogus code we just want to make
// sure that different functions are actually created.  If you change the
// body of one but not the other so they are different, please remove
// the dummy code
//

// GameWinDefaultInput ========================================================
/** The default input callback.  Currently does nothing. */
//=============================================================================
WindowMsgHandledType GameWinDefaultInput( GameWindow *window, UnsignedInt msg,
													WindowMsgData mData1, WindowMsgData mData2 )
{

	return MSG_IGNORED;

}  // end GameWinDefaultInput

///< Input that blocks all (mouse) input like a wall, instead of passing like it wasn't there
WindowMsgHandledType GameWinBlockInput( GameWindow *window, UnsignedInt msg,
													WindowMsgData mData1, WindowMsgData mData2 )
{
	if (msg == GWM_CHAR || msg == GWM_MOUSE_POS)
		return MSG_IGNORED;
	
	//Added By Sadullah Nader
	//Fix for drag selecting in the control bar
	if (msg == GWM_LEFT_UP )//|| msg == GWM_LEFT_DRAG)
	{
		//stop drag selecting 
		
		TheSelectionTranslator->setLeftMouseButton(FALSE);
		TheSelectionTranslator->setDragSelecting(FALSE);
		
		TheTacticalView->setMouseLock( FALSE );
		TheInGameUI->setSelecting( FALSE );
		TheInGameUI->endAreaSelectHint(NULL);
		
	}

	return MSG_HANDLED;

}  // end GameWinBlockInput

// GameWinDefaultSystem =======================================================
/** The default system callback.  Currently does nothing. */
//=============================================================================
WindowMsgHandledType GameWinDefaultSystem( GameWindow *window, UnsignedInt msg, 
													 WindowMsgData mData1, WindowMsgData mData2 )
{

	return MSG_IGNORED;

}  // end GameWinDefaultSystem

// GameWinDefaultTooltip ======================================================
/** Default tooltip callback */
//=============================================================================
void GameWinDefaultTooltip( GameWindow *window, 
														WinInstanceData *instData,
														UnsignedInt mouse )
{
	return;

}  // end GameWinDefaultTooltip

// GameWinDefaultDraw =========================================================
/** Default draw, does nothing */
//=============================================================================
void GameWinDefaultDraw( GameWindow *window, WinInstanceData *instData )
{

	return;

}  // end GameWinDefaultDraw

// GameWindow::winSetEnabledImage =============================================
/** Set an enabled image into the draw data for the enabled state */
//=============================================================================
// ?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z present-unmatched
Int GameWindow::winSetEnabledImage( Int index, const Image *image )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set enabled image, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_enabledDrawData[ index ].image = image;
	return WIN_ERR_OK;

}  // end winSetEnabledImage

// GameWindow::winSetEnabledColor =============================================
/** set color for enabled state at index */
//=============================================================================
Int GameWindow::winSetEnabledColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set enabled color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_enabledDrawData[ index ].color = color;
	return WIN_ERR_OK;

}  // end winSetEnabledColor

// GameWindow::winSetEnabledBorderColor =======================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetEnabledBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set enabled border color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_enabledDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetEnabledBorderColor

// GameWindow::winSetDisabledImage ============================================
/** Set an disabled image into the draw data for the disabled state */
//=============================================================================
// ?winSetDisabledImage@GameWindow@@QAEHHPBVImage@@@Z present-unmatched
Int GameWindow::winSetDisabledImage( Int index, const Image *image )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set disabled image, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_disabledDrawData[ index ].image = image;
	return WIN_ERR_OK;

}  // end winSetDisabledImage

// GameWindow::winSetDisabledColor ============================================
/** set color for disabled state at index */
//=============================================================================
Int GameWindow::winSetDisabledColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set disabled color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_disabledDrawData[ index ].color = color;
	return WIN_ERR_OK;

}  // end winSetDisabledColor

// GameWindow::winSetDisabledBorderColor ======================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetDisabledBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set disabled border color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_disabledDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetDisabledBorderColor

// GameWindow::winSetHiliteImage ==============================================
/** Set an hilite image into the draw data for the hilite state */
//=============================================================================
// ?winSetHiliteImage@GameWindow@@QAEHHPBVImage@@@Z present-unmatched
Int GameWindow::winSetHiliteImage( Int index, const Image *image )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set hilite image, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_hiliteDrawData[ index ].image = image;
	return WIN_ERR_OK;

}  // end winSetHiliteImage

// GameWindow::winSetHiliteColor ==============================================
/** set color for hilite state at index */
//=============================================================================
Int GameWindow::winSetHiliteColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set hilite color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_hiliteDrawData[ index ].color = color;
	return WIN_ERR_OK;

}  // end winSetHiliteColor

// GameWindow::winSetHiliteBorderColor ========================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetHiliteBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
	{

		DEBUG_LOG(( "set hilite border color, index out of range '%d'\n", index ));
		assert( 0 );
		return WIN_ERR_INVALID_PARAMETER;

	}  // end if

	m_instData.m_hiliteDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetHiliteBorderColor

// GameWindow::winGetInputFunc ================================================
//=============================================================================
// ?winGetInputFunc@GameWindow@@QAEP6A?AW4WindowMsgHandledType@@PAV1@III@ZXZ present-unmatched
GameWinInputFunc GameWindow::winGetInputFunc( void )
{

	return m_input;

}  // end winGetInputFunc

// GameWindow::winGetSystemFunc ===============================================
//=============================================================================
// ?winGetSystemFunc@GameWindow@@QAEP6A?AW4WindowMsgHandledType@@PAV1@III@ZXZ present-unmatched
GameWinSystemFunc GameWindow::winGetSystemFunc( void )
{

	return m_system;

}  // end winGetSystemFunc

// GameWindow::winGetTooltipFunc ==============================================
//=============================================================================
// ?winGetTooltipFunc@GameWindow@@QAEP6AXPAV1@PAVWinInstanceData@@I@ZXZ present-unmatched
GameWinTooltipFunc GameWindow::winGetTooltipFunc( void )
{

	return m_tooltip;

}  // end winGetTooltipFunc

// GameWindow::winGetDrawFunc =================================================
//=============================================================================
// ?winGetDrawFunc@GameWindow@@QAEP6AXPAV1@PAVWinInstanceData@@@ZXZ present-unmatched
GameWinDrawFunc GameWindow::winGetDrawFunc( void )
{

	return m_draw;

}  // end winGetDrawFunc

// GameWindow::winSetEditData =================================================
//=============================================================================
// ?winSetEditData@GameWindow@@QAEXPAUGameWindowEditData@@@Z present-unmatched
void GameWindow::winSetEditData( GameWindowEditData *editData )
{

	m_editData = editData;

}  // end winSetEditData

// GameWindow::winGetEditData =================================================
//=============================================================================
// ?winGetEditData@GameWindow@@QAEPAUGameWindowEditData@@XZ present-unmatched
GameWindowEditData *GameWindow::winGetEditData( void )
{

	return m_editData;

}  // end winGetEditData
