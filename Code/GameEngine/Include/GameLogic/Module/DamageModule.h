#pragma once

#ifndef __DamageModule_H_
#define __DamageModule_H_

#include "Common/Module.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BehaviorModule.h"

enum BodyDamageType;

class DamageModuleInterface
{
public:
	virtual void onDamage( DamageInfo *damageInfo ) = 0;
	virtual void onHealing( DamageInfo *damageInfo ) = 0;
	virtual void onBodyDamageStateChange( const DamageInfo* damageInfo,
		BodyDamageType oldState, BodyDamageType newState ) = 0;
};

class DamageModuleData : public BehaviorModuleData
{
public:
	DamageModuleData()
	{
	}

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);

		static const FieldParse dataFieldParse[] =
		{
			{ 0, 0, 0, 0 }
		};
		p.add(dataFieldParse);
	}
};

class RetailDamageModuleDataBase : public ModuleData
{
public:
	RetailDamageModuleDataBase();
	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);
	}

private:
	char m_bfmeLayoutPadding[ 0x5C ];
};

class RetailDamageModuleData : public RetailDamageModuleDataBase
{
public:
	RetailDamageModuleData()
	{
	}
};

class DamageModule : public BehaviorModule, public DamageModuleInterface
{
	MEMORY_POOL_GLUE_ABC( DamageModule )
	MAKE_STANDARD_MODULE_MACRO_ABC( DamageModule )
	MAKE_STANDARD_MODULE_DATA_MACRO_ABC( DamageModule, RetailDamageModuleData )

public:
	DamageModule( Thing *thing, const ModuleData* moduleData );
	static Int getInterfaceMask() { return MODULEINTERFACE_DAMAGE; }
	virtual DamageModuleInterface* getDamage() { return this; }
	virtual void onDamage( DamageInfo *damageInfo ) = 0;
	virtual void onHealing( DamageInfo *damageInfo ) = 0;
	virtual void onBodyDamageStateChange( const DamageInfo* damageInfo,
		BodyDamageType oldState, BodyDamageType newState ) = 0;
};

inline DamageModule::DamageModule( Thing *thing, const ModuleData* moduleData ) :
	BehaviorModule( thing, moduleData )
{
}

inline DamageModule::~DamageModule()
{
}

#endif
