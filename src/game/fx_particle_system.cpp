#include "fx_particle_system.h"

namespace FXParticleSystem {

const char *ButterflyDrawModuleInfo::GetSnapshotName()
{
    return "ButterflyDrawModuleInfo";
}

DefaultAlphaModuleInfo::~DefaultAlphaModuleInfo()
{
}

const char *DefaultAlphaModuleInfo::GetSnapshotName()
{
    return "DefaultAlphaModuleInfo";
}

const char *DefaultColorModuleInfo::GetSnapshotName()
{
    return "DefaultColorModuleInfo";
}

const char *DefaultDrawModuleInfo::GetSnapshotName()
{
    return "DefaultDrawModuleInfo";
}

DefaultPhysicsModuleInfo::~DefaultPhysicsModuleInfo()
{
}

const char *DefaultPhysicsModuleInfo::GetSnapshotName()
{
    return "DefaultPhysicsModuleInfo";
}

const char *DefaultUpdateModuleInfo::GetSnapshotName()
{
    return "DefaultUpdateModuleInfo";
}

EmissionVelocityInfo::EmissionVelocityInfo()
{
}

EmissionVelocityInfo::~EmissionVelocityInfo()
{
}

const char *EmissionVelocityInfo::GetSnapshotName()
{
    return "EmissionVelocityInfo";
}

EmissionVolumeInfo::EmissionVolumeInfo()
{
    m_flag = false;
}

EmissionVolumeInfo::~EmissionVolumeInfo()
{
}

const char *EmissionVolumeInfo::GetSnapshotName()
{
    return "EmissionVolumeInfo";
}

const char *LifeEventModuleInfo::GetSnapshotName()
{
    return "LifeEventModuleInfo";
}

const char *LightningDrawModuleInfo::GetSnapshotName()
{
    return "LightningDrawModuleInfo";
}

const char *ParticleSystemInfo::GetSnapshotName()
{
    return "ParticleSystemInfo";
}

QuadDrawModuleInfo::QuadDrawModuleInfo()
{
}

QuadDrawModuleInfo::~QuadDrawModuleInfo()
{
}

const char *QuadDrawModuleInfo::GetSnapshotName()
{
    return "QuadDrawModuleInfo";
}

const char *RenderObjectDrawModuleInfo::GetSnapshotName()
{
    return "RenderObjectDrawModuleInfo";
}

const char *RenderObjectUpdateModuleInfo::GetSnapshotName()
{
    return "RenderObjectUpdateModuleInfo";
}

const char *StreakDrawModuleInfo::GetSnapshotName()
{
    return "StreakDrawModuleInfo";
}

const char *TerrainCollisionModuleInfo::GetSnapshotName()
{
    return "TerrainCollisionModuleInfo";
}

const char *WindModuleInfo::GetSnapshotName()
{
    return "WindModuleInfo";
}

}
