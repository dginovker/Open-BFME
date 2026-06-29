#pragma once

#include "xfer.h"

namespace FXParticleSystem {

class ButterflyDrawModuleInfo {
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
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
    virtual ~EmissionVelocityInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
};

class EmissionVolumeInfo {
public:
    EmissionVolumeInfo();
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

}
