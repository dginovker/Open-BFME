// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Matrix3D transform class, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/matrix3d.cpp). Only the functions located in
// the binary are defined here; Multiply and Lerp are omitted because the retail
// build's inlining/codegen for them drifted from this source (see report).

#include "matrix3d.h"

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "vector3.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"
#include "D3dx8math.h"

// some static matrices which are sometimes useful
const Matrix3D Matrix3D::Identity
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D Matrix3D::RotateX90
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0,
	0.0,	1.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateX180
(
	1.0,	0.0,	0.0,	0.0,
	0.0, -1.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0
);

const Matrix3D Matrix3D::RotateX270
(
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0,
	0.0, -1.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateY90
(
	0.0,	0.0,	1.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
  -1.0,	0.0,	0.0,	0.0
);

const Matrix3D Matrix3D::RotateY180
(
  -1.0,	0.0,	0.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	0.0,	0.0, -1.0,	0.0
);

const Matrix3D Matrix3D::RotateY270
(
	0.0,	0.0, -1.0,	0.0,
	0.0,	1.0,	0.0,	0.0,
	1.0,	0.0,	0.0,	0.0
);

const Matrix3D	Matrix3D::RotateZ90
(
	0.0, -1.0,	0.0,	0.0,
	1.0,	0.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D Matrix3D::RotateZ180
(
  -1.0,	0.0,	0.0,	0.0,
	0.0, -1.0,	0.0,	0.0,
	0.0,	0.0,	1.0,	0.0
);

const Matrix3D	Matrix3D::RotateZ270
(
	0.0,	1.0,	0.0,	0.0,
  -1.0,	0.0,	0.0,	0.0,
 	0.0,	0.0,	1.0,	0.0
);


void Matrix3D::Set(const Matrix3 & rot,const Vector3 & pos)
{
	Row[0].Set( rot[0][0], rot[0][1], rot[0][2], pos[0]);
	Row[1].Set( rot[1][0], rot[1][1], rot[1][2], pos[1]);
	Row[2].Set( rot[2][0], rot[2][1], rot[2][2], pos[2]);
}


void Matrix3D::Set(const Quaternion & rot,const Vector3 & pos)
{
   Set_Rotation(rot);
   Set_Translation(pos);
}


void Matrix3D::Set_Rotation(const Matrix3 & m)
{
	Row[0][0] = m[0][0];
	Row[0][1] = m[0][1];
	Row[0][2] = m[0][2];

	Row[1][0] = m[1][0];
	Row[1][1] = m[1][1];
	Row[1][2] = m[1][2];

	Row[2][0] = m[2][0];
	Row[2][1] = m[2][1];
	Row[2][2] = m[2][2];
}


void Matrix3D::Set_Rotation(const Quaternion & q)
{
	Row[0][0] = (float)(1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]));
	Row[0][1] = (float)(2.0 * (q[0] * q[1] - q[2] * q[3]));
	Row[0][2] = (float)(2.0 * (q[2] * q[0] + q[1] * q[3]));

	Row[1][0] = (float)(2.0 * (q[0] * q[1] + q[2] * q[3]));
	Row[1][1] = (float)(1.0 - 2.0f * (q[2] * q[2] + q[0] * q[0]));
	Row[1][2] = (float)(2.0 * (q[1] * q[2] - q[0] * q[3]));

	Row[2][0] = (float)(2.0 * (q[2] * q[0] - q[1] * q[3]));
	Row[2][1] = (float)(2.0 * (q[1] * q[2] + q[0] * q[3]));
	Row[2][2] =(float)(1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]));
}


float Matrix3D::Get_X_Rotation(void) const
{
	return (WWMath::Atan2(Row[2][1], Row[1][1]));
}


float Matrix3D::Get_Y_Rotation(void) const
{
	return (WWMath::Atan2(Row[0][2], Row[2][2]));
}


float Matrix3D::Get_Z_Rotation(void) const
{
	return (WWMath::Atan2(Row[1][0], Row[0][0]));
}


Vector3 Matrix3D::Rotate_Vector(const Vector3 &vect) const
{
	return Vector3(
		(Row[0][0]*vect[0] + Row[0][1]*vect[1] + Row[0][2]*vect[2]),
		(Row[1][0]*vect[0] + Row[1][1]*vect[1] + Row[1][2]*vect[2]),
		(Row[2][0]*vect[0] + Row[2][1]*vect[1] + Row[2][2]*vect[2])
	);
}


Vector3 Matrix3D::Inverse_Rotate_Vector(const Vector3 &vect) const
{
	return Vector3(
		(Row[0][0]*vect[0] + Row[1][0]*vect[1] + Row[2][0]*vect[2]),
		(Row[0][1]*vect[0] + Row[1][1]*vect[1] + Row[2][1]*vect[2]),
		(Row[0][2]*vect[0] + Row[1][2]*vect[1] + Row[2][2]*vect[2])
	);
}

void Matrix3D::Look_At(const Vector3 &p,const Vector3 &t,float roll)
{
	float	dx,dy,dz;	//vector from p to t
	float	len1,len2;
	float	sinp,cosp;	//sine and cosine of the pitch ("up-down" tilt about x)
	float	siny,cosy;	//sine and cosine of the yaw ("left-right"tilt about z)

	dx = (t[0] - p[0]);
	dy = (t[1] - p[1]);
	dz = (t[2] - p[2]);

	len1 = (float)WWMath::Sqrt(dx*dx + dy*dy + dz*dz);
	len2 = (float)WWMath::Sqrt(dx*dx + dy*dy);

	if (len1 != 0.0f) {
		sinp = dz/len1;
		cosp = len2/len1;
	} else {
		sinp = 0.0f;
		cosp = 1.0f;
	}

	if (len2 != 0.0f) {
		siny = dy/len2;
		cosy = dx/len2;
	} else {
		siny = 0.0f;
		cosy = 1.0f;
	}

	// init the matrix with position p and -z pointing down +x and +y up
	Row[0].X = 0.0f;	Row[0].Y = 0.0f;	Row[0].Z = -1.0f;
	Row[1].X = -1.0f;	Row[1].Y = 0.0f;	Row[1].Z = 0.0f;
	Row[2].X = 0.0f;	Row[2].Y = 1.0f;	Row[2].Z = 0.0f;

	Row[0].W = p.X;
	Row[1].W = p.Y;
	Row[2].W = p.Z;

	// Yaw rotation to make the matrix look at the projection of the target
	// into the x-y plane
	Rotate_Y(siny,cosy);

	// rotate about local x axis to pitch up to the targets position
	Rotate_X(sinp,cosp);

	// roll about the local z axis (negate since we look down -z)
	Rotate_Z(-roll);
}

// Create a matrix given a position and a direction (x axis will point in direction)
// Make sure you pass in UNITIZED direction!!!
void Matrix3D::buildTransformMatrix( const Vector3 &pos, const Vector3 &dir )
{
	float sinp, cosp;	// sine and cosine of the pitch ("up-down" tilt about y)
	float siny, cosy;	// sine and cosine of the yaw ("left-right"tilt about z)

	float len2 = (float)sqrt( (dir.X * dir.X) + (dir.Y * dir.Y) );

	sinp = dir.Z;
	cosp = len2;

	if( len2 != 0.0f )
	{
		siny = dir.Y / len2;
		cosy = dir.X / len2;
	}
	else
	{
		siny = 0.0f;
		cosy = 1.0f;
	}

	Make_Identity();
	Translate( pos );

	// Yaw rotation to projection of target in x-y plane
	Rotate_Z( siny, cosy );

	// Pitch rotation
	Rotate_Y( -sinp, cosp );
}

void Matrix3D::Obj_Look_At(const Vector3 &p,const Vector3 &t,float roll)
{
	float	dx,dy,dz;	//vector from p to t
	float	len1,len2;
	float	sinp,cosp;	//sine and cosine of the pitch ("up-down" tilt about y)
	float	siny,cosy;	//sine and cosine of the yaw ("left-right"tilt about z)

	dx = (t[0] - p[0]);
	dy = (t[1] - p[1]);
	dz = (t[2] - p[2]);

	len1 = (float)sqrt(dx*dx + dy*dy + dz*dz);
	len2 = (float)sqrt(dx*dx + dy*dy);

	if (len1 != 0.0f) {
		sinp = dz/len1;
		cosp = len2/len1;
	} else {
		sinp = 0.0f;
		cosp = 1.0f;
	}

	if (len2 != 0.0f) {
		siny = dy/len2;
		cosy = dx/len2;
	} else {
		siny = 0.0f;
		cosy = 1.0f;
	}

	Make_Identity();
	Translate(p);

	// Yaw rotation to projection of target in x-y plane
	Rotate_Z(siny,cosy);

	// Pitch rotation
	Rotate_Y(-sinp,cosp);

	// Roll rotation
	Rotate_X(roll);
}


void Matrix3D::Get_Inverse(Matrix3D & inv) const
{
	// TODO: Implement the general purpose inverse function here (once we need it :-)
	//Get_Orthogonal_Inverse(inv);

	Matrix4	mat4(*this);
	Matrix4	mat4Inv;

	float det;
	D3DXMatrixInverse((D3DXMATRIX *)&mat4Inv, &det, (D3DXMATRIX*)&mat4);

	inv.Row[0][0]=mat4Inv[0][0];
	inv.Row[0][1]=mat4Inv[0][1];
	inv.Row[0][2]=mat4Inv[0][2];
	inv.Row[0][3]=mat4Inv[0][3];

	inv.Row[1][0]=mat4Inv[1][0];
	inv.Row[1][1]=mat4Inv[1][1];
	inv.Row[1][2]=mat4Inv[1][2];
	inv.Row[1][3]=mat4Inv[1][3];

	inv.Row[2][0]=mat4Inv[2][0];
	inv.Row[2][1]=mat4Inv[2][1];
	inv.Row[2][2]=mat4Inv[2][2];
	inv.Row[2][3]=mat4Inv[2][3];
}

void Matrix3D::Get_Orthogonal_Inverse(Matrix3D & inv) const
{
	// Transposing the rotation submatrix
	inv.Row[0][0] = Row[0][0];
	inv.Row[0][1] = Row[1][0];
	inv.Row[0][2] = Row[2][0];

	inv.Row[1][0] = Row[0][1];
	inv.Row[1][1] = Row[1][1];
	inv.Row[1][2] = Row[2][1];

	inv.Row[2][0] = Row[0][2];
	inv.Row[2][1] = Row[1][2];
	inv.Row[2][2] = Row[2][2];

	// Now, calculate translation portion of matrix:
	// T' = -R'T
	Vector3 trans = Get_Translation();
	trans = inv.Rotate_Vector(trans);
	trans = -trans;

	inv.Row[0][3] = trans[0];
	inv.Row[1][3] = trans[1];
	inv.Row[2][3] = trans[2];
}

void Matrix3D::Copy_3x3_Matrix(float matrix[3][3])
{
	Row[0][0] = matrix[0][0];
	Row[0][1] = matrix[0][1];
	Row[0][2] = matrix[0][2];
	Row[0][3] = 0;
	Row[1][0] = matrix[1][0];
	Row[1][1] = matrix[1][1];
	Row[1][2] = matrix[1][2];
	Row[1][3] = 0;
	Row[2][0] = matrix[2][0];
	Row[2][1] = matrix[2][1];
	Row[2][2] = matrix[2][2];
	Row[2][3] = 0;
}


void Matrix3D::Transform_Min_Max_AABox
(
	const Vector3 &		min,
	const Vector3 &		max,
	Vector3 *				set_min,
	Vector3 *				set_max
) const
{
	WWASSERT(set_min != &min);
	WWASSERT(set_max != &max);

	float tmp0,tmp1;

	// init the min and max to the translation of the transform
	set_min->X = set_max->X = Row[0][3];
	set_min->Y = set_max->Y = Row[1][3];
	set_min->Z = set_max->Z = Row[2][3];

	// now push them both out by the projections of the original intervals
	for (int i=0; i<3; i++) {

		for (int j=0; j<3; j++) {

			tmp0 = Row[i][j] * min[j];
			tmp1 = Row[i][j] * max[j];

			if (tmp0 < tmp1) {

				(*set_min)[i] += tmp0;
				(*set_max)[i] += tmp1;

			} else {

				(*set_min)[i] += tmp1;
				(*set_max)[i] += tmp0;

			}
		}
	}
}


void Matrix3D::Transform_Center_Extent_AABox
(
	const Vector3 &		center,
	const Vector3 &		extent,
	Vector3 *				set_center,
	Vector3 *				set_extent
) const
{
	WWASSERT(set_center != &center);
	WWASSERT(set_extent != &extent);

	// push each extent out to the projections of the original extents
	for (int i=0; i<3; i++) {

		// start the center out at the translation portion of the matrix
		// and the extent at zero
		(*set_center)[i] = Row[i][3];
		(*set_extent)[i] = 0.0f;

		for (int j=0; j<3; j++) {

			(*set_center)[i] += Row[i][j] * center[j];
			(*set_extent)[i] += WWMath::Fabs(Row[i][j] * extent[j]);

		}
	}
}


int Matrix3D::Is_Orthogonal(void) const
{
	Vector3 x(Row[0].X,Row[0].Y,Row[0].Z);
	Vector3 y(Row[1].X,Row[1].Y,Row[1].Z);
	Vector3 z(Row[2].X,Row[2].Y,Row[2].Z);

	if (Vector3::Dot_Product(x,y) > WWMATH_EPSILON) return 0;
	if (Vector3::Dot_Product(y,z) > WWMATH_EPSILON) return 0;
	if (Vector3::Dot_Product(z,x) > WWMATH_EPSILON) return 0;

	if (WWMath::Fabs(x.Length2() - 1.0f) > WWMATH_EPSILON) return 0;
	if (WWMath::Fabs(y.Length2() - 1.0f) > WWMATH_EPSILON) return 0;
	if (WWMath::Fabs(z.Length2() - 1.0f) > WWMATH_EPSILON) return 0;

	return 1;
}

void Matrix3D::Re_Orthogonalize(void)
{
	Vector3 x(Row[0][0],Row[0][1],Row[0][2]);
	Vector3 y(Row[1][0],Row[1][1],Row[1][2]);
	Vector3 z;

	(Vector3::Cross_Product(x,y,&z));
	(Vector3::Cross_Product(z,x,&y));

	float len = x.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		x *= 1.0f/len;
	}

	len = y.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		y *= 1.0f/len;
	}

	len = z.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		z *= 1.0f/len;
	}

	Row[0][0] = x.X;
	Row[0][1] = x.Y;
	Row[0][2] = x.Z;

	Row[1][0] = y.X;
	Row[1][1] = y.Y;
	Row[1][2] = y.Z;

	Row[2][0] = z.X;
	Row[2][1] = z.Y;
	Row[2][2] = z.Z;
}


bool Matrix3D::Solve_Linear_System(Matrix3D & system)
{
	/*
	** Gauss-Jordan Elimination
	** We repeatedly replace rows in the matrix with a linear combination of itself and
	** another row in the system in order to reduce the matrix to the identity matrix.
	** TODO: optimize away all unnecessary math operations!
	*/
	if (system[0][0] == 0.0f) return false;
	system[0] *= 1.0f / system[0][0];				// (0,0) now equals 1.0  (row,col)
	system[1] -= system[1][0] * system[0];			// (1,0) now equals 0.0
	system[2] -= system[2][0] * system[0];			// (2,0) now equals 0.0

	if (system[1][1] == 0.0f) return false;
	system[1] *= 1.0f / system[1][1];				// (1,1) now equals 1.0
	system[2] -= system[2][1] * system[1];			// (2,1) now equals 0.0

	if (system[2][2] == 0.0f) return false;
	system[2] *= 1.0f / system[2][2];				// (2,2) now equals 1.0, and we already have one answer

	system[1] -= system[1][2] * system[2];			// (1,2) now equals 0.0, and we have another answer
	system[0] -= system[0][2] * system[2];			// (0,2) now equals 0.0

	system[0] -= system[0][1] * system[1];			// (0,1) now equals 0.0, and we are done!

	return true;
}
