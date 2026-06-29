#pragma once

class Snapshot;

class Xfer {
public:
    Xfer();
    virtual ~Xfer();

    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);

    virtual Xfer &operator==(char &c);
    virtual Xfer &operator==(unsigned char &c);
    virtual Xfer &operator==(short &s);
    virtual Xfer &operator==(unsigned short &s);
    virtual Xfer &operator==(int &i);
    virtual Xfer &operator==(unsigned int &i);
    virtual Xfer &operator==(float &f);
    virtual Xfer &operator==(__int64 &i);
    virtual Xfer &operator==(bool &b);
    virtual Xfer &operator==(Snapshot &snapshot);
};
