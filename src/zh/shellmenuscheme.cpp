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

// FILE: ShellMenuScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	ShellMenuScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	
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

#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"
#include "GameClient/Shell.h"
#include "GameClient/Display.h"
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

const FieldParse ShellMenuSchemeManager::m_shellMenuSchemeFieldParseTable[] = 
{

	{ "ImagePart",						ShellMenuSchemeManager::parseImagePart,			NULL, NULL },
	{ "LinePart",							ShellMenuSchemeManager::parseLinePart,	NULL, NULL },
	{ NULL,										NULL,													NULL, 0 }  // keep this last

};

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z present-unmatched
void INI::parseShellMenuSchemeDefinition( INI *ini )
{
	AsciiString name;
	ShellMenuSchemeManager *SMSchemeManager;
	ShellMenuScheme *SMScheme;

	// read the name
	const char* c = ini->getNextToken();
	name.set( c );	

	// find existing item if present
	SMSchemeManager = TheShell->getShellMenuSchemeManager();
	DEBUG_ASSERTCRASH( SMSchemeManager, ("parseShellMenuSchemeDefinition: Unable to Get SMSchemeManager\n") );
	if( !SMSchemeManager )
		return;

	// If we have a previously allocated control bar, this will return a cleared out pointer to it so we
	// can overwrite it	
	SMScheme = SMSchemeManager->newShellMenuScheme( name );

	// sanity
	DEBUG_ASSERTCRASH( SMScheme, ("parseControlBarSchemeDefinition: Unable to allocate Scheme '%s'\n", name.str()) );

	// parse the ini definition
	ini->initFromINI( SMScheme, SMSchemeManager->getFieldParse() );

}  // end parseCommandButtonDefinition

ShellMenuSchemeLine::ShellMenuSchemeLine( void )
{
	m_startPos.x = m_startPos.y = 0;
	m_endPos.x = m_endPos.y = 0;
	m_color = GAME_COLOR_UNDEFINED;
	m_width = 1;
}
// ??1ShellMenuSchemeLine@@QAE@XZ present-unmatched
ShellMenuSchemeLine::~ShellMenuSchemeLine( void )
{
}

// ??0ShellMenuSchemeImage@@QAE@XZ present-unmatched
ShellMenuSchemeImage::ShellMenuSchemeImage( void )
{
	m_name.clear();
	m_position.x = m_position.y = 0;
	m_size.x = m_size.x = 0;
	m_image = NULL;
}

// ??1ShellMenuSchemeImage@@QAE@XZ present-unmatched
ShellMenuSchemeImage::~ShellMenuSchemeImage( void )
{
	m_image = NULL;
}

// ??0ShellMenuScheme@@QAE@XZ present-unmatched
ShellMenuScheme::ShellMenuScheme( void )
{
	
}

// ??1ShellMenuScheme@@QAE@XZ present-unmatched
ShellMenuScheme::~ShellMenuScheme( void )
{
	ShellMenuSchemeImageListIt it = m_imageList.begin();
	while(it != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *it;
		it = m_imageList.erase( it );
		if(image)
			delete image;
	}

	ShellMenuSchemeLineListIt lineIt = m_lineList.begin();
	while(lineIt != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *lineIt;
		lineIt = m_lineList.erase( lineIt );
		if(line)
			delete line;
	}

	
}

// ?addLine@ShellMenuScheme@@QAEXPAVShellMenuSchemeLine@@@Z present-unmatched
void ShellMenuScheme::addLine( ShellMenuSchemeLine* schemeLine )
{
	if(!schemeLine)
		return;

	m_lineList.push_back( schemeLine );
}


// ?addImage@ShellMenuScheme@@QAEXPAVShellMenuSchemeImage@@@Z present-unmatched
void ShellMenuScheme::addImage( ShellMenuSchemeImage* schemeImage )
{
	if(!schemeImage)
		return;

	m_imageList.push_back( schemeImage );
}

// ?draw@ShellMenuScheme@@QAEXXZ present-unmatched
void ShellMenuScheme::draw( void )
{

	ShellMenuSchemeImageListIt imageIt = m_imageList.begin();
	while(imageIt != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *imageIt;
		if(image && image->m_image)
		{
			TheDisplay->drawImage(image->m_image, image->m_position.x, image->m_position.y,
														image->m_position.x + image->m_size.x , image->m_position.y + image->m_size.y);
		}
		++imageIt;
	}

	ShellMenuSchemeLineListIt it = m_lineList.begin();
	while(it != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *it;
		
		if(line)
		{
			TheDisplay->drawLine(line->m_startPos.x, line->m_startPos.y, line->m_endPos.x,
														line->m_endPos.y,line->m_width, line->m_color);
		}
		++it;
	}


}

// ??0ShellMenuSchemeManager@@QAE@XZ present-unmatched
ShellMenuSchemeManager::ShellMenuSchemeManager( void )
{
	m_currentScheme = NULL;
}

// ??1ShellMenuSchemeManager@@QAE@XZ present-unmatched
ShellMenuSchemeManager::~ShellMenuSchemeManager( void )
{
	m_currentScheme = NULL;


	ShellMenuSchemeListIt it = m_schemeList.begin();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		it = m_schemeList.erase( it );
		if(scheme)
			delete scheme;
	}
	
}

// ?parseImagePart@ShellMenuSchemeManager@@ present-unmatched
void ShellMenuSchemeManager::parseImagePart(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	static const FieldParse myFieldParse[] = 
		{
			{ "Position",				INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeImage, m_position ) },
			{ "Size",						INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeImage, m_size ) },
      { "ImageName",			INI::parseMappedImage,		NULL, offsetof( ShellMenuSchemeImage, m_image ) },
			{ NULL,							NULL,											NULL, 0 }  // keep this last
		};

	ShellMenuSchemeImage *schemeImage = NEW ShellMenuSchemeImage;
	ini->initFromINI(schemeImage, myFieldParse);
	((ShellMenuScheme*)instance)->addImage(schemeImage);

}

// ?parseLinePart@ShellMenuSchemeManager@@ present-unmatched
void ShellMenuSchemeManager::parseLinePart(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
{
	static const FieldParse myFieldParse[] = 
		{
			{ "StartPosition",		INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeLine, m_startPos ) },
			{ "EndPosition",			INI::parseICoord2D,				NULL, offsetof( ShellMenuSchemeLine, m_endPos ) },
      { "Color",						INI::parseColorInt,				NULL, offsetof( ShellMenuSchemeLine, m_color ) },
			{ "Width",						INI::parseInt,						NULL, offsetof( ShellMenuSchemeLine, m_width ) },
			
			{ NULL,								NULL,											NULL, 0 }  // keep this last
		};

	ShellMenuSchemeLine *schemeLine = NEW ShellMenuSchemeLine;
	ini->initFromINI(schemeLine, myFieldParse);
	((ShellMenuScheme*)instance)->addLine(schemeLine);

}

// ?newShellMenuScheme@ShellMenuSchemeManager@@QAEPAVShellMenuScheme@@VAsciiString@@@Z present-unmatched
ShellMenuScheme *ShellMenuSchemeManager::newShellMenuScheme(AsciiString name)
{
	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if(scheme->m_name.compare(name) == 0)
		{
			m_schemeList.erase( it );
			delete scheme;
			break;
		}
		else
			++it;
	}
	ShellMenuScheme *newScheme = NEW ShellMenuScheme;
	newScheme->m_name.set(name);
	m_schemeList.push_back(newScheme);
	return newScheme;
}

// ?init@ShellMenuSchemeManager@@QAEXXZ present-unmatched
void ShellMenuSchemeManager::init( void )
{
	INI ini;
	// Read from INI all the ControlBarSchemes
	ini.load( AsciiString( "Data\\INI\\Default\\ShellMenuScheme.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\ShellMenuScheme.ini" ), INI_LOAD_OVERWRITE, NULL );

}

// ?setShellMenuScheme@ShellMenuSchemeManager@@QAEXVAsciiString@@@Z present-unmatched
void ShellMenuSchemeManager::setShellMenuScheme( AsciiString name )
{
	if(name.isEmpty())
	{
		m_currentScheme = NULL;
		return;
	}

	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if(scheme->m_name.compare(name) == 0)
		{
			m_currentScheme = scheme;
			break;
		}
		++it;
	}
}

// ?draw@ShellMenuSchemeManager@@QAEXXZ present-unmatched
void ShellMenuSchemeManager::draw( void )
{
	if(m_currentScheme)
		m_currentScheme->draw();
}

// ?update@ShellMenuSchemeManager@@QAEXXZ present-unmatched
void ShellMenuSchemeManager::update( void )
{

}
//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

