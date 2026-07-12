// cl: /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Include/Common
#include "xfer.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "snapshot.h"
#include "coord3d.h"
#include "coord2d.h"
#include "icoord.h"
#include "region.h"
#include "color.h"

Xfer::Xfer()
{
}

Xfer::~Xfer()
{
}

bool Xfer::IsLoading() const
{
    return false;
}

bool Xfer::IsStoring() const
{
    return false;
}

bool Xfer::IsCRC() const
{
    return false;
}

bool Xfer::IsLightCRC() const
{
    return false;
}

void Xfer::SkipBadBlock(Snapshot &snapshot, unsigned int size)
{
}

Xfer &Xfer::operator==(char &c)
{
    XferEnum((const char *)0x62797465, &c, 1);
    return *this;
}

Xfer &Xfer::operator==(unsigned char &c)
{
    XferEnum((const char *)0x75627974, &c, 1);
    return *this;
}

Xfer &Xfer::operator==(short &s)
{
    XferEnum((const char *)0x73687274, &s, 2);
    return *this;
}

Xfer &Xfer::operator==(unsigned short &s)
{
    XferEnum((const char *)0x75736874, &s, 2);
    return *this;
}

Xfer &Xfer::operator==(int &i)
{
    XferEnum((const char *)0x696e74, &i, 4);
    return *this;
}

Xfer &Xfer::operator==(unsigned int &i)
{
    XferEnum((const char *)0x75696e74, &i, 4);
    return *this;
}

Xfer &Xfer::operator==(float &f)
{
    XferEnum((const char *)0x7265616c, &f, 4);
    return *this;
}

Xfer &Xfer::operator==(__int64 &i)
{
    XferEnum((const char *)0x693634, &i, 8);
    return *this;
}

Xfer &Xfer::operator==(bool &b)
{
    XferEnum((const char *)0x626f6f6c, &b, 1);
    return *this;
}

Xfer &Xfer::operator==(Snapshot &snapshot)
{
    snapshot.DoXfer(*this);
    return *this;
}

Xfer &Xfer::operator==(Coord3DBase& v)
{
    XferEnum((const char *)0x00633364, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(ICoord3D& v)
{
    XferEnum((const char *)0x69633364, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(Region3D& v)
{
    XferEnum((const char *)0x00723364, 0, 0);
    XferEnum(0, &v.x_min, 12);
    XferEnum(0, &v.x_max, 12);
    return *this;
}

Xfer &Xfer::operator==(IRegion3D& v)
{
    XferEnum((const char *)0x69723364, 0, 0);
    XferEnum(0, &v.x_min, 12);
    XferEnum(0, &v.x_max, 12);
    return *this;
}

Xfer &Xfer::operator==(Coord2D& v)
{
    XferEnum((const char *)0x00633264, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(ICoord2D& v)
{
    XferEnum((const char *)0x69633264, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(Region2D& v)
{
    XferEnum((const char *)0x00723264, 0, 0);
    XferEnum(0, &v.x_min, 8);
    XferEnum(0, &v.x_max, 8);
    return *this;
}

Xfer &Xfer::operator==(IRegion2D& v)
{
    XferEnum((const char *)0x69723264, 0, 0);
    XferEnum(0, &v.x_min, 8);
    XferEnum(0, &v.x_max, 8);
    return *this;
}

Xfer &Xfer::operator==(RealRange& v)
{
    XferEnum((const char *)0x726e6765, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(RGBColor& v)
{
    XferEnum((const char *)0x00726762, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(RGBAColorReal& v)
{
    XferEnum((const char *)0x72676272, 0, 0);
    XferEnum(0, &v, 16);
    return *this;
}

Xfer &Xfer::operator==(RGBAColorInt& v)
{
    XferEnum((const char *)0x72676269, 0, 0);
    XferEnum(0, &v, 16);
    return *this;
}

void Xfer::Version1()
{
    Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    *this == v;
}

__declspec(naked) Xfer &Xfer::operator==(AsciiString &as)
{
    __asm {
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0xff
        __emit 0x50
        __emit 0x08
        __emit 0x84
        __emit 0xc0
        __emit 0x0f
        __emit 0x84
        __emit 0x87
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x07
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x35
        __emit 0x0f
        __emit 0xb7
        __emit 0x40
        __emit 0x04
        __emit 0x3d
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x7c
        __emit 0x2e
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x61
        __emit 0x8b
        __emit 0xce
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xff
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0xeb
        __emit 0x14
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x61
        __emit 0x8b
        __emit 0x16
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x07
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x16
        __emit 0x51
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x61
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x3d
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x75
        __emit 0x17
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x38
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x53
        __emit 0x8b
        __emit 0x1e
        __emit 0x50
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xb3
        __emit 0x11
        __emit 0xeb
        __emit 0xff
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x93
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x9c
        __emit 0x11
        __emit 0xeb
        __emit 0xff
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x5b
        __emit 0xc6
        __emit 0x04
        __emit 0x10
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0xe2
        __emit 0x0e
        __emit 0xeb
        __emit 0xff
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) Xfer &Xfer::operator==(UnicodeString &us)
{
    __asm {
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0xff
        __emit 0x50
        __emit 0x08
        __emit 0x84
        __emit 0xc0
        __emit 0x0f
        __emit 0x84
        __emit 0x89
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x07
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x35
        __emit 0x0f
        __emit 0xb7
        __emit 0x40
        __emit 0x04
        __emit 0x3d
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x7c
        __emit 0x2e
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x75
        __emit 0x8b
        __emit 0xce
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xff
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0xeb
        __emit 0x14
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x75
        __emit 0x8b
        __emit 0x16
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x07
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8c
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x16
        __emit 0x03
        __emit 0xc9
        __emit 0x51
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x74
        __emit 0x73
        __emit 0x75
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x3d
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x75
        __emit 0x17
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x3d
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x53
        __emit 0x8b
        __emit 0x1e
        __emit 0x8d
        __emit 0x0c
        __emit 0x00
        __emit 0x51
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x1e
        __emit 0x19
        __emit 0xeb
        __emit 0xff
        __emit 0x50
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x93
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x52
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x07
        __emit 0x19
        __emit 0xeb
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5b
        __emit 0x66
        __emit 0xc7
        __emit 0x04
        __emit 0x48
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0x3b
        __emit 0x16
        __emit 0xeb
        __emit 0xff
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) Xfer &Xfer::operator==(Version &v)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x53
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x8b
        __emit 0x07
        __emit 0xff
        __emit 0x50
        __emit 0x08
        __emit 0x84
        __emit 0xc0
        __emit 0x8b
        __emit 0x17
        __emit 0x8b
        __emit 0xcf
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x6a
        __emit 0x01
        __emit 0x40
        __emit 0x50
        __emit 0x68
        __emit 0x72
        __emit 0x65
        __emit 0x76
        __emit 0x00
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc7
        __emit 0x5f
        __emit 0x5b
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x55
        __emit 0x8b
        __emit 0x6c
        __emit 0x24
        __emit 0x18
        __emit 0x8a
        __emit 0x5d
        __emit 0x01
        __emit 0x56
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x75
        __emit 0x01
        __emit 0x56
        __emit 0x68
        __emit 0x72
        __emit 0x65
        __emit 0x76
        __emit 0x00
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x06
        __emit 0x8a
        __emit 0x4d
        __emit 0x00
        __emit 0x3a
        __emit 0xc1
        __emit 0x5e
        __emit 0x5d
        __emit 0x73
        __emit 0x2b
        __emit 0x0f
        __emit 0xb6
        __emit 0xc9
        __emit 0x51
        __emit 0x0f
        __emit 0xb6
        __emit 0xd0
        __emit 0x52
        __emit 0x68
        __emit 0x5c
        __emit 0x40
        __emit 0x14
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x6a
        __emit 0x02
        __emit 0x50
        __emit 0xe8
        __emit 0x81
        __emit 0xfd
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0x68
        __emit 0x5c
        __emit 0xfe
        __emit 0x1d
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0xe8
        __emit 0x4f
        __emit 0x08
        __emit 0x02
        __emit 0x00
        __emit 0x3a
        __emit 0xc3
        __emit 0x76
        __emit 0xa2
        __emit 0x0f
        __emit 0xb6
        __emit 0xd3
        __emit 0x52
        __emit 0x0f
        __emit 0xb6
        __emit 0xc0
        __emit 0x50
        __emit 0x68
        __emit 0x24
        __emit 0x40
        __emit 0x14
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x6a
        __emit 0x03
        __emit 0x51
        __emit 0xe8
        __emit 0x52
        __emit 0xfd
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0x68
        __emit 0x5c
        __emit 0xfe
        __emit 0x1d
        __emit 0x01
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0x52
        __emit 0xe8
        __emit 0x20
        __emit 0x08
        __emit 0x02
        __emit 0x00
    }
}

__declspec(naked) Xfer &Xfer::XferRawBytes(void *data, unsigned int size)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x04
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x28
        __emit 0x8b
        __emit 0x06
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x51
        __emit 0x68
        __emit 0x77
        __emit 0x61
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x90
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x16
        __emit 0x50
        __emit 0x57
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

__declspec(naked) Xfer &Xfer::XferEnum(const char *name, void *data, unsigned int size)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x0f
        __emit 0x84
        __emit 0x92
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xf8
        __emit 0x04
        __emit 0x0f
        __emit 0x87
        __emit 0x89
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x48
        __emit 0x83
        __emit 0xf8
        __emit 0x03
        __emit 0x77
        __emit 0x7a
        __emit 0xff
        __emit 0x24
        __emit 0x85
        __emit 0x74
        __emit 0x68
        __emit 0xdd
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0x06
        __emit 0x6a
        __emit 0x01
        __emit 0x51
        __emit 0x68
        __emit 0x31
        __emit 0x75
        __emit 0x6e
        __emit 0x65
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x90
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x02
        __emit 0x50
        __emit 0x68
        __emit 0x32
        __emit 0x75
        __emit 0x6e
        __emit 0x65
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x03
        __emit 0x50
        __emit 0x68
        __emit 0x33
        __emit 0x75
        __emit 0x6e
        __emit 0x65
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0x16
        __emit 0x6a
        __emit 0x04
        __emit 0x50
        __emit 0x68
        __emit 0x34
        __emit 0x75
        __emit 0x6e
        __emit 0x65
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x0c
        __emit 0x00
        __emit 0x6a
        __emit 0x00
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x6a
        __emit 0x04
        __emit 0x51
        __emit 0xe8
        __emit 0xbe
        __emit 0xf9
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x68
        __emit 0x5c
        __emit 0xfe
        __emit 0x1d
        __emit 0x01
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0xe8
        __emit 0x8c
        __emit 0x04
        __emit 0x02
        __emit 0x00
    }
}
