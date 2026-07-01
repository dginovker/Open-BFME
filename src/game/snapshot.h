#pragma once

class Xfer;

class Snapshot {
public:
    Snapshot();
    Snapshot(const Snapshot &that);
    virtual ~Snapshot();
    Snapshot &operator=(const Snapshot &that);

    virtual const char *GetSnapshotName() = 0;
    virtual void LoadPostProcess() = 0;
    virtual void DoXfer(Xfer &xfer) = 0;
};
