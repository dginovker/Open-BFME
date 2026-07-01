#include "ascii_string.h"
#include "unicode_string.h"
#include "string_base.h"

UnicodeString::UnicodeString()
{
    m_text = 0;
}

UnicodeString::UnicodeString(wchar_t c)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(c);
}

UnicodeString::UnicodeString(const wchar_t *str)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str);
}

UnicodeString::UnicodeString(const wchar_t *str, int len)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str, len);
}

UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t> *)&that);
}

UnicodeString::UnicodeString(const UnicodeString &that, int start, int len)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t> *)&that, start, len);
}

__declspec(naked) UnicodeString &UnicodeString::operator=(wchar_t c)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0xd7
        __emit 0x35
        __emit 0x32
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) UnicodeString &UnicodeString::operator=(const wchar_t *str)
{
    __asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xff
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x1a
        __emit 0x57
        __emit 0xff
        __emit 0x15
        __emit 0x24
        __emit 0x95
        __emit 0x35
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x50
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x81
        __emit 0x48
        __emit 0x80
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6f
        __emit 0x48
        __emit 0x80
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) UnicodeString &UnicodeString::operator+=(wchar_t c)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0x67
        __emit 0xb9
        __emit 0x44
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) UnicodeString &UnicodeString::operator+=(const wchar_t *str)
{
    __asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xff
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x1a
        __emit 0x57
        __emit 0xff
        __emit 0x15
        __emit 0x24
        __emit 0x95
        __emit 0x35
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x50
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xc1
        __emit 0xe5
        __emit 0x3e
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x57
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xaf
        __emit 0xe5
        __emit 0x3e
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) UnicodeString &UnicodeString::operator+=(const UnicodeString &that)
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
        __emit 0x9b
        __emit 0x95
        __emit 0x3f
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x51
        __emit 0xb8
        __emit 0x8c
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x87
        __emit 0x95
        __emit 0x3f
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) UnicodeString::~UnicodeString()
{
    __asm {
        __emit 0xe9
        __emit 0x2b
        __emit 0x93
        __emit 0x82
        __emit 0x00
    }
}

__declspec(naked) UnicodeString &UnicodeString::operator=(const UnicodeString &that)
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
        __emit 0x04
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

__declspec(naked) void __cdecl UnicodeString::format(UnicodeString fmt, ...)
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
        __emit 0x58
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
        __emit 0x8c
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
        __emit 0x62
        __emit 0xf7
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
        __emit 0xf1
        __emit 0xef
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

__declspec(naked) void UnicodeString::translate(const AsciiString &that)
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
        __emit 0x8b
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
        __emit 0xb0
        __emit 0xf4
        __emit 0x0f
        __emit 0x01
        __emit 0xe8
        __emit 0xc7
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

