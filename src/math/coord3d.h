#pragma once

#include "coord2d.h"

struct Coord3DBase {
    float x;
    float y;
    float z;
};

class Coord3D : public Coord3DBase {
public:
    Coord3D();
    Coord3D(const Coord3D &that);
    Coord3D(const Coord2D &that);
    Coord3D(const Coord3DBase &that);
    Coord3D(float x, float y, float z);
    Coord3D(int x, int y, int z);
    ~Coord3D();

    Coord3D &operator=(const Coord2D &that);
    Coord3D &operator=(const Coord2DBase &that);
    Coord3D &operator=(const Coord3DBase &that);

    Coord3D &Set(float x, float y, float z);
    Coord3D &Set2D(float x, float y);
    Coord3D &SetMaxVect();
    Coord3D &SetMinVect();
    Coord3D &SetXAxis();
    Coord3D &SetYAxis();
    Coord3D &SetZAxis();
    void zero();
    void set(float x, float y, float z);
    void set(const Coord3DBase *that);
    Coord3D &SetZero();
};
