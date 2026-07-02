// CollisionMath line-segment collision routines, verbatim from the Generals
// reference (Libraries/Source/WWVegas/WWMath/colmathline.cpp). The line-vs-AABox
// and line-vs-OBBox Collide (and their shared Test_Aligned_Box helper +
// BoxTestStruct/_box_normal table) are omitted: BFME built those two with different
// inlining, so they drift and can't be byte-matched here.
#include "colmath.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"

bool CollisionMath::Collide(const LineSegClass & line,const AAPlaneClass & plane,CastResultStruct * result)
{
	float num,den,t;

	den = line.Get_DP()[plane.Normal];

	/*
	** Check if line is parallel to this plane
	*/
	if (den == 0.0f) {
		return false;
	}

	num = -(line.Get_P0()[plane.Normal] - plane.Dist);
	t = num/den;

	/*
	** If t is not between 0 and 1, the line containing the segment intersects
	** the plane but the segment does not
	*/
	if ((t < 0.0f) || (t > 1.0f)) {
		return false;
	}

	/*
	** Ok, we hit the plane!
	*/
	if (t < result->Fraction) {
		result->Fraction = t;
		result->Normal.Set(0,0,0);
		result->Normal[plane.Normal] = 1.0f;
		return true;
	}
	return false;
}

bool CollisionMath::Collide(const LineSegClass & line,const PlaneClass & plane,CastResultStruct * result)
{
	float num,den,t;
	den = Vector3::Dot_Product(plane.N,line.Get_DP());

	/*
	** If the denominator is zero, the ray is parallel to the plane
	*/
	if (den == 0.0f) {
		return false;
	}

	num = -(Vector3::Dot_Product(plane.N,line.Get_P0()) - plane.D);
	t = num/den;

	/*
	** If t is not between 0 and 1, the line containing the segment intersects
	** the plane but the segment does not
	*/
	if ((t < 0.0f) || (t > 1.0f)) {
		return false;
	}

	/*
	** Ok, we hit the plane!
	*/
	if (t < result->Fraction) {
		result->Fraction = t;
		result->Normal = plane.N;

		/*
		** if user is asking for the point, compute it.
		*/
		if (result->ComputeContactPoint) {
			result->ContactPoint = line.Get_P0() + result->Fraction * line.Get_DP();
		}
		return true;
	}
	return false;
}

bool CollisionMath::Collide(const LineSegClass & line,const TriClass & tri,CastResultStruct * res)
{
	TRACK_COLLISION_RAY_TRI;

	/*
	** Compute intersection of the line with the plane of the polygon
	*/
	PlaneClass plane(*tri.N,*tri.V[0]);
	Vector3 ipoint;
	float num,den,t;

	den = Vector3::Dot_Product(plane.N,line.Get_DP());
	
	/*
	** If the denominator is zero, the ray is parallel to the plane
	*/
	if (den == 0.0f) {
		return false;
	}
	num = -(Vector3::Dot_Product(plane.N,line.Get_P0()) - plane.D);
	t = num/den;

	/*
	** If t is not between 0 and 1, the line containing the segment intersects
	** the plane but the segment does not
	*/
	if ((t < 0.0f) || (t > 1.0f)) {
		return false;
	}

	ipoint = line.Get_P0() + t*line.Get_DP();

	/*
	** Check if this point is inside the triangle
	*/
	if (!tri.Contains_Point(ipoint)) {
		return false;
	}

	/*
	** Ok, we hit the triangle, set the collision results
	*/
	if (t < res->Fraction) {
		res->Fraction = t;
		res->Normal = plane.N;
		if (res->ComputeContactPoint) {
			res->ContactPoint = line.Get_P0() + res->Fraction * line.Get_DP();
		}
		TRACK_COLLISION_RAY_TRI_HIT;
		return true;
	}
	return false;
}

bool CollisionMath::Collide(const LineSegClass & line,const SphereClass & sphere,CastResultStruct * res)
{
	// this game from graphics gems 1, page 388
	// intersection of a ray with a sphere
	Vector3 dc = sphere.Center - line.Get_P0();
	float clen = Vector3::Dot_Product((dc) , line.Get_Dir());
	float disc = (sphere.Radius * sphere.Radius) - (dc.Length2() - clen*clen);
	if (disc < 0.0f) {
		return false;
	} else {
		float d = WWMath::Sqrt(disc);
		float frac = (clen - d) / line.Get_Length();
		if (frac<0.0f)
			frac = (clen + d) / line.Get_Length();
		if (frac<0.0f) return false;
		if (frac < res->Fraction) {

			res->Fraction = frac;

			Vector3 p = line.Get_P0() + (clen - d)*line.Get_Dir();
			Vector3 norm = p - sphere.Center;
			norm /= sphere.Radius;
			
			res->Normal = norm;
			if (res->ComputeContactPoint) {
				res->ContactPoint = line.Get_P0() + res->Fraction * line.Get_DP();
			}
			return true;
		}
	}
	return false;
}
