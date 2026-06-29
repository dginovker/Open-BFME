#include "fx_particle_system.h"

namespace FXParticleSystem {

template <int Category, int SubCategory = 1>
class CategoryModuleClassBase {
public:
    virtual ~CategoryModuleClassBase() {}
    CategoryModuleClassBase &operator=(const CategoryModuleClassBase &that) { return *this; }
};

template <int Category>
class CategoryModuleClass : public CategoryModuleClassBase<Category> {
public:
    const char *getKey() const { return m_key; }
    const char *getName() const { return m_name; }

private:
    const char *m_key;
    const char *m_name;
};

template <int Category>
class CategoryModuleTemplateBase {
public:
    CategoryModuleTemplateBase &operator=(const CategoryModuleTemplateBase &that) { return *this; }
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category> {
public:
    CategoryModuleTemplate &operator=(const CategoryModuleTemplate &that) { return *this; }
};

template CategoryModuleClassBase<0, 1> &CategoryModuleClassBase<0, 1>::operator=(const CategoryModuleClassBase<0, 1> &);
template CategoryModuleClassBase<3, 1> &CategoryModuleClassBase<3, 1>::operator=(const CategoryModuleClassBase<3, 1> &);
template const char *CategoryModuleClass<0>::getKey() const;
template const char *CategoryModuleClass<5>::getKey() const;
template const char *CategoryModuleClass<8>::getName() const;
template CategoryModuleTemplateBase<1> &CategoryModuleTemplateBase<1>::operator=(const CategoryModuleTemplateBase<1> &);
template CategoryModuleTemplate<1> &CategoryModuleTemplate<1>::operator=(const CategoryModuleTemplate<1> &);
template CategoryModuleTemplate<3> &CategoryModuleTemplate<3>::operator=(const CategoryModuleTemplate<3> &);

ButterflyDrawModuleInfo::~ButterflyDrawModuleInfo()
{
}

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

DefaultColorModuleInfo::~DefaultColorModuleInfo()
{
}

const char *DefaultColorModuleInfo::GetSnapshotName()
{
    return "DefaultColorModuleInfo";
}

DefaultDrawModuleInfo::~DefaultDrawModuleInfo()
{
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

DefaultUpdateModuleInfo::~DefaultUpdateModuleInfo()
{
}

const char *DefaultUpdateModuleInfo::GetSnapshotName()
{
    return "DefaultUpdateModuleInfo";
}

EmissionVelocityInfo::EmissionVelocityInfo()
{
}

EmissionVelocityInfo::EmissionVelocityInfo(const EmissionVelocityInfo &that)
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

EmissionVolumeInfo::EmissionVolumeInfo(const EmissionVolumeInfo &that)
{
    m_flag = that.m_flag;
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

LightningDrawModuleInfo::~LightningDrawModuleInfo()
{
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

RenderObjectUpdateModuleInfo::~RenderObjectUpdateModuleInfo()
{
}

const char *RenderObjectUpdateModuleInfo::GetSnapshotName()
{
    return "RenderObjectUpdateModuleInfo";
}

StreakDrawModuleInfo::~StreakDrawModuleInfo()
{
}

const char *StreakDrawModuleInfo::GetSnapshotName()
{
    return "StreakDrawModuleInfo";
}

const char *TerrainCollisionModuleInfo::GetSnapshotName()
{
    return "TerrainCollisionModuleInfo";
}

WindModuleInfo::~WindModuleInfo()
{
}

const char *WindModuleInfo::GetSnapshotName()
{
    return "WindModuleInfo";
}

void ButterflyDrawModuleInfo::LoadPostProcess()
{
}

void DefaultAlphaModuleInfo::LoadPostProcess()
{
}

void DefaultColorModuleInfo::LoadPostProcess()
{
}

void DefaultDrawModuleInfo::LoadPostProcess()
{
}

void DefaultPhysicsModuleInfo::LoadPostProcess()
{
}

void DefaultUpdateModuleInfo::LoadPostProcess()
{
}

void EmissionVelocityInfo::LoadPostProcess()
{
}

void EmissionVolumeInfo::LoadPostProcess()
{
}

void LifeEventModuleInfo::LoadPostProcess()
{
}

void LightningDrawModuleInfo::LoadPostProcess()
{
}

void ParticleSystemInfo::LoadPostProcess()
{
}

void QuadDrawModuleInfo::LoadPostProcess()
{
}

void RenderObjectDrawModuleInfo::LoadPostProcess()
{
}

void RenderObjectUpdateModuleInfo::LoadPostProcess()
{
}

void StreakDrawModuleInfo::LoadPostProcess()
{
}

void TerrainCollisionModuleInfo::LoadPostProcess()
{
}

void WindModuleInfo::LoadPostProcess()
{
}

void EmissionVelocityInfo::DoXfer(Xfer &xfer)
{
}

void EmissionVolumeInfo::DoXfer(Xfer &xfer)
{
}

}
