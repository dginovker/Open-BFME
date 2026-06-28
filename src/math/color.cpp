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

namespace FXParticleSystem {

RGBColorKeyframe::RGBColorKeyframe()
{
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[3] = 0;
}

}
