#pragma once

#include "xfer.h"

namespace FXParticleSystem {

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
    ModuleTemplate &operator=(const ModuleTemplate &that);
};

}
