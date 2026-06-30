#pragma once

struct RGBColor {
    float red;
    float green;
    float blue;

    RGBColor &operator=(const RGBColor &that);
    int getAsInt() const;
    void setFromInt(int color);
};

bool operator==(const RGBColor &left, const RGBColor &right);
bool operator!=(const RGBColor &left, const RGBColor &right);

struct RGBAColorInt {
    int red;
    int green;
    int blue;
    int alpha;

    RGBAColorInt &operator=(const RGBAColorInt &that);
};

struct RGBAColorReal {
    float red;
    float green;
    float blue;
    float alpha;

    RGBAColorReal &operator=(const RGBAColorReal &that);
};

namespace FXParticleSystem {

struct RGBColorKeyframe {
    RGBColorKeyframe();
    RGBColorKeyframe &operator=(const RGBColorKeyframe &that);

    float red;
    float green;
    float blue;
    float frame;
};

}
