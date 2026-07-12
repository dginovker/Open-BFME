#pragma once

#include "ascii_string.h"

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
