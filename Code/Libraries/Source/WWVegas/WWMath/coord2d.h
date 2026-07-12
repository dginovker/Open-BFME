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
    float operator*(const Coord2D &that) const;
    float operator*(const Coord3DBase &that) const;
    Coord2D &operator*=(float scale);
    Coord2D &operator/=(float divisor);
    Coord2D &operator+=(const Coord2D &that);
    Coord2D &operator+=(const Coord3DBase &that);
    Coord2D &operator-=(const Coord2D &that);
    Coord2D &operator-=(const Coord3DBase &that);

    Coord2D &Add(const Coord2D &that);
    Coord2D &Add(const Coord3DBase &that);
    float GetLength() const;
    float GetLengthEstimate() const;
    float GetLengthSqrd() const;
    float toAngle() const;
    Coord2D &Rotate(float angle);
    bool IsExactlyEqualTo(const Coord2D &that) const;
    float length() const;
    Coord2D &Negate();
    void normalize();
    float Normalize();
    Coord2D &Rotate(float sine, float cosine);
    Coord2D &Rotate(Coord2D &coord, float sine, float cosine);
    Coord2D &Rotate(const Coord2D &source, float angle);
    Coord2D &Scale(float scale);
    Coord2D &Set(float x, float y);
    Coord2D &SetMaxVect();
    Coord2D &SetMinVect();
    Coord2D &SetXAxis();
    Coord2D &SetYAxis();
    Coord2D &SetZero();
    Coord2D &Sub(const Coord2D &that);
    Coord2D &Sub(const Coord3DBase &that);
};
