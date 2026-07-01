#include "unicode_string.h"
#include "ascii_string.h"
#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *str);

AsciiString::AsciiString()
{
    m_text = 0;
}

AsciiString::AsciiString(char c)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(c);
}

AsciiString::AsciiString(const char *str)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(str);
}

AsciiString::AsciiString(const AsciiString &that)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
}

AsciiString::AsciiString(const AsciiString &that, int start, int len)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that, start, len);
}

AsciiString::AsciiString(const char *str, int len)
{
    ((StringBase<char> *)this)->StringBase<char>::StringBase(str, len);
}

AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

AsciiString &AsciiString::operator=(char c)
{
    char ch = c;
    ((StringBase<char> *)this)->set(&ch, 1);
    return *this;
}

__declspec(naked) AsciiString &AsciiString::operator=(const AsciiString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0xe8
        __emit 0x83
        __emit 0xb7
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

AsciiString &AsciiString::operator=(const char *str)
{
    ((StringBase<char> *)this)->set(str, str ? strlen(str) : 0);
    return *this;
}

__declspec(naked) AsciiString &AsciiString::operator+=(const AsciiString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x06
        __emit 0x0f
        __emit 0xb7
        __emit 0x48
        __emit 0x04
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x12
        __emit 0x51
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x2b
        __emit 0x65
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x51
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x17
        __emit 0x65
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

AsciiString &AsciiString::operator+=(char c)
{
    char ch = c;
    ((StringBase<char> *)this)->concat(&ch, 1);
    return *this;
}

AsciiString &AsciiString::operator+=(const char *str)
{
    ((StringBase<char> *)this)->concat(str, str ? strlen(str) : 0);
    return *this;
}

__declspec(naked) AsciiString operator+(AsciiString left, const char *right)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x91
        __emit 0x96
        __emit 0xff
        __emit 0x00
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x85
        __emit 0xd2
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x10
        __emit 0x8b
        __emit 0xc2
        __emit 0x8d
        __emit 0x70
        __emit 0x01
        __emit 0x8a
        __emit 0x08
        __emit 0x40
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc6
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0xe8
        __emit 0x44
        __emit 0xa7
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x18
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x34
        __emit 0xa5
        __emit 0x7b
        __emit 0x00
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0xfe
        __emit 0xa2
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

__declspec(naked) AsciiString operator+(AsciiString left, const AsciiString &right)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb1
        __emit 0x98
        __emit 0xff
        __emit 0x00
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0xc7
        __emit 0x04
        __emit 0x24
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x06
        __emit 0x0f
        __emit 0xb7
        __emit 0x48
        __emit 0x04
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc9
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
        __emit 0x56
        __emit 0x51
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0xe8
        __emit 0xaf
        __emit 0x64
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x18
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x9f
        __emit 0x62
        __emit 0x7b
        __emit 0x00
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0x69
        __emit 0x60
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

__declspec(naked) AsciiString operator+(AsciiString left, char right)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x01
        __emit 0x46
        __emit 0x05
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0x51
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xe8
        __emit 0xe1
        __emit 0xf8
        __emit 0x09
        __emit 0x00
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x18
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x1c
        __emit 0x52
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xd1
        __emit 0xf6
        __emit 0x09
        __emit 0x00
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0x9b
        __emit 0xf4
        __emit 0x09
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

__declspec(naked) AsciiString::AsciiString(const UnicodeString &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x38
        __emit 0x69
        __emit 0x05
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x06
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
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
        __emit 0x50
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x20
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x28
        __emit 0x30
        __emit 0x13
        __emit 0x01
        __emit 0xe8
        __emit 0xdf
        __emit 0xfa
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x09
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x8b
        __emit 0xc6
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator=(const UnicodeString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
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
        __emit 0x50
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x28
        __emit 0x30
        __emit 0x13
        __emit 0x01
        __emit 0xe8
        __emit 0x97
        __emit 0xfa
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0xc1
        __emit 0xfe
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator+=(const UnicodeString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
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
        __emit 0x50
        __emit 0x8b
        __emit 0x06
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
        __emit 0x50
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x2c
        __emit 0x30
        __emit 0x13
        __emit 0x01
        __emit 0xe8
        __emit 0x46
        __emit 0xfa
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x70
        __emit 0xfe
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) void __cdecl AsciiString::format(AsciiString fmt, ...)
{
    __asm {
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x18
        __emit 0x69
        __emit 0x05
        __emit 0x01
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
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
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0x51
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0xe8
        __emit 0x32
        __emit 0xf0
        __emit 0xff
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x01
        __emit 0xe9
        __emit 0xff
        __emit 0xff
        __emit 0x8b
        __emit 0x0c
        __emit 0x24
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc3
    }
}

__declspec(naked) void AsciiString::translate(const UnicodeString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
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
        __emit 0x50
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x28
        __emit 0x30
        __emit 0x13
        __emit 0x01
        __emit 0xe8
        __emit 0x47
        __emit 0xfb
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x71
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

