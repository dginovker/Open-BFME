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

// Smudge.cpp ////////////////////////////////////////////////////////////////////////////////
// Smudge System implementation
// Author: Mark Wilczynski, June 2003
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the Game
#include "GameClient/Smudge.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

DLListClass<Smudge> SmudgeSet::m_freeSmudgeList;	///<list of unused smudges for use by SmudgeSets.

SmudgeManager::SmudgeManager(void)
{
	m_smudgeCountLastFrame=0;
	m_hardwareSupportStatus = SMUDGE_SUPPORT_UNKNOWN;
}

// ??1SmudgeManager@@UAE@XZ present-unmatched
SmudgeManager::~SmudgeManager()
{
	reset();	//release all smudge sets and smudges to free pool.

	SmudgeSet* head;

	//free memory used by smudge sets
	while ((head = m_freeSmudgeSetList.Head ()) != NULL) {
		m_freeSmudgeSetList.Remove_Head ();
		delete head;
	}

	Smudge* head2;
	//free memory used by smudges
	while ((head2 = SmudgeSet::m_freeSmudgeList.Head ()) != NULL) {
		m_freeSmudgeSetList.Remove_Head ();
		delete head2;
	}
}

// ?init@SmudgeManager@@UAEXXZ present-unmatched
void SmudgeManager::init(void)
{

}

// ?reset@SmudgeManager@@UAEXXZ present-unmatched
void SmudgeManager::reset(void)
{
	SmudgeSet* head;

	//Return all smudgeSets back to free pool.
	while ((head = m_usedSmudgeSetList.Head ()) != NULL) {
		m_usedSmudgeSetList.Remove_Head ();
		head->reset();	//free all smudges.
		m_freeSmudgeSetList.Add_Tail(head);
	}
}

// ?addSmudgeSet@SmudgeManager@@QAEPAUSmudgeSet@@XZ present-unmatched
SmudgeSet *SmudgeManager::addSmudgeSet(void)
{
	SmudgeSet* set=m_freeSmudgeSetList.Head();
	if (set) {
		set->Remove();	//remove from free list
		m_usedSmudgeSetList.Add_Tail(set);	//add to used list.
		return set;
	}
	set=W3DNEW SmudgeSet();
	m_usedSmudgeSetList.Add_Tail(set);	//add to used list.
	return set;
}

// ?removeSmudgeSet@SmudgeManager@@QAEXAAUSmudgeSet@@@Z present-unmatched
void SmudgeManager::removeSmudgeSet(SmudgeSet &mySmudge)
{
	mySmudge.Remove();	//remove from used list
	m_freeSmudgeSetList.Add_Head(&mySmudge);	//add to free list.
}

SmudgeSet::SmudgeSet(void)
{
	m_usedSmudgeCount=0;
}

// ??1SmudgeSet@@UAE@XZ present-unmatched
SmudgeSet::~SmudgeSet()
{
	reset();
}

// ?reset@SmudgeSet@@QAEXXZ present-unmatched
void SmudgeSet::reset(void)
{
	Smudge* head;

	while ((head = m_usedSmudgeList.Head ()) != NULL) {
		m_usedSmudgeList.Remove_Head ();
		m_freeSmudgeList.Add_Head(head);	//add to free list
	}
}

// ?addSmudgeToSet@SmudgeSet@@QAEPAUSmudge@@XZ present-unmatched
Smudge *SmudgeSet::addSmudgeToSet(void)
{
	Smudge* smudge=m_freeSmudgeList.Head();
	if (smudge) {
		smudge->Remove();	//remove from free list
		m_usedSmudgeList.Add_Tail(smudge);	//add to used list.
		m_usedSmudgeCount++;
		return smudge;
	}
	smudge=W3DNEW Smudge();
	m_usedSmudgeList.Add_Tail(smudge);	//add to used list.
	m_usedSmudgeCount++;
	return smudge;
}

// ?removeSmudgeFromSet@SmudgeSet@@QAEXAAUSmudge@@@Z present-unmatched
void SmudgeSet::removeSmudgeFromSet(Smudge &mySmudge)
{
	mySmudge.Remove();	//remove from used list.
	m_freeSmudgeList.Add_Head(&mySmudge);	//add to free list
	m_usedSmudgeCount--;
}
