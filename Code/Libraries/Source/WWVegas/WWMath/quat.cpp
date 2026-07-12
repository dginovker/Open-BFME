// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Quaternion routines, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/quat.cpp). Only functions located in the
// binary are defined here. Trackball, Fast_Slerp, Build_Quaternion(Matrix3D)
// and Randomize are absent/drifted in lotrbfme.exe and were dropped.
// project_to_sphere is kept (its only caller, Trackball, was dropped) by
// removing its `static` storage class so the compiler still emits it; the
// body is unchanged so its bytes are identical.
#include "quat.h"
#include "matrix3d.h"
#include "matrix4.h"
#include "wwmath.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define SLERP_EPSILON		0.001

static int _nxt[3] = { 1 , 2 , 0 };

Quaternion::Quaternion(const Vector3 & axis,float angle)
{
	float s = WWMath::Sin(angle/2);
	float c = WWMath::Cos(angle/2);
	X = s * axis.X;
	Y = s * axis.Y;
	Z = s * axis.Z;
	W = c;
}

void Quaternion::Normalize()
{
	float len2=X * X + Y * Y + Z * Z + W * W;
	if (0.0f == len2) {
		return;
	} else {
		float inv_mag = WWMath::Inv_Sqrt(len2);

		X *= inv_mag;
		Y *= inv_mag;
		Z *= inv_mag;
		W *= inv_mag;
	}
}

Quaternion & Quaternion::Make_Closest(const Quaternion & qto)
{
	float cos_t = qto.X * X + qto.Y * Y + qto.Z * Z + qto.W * W;

	// if we are on opposite hemisphere from qto, negate ourselves
	if (cos_t < 0.0) {
		X = -X;
		Y = -Y;
		Z = -Z;
		W = -W;
	}

	return *this;
}

Quaternion Axis_To_Quat(const Vector3 &a, float phi)
{
	Quaternion q;
	Vector3 tmp = a;

	tmp.Normalize();
	q[0] = tmp[0];
	q[1] = tmp[1];
	q[2] = tmp[2];

	q.Scale(WWMath::Sin(phi / 2.0f));
	q[3] =  WWMath::Cos(phi / 2.0f);

	return q;
}

void Slerp(Quaternion& res, const Quaternion & p,const Quaternion & q,float alpha)
{
	float beta;				// complementary interploation parameter
	float theta;				// angle between p and q
	//float sin_t
	float cos_t; 		// sine, cosine of theta
	float oo_sin_t;
	int qflip;					// use flip of q?

	// cos theta = dot product of p and q
	cos_t = p.X * q.X + p.Y * q.Y + p.Z * q.Z + p.W * q.W;

	// if q is on opposite hemisphere from A, use -B instead
	if (cos_t < 0.0f) {
		cos_t = -cos_t;
		qflip = true;
	} else {
		qflip = false;
	}

	if (1.0f - cos_t < WWMATH_EPSILON * WWMATH_EPSILON) {

		// if q is very close to p, just linearly interpolate
		// between the two.
		beta = 1.0f - alpha;

	} else {

		// normal slerp!
		theta = WWMath::Acos(cos_t);
		float sin_t = WWMath::Sin(theta);
		oo_sin_t = 1.0f / sin_t;
		beta = WWMath::Sin(theta - alpha*theta) * oo_sin_t;
		alpha = WWMath::Sin(alpha*theta) * oo_sin_t;
	}

	if (qflip) {
		alpha = -alpha;
	}

	res.X = beta*p.X + alpha*q.X;
	res.Y = beta*p.Y + alpha*q.Y;
	res.Z = beta*p.Z + alpha*q.Z;
	res.W = beta*p.W + alpha*q.W;
}

void Slerp_Setup(const Quaternion & p,const Quaternion & q,SlerpInfoStruct * slerpinfo)
{
	float cos_t;

	assert(slerpinfo != NULL);

	// cos theta = dot product of p and q
	cos_t = p.X * q.X + p.Y * q.Y + p.Z * q.Z + p.W * q.W;

	// if q is on opposite hemisphere from A, use -B instead
	if (cos_t < 0.0f) {
		cos_t = -cos_t;
		slerpinfo->Flip = true;
	} else {
		slerpinfo->Flip = false;
	}

	if (1.0f - cos_t < SLERP_EPSILON) {

		slerpinfo->Linear = true;
		slerpinfo->Theta = 0.0f;
		slerpinfo->SinT = 0.0f;

	} else {

		slerpinfo->Linear = false;
		slerpinfo->Theta = WWMath::Acos(cos_t);
		slerpinfo->SinT = WWMath::Sin(slerpinfo->Theta);

	}
}

Quaternion Cached_Slerp(const Quaternion & p,const Quaternion & q,float alpha,SlerpInfoStruct * slerpinfo)
{
	float beta;				// complementary interploation parameter
	float oo_sin_t;

	if (slerpinfo->Linear) {

		// if q is very close to p, just linearly interpolate
		// between the two.
		beta = 1.0f - alpha;

	} else {

		// normal slerp!
		oo_sin_t = 1.0f / slerpinfo->Theta;
		beta = WWMath::Sin(slerpinfo->Theta - alpha*slerpinfo->Theta) * oo_sin_t;
		alpha = WWMath::Sin(alpha*slerpinfo->Theta) * oo_sin_t;
	}

	if (slerpinfo->Flip) {
		alpha = -alpha;
	}

	Quaternion res;
	res.X = beta*p.X + alpha*q.X;
	res.Y = beta*p.Y + alpha*q.Y;
	res.Z = beta*p.Z + alpha*q.Z;
	res.W = beta*p.W + alpha*q.W;

	return res;
}

void Cached_Slerp(const Quaternion & p,const Quaternion & q,float alpha,SlerpInfoStruct * slerpinfo,Quaternion * set_q)
{
	float beta;				// complementary interploation parameter
	float oo_sin_t;

	if (slerpinfo->Linear) {

		// if q is very close to p, just linearly interpolate
		// between the two.
		beta = 1.0f - alpha;

	} else {

		// normal slerp!
		oo_sin_t = 1.0f / slerpinfo->Theta;
		beta = WWMath::Sin(slerpinfo->Theta - alpha*slerpinfo->Theta) * oo_sin_t;
		alpha = WWMath::Sin(alpha*slerpinfo->Theta) * oo_sin_t;
	}

	if (slerpinfo->Flip) {
		alpha = -alpha;
	}

	set_q->X = beta*p.X + alpha*q.X;
	set_q->Y = beta*p.Y + alpha*q.Y;
	set_q->Z = beta*p.Z + alpha*q.Z;
	set_q->W = beta*p.W + alpha*q.W;
}

Quaternion Build_Quaternion(const Matrix3 & mat)
{
	float tr,s;
	int i,j,k;
	Quaternion q;

	// sum the diagonal of the rotation matrix
	tr = mat[0][0] + mat[1][1] + mat[2][2];

	if (tr > 0.0) {

		s = sqrt(tr + 1.0);
		q[3] = s * 0.5;
		s = 0.5 / s;

		q[0] = (mat[2][1] - mat[1][2]) * s;
		q[1] = (mat[0][2] - mat[2][0]) * s;
		q[2] = (mat[1][0] - mat[0][1]) * s;

	} else {

		i = 0;
		if (mat[1][1] > mat[0][0]) i = 1;
		if (mat[2][2] > mat[i][i]) i = 2;

		j = _nxt[i];
		k = _nxt[j];

		s = sqrt( (mat[i][i] - (mat[j][j]+mat[k][k])) + 1.0);

		q[i] =	s * 0.5;

		if (s != 0.0) {
			s = 0.5/s;
		}

		q[3] = 	( mat[k][j] - mat[j][k] ) * s;
		q[j] =	( mat[j][i] + mat[i][j] ) * s;
		q[k] =	( mat[k][i] + mat[i][k] ) * s;
	}

	return q;
}

Quaternion Build_Quaternion(const Matrix4 & mat)
{
	float tr,s;
	int i,j,k;
	Quaternion q;

	// sum the diagonal of the rotation matrix
	tr = mat[0][0] + mat[1][1] + mat[2][2];

	if (tr > 0.0) {

		s = sqrt(tr + 1.0);
		q[3] = s * 0.5;
		s = 0.5 / s;

		q[0] = (mat[2][1] - mat[1][2]) * s;
		q[1] = (mat[0][2] - mat[2][0]) * s;
		q[2] = (mat[1][0] - mat[0][1]) * s;

	} else {

		i = 0;
		if (mat[1][1] > mat[0][0]) i = 1;
		if (mat[2][2] > mat[i][i]) i = 2;

		j = _nxt[i];
		k = _nxt[j];

		s = sqrt( (mat[i][i] - (mat[j][j]+mat[k][k])) + 1.0);

		q[i] =	s * 0.5;
		if (s != 0.0) {
			s = 0.5/s;
		}
		q[3] = 	( mat[k][j] - mat[j][k] ) * s;
		q[j] =	( mat[j][i] + mat[i][j] ) * s;
		q[k] =	( mat[k][i] + mat[i][k] ) * s;
	}

	return q;
}

Matrix3	Build_Matrix3(const Quaternion & q)
{
	Matrix3 m;

	m[0][0] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]));
	m[0][1] = (float)(2.0 * (q[0] * q[1] - q[2] * q[3]));
	m[0][2] = (float)(2.0 * (q[2] * q[0] + q[1] * q[3]));

	m[1][0] = (float)(2.0 * (q[0] * q[1] + q[2] * q[3]));
	m[1][1] = (float)(1.0 - 2.0f * (q[2] * q[2] + q[0] * q[0]));
	m[1][2] = (float)(2.0 * (q[1] * q[2] - q[0] * q[3]));

	m[2][0] = (float)(2.0 * (q[2] * q[0] - q[1] * q[3]));
	m[2][1] = (float)(2.0 * (q[1] * q[2] + q[0] * q[3]));
	m[2][2] =(float)(1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]));

	return m;
}

Matrix4 Build_Matrix4(const Quaternion & q)
{
	Matrix4 m;

	// initialize the rotation sub-matrix
	m[0][0] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]));
	m[0][1] = (float)(2.0 * (q[0] * q[1] - q[2] * q[3]));
	m[0][2] = (float)(2.0 * (q[2] * q[0] + q[1] * q[3]));

	m[1][0] = (float)(2.0 * (q[0] * q[1] + q[2] * q[3]));
	m[1][1] = (float)(1.0 - 2.0f * (q[2] * q[2] + q[0] * q[0]));
	m[1][2] = (float)(2.0 * (q[1] * q[2] - q[0] * q[3]));

	m[2][0] = (float)(2.0 * (q[2] * q[0] - q[1] * q[3]));
	m[2][1] = (float)(2.0 * (q[1] * q[2] + q[0] * q[3]));
	m[2][2] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]));

	// no translation
	m[0][3] = m[1][3] = m[2][3] = 0.0f;

	// last row
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
	m[3][3] = 1.0f;
	return m;
}

void Quaternion::Rotate_X(float theta)
{
	// TODO: optimize this
	*this = (*this) * Quaternion(Vector3(1,0,0),theta);
}

void Quaternion::Rotate_Y(float theta)
{
	// TODO: optimize this
	*this = (*this) * Quaternion(Vector3(0,1,0),theta);
}

void Quaternion::Rotate_Z(float theta)
{
	// TODO: optimize this
	*this = (*this) * Quaternion(Vector3(0,0,1),theta);
}

float project_to_sphere(float r, float x, float y)
{
	const float SQRT2 = 1.41421356f;
	float t, z;
	float d = WWMath::Sqrt(x * x + y * y);

	if (d < r * (SQRT2/(2.0f)))			// inside sphere
		z = WWMath::Sqrt(r * r - d * d);
	else {								// on hyperbola
		t = r / SQRT2;
		z = t * t / d;
	}

	return z;
}
