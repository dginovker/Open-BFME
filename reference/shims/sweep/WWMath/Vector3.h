/*
**  WWMath/Vector3.h shim — minimal declaration for sweep compilation
*/

#pragma once

#ifndef _VECTOR3_H
#define _VECTOR3_H

struct Vector3
{
	float X, Y, Z;

	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

#endif
