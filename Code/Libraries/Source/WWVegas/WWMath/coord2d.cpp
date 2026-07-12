// cl: /ICode/GameEngine/Source/Common
#include "coord2d.h"
#include "debug.h"
#include "coord3d.h"

#include <math.h>

Coord2DBase &Coord2DBase::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D::Coord2D()
{
}

Coord2D::Coord2D(const Coord2D &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
}

Coord2D::Coord2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Coord2D::Coord2D(int x, int y)
{
    this->x = (float)x;
    this->y = (float)y;
}

Coord2D::~Coord2D()
{
}

Coord2D &Coord2D::operator=(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D &Coord2D::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

Coord2D &Coord2D::operator=(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

float Coord2D::operator*(const Coord2D &that) const
{
    return x * that.x + y * that.y;
}

float Coord2D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y;
}

Coord2D &Coord2D::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::operator+=(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::operator-=(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::operator-=(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::Add(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord2D &Coord2D::Add(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

float Coord2D::GetLength() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

float Coord2D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

bool Coord2D::IsExactlyEqualTo(const Coord2D &that) const
{
    return x == that.x && y == that.y;
}

float Coord2D::length() const
{
    return (float)sqrt(x * x + y * y);
}

Coord2D &Coord2D::Negate()
{
    x = -x;
    y = -y;
    return *this;
}

static const float one = 1.0f;
static const float zero_value = 0.0f;
static const float length_estimate_factor = 0.25f;

void Coord2D::normalize()
{
    float len = (float)sqrt(x * x + y * y);
    if (len != zero_value) {
        float scale = one / len;
        x *= scale;
        y *= scale;
    }
}

float Coord2D::Normalize()
{
    __asm {
        fld dword ptr [ecx]
        fld dword ptr [ecx + 4]
        fld ST(0)
        fmul ST(0), ST(1)
        fld ST(2)
        fmul ST(0), ST(3)
        faddp ST(1), ST(0)
        fsqrt
        fstp ST(2)
        fstp ST(0)
        fld one
        fdiv ST(0), ST(1)
        fld ST(0)
        fmul dword ptr [ecx]
        fstp dword ptr [ecx]
        fmul dword ptr [ecx + 4]
        fstp dword ptr [ecx + 4]
    }
}

float Coord2D::GetLengthEstimate() const
{
    float ax = fabs(x);
    float ay = fabs(y);
    if (ax > ay) {
        return ax + length_estimate_factor * ay;
    }
    return ay + length_estimate_factor * ax;
}

Coord2D &Coord2D::Rotate(float sine, float cosine)
{
    float new_x = cosine * x - sine * y;

    y = cosine * y + sine * x;
    x = new_x;
    return *this;
}

Coord2D &Coord2D::Rotate(Coord2D &coord, float sine, float cosine)
{
    x = cosine * coord.x - sine * coord.y;
    y = cosine * coord.y + sine * coord.x;
    return *this;
}

__declspec(naked) float Coord2D::toAngle() const
{
    __asm {
        __emit 0x51
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd9
        __emit 0x01
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0xc2
        __emit 0xd8
        __emit 0xcb
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0xfa
        __emit 0xdd
        __emit 0xda
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0xc1
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x0a
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x59
        __emit 0xc3
        __emit 0xd8
        __emit 0x39
        __emit 0xd8
        __emit 0x15
        __emit 0x3c
        __emit 0xbf
        __emit 0x09
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x05
        __emit 0x7a
        __emit 0x0b
        __emit 0xdd
        __emit 0xd8
        __emit 0xc7
        __emit 0x04
        __emit 0x24
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0xbf
        __emit 0xeb
        __emit 0x1b
        __emit 0xd8
        __emit 0x15
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x75
        __emit 0x0b
        __emit 0xdd
        __emit 0xd8
        __emit 0xc7
        __emit 0x04
        __emit 0x24
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0xeb
        __emit 0x03
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd8
        __emit 0x1d
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x05
        __emit 0x7a
        __emit 0x10
        __emit 0x8b
        __emit 0x04
        __emit 0x24
        __emit 0x50
        __emit 0xe8
        __emit 0x11
        __emit 0xdc
        __emit 0x6c
        __emit 0x00
        __emit 0xd9
        __emit 0xe0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x59
        __emit 0xc3
        __emit 0x8b
        __emit 0x0c
        __emit 0x24
        __emit 0x51
        __emit 0xe8
        __emit 0x01
        __emit 0xdc
        __emit 0x6c
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x59
        __emit 0xc3
    }
}

__declspec(naked) Coord2D &Coord2D::Rotate(float angle)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0xfe
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0xff
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x08
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x48
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x48
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0x18
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

__declspec(naked) Coord2D &Coord2D::Rotate(const Coord2D &source, float angle)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x18
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x09
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

Coord2D &Coord2D::Scale(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord2D &Coord2D::Set(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

Coord2D &Coord2D::SetMaxVect()
{
    y = 3.4028234663852886e38f;
    x = 3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetMinVect()
{
    y = -3.4028234663852886e38f;
    x = -3.4028234663852886e38f;
    return *this;
}

Coord2D &Coord2D::SetXAxis()
{
    x = 1.0f;
    y = 0.0f;
    return *this;
}

Coord2D &Coord2D::SetYAxis()
{
    x = 0.0f;
    y = 1.0f;
    return *this;
}

Coord2D &Coord2D::SetZero()
{
    y = 0.0f;
    x = 0.0f;
    return *this;
}

Coord2D &Coord2D::Sub(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord2D &Coord2D::Sub(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Debug &operator<<(Debug &debug, const Coord2D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ")";
    return debug;
}
