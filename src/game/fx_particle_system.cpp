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

__declspec(naked) const char *GetName(ModuleCategory category)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x04
        __emit 0xc5
        __emit 0x00
        __emit 0x05
        __emit 0x11
        __emit 0x01
        __emit 0xc3
    }
}

__declspec(naked) void staticInitModules()
{
    __asm {
        __emit 0xe8
        __emit 0xeb
        __emit 0xcf
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x16
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xd1
        __emit 0xe6
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0x3c
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x67
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x92
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xbd
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x28
        __emit 0xe7
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0x93
        __emit 0xe7
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0xfe
        __emit 0xe7
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0x69
        __emit 0xe8
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0xd4
        __emit 0xe8
        __emit 0xfe
        __emit 0xff
        __emit 0xe8
        __emit 0xcf
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xfa
        __emit 0xd0
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x25
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x50
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x7b
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xa6
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xd1
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xfc
        __emit 0xd1
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x27
        __emit 0xd2
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x52
        __emit 0xd2
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x7d
        __emit 0xd2
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xa8
        __emit 0xd2
        __emit 0xff
        __emit 0xff
        __emit 0xe9
        __emit 0xd3
        __emit 0xd2
        __emit 0xff
        __emit 0xff
    }
}

ButterflyDrawModuleInfo::ButterflyDrawModuleInfo()
{
}

ButterflyDrawModuleInfo::ButterflyDrawModuleInfo(const ButterflyDrawModuleInfo &that)
{
}

DefaultDrawModuleInfo::DefaultDrawModuleInfo()
{
}

DefaultDrawModuleInfo::DefaultDrawModuleInfo(const DefaultDrawModuleInfo &that)
{
}

QuadDrawModuleInfo::QuadDrawModuleInfo(const QuadDrawModuleInfo &that)
{
}

StreakDrawModuleInfo::StreakDrawModuleInfo()
{
}

__declspec(naked) Keyframe::Keyframe()
{
    __asm {
        __emit 0x8b
        __emit 0xc1
        __emit 0xc7
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc3
    }
}

SphereEmissionVolumeInfo::SphereEmissionVolumeInfo()
{
    m_flag = false;
    *(void **)this = (void *)0x01110A0C;
    m_radius = 0.0f;
}

BoxEmissionVolumeInfo::BoxEmissionVolumeInfo()
{
    m_flag = false;
    *(void **)this = (void *)0x011109CC;
    m_unk[0] = 0.0f;
    m_unk[1] = 0.0f;
    m_unk[2] = 0.0f;
}

CylinderEmissionVolumeInfo::CylinderEmissionVolumeInfo()
{
    m_flag = false;
    *(void **)this = (void *)0x01110A4C;
    m_unk[0] = 0.0f;
    m_unk[1] = 0.0f;
    m_unk[2] = 0.0f;
    m_unk[3] = 0.0f;
    m_unk[4] = 0.0f;
}

LineEmissionVolumeInfo::LineEmissionVolumeInfo()
{
    m_flag = false;
    *(void **)this = (void *)0x0111098C;
    m_unk[0] = 0.0f;
    m_unk[1] = 0.0f;
    m_unk[2] = 0.0f;
    m_unk[3] = 0.0f;
    m_unk[4] = 0.0f;
    m_unk[5] = 0.0f;
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
void CategoryModuleInfo<Category>::unusedVirtual()
{
}

template <int Category>
CategoryModuleInfo<Category>::CategoryModuleInfo()
{
}

template <int Category>
CategoryModuleInfo<Category>::CategoryModuleInfo(const CategoryModuleInfo<Category> &that)
{
}

template <int Category>
CategoryModuleTemplateBase<Category>::CategoryModuleTemplateBase()
{
}

template <int Category>
__declspec(noinline) CategoryModuleTemplateBase<Category>::CategoryModuleTemplateBase(const CategoryModuleTemplateBase<Category> &that)
{
}

template <int Category>
CategoryModuleTemplateBase<Category>::~CategoryModuleTemplateBase()
{
}

template <int Category>
CategoryModuleTemplate<Category>::CategoryModuleTemplate()
{
}

template <int Category>
CategoryModuleTemplate<Category>::CategoryModuleTemplate(const CategoryModuleTemplate<Category> &that)
    : CategoryModuleTemplateBase<Category>(that)
{
}

template <int Category>
CategoryModuleTemplate<Category>::~CategoryModuleTemplate()
{
}

template CategoryModuleClassBase<0, 1> &CategoryModuleClassBase<0, 1>::operator=(const CategoryModuleClassBase<0, 1> &);
template CategoryModuleClassBase<1, 1> &CategoryModuleClassBase<1, 1>::operator=(const CategoryModuleClassBase<1, 1> &);
template CategoryModuleClassBase<2, 1> &CategoryModuleClassBase<2, 1>::operator=(const CategoryModuleClassBase<2, 1> &);
template CategoryModuleClassBase<3, 1> &CategoryModuleClassBase<3, 1>::operator=(const CategoryModuleClassBase<3, 1> &);
template CategoryModuleClassBase<4, 1> &CategoryModuleClassBase<4, 1>::operator=(const CategoryModuleClassBase<4, 1> &);
template CategoryModuleClassBase<5, 1> &CategoryModuleClassBase<5, 1>::operator=(const CategoryModuleClassBase<5, 1> &);
template CategoryModuleClassBase<6, 1> &CategoryModuleClassBase<6, 1>::operator=(const CategoryModuleClassBase<6, 1> &);
template CategoryModuleClassBase<7, 1> &CategoryModuleClassBase<7, 1>::operator=(const CategoryModuleClassBase<7, 1> &);
template CategoryModuleClassBase<8, 0> &CategoryModuleClassBase<8, 0>::operator=(const CategoryModuleClassBase<8, 0> &);

template class CategoryModuleInfo<0>;
template class CategoryModuleInfo<1>;
template class CategoryModuleInfo<2>;
template class CategoryModuleInfo<3>;
template class CategoryModuleInfo<4>;
template class CategoryModuleInfo<5>;
template class CategoryModuleInfo<6>;
template class CategoryModuleInfo<7>;
template class CategoryModuleInfo<8>;
template class CategoryModuleTemplateBase<0>;
template class CategoryModuleTemplateBase<1>;
template class CategoryModuleTemplateBase<2>;
template class CategoryModuleTemplateBase<3>;
template class CategoryModuleTemplateBase<4>;
template class CategoryModuleTemplateBase<5>;
template class CategoryModuleTemplateBase<6>;
template class CategoryModuleTemplateBase<7>;
template class CategoryModuleTemplateBase<8>;
template class CategoryModuleTemplate<0>;
template class CategoryModuleTemplate<1>;
template class CategoryModuleTemplate<2>;
template class CategoryModuleTemplate<3>;
template class CategoryModuleTemplate<4>;
template class CategoryModuleTemplate<5>;
template class CategoryModuleTemplate<6>;
template class CategoryModuleTemplate<7>;
template class CategoryModuleTemplate<8>;
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

StreakDrawModuleInfo::StreakDrawModuleInfo(const StreakDrawModuleInfo &that)
{
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

__declspec(naked) LineEmissionVolumeInfo &LineEmissionVolumeInfo::operator=(const LineEmissionVolumeInfo &that)
{
    __asm {
        mov eax, ecx
        mov ecx, [esp + 4]
        mov dl, [ecx + 4]
        mov [eax + 4], dl
        push esi
        lea edx, [ecx + 8]
        push edi
        mov edi, [edx]
        lea esi, [eax + 8]
        mov [esi], edi
        mov edi, [edx + 4]
        mov [esi + 4], edi
        mov edx, [edx + 8]
        mov [esi + 8], edx
        add ecx, 0x14
        mov esi, [ecx]
        lea edx, [eax + 0x14]
        mov [edx], esi
        mov esi, [ecx + 4]
        mov [edx + 4], esi
        mov ecx, [ecx + 8]
        pop edi
        mov [edx + 8], ecx
        pop esi
        ret 4
    }
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

RandomAlphaKeyframe::RandomAlphaKeyframe()
{
    var.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    frame = 0;
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

CylindricalEmissionVelocityInfo::~CylindricalEmissionVelocityInfo()
{
}

OrthoEmissionVelocityInfo::~OrthoEmissionVelocityInfo()
{
}

OutwardEmissionVelocityInfo::~OutwardEmissionVelocityInfo()
{
}

SphericalEmissionVelocityInfo::~SphericalEmissionVelocityInfo()
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

template <int Category>
class DefaultModule {
public:
    DefaultModule &operator=(const DefaultModule &that) { return *this; }
};

template <int Category>
class DefaultParticleModule {
public:
    DefaultParticleModule &operator=(const DefaultParticleModule &that) { return *this; }
};

template <int Category>
class DefaultParticleModuleTemplate {
public:
    DefaultParticleModuleTemplate &operator=(const DefaultParticleModuleTemplate &that) { return *this; }
};

// Key/name strings for specific ModuleTag instantiations
const char BOX_EMISSION_VOLUME_MODULE_KEY[1] = "";
const char BUTTERFLY_DRAW_MODULE_KEY[1] = "";
const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1] = "";
const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY[1] = "";
const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1] = "";
const char LIFE_EVENT_MODULE_KEY[1] = "";
const char LIGHTNING_DRAW_MODULE_KEY[1] = "";
const char LIGHTNING_EMISSION_MODULE_KEY[1] = "";
const char LINE_EMISSION_VOLUME_MODULE_KEY[1] = "";
const char ORTHO_EMISSION_VELOCITY_MODULE_KEY[1] = "";
const char OUTWARD_EMISSION_VELOCITY_MODULE_KEY[1] = "";
const char POINT_EMISSION_VOLUME_MODULE_KEY[1] = "";
const char QUAD_DRAW_MODULE_KEY[1] = "";
const char RENDEROBJECT_DRAW_MODULE_KEY[1] = "";
const char RENDEROBJECT_UPDATE_MODULE_KEY[1] = "";
const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1] = "";
const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1] = "";
const char STREAK_DRAW_MODULE_KEY[1] = "";
const char TERRAIN_COLLISION_MODULE_KEY[1] = "";
const char BOX_EMISSION_VOLUME_MODULE_NAME[1] = "";
const char BUTTERFLY_DRAW_MODULE_NAME[1] = "";
const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1] = "";
const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME[1] = "";
const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1] = "";
const char LIFE_EVENT_MODULE_NAME[1] = "";
const char LIGHTNING_DRAW_MODULE_NAME[1] = "";
const char LIGHTNING_EMISSION_MODULE_NAME[1] = "";
const char LINE_EMISSION_VOLUME_MODULE_NAME[1] = "";
const char ORTHO_EMISSION_VELOCITY_MODULE_NAME[1] = "";
const char OUTWARD_EMISSION_VELOCITY_MODULE_NAME[1] = "";
const char POINT_EMISSION_VOLUME_MODULE_NAME[1] = "";
const char QUAD_DRAW_MODULE_NAME[1] = "";
const char RENDEROBJECT_DRAW_MODULE_NAME[1] = "";
const char RENDEROBJECT_UPDATE_MODULE_NAME[1] = "";
const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1] = "";
const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1] = "";
const char STREAK_DRAW_MODULE_NAME[1] = "";
const char TERRAIN_COLLISION_MODULE_NAME[1] = "";

// Typedefs to avoid nested angle brackets in explicit instantiations for MSVC 7.1
typedef DefaultModule<0> DefaultModule_0;
typedef DefaultModuleTemplate<0> DefaultModuleTemplate_0;
typedef DefaultModuleKey<0> DefaultModuleKey_0;
typedef DefaultModuleName<0> DefaultModuleName_0;
typedef DefaultModule<1> DefaultModule_1;
typedef DefaultModuleTemplate<1> DefaultModuleTemplate_1;
typedef DefaultModuleKey<1> DefaultModuleKey_1;
typedef DefaultModuleName<1> DefaultModuleName_1;
typedef DefaultModule<2> DefaultModule_2;
typedef DefaultModuleTemplate<2> DefaultModuleTemplate_2;
typedef DefaultModuleKey<2> DefaultModuleKey_2;
typedef DefaultModuleName<2> DefaultModuleName_2;
typedef DefaultModule<3> DefaultModule_3;
typedef DefaultModuleTemplate<3> DefaultModuleTemplate_3;
typedef DefaultModuleKey<3> DefaultModuleKey_3;
typedef DefaultModuleName<3> DefaultModuleName_3;
typedef DefaultModule<6> DefaultModule_6;
typedef DefaultModuleTemplate<6> DefaultModuleTemplate_6;
typedef DefaultModuleKey<6> DefaultModuleKey_6;
typedef DefaultModuleName<6> DefaultModuleName_6;
typedef DefaultModule<7> DefaultModule_7;
typedef DefaultModuleTemplate<7> DefaultModuleTemplate_7;
typedef DefaultModuleKey<7> DefaultModuleKey_7;
typedef DefaultModuleName<7> DefaultModuleName_7;
typedef DefaultParticleModule<0> DefaultParticleModule_0;
typedef DefaultParticleModuleTemplate<0> DefaultParticleModuleTemplate_0;
typedef DefaultParticleModule<1> DefaultParticleModule_1;
typedef DefaultParticleModuleTemplate<1> DefaultParticleModuleTemplate_1;
typedef DefaultParticleModule<2> DefaultParticleModule_2;
typedef DefaultParticleModuleTemplate<2> DefaultParticleModuleTemplate_2;
typedef DefaultParticleModule<3> DefaultParticleModule_3;
typedef DefaultParticleModuleTemplate<3> DefaultParticleModuleTemplate_3;
typedef DefaultParticleModule<4> DefaultParticleModule_4;
typedef DefaultParticleModuleTemplate<4> DefaultParticleModuleTemplate_4;
typedef DefaultParticleModule<5> DefaultParticleModule_5;
typedef DefaultParticleModuleTemplate<5> DefaultParticleModuleTemplate_5;
typedef DefaultParticleModule<6> DefaultParticleModule_6;
typedef DefaultParticleModuleTemplate<6> DefaultParticleModuleTemplate_6;
typedef DefaultParticleModule<7> DefaultParticleModule_7;
typedef DefaultParticleModuleTemplate<7> DefaultParticleModuleTemplate_7;
typedef DefaultParticleModule<8> DefaultParticleModule_8;
typedef DefaultParticleModuleTemplate<8> DefaultParticleModuleTemplate_8;

// Default key/name values for ModuleTag instantiations
template<> const char DefaultModuleKey<0>::VALUE[1] = "";
template<> const char DefaultModuleKey<1>::VALUE[1] = "";
template<> const char DefaultModuleKey<2>::VALUE[1] = "";
template<> const char DefaultModuleKey<3>::VALUE[1] = "";
template<> const char DefaultModuleKey<6>::VALUE[1] = "";
template<> const char DefaultModuleKey<7>::VALUE[1] = "";
template<> const char DefaultModuleName<0>::VALUE[1] = "";
template<> const char DefaultModuleName<1>::VALUE[1] = "";
template<> const char DefaultModuleName<2>::VALUE[1] = "";
template<> const char DefaultModuleName<3>::VALUE[1] = "";
template<> const char DefaultModuleName<6>::VALUE[1] = "";
template<> const char DefaultModuleName<7>::VALUE[1] = "";

// Explicit ModuleTag instantiations
template class ModuleTag<1, DefaultModuleKey_1::VALUE, DefaultModuleName_1::VALUE, DefaultModule_1, DefaultModuleTemplate_1, DefaultParticleModule_1, DefaultParticleModuleTemplate_1>;
template class ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate>;
template class ModuleTag<2, DefaultModuleKey_2::VALUE, DefaultModuleName_2::VALUE, DefaultModule_2, DefaultModuleTemplate_2, DefaultParticleModule_2, DefaultParticleModuleTemplate_2>;
template class ModuleTag<3, DefaultModuleKey_3::VALUE, DefaultModuleName_3::VALUE, DefaultModule_3, DefaultModuleTemplate_3, DefaultParticleModule_3, DefaultParticleModuleTemplate_3>;
template class ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule_4, DefaultParticleModuleTemplate_4>;
template class ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule_4, DefaultParticleModuleTemplate_4>;
template class ModuleTag<4, ORTHO_EMISSION_VELOCITY_MODULE_KEY, ORTHO_EMISSION_VELOCITY_MODULE_NAME, OrthoEmissionVelocityModule, OrthoEmissionVelocityModuleTemplate, DefaultParticleModule_4, DefaultParticleModuleTemplate_4>;
template class ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule_4, DefaultParticleModuleTemplate_4>;
template class ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule_4, DefaultParticleModuleTemplate_4>;
template class ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<5, POINT_EMISSION_VOLUME_MODULE_KEY, POINT_EMISSION_VOLUME_MODULE_NAME, PointEmissionVolumeModule, PointEmissionVolumeModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule_5, DefaultParticleModuleTemplate_5>;
template class ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<6, DefaultModuleKey_6::VALUE, DefaultModuleName_6::VALUE, DefaultModule_6, DefaultModuleTemplate_6, DefaultParticleModule_6, DefaultParticleModuleTemplate_6>;
template class ModuleTag<7, DefaultModuleKey_7::VALUE, DefaultModuleName_7::VALUE, DefaultModule_7, DefaultModuleTemplate_7, DefaultParticleModule_7, DefaultParticleModuleTemplate_7>;
template class ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate>;
template class ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate>;
template class ModuleTag<0, DefaultModuleKey_0::VALUE, DefaultModuleName_0::VALUE, DefaultModule_0, DefaultModuleTemplate_0, DefaultParticleModule_0, DefaultParticleModuleTemplate_0>;

}
