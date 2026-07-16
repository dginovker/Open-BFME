// cl: /DNDEBUG /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// module_pool_glue_bulk.cpp ---------------------------------------------
//
// Retail lotrbfme.exe emits each module class's MemoryPool glue
// (getClassMemoryPool) in the class's own translation unit, pulled in by its
// vtable (getObjectMemoryPool). Our sweep ports do not compile those class TUs,
// and retail's friend_newModuleInstance uses global operator new (not the pool
// placement new), so modulefactory.cpp no longer drags the glue in either.
// This translation unit emits the glue instead, byte-identical to retail's,
// by taking the address of each class's pool placement operator new.
//

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Module.h"
#include "Common/ModuleFactory.h"
#include "Common/NameKeyGenerator.h"
#include "GameLogic/Module/AutoHealBehavior.h"
#include "GameLogic/Module/GrantStealthBehavior.h"
#include "GameLogic/Module/NeutronBlastBehavior.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CountermeasuresBehavior.h"
#include "GameLogic/Module/DumbProjectileBehavior.h"
#include "GameLogic/Module/InstantDeathBehavior.h"
#include "GameLogic/Module/SlowDeathBehavior.h"
#include "GameLogic/Module/HelicopterSlowDeathUpdate.h"
#include "GameLogic/Module/NeutronMissileSlowDeathUpdate.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/OverchargeBehavior.h"
#include "GameLogic/Module/HealContain.h"
#include "GameLogic/Module/GarrisonContain.h"
#include "GameLogic/Module/InternetHackContain.h"
#include "GameLogic/Module/RailedTransportContain.h"
#include "GameLogic/Module/RiderChangeContain.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/Module/MobNexusContain.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Module/OverlordContain.h"
#include "GameLogic/Module/HelixContain.h"
#include "GameLogic/Module/ParachuteContain.h"
#include "GameLogic/Module/POWTruckBehavior.h"
#include "GameLogic/Module/PrisonBehavior.h"
#include "GameLogic/Module/PropagandaCenterBehavior.h"
#include "GameLogic/Module/PropagandaTowerBehavior.h"
#include "GameLogic/Module/BunkerBusterBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDamagedBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDeadBehavior.h"
#include "GameLogic/Module/GenerateMinefieldBehavior.h"
#include "GameLogic/Module/ParkingPlaceBehavior.h"
#include "GameLogic/Module/FlightDeckBehavior.h"
#include "GameLogic/Module/PoisonedBehavior.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/SupplyWarehouseCripplingBehavior.h"
#include "GameLogic/Module/TechBuildingBehavior.h"
#include "GameLogic/Module/MinefieldBehavior.h"
#include "GameLogic/Module/BattleBusSlowDeathBehavior.h"
#include "GameLogic/Module/JetSlowDeathBehavior.h"
#include "GameLogic/Module/CreateCrateDie.h"
#include "GameLogic/Module/CreateObjectDie.h"
#include "GameLogic/Module/CrushDie.h"
#include "GameLogic/Module/DamDie.h"
#include "GameLogic/Module/DestroyDie.h"
#include "GameLogic/Module/EjectPilotDie.h"
#include "GameLogic/Module/FXListDie.h"
#include "GameLogic/Module/RebuildHoleExposeDie.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/UpgradeDie.h"
#include "GameLogic/Module/KeepObjectDie.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AnimationSteeringUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/BaseRegenerateUpdate.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/ChinookAIUpdate.h"
#include "GameLogic/Module/DefaultProductionExitUpdate.h"
#include "GameLogic/Module/DeletionUpdate.h"
#include "GameLogic/Module/SmartBombTargetHomingUpdate.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/DynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/DynamicShroudClearingRangeUpdate.h"
#include "GameLogic/Module/EnemyNearUpdate.h"
#include "GameLogic/Module/FireSpreadUpdate.h"
#include "GameLogic/Module/FirestormDynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/FireWeaponUpdate.h"
#include "GameLogic/Module/FlammableUpdate.h"
#include "GameLogic/Module/FloatUpdate.h"
#include "GameLogic/Module/TensileFormationUpdate.h"
#include "GameLogic/Module/HackInternetAIUpdate.h"
#include "GameLogic/Module/DeployStyleAIUpdate.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Module/HeightDieUpdate.h"
#include "GameLogic/Module/HordeUpdate.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/PointDefenseLaserUpdate.h"
#include "GameLogic/Module/CleanupHazardUpdate.h"
#include "GameLogic/Module/AutoFindHealingUpdate.h"
#include "GameLogic/Module/CommandButtonHuntUpdate.h"
#include "GameLogic/Module/PilotFindVehicleUpdate.h"
#include "GameLogic/Module/DemoTrapUpdate.h"
#include "GameLogic/Module/ParticleUplinkCannonUpdate.h"
#include "GameLogic/Module/SpectreGunshipUpdate.h"
#include "GameLogic/Module/SpectreGunshipDeploymentUpdate.h"
#include "GameLogic/Module/BaikonurLaunchPower.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/LifetimeUpdate.h"
#include "GameLogic/Module/RadiusDecalUpdate.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/MissileAIUpdate.h"
#include "GameLogic/Module/NeutronMissileUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/POWTruckAIUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/ProneUpdate.h"
#include "GameLogic/Module/QueueProductionExitUpdate.h"
#include "GameLogic/Module/RadarUpdate.h"
#include "GameLogic/Module/RepairDockUpdate.h"
#include "GameLogic/Module/PrisonDockUpdate.h"
#include "GameLogic/Module/RailedTransportDockUpdate.h"
#include "GameLogic/Module/RailedTransportAIUpdate.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Module/SlavedUpdate.h"
#include "GameLogic/Module/MobMemberSlavedUpdate.h"
#include "GameLogic/Module/SpecialAbilityUpdate.h"
#include "GameLogic/Module/MissileLauncherBuildingUpdate.h"
#include "GameLogic/Module/StealthDetectorUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpawnPointProductionExitUpdate.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/SpyVisionUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/FireOCLAfterWeaponCooldownUpdate.h"
#include "GameLogic/Module/HijackerUpdate.h"
#include "GameLogic/Module/StructureCollapseUpdate.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyCenterProductionExitUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/Module/TransportAIUpdate.h"
#include "GameLogic/Module/WanderAIUpdate.h"
#include "GameLogic/Module/WaveGuideUpdate.h"
#include "GameLogic/Module/WeaponBonusUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"
#include "GameLogic/Module/PowerPlantUpdate.h"
#include "GameLogic/Module/CheckpointUpdate.h"
#include "GameLogic/Module/EMPUpdate.h"
#include "GameLogic/Module/ActiveShroudUpgrade.h"
#include "GameLogic/Module/ArmorUpgrade.h"
#include "GameLogic/Module/CommandSetUpgrade.h"
#include "GameLogic/Module/GrantScienceUpgrade.h"
#include "GameLogic/Module/PassengersFireUpgrade.h"
#include "GameLogic/Module/LocomotorSetUpgrade.h"
#include "GameLogic/Module/ObjectCreationUpgrade.h"
#include "GameLogic/Module/RadarUpgrade.h"
#include "GameLogic/Module/PowerPlantUpgrade.h"
#include "GameLogic/Module/ReplaceObjectUpgrade.h"
#include "GameLogic/Module/ModelConditionUpgrade.h"
#include "GameLogic/Module/StatusBitsUpgrade.h"
#include "GameLogic/Module/SubObjectsUpgrade.h"
#include "GameLogic/Module/StealthUpgrade.h"
#include "GameLogic/Module/UnpauseSpecialPowerUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/WeaponSetUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/CostModifierUpgrade.h"
#include "GameLogic/Module/ExperienceScalarUpgrade.h"
#include "GameLogic/Module/MaxHealthUpgrade.h"
#include "GameLogic/Module/LockWeaponCreate.h"
#include "GameLogic/Module/SupplyCenterCreate.h"
#include "GameLogic/Module/SupplyWarehouseCreate.h"
#include "GameLogic/Module/GrantUpgradeCreate.h"
#include "GameLogic/Module/PreorderCreate.h"
#include "GameLogic/Module/SpecialPowerCreate.h"
#include "GameLogic/Module/VeterancyGainCreate.h"
#include "GameLogic/Module/BoneFXDamage.h"
#include "GameLogic/Module/TransitionDamageFX.h"
#include "GameLogic/Module/FireWeaponCollide.h"
#include "GameLogic/Module/SquishCollide.h"
#include "GameLogic/Module/ConvertToCarBombCrateCollide.h"
#include "GameLogic/Module/ConvertToHijackedVehicleCrateCollide.h"
#include "GameLogic/Module/HealCrateCollide.h"
#include "GameLogic/Module/MoneyCrateCollide.h"
#include "GameLogic/Module/SabotageCommandCenterCrateCollide.h"
#include "GameLogic/Module/SabotageFakeBuildingCrateCollide.h"
#include "GameLogic/Module/SabotageInternetCenterCrateCollide.h"
#include "GameLogic/Module/SabotageMilitaryFactoryCrateCollide.h"
#include "GameLogic/Module/SabotagePowerPlantCrateCollide.h"
#include "GameLogic/Module/SabotageSuperweaponCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyCenterCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyDropzoneCrateCollide.h"
#include "GameLogic/Module/SalvageCrateCollide.h"
#include "GameLogic/Module/ShroudCrateCollide.h"
#include "GameLogic/Module/UnitCrateCollide.h"
#include "GameLogic/Module/VeterancyCrateCollide.h"
#include "GameLogic/Module/InactiveBody.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/HighlanderBody.h"
#include "GameLogic/Module/ImmortalBody.h"
#include "GameLogic/Module/StructureBody.h"
#include "GameLogic/Module/HiveStructureBody.h"
#include "GameLogic/Module/UndeadBody.h"
#include "GameLogic/Module/CashHackSpecialPower.h"
#include "GameLogic/Module/DefectorSpecialPower.h"
#include "GameLogic/Module/DemoralizeSpecialPower.h"
#include "GameLogic/Module/OCLSpecialPower.h"
#include "GameLogic/Module/SpecialAbility.h"
#include "GameLogic/Module/SpyVisionSpecialPower.h"
#include "GameLogic/Module/CashBountyPower.h"
#include "GameLogic/Module/CleanupAreaPower.h"
#include "GameLogic/Module/FireWeaponPower.h"
#include "GameClient/Module/AnimatedParticleSysBoneClientUpdate.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "GameClient/Module/BeaconClientUpdate.h"

namespace ModulePoolGlueBulk
{

// Keep a separate pool-placement helper so getClassMemoryPool is emitted, while
// the candidate body itself follows BFME's global-allocation module factory.
#define EMIT_MODULE_POOL_GLUE( cls ) \
	Module *pool_emit_##cls( Thing *thing, const ModuleData *moduleData ) { return newInstance( cls )( thing, moduleData ); } \
	Module *emit_##cls( Thing *thing, const ModuleData *moduleData ) { return ::new cls( thing, moduleData ); }

EMIT_MODULE_POOL_GLUE( AIUpdateInterface )
EMIT_MODULE_POOL_GLUE( ArmorUpgrade )
EMIT_MODULE_POOL_GLUE( AssaultTransportAIUpdate )
EMIT_MODULE_POOL_GLUE( AssistedTargetingUpdate )
EMIT_MODULE_POOL_GLUE( AutoDepositUpdate )
EMIT_MODULE_POOL_GLUE( AutoFindHealingUpdate )
EMIT_MODULE_POOL_GLUE( AutoHealBehavior )
EMIT_MODULE_POOL_GLUE( BattlePlanUpdate )
EMIT_MODULE_POOL_GLUE( BridgeBehavior )
EMIT_MODULE_POOL_GLUE( BridgeTowerBehavior )
EMIT_MODULE_POOL_GLUE( CaveContain )
EMIT_MODULE_POOL_GLUE( CommandButtonHuntUpdate )
EMIT_MODULE_POOL_GLUE( CommandSetUpgrade )
EMIT_MODULE_POOL_GLUE( CostModifierUpgrade )
EMIT_MODULE_POOL_GLUE( CreateCrateDie )
EMIT_MODULE_POOL_GLUE( CreateObjectDie )
EMIT_MODULE_POOL_GLUE( CrushDie )
EMIT_MODULE_POOL_GLUE( DefaultProductionExitUpdate )
EMIT_MODULE_POOL_GLUE( DeletionUpdate )
EMIT_MODULE_POOL_GLUE( DemoTrapUpdate )
EMIT_MODULE_POOL_GLUE( DeployStyleAIUpdate )
EMIT_MODULE_POOL_GLUE( DestroyDie )
EMIT_MODULE_POOL_GLUE( DozerAIUpdate )
EMIT_MODULE_POOL_GLUE( DynamicShroudClearingRangeUpdate )
EMIT_MODULE_POOL_GLUE( ExperienceScalarUpgrade )
EMIT_MODULE_POOL_GLUE( FXListDie )
EMIT_MODULE_POOL_GLUE( FireSpreadUpdate )
EMIT_MODULE_POOL_GLUE( FireWeaponCollide )
EMIT_MODULE_POOL_GLUE( FireWeaponUpdate )
EMIT_MODULE_POOL_GLUE( FireWeaponWhenDamagedBehavior )
EMIT_MODULE_POOL_GLUE( FireWeaponWhenDeadBehavior )
EMIT_MODULE_POOL_GLUE( FlammableUpdate )
EMIT_MODULE_POOL_GLUE( FloatUpdate )
EMIT_MODULE_POOL_GLUE( GarrisonContain )
EMIT_MODULE_POOL_GLUE( GrantUpgradeCreate )
EMIT_MODULE_POOL_GLUE( HealContain )
EMIT_MODULE_POOL_GLUE( HealCrateCollide )
EMIT_MODULE_POOL_GLUE( HeightDieUpdate )
EMIT_MODULE_POOL_GLUE( HijackerUpdate )
EMIT_MODULE_POOL_GLUE( InstantDeathBehavior )
EMIT_MODULE_POOL_GLUE( KeepObjectDie )
EMIT_MODULE_POOL_GLUE( LaserUpdate )
EMIT_MODULE_POOL_GLUE( LifetimeUpdate )
EMIT_MODULE_POOL_GLUE( LockWeaponCreate )
EMIT_MODULE_POOL_GLUE( LocomotorSetUpgrade )
EMIT_MODULE_POOL_GLUE( MaxHealthUpgrade )
EMIT_MODULE_POOL_GLUE( ModelConditionUpgrade )
EMIT_MODULE_POOL_GLUE( MoneyCrateCollide )
EMIT_MODULE_POOL_GLUE( ObjectCreationUpgrade )
EMIT_MODULE_POOL_GLUE( OpenContain )
EMIT_MODULE_POOL_GLUE( PoisonedBehavior )
EMIT_MODULE_POOL_GLUE( PreorderCreate )
EMIT_MODULE_POOL_GLUE( ProductionUpdate )
EMIT_MODULE_POOL_GLUE( ProneUpdate )
EMIT_MODULE_POOL_GLUE( PropagandaTowerBehavior )
EMIT_MODULE_POOL_GLUE( QueueProductionExitUpdate )
EMIT_MODULE_POOL_GLUE( RadarUpdate )
EMIT_MODULE_POOL_GLUE( RadarUpgrade )
EMIT_MODULE_POOL_GLUE( RadiusDecalUpdate )
EMIT_MODULE_POOL_GLUE( RailedTransportDockUpdate )
EMIT_MODULE_POOL_GLUE( RepairDockUpdate )
EMIT_MODULE_POOL_GLUE( RiderChangeContain )
EMIT_MODULE_POOL_GLUE( SalvageCrateCollide )
EMIT_MODULE_POOL_GLUE( ShroudCrateCollide )
EMIT_MODULE_POOL_GLUE( SlavedUpdate )
EMIT_MODULE_POOL_GLUE( SpawnBehavior )
EMIT_MODULE_POOL_GLUE( SpawnPointProductionExitUpdate )
EMIT_MODULE_POOL_GLUE( SpecialPowerCompletionDie )
EMIT_MODULE_POOL_GLUE( SpecialPowerCreate )
EMIT_MODULE_POOL_GLUE( SquishCollide )
EMIT_MODULE_POOL_GLUE( StatusBitsUpgrade )
EMIT_MODULE_POOL_GLUE( StealthDetectorUpdate )
EMIT_MODULE_POOL_GLUE( StealthUpdate )
EMIT_MODULE_POOL_GLUE( StealthUpgrade )
EMIT_MODULE_POOL_GLUE( SubObjectsUpgrade )
EMIT_MODULE_POOL_GLUE( SupplyCenterCreate )
EMIT_MODULE_POOL_GLUE( SupplyCenterDockUpdate )
EMIT_MODULE_POOL_GLUE( SupplyCenterProductionExitUpdate )
EMIT_MODULE_POOL_GLUE( SupplyTruckAIUpdate )
EMIT_MODULE_POOL_GLUE( SupplyWarehouseCreate )
EMIT_MODULE_POOL_GLUE( SupplyWarehouseCripplingBehavior )
EMIT_MODULE_POOL_GLUE( SupplyWarehouseDockUpdate )
EMIT_MODULE_POOL_GLUE( TransitionDamageFX )
EMIT_MODULE_POOL_GLUE( TransportAIUpdate )
EMIT_MODULE_POOL_GLUE( TransportContain )
EMIT_MODULE_POOL_GLUE( TunnelContain )
EMIT_MODULE_POOL_GLUE( UnitCrateCollide )
EMIT_MODULE_POOL_GLUE( UnpauseSpecialPowerUpgrade )
EMIT_MODULE_POOL_GLUE( UpgradeDie )
EMIT_MODULE_POOL_GLUE( VeterancyCrateCollide )
EMIT_MODULE_POOL_GLUE( WanderAIUpdate )
EMIT_MODULE_POOL_GLUE( WeaponBonusUpgrade )
EMIT_MODULE_POOL_GLUE( WeaponSetUpgrade )
EMIT_MODULE_POOL_GLUE( WorkerAIUpdate )
EMIT_MODULE_POOL_GLUE( InactiveBody )
EMIT_MODULE_POOL_GLUE( ActiveBody )
EMIT_MODULE_POOL_GLUE( HighlanderBody )
EMIT_MODULE_POOL_GLUE( ImmortalBody )
EMIT_MODULE_POOL_GLUE( StructureBody )
EMIT_MODULE_POOL_GLUE( DefectorSpecialPower )
EMIT_MODULE_POOL_GLUE( OCLSpecialPower )
EMIT_MODULE_POOL_GLUE( SpecialAbility )
EMIT_MODULE_POOL_GLUE( AnimatedParticleSysBoneClientUpdate )
EMIT_MODULE_POOL_GLUE( BeaconClientUpdate )

} // namespace ModulePoolGlueBulk
