// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: UserPreferences.cpp
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of user preferences
///////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/GameSpyMiscPreferences.h"
#include "Common/UserPreferences.h"
#include "Common/LadderPreferences.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Registry.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/IgnorePreferences.h"
#include "Common/QuotedPrintable.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE TYPES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE DATA ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC DATA ////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

static AsciiString intAsStr(Int val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString boolAsStr(Bool val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString realAsStr(Real val)
{
	AsciiString ret;
	ret.format("%g", val);
	return ret;
}

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// UserPreferences Class 
//-----------------------------------------------------------------------------

// ??0UserPreferences@@QAE@XZ present-unmatched
UserPreferences::UserPreferences( void )
{
}

// ??1UserPreferences@@UAE@XZ present-unmatched
UserPreferences::~UserPreferences( void )
{
}

#define LINE_LEN 2048
// ?load@UserPreferences@@UAE_NVAsciiString@@@Z present-unmatched
Bool UserPreferences::load(AsciiString fname)
{
//	if (strstr(fname.str(), "\\"))
//		throw INI_INVALID_DATA;	// must be a leaf name

	m_filename = TheGlobalData->getPath_UserData();
	m_filename.concat(fname);

	FILE *fp = fopen(m_filename.str(), "r");
	if (fp)
	{
		char buf[LINE_LEN];
		while( fgets( buf, LINE_LEN, fp ) != NULL )
		{
			AsciiString line = buf;
			line.trim();

			AsciiString key, val;
			line.nextToken(&key, "=");
			val = line.str() + 1;

			key.trim();
			val.trim();

			if (key.isEmpty() || val.isEmpty())
				continue;

			(*this)[key] = val;
		}  // end while
		fclose(fp);
		return true;
	}
	return false;
}

// ?write@UserPreferences@@UAE_NXZ
// Body in UserPreferences_write.asm (exact 162B retail).

// ?getBool@UserPreferences@@QBE_NVAsciiString@@_N@Z present-unmatched
Bool UserPreferences::getBool(AsciiString key, Bool defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	val.toLower();
	return (val == "1" || val == "t" || val == "true" || val == "y" || val == "yes" || val == "ok");
}

// ?getReal@UserPreferences@@QBEMVAsciiString@@M@Z present-unmatched
Real UserPreferences::getReal(AsciiString key, Real defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	return (Real)atof(val.str());
}

// ?getInt@UserPreferences@@QBEHVAsciiString@@H@Z present-unmatched
Int UserPreferences::getInt(AsciiString key, Int defaultValue) const
{
	AsciiString val = getAsciiString(key, AsciiString::TheEmptyString);
	if (val.isEmpty())
	{
		return defaultValue;
	}

	return atoi(val.str());
}

// ?getAsciiString@UserPreferences@@QBE?AVAsciiString@@V2@0@Z present-unmatched
AsciiString UserPreferences::getAsciiString(AsciiString key, AsciiString defaultValue) const
{
	UserPreferences::const_iterator it = find(key);
	if (it == end())
	{
		return defaultValue;
	}

	return it->second;
}

// ?setBool@UserPreferences@@QAEXVAsciiString@@_N@Z present-unmatched
void UserPreferences::setBool(AsciiString key, Bool val)
{
	(*this)[key] = boolAsStr(val);
}

// ?setReal@UserPreferences@@QAEXVAsciiString@@M@Z present-unmatched
void UserPreferences::setReal(AsciiString key, Real val)
{
	(*this)[key] = realAsStr(val);
}

// ?setInt@UserPreferences@@QAEXVAsciiString@@H@Z present-unmatched
void UserPreferences::setInt(AsciiString key, Int val)
{
	(*this)[key] = intAsStr(val);
}

// ?setAsciiString@UserPreferences@@QAEXVAsciiString@@0@Z present-unmatched
void UserPreferences::setAsciiString(AsciiString key, AsciiString val)
{
	(*this)[key] = val;
}

//-----------------------------------------------------------------------------
// QuickMatchPreferences base class 
//-----------------------------------------------------------------------------

// ??0QuickMatchPreferences@@QAE@XZ present-unmatched
QuickMatchPreferences::QuickMatchPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\QMPref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1QuickMatchPreferences@@UAE@XZ present-unmatched
QuickMatchPreferences::~QuickMatchPreferences()
{
}

// ?setMapSelected@QuickMatchPreferences@@QAEXABVAsciiString@@_N@Z present-unmatched
void QuickMatchPreferences::setMapSelected(const AsciiString& mapName, Bool selected)
{
	(*this)[AsciiStringToQuotedPrintable(mapName)] = (selected)?"1":"0";
}

// ?isMapSelected@QuickMatchPreferences@@QAE_NABVAsciiString@@@Z present-unmatched
Bool QuickMatchPreferences::isMapSelected(const AsciiString& mapName)
{
	Int ret;
	QuickMatchPreferences::const_iterator it = find(AsciiStringToQuotedPrintable(mapName));
	if (it == end())
	{
		return TRUE;
	}

	ret = atoi(it->second.str());

	return (ret != 0);
}

// ?setLastLadder@QuickMatchPreferences@@QAEXABVAsciiString@@G@Z present-unmatched
void QuickMatchPreferences::setLastLadder(const AsciiString& addr, UnsignedShort port)
{
	AsciiString strVal;
	strVal.format("%d", port);
	(*this)["LastLadderAddr"] = addr;
	(*this)["LastLadderPort"] = strVal;
}

// ?getLastLadderAddr@QuickMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString QuickMatchPreferences::getLastLadderAddr( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderAddr");
	if (it == end())
	{
		return AsciiString::TheEmptyString;
	}
	return it->second;
}

// ?getLastLadderPort@QuickMatchPreferences@@QAEGXZ present-unmatched
UnsignedShort QuickMatchPreferences::getLastLadderPort( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

// ?setMaxDisconnects@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setMaxDisconnects(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxDisconnects"] = strVal;
}

// ?getMaxDisconnects@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getMaxDisconnects( void )
{
	QuickMatchPreferences::const_iterator it = find("MaxDisconnects");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

// ?setMaxPoints@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setMaxPoints(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxPoints"] = strVal;
}

// ?getMaxPoints@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getMaxPoints( void )
{
	QuickMatchPreferences::const_iterator it = find("MaxPoints");
	if (it == end())
	{
		return 1000;
	}
	return atoi(it->second.str());
}

// ?setMinPoints@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setMinPoints(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MinPoints"] = strVal;
}

// ?getMinPoints@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getMinPoints( void )
{
	QuickMatchPreferences::const_iterator it = find("MinPoints");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

// ?setWaitTime@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setWaitTime(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["WaitTime"] = strVal;
}

// ?getWaitTime@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getWaitTime( void )
{
	QuickMatchPreferences::const_iterator it = find("WaitTime");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

// ?setNumPlayers@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setNumPlayers(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["NumPlayers"] = strVal;
}

// ?getNumPlayers@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getNumPlayers( void )
{
	QuickMatchPreferences::const_iterator it = find("NumPlayers");
	if (it == end())
	{
		return 0;	// first in list, 1v1
	}
	return atoi(it->second.str());
}

// ?setMaxPing@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setMaxPing(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxPing"] = strVal;
}

// ?getMaxPing@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getMaxPing( void )
{
	QuickMatchPreferences::const_iterator it = find("MaxPing");
	if (it == end())
	{
		return 5;
	}
	return atoi(it->second.str());
}

// ?setColor@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setColor( Int val )
{
	setInt("Color", val);
}

Int QuickMatchPreferences::getColor( void )
{
	return getInt("Color", 0);
}

// ?setSide@QuickMatchPreferences@@QAEXH@Z present-unmatched
void QuickMatchPreferences::setSide( Int val )
{
	setInt("Side", val);
}

// ?getSide@QuickMatchPreferences@@QAEHXZ present-unmatched
Int QuickMatchPreferences::getSide( void )
{
	return getInt("Side", 0);
}

//-----------------------------------------------------------------------------
// CustomMatchPreferences base class 
//-----------------------------------------------------------------------------

// ??0CustomMatchPreferences@@QAE@XZ present-unmatched
CustomMatchPreferences::CustomMatchPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\CustomPref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1CustomMatchPreferences@@UAE@XZ present-unmatched
CustomMatchPreferences::~CustomMatchPreferences()
{
}

// ?setLastLadder@CustomMatchPreferences@@QAEXABVAsciiString@@G@Z present-unmatched
void CustomMatchPreferences::setLastLadder(const AsciiString& addr, UnsignedShort port)
{
	AsciiString strVal;
	strVal.format("%d", port);
	(*this)["LastLadderAddr"] = addr;
	(*this)["LastLadderPort"] = strVal;
}

// ?getLastLadderAddr@CustomMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString CustomMatchPreferences::getLastLadderAddr( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderAddr");
	if (it == end())
	{
		return AsciiString::TheEmptyString;
	}
	return it->second;
}

// ?getLastLadderPort@CustomMatchPreferences@@QAEGXZ present-unmatched
UnsignedShort CustomMatchPreferences::getLastLadderPort( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

Int CustomMatchPreferences::getPreferredColor(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("Color");
	if (it == end())
	{
		return -1;
	}

	ret = atoi(it->second.str());
	if (ret < -1 || ret >= TheMultiplayerSettings->getNumColors())
		ret = -1;

	return ret;
}

// ?setPreferredColor@CustomMatchPreferences@@QAEXH@Z present-unmatched
void CustomMatchPreferences::setPreferredColor(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["Color"] = s;
}

Int CustomMatchPreferences::getChatSizeSlider(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("ChatSlider");
	if (it == end())
	{
		return 45;
	}

	ret = atoi(it->second.str());
	if (ret < 0 || ret > 100)
		ret = 45;

	return ret;
}

void CustomMatchPreferences::setChatSizeSlider(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["ChatSlider"] = s;
}

Int CustomMatchPreferences::getPreferredFaction(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("PlayerTemplate");
	if (it == end())
	{
		return PLAYERTEMPLATE_RANDOM;
	}

	ret = atoi(it->second.str());
	if (ret == PLAYERTEMPLATE_OBSERVER || ret < PLAYERTEMPLATE_MIN || ret >= ThePlayerTemplateStore->getPlayerTemplateCount())
		ret = PLAYERTEMPLATE_RANDOM;

	if (ret >= 0)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(ret);
		if (!fac)
			ret = PLAYERTEMPLATE_RANDOM;
		else if (fac->getStartingBuilding().isEmpty())
			ret = PLAYERTEMPLATE_RANDOM;
		else if (TheGameInfo && TheGameInfo->oldFactionsOnly() && !fac->isOldFaction())
			ret = PLAYERTEMPLATE_RANDOM;
		else {
			// Prevent from loading the disabled Generals, in case you had previously selected one as your preferred faction.
			// This is also enforced at GUI setup (GUIUtil.cpp and GameLogic.cpp).
			// @todo: unlock these when something rad happens
			Bool disallowLockedGenerals = TRUE;
			const GeneralPersona *general = TheChallengeGenerals->getGeneralByTemplateName(fac->getName());
			Bool startsLocked = general ? !general->isStartingEnabled() : FALSE;
			if (disallowLockedGenerals && startsLocked)
				ret = PLAYERTEMPLATE_RANDOM;
		}
	}

	return ret;
}

void CustomMatchPreferences::setPreferredFaction(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["PlayerTemplate"] = s;
}

Bool CustomMatchPreferences::usesSystemMapDir(void)
{
	CustomMatchPreferences::const_iterator it = find("UseSystemMapDir");
	if (it == end())
		return TRUE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setUsesSystemMapDir(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["UseSystemMapDir"] = s;
}

Bool CustomMatchPreferences::usesLongGameList(void)
{
	return TRUE;
	CustomMatchPreferences::const_iterator it = find("UseLongGameList");
	if (it == end())
		return FALSE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setUsesLongGameList(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["UseLongGameList"] = s;
}

Bool CustomMatchPreferences::allowsObservers(void)
{
	CustomMatchPreferences::const_iterator it = find("AllowObservers");
	if (it == end())
		return TRUE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setAllowsObserver(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["AllowObservers"] = s;
}

Bool CustomMatchPreferences::getDisallowAsianText( void )
{
	CustomMatchPreferences::const_iterator it = find("DisallowAsianText");
	if (it == end())
	{
		// since English Win98 machines don't have a Unicode font installed by default,
		// we're forced to disable asian chat by default for English builds.
		if (GetRegistryLanguage().compareNoCase("chinese") == 0 || GetRegistryLanguage().compareNoCase("korean") == 0 )
			return FALSE;
		else
			return TRUE;
	}

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?setDisallowAsianText@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setDisallowAsianText(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["DisallowAsianText"] = s;

}

Bool CustomMatchPreferences::getDisallowNonAsianText( void )
{
	CustomMatchPreferences::const_iterator it = find("DisallowNonAsianText");
	if (it == end())
		return FALSE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?setDisallowNonAsianText@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setDisallowNonAsianText( Bool val )
{
	AsciiString s;
	s.format("%d", val);
	(*this)["DisallowNonAsianText"] = s;
}

// ?getPreferredMap@CustomMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString CustomMatchPreferences::getPreferredMap(void)
{
	AsciiString ret;
	CustomMatchPreferences::const_iterator it = find("Map");
	if (it == end())
	{	//found find map, use default instead
		ret = getDefaultOfficialMap();
		return ret;
	}

	ret = QuotedPrintableToAsciiString(it->second);
	ret.trim();
	if (ret.isEmpty() || !isValidMap(ret, TRUE))
	{	//map is invalid, use default instead
		ret = getDefaultOfficialMap();
		return ret;
	}
	
	//can only use official maps if recording stats
	if( getUseStats() && !isOfficialMap(ret) )
		ret = getDefaultOfficialMap();
	return ret;
}

// ?setPreferredMap@CustomMatchPreferences@@QAEXVAsciiString@@@Z present-unmatched
void CustomMatchPreferences::setPreferredMap(AsciiString val)
{
	(*this)["Map"] = AsciiStringToQuotedPrintable(val);
}


static const char superweaponRestrictionKey[] = "SuperweaponRestrict";

// ?getSuperweaponRestricted@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getSuperweaponRestricted(void) const
{
  const_iterator it = find(superweaponRestrictionKey);
  if (it == end())
  {
    return false;
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setSuperweaponRestricted@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setSuperweaponRestricted( Bool superweaponRestricted )
{
  (*this)[superweaponRestrictionKey] = superweaponRestricted ? "Yes" : "No";
}

static const char startingCashKey[] = "StartingCash";
// ?getStartingCash@CustomMatchPreferences@@QBE?AVMoney@@XZ present-unmatched
Money CustomMatchPreferences::getStartingCash(void) const
{
  const_iterator it = find(startingCashKey);
  if (it == end())
  {
    return TheMultiplayerSettings->getDefaultStartingMoney();
  }
  
  Money money;
  money.deposit( strtoul( it->second.str(), NULL, 10 ), FALSE  );
  
  return money;
}

// ?setStartingCash@CustomMatchPreferences@@QAEXABVMoney@@@Z present-unmatched
void CustomMatchPreferences::setStartingCash( const Money & startingCash )
{
  AsciiString option;
  
  option.format( "%d", startingCash.countMoney() );
  
  (*this)[startingCashKey] = option;
}


static const char limitFactionsKey[] = "LimitArmies";

// Prefers to only use the original 3 sides, not USA Air Force General, GLA Toxin General, et al
// ?getFactionsLimited@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getFactionsLimited(void) const
{
  const_iterator it = find(limitFactionsKey);
  if (it == end())
  {
    return false; // The default
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setFactionsLimited@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setFactionsLimited( Bool factionsLimited )
{
  (*this)[limitFactionsKey] = factionsLimited ? "Yes" : "No";
}


static const char useStatsKey[] = "UseStats";

// ?getUseStats@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getUseStats(void) const
{
  const_iterator it = find(useStatsKey);
  if (it == end())
  {
    return true; // The default
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setUseStats@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setUseStats( Bool useStats )
{
  (*this)[useStatsKey] = useStats ? "Yes" : "No";
}

//-----------------------------------------------------------------------------
// GameSpyMiscPreferences base class 
//-----------------------------------------------------------------------------

GameSpyMiscPreferences::GameSpyMiscPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\GSMiscPref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1GameSpyMiscPreferences@@UAE@XZ present-unmatched
GameSpyMiscPreferences::~GameSpyMiscPreferences()
{
}

Int GameSpyMiscPreferences::getLocale( void )
{
	return getInt("Locale", 0);
}

void GameSpyMiscPreferences::setLocale( Int val )
{
	setInt("Locale", val);
}

AsciiString GameSpyMiscPreferences::getCachedStats( void )
{
	return getAsciiString("CachedStats", AsciiString::TheEmptyString);
}

void GameSpyMiscPreferences::setCachedStats( AsciiString val )
{
	setAsciiString("CachedStats", val);
}

// ?getQuickMatchResLocked@GameSpyMiscPreferences@@QAE_NXZ present-unmatched
Bool GameSpyMiscPreferences::getQuickMatchResLocked( void )
{
	return getBool("QMResLock", FALSE);
}

Int GameSpyMiscPreferences::getMaxMessagesPerUpdate( void )
{
	return getInt("MaxMessagesPerUpdate", 100);
}
//-----------------------------------------------------------------------------
// IgnorePreferences base class 
//-----------------------------------------------------------------------------

IgnorePreferences::IgnorePreferences()
{
	AsciiString userPrefFilename;
//	if(!TheGameSpyInfo)
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\IgnorePref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1IgnorePreferences@@UAE@XZ present-unmatched
IgnorePreferences::~IgnorePreferences()
{
}

// ?setIgnore@IgnorePreferences@@QAEXABVAsciiString@@H_N@Z present-unmatched
void IgnorePreferences::setIgnore(const AsciiString& userName, Int profileID, Bool ignore)
{
	AsciiString strVal;
	strVal.format("%d", profileID);
	if (ignore)
	{
		(*this)[strVal] = userName;
	}
	else
	{
		erase(strVal);
	}
}

// ?getIgnores@IgnorePreferences@@QAE?AV?$map@HVAsciiString@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@3@@_STL@@XZ present-unmatched
IgnorePrefMap IgnorePreferences::getIgnores(void)
{
	IgnorePrefMap ignores;
	
	IgnorePreferences::iterator it;
	for (it = begin(); it != end(); ++it)
	{
		AsciiString profileStr = it->first;
		AsciiString lastLoginStr = it->second;
		Int profileID = atoi(profileStr.str());

		ignores[profileID] = lastLoginStr;
	}

	return ignores;
}

//-----------------------------------------------------------------------------
// LadderPreferences base class 
//-----------------------------------------------------------------------------

// ??0LadderPreferences@@QAE@XZ present-unmatched
LadderPreferences::LadderPreferences()
{
}

LadderPreferences::~LadderPreferences()
{
}

// ?loadProfile@LadderPreferences@@QAE_NH@Z present-unmatched
Bool LadderPreferences::loadProfile( Int profileID )
{
	clear();
	m_ladders.clear();
	AsciiString userPrefFilename;
	userPrefFilename.format("GeneralsOnline\\Ladders%d.ini", profileID);
	Bool success = load(userPrefFilename);
	if (!success)
		return success;

	// parse out our ladders
	for (LadderPreferences::iterator it = begin(); it != end(); ++it)
	{
		LadderPref p;
		AsciiString ladName = it->first;
		AsciiString ladData = it->second;

		DEBUG_LOG(("Looking at [%s] = [%s]\n", ladName.str(), ladData.str()));

		const char *ptr = ladName.reverseFind(':');
		DEBUG_ASSERTCRASH(ptr, ("Did not find ':' in ladder name - skipping"));
		if (!ptr)
			continue;

		p.port = atoi( ptr + 1 );
		for (Int i=0; i<strlen(ptr); ++i)
		{
			ladName.removeLastChar();
		}
		p.address = QuotedPrintableToAsciiString(ladName);

		ptr = ladData.reverseFind(':');
		DEBUG_ASSERTCRASH(ptr, ("Did not find ':' in ladder data - skipping"));
		if (!ptr)
			continue;

		p.lastPlayDate = atoi( ptr + 1 );
		for (i=0; i<strlen(ptr); ++i)
		{
			ladData.removeLastChar();
		}
		p.name = QuotedPrintableToUnicodeString(ladData);

		m_ladders[p.lastPlayDate] = p;
	}

	return true;
}

// ?write@LadderPreferences@@UAE_NXZ present-unmatched
bool LadderPreferences::write( void )
{
	clear();
	LadderPrefMap::iterator lpIt;

	static const Int MAX_LADDERS = 5;
	Int count;
	for (lpIt = m_ladders.begin(), count=0; lpIt != m_ladders.end() && count<MAX_LADDERS; ++lpIt, ++count)
	{
		LadderPref p = lpIt->second;
		AsciiString ladName;
		AsciiString ladData;
		ladName.format("%s:%d", AsciiStringToQuotedPrintable(p.address).str(), p.port);
		ladData.format("%s:%d", UnicodeStringToQuotedPrintable(p.name).str(), p.lastPlayDate);
		(*this)[ladName] = ladData;
	}

	return UserPreferences::write();
}

// ?getRecentLadders@LadderPreferences@@QAEABV?$map@JVLadderPref@@U?$less@J@_STL@@V?$allocator@U?$pair@$$CBJVLadderPref@@@_STL@@@3@@_STL@@XZ present-unmatched
const LadderPrefMap& LadderPreferences::getRecentLadders( void )
{
	return m_ladders;
}

// ?addRecentLadder@LadderPreferences@@QAEXVLadderPref@@@Z present-unmatched
void LadderPreferences::addRecentLadder( LadderPref ladder )
{
	for (LadderPrefMap::iterator it = m_ladders.begin(); it != m_ladders.end(); ++it)
	{
		if (it->second == ladder)
		{
			m_ladders.erase(it);
			break;
		}
	}

	m_ladders[ladder.lastPlayDate] = ladder;
}
