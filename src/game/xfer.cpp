#include "xfer.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "snapshot.h"
#include "../math/coord3d.h"
#include "../math/coord2d.h"
#include "../math/icoord.h"
#include "../math/region.h"
#include "../math/color.h"

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

__declspec(naked) Xfer &Xfer::operator==(char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x62797465
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned char &c)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x75627974
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x73687274
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned short &s)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 2
        push ecx
        push 0x75736874
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(unsigned int &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x75696e74
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(float &f)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 4
        push ecx
        push 0x7265616c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(__int64 &i)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 8
        push ecx
        push 0x693634
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(bool &b)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [esi]
        push 1
        push ecx
        push 0x626f6f6c
        mov ecx, esi
        call dword ptr [eax + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(Snapshot &snapshot)
{
    __asm {
        push esi
        mov esi, ecx
        mov ecx, [esp + 8]
        mov eax, [ecx]
        push esi
        call dword ptr [eax + 0x0c]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) Xfer &Xfer::operator==(Coord3DBase& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00633364
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(ICoord3D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69633364
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Region3D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00723364
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 12
        add edi, 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(IRegion3D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69723364
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 12
        add edi, 12
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Coord2D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00633264
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(ICoord2D& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69633264
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(Region2D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00723264
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 8
        add edi, 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(IRegion2D& v)
{
    __asm {
        push esi
        push edi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x69723264
        call dword ptr [eax + 0x94]
        mov edi, [esp + 0xc]
        mov edx, [esi]
        push 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, [esi]
        push 8
        add edi, 8
        push edi
        push 0
        mov ecx, esi
        call dword ptr [eax + 0x94]
        pop edi
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RealRange& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x726e6765
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 8
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBColor& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x00726762
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 12
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBAColorReal& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x72676272
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 16
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}
__declspec(naked) Xfer &Xfer::operator==(RGBAColorInt& v)
{
    __asm {
        push esi
        push 0
        mov esi, ecx
        mov eax, [esi]
        push 0
        push 0x72676269
        call dword ptr [eax + 0x94]
        mov eax, [esp + 0x8]
        mov edx, [esi]
        push 16
        push eax
        push 0
        mov ecx, esi
        call dword ptr [edx + 0x94]
        mov eax, esi
        pop esi
        ret 4
    }
}

__declspec(naked) void Xfer::Version1()
{
    __asm {
        __emit 0x51
        __emit 0xb0
        __emit 0x01
        __emit 0x8d
        __emit 0x14
        __emit 0x24
        __emit 0x88
        __emit 0x04
        __emit 0x24
        __emit 0x88
        __emit 0x44
        __emit 0x24
        __emit 0x01
        __emit 0x8b
        __emit 0x01
        __emit 0x52
        __emit 0xff
        __emit 0x50
        __emit 0x28
        __emit 0x59
        __emit 0xc3
    }
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
