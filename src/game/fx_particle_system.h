#pragma once

#include "ascii_string.h"
#include "game_client_random_variable.h"
#include "xfer.h"

struct Region2D;
class AssetList;

namespace FXParticleSystem {

struct RandomAlphaKeyframe {
    RandomAlphaKeyframe();

    GameClientRandomVariable var;
    float frame;
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

// Forward declarations for int-based module templates
template <int Category> class DefaultModule;
template <int Category> class DefaultModuleTemplate;
template <int Category> class DefaultParticleModule;
template <int Category> class DefaultParticleModuleTemplate;

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
};

template <int Category>
struct DefaultModuleName {
    static const char VALUE[1];
    DefaultModuleName &operator=(const DefaultModuleName &that) { return *this; }
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

class ButterflyDrawModuleInfo {
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    ButterflyDrawModuleInfo &operator=(const ButterflyDrawModuleInfo &that);
};

class ButterflyDrawModuleTemplate {
public:
    ButterflyDrawModuleTemplate &operator=(const ButterflyDrawModuleTemplate &that);
};

class DefaultAlphaModuleInfo {
public:
    virtual ~DefaultAlphaModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    DefaultAlphaModuleInfo &operator=(const DefaultAlphaModuleInfo &that);
};

class DefaultColorModuleInfo {
public:
    virtual ~DefaultColorModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class DefaultDrawModuleInfo {
public:
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    DefaultDrawModuleInfo &operator=(const DefaultDrawModuleInfo &that);
};

class DefaultPhysicsModuleInfo {
public:
    virtual ~DefaultPhysicsModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class DefaultUpdateModuleInfo {
public:
    virtual ~DefaultUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class EmissionVelocityInfo {
public:
    EmissionVelocityInfo();
    EmissionVelocityInfo(const EmissionVelocityInfo &that);
    virtual ~EmissionVelocityInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    EmissionVelocityInfo &operator=(const EmissionVelocityInfo &that);
};

class LightningEmissionInfo : public EmissionVelocityInfo {
public:
    virtual ~LightningEmissionInfo();
    LightningEmissionInfo &operator=(const LightningEmissionInfo &that);

private:
    bool m_active;
    struct { float x, y, z; } m_points[11];
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

class EmissionVolumeInfo {
public:
    EmissionVolumeInfo();
    EmissionVolumeInfo(const EmissionVolumeInfo &that);
    virtual ~EmissionVolumeInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);

    bool m_flag;
};

class BoxEmissionVolumeInfo : public EmissionVolumeInfo {
public:
    virtual ~BoxEmissionVolumeInfo();
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo {
public:
    virtual ~SphereEmissionVolumeInfo();
};

class CylinderEmissionVolumeInfo : public EmissionVolumeInfo {
public:
    virtual ~CylinderEmissionVolumeInfo();
};

class LineEmissionVolumeInfo : public EmissionVolumeInfo {
public:
    virtual ~LineEmissionVolumeInfo();
};

class LifeEventModuleInfo {
public:
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class LightningDrawModuleInfo {
public:
    virtual ~LightningDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class ParticleSystemInfo {
public:
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class QuadDrawModuleInfo {
public:
    QuadDrawModuleInfo();
    virtual ~QuadDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    QuadDrawModuleInfo &operator=(const QuadDrawModuleInfo &that);
};

class QuadDrawModuleTemplate {
public:
    QuadDrawModuleTemplate &operator=(const QuadDrawModuleTemplate &that);
};

class RenderObjectDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class RenderObjectUpdateModuleInfo {
public:
    virtual ~RenderObjectUpdateModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class StreakDrawModuleInfo {
public:
    StreakDrawModuleInfo(const StreakDrawModuleInfo &that);
    virtual ~StreakDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    StreakDrawModuleInfo &operator=(const StreakDrawModuleInfo &that);
};

class StreakDrawModuleTemplate {
public:
    StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &that);
};

struct OrthoEmissionVelocityModuleTag {
    OrthoEmissionVelocityModuleTag &operator=(const OrthoEmissionVelocityModuleTag &that);
};

struct PointEmissionVolumeModuleTag {
    PointEmissionVolumeModuleTag &operator=(const PointEmissionVolumeModuleTag &that);
};

class TerrainCollisionModuleInfo {
public:
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class WindModuleInfo {
public:
    virtual ~WindModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
};

class ModuleTemplate {
public:
    ModuleTemplate();
    ModuleTemplate(const ModuleTemplate &that);
    virtual ~ModuleTemplate();
    ModuleTemplate &operator=(const ModuleTemplate &that);
};

struct Keyframe {
    float frame;
    float value;

    Keyframe &operator=(const Keyframe &that);
};

class ParticleSystemTemplate {
public:
    AsciiString getName() const;
    AsciiString getTextureFilename() const;
    void setTextureFilename(AsciiString &filename);
    void setSlaveSystemName(const AsciiString &name);
    ParticleType getParticleType() const;
    const Region2D *getUV() const;
    void setUV(const Region2D *uv);
    void GetAssetList(AssetList &list) const;
};

}
