#pragma once

class AsciiString;
class UnicodeString;
class Snapshot;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;

class Xfer {
public:
    class Version {
    public:
        unsigned char data[2];
    };

    Xfer();
    virtual ~Xfer();
    void Version1();

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

    virtual Xfer &operator==(Coord3DBase &v);
    virtual Xfer &operator==(ICoord3D &v);
    virtual Xfer &operator==(Region3D &v);
    virtual Xfer &operator==(IRegion3D &v);
    virtual Xfer &operator==(Coord2D &v);
    virtual Xfer &operator==(ICoord2D &v);
    virtual Xfer &operator==(Region2D &v);
    virtual Xfer &operator==(IRegion2D &v);
    virtual Xfer &operator==(RealRange &v);
    virtual Xfer &operator==(RGBColor &v);
    virtual Xfer &operator==(RGBAColorReal &v);
    virtual Xfer &operator==(RGBAColorInt &v);

    virtual Xfer &operator==(AsciiString &as);
    virtual Xfer &operator==(UnicodeString &us);
    virtual Xfer &operator==(Version &v);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
};
