#include "coord2d.h"
#include "coord3d.h"

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

bool Coord2D::IsExactlyEqualTo(const Coord2D &that) const
{
    return x == that.x && y == that.y;
}

Coord2D &Coord2D::Negate()
{
    x = -x;
    y = -y;
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
