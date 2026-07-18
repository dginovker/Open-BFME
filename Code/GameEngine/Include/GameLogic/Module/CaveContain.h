#pragma once

#ifndef __CAVE_CONTAIN_H_
#define __CAVE_CONTAIN_H_

#include "GameLogic/Module/CreateModule.h"
#include "GameLogic/Module/OpenContain.h"

struct Sound;
class Team;

class CaveContainModuleData : public OpenContainModuleData
{
public:
	char m_bfmeLayoutPadding[ 0x44 ];
	Int m_caveIndexData;

	CaveContainModuleData()
	{
		m_caveIndexData = 0;
	}

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		OpenContainModuleData::buildFieldParse(p);

		static const FieldParse dataFieldParse[] =
		{
			{ "CaveIndex", INI::parseInt, NULL, offsetof( CaveContainModuleData, m_caveIndexData ) },
			{ 0, 0, 0, 0 }
		};
		p.add(dataFieldParse);
	}
};

class CaveContain : public OpenContain, public CreateModuleInterface, public CaveInterface
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( CaveContain, "CaveContain" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( CaveContain, CaveContainModuleData )

public:
	CaveContain( Thing *thing, const ModuleData* moduleData );

	virtual CreateModuleInterface* getCreate() { return this; }
	virtual CaveInterface* getCaveInterface() { return this; }
	static Int getInterfaceMask() { return OpenContain::getInterfaceMask() | (MODULEINTERFACE_CREATE); }

	virtual OpenContain *asOpenContain() { return this; }
	virtual Bool isGarrisonable() const { return false; }
	virtual Bool isBustable() const { return TRUE; }
	virtual Bool isHealContain() const { return false; }

	virtual void onContaining( Object *obj, Bool wasSelected );
	virtual void onRemoving( Object *obj );

	virtual Bool isValidContainerFor(const Object* obj, Bool checkCapacity) const;
	virtual void addToContainList( Object *obj );
	virtual void removeFromContain( Object *obj, Bool exposeStealthUnits = FALSE );
	virtual void removeAllContained( Bool exposeStealthUnits = FALSE );

	virtual void recalcApparentControllingPlayer( void );

	virtual void iterateContained( ContainIterateFunc func, void *userData, Bool reverse );
	virtual UnsignedInt getContainCount() const;
	virtual Int getContainMax( void ) const;
	virtual const ContainedItemsList* getContainedItemsList() const;
	virtual Bool isKickOutOnCapture(){ return FALSE; }

	virtual void onDie( const DamageInfo *damageInfo );

	virtual void onCreate( void );
	virtual void onBuildComplete();
	virtual Bool shouldDoOnBuildComplete() const { return m_needToRunOnBuildComplete; }

	virtual void tryToSetCaveIndex( Int newIndex );
	virtual void setOriginalTeam( Team *oldTeam );

protected:
	void changeTeamOnAllConnectedCaves( Team *newTeam, Bool setOriginalTeams );

	Bool m_needToRunOnBuildComplete;
	Int m_caveIndex;
	Team *m_originalTeam;
};

#endif
