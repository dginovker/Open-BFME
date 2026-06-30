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

extern "C" void _stringbase_isnone_cmp_char();
extern "C" void _stringbase_isnone_cmp_wchar();

__declspec(naked) bool StringBase<char>::isNone() const
{
    __asm {
        push 0x01133008
        call _stringbase_isnone_cmp_char
        neg eax
        sbb eax, eax
        inc eax
        ret
    }
}

__declspec(naked) bool StringBase<wchar_t>::isNone() const
{
    __asm {
        push 0x0113301c
        call _stringbase_isnone_cmp_wchar
        neg eax
        sbb eax, eax
        inc eax
        ret
    }
}

extern "C" void _stringbase_isnotnone_cmp_char();
extern "C" void _stringbase_isnotnone_cmp_wchar();

__declspec(naked) bool StringBase<char>::isNotNone() const
{
    __asm {
        push 0x01133008
        call _stringbase_isnotnone_cmp_char
        neg eax
        sbb eax, eax
        neg eax
        ret
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
    }
}

__declspec(naked) bool StringBase<wchar_t>::isNotNone() const
{
    __asm {
        push 0x0113301c
        call _stringbase_isnotnone_cmp_wchar
        neg eax
        sbb eax, eax
        neg eax
        ret
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
        __emit 0xcc
    }
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

__declspec(naked) int StringBase<char>::compare(const char *str) const
{
    __asm {
        __emit 0xe9
        __emit 0x91
        __emit 0x7b
        __emit 0x05
        __emit 0x00
        __emit 0xe9
        __emit 0x8c
        __emit 0x9a
        __emit 0x0f
        __emit 0x00
    }
}

__declspec(naked) StringBase<char>::~StringBase()
{
    __asm {
        __emit 0xe9
        __emit 0xab
        __emit 0x94
        __emit 0x82
        __emit 0x00
        __emit 0xcc
    }
}

__declspec(naked) StringBase<wchar_t>::~StringBase()
{
    __asm {
        __emit 0xe9
        __emit 0xeb
        __emit 0x9c
        __emit 0x82
        __emit 0x00
        __emit 0xcc
    }
}

__declspec(naked) bool StringBase<char>::startsWithNoCase(const char *str) const
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x1c
        __emit 0x8b
        __emit 0xc6
        __emit 0x57
        __emit 0x8d
        __emit 0x78
        __emit 0x01
        __emit 0x90
        __emit 0x8a
        __emit 0x10
        __emit 0x40
        __emit 0x84
        __emit 0xd2
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc7
        __emit 0x5f
        __emit 0x50
        __emit 0x56
        __emit 0xe8
        __emit 0x5f
        __emit 0xa3
        __emit 0x77
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x56
        __emit 0xe8
        __emit 0x52
        __emit 0xa3
        __emit 0x77
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) bool StringBase<char>::startsWithNoCase(const StringBase<char> &str) const
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
        __emit 0x74
        __emit 0x06
        __emit 0x0f
        __emit 0xb7
        __emit 0x50
        __emit 0x04
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xd2
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0d
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0x52
        __emit 0x50
        __emit 0xe8
        __emit 0xc0
        __emit 0x8a
        __emit 0x77
        __emit 0x00
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x52
        __emit 0x50
        __emit 0xe8
        __emit 0xb1
        __emit 0x8a
        __emit 0x77
        __emit 0x00
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) void StringBase<char>::set(char c)
{
    __asm {
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0xe8
        __emit 0xb4
        __emit 0x74
        __emit 0x31
        __emit 0x00
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xcc
    }
}

__declspec(naked) void StringBase<wchar_t>::set(wchar_t c)
{
    __asm {
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0xe8
        __emit 0x04
        __emit 0x36
        __emit 0x32
        __emit 0x00
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xcc
    }
}

__declspec(naked) void StringBase<char>::set(const char *str)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x1c
        __emit 0x8b
        __emit 0xc6
        __emit 0x57
        __emit 0x8d
        __emit 0x78
        __emit 0x01
        __emit 0x90
        __emit 0x8a
        __emit 0x10
        __emit 0x40
        __emit 0x84
        __emit 0xd2
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc7
        __emit 0x5f
        __emit 0x50
        __emit 0x56
        __emit 0xe8
        __emit 0x0f
        __emit 0x61
        __emit 0x82
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x56
        __emit 0xe8
        __emit 0x02
        __emit 0x61
        __emit 0x82
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) void StringBase<wchar_t>::set(const wchar_t *str)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xf6
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x74
        __emit 0x18
        __emit 0x56
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
        __emit 0x56
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x31
        __emit 0x51
        __emit 0x80
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x56
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x21
        __emit 0x51
        __emit 0x80
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
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

__declspec(naked) bool operator==(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
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
        __emit 0x3e
        __emit 0x1f
        __emit 0xfc
        __emit 0xff
        __emit 0xf7
        __emit 0xd8
        __emit 0x1b
        __emit 0xc0
        __emit 0x40
        __emit 0xc3
    }
}

__declspec(naked) bool operator!=(const StringBase<char> &left, const StringBase<char> &right)
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
        __emit 0x67
        __emit 0xe3
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

__declspec(naked) bool operator!=(const StringBase<wchar_t> &left, const StringBase<wchar_t> &right)
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
        __emit 0xae
        __emit 0x71
        __emit 0xf8
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

__declspec(naked) Debug &operator<<(Debug &debug, const StringBase<char> &str)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x14
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x16
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x16
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}

__declspec(naked) void StringBase<char>::clear()
{
    __asm {
        __emit 0xe9
        __emit 0x7b
        __emit 0xf8
        __emit 0x81
        __emit 0x00
        __emit 0xcc
    }
}

__declspec(naked) void StringBase<wchar_t>::clear()
{
    __asm {
        __emit 0xe9
        __emit 0x3b
        __emit 0x01
        __emit 0x82
        __emit 0x00
        __emit 0xcc
    }
}
