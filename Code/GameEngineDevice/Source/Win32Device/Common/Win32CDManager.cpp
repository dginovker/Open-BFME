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
// Module:    Game Engine Device Win32 Common
//
// File name: Win32CDManager.cpp
//
// Created:   11/26/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "windows.h"

#include "Common/GameMemory.h"
#include "Common/FileSystem.h"

#include "Win32DEvice/Common/Win32CDManager.h"

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


CDManagerInterface* CreateCDManager( void )
{
	return NEW Win32CDManager;
}

//============================================================================
// Win32CDDrive::Win32CDDrive
//============================================================================

// ??0Win32CDDrive@@QAE@XZ present-unmatched
Win32CDDrive::Win32CDDrive()
{

}

//============================================================================
// Win32CDDrive::~Win32CDDrive
//============================================================================

// ??1Win32CDDrive@@UAE@XZ present-unmatched
Win32CDDrive::~Win32CDDrive()
{

}

//============================================================================
// Win32CDDrive::refreshInfo
//============================================================================

// ?refreshInfo@Win32CDDrive@@UAEXXZ present-unmatched
void Win32CDDrive::refreshInfo( void )
{
	Bool mayRequireUpdate = (m_disk != CD::NO_DISK);
	Char volName[1024];
	// read the volume info
	if ( GetVolumeInformation( m_drivePath.str(), volName, sizeof(volName) -1, NULL, NULL, NULL, NULL, 0 ))
	{
		m_diskName = volName;
		m_disk = CD::UNKNOWN_DISK;
	}
	else
	{
		m_diskName.clear();
		m_disk = CD::NO_DISK;
		
		if (mayRequireUpdate) 
			TheFileSystem->unloadMusicFilesFromCD();
	}

	// This is an override, not an extension of CDDrive
}

//============================================================================
// Win32CDManager::Win32CDManager
//============================================================================

// ??0Win32CDManager@@QAE@XZ present-unmatched
Win32CDManager::Win32CDManager()
{

}

//============================================================================
// Win32CDManager::~Win32CDManager
//============================================================================

// ??1Win32CDManager@@UAE@XZ present-unmatched
Win32CDManager::~Win32CDManager()
{

}

//============================================================================
// Win32CDManager::init
//============================================================================

// ?init@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::init( void )
{
// ?init@CDManager@@ present-unmatched
	CDManager::init();	// init base classes

	destroyAllDrives();

	// detect CD Drives
	for ( Char driveLetter = 'a'; driveLetter <= 'z'; driveLetter++ )
	{
		AsciiString drivePath;
		drivePath.format( "%c:\\", driveLetter );

		if ( GetDriveType( drivePath.str() ) == DRIVE_CDROM )
		{
			newDrive( drivePath.str() );
		}
	}

	refreshDrives();
}

//============================================================================
// Win32CDManager::update
//============================================================================

// ?update@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::update( void )
{
	CDManager::update();


}

//============================================================================
// Win32CDManager::reset
//============================================================================

// ?reset@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::reset( void )
{
	CDManager::reset();

}

//============================================================================
// Win32CDManager::createDrive
//============================================================================

CDDriveInterface* Win32CDManager::createDrive( void )
{
	return NEW Win32CDDrive;
}


//============================================================================
// Win32CDManager::refreshDrives
//============================================================================

// ?refreshDrives@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::refreshDrives( void )
{
	CDManager::refreshDrives();
}




