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
// Module:    Game Engine Common
//
// File name: CDManager.cpp
//
// Created:   11/26/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/CDManager.h"
#include "GameLogic/GameLogic.h"

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

CDManagerInterface* TheCDManager = NULL;

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
// CDDrive::CDDrive
//============================================================================

// ??0CDDrive@@ present-unmatched
CDDrive::CDDrive()
: m_disk(CD::UNKNOWN_DISK)
{
	m_diskName.clear();
	m_drivePath.clear();
	
}

//============================================================================
// CDDrive::~CDDrive
//============================================================================

// ??1CDDrive@@ present-unmatched
CDDrive::~CDDrive()
{

}

//============================================================================
// CDDrive::getPath
//============================================================================

// ?getPath@CDDrive@@ present-unmatched
AsciiString CDDrive::getPath( void )
{
	return m_drivePath;
}

//============================================================================
// CDDrive::getDiskName
//============================================================================

// ?getDiskName@CDDrive@@ present-unmatched
AsciiString CDDrive::getDiskName( void )
{
	return m_diskName;
}

// ?refreshInfo@CDDrive@@ present-unmatched
void CDDrive::refreshInfo( void )
{
		// map disk names to disk ID
		m_disk = CD::UNKNOWN_DISK;
}

//============================================================================
// CDDrive::getDisk
//============================================================================

// ?getDisk@CDDrive@@ present-unmatched
CD::Disk CDDrive::getDisk( void )
{
	return m_disk;
}

//============================================================================
// CDDrive::setPath
//============================================================================

// ?setPath@CDDrive@@ present-unmatched
void CDDrive::setPath( const Char *path )
{
	m_drivePath = path;
}

//============================================================================
// CDManager::CDManager
//============================================================================

CDManager::CDManager()
{

}

//============================================================================
// CDManager::~CDManager
//============================================================================

CDManager::~CDManager()
{
	destroyAllDrives();
}

//============================================================================
// CDManager::init
//============================================================================

// ?init@CDManager@@ present-unmatched
void CDManager::init( void )
{

}

//============================================================================
// CDManager::update
//============================================================================

// ?update@CDManager@@ present-unmatched
void CDManager::update( void )
{
	// Every so often, check to make sure the CD is still in the drive
	if ((TheGameLogic->getFrame() % 300) == 299) {
		refreshDrives();
	}
}

//============================================================================
// CDManager::reset
//============================================================================

// ?reset@CDManager@@ present-unmatched
void CDManager::reset( void )
{

}

//============================================================================
// CDManager::driveCount
//============================================================================

// ?driveCount@CDManager@@ present-unmatched
Int CDManager::driveCount( void )
{
	return m_drives.nodeCount();
}

//============================================================================
// CDManager::getDrive
//============================================================================

CDDriveInterface* CDManager::getDrive( Int index )
{
	CDDriveInterface *cd = NULL;
	LListNode *node = m_drives.getNode( index );

	if ( node )
	{
		cd = (CDDriveInterface*) node->item();
	}

	return cd;
}

//============================================================================
// CDManager::newDrive
//============================================================================

// ?newDrive@CDManager@@ present-unmatched
CDDriveInterface* CDManager::newDrive( const Char *path )
{
	CDDrive *drive= (CDDrive*) createDrive();

	if ( drive )
	{
		drive->setPath( path );
		
		drive->m_node.setItem( drive );
		m_drives.add( &drive->m_node );
	}
	return drive;
}

//============================================================================
// CDManager::refreshDrives
//============================================================================

void CDManager::refreshDrives( void )
{
	LListNode *node = m_drives.firstNode();

	while ( node )
	{
		CDDriveInterface *drive = (CDDriveInterface *) node->item();
		if ( drive )
		{
			drive->refreshInfo();
		}

		node = node->next();
	}
}


//============================================================================
// CDManager::destroyAllDrives
//============================================================================

void CDManager::destroyAllDrives( void )
{
	LListNode *node;

	while ( (node = m_drives.firstNode() ) != NULL )
	{
		node->remove();
		CDDriveInterface *drive = (CDDriveInterface *) node->item();
		if ( drive )
		{
			delete drive;
		}
	}
}





