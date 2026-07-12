// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// WWMath collision-vs-plane tests, verbatim from the Generals reference
// (Libraries/Source/WWVegas/WWMath/colmathplane.cpp). WWASSERT compiles out in
// the retail (non-DEBUG_CRASHING) build, matching what BFME shipped.
#include "colmath.h"
#include "colmathplane.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"



CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const Vector3 & point)
{
	float delta = point[plane.Normal] - plane.Dist;
	if (delta > COINCIDENCE_EPSILON) {
		return POS;
	}
	if (delta < -COINCIDENCE_EPSILON) {
		return NEG;
	}
	return ON;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const LineSegClass & line)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P0());
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P1());
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const TriClass & tri)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[0]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[1]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[2]);
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const SphereClass & sphere)
{
	float delta = sphere.Center[plane.Normal] - plane.Dist;
	if (delta > sphere.Radius) {
		return POS;
	}
	if (delta < sphere.Radius) {
		return NEG;
	}
	return BOTH;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & plane,const AABoxClass & box)
{
	float delta;
	int mask = 0;

	// check the 'min' side of the box
	delta = (box.Center[plane.Normal] - box.Extent[plane.Normal]) - plane.Dist;
	if (delta > WWMATH_EPSILON) {
		mask |= POS;
	} else if (delta < -WWMATH_EPSILON) {
		mask |= NEG;
	} else {
		mask |= ON;
	}

	// check the 'max' side of the box
	delta = (box.Center[plane.Normal] + box.Extent[plane.Normal]) - plane.Dist;
	if (delta > WWMATH_EPSILON) {
		mask |= POS;
	} else if (delta < -WWMATH_EPSILON) {
		mask |= NEG;
	} else {
		mask |= ON;
	}

	return eval_overlap_mask(mask);
}


CollisionMath::OverlapType
CollisionMath::Overlap_Test(const AAPlaneClass & /*plane*/,const OBBoxClass & /*box*/)
{
// TODO
	WWASSERT(0);
	return POS;
}


// Plane functions.  Where is operand B with respect to the plane

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const LineSegClass & line)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P0());
	mask |= CollisionMath::Overlap_Test(plane,line.Get_P1());
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const TriClass & tri)
{
	int mask = 0;
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[0]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[1]);
	mask |= CollisionMath::Overlap_Test(plane,*tri.V[2]);
	return eval_overlap_mask(mask);
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const SphereClass & sphere)
{
	float dist = Vector3::Dot_Product(sphere.Center,plane.N) - plane.D;
	if (dist > sphere.Radius) {
		return POS;
	}
	if (dist < -sphere.Radius) {
		return NEG;
	}
	return BOTH;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const OBBoxClass & box)
{
	// rotate the plane normal into box coordinates
	Vector3 local_normal;
	Vector3 posfarpt;
	Vector3 negfarpt;
	Matrix3::Transpose_Rotate_Vector(box.Basis,plane.N,&local_normal);

	get_far_extent(local_normal,box.Extent,&posfarpt);

	// transform the two extreme box coordinates into world space
	Matrix3::Rotate_Vector(box.Basis,posfarpt,&posfarpt);
	negfarpt = -posfarpt;
	posfarpt += box.Center;
	negfarpt += box.Center;

	// overlap test
	if (Overlap_Test(plane,negfarpt) == POS) {
		return POS;
	}
	if (Overlap_Test(plane,posfarpt) == NEG) {
		return NEG;
	}
	return BOTH;
}
