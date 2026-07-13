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

// FILE: GameWindowTransitionsStyles.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Dec 2002
//
//	Filename: 	GameWindowTransitionsStyles.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The Actual Styles that can fire off.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/AudioEventRTS.h"
#include "Common/GameAudio.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/Controlbar.h"

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
void drawTypeText( GameWindow *window, DisplayString *str);
//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ??0Transition@@QAE@XZ present-unmatched
Transition::Transition ( void )
{
	
}

// ??1Transition@@UAE@XZ present-unmatched
Transition::~Transition( void )
{

}
//-----------------------------------------------------------------------------

// ??0FlashTransition@@QAE@XZ present-unmatched
FlashTransition::FlashTransition ( void )
{
	m_frameLength = FLASHTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1FlashTransition@@UAE@XZ present-unmatched
FlashTransition::~FlashTransition( void )
{
	m_win = NULL;
}

// ?init@FlashTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void FlashTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(FLASHTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;

}

// ?update@FlashTransition@@UAEXH@Z present-unmatched
void FlashTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < FLASHTRANSITION_START || frame > FLASHTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("FlashTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case FLASHTRANSITION_START:
		{
			
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case FLASHTRANSITION_FADE_IN_1:
		if(m_isForward)
		{
			AudioEventRTS buttonClick("GUIBoarderFadeIn");

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &buttonClick );
			}  // end if
		
		}
	case FLASHTRANSITION_FADE_IN_2:
	case FLASHTRANSITION_FADE_IN_3:
		{
			if(!m_win)
				break;
			m_win->winHide(TRUE);
			m_drawState = frame;
		}
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			if(!m_win)
				break;
			m_win->winHide(FALSE);
			m_drawState = frame;
		}
		break;
	case FLASHTRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
		break;
	}
	
	
}

// ?reverse@FlashTransition@@UAEXXZ present-unmatched
void FlashTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@FlashTransition@@UAEXXZ present-unmatched
void FlashTransition::draw( void )
{
	switch (m_drawState) 
	{
		case FLASHTRANSITION_FADE_IN_1:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,100));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 33));
		}
		break;
		case FLASHTRANSITION_FADE_IN_2:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,150));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 66));
		}
		break;
		case FLASHTRANSITION_FADE_IN_3:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,200));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 99));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 75));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255,50));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 25));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			TheDisplay->drawOpenRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x+1, m_pos.y+1,m_size.x-2, m_size.y, GameMakeColor(255, 255, 255, 10));
		}
		break;
	}
}
	
// ?skip@FlashTransition@@UAEXXZ present-unmatched
void FlashTransition::skip( void )
{
	update(FLASHTRANSITION_END);
}
	
//-----------------------------------------------------------------------------


// ??0ButtonFlashTransition@@QAE@XZ present-unmatched
ButtonFlashTransition::ButtonFlashTransition ( void )
{
	m_frameLength = BUTTONFLASHTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1ButtonFlashTransition@@UAE@XZ present-unmatched
ButtonFlashTransition::~ButtonFlashTransition( void )
{
	m_win = NULL;
}

// ?init@ButtonFlashTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void ButtonFlashTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(BUTTONFLASHTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_gradient = (Image *)TheMappedImageCollection->findImageByName("Gradient");
}

// ?update@ButtonFlashTransition@@UAEXH@Z present-unmatched
void ButtonFlashTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < BUTTONFLASHTRANSITION_START || frame > BUTTONFLASHTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ButtonFlashTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case BUTTONFLASHTRANSITION_START:
		{
			
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_1:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
				{
					AudioEventRTS buttonClick("GUIButtonsFadeIn");
	
					if( TheAudio )
					{
						TheAudio->addAudioEvent( &buttonClick );
					}  // end if

					m_drawState = frame;
				}
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_2:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_3:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2;		
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_IN_3;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_IN_2;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
				if(!m_win)
					break;
				m_win->winHide(TRUE);
				if(m_isForward)
					m_drawState = frame;
				else
					m_drawState = BUTTONFLASHTRANSITION_FADE_IN_1;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1:
		{
			if(!m_win)
				break;
			if(m_isForward)
			{
//				AudioEventRTS buttonClick("GUIBlip");
//	
//				if( TheAudio )
//				{
//					TheAudio->addAudioEvent( &buttonClick );
//				}  // end if

				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				
				m_win->winHide(TRUE);	
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4;
			}

		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2:
		{
			if(!m_win)
				break;
			if(m_isForward)
			{
				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);	
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1:
		{
			if(!m_win)
				break;
			if(m_isForward)
			{
				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);	
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2:
		{
			if(!m_win)
				break;
			if(m_isForward)
			{
				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);	
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3:
		{
			if(!m_win)
				break;
			if(m_isForward)
			{
				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(FALSE);			
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4:
		{

			if(!m_win)
				break;
			if(m_isForward)
			{
				m_win->winHide(FALSE);			
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(FALSE);	
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1;
			}
			
		}
		break;
	case BUTTONFLASHTRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
		break;
	}
	if(frame > BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4 && frame < BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1)
		m_drawState = BUTTONFLASHTRANSITION_SHOW_BACKGROUND;
	
}

// ?reverse@ButtonFlashTransition@@UAEXXZ present-unmatched
void ButtonFlashTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@ButtonFlashTransition@@UAEXXZ present-unmatched
void ButtonFlashTransition::draw( void )
{
	switch (m_drawState) 
	{
		case BUTTONFLASHTRANSITION_FADE_IN_1:
		{
			//PushButtonImageDrawThree(m_win, 100);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,100));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 75));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_IN_2:
		{
			//PushButtonImageDrawThree(m_win, 150);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,150));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 150));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_IN_3:
		{
			//PushButtonImageDrawThree(m_win, 200);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,200));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 200));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1:
		{
			PushButtonImageDrawThree(m_win, 255);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 150));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2:
		{
			PushButtonImageDrawThree(m_win, 255);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255,100));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3:
		{
			PushButtonImageDrawThree(m_win, 255);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 50));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			PushButtonImageDrawThree(m_win, 255);
			TheDisplay->drawOpenRect(m_pos.x, m_pos.y,m_size.x, m_size.y, 1, GameMakeColor(255, 255, 255,250));
			TheDisplay->drawFillRect(m_pos.x, m_pos.y,m_size.x, m_size.y, GameMakeColor(255, 255, 255, 15));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1:
		{
			if(m_isForward)
				PushButtonImageDrawThree(m_win, 255);
			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,100));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2:
		{
			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,200));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1:
		{
			if(!m_isForward)
				PushButtonImageDrawThree(m_win, 255);

			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,150));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2:
		{
			if(!m_isForward)
				PushButtonImageDrawThree(m_win, 255);

			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,100));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3:
		{
			if(!m_isForward)
				PushButtonImageDrawThree(m_win, 255);

			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,50));
		}
		break;
		case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4:
		{
			if(!m_isForward)
				PushButtonImageDrawThree(m_win, 255);

			TheDisplay->drawImage(m_gradient, m_pos.x, m_pos.y, m_pos.x +m_size.x, m_pos.y + m_size.y,GameMakeColor(255,255,255,17));
		}
		break;
		case BUTTONFLASHTRANSITION_SHOW_BACKGROUND:
		{
			PushButtonImageDrawThree(m_win, 255);
		}
		break;

	}
}
	
// ?skip@ButtonFlashTransition@@UAEXXZ present-unmatched
void ButtonFlashTransition::skip( void )
{
	update(BUTTONFLASHTRANSITION_END);
}


//-----------------------------------------------------------------------------

// ??0FadeTransition@@QAE@XZ present-unmatched
FadeTransition::FadeTransition ( void )
{
	m_frameLength = FADETRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1FadeTransition@@UAE@XZ present-unmatched
FadeTransition::~FadeTransition( void )
{
	m_win = NULL;
}

// ?init@FadeTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void FadeTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(FADETRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
}

void FadeTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < FADETRANSITION_START || frame > FADETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("FadeTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case FADETRANSITION_START:
		{
			
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case FADETRANSITION_FADE_IN_1:
	case FADETRANSITION_FADE_IN_2:
	case FADETRANSITION_FADE_IN_3:
	case FADETRANSITION_FADE_IN_4:
	case FADETRANSITION_FADE_IN_5:
	case FADETRANSITION_FADE_IN_6:
	case FADETRANSITION_FADE_IN_7:
	case FADETRANSITION_FADE_IN_8:
	case FADETRANSITION_FADE_IN_9:
		m_win->winHide(TRUE);

		m_drawState = frame;
		break;
	case FADETRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}

// ?reverse@FadeTransition@@UAEXXZ present-unmatched
void FadeTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@FadeTransition@@UAEXXZ present-unmatched
void FadeTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_win->winGetEnabledImage(0);
	switch (m_drawState) 
	{
		case FADETRANSITION_FADE_IN_1:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 25));
		}
		break;
		case FADETRANSITION_FADE_IN_2:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 50));
		}
		break;
		case FADETRANSITION_FADE_IN_3:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 75));
		}
		break;
		case FADETRANSITION_FADE_IN_4:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 100));
		}
		break;
		case FADETRANSITION_FADE_IN_5:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 125));
		}
		break;
		case FADETRANSITION_FADE_IN_6:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 150));
		}
		break;
		case FADETRANSITION_FADE_IN_7:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 175));
		}
		break;
		case FADETRANSITION_FADE_IN_8:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 200));
		}
		break;
		case FADETRANSITION_FADE_IN_9:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 225));
		}
	}
}
	
// ?skip@FadeTransition@@UAEXXZ present-unmatched
void FadeTransition::skip( void )
{
	update(FADETRANSITION_END);
}
//-----------------------------------------------------------------------------

// ??0ScaleUpTransition@@QAE@XZ present-unmatched
ScaleUpTransition::ScaleUpTransition ( void )
{
	m_frameLength = SCALEUPTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1ScaleUpTransition@@UAE@XZ present-unmatched
ScaleUpTransition::~ScaleUpTransition( void )
{
	m_win = NULL;
}

// ?init@ScaleUpTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void ScaleUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(SCALEUPTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	
	m_centerPos.x = m_pos.x + m_size.x / 2;
	m_centerPos.y = m_pos.y + m_size.y / 2;
	m_incrementSize.x = m_size.x / SCALEUPTRANSITION_END;
	m_incrementSize.y = m_size.y / SCALEUPTRANSITION_END;

}

// ?update@ScaleUpTransition@@UAEXH@Z present-unmatched
void ScaleUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < SCALEUPTRANSITION_START || frame > SCALEUPTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ScaleUpTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case SCALEUPTRANSITION_START:
		{
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case SCALEUPTRANSITION_1:
		if(m_isForward)
		{
			AudioEventRTS buttonClick("GUILogoMouseOver");

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &buttonClick );
			}  // end if

			
		}

	case SCALEUPTRANSITION_2:
	case SCALEUPTRANSITION_3:
	case SCALEUPTRANSITION_4:
	case SCALEUPTRANSITION_5:
//	case SCALEUPTRANSITION_6:
//	case SCALEUPTRANSITION_7:
//	case SCALEUPTRANSITION_8:
//	case SCALEUPTRANSITION_9:
//	case SCALEUPTRANSITION_10:
//	case SCALEUPTRANSITION_11:
//	case SCALEUPTRANSITION_12:
//	case SCALEUPTRANSITION_13:
//	case SCALEUPTRANSITION_14:
//	case SCALEUPTRANSITION_15:
//	case SCALEUPTRANSITION_16:
//	case SCALEUPTRANSITION_17:
//	case SCALEUPTRANSITION_18:
//	case SCALEUPTRANSITION_19:
		if(m_win)
			m_win->winHide(TRUE);
		m_drawState = frame;
		break;
	case SCALEUPTRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}

// ?reverse@ScaleUpTransition@@UAEXXZ present-unmatched
void ScaleUpTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@ScaleUpTransition@@UAEXXZ present-unmatched
void ScaleUpTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_win->winGetEnabledImage(0);
	if(m_drawState <= SCALEUPTRANSITION_START || m_drawState >= SCALEUPTRANSITION_END)
		return;
	Int x = m_centerPos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_centerPos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = x + m_incrementSize.x * m_drawState;
	Int y1 = y + m_incrementSize.y * m_drawState;
	TheDisplay->drawImage(image, x,y, x1, y1);
}
	
// ?skip@ScaleUpTransition@@UAEXXZ present-unmatched
void ScaleUpTransition::skip( void )
{
	update(SCALEUPTRANSITION_END);
}

//-----------------------------------------------------------------------------

// ??0ScoreScaleUpTransition@@QAE@XZ present-unmatched
ScoreScaleUpTransition::ScoreScaleUpTransition ( void )
{
	m_frameLength = SCORESCALEUPTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1ScoreScaleUpTransition@@UAE@XZ present-unmatched
ScoreScaleUpTransition::~ScoreScaleUpTransition( void )
{
	m_win = NULL;
}

// ?init@ScoreScaleUpTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void ScoreScaleUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(SCORESCALEUPTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	
	m_centerPos.x = m_pos.x + m_size.x / 2;
	m_centerPos.y = m_pos.y + m_size.y / 2;
	m_incrementSize.x = m_size.x / SCORESCALEUPTRANSITION_END;
	m_incrementSize.y = m_size.y / SCORESCALEUPTRANSITION_END;

}

// ?update@ScoreScaleUpTransition@@UAEXH@Z present-unmatched
void ScoreScaleUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < SCORESCALEUPTRANSITION_START || frame > SCORESCALEUPTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ScoreScaleUpTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case SCORESCALEUPTRANSITION_START:
		{
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case SCORESCALEUPTRANSITION_1:
		if(m_isForward)
		{
			AudioEventRTS buttonClick("GUIScoreScreenPictures");

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &buttonClick );
			}  // end if

			
		}

	case SCORESCALEUPTRANSITION_2:
	case SCORESCALEUPTRANSITION_3:
	case SCORESCALEUPTRANSITION_4:
	case SCORESCALEUPTRANSITION_5:
//	case SCORESCALEUPTRANSITION_6:
//	case SCORESCALEUPTRANSITION_7:
//	case SCORESCALEUPTRANSITION_8:
//	case SCORESCALEUPTRANSITION_9:
//	case SCORESCALEUPTRANSITION_10:
//	case SCORESCALEUPTRANSITION_11:
//	case SCORESCALEUPTRANSITION_12:
//	case SCORESCALEUPTRANSITION_13:
//	case SCORESCALEUPTRANSITION_14:
//	case SCORESCALEUPTRANSITION_15:
//	case SCORESCALEUPTRANSITION_16:
//	case SCORESCALEUPTRANSITION_17:
//	case SCORESCALEUPTRANSITION_18:
//	case SCORESCALEUPTRANSITION_19:
		if(m_win)
			m_win->winHide(TRUE);
		m_drawState = frame;
		break;
	case SCORESCALEUPTRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}

// ?reverse@ScoreScaleUpTransition@@UAEXXZ present-unmatched
void ScoreScaleUpTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@ScoreScaleUpTransition@@UAEXXZ present-unmatched
void ScoreScaleUpTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_win->winGetEnabledImage(0);
	if(m_drawState <= SCORESCALEUPTRANSITION_START || m_drawState >= SCORESCALEUPTRANSITION_END)
		return;
	Int x = m_centerPos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_centerPos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = x + m_incrementSize.x * m_drawState;
	Int y1 = y + m_incrementSize.y * m_drawState;
	TheDisplay->drawImage(image, x,y, x1, y1);
}
	
// ?skip@ScoreScaleUpTransition@@UAEXXZ present-unmatched
void ScoreScaleUpTransition::skip( void )
{
	update(SCORESCALEUPTRANSITION_END);
}

//-----------------------------------------------------------------------------

// ??0MainMenuScaleUpTransition@@QAE@XZ present-unmatched
MainMenuScaleUpTransition::MainMenuScaleUpTransition ( void )
{
	m_frameLength = MAINMENUSCALEUPTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1MainMenuScaleUpTransition@@UAE@XZ present-unmatched
MainMenuScaleUpTransition::~MainMenuScaleUpTransition( void )
{
	m_win = NULL;
}

// ?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void MainMenuScaleUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_growWin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("MainMenu.wnd:WinGrowMarker"));
	if(!m_growWin)
		return;

	m_growWin->winGetSize(&m_growSize.x, &m_growSize.y);
	m_growWin->winGetScreenPosition(&m_growPos.x, &m_growPos.y );

	m_isForward = FALSE;
	update(MAINMENUSCALEUPTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_incrementPos.x = (m_growPos.x - m_pos.x)  / MAINMENUSCALEUPTRANSITION_END;
	m_incrementPos.y = (m_growPos.y - m_pos.y)  / MAINMENUSCALEUPTRANSITION_END;
	m_incrementSize.x = (m_growSize.x - m_size.x) / MAINMENUSCALEUPTRANSITION_END;
	m_incrementSize.y = (m_growSize.y - m_size.y) / MAINMENUSCALEUPTRANSITION_END;
	const Image *image = m_win->winGetDisabledImage(0);
	m_growWin->winSetEnabledImage(0, image);
	
}

// ?update@MainMenuScaleUpTransition@@UAEXH@Z present-unmatched
void MainMenuScaleUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < MAINMENUSCALEUPTRANSITION_START || frame > MAINMENUSCALEUPTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("MainMenuScaleUpTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case MAINMENUSCALEUPTRANSITION_START:
		{
			
			if(m_isForward || !m_win || !m_growWin)
				break;
//			m_win->winHide(TRUE);
			m_growWin->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case MAINMENUSCALEUPTRANSITION_END:
		{
			if(!m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(TRUE);
			m_growWin->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
	if(frame == 1)
	{
		AudioEventRTS buttonClick("GUILogoSelect");

		if( TheAudio )
		{
			TheAudio->addAudioEvent( &buttonClick );
		}  // end if			
	}
	if(frame > MAINMENUSCALEUPTRANSITION_START && frame < MAINMENUSCALEUPTRANSITION_END)
	{
		if(m_win)
			m_win->winHide(TRUE);
		if(m_growWin)
			m_growWin->winHide(TRUE);
		m_drawState = frame;
	}

}

// ?reverse@MainMenuScaleUpTransition@@UAEXXZ present-unmatched
void MainMenuScaleUpTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@MainMenuScaleUpTransition@@UAEXXZ present-unmatched
void MainMenuScaleUpTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_growWin->winGetEnabledImage(0);
	if(m_drawState <= MAINMENUSCALEUPTRANSITION_START || m_drawState >= MAINMENUSCALEUPTRANSITION_END)
		return;
	Int x = m_pos.x + ((m_incrementPos.x * m_drawState));
	Int y = m_pos.y + ((m_incrementPos.y * m_drawState));
	Int x1 = x + m_size.x + ((m_incrementSize.x * m_drawState));
	Int y1 = y + m_size.y + ((m_incrementSize.y * m_drawState));
	TheDisplay->drawImage(image, x,y, x1, y1);
}
	
// ?skip@MainMenuScaleUpTransition@@UAEXXZ present-unmatched
void MainMenuScaleUpTransition::skip( void )
{
	update(MAINMENUSCALEUPTRANSITION_END);
}

//-----------------------------------------------------------------------------

// ??0MainMenuMediumScaleUpTransition@@QAE@XZ present-unmatched
MainMenuMediumScaleUpTransition::MainMenuMediumScaleUpTransition ( void )
{
	m_frameLength = MAINMENUMEDIUMSCALEUPTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1MainMenuMediumScaleUpTransition@@UAE@XZ present-unmatched
MainMenuMediumScaleUpTransition::~MainMenuMediumScaleUpTransition( void )
{
	m_win = NULL;
}

// ?init@MainMenuMediumScaleUpTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void MainMenuMediumScaleUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	AsciiString growWinName;
	growWinName = m_win->winGetInstanceData()->m_decoratedNameString;
	growWinName.concat("Medium");
	m_growWin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(growWinName));
	if(!m_growWin)
		return;

	m_growWin->winGetSize(&m_growSize.x, &m_growSize.y);
	m_growWin->winGetScreenPosition(&m_growPos.x, &m_growPos.y );

	m_isForward = FALSE;
	update(MAINMENUMEDIUMSCALEUPTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	
	m_incrementSize.x = (m_growSize.x - m_size.x) / MAINMENUMEDIUMSCALEUPTRANSITION_END;
	m_incrementSize.y = (m_growSize.y - m_size.y) / MAINMENUMEDIUMSCALEUPTRANSITION_END;
//	const Image *image = m_win->winGetEnabledImage(0);
	//m_growWin->winSetEnabledImage(0, image);
	
}

// ?update@MainMenuMediumScaleUpTransition@@UAEXH@Z present-unmatched
void MainMenuMediumScaleUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < MAINMENUMEDIUMSCALEUPTRANSITION_START || frame > MAINMENUMEDIUMSCALEUPTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("MainMenuMediumScaleUpTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case MAINMENUMEDIUMSCALEUPTRANSITION_START:
		{
			
			if(m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(FALSE);
			m_growWin->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case MAINMENUMEDIUMSCALEUPTRANSITION_END:
		{
			if(!m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(TRUE);
			m_growWin->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
	if(frame > MAINMENUMEDIUMSCALEUPTRANSITION_START && frame < MAINMENUMEDIUMSCALEUPTRANSITION_END)
	{
		if(frame == 1 && m_isForward)
		{
			AudioEventRTS buttonClick("GUILogoMouseOver");

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &buttonClick );
			}  // end if			
		}
		if(m_win)
			m_win->winHide(TRUE);
		if(m_growWin)
			m_growWin->winHide(TRUE);
		m_drawState = frame;
	}
}

void MainMenuMediumScaleUpTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
	m_win->winHide(TRUE);
	m_growWin->winHide(TRUE);

}

// ?draw@MainMenuMediumScaleUpTransition@@UAEXXZ present-unmatched
void MainMenuMediumScaleUpTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_win->winGetEnabledImage(0);
	if(m_drawState <= MAINMENUMEDIUMSCALEUPTRANSITION_START || m_drawState >= MAINMENUMEDIUMSCALEUPTRANSITION_END)
		return;
	Int x = m_pos.x - ((m_incrementSize.x * m_drawState) /2);
	Int y = m_pos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = m_pos.x + m_size.x + ((m_incrementSize.x * m_drawState) / 2);
	Int y1 = m_pos.y + m_size.y + ((m_incrementSize.y * m_drawState) / 2);
	TheDisplay->drawImage(image, x,y, x1, y1);
}
	
// ?skip@MainMenuMediumScaleUpTransition@@UAEXXZ present-unmatched
void MainMenuMediumScaleUpTransition::skip( void )
{
	update(MAINMENUMEDIUMSCALEUPTRANSITION_END);
}
//-----------------------------------------------------------------------------

// ??0MainMenuSmallScaleDownTransition@@QAE@XZ present-unmatched
MainMenuSmallScaleDownTransition::MainMenuSmallScaleDownTransition ( void )
{
	m_frameLength = MAINMENUSMALLSCALEDOWNTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
}

// ??1MainMenuSmallScaleDownTransition@@UAE@XZ present-unmatched
MainMenuSmallScaleDownTransition::~MainMenuSmallScaleDownTransition( void )
{
	m_win = NULL;
}

// ?init@MainMenuSmallScaleDownTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void MainMenuSmallScaleDownTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	AsciiString growWinName;
	growWinName = m_win->winGetInstanceData()->m_decoratedNameString;
	growWinName.concat("Small");
	m_growWin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(growWinName));
	if(!m_growWin)
		return;

	m_growWin->winGetSize(&m_growSize.x, &m_growSize.y);
	m_growWin->winGetScreenPosition(&m_growPos.x, &m_growPos.y );

	m_isForward = FALSE;
	update(MAINMENUSMALLSCALEDOWNTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	
	m_incrementSize.x = (m_growSize.x - m_size.x) / MAINMENUSMALLSCALEDOWNTRANSITION_END;
	m_incrementSize.y = (m_growSize.y - m_size.y) / MAINMENUSMALLSCALEDOWNTRANSITION_END;
	const Image *image = m_win->winGetEnabledImage(0);
	m_growWin->winSetEnabledImage(0, image);
	
}

void MainMenuSmallScaleDownTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < MAINMENUSMALLSCALEDOWNTRANSITION_START || frame > MAINMENUSMALLSCALEDOWNTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("MainMenuSmallScaleDownTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case MAINMENUSMALLSCALEDOWNTRANSITION_START:
		{
			
			if(m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(FALSE);
			m_growWin->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case MAINMENUSMALLSCALEDOWNTRANSITION_1:
	case MAINMENUSMALLSCALEDOWNTRANSITION_2:
	case MAINMENUSMALLSCALEDOWNTRANSITION_3:
	case MAINMENUSMALLSCALEDOWNTRANSITION_4:
	case MAINMENUSMALLSCALEDOWNTRANSITION_5:
		if(m_win)
			m_win->winHide(TRUE);
		if(m_growWin)
			m_growWin->winHide(TRUE);
		m_drawState = frame;
		break;
	case MAINMENUSMALLSCALEDOWNTRANSITION_END:
		{
			if(!m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(TRUE);
			m_growWin->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}

// ?reverse@MainMenuSmallScaleDownTransition@@UAEXXZ present-unmatched
void MainMenuSmallScaleDownTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@MainMenuSmallScaleDownTransition@@UAEXXZ present-unmatched
void MainMenuSmallScaleDownTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = m_win->winGetEnabledImage(0);
	if(m_drawState <= MAINMENUSMALLSCALEDOWNTRANSITION_START || m_drawState >= MAINMENUSMALLSCALEDOWNTRANSITION_END)
		return;
	Int x = m_pos.x - ((m_incrementSize.x * m_drawState) /2);
	Int y = m_pos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = m_pos.x + m_size.x + ((m_incrementSize.x * m_drawState) / 2);
	Int y1 = m_pos.y + m_size.y + ((m_incrementSize.y * m_drawState) / 2);
	TheDisplay->drawImage(image, x,y, x1, y1);
}
	
// ?skip@MainMenuSmallScaleDownTransition@@UAEXXZ present-unmatched
void MainMenuSmallScaleDownTransition::skip( void )
{
	update(MAINMENUSMALLSCALEDOWNTRANSITION_END);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// ??0TextTypeTransition@@QAE@XZ present-unmatched
TextTypeTransition::TextTypeTransition ( void )
{
	m_frameLength = TEXTTYPETRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
	m_dStr = NULL;
}

// ??1TextTypeTransition@@UAE@XZ present-unmatched
TextTypeTransition::~TextTypeTransition( void )
{
	m_win = NULL;
	if(m_dStr)
		TheDisplayStringManager->freeDisplayString(m_dStr);
	m_dStr = NULL;
}

// ?init@TextTypeTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void TextTypeTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}
	m_isForward = FALSE;
	update(TEXTTYPETRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_dStr = TheDisplayStringManager->newDisplayString();
	m_fullText = GadgetStaticTextGetText(m_win);		
	Int length = m_fullText.getLength();
	m_frameLength = MIN(length, TEXTTYPETRANSITION_END);
}

// ?update@TextTypeTransition@@UAEXH@Z present-unmatched
void TextTypeTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < TEXTTYPETRANSITION_START || frame > TEXTTYPETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("TextTypeTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case TEXTTYPETRANSITION_START:
		{
			
			if(m_isForward || !m_win )
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case TEXTTYPETRANSITION_END:
		{
			if(!m_isForward || !m_win )
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
	if(frame >= m_frameLength)
	{
		m_win->winHide(FALSE);

	}
	if(frame > TEXTTYPETRANSITION_START && frame < m_frameLength)
	{
		m_win->winHide(TRUE);
		m_drawState = frame;
		AudioEventRTS buttonClick("GUITypeText");

		if( TheAudio )
		{
			TheAudio->addAudioEvent( &buttonClick );
		}  // end if
		if(m_isForward)
		{
			m_partialText.concat(m_fullText.getCharAt(frame - 1));
		}
		else
		{
			m_partialText.removeLastChar();
		}
	}
}

// ?reverse@TextTypeTransition@@UAEXXZ present-unmatched
void TextTypeTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;

	m_partialText = m_fullText;
}

// ?draw@TextTypeTransition@@UAEXXZ present-unmatched
void TextTypeTransition::draw( void )
{
	if(m_drawState > TEXTTYPETRANSITION_START && m_drawState < m_frameLength)
	{
		m_dStr->setText(m_partialText);
		drawTypeText(m_win, m_dStr);
	}
}
	
// ?skip@TextTypeTransition@@UAEXXZ present-unmatched
void TextTypeTransition::skip( void )
{
	update(TEXTTYPETRANSITION_END);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// ??0CountUpTransition@@QAE@XZ present-unmatched
CountUpTransition::CountUpTransition ( void )
{
	m_frameLength = COUNTUPTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;

}

// ??1CountUpTransition@@UAE@XZ present-unmatched
CountUpTransition::~CountUpTransition( void )
{
	m_win = NULL;
}

// ?init@CountUpTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void CountUpTransition::init( GameWindow *win )
{
	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );

		if( m_win->winIsHidden() )
		{
			m_isForward = TRUE;
			m_isFinished = TRUE;
			m_frameLength = 0;
			return;
		}
	}
	m_fullText = GadgetStaticTextGetText(m_win);		
	m_isForward = FALSE;
	update(COUNTUPTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	
	AsciiString tempStr;
	tempStr.translate(m_fullText);
	m_intValue = atoi(tempStr.str());
	DEBUG_LOG(("CountUpTransition::init %hs %s %d\n", m_fullText.str(), tempStr.str(), m_intValue));
	if(m_intValue < COUNTUPTRANSITION_END)
	{
		m_countState = COUNT_ONES;
		m_frameLength = MIN(m_intValue, COUNTUPTRANSITION_END);
	}
	else if(m_intValue/100 < COUNTUPTRANSITION_END)
	{
		m_countState = COUNT_100S;
		m_frameLength = MIN(m_intValue/100, COUNTUPTRANSITION_END);
	}
	else
	{
		m_countState = COUNT_1000S;
		m_frameLength = MIN(m_intValue/1000, COUNTUPTRANSITION_END);
	}
	
	m_currentValue = 0;
	UnicodeString currVal;
	currVal.format(L"%d",m_currentValue);
	GadgetStaticTextSetText(m_win, currVal);
}

// ?update@CountUpTransition@@UAEXH@Z present-unmatched
void CountUpTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < COUNTUPTRANSITION_START || frame > COUNTUPTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("CountUpTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case COUNTUPTRANSITION_START:
		{
			
			if(m_isForward || !m_win )
				break;
			m_currentValue = 0;
			UnicodeString currVal;
			currVal.format(L"%d",m_currentValue);
			GadgetStaticTextSetText(m_win, currVal);

			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case COUNTUPTRANSITION_END:
		{
			if(!m_isForward || !m_win )
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
	if(frame >= m_frameLength)
	{
		m_win->winHide(FALSE);

	}
	if(frame > COUNTUPTRANSITION_START && frame < m_frameLength)
	{
		m_win->winHide(FALSE);
		m_drawState = frame;
		AudioEventRTS buttonClick("GUIScoreScreenTick");

		if( TheAudio )
		{
			TheAudio->addAudioEvent( &buttonClick );
		}  // end if
		m_currentValue +=m_countState;
		if(m_currentValue > m_intValue)
			m_currentValue = m_intValue;

		UnicodeString currVal;
		currVal.format(L"%d",m_currentValue);
		GadgetStaticTextSetText(m_win, currVal);
	}
	if( frame == m_frameLength )
	{
		GadgetStaticTextSetText(m_win, m_fullText);
		m_isFinished = TRUE;
	}
}

void CountUpTransition::reverse( void )
{
	if( m_win->winIsHidden() )
	{
		m_isForward = FALSE;
		m_isFinished = TRUE;
		m_frameLength = 0;
		return;
	}
	m_isFinished = FALSE;
	m_isForward = FALSE;

}

// ?draw@CountUpTransition@@UAEXXZ present-unmatched
void CountUpTransition::draw( void )
{
}
	
// ?skip@CountUpTransition@@UAEXXZ present-unmatched
void CountUpTransition::skip( void )
{
	if (!m_isFinished)
		update(COUNTUPTRANSITION_END);
}

//-----------------------------------------------------------------------------

// ??0ScreenFadeTransition@@QAE@XZ present-unmatched
ScreenFadeTransition::ScreenFadeTransition ( void )
{
	m_frameLength = SCREENFADETRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
	
}

// ??1ScreenFadeTransition@@UAE@XZ present-unmatched
ScreenFadeTransition::~ScreenFadeTransition( void )
{
	m_win = NULL;
	
}

// ?init@ScreenFadeTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void ScreenFadeTransition::init( GameWindow *win )
{
	m_isForward = FALSE;
	update(SCREENFADETRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;

	m_percent = 1.0f / (SCREENFADETRANSITION_END - 1);

	m_pos.y = m_pos.x = 0;
	m_size.x = TheDisplay->getWidth();
	m_size.y = TheDisplay->getHeight();

}

// ?update@ScreenFadeTransition@@UAEXH@Z present-unmatched
void ScreenFadeTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < SCREENFADETRANSITION_START || frame > SCREENFADETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ScreenFadeTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case SCREENFADETRANSITION_START:
		{
			m_isFinished = TRUE;
		}
		break;
	case SCREENFADETRANSITION_END:
		{
			m_isFinished = TRUE;
		}
	}	
	m_drawState = frame;	
}

// ?reverse@ScreenFadeTransition@@UAEXXZ present-unmatched
void ScreenFadeTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
}

// ?draw@ScreenFadeTransition@@UAEXXZ present-unmatched
void ScreenFadeTransition::draw( void )
{
	Int alpha = m_percent*255 *m_drawState;
	if(alpha > 255)
		alpha = 255;
	TheDisplay->drawFillRect(m_pos.x, m_pos.y, m_size.x, m_size.y , GameMakeColor(0,0,0,alpha));

}
	
// ?skip@ScreenFadeTransition@@UAEXXZ present-unmatched
void ScreenFadeTransition::skip( void )
{
	update(SCREENFADETRANSITION_END);
}


//-----------------------------------------------------------------------------

// ??0ControlBarArrowTransition@@QAE@XZ present-unmatched
ControlBarArrowTransition::ControlBarArrowTransition ( void )
{
	m_frameLength = CONTROLBARARROWTRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
	m_arrowImage = NULL;
	
}

// ??1ControlBarArrowTransition@@UAE@XZ present-unmatched
ControlBarArrowTransition::~ControlBarArrowTransition( void )
{
	m_win = NULL;
	m_arrowImage = NULL;
}

void ControlBarArrowTransition::init( GameWindow *win )
{
	m_isForward = FALSE;
	update(CONTROLBARARROWTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;

	m_percent = 1.0f / CONTROLBARARROWTRANSITION_BEGIN_FADE;
	m_fadePercent = 1.0f/ (CONTROLBARARROWTRANSITION_END - CONTROLBARARROWTRANSITION_BEGIN_FADE);
	
	m_arrowImage = TheControlBar->getArrowImage();
	GameWindow *twin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
	if(!twin || !m_arrowImage)
	{
		m_isFinished = TRUE;
		return;
	}
	ICoord2D screenPos, screenSize;
	twin->winGetScreenPosition(&screenPos.x, &screenPos.y);
	twin->winGetSize(&screenSize.x, &screenSize.y);
	
	m_incrementPos.x = 0;
	m_incrementPos.y = screenPos.y * m_percent;

	m_pos.y = 0 - m_arrowImage->getImageHeight() + 20;
	m_pos.x = (screenPos.x + screenSize.x /2) - m_arrowImage->getImageWidth() /2;

	m_size.x = m_arrowImage->getImageWidth();
	m_size.y = m_arrowImage->getImageHeight();

}

void ControlBarArrowTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < CONTROLBARARROWTRANSITION_START || frame > CONTROLBARARROWTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ControlBarArrowTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case CONTROLBARARROWTRANSITION_START:
		{
			m_isFinished = TRUE;
		}
		break;
	case CONTROLBARARROWTRANSITION_END:
		{
			m_isFinished = TRUE;
		}
	}	
	m_drawState = frame;	
}

// ?reverse@ControlBarArrowTransition@@UAEXXZ present-unmatched
void ControlBarArrowTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
}

// ?draw@ControlBarArrowTransition@@UAEXXZ present-unmatched
void ControlBarArrowTransition::draw( void )
{
	if(m_drawState <0)
		return;
	if(m_drawState < CONTROLBARARROWTRANSITION_BEGIN_FADE)
	{
		Int yPos = 	m_pos.y + m_incrementPos.y* m_drawState;
		TheDisplay->drawImage(m_arrowImage, m_pos.x, yPos, m_pos.x + m_size.x, yPos + m_size.y );

	}
	else
	{
		Int alpha = (1 - (m_fadePercent *(m_drawState - CONTROLBARARROWTRANSITION_BEGIN_FADE )) )*255 ;
		if(alpha > 255)
			alpha = 255;
		Int yPos = 	m_pos.y + m_incrementPos.y* (CONTROLBARARROWTRANSITION_BEGIN_FADE - 1);

		TheDisplay->drawImage(m_arrowImage, m_pos.x, yPos, m_pos.x + m_size.x, yPos + m_size.y , GameMakeColor(255,255,255,alpha));
	}
	
}
	
// ?skip@ControlBarArrowTransition@@UAEXXZ present-unmatched
void ControlBarArrowTransition::skip( void )
{
	update(CONTROLBARARROWTRANSITION_END);
}





//-----------------------------------------------------------------------------

// ??0FullFadeTransition@@QAE@XZ present-unmatched
FullFadeTransition::FullFadeTransition ( void )
{
	m_frameLength = FULLFADETRANSITION_END;
	m_win = NULL;
	m_drawState = -1;
	m_isForward = TRUE;
	
}

// ??1FullFadeTransition@@UAE@XZ present-unmatched
FullFadeTransition::~FullFadeTransition( void )
{
	m_win = NULL;
	
}

// ?init@FullFadeTransition@@UAEXPAVGameWindow@@@Z present-unmatched
void FullFadeTransition::init( GameWindow *win )
{

	if(win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y );
	}

	m_isForward = FALSE;
	update(FULLFADETRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;

	m_percent = 1.0f / (FULLFADETRANSITION_END/2);

}

// ?update@FullFadeTransition@@UAEXH@Z present-unmatched
void FullFadeTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < FULLFADETRANSITION_START || frame > FULLFADETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("FullFadeTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case FULLFADETRANSITION_START:
		{
						
			if(m_isForward || !m_win )
				break;

			m_win->winHide(TRUE);
			m_isFinished = TRUE;

		}
		break;
	case FULLFADETRANSITION_END:
		{
			if(!m_isForward || !m_win )
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;

		}
	}	
	if(frame == FULLFADETRANSITION_END/2)
	{
		if(m_isForward)
			m_win->winHide(FALSE);	
		else
			m_win->winHide(TRUE);	
	}
	m_drawState = frame;	
}

// ?reverse@FullFadeTransition@@UAEXXZ present-unmatched
void FullFadeTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
}

// ?draw@FullFadeTransition@@UAEXXZ present-unmatched
void FullFadeTransition::draw( void )
{
	Int alpha;
	if(m_drawState > (FULLFADETRANSITION_END/2))
		alpha = m_percent * 255 * (FULLFADETRANSITION_END - m_drawState);
	else
		alpha = m_percent * 255 *m_drawState;
	if(alpha > 255)
		alpha = 255;
	TheDisplay->drawFillRect(m_pos.x, m_pos.y, m_size.x, m_size.y , GameMakeColor(0,0,0,alpha));
	TheDisplay->drawOpenRect(m_pos.x, m_pos.y, m_size.x, m_size.y , 1.0f, GameMakeColor(60,60,180,alpha));
}
	
// ?skip@FullFadeTransition@@UAEXXZ present-unmatched
void FullFadeTransition::skip( void )
{
	update(FULLFADETRANSITION_END);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// ??0TextOnFrameTransition@@QAE@XZ present-unmatched
TextOnFrameTransition::TextOnFrameTransition ( void )
{
	m_frameLength = TEXTONFRAMETRANSITION_END;
	m_win = NULL;
	m_isForward = TRUE;
	
}

// ??1TextOnFrameTransition@@UAE@XZ present-unmatched
TextOnFrameTransition::~TextOnFrameTransition( void )
{
	m_win = NULL;
	
}

void TextOnFrameTransition::init( GameWindow *win )
{

	if(win)
	{
		m_win = win;
	}
	if(m_win->winIsHidden())
	{
		m_isFinished = TRUE;
		m_isForward = TRUE;
		m_frameLength = 0;
	}
	else
	{
		m_isForward = FALSE;
		update(TEXTONFRAMETRANSITION_START);
		m_isFinished = FALSE;
		m_isForward = TRUE;
	}
}

// ?update@TextOnFrameTransition@@UAEXH@Z present-unmatched
void TextOnFrameTransition::update( Int frame )
{
	if(frame < TEXTONFRAMETRANSITION_START || frame > TEXTONFRAMETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("TextOnFrameTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case TEXTONFRAMETRANSITION_START:
		{
						
			if(m_isForward || !m_win )
				break;

			m_win->winHide(TRUE);
			m_isFinished = TRUE;

		}
		break;
	case TEXTONFRAMETRANSITION_END:
		{
			if(!m_isForward || !m_win )
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;

		}
	}	
}

void TextOnFrameTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
	if(m_win->winIsHidden())
	{
		m_isFinished = TRUE;
		m_frameLength = 0;
	}
}

// ?draw@TextOnFrameTransition@@UAEXXZ present-unmatched
void TextOnFrameTransition::draw( void )
{
}
	
// ?skip@TextOnFrameTransition@@UAEXXZ present-unmatched
void TextOnFrameTransition::skip( void )
{
	if (!m_isFinished)
		update(TEXTONFRAMETRANSITION_END);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// ??0ReverseSoundTransition@@QAE@XZ present-unmatched
ReverseSoundTransition::ReverseSoundTransition ( void )
{
	m_frameLength = REVERSESOUNDTRANSITION_END;
	m_win = NULL;
	m_isForward = TRUE;
	
}

// ??1ReverseSoundTransition@@UAE@XZ present-unmatched
ReverseSoundTransition::~ReverseSoundTransition( void )
{
	m_win = NULL;
	
}

void ReverseSoundTransition::init( GameWindow *win )
{
	m_isFinished = TRUE;
	m_isForward = TRUE;
}

// ?update@ReverseSoundTransition@@UAEXH@Z present-unmatched
void ReverseSoundTransition::update( Int frame )
{
	if(frame < REVERSESOUNDTRANSITION_START || frame > REVERSESOUNDTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ReverseSoundTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case REVERSESOUNDTRANSITION_START:
		{
						
			if(m_isForward  )
				break;

			m_isFinished = TRUE;

		}
		break;
		
	case REVERSESOUNDTRANSITION_FIRESOUND:
		{
			AudioEventRTS buttonClick("GUITransitionFade");

			if( TheAudio )
			{
				TheAudio->addAudioEvent( &buttonClick );
			}  // end if		

		}
	case REVERSESOUNDTRANSITION_END:
		{
			if(!m_isForward  )
				break;
			m_isFinished = TRUE;

		}
	}	
}

// ?reverse@ReverseSoundTransition@@UAEXXZ present-unmatched
void ReverseSoundTransition::reverse( void )
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
}

// ?draw@ReverseSoundTransition@@UAEXXZ present-unmatched
void ReverseSoundTransition::draw( void )
{
}
	
void ReverseSoundTransition::skip( void )
{
	if (!m_isFinished)
		update(REVERSESOUNDTRANSITION_END);
}



//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

void PushButtonImageDrawThree(GameWindow *window, Int alpha )
{
	WinInstanceData *instData = window->winGetInstanceData();
	const Image *leftImage, *rightImage, *centerImage;
	ICoord2D origin, size, start, end;
	Int xOffset, yOffset;
	Int i;
	Int color = GameMakeColor(255,255,255,alpha);
	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	leftImage					= GadgetButtonGetLeftEnabledImage( window );
	rightImage				= GadgetButtonGetRightEnabledImage( window );
	centerImage				= GadgetButtonGetMiddleEnabledImage( window );

	// sanity, we need to have these images to make it look right
	if( leftImage == NULL || rightImage == NULL || 
			centerImage == NULL )
		return;

	// get image sizes for the ends
	ICoord2D leftSize, rightSize;
	leftSize.x = leftImage->getImageWidth();
	leftSize.y = leftImage->getImageHeight();
	rightSize.x = rightImage->getImageWidth();
	rightSize.y = rightImage->getImageHeight();

	// get two key points used in the end drawing
	ICoord2D leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y + yOffset;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;
	
	if( centerWidth <= 0)
	{
		// draw left end
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end.y = leftEnd.y;
		end.x = origin.x + xOffset + size.x/2;
		TheDisplay->drawImage(leftImage, start.x, start.y, end.x, end.y,color);

		// draw right end
		start.y = rightStart.y;
		start.x = end.x;
		end.x = origin.x + size.x;
		end.y = start.y + size.y;
		TheDisplay->drawImage(rightImage, start.x, start.y, end.x, end.y,color);
	}
	else
	{
		
		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerImage->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = origin.y + yOffset;
		end.y = start.y + size.y + yOffset; //centerImage->getImageHeight() + yOffset;
		for( i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerImage->getImageWidth();
			
			TheDisplay->drawImage( centerImage, 
																			start.x, start.y,
																			end.x, end.y,color );
			start.x += centerImage->getImageWidth();

		}  // end for i

		// we will draw the image but clip the parts we don't want to show
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = rightStart.x;
		reg.hi.y = end.y;
		centerWidth = rightStart.x - start.x;
		if( centerWidth > 0)
		{
			TheDisplay->setClipRegion(&reg);
			end.x = start.x + centerImage->getImageWidth();
			TheDisplay->drawImage( centerImage,
																			start.x, start.y,
																			end.x, end.y,color );
			TheDisplay->enableClipping(FALSE);
		}

		// draw left end
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end = leftEnd;
		TheDisplay->drawImage(leftImage, start.x, start.y, end.x, end.y,color);

		// draw right end
		start = rightStart;
		end.x = start.x + rightSize.x;
		end.y = start.y + size.y;
		TheDisplay->drawImage(rightImage, start.x, start.y, end.x, end.y,color);
	}
	
}

static void drawTypeText( GameWindow *window, DisplayString *str)
{
	TextData *tData = (TextData *)window->winGetUserData();
	Int textColor = window->winGetEnabledTextColor();
	Int textDropColor = window->winGetEnabledTextBorderColor();
	Int textWidth, textHeight, wordWrap;
	DisplayString *text = tData->text;
	ICoord2D origin, size, textPos;
	IRegion2D clipRegion;
	// sanity
	if( text == NULL || text->getTextLength() == 0 )
		return;
	GameFont *font = text->getFont();
	
	str->setFont(font);

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );
	
	// Set the text Wrap width
	wordWrap = size.x - 10;
	text->setWordWrap(wordWrap);	
	str->setWordWrap(wordWrap);
	if( BitTest(window->winGetStatus(), WIN_STATUS_WRAP_CENTERED)		)
	{
		str->setWordWrapCentered(TRUE);
		text->setWordWrapCentered(TRUE);
	}
	else
	{
		text->setWordWrapCentered(FALSE);
		str->setWordWrapCentered(FALSE);

	}


	// how much space will this text take up
	text->getSize( &textWidth, &textHeight );
		
	//Init the clip region
	clipRegion.lo.x = origin.x ;
	clipRegion.lo.y = origin.y ;
	clipRegion.hi.x = origin.x + size.x ;
	clipRegion.hi.y = origin.y + size.y;
	
	if( tData->centered )
	{

		textPos.x = origin.x + (size.x / 2) - (textWidth / 2);
		textPos.y = origin.y + (size.y / 2) - (textHeight / 2);
		str->setClipRegion(&clipRegion);
		str->draw( textPos.x, textPos.y, textColor, textDropColor );
	}  // end if
	else
	{

		// draw the text
		textPos.x = origin.x + 7;
		textPos.y = origin.y + (size.y / 2) - (textHeight / 2);
		str->setClipRegion(&clipRegion);
		str->draw( textPos.x, textPos.y, textColor, textDropColor );

	}  // end else


}  // end drawStaticTextText
