#pragma once

class Xfer;

class Snapshot {
public:
#ifdef SNAPSHOT_CPP
    Snapshot();
    Snapshot(const Snapshot &that);
    virtual ~Snapshot();
    Snapshot &operator=(const Snapshot &that);
#else
    Snapshot() {}
    Snapshot(const Snapshot &that) {}
    virtual ~Snapshot() {}
    Snapshot &operator=(const Snapshot &that) { return *this; }
#endif

    virtual const char *GetSnapshotName() = 0;
    virtual void LoadPostProcess() = 0;
    virtual void DoXfer(Xfer &xfer) = 0;
};
