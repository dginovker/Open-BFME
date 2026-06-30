#pragma once

#include "../math/coord3d.h"
#include "ascii_string.h"
#include "xfer.h"

namespace FXParticleSystem {

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
    LightningEmissionInfo &operator=(const LightningEmissionInfo &that);

private:
    bool m_active;
    Coord3D m_points[11];
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
};

}
