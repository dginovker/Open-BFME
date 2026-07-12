// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "colmath.h"
#include "colmathinlines.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "frustum.h"
#include "wwdebug.h"


// TODO: Most of these overlap functions actually do not catch all cases of when
// the primitive is outside of the frustum...


// Frustum functions
CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const Vector3 & point)
{
	int mask = 0;
	
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],point);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const TriClass & tri)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],tri);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const SphereClass & sphere)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],sphere);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const AABoxClass & box)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],box);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}


CollisionMath::OverlapType
CollisionMath::Overlap_Test(const FrustumClass & frustum,const OBBoxClass & box)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {
		int result = CollisionMath::Overlap_Test(frustum.Planes[i],box);
		if (result == OUTSIDE) {
			return OUTSIDE;
		}
		mask |= result;
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}


CollisionMath::OverlapType	
CollisionMath::Overlap_Test(const FrustumClass & frustum,const OBBoxClass & box,int & planes_passed)
{
	int mask = 0;
	
	// TODO: doesn't catch all cases...
	for (int i = 0; i < 6; i++) {

		int plane_bit = (1<<i);

		// only check this plane if we have to	
		if ((planes_passed & plane_bit) == 0) {
			
			int result = CollisionMath::Overlap_Test(frustum.Planes[i],box);
			if (result == OUTSIDE) {
				return OUTSIDE;
			} else if (result == INSIDE) {
				planes_passed |= plane_bit;
			}
			mask |= result;

		} else {
		
			mask |= INSIDE;

		}
	}

	if (mask == INSIDE) {
		return INSIDE;
	}
	return OVERLAPPED;
}

