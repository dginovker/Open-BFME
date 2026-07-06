#pragma once

#include "ascii_string.h"
#include "game_client_random_variable.h"
#include "xfer.h"
#include "../math/color.h"
#include "snapshot.h"

struct Region2D;
class AssetList;
class INI {
public:
    void initFromINI(void *data, const void *parseTable);
    static void parseFXList(INI *ini, void *data, void *store, const void *userData);
};
class File;
class FXList;
template <class T>
class TrackingPtr {
    T *m_ptr;
};

namespace FXParticleSystem {

class ParticleSystem;

struct RandomAlphaKeyframe {
    RandomAlphaKeyframe()
    {
        var.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
        frame = 0.0f;
    }

    GameClientRandomVariable var;
    float frame;

    RandomAlphaKeyframe &operator=(const RandomAlphaKeyframe &that);
};

enum ParticleType {
    PARTICLE_TYPE_DEFAULT,
};

enum ModuleCategory {
    MODULE_CATEGORY_DRAW = 0,
    MODULE_CATEGORY_UPDATE = 1,
    MODULE_CATEGORY_EMISSION = 2,
    MODULE_CATEGORY_VELOCITY = 3,
    MODULE_CATEGORY_VOLUME = 4,
    MODULE_CATEGORY_LIFE_EVENT = 5,
    MODULE_CATEGORY_COLLISION = 6,
    MODULE_CATEGORY_WIND = 7,
};

const char *GetKey(ModuleCategory category);
const char *GetName(ModuleCategory category);
void staticInitModules();

// Forward declarations for int-based module templates
template <int Category> class DefaultModule;
template <int Category> class DefaultModuleTemplate;
template <int Category> class DefaultParticleModule;
template <int Category> class DefaultParticleModuleTemplate;
template <int Category> class CategoryModuleTemplate;

// Forward declarations for module classes used by ModuleTag
class BoxEmissionVolumeModule;
class ButterflyDrawModule;
class CylinderEmissionVolumeModule;
class CylindricalEmissionVelocityModule;
class HemisphericalEmissionVelocityModule;
class LifeEventModule;
class LightningDrawModule;
class LightningEmissionModule;
class LineEmissionVolumeModule;
class OrthoEmissionVelocityModule;
class OutwardEmissionVelocityModule;
class PointEmissionVolumeModule;
class QuadDrawModule;
class RenderObjectDrawModule;
class RenderObjectUpdateModule;
class SphereEmissionVolumeModule;
class SphericalEmissionVelocityModule;
class StreakDrawModule;
class TerrainCollisionModule;

class BoxEmissionVolumeModuleTemplate;
class ButterflyDrawModuleTemplate;
class CylinderEmissionVolumeModuleTemplate;
class CylindricalEmissionVelocityModuleTemplate;
class HemisphericalEmissionVelocityModuleTemplate;
class LifeEventModuleTemplate;
class LightningDrawModuleTemplate;
class LightningEmissionModuleTemplate;
class LineEmissionVolumeModuleTemplate;
class OrthoEmissionVelocityModuleTemplate;
class OutwardEmissionVelocityModuleTemplate;
class PointEmissionVolumeModuleTemplate;
class QuadDrawModuleTemplate;
class RenderObjectDrawModuleTemplate;
class RenderObjectUpdateModuleTemplate;
class SphereEmissionVolumeModuleTemplate;
class SphericalEmissionVelocityModuleTemplate;
class StreakDrawModuleTemplate;
class TerrainCollisionModuleTemplate;

class ParticleLifeEventModule;
class ParticleTerrainCollisionModule;
class RenderObjectParticleUpdateModule;

class ParticleLifeEventModuleTemplate;
class ParticleTerrainCollisionModuleTemplate;
class RenderObjectParticleUpdateModuleTemplate;

template <int Category>
struct DefaultModuleKey {
    static const char VALUE[1];
    DefaultModuleKey &operator=(const DefaultModuleKey &that) { return *this; }
private:
    static const char *GetValue();
};

template <int Category>
struct DefaultModuleName {
    static const char VALUE[1];
    DefaultModuleName &operator=(const DefaultModuleName &that) { return *this; }
private:
    static const char *GetValue();
};

template <int N>
class DefaultModuleTag {
public:
    DefaultModuleTag &operator=(const DefaultModuleTag &that) { return *this; }
};

// Namespace-level key/name strings for specific ModuleTag instantiations
extern const char BOX_EMISSION_VOLUME_MODULE_KEY[1];
extern const char BUTTERFLY_DRAW_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIGHTNING_DRAW_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LINE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char ORTHO_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char POINT_EMISSION_VOLUME_MODULE_KEY[1];
extern const char QUAD_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_UPDATE_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char STREAK_DRAW_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_KEY[1];

extern const char BOX_EMISSION_VOLUME_MODULE_NAME[1];
extern const char BUTTERFLY_DRAW_MODULE_NAME[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char LIFE_EVENT_MODULE_NAME[1];
extern const char LIGHTNING_DRAW_MODULE_NAME[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];
extern const char LINE_EMISSION_VOLUME_MODULE_NAME[1];
extern const char ORTHO_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char POINT_EMISSION_VOLUME_MODULE_NAME[1];
extern const char QUAD_DRAW_MODULE_NAME[1];
extern const char RENDEROBJECT_DRAW_MODULE_NAME[1];
extern const char RENDEROBJECT_UPDATE_MODULE_NAME[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char STREAK_DRAW_MODULE_NAME[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class DefaultParticleModule, class DefaultParticleModuleTemplate>
class ModuleTag {
public:
    ModuleTag &operator=(const ModuleTag &that) { return *this; }
};

class ButterflyDrawModuleInfo : public Snapshot {
public:
    ButterflyDrawModuleInfo();
    __declspec(nothrow) ButterflyDrawModuleInfo(const ButterflyDrawModuleInfo &that);
    virtual ~ButterflyDrawModuleInfo() {}
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    ButterflyDrawModuleInfo &operator=(const ButterflyDrawModuleInfo &that);
};


class DefaultAlphaModuleInfo {
public:
    DefaultAlphaModuleInfo();
    virtual ~DefaultAlphaModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    DefaultAlphaModuleInfo &operator=(const DefaultAlphaModuleInfo &that);

    RandomAlphaKeyframe m_alphaKey[8];
};

class DefaultColorModuleInfo {
public:
    DefaultColorModuleInfo();
    virtual ~DefaultColorModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    DefaultColorModuleInfo &operator=(const DefaultColorModuleInfo &that);
    void tintAllColors(int tint);

    RGBColorKeyframe m_colorKey[8];
    GameClientRandomVariable m_colorScale;
};

class DefaultDrawModuleInfo {
public:
    DefaultDrawModuleInfo();
    DefaultDrawModuleInfo(const DefaultDrawModuleInfo &that);
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    DefaultDrawModuleInfo &operator=(const DefaultDrawModuleInfo &that);
};

class DefaultPhysicsModuleInfo {
public:
    DefaultPhysicsModuleInfo();
    DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that);
    virtual ~DefaultPhysicsModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    DefaultPhysicsModuleInfo &operator=(const DefaultPhysicsModuleInfo &that);

    float m_field0;
    float m_field1;
    float m_field2;
    int m_field3;
    GameClientRandomVariable m_var1;
};

class DefaultUpdateModuleInfo {
public:
    DefaultUpdateModuleInfo();
    DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &that);
    virtual ~DefaultUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    DefaultUpdateModuleInfo &operator=(const DefaultUpdateModuleInfo &that);

    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
    GameClientRandomVariable m_var3;
    GameClientRandomVariable m_var4;
    int m_extra;
};

class EmissionVelocityInfo {
public:
    EmissionVelocityInfo() {}
    __declspec(nothrow) EmissionVelocityInfo(const EmissionVelocityInfo &that);
    virtual ~EmissionVelocityInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    EmissionVelocityInfo &operator=(const EmissionVelocityInfo &that);
};

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo {
public:
    CylindricalEmissionVelocityInfo();
    __declspec(nothrow) CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that);
    virtual ~CylindricalEmissionVelocityInfo();
    CylindricalEmissionVelocityInfo &operator=(const CylindricalEmissionVelocityInfo &that);
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
};

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo {
public:
    OrthoEmissionVelocityInfo();
    __declspec(nothrow) OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &that);
    virtual ~OrthoEmissionVelocityInfo();
    OrthoEmissionVelocityInfo &operator=(const OrthoEmissionVelocityInfo &that);
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
};

class OutwardEmissionVelocityInfo : public EmissionVelocityInfo {
public:
    OutwardEmissionVelocityInfo();
    __declspec(nothrow) OutwardEmissionVelocityInfo(const OutwardEmissionVelocityInfo &that);
    virtual ~OutwardEmissionVelocityInfo();
    OutwardEmissionVelocityInfo &operator=(const OutwardEmissionVelocityInfo &that);
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
};

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo {
public:
    SphericalEmissionVelocityInfo();
    __declspec(nothrow) SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &that);
    virtual ~SphericalEmissionVelocityInfo();
    SphericalEmissionVelocityInfo &operator=(const SphericalEmissionVelocityInfo &that);
    GameClientRandomVariable m_var0;
};

class EventModuleInfo {
public:
    EventModuleInfo();
    EventModuleInfo &operator=(const EventModuleInfo &that);

protected:
    ~EventModuleInfo();

private:
    bool m_unk0;
    bool m_unk1;
};

class EmissionVolumeInfo : public Snapshot {
public:
#ifdef FX_PARTICLE_SYSTEM_CPP
    EmissionVolumeInfo();
#else
    EmissionVolumeInfo() : m_flag(false) {}
#endif
    __declspec(nothrow) EmissionVolumeInfo(const EmissionVolumeInfo &that);
    virtual ~EmissionVolumeInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    EmissionVolumeInfo &operator=(const EmissionVolumeInfo &that);

    bool m_flag;
};

class LightningEmissionInfo : public EmissionVolumeInfo {
public:
    LightningEmissionInfo();
    LightningEmissionInfo(const LightningEmissionInfo &that);
    virtual ~LightningEmissionInfo();
    LightningEmissionInfo &operator=(const LightningEmissionInfo &that);

    struct Point3D { float x, y, z; };
    Point3D m_points[11];
};

class BoxEmissionVolumeInfo : public EmissionVolumeInfo {
public:
#ifdef FX_PARTICLE_SYSTEM_CPP
    BoxEmissionVolumeInfo();
#else
    BoxEmissionVolumeInfo() : EmissionVolumeInfo() {
        m_unk[0] = 0.0f;
        m_unk[1] = 0.0f;
        m_unk[2] = 0.0f;
    }
#endif
    BoxEmissionVolumeInfo(const BoxEmissionVolumeInfo &that);
    virtual ~BoxEmissionVolumeInfo();
    BoxEmissionVolumeInfo &operator=(const BoxEmissionVolumeInfo &that);

private:
    float m_unk[3];
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo {
public:
#ifdef FX_PARTICLE_SYSTEM_CPP
    SphereEmissionVolumeInfo();
#else
    SphereEmissionVolumeInfo() : EmissionVolumeInfo(), m_radius(0.0f) {}
#endif
    __declspec(nothrow) SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that);
    virtual ~SphereEmissionVolumeInfo();
    SphereEmissionVolumeInfo &operator=(const SphereEmissionVolumeInfo &that);

private:
    float m_radius;
};

class CylinderEmissionVolumeInfo : public EmissionVolumeInfo {
public:
#ifdef FX_PARTICLE_SYSTEM_CPP
    CylinderEmissionVolumeInfo();
#else
    CylinderEmissionVolumeInfo() : EmissionVolumeInfo() {
        m_unk[0] = 0.0f;
        m_unk[1] = 0.0f;
        m_unk[2] = 0.0f;
        m_unk[3] = 0.0f;
        m_unk[4] = 0.0f;
    }
#endif
    CylinderEmissionVolumeInfo(const CylinderEmissionVolumeInfo &that);
    virtual ~CylinderEmissionVolumeInfo();
    CylinderEmissionVolumeInfo &operator=(const CylinderEmissionVolumeInfo &that);

private:
    float m_unk[5];
};

class LineEmissionVolumeInfo : public EmissionVolumeInfo {
public:
#ifdef FX_PARTICLE_SYSTEM_CPP
    LineEmissionVolumeInfo();
#else
    LineEmissionVolumeInfo() : EmissionVolumeInfo() {
        m_unk[0] = 0.0f;
        m_unk[1] = 0.0f;
        m_unk[2] = 0.0f;
        m_unk[3] = 0.0f;
        m_unk[4] = 0.0f;
        m_unk[5] = 0.0f;
    }
#endif
    LineEmissionVolumeInfo(const LineEmissionVolumeInfo &that);
    LineEmissionVolumeInfo &operator=(const LineEmissionVolumeInfo &that);
    virtual ~LineEmissionVolumeInfo();

private:
    float m_unk[6];
};

class LifeEventModuleInfo {
public:
    LifeEventModuleInfo();
    LifeEventModuleInfo(const LifeEventModuleInfo &that);
    virtual ~LifeEventModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    LifeEventModuleInfo &operator=(const LifeEventModuleInfo &that);
    const FXList *getEventFX();
};

class LightningDrawModuleInfo {
public:
    LightningDrawModuleInfo();
    LightningDrawModuleInfo(const LightningDrawModuleInfo &that);
    virtual ~LightningDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    LightningDrawModuleInfo &operator=(const LightningDrawModuleInfo &that);
    GameClientRandomVariable m_gcrv1;
    GameClientRandomVariable m_gcrv2;
    GameClientRandomVariable m_gcrv3;
    int m_field28;
    bool m_flag;
};

class ParticleSystemInfo {
public:
    ParticleSystemInfo();
    ParticleSystemInfo(const ParticleSystemInfo &that);
    virtual ~ParticleSystemInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    ParticleSystemInfo &operator=(const ParticleSystemInfo &that);
};

class QuadDrawModuleInfo : public Snapshot {
public:
    QuadDrawModuleInfo();
    __declspec(nothrow) QuadDrawModuleInfo(const QuadDrawModuleInfo &that);
    virtual ~QuadDrawModuleInfo() {}
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    QuadDrawModuleInfo &operator=(const QuadDrawModuleInfo &that);
};


class RenderObjectDrawModuleInfo {
public:
    RenderObjectDrawModuleInfo();
    RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &that);
    virtual ~RenderObjectDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    RenderObjectDrawModuleInfo &operator=(const RenderObjectDrawModuleInfo &that);
};

class RenderObjectUpdateModuleInfo {
public:
    RenderObjectUpdateModuleInfo();
    RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that);
    virtual ~RenderObjectUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    RenderObjectUpdateModuleInfo &operator=(const RenderObjectUpdateModuleInfo &that);
};

class StreakDrawModuleInfo {
public:
    StreakDrawModuleInfo();
    StreakDrawModuleInfo(const StreakDrawModuleInfo &that);
    virtual ~StreakDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    StreakDrawModuleInfo &operator=(const StreakDrawModuleInfo &that);
};

struct OrthoEmissionVelocityModuleTag {
    OrthoEmissionVelocityModuleTag &operator=(const OrthoEmissionVelocityModuleTag &that);
};

struct PointEmissionVolumeModuleTag {
    PointEmissionVolumeModuleTag &operator=(const PointEmissionVolumeModuleTag &that);
};

class TerrainCollisionModuleInfo {
public:
    TerrainCollisionModuleInfo();
    TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &that);
    virtual ~TerrainCollisionModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    TerrainCollisionModuleInfo &operator=(const TerrainCollisionModuleInfo &that);
    const FXList *getEventFX();
};

class WindModuleInfo {
public:
    WindModuleInfo();
    WindModuleInfo(const WindModuleInfo &that);
    virtual ~WindModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    WindModuleInfo &operator=(const WindModuleInfo &that);
    int m_type;
    float m_f0, m_f1, m_f2, m_f3, m_f4, m_f5, m_f6, m_f7, m_f8, m_f9, m_f10, m_f11, m_f12;
    bool m_flag;
    int m_i0, m_i1;
};

class ModuleTemplate {
public:
    ModuleTemplate() {}
    ModuleTemplate(const ModuleTemplate &that) {}
    virtual ~ModuleTemplate() {}
    ModuleTemplate &operator=(const ModuleTemplate &that);
};

// CategoryModuleInfo<N> - base for CategoryModuleTemplateBase, split across header/cpp
template <int Category>
class CategoryModuleInfo {
public:
    CategoryModuleInfo() {}
    CategoryModuleInfo(const CategoryModuleInfo<Category> &that);
    virtual void unusedVirtual();
    CategoryModuleInfo<Category> &operator=(const CategoryModuleInfo<Category> &that) { return *this; }

protected:
    ~CategoryModuleInfo() { }
};

// CategoryModuleTemplateBase<N>
template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<Category> {
public:
    CategoryModuleTemplateBase() {}
    CategoryModuleTemplateBase(const CategoryModuleTemplateBase<Category> &that);
    virtual ~CategoryModuleTemplateBase() {}
    CategoryModuleTemplateBase<Category> &operator=(const CategoryModuleTemplateBase<Category> &that) { return *this; }
};

// CategoryModuleTemplate<N>
template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category> {
public:
    CategoryModuleTemplate() {}
    __declspec(nothrow) CategoryModuleTemplate(const CategoryModuleTemplate<Category> &that);
    virtual ~CategoryModuleTemplate() {}
    CategoryModuleTemplate<Category> &operator=(const CategoryModuleTemplate<Category> &that) { return *this; }
};

class BoxEmissionVolumeModuleTemplate : public CategoryModuleTemplate<5>, public BoxEmissionVolumeInfo {
public:
    BoxEmissionVolumeModuleTemplate();
    BoxEmissionVolumeModuleTemplate(const BoxEmissionVolumeModuleTemplate &that);
    virtual ~BoxEmissionVolumeModuleTemplate();
    BoxEmissionVolumeModuleTemplate &operator=(const BoxEmissionVolumeModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class CylinderEmissionVolumeModuleTemplate : public CategoryModuleTemplate<5>, public CylinderEmissionVolumeInfo {
public:
    CylinderEmissionVolumeModuleTemplate();
    CylinderEmissionVolumeModuleTemplate(const CylinderEmissionVolumeModuleTemplate &that);
    virtual ~CylinderEmissionVolumeModuleTemplate();
    CylinderEmissionVolumeModuleTemplate &operator=(const CylinderEmissionVolumeModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class CylindricalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>, public CylindricalEmissionVelocityInfo {
public:
    CylindricalEmissionVelocityModuleTemplate();
    CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &that);
    virtual ~CylindricalEmissionVelocityModuleTemplate();
    CylindricalEmissionVelocityModuleTemplate &operator=(const CylindricalEmissionVelocityModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>, public SphericalEmissionVelocityInfo {
public:
    SphericalEmissionVelocityModuleTemplate();
    SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that);
    virtual ~SphericalEmissionVelocityModuleTemplate();
    SphericalEmissionVelocityModuleTemplate &operator=(const SphericalEmissionVelocityModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class HemisphericalEmissionVelocityModuleTemplate : public SphericalEmissionVelocityModuleTemplate {
public:
    HemisphericalEmissionVelocityModuleTemplate();
    HemisphericalEmissionVelocityModuleTemplate(const HemisphericalEmissionVelocityModuleTemplate &that);
    virtual ~HemisphericalEmissionVelocityModuleTemplate();
    HemisphericalEmissionVelocityModuleTemplate &operator=(const HemisphericalEmissionVelocityModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class LifeEventModuleTemplate {
public:
    LifeEventModuleTemplate();
    LifeEventModuleTemplate(const LifeEventModuleTemplate &that);
    virtual ~LifeEventModuleTemplate();
    LifeEventModuleTemplate &operator=(const LifeEventModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
    static void parseEventFXListName(INI *ini, void *data, void *store, const void *userData);
};

class LightningDrawModuleTemplate : public CategoryModuleTemplate<6>, public LightningDrawModuleInfo {
public:
    LightningDrawModuleTemplate();
    LightningDrawModuleTemplate(const LightningDrawModuleTemplate &that);
    virtual ~LightningDrawModuleTemplate();
    LightningDrawModuleTemplate &operator=(const LightningDrawModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class LightningEmissionModuleTemplate : public CategoryModuleTemplate<5>, public LightningEmissionInfo {
public:
    LightningEmissionModuleTemplate();
    __declspec(nothrow) LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that);
    virtual ~LightningEmissionModuleTemplate();
    LightningEmissionModuleTemplate &operator=(const LightningEmissionModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class LineEmissionVolumeModuleTemplate : public CategoryModuleTemplate<5>, public LineEmissionVolumeInfo {
public:
    LineEmissionVolumeModuleTemplate();
    LineEmissionVolumeModuleTemplate(const LineEmissionVolumeModuleTemplate &that);
    virtual ~LineEmissionVolumeModuleTemplate();
    LineEmissionVolumeModuleTemplate &operator=(const LineEmissionVolumeModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class OrthoEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>, public OrthoEmissionVelocityInfo {
public:
    OrthoEmissionVelocityModuleTemplate();
    OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &that);
    virtual ~OrthoEmissionVelocityModuleTemplate();
    OrthoEmissionVelocityModuleTemplate &operator=(const OrthoEmissionVelocityModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class OutwardEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>, public OutwardEmissionVelocityInfo {
public:
    OutwardEmissionVelocityModuleTemplate();
    OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &that);
    virtual ~OutwardEmissionVelocityModuleTemplate();
    OutwardEmissionVelocityModuleTemplate &operator=(const OutwardEmissionVelocityModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class PointEmissionVolumeModuleTemplate : public CategoryModuleTemplate<5>, public EmissionVolumeInfo {
public:
    PointEmissionVolumeModuleTemplate();
    PointEmissionVolumeModuleTemplate(const PointEmissionVolumeModuleTemplate &that);
    virtual ~PointEmissionVolumeModuleTemplate();
    PointEmissionVolumeModuleTemplate &operator=(const PointEmissionVolumeModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class RenderObjectDrawModuleTemplate {
public:
    RenderObjectDrawModuleTemplate();
    RenderObjectDrawModuleTemplate(const RenderObjectDrawModuleTemplate &that);
    virtual ~RenderObjectDrawModuleTemplate();
    RenderObjectDrawModuleTemplate &operator=(const RenderObjectDrawModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class RenderObjectUpdateModuleTemplate {
public:
    RenderObjectUpdateModuleTemplate();
    RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &that);
    virtual ~RenderObjectUpdateModuleTemplate();
    RenderObjectUpdateModuleTemplate &operator=(const RenderObjectUpdateModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class SphereEmissionVolumeModuleTemplate : public CategoryModuleTemplate<5>, public SphereEmissionVolumeInfo {
public:
    SphereEmissionVolumeModuleTemplate();
    SphereEmissionVolumeModuleTemplate(const SphereEmissionVolumeModuleTemplate &that);
    virtual ~SphereEmissionVolumeModuleTemplate();
    SphereEmissionVolumeModuleTemplate &operator=(const SphereEmissionVolumeModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class StreakDrawModuleTemplate : public CategoryModuleTemplate<6>, public StreakDrawModuleInfo {
public:
    StreakDrawModuleTemplate();
    __declspec(nothrow) StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that);
    virtual ~StreakDrawModuleTemplate();
    StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class TerrainCollisionModuleTemplate {
public:
    TerrainCollisionModuleTemplate();
    TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that);
    virtual ~TerrainCollisionModuleTemplate();
    TerrainCollisionModuleTemplate &operator=(const TerrainCollisionModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
    static void parseEventFXListName(INI *ini, void *data, void *store, const void *userData);
};

struct Keyframe {
    Keyframe();

    float frame;
    float value;

    Keyframe &operator=(const Keyframe &that);
};

class ParticleSystemTemplate {
public:
    ParticleSystemTemplate();
    ParticleSystemTemplate(const AsciiString &name);
    ParticleSystemTemplate(const ParticleSystemTemplate &that);
    virtual ~ParticleSystemTemplate();
    ParticleSystemTemplate &operator=(const ParticleSystemTemplate &that);
    AsciiString getName() const;
    AsciiString getTextureFilename() const;
    void setTextureFilename(AsciiString &filename);
    void setSlaveSystemName(const AsciiString &name);
    ParticleType getParticleType() const;
    const Region2D *getUV() const;
    void setUV(const Region2D *uv);
    void GetAssetList(AssetList &list) const;
    static void parse(INI *ini, void *data, void *store, const void *userData);
    void writeINI(File &file, unsigned int flags) const;
    TrackingPtr<ParticleSystem> createSlaveSystem(bool) const;
};

// Template class for DefaultModuleTemplate<N>
template <int N>
class DefaultModuleTemplate {
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate<N> &that);
    virtual ~DefaultModuleTemplate();
    DefaultModuleTemplate<N> &operator=(const DefaultModuleTemplate<N> &that) { return *this; }
    void parse(INI *ini);
    static void parseRGBColorKeyframe(INI *ini, void *data, void *store, const void *userData);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class ButterflyDrawModuleTemplate : public CategoryModuleTemplate<6>, public ButterflyDrawModuleInfo {
public:
    ButterflyDrawModuleTemplate();
    ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &that);
    virtual ~ButterflyDrawModuleTemplate();
    ButterflyDrawModuleTemplate &operator=(const ButterflyDrawModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

class QuadDrawModuleTemplate : public CategoryModuleTemplate<6>, public QuadDrawModuleInfo {
public:
    QuadDrawModuleTemplate();
    QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that);
    virtual ~QuadDrawModuleTemplate();
    QuadDrawModuleTemplate &operator=(const QuadDrawModuleTemplate &that);
    void parse(INI *ini);
    virtual void writeINI(File &file, unsigned int flags) const;
};

template <typename Tag> class ConcreteModuleClass;
template <typename Tag> class ConcreteModuleTemplate;

// Explicit specializations - MSVC 7.1 does not support partial specializations,
// so each tag type gets its own full template<> specialization.

#ifndef FXPS_V
#define FXPS_V
#endif

template <>
class ConcreteModuleClass<DefaultModuleTag<0> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<0> > &getInstance();
    FXPS_V DefaultModuleTemplate<0> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<0> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<0> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<0> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<0> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<0> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<0> > &getClass() const;    FXPS_V DefaultModuleTemplate<0> *clone() const;    FXPS_V DefaultModule<0> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<DefaultModuleTag<1> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<1> > &getInstance();
    FXPS_V DefaultModuleTemplate<1> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<1> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<1> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<1> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<1> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<1> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<1> > &getClass() const;    FXPS_V DefaultModuleTemplate<1> *clone() const;    FXPS_V DefaultModule<1> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<DefaultModuleTag<2> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<2> > &getInstance();
    FXPS_V DefaultModuleTemplate<2> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<2> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<2> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<2> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<2> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<2> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<2> > &getClass() const;    FXPS_V DefaultModuleTemplate<2> *clone() const;    FXPS_V DefaultModule<2> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<DefaultModuleTag<3> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<3> > &getInstance();
    FXPS_V DefaultModuleTemplate<3> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<3> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<3> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<3> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<3> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<3> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<3> > &getClass() const;    FXPS_V DefaultModuleTemplate<3> *clone() const;    FXPS_V DefaultModule<3> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<DefaultModuleTag<6> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<6> > &getInstance();
    FXPS_V DefaultModuleTemplate<6> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<6> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<6> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<6> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<6> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<6> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<6> > &getClass() const;    FXPS_V DefaultModuleTemplate<6> *clone() const;    FXPS_V DefaultModule<6> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<DefaultModuleTag<7> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<DefaultModuleTag<7> > &getInstance();
    FXPS_V DefaultModuleTemplate<7> *createTemplate(INI *ini) const;    FXPS_V DefaultModuleTemplate<7> *createTemplate() const;};

template <>
class ConcreteModuleTemplate<DefaultModuleTag<7> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<7> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<DefaultModuleTag<7> > &operator=(const ConcreteModuleTemplate<DefaultModuleTag<7> > &that);
    FXPS_V const ConcreteModuleClass<DefaultModuleTag<7> > &getClass() const;    FXPS_V DefaultModuleTemplate<7> *clone() const;    FXPS_V DefaultModule<7> *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<OrthoEmissionVelocityModuleTag> {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<OrthoEmissionVelocityModuleTag> &getInstance();
    FXPS_V OrthoEmissionVelocityModuleTemplate *createTemplate(INI *ini) const;    FXPS_V OrthoEmissionVelocityModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &operator=(const ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &that);
    FXPS_V const ConcreteModuleClass<OrthoEmissionVelocityModuleTag> &getClass() const;    FXPS_V OrthoEmissionVelocityModuleTemplate *clone() const;    FXPS_V OrthoEmissionVelocityModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<PointEmissionVolumeModuleTag> {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<PointEmissionVolumeModuleTag> &getInstance();
    FXPS_V PointEmissionVolumeModuleTemplate *createTemplate(INI *ini) const;    FXPS_V PointEmissionVolumeModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<PointEmissionVolumeModuleTag> {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &operator=(const ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &that);
    FXPS_V const ConcreteModuleClass<PointEmissionVolumeModuleTag> &getClass() const;    FXPS_V PointEmissionVolumeModuleTemplate *clone() const;    FXPS_V PointEmissionVolumeModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getInstance();
    FXPS_V BoxEmissionVolumeModuleTemplate *createTemplate(INI *ini) const;    FXPS_V BoxEmissionVolumeModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &operator=(const ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getClass() const;    FXPS_V BoxEmissionVolumeModuleTemplate *clone() const;    FXPS_V BoxEmissionVolumeModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getInstance();
    FXPS_V ButterflyDrawModuleTemplate *createTemplate(INI *ini) const;    FXPS_V ButterflyDrawModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &operator=(const ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getClass() const;    FXPS_V ButterflyDrawModuleTemplate *clone() const;    FXPS_V ButterflyDrawModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getInstance();
    FXPS_V CylinderEmissionVolumeModuleTemplate *createTemplate(INI *ini) const;    FXPS_V CylinderEmissionVolumeModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &operator=(const ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getClass() const;    FXPS_V CylinderEmissionVolumeModuleTemplate *clone() const;    FXPS_V CylinderEmissionVolumeModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getInstance();
    FXPS_V CylindricalEmissionVelocityModuleTemplate *createTemplate(INI *ini) const;    FXPS_V CylindricalEmissionVelocityModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &operator=(const ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getClass() const;    FXPS_V CylindricalEmissionVelocityModuleTemplate *clone() const;    FXPS_V CylindricalEmissionVelocityModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getInstance();
    FXPS_V HemisphericalEmissionVelocityModuleTemplate *createTemplate(INI *ini) const;    FXPS_V HemisphericalEmissionVelocityModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &operator=(const ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getClass() const;    FXPS_V HemisphericalEmissionVelocityModuleTemplate *clone() const;    FXPS_V HemisphericalEmissionVelocityModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &getInstance();
    FXPS_V LifeEventModuleTemplate *createTemplate(INI *ini) const;    FXPS_V LifeEventModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &operator=(const ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &getClass() const;    FXPS_V LifeEventModuleTemplate *clone() const;    FXPS_V LifeEventModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getInstance();
    FXPS_V LightningDrawModuleTemplate *createTemplate(INI *ini) const;    FXPS_V LightningDrawModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &operator=(const ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getClass() const;    FXPS_V LightningDrawModuleTemplate *clone() const;    FXPS_V LightningDrawModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getInstance();
    FXPS_V LightningEmissionModuleTemplate *createTemplate(INI *ini) const;    FXPS_V LightningEmissionModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &operator=(const ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getClass() const;    FXPS_V LightningEmissionModuleTemplate *clone() const;    FXPS_V LightningEmissionModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getInstance();
    FXPS_V LineEmissionVolumeModuleTemplate *createTemplate(INI *ini) const;    FXPS_V LineEmissionVolumeModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &operator=(const ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getClass() const;    FXPS_V LineEmissionVolumeModuleTemplate *clone() const;    FXPS_V LineEmissionVolumeModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getInstance();
    FXPS_V OutwardEmissionVelocityModuleTemplate *createTemplate(INI *ini) const;    FXPS_V OutwardEmissionVelocityModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &operator=(const ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getClass() const;    FXPS_V OutwardEmissionVelocityModuleTemplate *clone() const;    FXPS_V OutwardEmissionVelocityModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getInstance();
    FXPS_V QuadDrawModuleTemplate *createTemplate(INI *ini) const;    FXPS_V QuadDrawModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &operator=(const ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getClass() const;    FXPS_V QuadDrawModuleTemplate *clone() const;    FXPS_V QuadDrawModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getInstance();
    FXPS_V RenderObjectDrawModuleTemplate *createTemplate(INI *ini) const;    FXPS_V RenderObjectDrawModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &operator=(const ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getClass() const;    FXPS_V RenderObjectDrawModuleTemplate *clone() const;    FXPS_V RenderObjectDrawModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &getInstance();
    FXPS_V RenderObjectUpdateModuleTemplate *createTemplate(INI *ini) const;    FXPS_V RenderObjectUpdateModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &operator=(const ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &getClass() const;    FXPS_V RenderObjectUpdateModuleTemplate *clone() const;    FXPS_V RenderObjectUpdateModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getInstance();
    FXPS_V SphereEmissionVolumeModuleTemplate *createTemplate(INI *ini) const;    FXPS_V SphereEmissionVolumeModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &operator=(const ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &getClass() const;    FXPS_V SphereEmissionVolumeModuleTemplate *clone() const;    FXPS_V SphereEmissionVolumeModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getInstance();
    FXPS_V SphericalEmissionVelocityModuleTemplate *createTemplate(INI *ini) const;    FXPS_V SphericalEmissionVelocityModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &operator=(const ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &getClass() const;    FXPS_V SphericalEmissionVelocityModuleTemplate *clone() const;    FXPS_V SphericalEmissionVelocityModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getInstance();
    FXPS_V StreakDrawModuleTemplate *createTemplate(INI *ini) const;    FXPS_V StreakDrawModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &operator=(const ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &getClass() const;    FXPS_V StreakDrawModuleTemplate *clone() const;    FXPS_V StreakDrawModule *createModule(TrackingPtr<ParticleSystem> &sys);};

template <>
class ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > {
private:
    ConcreteModuleClass();
public:
    ~ConcreteModuleClass();
    static const ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &getInstance();
    FXPS_V TerrainCollisionModuleTemplate *createTemplate(INI *ini) const;    FXPS_V TerrainCollisionModuleTemplate *createTemplate() const;};

template <>
class ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > {
public:
    ConcreteModuleTemplate();
    ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &that);
    FXPS_V ~ConcreteModuleTemplate();    ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &operator=(const ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &that);
    FXPS_V const ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &getClass() const;    FXPS_V TerrainCollisionModuleTemplate *clone() const;    FXPS_V TerrainCollisionModule *createModule(TrackingPtr<ParticleSystem> &sys);};
} // namespace FXParticleSystem
