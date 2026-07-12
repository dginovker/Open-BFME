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
struct XferReservedTag;

class Xfer {
public:
    class Version {
    public:
        unsigned char data[2];
    };

    Xfer();
    virtual ~Xfer();
    void Version1();

    // Virtual layout reproduces the binary's Xfer vtable (base ??_7Xfer@@6B@).
    // MSVC 7.1 groups the overloaded operator== into one contiguous block at the
    // first overload's slot and emits the overloads in reverse declaration order,
    // so the declaration order below is the reverse of the vtable slot order.
    virtual bool IsLoading() const;                                 // slot 1
    virtual bool IsStoring() const;                                 // slot 2
    virtual bool IsCRC() const;                                     // slot 3
    virtual bool IsLightCRC() const;                                // slot 4
    virtual void ReservedVirtual1();                                // slot 5
    virtual void ReservedVirtual2();                                // slot 6
    virtual void ReservedVirtual3();                                // slot 7
    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size); // slot 8
    virtual Xfer &XferRawBytes(void *data, unsigned int size);      // slot 9

    // operator== overload group -> vtable slots 10..35 (reverse of this order)
    virtual Xfer &operator==(bool &b);                              // slot 35
    virtual Xfer &operator==(char &c);                              // slot 34
    virtual Xfer &operator==(unsigned char &c);                     // slot 33
    virtual Xfer &operator==(short &s);                             // slot 32
    virtual Xfer &operator==(unsigned short &s);                    // slot 31
    virtual Xfer &operator==(int &i);                               // slot 30
    virtual Xfer &operator==(unsigned int &i);                      // slot 29
    virtual Xfer &operator==(__int64 &i);                           // slot 28
    virtual Xfer &operator==(float &f);                             // slot 27
    virtual Xfer &operator==(AsciiString &as);                      // slot 26
    virtual Xfer &operator==(UnicodeString &us);                    // slot 25
    virtual Xfer &operator==(Coord3DBase &v);                       // slot 24
    virtual Xfer &operator==(ICoord3D &v);                          // slot 23
    virtual Xfer &operator==(Region3D &v);                          // slot 22
    virtual Xfer &operator==(IRegion3D &v);                         // slot 21
    virtual Xfer &operator==(Coord2D &v);                           // slot 20
    virtual Xfer &operator==(ICoord2D &v);                          // slot 19
    virtual Xfer &operator==(Region2D &v);                          // slot 18
    virtual Xfer &operator==(IRegion2D &v);                         // slot 17
    virtual Xfer &operator==(RealRange &v);                         // slot 16
    virtual Xfer &operator==(RGBColor &v);                          // slot 15
    virtual Xfer &operator==(RGBAColorReal &v);                     // slot 14
    virtual Xfer &operator==(RGBAColorInt &v);                      // slot 13
    virtual Xfer &operator==(Snapshot &snapshot);                   // slot 12
    virtual Xfer &operator==(XferReservedTag &r);                   // slot 11 (reserved overload)
    virtual Xfer &operator==(Version &v);                           // slot 10

    virtual void ReservedVirtual4();                                // slot 36
    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size); // slot 37

public:
    // Stubs so Xfer-using .cpp files compile; the xfer() methods that call these
    // won't byte-match (they'd need the real slot mapping — see game-file-recipe),
    // but a file's NON-xfer functions (e.g. geometry math) place fine.
    void xferVersion(unsigned char*, unsigned char);
    void xferInt(int*p){*this==*p;}
    void xferReal(float*p){*this==*p;}
    void xferUser(void*, int);
    void xferAsciiString(AsciiString*p){*this==*p;}
    void xferUnsignedInt(unsigned int*p){*this==*p;}
    void xferByte(char*p){*this==*p;}
    void xferBool(bool*p){*this==*p;}
    void xferCoord3D(void*) {}
};
