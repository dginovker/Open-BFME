#include "region.h"

#include "icoord.h"

bool IRegion2D::operator==(const IRegion2D &that) const
{
    return x_min == that.x_min &&
        y_min == that.y_min &&
        x_max == that.x_max &&
        y_max == that.y_max;
}

bool IRegion2D::operator!=(const IRegion2D &that) const
{
    return !(*this == that);
}

void IRegion2D::expandBy(const ICoord2D &point)
{
    if (point.x < x_min) {
        x_min = point.x;
    } else if (point.x > x_max) {
        x_max = point.x;
    }

    if (point.y < y_min) {
        y_min = point.y;
    } else if (point.y > y_max) {
        y_max = point.y;
    }
}

int IRegion2D::width() const
{
    return x_max - x_min;
}

int IRegion2D::height() const
{
    return y_max - y_min;
}

IRegion3D::IRegion3D()
{
}

void IRegion3D::expandBy(const ICoord3D &point)
{
    if (point.x < x_min) {
        x_min = point.x;
    } else if (point.x > x_max) {
        x_max = point.x;
    }

    if (point.y < y_min) {
        y_min = point.y;
    } else if (point.y > y_max) {
        y_max = point.y;
    }

    if (point.z < z_min) {
        z_min = point.z;
    } else if (point.z > z_max) {
        z_max = point.z;
    }
}

int IRegion3D::width() const
{
    return x_max - x_min;
}

int IRegion3D::height() const
{
    return y_max - y_min;
}

int IRegion3D::depth() const
{
    return z_max - z_min;
}

Region2D::Region2D()
{
}

Region2D::Region2D(const Region2D &that)
{
    x_min = that.x_min;
    y_min = that.y_min;
    x_max = that.x_max;
    y_max = that.y_max;
}

Region2D::Region2D(const Coord2D &lower_left, const Coord2D &upper_right)
{
    x_min = lower_left.x;
    y_min = lower_left.y;
    x_max = upper_right.x;
    y_max = upper_right.y;
}

Region2D::~Region2D()
{
}

bool Region2D::IsExactlyEqualTo(const Region2D &that) const
{
    return that.x_min == x_min &&
        that.y_min == y_min &&
        that.x_max == x_max &&
        that.y_max == y_max;
}

void Region2D::expandBy(const Coord2D &point)
{
    float x = point.x;

    if (x < x_min) {
        x_min = x;
    } else if (x > x_max) {
        x_max = x;
    }

    float y = point.y;

    if (y < y_min) {
        y_min = y;
    } else if (y > y_max) {
        y_max = y;
    }
}

bool Region2D::isInside(const Coord2D &point) const
{
    return point.x > x_min &&
        point.x < x_max &&
        point.y > y_min &&
        point.y < y_max;
}

float Region2D::width() const
{
    return x_max - x_min;
}

float Region2D::height() const
{
    return y_max - y_min;
}

Region3D::Region3D()
{
}

Region3D::Region3D(const Region3D &that)
{
    x_min = that.x_min;
    y_min = that.y_min;
    z_min = that.z_min;
    x_max = that.x_max;
    y_max = that.y_max;
    z_max = that.z_max;
}

Region3D::~Region3D()
{
}

float Region3D::width() const
{
    return x_max - x_min;
}

float Region3D::height() const
{
    return y_max - y_min;
}

float Region3D::depth() const
{
    return z_max - z_min;
}

void Region3D::expandBy(const Coord3D &point)
{
    float x = point.x;

    if (x < x_min) {
        x_min = x;
    } else if (x > x_max) {
        x_max = x;
    }

    float y = point.y;

    if (y < y_min) {
        y_min = y;
    } else if (y > y_max) {
        y_max = y;
    }

    float z = point.z;

    if (z < z_min) {
        z_min = z;
    } else if (z > z_max) {
        z_max = z;
    }
}

bool Region3D::isInRegionNoZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max;
}

bool Region3D::isInRegionWithZ(const Coord3D *point) const
{
    return x_min < point->x &&
        point->x < x_max &&
        y_min < point->y &&
        point->y < y_max &&
        z_min < point->z &&
        point->z < z_max;
}

void Region3D::zero()
{
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[2] = 0;
    ((unsigned int *)this)[3] = 0;
    ((unsigned int *)this)[4] = 0;
    ((unsigned int *)this)[5] = 0;
}
