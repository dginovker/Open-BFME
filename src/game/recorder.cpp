#include "string_base.h"

static const char replayExtention[] = ".rep";
static const char lastReplayFileName[] = "00000000";

class AsciiString : public StringBase<char> {
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &that) : StringBase<char>(that) {}
    AsciiString(const char *str) : StringBase<char>(str) {}
    ~AsciiString() { releaseBuffer(); }

    void concat(const char *str)
    {
        const char *start = str;
        const char *end = str + 1;
        while (*str++) {
        }
        StringBase<char>::concat(start, str - end);
    }
};

class GlobalData {
public:
    AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class RecorderClass {
public:
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
    AsciiString getLastReplayFileName();
};

__declspec(naked) AsciiString RecorderClass::getReplayDir()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x61
        __emit 0x60
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
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8d
        __emit 0x04
        __emit 0x24
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x0d
        __emit 0xc8
        __emit 0xd5
        __emit 0x2e
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0x6b
        __emit 0x7c
        __emit 0xf7
        __emit 0xff
        __emit 0xb8
        __emit 0xa4
        __emit 0xfe
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x50
        __emit 0x01
        __emit 0x90
        __emit 0x8a
        __emit 0x08
        __emit 0x40
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0xf9
        __emit 0x56
        __emit 0x2b
        __emit 0xc2
        __emit 0x50
        __emit 0x68
        __emit 0xa4
        __emit 0xfe
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xe8
        __emit 0xb7
        __emit 0xf2
        __emit 0x7e
        __emit 0x00
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x1c
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xa7
        __emit 0xf0
        __emit 0x7e
        __emit 0x00
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0xe8
        __emit 0x71
        __emit 0xee
        __emit 0x7e
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
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
        __emit 0x14
        __emit 0xc3
    }
}

AsciiString RecorderClass::getReplayExtention()
{
    return AsciiString(replayExtention);
}

AsciiString RecorderClass::getLastReplayFileName()
{
    return AsciiString(lastReplayFileName);
}
