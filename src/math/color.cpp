#include "color.h"

#include "../game/debug.h"

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

Debug &operator<<(Debug &debug, const RGBColor &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorReal &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorInt &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

namespace FXParticleSystem {

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
