// cl: /ICode/Libraries/Include/Lib
#include "trig.h"

#include <math.h>

extern "C" void bfme_acos();
extern "C" void bfme_asin();

float Sin(float radians)
{
    return sinf(radians);
}

float Cos(float radians)
{
    return cosf(radians);
}

float Tan(float radians)
{
    return tanf(radians);
}

float ACos(float x)
{
    __asm {
        fld dword ptr [esp + 4]
        call bfme_acos
        ret
    }
}

float ASin(float x)
{
    __asm {
        fld dword ptr [esp + 4]
        call bfme_asin
        ret
    }
}

float deg2rad(float degrees)
{
    return degrees * 0.01745329238474369f;
}

float rad2deg(float radians)
{
    return radians * 57.2957763671875f;
}
