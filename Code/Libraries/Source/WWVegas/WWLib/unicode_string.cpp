// cl: /MD /EHsc
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

UnicodeString &UnicodeString::operator=(wchar_t c)
{
    wchar_t ch = c;
    ((StringBase<wchar_t> *)this)->set(&ch, 1);
    return *this;
}

UnicodeString &UnicodeString::operator=(const wchar_t *str)
{
    ((StringBase<wchar_t> *)this)->set(str, str ? (int)wcslen(str) : 0);
    return *this;
}

UnicodeString &UnicodeString::operator+=(wchar_t c)
{
    wchar_t ch = c;
    ((StringBase<wchar_t> *)this)->concat(&ch, 1);
    return *this;
}

UnicodeString &UnicodeString::operator+=(const wchar_t *str)
{
    ((StringBase<wchar_t> *)this)->concat(str, str ? (int)wcslen(str) : 0);
    return *this;
}

UnicodeString &UnicodeString::operator+=(const UnicodeString &that)
{
    const StringBase<wchar_t> *s = (const StringBase<wchar_t> *)&that;
    ((StringBase<wchar_t> *)this)->concat(s->m_data ? &s->m_data->data[0] : (const wchar_t *)L"",
                                          s->m_data ? s->m_data->length : 0);
    return *this;
}

UnicodeString::~UnicodeString()
{
    ((StringBase<wchar_t> *)this)->releaseBuffer();
}

UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
    return *this;
}

void __cdecl UnicodeString::format(UnicodeString fmt, ...)
{
    const StringBase<wchar_t> *f = (const StringBase<wchar_t> *)&fmt;
    ((StringBase<wchar_t> *)this)->format_va(f->m_data ? &f->m_data->data[0] : (const wchar_t *)L"",
                                             (char *)(&fmt + 1));
}

void UnicodeString::translate(const AsciiString &that)
{
    const StringBase<char> *a = (const StringBase<char> *)&that;
    format(UnicodeString(L"%hs"), a->m_data ? &a->m_data->data[0] : (const char *)"");
}
