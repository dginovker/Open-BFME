#include "coord3d.h"

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

bool Coord3D::IsExactlyEqualTo(const Coord3D &that) const
{
    return x == that.x && y == that.y && z == that.z;
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
