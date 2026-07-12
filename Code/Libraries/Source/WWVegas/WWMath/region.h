#pragma once

#include "coord2d.h"
#include "coord3d.h"

struct ICoord2D;
struct ICoord3D;

struct RealRange {
    RealRange &operator=(const RealRange &that);
    void combine(RealRange &that);

    float min;
    float max;
};

struct IRegion2D {
    bool operator==(const IRegion2D &that) const;
    bool operator!=(const IRegion2D &that) const;

    IRegion2D &operator=(const IRegion2D &that);
    void expandBy(const ICoord2D &point);
    int width() const;
    int height() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

struct IRegion3D {
    IRegion3D();
    IRegion3D &operator=(const IRegion3D &that);

    void expandBy(const ICoord3D &point);
    int width() const;
    int height() const;
    int depth() const;

    int x_min;
    int y_min;
    int z_min;
    int x_max;
    int y_max;
    int z_max;
};

struct Region2D {
    Region2D();
    Region2D(const Region2D &that);
    Region2D(const Coord2D &lower_left, const Coord2D &upper_right);
    ~Region2D();

    Region2D &operator=(const Region2D &that);
    bool IsExactlyEqualTo(const Region2D &that) const;
    void expandBy(const Coord2D &point);
    bool isInside(const Coord2D &point) const;
    float width() const;
    float height() const;

    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

struct Region3D {
    Region3D();
    Region3D(const Region3D &that);
    ~Region3D();

    Region3D &operator=(const Region3D &that);
    float width() const;
    float height() const;
    float depth() const;
    void expandBy(const Coord3D &point);
    bool isInRegionNoZ(const Coord3D *point) const;
    bool isInRegionWithZ(const Coord3D *point) const;
    void zero();

    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};
