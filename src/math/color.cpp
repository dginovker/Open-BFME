#include "color.h"

RGBColor &RGBColor::operator=(const RGBColor &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

int RGBColor::getAsInt() const
{
    return ((int)(red * 255.0) << 16) | ((int)(green * 255.0) << 8) | ((int)(blue * 255.0) << 0);
}

void RGBColor::setFromInt(int color)
{
    static const float scale = 1.0f / 255.0f;
    red = (float)((color >> 16) & 0xFF) * scale;
    green = (float)((color >> 8) & 0xFF) * scale;
    blue = (float)(color & 0xFF) * scale;
}

bool operator==(const RGBColor &left, const RGBColor &right)
{
    return left.red == right.red &&
        left.green == right.green &&
        left.blue == right.blue;
}

bool operator!=(const RGBColor &left, const RGBColor &right)
{
    return !(left == right);
}

RGBAColorInt &RGBAColorInt::operator=(const RGBAColorInt &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

RGBAColorReal &RGBAColorReal::operator=(const RGBAColorReal &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

class Debug;

__declspec(naked) Debug &operator<<(Debug &debug, const RGBColor &color)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0x68
        __emit 0x64
        __emit 0xe4
        __emit 0x0e
        __emit 0x01
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x50
        __emit 0x38
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x0f
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x20
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x5c
        __emit 0xdf
        __emit 0x09
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0x4f
        __emit 0x04
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x20
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x5c
        __emit 0xdf
        __emit 0x09
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0x4f
        __emit 0x08
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x20
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x04
        __emit 0x28
        __emit 0x08
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}

namespace FXParticleSystem {

RGBColorKeyframe::RGBColorKeyframe()
{
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[3] = 0;
}

RGBColorKeyframe &RGBColorKeyframe::operator=(const RGBColorKeyframe &that)
{
    struct Raw {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int frame;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

}
