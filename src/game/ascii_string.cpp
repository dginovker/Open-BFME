#include "ascii_string.h"

AsciiString::AsciiString()
{
    m_text = 0;
}

__declspec(naked) AsciiString::AsciiString(char c)
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
        __emit 0x23
        __emit 0x07
        __emit 0x0a
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString::AsciiString(const AsciiString &that)
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
        __emit 0x03
        __emit 0x8d
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

__declspec(naked) AsciiString::AsciiString(const char *str, int len)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6c
        __emit 0x8c
        __emit 0x7d
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

__declspec(naked) AsciiString::~AsciiString()
{
    __asm {
        __emit 0xe9
        __emit 0xab
        __emit 0x8a
        __emit 0x82
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator=(const AsciiString &that)
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
        __emit 0xb7
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

__declspec(naked) AsciiString &AsciiString::operator=(const char *str)
{
    __asm {
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xd2
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x74
        __emit 0x1f
        __emit 0x8b
        __emit 0xc2
        __emit 0x56
        __emit 0x8d
        __emit 0x70
        __emit 0x01
        __emit 0x8a
        __emit 0x08
        __emit 0x40
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc6
        __emit 0x5e
        __emit 0x50
        __emit 0x52
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xbc
        __emit 0x5c
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc7
        __emit 0x5f
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x52
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xab
        __emit 0x5c
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0xc7
        __emit 0x5f
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator+=(const AsciiString &that)
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
        __emit 0x2b
        __emit 0x65
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x51
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x17
        __emit 0x65
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator+=(char c)
{
    __asm {
        __emit 0x8a
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
        __emit 0x88
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0xe7
        __emit 0x52
        __emit 0x6f
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) AsciiString &AsciiString::operator+=(const char *str)
{
    __asm {
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xd2
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x74
        __emit 0x1f
        __emit 0x8b
        __emit 0xc2
        __emit 0x56
        __emit 0x8d
        __emit 0x70
        __emit 0x01
        __emit 0x8a
        __emit 0x08
        __emit 0x40
        __emit 0x84
        __emit 0xc9
        __emit 0x75
        __emit 0xf9
        __emit 0x2b
        __emit 0xc6
        __emit 0x5e
        __emit 0x50
        __emit 0x52
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x6c
        __emit 0xc1
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc7
        __emit 0x5f
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x50
        __emit 0x52
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x5b
        __emit 0xc1
        __emit 0x7b
        __emit 0x00
        __emit 0x8b
        __emit 0xc7
        __emit 0x5f
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
