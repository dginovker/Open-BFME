#include "string_base.h"

#define EOF (-1)

struct _iobuf;
typedef _iobuf FILE;
typedef unsigned short wchar_t;
extern "C" __declspec(dllimport) int __cdecl fgetc(FILE *stream);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);

class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }
    void clear() { base()->releaseBuffer(); }

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

class MessageStream {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void appendMessage(int type);
};

extern MessageStream *TheMessageStream;

class RecorderClass {
protected:
    AsciiString readAsciiString();
    UnicodeString readUnicodeString();
    void readNextFrame();

private:
    int m_padding0;
    int m_padding4;
    int m_padding8;
    FILE *m_file;
    AsciiString m_fileName;
    char m_padding14[0x2a8 - 0x14];
    bool m_doingAnalysis;
    char m_padding2a9[0x2b0 - 0x2a9];
    int m_nextFrame;
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

void RecorderClass::readNextFrame()
{
    int retcode = fread(&m_nextFrame, sizeof(m_nextFrame), 1, m_file);
    if (retcode != 1) {
        m_nextFrame = -1;
        if (m_file != 0) {
            fclose(m_file);
            m_file = 0;
        }
        m_fileName.clear();
        if (!m_doingAnalysis) {
            TheMessageStream->appendMessage(0x1d);
        }
    }
}
