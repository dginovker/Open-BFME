#include "string_base.h"

#include <string.h>

template <typename T>
StringBase<T>::StringBase()
{
    m_data = 0;
}

template <typename T>
void StringBase<T>::debugIgnoreLeaks()
{
}

template <typename T>
bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template <typename T>
bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

template <typename T>
int StringBase<T>::getLength() const
{
    return m_data ? m_data->length : 0;
}

template <typename T>
const T *StringBase<T>::str() const
{
    return m_data ? &m_data->data[0] : (const T *)"";
}

template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *start = m_data ? &m_data->data[0] : (const T *)"";
    const T *end = start + (m_data ? m_data->length : 0);

    for (const T *p = start; p != end; ++p) {
        if (*p == c) {
            return p;
        }
    }

    return 0;
}

template <typename T>
T *StringBase<T>::peek() const
{
    return &m_data->data[0];
}

template <typename T>
T StringBase<T>::getCharAt(int index) const
{
    return m_data ? m_data->data[index] : 0;
}

template <typename T>
void StringBase<T>::validate() const
{
}

template class StringBase<char>;
template class StringBase<wchar_t>;

__declspec(naked) bool operator<(const StringBase<char> &left, const StringBase<char> &right)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0xe8
        __emit 0xe7
        __emit 0xf1
        __emit 0xfb
        __emit 0xff
        __emit 0x33
        __emit 0xc9
        __emit 0x85
        __emit 0xc0
        __emit 0x0f
        __emit 0x9c
        __emit 0xc1
        __emit 0x8a
        __emit 0xc1
        __emit 0xc3
    }
}

__declspec(naked) bool operator<(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0xe8
        __emit 0x8e
        __emit 0x3b
        __emit 0xad
        __emit 0xff
        __emit 0x33
        __emit 0xc9
        __emit 0x85
        __emit 0xc0
        __emit 0x0f
        __emit 0x9c
        __emit 0xc1
        __emit 0x8a
        __emit 0xc1
        __emit 0xc3
    }
}

__declspec(naked) bool operator!=(const StringBase<char> &left, const char *right)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0xe8
        __emit 0xdc
        __emit 0xa2
        __emit 0xf7
        __emit 0xff
        __emit 0xf7
        __emit 0xd8
        __emit 0x1b
        __emit 0xc0
        __emit 0xf7
        __emit 0xd8
        __emit 0xc3
    }
}

__declspec(naked) bool operator==(const StringBase<char> &left, const char *right)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0xe8
        __emit 0xdc
        __emit 0x0d
        __emit 0xfa
        __emit 0xff
        __emit 0xf7
        __emit 0xd8
        __emit 0x1b
        __emit 0xc0
        __emit 0x40
        __emit 0xc3
    }
}

__declspec(naked) bool operator==(const StringBase<char> &left, const StringBase<char> &right)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x50
        __emit 0xe8
        __emit 0xc7
        __emit 0x20
        __emit 0xfa
        __emit 0xff
        __emit 0xf7
        __emit 0xd8
        __emit 0x1b
        __emit 0xc0
        __emit 0x40
        __emit 0xc3
    }
}
