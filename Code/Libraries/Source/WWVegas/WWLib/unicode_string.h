#pragma once

#include <wchar.h>
#include "string_base.h"

class AsciiString;

class UnicodeString {
public:
    UnicodeString();
    UnicodeString(wchar_t c);
    UnicodeString(const wchar_t *str);
    UnicodeString(const wchar_t *str, int len);
    UnicodeString(const UnicodeString &that);
    UnicodeString(const UnicodeString &that, int start, int len);
    ~UnicodeString();
    UnicodeString &operator=(const UnicodeString &that);
    UnicodeString &operator=(wchar_t c);
    UnicodeString &operator=(const wchar_t *str);
    UnicodeString &operator+=(const UnicodeString &that);
    UnicodeString &operator+=(wchar_t c);
    UnicodeString &operator+=(const wchar_t *str);
    void __cdecl format(UnicodeString fmt, ...);
    void translate(const AsciiString &that);

public:
    // Delegate to StringBase<unsigned short> (matched, mangles @StringBase@G).
    const wchar_t *str() const { return (const wchar_t*)((const StringBase<unsigned short>*)this)->str(); }
    int getLength() const { return ((const StringBase<unsigned short>*)this)->getLength(); }
    wchar_t getCharAt(int i) const { return (wchar_t)((const StringBase<unsigned short>*)this)->getCharAt(i); }
    bool isEmpty() const { return ((const StringBase<unsigned short>*)this)->isEmpty(); }
    bool isNotEmpty() const { return ((const StringBase<unsigned short>*)this)->isNotEmpty(); }
    int compare(const UnicodeString &s) const { return ((const StringBase<unsigned short>*)this)->compare(*(const StringBase<unsigned short>*)&s); }
    int compareNoCase(const UnicodeString &s) const { return ((const StringBase<unsigned short>*)this)->compareNoCase(*(const StringBase<unsigned short>*)&s); }
private:
    wchar_t *m_text;
};
