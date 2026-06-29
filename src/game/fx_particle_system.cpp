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

template <int Category>
class CategoryModuleInfo {
public:
    CategoryModuleInfo &operator=(const CategoryModuleInfo &that) { return *this; }
};

template <int Category>
struct DefaultModuleKey {
    DefaultModuleKey &operator=(const DefaultModuleKey &that) { return *this; }
};

template <int Category>
struct DefaultModuleName {
    DefaultModuleName &operator=(const DefaultModuleName &that) { return *this; }
};

template <int Category>
class DefaultModuleTemplate {
public:
    DefaultModuleTemplate &operator=(const DefaultModuleTemplate &that) { return *this; }
};

template CategoryModuleClassBase<0, 1> &CategoryModuleClassBase<0, 1>::operator=(const CategoryModuleClassBase<0, 1> &);
template CategoryModuleClassBase<1, 1> &CategoryModuleClassBase<1, 1>::operator=(const CategoryModuleClassBase<1, 1> &);
template CategoryModuleClassBase<2, 1> &CategoryModuleClassBase<2, 1>::operator=(const CategoryModuleClassBase<2, 1> &);
template CategoryModuleClassBase<3, 1> &CategoryModuleClassBase<3, 1>::operator=(const CategoryModuleClassBase<3, 1> &);
template CategoryModuleClassBase<4, 1> &CategoryModuleClassBase<4, 1>::operator=(const CategoryModuleClassBase<4, 1> &);
template CategoryModuleClassBase<5, 1> &CategoryModuleClassBase<5, 1>::operator=(const CategoryModuleClassBase<5, 1> &);
template CategoryModuleClassBase<6, 1> &CategoryModuleClassBase<6, 1>::operator=(const CategoryModuleClassBase<6, 1> &);
template CategoryModuleClassBase<7, 1> &CategoryModuleClassBase<7, 1>::operator=(const CategoryModuleClassBase<7, 1> &);
template CategoryModuleClassBase<8, 0> &CategoryModuleClassBase<8, 0>::operator=(const CategoryModuleClassBase<8, 0> &);
template const char *CategoryModuleClass<0>::getKey() const;
template const char *CategoryModuleClass<5>::getKey() const;
template const char *CategoryModuleClass<8>::getName() const;
template CategoryModuleTemplateBase<0> &CategoryModuleTemplateBase<0>::operator=(const CategoryModuleTemplateBase<0> &);
template CategoryModuleTemplateBase<1> &CategoryModuleTemplateBase<1>::operator=(const CategoryModuleTemplateBase<1> &);
template CategoryModuleTemplateBase<2> &CategoryModuleTemplateBase<2>::operator=(const CategoryModuleTemplateBase<2> &);
template CategoryModuleTemplateBase<3> &CategoryModuleTemplateBase<3>::operator=(const CategoryModuleTemplateBase<3> &);
template CategoryModuleTemplateBase<4> &CategoryModuleTemplateBase<4>::operator=(const CategoryModuleTemplateBase<4> &);
template CategoryModuleTemplateBase<5> &CategoryModuleTemplateBase<5>::operator=(const CategoryModuleTemplateBase<5> &);
template CategoryModuleTemplateBase<6> &CategoryModuleTemplateBase<6>::operator=(const CategoryModuleTemplateBase<6> &);
template CategoryModuleTemplateBase<7> &CategoryModuleTemplateBase<7>::operator=(const CategoryModuleTemplateBase<7> &);
template CategoryModuleTemplateBase<8> &CategoryModuleTemplateBase<8>::operator=(const CategoryModuleTemplateBase<8> &);
template CategoryModuleTemplate<0> &CategoryModuleTemplate<0>::operator=(const CategoryModuleTemplate<0> &);
template CategoryModuleTemplate<1> &CategoryModuleTemplate<1>::operator=(const CategoryModuleTemplate<1> &);
template CategoryModuleTemplate<2> &CategoryModuleTemplate<2>::operator=(const CategoryModuleTemplate<2> &);
template CategoryModuleTemplate<3> &CategoryModuleTemplate<3>::operator=(const CategoryModuleTemplate<3> &);
template CategoryModuleTemplate<4> &CategoryModuleTemplate<4>::operator=(const CategoryModuleTemplate<4> &);
template CategoryModuleTemplate<5> &CategoryModuleTemplate<5>::operator=(const CategoryModuleTemplate<5> &);
template CategoryModuleTemplate<6> &CategoryModuleTemplate<6>::operator=(const CategoryModuleTemplate<6> &);
template CategoryModuleInfo<0> &CategoryModuleInfo<0>::operator=(const CategoryModuleInfo<0> &);
template CategoryModuleInfo<1> &CategoryModuleInfo<1>::operator=(const CategoryModuleInfo<1> &);
template CategoryModuleInfo<2> &CategoryModuleInfo<2>::operator=(const CategoryModuleInfo<2> &);
template CategoryModuleInfo<3> &CategoryModuleInfo<3>::operator=(const CategoryModuleInfo<3> &);
template CategoryModuleInfo<4> &CategoryModuleInfo<4>::operator=(const CategoryModuleInfo<4> &);
template CategoryModuleInfo<5> &CategoryModuleInfo<5>::operator=(const CategoryModuleInfo<5> &);
template CategoryModuleInfo<6> &CategoryModuleInfo<6>::operator=(const CategoryModuleInfo<6> &);
template CategoryModuleInfo<7> &CategoryModuleInfo<7>::operator=(const CategoryModuleInfo<7> &);
template CategoryModuleInfo<8> &CategoryModuleInfo<8>::operator=(const CategoryModuleInfo<8> &);
template DefaultModuleKey<0> &DefaultModuleKey<0>::operator=(const DefaultModuleKey<0> &);
template DefaultModuleKey<1> &DefaultModuleKey<1>::operator=(const DefaultModuleKey<1> &);
template DefaultModuleKey<2> &DefaultModuleKey<2>::operator=(const DefaultModuleKey<2> &);
template DefaultModuleKey<3> &DefaultModuleKey<3>::operator=(const DefaultModuleKey<3> &);
template DefaultModuleKey<6> &DefaultModuleKey<6>::operator=(const DefaultModuleKey<6> &);
template DefaultModuleKey<7> &DefaultModuleKey<7>::operator=(const DefaultModuleKey<7> &);
template DefaultModuleName<0> &DefaultModuleName<0>::operator=(const DefaultModuleName<0> &);
template DefaultModuleName<1> &DefaultModuleName<1>::operator=(const DefaultModuleName<1> &);
template DefaultModuleName<2> &DefaultModuleName<2>::operator=(const DefaultModuleName<2> &);
template DefaultModuleName<3> &DefaultModuleName<3>::operator=(const DefaultModuleName<3> &);
template DefaultModuleName<6> &DefaultModuleName<6>::operator=(const DefaultModuleName<6> &);
template DefaultModuleName<7> &DefaultModuleName<7>::operator=(const DefaultModuleName<7> &);
template DefaultModuleTemplate<6> &DefaultModuleTemplate<6>::operator=(const DefaultModuleTemplate<6> &);

ButterflyDrawModuleInfo &ButterflyDrawModuleInfo::operator=(const ButterflyDrawModuleInfo &that)
{
    return *this;
}

ButterflyDrawModuleTemplate &ButterflyDrawModuleTemplate::operator=(const ButterflyDrawModuleTemplate &that)
{
    return *this;
}

DefaultDrawModuleInfo &DefaultDrawModuleInfo::operator=(const DefaultDrawModuleInfo &that)
{
    return *this;
}

EmissionVelocityInfo &EmissionVelocityInfo::operator=(const EmissionVelocityInfo &that)
{
    return *this;
}

QuadDrawModuleInfo &QuadDrawModuleInfo::operator=(const QuadDrawModuleInfo &that)
{
    return *this;
}

QuadDrawModuleTemplate &QuadDrawModuleTemplate::operator=(const QuadDrawModuleTemplate &that)
{
    return *this;
}

StreakDrawModuleInfo &StreakDrawModuleInfo::operator=(const StreakDrawModuleInfo &that)
{
    return *this;
}

StreakDrawModuleTemplate &StreakDrawModuleTemplate::operator=(const StreakDrawModuleTemplate &that)
{
    return *this;
}

OrthoEmissionVelocityModuleTag &OrthoEmissionVelocityModuleTag::operator=(const OrthoEmissionVelocityModuleTag &that)
{
    return *this;
}

PointEmissionVolumeModuleTag &PointEmissionVolumeModuleTag::operator=(const PointEmissionVolumeModuleTag &that)
{
    return *this;
}

ModuleTemplate &ModuleTemplate::operator=(const ModuleTemplate &that)
{
    return *this;
}

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
