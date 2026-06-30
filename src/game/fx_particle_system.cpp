#include "fx_particle_system.h"

#include "../math/region.h"

namespace FXParticleSystem {

__declspec(naked) const char *GetKey(ModuleCategory category)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x04
        __emit 0xc5
        __emit 0x04
        __emit 0x05
        __emit 0x11
        __emit 0x01
        __emit 0xc3
    }
}

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
    CategoryModuleInfo(const CategoryModuleInfo &that);
    virtual ~CategoryModuleInfo() { }
    CategoryModuleInfo &operator=(const CategoryModuleInfo &that) { return *this; }
};

template <int Category>
CategoryModuleInfo<Category>::CategoryModuleInfo(const CategoryModuleInfo<Category> &that)
{
}

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
template class CategoryModuleInfo<0>;
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

__declspec(naked) LightningEmissionInfo &LightningEmissionInfo::operator=(const LightningEmissionInfo &that)
{
    __asm {
        push esi
        push edi
        mov eax, ecx
        mov ecx, [esp+0x0c]
        mov dl, [ecx+4]
        mov [eax+4], dl
        lea edx, [ecx+0x8]
        mov edi, [edx]
        lea esi, [eax+0x8]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x14]
        mov edi, [edx]
        lea esi, [eax+0x14]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x20]
        mov edi, [edx]
        lea esi, [eax+0x20]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x2c]
        mov edi, [edx]
        lea esi, [eax+0x2c]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x38]
        mov edi, [edx]
        lea esi, [eax+0x38]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x44]
        mov edi, [edx]
        lea esi, [eax+0x44]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x50]
        mov edi, [edx]
        lea esi, [eax+0x50]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x5c]
        mov edi, [edx]
        lea esi, [eax+0x5c]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x68]
        mov edi, [edx]
        lea esi, [eax+0x68]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        lea edx, [ecx+0x74]
        mov edi, [edx]
        lea esi, [eax+0x74]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        add ecx, 0x80
        mov esi, [ecx]
        lea edx, [eax+0x80]
        mov [edx], esi
        mov esi, [ecx+4]
        mov [edx+4], esi
        mov ecx, [ecx+8]
        pop edi
        mov [edx+8], ecx
        pop esi
        ret 4
    }
}

LightningEmissionInfo::~LightningEmissionInfo()
{
    *(void **)this = (void *)0x01073744;
}

__declspec(naked) EventModuleInfo::EventModuleInfo()
{
    __asm {
        mov eax, ecx
        mov byte ptr [eax], 1
        mov byte ptr [eax + 1], 1
        ret
    }
}

__declspec(naked) EventModuleInfo::~EventModuleInfo()
{
    __asm {
        ret
    }
}

__declspec(naked) EventModuleInfo &EventModuleInfo::operator=(const EventModuleInfo &that)
{
    __asm {
        mov eax, ecx
        mov ecx, [esp + 4]
        mov dx, [ecx]
        mov [eax], dx
        ret 4
    }
}

BoxEmissionVolumeInfo::~BoxEmissionVolumeInfo()
{
    *(void **)this = (void *)0x01073744;
}

SphereEmissionVolumeInfo::~SphereEmissionVolumeInfo()
{
    *(void **)this = (void *)0x01073744;
}

CylinderEmissionVolumeInfo::~CylinderEmissionVolumeInfo()
{
    *(void **)this = (void *)0x01073744;
}

LineEmissionVolumeInfo::~LineEmissionVolumeInfo()
{
    *(void **)this = (void *)0x01073744;
}

ModuleTemplate &ModuleTemplate::operator=(const ModuleTemplate &that)
{
    return *this;
}

ModuleTemplate::ModuleTemplate()
{
}

ModuleTemplate::ModuleTemplate(const ModuleTemplate &that)
{
}

ModuleTemplate::~ModuleTemplate()
{
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

__declspec(naked) DefaultAlphaModuleInfo &DefaultAlphaModuleInfo::operator=(const DefaultAlphaModuleInfo &that)
{
    __asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xc1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x04
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x04
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x14
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x14
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x24
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x24
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x34
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x34
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x44
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x44
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x54
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x54
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x8d
        __emit 0x51
        __emit 0x64
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x64
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x7a
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0x52
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0x83
        __emit 0xc1
        __emit 0x74
        __emit 0x8b
        __emit 0x31
        __emit 0x8d
        __emit 0x50
        __emit 0x74
        __emit 0x89
        __emit 0x32
        __emit 0x8b
        __emit 0x71
        __emit 0x04
        __emit 0x89
        __emit 0x72
        __emit 0x04
        __emit 0x8b
        __emit 0x71
        __emit 0x08
        __emit 0x89
        __emit 0x72
        __emit 0x08
        __emit 0x8b
        __emit 0x49
        __emit 0x0c
        __emit 0x5f
        __emit 0x89
        __emit 0x4a
        __emit 0x0c
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
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

__declspec(naked) AsciiString ParticleSystemTemplate::getName() const
{
    __asm {
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x81
        __emit 0xc1
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x34
        __emit 0x89
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString ParticleSystemTemplate::getTextureFilename() const
{
    __asm {
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x83
        __emit 0xc1
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x07
        __emit 0x89
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) void ParticleSystemTemplate::setTextureFilename(AsciiString &filename)
{
    __asm {
        __emit 0x83
        __emit 0xc1
        __emit 0x10
        __emit 0xe9
        __emit 0x38
        __emit 0xb1
        __emit 0x82
        __emit 0x00
    }
}

__declspec(naked) void ParticleSystemTemplate::setSlaveSystemName(const AsciiString &name)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x68
        __emit 0xe8
        __emit 0xf0
        __emit 0x95
        __emit 0x2c
        __emit 0x00
        __emit 0xc7
        __emit 0x86
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

ParticleType ParticleSystemTemplate::getParticleType() const
{
    return *reinterpret_cast<const ParticleType *>(reinterpret_cast<const char *>(this) + 0xc);
}

const Region2D *ParticleSystemTemplate::getUV() const
{
    return reinterpret_cast<const Region2D *>(reinterpret_cast<const char *>(this) + 0x84);
}

__declspec(naked) void ParticleSystemTemplate::setUV(const Region2D *uv)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x1c
        __emit 0x8b
        __emit 0x10
        __emit 0x81
        __emit 0xc1
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x11
        __emit 0x8b
        __emit 0x50
        __emit 0x04
        __emit 0x89
        __emit 0x51
        __emit 0x04
        __emit 0x8b
        __emit 0x50
        __emit 0x08
        __emit 0x89
        __emit 0x51
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x0c
        __emit 0x89
        __emit 0x41
        __emit 0x0c
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

void ParticleSystemTemplate::GetAssetList(AssetList &list) const
{
}

Keyframe &Keyframe::operator=(const Keyframe &that)
{
    struct Raw {
        unsigned int frame;
        unsigned int value;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

}
