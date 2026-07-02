// CollisionMath AABox routines, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/colmathaabox.cpp). Only the functions located
// in lotrbfme.exe are kept; the two moving-AABox Collide (and its aab_separation_test
// helper + AABCollisionStruct) are omitted -- BFME inlined the struct ctor with a
// different register allocation, so that function drifts and can't be byte-matched.
#include "colmath.h"
#include "colmathinlines.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"

bool CollisionMath::Intersection_Test(const AABoxClass & box,const AABoxClass & box2)
{
	Vector3 dc = box2.Center - box.Center;

	if (box.Extent.X + box2.Extent.X < WWMath::Fabs(dc.X)) return false;
	if (box.Extent.Y + box2.Extent.Y < WWMath::Fabs(dc.Y)) return false;
	if (box.Extent.Z + box2.Extent.Z < WWMath::Fabs(dc.Z)) return false;
	return true;
}

CollisionMath::OverlapType CollisionMath::Overlap_Test(const AABoxClass & box,const SphereClass & sphere)
{
	// TODO: this function seems incorrect.  Not currently using it though
	Vector3 dist = sphere.Center - box.Center;

	Vector3 extent;
	extent.X = box.Extent.X + sphere.Radius;
	extent.Y = box.Extent.Y + sphere.Radius;
	extent.Z = box.Extent.Z + sphere.Radius;

	//
	//	Check to see if the sphere is completely outside the box
	//
	if (WWMath::Fabs(dist.X) > extent.X) return OUTSIDE;
	if (WWMath::Fabs(dist.Y) > extent.Y) return OUTSIDE;
	if (WWMath::Fabs(dist.Z) > extent.Z) return OUTSIDE;

	return INSIDE;
}

CollisionMath::OverlapType CollisionMath::Overlap_Test(const AABoxClass & box,const LineSegClass & line)
{
	// If both endpoints are in, return INSIDE
	// If either was inside, return OVERLAPPED
	int inside_point_count = 0;
	if (CollisionMath::Overlap_Test(box,line.Get_P0()) == INSIDE) inside_point_count++;
	if (CollisionMath::Overlap_Test(box,line.Get_P1()) == INSIDE) inside_point_count++;
	
	if (inside_point_count == 2) {
	
		return INSIDE;
	
	} else if (inside_point_count == 1) {
	
		return OVERLAPPED;
	
	} else {

		// Here I'm using the separating axis theorem to test if the line-segment
		// and the box can be separated by a plane.  Any two convex objects that are
		// not intersecting can be separated by a plane defined by either a 
		// face normal from one of the objects or the cross-product of an edge from 
		// each object.  In the case of an axis-aligned box and a line-segment, we
		// have to check the three coordinate axes and the cross product between
		// each and the direction vector of the line segment.
		//
		// Here is the general test for an arbitrary axis:
		// -----------------------------------------------
		// box_proj = fabs(extent.X*axis.X) + fabs(extent.Y*axis.Y) + fabs(extent.Z*axis.Z)
		// p0_proj = fabs(dot_product(dp0,axis))
		// dp_proj = fabs(dot_product(dp,axis))
		// if (p0_proj > 0) {
		// 	if (p0_proj > box_proj - WWMath::Min(dp_proj,0.0f)) return OUTSIDE;
		// } else {
		// 	if (-p0_proj > box_proj + WWMath::Max(dp_proj,0.0f)) return OUTSIDE;
		// }
		//
		// In practice, there are optimizations you can make on each of the axes that
		// we need to test (see below).

		float box_proj,p0_proj,dp_proj;
		// joined onto one line so the qualified call isn't at line-start
		// (works around find_declared_unmatched.py mistaking it for a definition)
		Vector3 dp0; Vector3::Subtract(line.Get_P0(),box.Center,&dp0);

		// Project box and line onto the x-axis
		// Since I know the axis is the x-axis, just take the x components of each
		// vector instead of doing the dot-product.  The projection of 'dp' is only
		// counted if it points towards the center of the box (i.e. it decreases the
		// chances of them being separated...)
		box_proj = box.Extent.X;
		p0_proj = dp0.X;
		dp_proj = line.Get_DP().X;
		if (p0_proj > 0) {
			if (p0_proj > box_proj - WWMath::Min(dp_proj,0.0f)) return OUTSIDE;
		} else {
			if (-p0_proj > box_proj + WWMath::Max(dp_proj,0.0f)) return OUTSIDE;
		}

		// Project box and line onto the y-axis
		box_proj = box.Extent.Y;
		p0_proj = dp0.Y;
		dp_proj = line.Get_DP().Y;
		if (p0_proj > 0) {
			if (p0_proj > box_proj - WWMath::Min(dp_proj,0.0f)) return OUTSIDE;
		} else {
			if (-p0_proj > box_proj + WWMath::Max(dp_proj,0.0f)) return OUTSIDE;
		}

		// Project box and line onto the z-axis
		box_proj = box.Extent.Z;
		p0_proj = dp0.Z;
		dp_proj = line.Get_DP().Z;
		if (p0_proj > 0) {
			if (p0_proj > box_proj - WWMath::Min(dp_proj,0.0f)) return OUTSIDE;
		} else {
			if (-p0_proj > box_proj + WWMath::Max(dp_proj,0.0f)) return OUTSIDE;
		}
	
		// Project box and line onto (x cross line)
		// I'm manually optimizing the cross-product and taking advantage of the fact
		// that 'dp' will always project to zero for this axis.
		Vector3 axis;
		axis.Set(0,-line.Get_Dir().Z,line.Get_Dir().Y);	// == (1,0,0) cross (x,y,z)
		box_proj = WWMath::Fabs(axis.Y*box.Extent.Y) + WWMath::Fabs(axis.Z*box.Extent.Z);
		p0_proj = Vector3::Dot_Product(axis,dp0);
		if (WWMath::Fabs(p0_proj) > box_proj) return OUTSIDE;

		// Project box and line onto (y cross line)
		axis.Set(line.Get_Dir().Z,0,-line.Get_Dir().X);	// == (0,1,0) cross (x,y,z)
		box_proj = WWMath::Fabs(axis.X*box.Extent.X) + WWMath::Fabs(axis.Z*box.Extent.Z);
		p0_proj = Vector3::Dot_Product(axis,dp0);
		if (WWMath::Fabs(p0_proj) > box_proj) return OUTSIDE;

		// Project box and line onto (z cross line)
		axis.Set(-line.Get_Dir().Y,line.Get_Dir().X,0);	// == (0,0,1) cross (x,y,z)
		box_proj = WWMath::Fabs(axis.X*box.Extent.X) + WWMath::Fabs(axis.Y*box.Extent.Y);
		p0_proj = Vector3::Dot_Product(axis,dp0);
		if (WWMath::Fabs(p0_proj) > box_proj) return OUTSIDE;

	}
	return OVERLAPPED;
}

CollisionMath::OverlapType CollisionMath::Overlap_Test(const AABoxClass & box,const TriClass & tri)
{
	CastResultStruct res;
	CollisionMath::Collide(box,Vector3(0,0,0),tri,&res);
	return eval_overlap_collision(res);
}

bool CollisionMath::Collide
(
	const AABoxClass &		box,
	const Vector3 &			move_vector,
	const PlaneClass &		plane,
	CastResultStruct *		result
)
{
	float frac;

	float extent = box.Project_To_Axis(plane.N);
	float dist = Vector3::Dot_Product(plane.N,box.Center) + plane.D;
	float move = Vector3::Dot_Product(plane.N,move_vector);

	if (dist > extent) {
		if (dist + move > extent) {
			// entire move ok!
			frac = 1.0f;
		} else {
			// partial move allowed
			frac = (extent - dist) / move;
		}

	} else if (dist < -extent) {
		if (dist + move < -extent) {
			// entire move ok!
			frac = 1.0f;
		} else {
			// partial move allowed
			frac = (-extent - dist) / move;
		}

	} else {
		result->StartBad = true;
		result->Normal = plane.N;
		return true;
	}

	if (frac < result->Fraction) {
		result->Fraction = frac;
		result->Normal = plane.N;
		if (result->ComputeContactPoint) {
			Vector3 move_dir(move_vector);
			move_dir.Normalize();
			float move_extent = Vector3::Dot_Product(box.Extent,move_dir);
			result->ContactPoint = box.Center + result->Fraction * move_vector + move_extent * move_dir;
		}
		return true;
	}

	return false;
}
