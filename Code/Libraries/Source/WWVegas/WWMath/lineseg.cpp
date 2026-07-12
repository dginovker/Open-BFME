// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WWMath line-segment routines, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/lineseg.cpp). Built with NDEBUG because the
// retail executable compiled the vector asserts (e.g. in Vector3::Cross_Product,
// reached from Find_Intersection) out.
#include "lineseg.h"

#include "matrix3d.h"

void LineSegClass::Set(const LineSegClass & that,const Matrix3D & tm)
{
	/*
	** Transform P0 and P1
	*/
	Matrix3D::Transform_Vector(tm,that.P0,&P0);
	Matrix3D::Transform_Vector(tm,that.P1,&P1);

	/*
	** Just calculate DP
	*/
	DP = P1 - P0;

	/*
	** Rotate the direction vector
	*/
	Matrix3D::Rotate_Vector(tm,that.Dir,&Dir);

	/*
	** Length should be un-changed
	*/
	Length = that.Length;
}

void LineSegClass::Set_Random(const Vector3 & min,const Vector3 & max)
{
	float frac;

	frac = WWMath::Random_Float();
	P0.X = min.X + frac * (max.X - min.X);
	frac = WWMath::Random_Float();
	P0.Y = min.Y + frac * (max.Y - min.Y);
	frac = WWMath::Random_Float();
	P0.Z = min.Z + frac * (max.Z - min.Z);

	frac = WWMath::Random_Float();
	P1.X = min.X + frac * (max.X - min.X);
	frac = WWMath::Random_Float();
	P1.Y = min.Y + frac * (max.Y - min.Y);
	frac = WWMath::Random_Float();
	P1.Z = min.Z + frac * (max.Z - min.Z);

	DP = P1 - P0;
	Dir = DP;
	Dir.Normalize();
	Length = DP.Length();
}


Vector3 LineSegClass::Find_Point_Closest_To(const Vector3 &pos) const
{
	// Get a vector from one line endpoint to point in question.
	Vector3 v_0_pos = (pos - P0);
	float dotprod = Vector3::Dot_Product(Dir, v_0_pos);

	// Check to see if point is past either of the endpoints.
	// (Unable to draw a perpendicular line from the point to the line segment.)
	if (dotprod <= 0.0) {
		return(P0);
	} else if (dotprod >= Length) {
		return(P1);
	}

	// Find point on line seg that is closest to pos passed in.
	Vector3 point = P0 + (dotprod * Dir);
	return(point);
}


bool
LineSegClass::Find_Intersection
(
	const LineSegClass &	other_line,
	Vector3 *				p1,
	float	*					fraction1,
	Vector3 *				p2,
	float *					fraction2
) const
{
	bool retval = false;

#ifdef ALLOW_TEMPORARIES
	Vector3 cross1 = Vector3::Cross_Product (Dir, other_line.Dir);
	Vector3 cross2 = Vector3::Cross_Product (other_line.P0 - P0, other_line.Dir);
	float top1		= cross2 * cross1;
	float bottom1	= cross1 * cross1;

	Vector3 cross3 = Vector3::Cross_Product (other_line.Dir, Dir);
	Vector3 cross4 = Vector3::Cross_Product (P0 - other_line.P0, Dir);
	float top2		= cross4 * cross3;
	float bottom2	= cross3 * cross3;
#else
	Vector3 cross1, cross2, cross3, cross4;

	Vector3::Cross_Product(Dir, other_line.Dir, &cross1);
	Vector3::Cross_Product(other_line.P0 - P0, other_line.Dir, &cross2);
	float top1		= Vector3::Dot_Product(cross2, cross1);
	float bottom1	= Vector3::Dot_Product(cross1, cross1);

	Vector3::Cross_Product(other_line.Dir, Dir, &cross3);
	Vector3::Cross_Product(P0 - other_line.P0, Dir, &cross4);
	float top2		= Vector3::Dot_Product(cross4, cross3);
	float bottom2	= Vector3::Dot_Product(cross3, cross3);
#endif

	//
	//	If either of the divisors are 0, then the lines are parallel
	//
	if (bottom1 != 0 && bottom2 != 0) {
		float length1 = top1 / bottom1;
		float length2 = top2 / bottom2;

		//
		//	Calculate the closest points on both lines.
		// Note:  If the points are the same, then the lines intersect.
		//
		(*p1) = P0 + (Dir * length1);
		(*p2) = other_line.P0 + (other_line.Dir * length2);

		//
		//	Return the fractions if they caller wants them
		//
		if (fraction1 != NULL) {
			(*fraction1) = length1 / Length;
		}

		if (fraction2 != NULL) {
			(*fraction2) = length2 / Length;
		}

		retval = true;
	}

	return retval;
}
