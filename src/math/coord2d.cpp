#include "coord2d.h"
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

Coord2D &Coord2D::Rotate(const Coord2D &source, float angle)
{
    float sine;
    float cosine;
    __asm {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }
    x = cosine * source.x - sine * source.y;
    y = sine * source.x + cosine * source.y;
    return *this;
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

class Debug;

__declspec(naked) Debug &operator<<(Debug &debug, const Coord2D &coord)
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
