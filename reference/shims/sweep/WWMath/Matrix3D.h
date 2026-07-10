/*
**  WWMath/Matrix3D.h shim — minimal declaration for sweep compilation
**  The real Matrix3D is a WWSMath type.
*/

#pragma once

#ifndef _MATRIX3D_H
#define _MATRIX3D_H

#include "../../../../../CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h"

class Matrix3D
{
public:
	float Row[3][3];

	static void Transform_Vector(const Matrix3D& tm, const struct Vector3& in, struct Vector3* out);
	static void Rotate_Vector(const Matrix3D& tm, const struct Vector3& in, struct Vector3* out);
	void Make_Identity();
};

#endif
