#pragma once

struct Coord3DBase;

struct Coord2DBase {
    Coord2DBase &operator=(const Coord2DBase &that);

    float x;
    float y;
};

class Coord2D : public Coord2DBase {
public:
    Coord2D();
    Coord2D(const Coord2D &that);
    Coord2D(const Coord2DBase &that);
    Coord2D(const Coord3DBase &that);
    Coord2D(float x, float y);
    Coord2D(int x, int y);
    ~Coord2D();

    Coord2D &operator=(const Coord2D &that);
    Coord2D &operator=(const Coord2DBase &that);
    Coord2D &operator=(const Coord3DBase &that);

    Coord2D &Set(float x, float y);
    Coord2D &SetMaxVect();
    Coord2D &SetMinVect();
    Coord2D &SetXAxis();
    Coord2D &SetYAxis();
    Coord2D &SetZero();
};
