#pragma once

#include <wchar.h>

class UnicodeString {
public:
    UnicodeString();
    UnicodeString(wchar_t c);
    UnicodeString(const wchar_t *str);
    UnicodeString(const wchar_t *str, int len);
    UnicodeString(const UnicodeString &that, int start, int len);
    UnicodeString &operator=(const UnicodeString &that);
    UnicodeString &operator=(wchar_t c);
    UnicodeString &operator=(const wchar_t *str);
    UnicodeString &operator+=(wchar_t c);
    UnicodeString &operator+=(const wchar_t *str);

private:
    wchar_t *m_text;
};
