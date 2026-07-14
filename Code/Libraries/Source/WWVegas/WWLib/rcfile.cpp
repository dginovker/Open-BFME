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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : wwlib                                                        *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/rcfile.cpp                             $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 7/09/99 1:37p                                               $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "rcfile.h"
#include <stdlib.h>

const char * RESOURCE_FILE_TYPE_NAME = "File";


// ??0ResourceFileClass@@ present-unmatched
ResourceFileClass::ResourceFileClass(HMODULE hmodule, char const *filename) :
	ResourceName(NULL),
	hModule(NULL),
	FileBytes(NULL),
	FilePtr(NULL),
	EndOfFile(NULL)
{
	Set_Name(filename);
	HRSRC hresource = FindResource(hmodule,ResourceName,RESOURCE_FILE_TYPE_NAME);	

	if (hresource) {
		HGLOBAL hglob = LoadResource(hmodule,hresource);
		if (hglob) {
			FileBytes = (unsigned char *)LockResource(hglob);
			if (FileBytes) {
				FilePtr = FileBytes;
				EndOfFile = FileBytes + SizeofResource(hmodule,hresource);
			}
		}
	}
}

// ??1ResourceFileClass@@ present-unmatched
ResourceFileClass::~ResourceFileClass(void)									
{ 
	if (ResourceName) 
		free(ResourceName); 
}

// ?Set_Name@ResourceFileClass@@ present-unmatched
char const * ResourceFileClass::Set_Name(char const *filename)
{
	if (ResourceName) {
		free(ResourceName);
		ResourceName = NULL;
	}
	if (filename) {
		ResourceName = strdup(filename);
	} 
	return ResourceName;
}

// ?Read@ResourceFileClass@@ present-unmatched
int ResourceFileClass::Read(void *buffer, int size)
{
	if (!FilePtr) return 0;

	if (FilePtr + size > EndOfFile) {
		size = EndOfFile - FilePtr;
	}
	memcpy(buffer,FilePtr,size);
	FilePtr += size;
	return size;
}

// ?Seek@ResourceFileClass@@ present-unmatched
int ResourceFileClass::Seek(int pos, int dir)
{
	switch (dir) {
		case SEEK_SET:
			FilePtr = FileBytes + pos;
			break;

		case SEEK_CUR:
			FilePtr = FilePtr + pos;
			break;

		case SEEK_END:
			FilePtr = EndOfFile + pos;
			break;
	}

	if (FilePtr > EndOfFile) {
		FilePtr = EndOfFile;
	}
	if (FilePtr < FileBytes) {
		FilePtr = FileBytes;
	}
	
	return FilePtr - FileBytes;
}

// ?Size@ResourceFileClass@@ present-unmatched
int ResourceFileClass::Size(void)
{
	return EndOfFile - FileBytes;
}

// ?Error@ResourceFileClass@@ present-unmatched
void ResourceFileClass::Error(int /*error*/, int /*canretry*/, char const * /*filename*/)
{
}
