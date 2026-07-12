// cl: /EHsc
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

AsciiString &AsciiString::operator=(const AsciiString &that)
{
    ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
    return *this;
}

AsciiString &AsciiString::operator=(const char *str)
{
    ((StringBase<char> *)this)->set(str, str ? strlen(str) : 0);
    return *this;
}

AsciiString &AsciiString::operator+=(const AsciiString &that)
{
    const StringBase<char> *s = (const StringBase<char> *)&that;
    ((StringBase<char> *)this)->concat(s->m_data ? &s->m_data->data[0] : (const char *)"",
                                       s->m_data ? s->m_data->length : 0);
    return *this;
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

AsciiString operator+(AsciiString left, const char *right)
{
    left += right;
    return left;
}

AsciiString operator+(AsciiString left, const AsciiString &right)
{
    left += right;
    return left;
}

AsciiString operator+(AsciiString left, char right)
{
    left += right;
    return left;
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

AsciiString &AsciiString::operator=(const UnicodeString &that)
{
    const StringBase<wchar_t> *w = (const StringBase<wchar_t> *)&that;
    format(AsciiString("%ls"), w->m_data ? &w->m_data->data[0] : (const wchar_t *)L"");
    return *this;
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

void __cdecl AsciiString::format(AsciiString fmt, ...)
{
    const StringBase<char> *f = (const StringBase<char> *)&fmt;
    ((StringBase<char> *)this)->format_va(f->m_data ? &f->m_data->data[0] : (const char *)"",
                                          (char *)(&fmt + 1));
}

void AsciiString::translate(const UnicodeString &that)
{
    const StringBase<wchar_t> *w = (const StringBase<wchar_t> *)&that;
    format(AsciiString("%ls"), w->m_data ? &w->m_data->data[0] : (const wchar_t *)L"");
}

