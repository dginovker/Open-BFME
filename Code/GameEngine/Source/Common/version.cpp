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

// FILE: version.cpp //////////////////////////////////////////////////////
// Generals version number class
// Author: Matthew D. Campbell, November 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/GameText.h"
#include "Common/Version.h"

Version *TheVersion = NULL;	///< The Version singleton

// ??0Version@@ present-unmatched
Version::Version()
{
	m_major = 1;
	m_minor = 0;
	m_buildNum = 0;
	m_localBuildNum = 0;
	m_buildUser = AsciiString("somebody");
	m_buildLocation = AsciiString("somewhere");
#if defined _DEBUG || defined _INTERNAL
	m_showFullVersion = TRUE;
#else
	m_showFullVersion = FALSE;
#endif
}

// ?setVersion@Version@@ present-unmatched
void Version::setVersion(Int major, Int minor, Int buildNum,
												 Int localBuildNum, AsciiString user, AsciiString location,
												 AsciiString buildTime, AsciiString buildDate)
{
	m_major = major;
	m_minor = minor;
	m_buildNum = buildNum;
	m_localBuildNum = localBuildNum;
	m_buildUser = user;
	m_buildLocation = location;
	m_buildTime = buildTime;
	m_buildDate = buildDate;
}

UnsignedInt Version::getVersionNumber( void )
{
	return m_major << 16 | m_minor;
}

// ?getAsciiVersion@Version@@ present-unmatched
AsciiString Version::getAsciiVersion( void )
{
	AsciiString version;
#if defined _DEBUG || defined _INTERNAL
	if (m_localBuildNum)
		version.format("%d.%d.%d.%d%c%c", m_major, m_minor, m_buildNum, m_localBuildNum,
			m_buildUser.getCharAt(0), m_buildUser.getCharAt(1));
	else
		version.format("%d.%d.%d", m_major, m_minor, m_buildNum);
#else // defined _DEBUG || defined _INTERNAL
	version.format("%d.%d", m_major, m_minor);
#endif // defined _DEBUG || defined _INTERNAL

	return version;
}

// ?getUnicodeVersion@Version@@ present-unmatched
UnicodeString Version::getUnicodeVersion( void )
{
	UnicodeString version;

#if defined _DEBUG || defined _INTERNAL
	if (!m_localBuildNum)
		version.format(TheGameText->fetch("Version:Format3").str(), m_major, m_minor, m_buildNum);
	else
		version.format(TheGameText->fetch("Version:Format4").str(), m_major, m_minor, m_buildNum, m_localBuildNum,
			m_buildUser.getCharAt(0), m_buildUser.getCharAt(1));
#else // defined _DEBUG || defined _INTERNAL
	version.format(TheGameText->fetch("Version:Format2").str(), m_major, m_minor);
#endif // defined _DEBUG || defined _INTERNAL

#ifdef _DEBUG
	version.concat(UnicodeString(L" Debug"));
#endif

#ifdef _INTERNAL
	version.concat(UnicodeString(L" Internal"));
#endif

	return version;
}

// ?getFullUnicodeVersion@Version@@ present-unmatched
UnicodeString Version::getFullUnicodeVersion( void )
{
	UnicodeString version;

	if (!m_localBuildNum)
		version.format(TheGameText->fetch("Version:Format3").str(), m_major, m_minor, m_buildNum);
	else
		version.format(TheGameText->fetch("Version:Format4").str(), m_major, m_minor, m_buildNum, m_localBuildNum,
			m_buildUser.getCharAt(0), m_buildUser.getCharAt(1));

#ifdef _DEBUG
	version.concat(UnicodeString(L" Debug"));
#endif

#ifdef _INTERNAL
	version.concat(UnicodeString(L" Internal"));
#endif

	return version;
}

// ?getAsciiBuildTime@Version@@ present-unmatched
AsciiString Version::getAsciiBuildTime( void )
{
	AsciiString timeStr;
	timeStr.format("%s %s", m_buildDate.str(), m_buildTime.str());

	return timeStr;
}

// ?getUnicodeBuildTime@Version@@ present-unmatched
UnicodeString Version::getUnicodeBuildTime( void )
{
	UnicodeString build;
	UnicodeString dateStr;
	UnicodeString timeStr;

	dateStr.translate(m_buildDate);
	timeStr.translate(m_buildTime);
	build.format(TheGameText->fetch("Version:BuildTime").str(), dateStr.str(), timeStr.str());

	return build;
}

// ?getAsciiBuildLocation@Version@@ present-unmatched
AsciiString Version::getAsciiBuildLocation( void )
{
	return AsciiString(m_buildLocation);
}

// ?getUnicodeBuildLocation@Version@@ present-unmatched
UnicodeString Version::getUnicodeBuildLocation( void )
{
	UnicodeString build;
	UnicodeString machine;

	machine.translate(AsciiString(m_buildLocation));
	build.format(TheGameText->fetch("Version:BuildMachine").str(), machine.str());

	return build;
}

// ?getAsciiBuildUser@Version@@ present-unmatched
AsciiString Version::getAsciiBuildUser( void )
{
	return AsciiString(m_buildUser);
}

// ?getUnicodeBuildUser@Version@@ present-unmatched
UnicodeString Version::getUnicodeBuildUser( void )
{
	UnicodeString build;
	UnicodeString user;

	user.translate(AsciiString(m_buildUser));
	build.format(TheGameText->fetch("Version:BuildUser").str(), user.str());

	return build;
}
