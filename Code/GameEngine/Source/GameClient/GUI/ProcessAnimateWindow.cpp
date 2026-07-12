// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: ProcessAnimateWindow.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Mar 2002
//
//	Filename: 	ProcessAnimateWindow.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Holds all the process modules for the Animate Window Class
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

#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromRight PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromRight::ProcessAnimateWindowSlideFromRight( void )
{
	m_maxVel.x =  -40.0f;  // top speed windows travel in x and y
	m_maxVel.y = 0.0f;
	m_slowDownThreshold = 80;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.67f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 2.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

//-----------------------------------------------------------------------------
// ??1ProcessAnimateWindowSlideFromRight@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromRight::~ProcessAnimateWindowSlideFromRight( void ) { }

//-----------------------------------------------------------------------------
// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromRight::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	
	animWin->setFinished( FALSE );

}

//-----------------------------------------------------------------------------
// ?initAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromRight::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	animWin->setFinished( FALSE );

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Right of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x + travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel.x = m_maxVel.x;
	vel.y = 0.0f;


	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}


//-----------------------------------------------------------------------------
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromRight::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x < endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( curPos.x - endPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_slowDownRatio;
	}
	if( vel.x >= -1.0f)
		vel.x = -1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRight@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromRight::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x > startPos.x)
	{
		curPos.x = startPos.x;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( curPos.x - endPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_speedUpRatio;
	}
	else
	{
		vel.x = -m_maxVel.x;
	}
	if( vel.x > -m_maxVel.x)
		vel.x = -m_maxVel.x;
	animWin->setVel(vel);
	return FALSE;
}

//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromLeft PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromLeft::ProcessAnimateWindowSlideFromLeft( void )
{
	m_maxVel.x =  40.0f;  // top speed windows travel in x and y
	m_maxVel.y = 0.0f;
	m_slowDownThreshold = 80;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.67f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 2.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

// ??1ProcessAnimateWindowSlideFromLeft@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromLeft::~ProcessAnimateWindowSlideFromLeft( void ) { }

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromLeft::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	

}

// ?initAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromLeft::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Left of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x - travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromLeft::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;
	
	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x > endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( endPos.x - curPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_slowDownRatio;
	}
	if( vel.x < 1.0f)
		vel.x = 1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromLeft::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x < startPos.x)
	{
		curPos.x = startPos.x;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( endPos.x - curPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_speedUpRatio;
	}
	else
	{
		vel.x = -m_maxVel.x;
	}
	if( vel.x < -m_maxVel.x)
		vel.x = -m_maxVel.x;
	animWin->setVel(vel);
	return FALSE;
}

//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromTop PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromTop::ProcessAnimateWindowSlideFromTop( void )
{
	m_maxVel.y =  40.0f;  // top speed windows travel in x and y
	m_maxVel.x = 0.0f;
	m_slowDownThreshold = 80;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.67f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 2.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

// ??1ProcessAnimateWindowSlideFromTop@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromTop::~ProcessAnimateWindowSlideFromTop( void ) { }

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromTop::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	

}

// ?initAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromTop::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Top of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x ;
	startPos.y = curPos.y = restPos.y - travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromTop::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;
	
	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > endPos.y)
	{
		curPos.y = endPos.y;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( endPos.y - curPos.y  <= m_slowDownThreshold )
	{
		vel.y *= m_slowDownRatio;
	}
	if( vel.y < 1.0f)
		vel.y = 1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromTop::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y < startPos.y)
	{
		curPos.y = startPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( endPos.y - curPos.y <= m_slowDownThreshold )
	{
		vel.y *= m_speedUpRatio;
	}
	else
	{
		vel.y = -m_maxVel.y;
	}
	if( vel.y < -m_maxVel.y)
		vel.y = -m_maxVel.y;
	animWin->setVel(vel);
	return FALSE;
}

//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromBottom PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromBottom::ProcessAnimateWindowSlideFromBottom( void )
{
	m_maxVel.y =  -40.0f;  // top speed windows travel in x and y
	m_maxVel.x = 0.0f;
	m_slowDownThreshold = 80;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.67f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 2.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

// ??1ProcessAnimateWindowSlideFromBottom@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromBottom::~ProcessAnimateWindowSlideFromBottom( void ) { }

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromBottom::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	

}


// ?initAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromBottom::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromBottom::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y < endPos.y)
	{
		curPos.y = endPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( curPos.y - endPos.y <= m_slowDownThreshold )
	{
		vel.y *= m_slowDownRatio;
	}
	if( vel.y >= -1.0f)
		vel.y = -1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottom@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromBottom::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > startPos.y)
	{
		curPos.y = startPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( curPos.y - endPos.y <= m_slowDownThreshold )
	{
		vel.y *= m_speedUpRatio;
	}
	else
	{
		vel.y = -m_maxVel.y;
	}
	if( vel.y > -m_maxVel.y)
		vel.y = -m_maxVel.y;
	animWin->setVel(vel);
	return FALSE;
}


//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromBottomTimed PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

// ??0ProcessAnimateWindowSlideFromBottomTimed@@QAE@XZ present-unmatched
ProcessAnimateWindowSlideFromBottomTimed::ProcessAnimateWindowSlideFromBottomTimed( void )
{
	m_maxDuration = 1000;
}

// ??1ProcessAnimateWindowSlideFromBottomTimed@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromBottomTimed::~ProcessAnimateWindowSlideFromBottomTimed( void ) { }

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	restPos = animWin->getRestPos();
	startPos.x = restPos.x;
	curPos.y = startPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	endPos.x = curPos.x = restPos.x;
	endPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = timeGetTime();

	DEBUG_LOG(("initReverseAnimateWindow at %d (%d->%d)\n", now, now, now + m_maxDuration));
	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, now, now + m_maxDuration);
}


// ?initAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Bottom of the screen
	Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x;
	startPos.y = curPos.y = restPos.y + travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	UnsignedInt now = timeGetTime();
	UnsignedInt delay = animWin->getDelay();

	DEBUG_LOG(("initAnimateWindow at %d (%d->%d)\n", now, now + delay, now + m_maxDuration + delay));
	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, now + delay, now + m_maxDuration + delay);
}

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D startPos = animWin->getStartPos();
	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();

	UnsignedInt now = timeGetTime();
	UnsignedInt startTime = animWin->getStartTime();
	UnsignedInt endTime = animWin->getEndTime();

	if (now < startTime)
		return FALSE;

	Real percentDone = 1.0f - (Real)(endTime - now) / (Real)(m_maxDuration);
	if (now >= endTime)
	{
		curPos.y = endPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		DEBUG_LOG(("window finished animating at %d (%d->%d)\n", now, startTime, endTime));
		return TRUE;
	}

	curPos.y = startPos.y + percentDone*(endPos.y - startPos.y);
	DEBUG_LOG(("(%d,%d) -> (%d,%d) -> (%d,%d) at %g\n",
		startPos.x, startPos.y, curPos.x, curPos.y, endPos.x, endPos.y, percentDone));

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromBottomTimed@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow( AnimateWindow *animWin )
{
	return updateAnimateWindow(animWin);
}


//-----------------------------------------------------------------------------
// ProcessAnimateWindowSpiral PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

// ??0ProcessAnimateWindowSpiral@@QAE@XZ present-unmatched
ProcessAnimateWindowSpiral::ProcessAnimateWindowSpiral( void )
{
	m_maxR = TheDisplay->getWidth() / 2;
	m_deltaTheta = .33f;	
}

//-----------------------------------------------------------------------------
// ??1ProcessAnimateWindowSpiral@@UAE@XZ present-unmatched
ProcessAnimateWindowSpiral::~ProcessAnimateWindowSpiral( void ) { }

//-----------------------------------------------------------------------------
// ?initReverseAnimateWindow@ProcessAnimateWindowSpiral@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSpiral::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x = 0;
	vel.y = 0;
	animWin->setVel( vel );	

}

//-----------------------------------------------------------------------------
// ?initAnimateWindow@ProcessAnimateWindowSpiral@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSpiral::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	ICoord2D size = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	win->winGetSize(&size.x,&size.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;
	//set the initial positions for the window. In this case, off the Bottom of the screen
	vel.x = 0;
	vel.y = m_maxR;
	startPos.x = curPos.x = (vel.y * cos(vel.x)) + endPos.x;
	startPos.y = curPos.y = (vel.y * sin(vel.x)) + endPos.y;


	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

//-----------------------------------------------------------------------------
// ?updateAnimateWindow@ProcessAnimateWindowSpiral@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSpiral::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	
	curPos.x = (vel.y * cos(vel.x)) + endPos.x; 
	curPos.y = (vel.y * sin(vel.x)) + endPos.y;

	vel.x = vel.x + m_deltaTheta;
	vel.y -=5;
	
	ICoord2D size;
	win->winGetSize(&size.x, &size.y);
	Int m_max = min(size.x/2, size.y/2);

	if(vel.y < m_max)
	{
		ICoord2D restPos = animWin->getRestPos();
		animWin->setFinished( TRUE );
		win->winSetPosition(restPos.x, restPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	animWin->setVel(vel);
	return FALSE;
}

//-----------------------------------------------------------------------------
// ?reverseAnimateWindow@ProcessAnimateWindowSpiral@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSpiral::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;



	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	
	curPos.x = (vel.y * cos(vel.x)) + endPos.x; 
	curPos.y = (vel.y * sin(vel.x)) + endPos.y;

	vel.x = vel.x - m_deltaTheta;
	vel.y +=5;
	
	ICoord2D size;
	win->winGetSize(&size.x, &size.y);
//	Int m_max = min(size.x/2, size.y/2);

	if(vel.y > m_maxR)
	{
		//ICoord2D restPos = animWin->getRestPos();
		animWin->setFinished( TRUE );
		//win->winSetPosition(restPos.x, restPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	animWin->setVel(vel);
	return FALSE;
}


//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromTopFast PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromTopFast::ProcessAnimateWindowSlideFromTopFast( void )
{
	m_maxVel.y =  60.0f;  // top speed windows travel in x and y
	m_maxVel.x = 0.0f;
	m_slowDownThreshold = 40;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.67f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 4.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

// ??1ProcessAnimateWindowSlideFromTopFast@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromTopFast::~ProcessAnimateWindowSlideFromTopFast( void ) { }

// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromTopFast::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	

}

// ?initAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromTopFast::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	ICoord2D size = {0,0};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;
	
	win->winGetSize(&size.x, &size.y);

	//set the initial positions for the window. In this case, off the Top of the screen
	//Int travelDistance = TheDisplay->getWidth();// / 4 * 3;
	startPos.x = curPos.x = restPos.x ;
	startPos.y = curPos.y = -size.y;//restPos.y - travelDistance;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel = m_maxVel;

	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}

// ?updateAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromTopFast::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;
	
	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y > endPos.y)
	{
		curPos.y = endPos.y;
		win->winSetPosition(curPos.x, curPos.y);
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( endPos.y - curPos.y  <= m_slowDownThreshold )
	{
		vel.y *= m_slowDownRatio;
	}
	if( vel.y < 1.0f)
		vel.y = 1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromTopFast::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.y += (Int)vel.y;

	if(curPos.y < startPos.y)
	{
		curPos.y = startPos.y;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( endPos.y - curPos.y <= m_slowDownThreshold )
	{
		vel.y *= m_speedUpRatio;
	}
	else
	{
		vel.y = -m_maxVel.y;
	}
	if( vel.y < -m_maxVel.y)
		vel.y = -m_maxVel.y;
	animWin->setVel(vel);
	return FALSE;
}


//-----------------------------------------------------------------------------
// ProcessAnimateWindowSlideFromRightFast PUBLIC FUNCTIONS ////////////////////////
//-----------------------------------------------------------------------------

ProcessAnimateWindowSlideFromRightFast::ProcessAnimateWindowSlideFromRightFast( void )
{
	m_maxVel.x =  -80.0f;  // top speed windows travel in x and y
	m_maxVel.y = 0.0f;
	m_slowDownThreshold = 60;  // when widnows get this close to their resting
																			// positions they start to slow down
	m_slowDownRatio = 0.77f;  // how fast the windows slow down (smaller slows quicker)
	m_speedUpRatio = 3.0f - m_slowDownRatio;  // how fast the windows speed up
	
}

//-----------------------------------------------------------------------------
// ??1ProcessAnimateWindowSlideFromRightFast@@UAE@XZ present-unmatched
ProcessAnimateWindowSlideFromRightFast::~ProcessAnimateWindowSlideFromRightFast( void ) { }

//-----------------------------------------------------------------------------
// ?initReverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@I@Z present-unmatched
void ProcessAnimateWindowSlideFromRightFast::initReverseAnimateWindow( AnimateWindow *animWin, UnsignedInt maxDelay )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	if(animWin->getDelay() > 0)
		animWin->setStartTime(timeGetTime() + (maxDelay - animWin->getDelay()));
	Coord2D vel = animWin->getVel();
	vel.x *= -1;
	vel.y *= -1;
	animWin->setVel( vel );	
	animWin->setFinished( FALSE );
	GameWindow * win = animWin->getGameWindow();
	ICoord2D pos, tempPos;
	win->winGetPosition(&pos.x, &pos.y);
	tempPos = animWin->getCurPos();
	tempPos.y = pos.y;
	animWin->setCurPos(tempPos);

	tempPos = animWin->getEndPos();
	tempPos.y = pos.y;
	animWin->setEndPos(tempPos);

	tempPos = animWin->getStartPos();
	tempPos.y = pos.y;
	animWin->setStartPos(tempPos);




}

//-----------------------------------------------------------------------------
// ?initAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAEXPAVAnimateWindow@@@Z present-unmatched
void ProcessAnimateWindowSlideFromRightFast::initAnimateWindow( AnimateWindow *animWin )
{
	ICoord2D restPos = {0,0};
	ICoord2D startPos = {0,0};
	ICoord2D size = {0,0};
	ICoord2D curPos = {0,0};
	ICoord2D endPos = {0,0};
	Coord2D	vel = {0.0f,0.0f};
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into initAnimateWindow as a NULL Pointer... bad bad bad!"));
		return;
	}
	animWin->setFinished( FALSE );

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return;
	}
	win->winGetPosition(&restPos.x, &restPos.y);
	win->winGetSize(&size.x, &size.y);
	endPos.x = restPos.x;
	endPos.y = restPos.y;

	//set the initial positions for the window. In this case, off the Right of the screen
	Int travelDistance = TheDisplay->getWidth() - restPos.x + size.x ;// / 4 * 3;
	startPos.x = curPos.x = restPos.x + travelDistance;
	startPos.y = curPos.y = restPos.y;

	//set the window's position to the new start positions.
	win->winSetPosition(startPos.x, startPos.y);

	//Now initialize the velocities
	vel.x = m_maxVel.x;
	vel.y = 0.0f;


	animWin->setAnimData(startPos, endPos, curPos, restPos, vel, timeGetTime() + animWin->getDelay(), 0);
}


//-----------------------------------------------------------------------------
// ?updateAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromRightFast::updateAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;
	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D endPos = animWin->getEndPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x < endPos.x)
	{
		curPos.x = endPos.x;
		animWin->setFinished( TRUE );
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);
	if( curPos.x - endPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_slowDownRatio;
	}
	if( vel.x >= -1.0f)
		vel.x = -1.0f;
	animWin->setVel(vel);
	return FALSE;
}

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromRightFast@@UAE_NPAVAnimateWindow@@@Z present-unmatched
Bool ProcessAnimateWindowSlideFromRightFast::reverseAnimateWindow( AnimateWindow *animWin )
{
	
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}

	// if the window has finished animating into position, return
	if(animWin->isFinished())
		return TRUE;

	// if the window hasn't started animating...return that we're not finished
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;

	// it's set that the window is passed in as it's current position being it's rest position
	// so save off the rest position
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x > startPos.x)
	{
		curPos.x = startPos.x;
		animWin->setFinished( TRUE );
		win->winSetPosition(curPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	if( curPos.x - endPos.x <= m_slowDownThreshold )
	{
		vel.x *= m_speedUpRatio;
	}
	else
	{
		vel.x = -m_maxVel.x;
	}
	if( vel.x > -m_maxVel.x)
		vel.x = -m_maxVel.x;
	animWin->setVel(vel);
	return FALSE;
}
