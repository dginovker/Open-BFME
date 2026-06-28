#pragma once

#include "coord2d.h"
#include "coord3d.h"

struct IRegion2D {
    bool operator==(const IRegion2D &that) const;
    bool operator!=(const IRegion2D &that) const;

    int width() const;
    int height() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

struct IRegion3D {
    IRegion3D();

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

    bool IsExactlyEqualTo(const Region2D &that) const;
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

    float width() const;
    float height() const;
    float depth() const;
    void zero();

    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};
