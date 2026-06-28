#pragma once

namespace FXParticleSystem {

class ButterflyDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class DefaultAlphaModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class DefaultColorModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class DefaultDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class DefaultPhysicsModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class DefaultUpdateModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class EmissionVelocityInfo {
public:
    virtual const char *GetSnapshotName();
};

class EmissionVolumeInfo {
public:
    virtual const char *GetSnapshotName();
};

class LifeEventModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class LightningDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class ParticleSystemInfo {
public:
    virtual const char *GetSnapshotName();
};

class QuadDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class RenderObjectDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class RenderObjectUpdateModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class StreakDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class TerrainCollisionModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class WindModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

}
