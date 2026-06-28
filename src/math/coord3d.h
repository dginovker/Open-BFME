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
    bool operator==(const Coord3D &that) const;
    float operator*(const Coord2D &that) const;
    float operator*(const Coord3DBase &that) const;
    Coord3D &operator*=(float scale);
    Coord3D &operator+=(const Coord2D &that);
    Coord3D &operator+=(const Coord3DBase &that);
    Coord3D &operator-=(const Coord2D &that);
    Coord3D &operator-=(const Coord3DBase &that);

    Coord3D &Add(const Coord2D &that);
    Coord3D &Add(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Add(const Coord3DBase &that);
    Coord3D &Add(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Add(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Add2D(const Coord3DBase &that);
    Coord3D &Add2D(const Coord3DBase &left, const Coord3DBase &right);
    bool equals(const Coord3DBase &that) const;
    bool IsExactlyEqualTo(const Coord3D &that) const;
    float lengthSqr() const;
    Coord3D &Negate();
    Coord3D &Scale(float scale);
    Coord3D &Scale(const Coord3DBase &that, float scale);
    Coord3D &Scale2D(float scale);
    Coord3D &Scale2D(const Coord3DBase &that, float scale);
    Coord3D &Set(float x, float y, float z);
    Coord3D &Set2D(float x, float y);
    Coord3D &SetMaxVect();
    Coord3D &SetMinVect();
    Coord3D &SetXAxis();
    Coord3D &SetYAxis();
    Coord3D &SetZAxis();
    void zero();
    void add(const Coord3DBase *that);
    void scale(float scale);
    void set(float x, float y, float z);
    void set(const Coord3DBase *that);
    void sub(const Coord3DBase *that);
    Coord3D &SetZero();
    Coord3D &Sub(const Coord2D &that);
    Coord3D &Sub(const Coord2D &left, const Coord3DBase &right);
    Coord3D &Sub(const Coord3DBase &that);
    Coord3D &Sub(const Coord3DBase &left, const Coord2D &right);
    Coord3D &Sub(const Coord3DBase &left, const Coord3DBase &right);
    Coord3D &Sub2D(const Coord3DBase &that);
    Coord3D &Sub2D(const Coord3DBase &left, const Coord3DBase &right);
};
