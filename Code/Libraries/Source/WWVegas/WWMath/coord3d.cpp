// cl: /ICode/GameEngine/Source/Common
#include "coord3d.h"

#include "debug.h"
#include <math.h>

Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that)
{
    struct Raw {
        unsigned int x;
        unsigned int y;
        unsigned int z;
    };
    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

Coord3D::Coord3D()
{
}

Coord3D::Coord3D(const Coord3D &that)
{
    x = that.x;
    y = that.y;
    z = that.z;
}

Coord3D::Coord3D(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;
}

Coord3D::Coord3D(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    z = that.z;
}

Coord3D::Coord3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Coord3D::Coord3D(int x, int y, int z)
{
    this->x = (float)x;
    this->y = (float)y;
    this->z = (float)z;
}

Coord3D::~Coord3D()
{
}

Coord3D &Coord3D::operator=(const Coord3D &that)
{
    Coord3DBase *base = this;
    *base = that;
    return *this;
}

Coord3D &Coord3D::operator=(const Coord2D &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;
    return *this;
}

Coord3D &Coord3D::operator=(const Coord2DBase &that)
{
    x = that.x;
    y = that.y;
    z = 0.0f;
    return *this;
}

Coord3D &Coord3D::operator=(const Coord3DBase &that)
{
    x = that.x;
    y = that.y;
    z = that.z;
    return *this;
}

bool Coord3D::operator==(const Coord3D &that) const
{
    return x == that.x && y == that.y && z == that.z;
}

float Coord3D::operator*(const Coord2D &that) const
{
    return x * that.x + y * that.y;
}

float Coord3D::operator*(const Coord3DBase &that) const
{
    return x * that.x + y * that.y + z * that.z;
}

Coord3D &Coord3D::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Coord3D &Coord3D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Coord3D &Coord3D::operator+=(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord3D &Coord3D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    z += that.z;
    return *this;
}

Coord3D &Coord3D::operator-=(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord3D &Coord3D::operator-=(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    z -= that.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord3D &Coord3D::Add(const Coord2D &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = right.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    z += that.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &left, const Coord2D &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = left.z;
    return *this;
}

Coord3D &Coord3D::Add(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    z = left.z + right.z;
    return *this;
}

Coord3D &Coord3D::Add2D(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

Coord3D &Coord3D::Add2D(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x + right.x;
    y = left.y + right.y;
    return *this;
}

bool Coord3D::equals(const Coord3DBase &that) const
{
    return x == that.x && y == that.y && z == that.z;
}

float Coord3D::GetLength() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

float Coord3D::GetLength2D() const
{
    float x_value = x;
    float y_value = y;

    return (float)sqrt(x_value * x_value + y_value * y_value);
}

static const float length_estimate_factor = 0.25f;
static const float one = 1.0f;
static const float zero_value = 0.0f;

void Coord3D::normalize()
{
    float len = (float)sqrt(x * x + y * y + z * z);
    if (len != zero_value) {
        float scale = one / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

float Coord3D::Normalize()
{
    float len = GetLength();
    float scale = one / len;
    x *= scale;
    y *= scale;
    z *= scale;
    return len;
}

float Coord3D::Normalize2D()
{
    float len = GetLength2D();
    float scale = one / len;
    x *= scale;
    y *= scale;
    return len;
}

float Coord3D::GetLengthEstimate2D() const
{
    float ax = fabs(x);
    float ay = fabs(y);
    if (ax > ay) {
        return ax + length_estimate_factor * ay;
    }
    return ay + length_estimate_factor * ax;
}

__declspec(naked) float Coord3D::GetLengthEstimate() const
{
    __asm {
        __emit 0x51
        __emit 0xd9
        __emit 0x01
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0xd9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x75
        __emit 0x0c
        __emit 0xd9
        __emit 0x05
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0xc9
        __emit 0xd8
        __emit 0xc2
        __emit 0xeb
        __emit 0x0a
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd8
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0xc1
        __emit 0xdf
        __emit 0xe0
        __emit 0xd8
        __emit 0xd9
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0xdf
        __emit 0xe0
        __emit 0x75
        __emit 0x1c
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x74
        __emit 0x02
        __emit 0xd9
        __emit 0xc9
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0x59
        __emit 0xc3
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x74
        __emit 0x02
        __emit 0xd9
        __emit 0xc9
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0x04
        __emit 0x24
        __emit 0x59
    }
}

__declspec(naked) float Coord3D::lengthEstimate() const
{
    __asm {
        __emit 0x51
        __emit 0xd9
        __emit 0x01
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0xd9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x75
        __emit 0x0c
        __emit 0xd9
        __emit 0x05
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0xc9
        __emit 0xd8
        __emit 0xc2
        __emit 0xeb
        __emit 0x0a
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xd9
        __emit 0xe1
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0xd8
        __emit 0x1c
        __emit 0x24
        __emit 0xd9
        __emit 0xc1
        __emit 0xdf
        __emit 0xe0
        __emit 0xd8
        __emit 0xd9
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0xdf
        __emit 0xe0
        __emit 0x75
        __emit 0x1c
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x74
        __emit 0x02
        __emit 0xd9
        __emit 0xc9
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0x59
        __emit 0xc3
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x74
        __emit 0x02
        __emit 0xd9
        __emit 0xc9
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xde
        __emit 0xc1
        __emit 0xd8
        __emit 0x0d
        __emit 0x6c
        __emit 0x3b
        __emit 0x08
        __emit 0x01
        __emit 0xd8
        __emit 0x04
        __emit 0x24
        __emit 0x59
        __emit 0xc3
    }
}

float Coord3D::GetLengthSqrd() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;

    return x_value * x_value + y_value * y_value + z_value * z_value;
}

float Coord3D::GetLengthSqrd2D() const
{
    float x_value = x;
    float y_value = y;

    return x_value * x_value + y_value * y_value;
}

bool Coord3D::IsExactlyEqualTo(const Coord3D &that) const
{
    return x == that.x && y == that.y && z == that.z;
}

float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

float Coord3D::lengthSqr() const
{
    return z * z + y * y + x * x;
}

Coord3D &Coord3D::Negate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

Coord3D &Coord3D::Scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Coord3D &Coord3D::Scale(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    z = that.z * scale;
    return *this;
}

Coord3D &Coord3D::Scale2D(float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Coord3D &Coord3D::Scale2D(const Coord3DBase &that, float scale)
{
    x = that.x * scale;
    y = that.y * scale;
    return *this;
}

Coord3D &Coord3D::Set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

Coord3D &Coord3D::Set2D(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

Coord3D &Coord3D::SetMaxVect()
{
    ((unsigned int *)this)[2] = 0x7f7fffff;
    ((unsigned int *)this)[1] = 0x7f7fffff;
    ((unsigned int *)this)[0] = 0x7f7fffff;
    return *this;
}

Coord3D &Coord3D::SetMinVect()
{
    ((unsigned int *)this)[2] = 0xff7fffff;
    ((unsigned int *)this)[1] = 0xff7fffff;
    ((unsigned int *)this)[0] = 0xff7fffff;
    return *this;
}

Coord3D &Coord3D::SetXAxis()
{
    unsigned int zero = 0;

    ((unsigned int *)this)[0] = 0x3f800000;
    ((unsigned int *)this)[1] = zero;
    ((unsigned int *)this)[2] = zero;
    return *this;
}

Coord3D &Coord3D::SetYAxis()
{
    x = 0.0f;
    y = 1.0f;
    z = 0.0f;
    return *this;
}

Coord3D &Coord3D::SetZAxis()
{
    x = 0.0f;
    y = 0.0f;
    z = 1.0f;
    return *this;
}

void Coord3D::zero()
{
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[2] = 0;
}

void Coord3D::add(const Coord3DBase *that)
{
    x += that->x;
    y += that->y;
    z += that->z;
}

void Coord3D::scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
}

void Coord3D::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Coord3D::set(const Coord3DBase *that)
{
    x = that->x;
    y = that->y;
    z = that->z;
}

void Coord3D::sub(const Coord3DBase *that)
{
    x -= that->x;
    y -= that->y;
    z -= that->z;
}

void Coord3D::crossProduct(const Coord3D *left, const Coord3D *right, Coord3D *result)
{
    result->x = left->y * right->z - left->z * right->y;
    result->y = left->z * right->x - left->x * right->z;
    result->z = left->x * right->y - left->y * right->x;
}

__declspec(naked) Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    __asm {
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x18
        __emit 0xd9
        __emit 0x06
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x02
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0x02
        __emit 0xd8
        __emit 0x4e
        __emit 0x04
        __emit 0xd9
        __emit 0x06
        __emit 0x5e
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

Coord3D &Coord3D::SetZero()
{
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[0] = 0;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord2D &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = -right.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    z -= that.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord3DBase &left, const Coord2D &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = left.z;
    return *this;
}

Coord3D &Coord3D::Sub(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    z = left.z - right.z;
    return *this;
}

Coord3D &Coord3D::Sub2D(const Coord3DBase &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

Coord3D &Coord3D::Sub2D(const Coord3DBase &left, const Coord3DBase &right)
{
    x = left.x - right.x;
    y = left.y - right.y;
    return *this;
}

Debug &operator<<(Debug &debug, const Coord3D &coord)
{
    debug << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
    return debug;
}
