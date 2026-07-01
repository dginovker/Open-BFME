#include "string_base.h"

#define EOF (-1)

struct _iobuf;
typedef _iobuf FILE;
typedef unsigned short wchar_t;
extern "C" __declspec(dllimport) int __cdecl fgetc(FILE *stream);

class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }

private:
    StringBase<char> *base() { return (StringBase<char> *)this; }
    const StringBase<char> *base() const { return (const StringBase<char> *)this; }

private:
    StringBase<char>::Header *m_data;
};

class UnicodeString {
public:
    UnicodeString() { base()->StringBase<wchar_t>::StringBase(); }
    UnicodeString(const UnicodeString &that) { base()->StringBase<wchar_t>::StringBase(*that.base()); }
    UnicodeString(const wchar_t *str) { base()->StringBase<wchar_t>::StringBase(str); }
    ~UnicodeString() { base()->releaseBuffer(); }

private:
    StringBase<wchar_t> *base() { return (StringBase<wchar_t> *)this; }
    const StringBase<wchar_t> *base() const { return (const StringBase<wchar_t> *)this; }

private:
    StringBase<wchar_t>::Header *m_data;
};

UnicodeString readUnicodeString(FILE *file);

class RecorderClass {
protected:
    AsciiString readAsciiString();
    UnicodeString readUnicodeString();

private:
    int m_padding0;
    int m_padding4;
    int m_padding8;
    FILE *m_file;
};

AsciiString RecorderClass::readAsciiString()
{
    char str[1024] = "";
    int index = 0;

    int c = fgetc(m_file);
    if (c == EOF) {
        str[index] = 0;
    }
    str[index] = c;

    while (index < 1024 && str[index] != 0) {
        ++index;
        int c = fgetc(m_file);
        if (c == EOF) {
            str[index] = 0;
            break;
        }
        str[index] = c;
    }
    str[1023] = '\0';

    AsciiString retval(str);
    return retval;
}

UnicodeString RecorderClass::readUnicodeString()
{
    return ::readUnicodeString(m_file);
}
