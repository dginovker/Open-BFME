#pragma once

#include "coord3d.h"

class Matrix4D {
public:
    Matrix4D();
    Matrix4D(const Matrix4D &that);
    Matrix4D(bool identity);
    Matrix4D(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    Matrix4D &operator=(const Matrix4D &that);
    Matrix4D &operator*=(float scale);
    Matrix4D &operator+=(const Matrix4D &that);
    Matrix4D &operator-=(const Matrix4D &that);

    Coord3D &GetXVector(Coord3D &out) const;
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &GetTranslationVector(Coord3D &out) const;
    Matrix4D &Set(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
    Matrix4D &SetIdentity();

    float values[16];
};
