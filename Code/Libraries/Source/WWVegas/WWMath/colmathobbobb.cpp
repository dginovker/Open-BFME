// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "colmath.h"
#include "obbox.h"
#include "aabox.h"
#include "wwdebug.h"

#define AXISLEN_EPSILON2	WWMATH_EPSILON * WWMATH_EPSILON	// squared length of a separating axis must be larger than this

enum 
{
	/* Axes used in Box-Box intersection tests */
	INTERSECTION = 0,
	AXIS_A0,	
	AXIS_A1,
	AXIS_A2,
	AXIS_B0,
	AXIS_B1,
	AXIS_B2,
	AXIS_A0B0,
	AXIS_A0B1,
	AXIS_A0B2,
	AXIS_A1B0,
	AXIS_A1B1,
	AXIS_A1B2,
	AXIS_A2B0,
	AXIS_A2B1,
	AXIS_A2B2
};

struct ObbIntersectionStruct
{
	ObbIntersectionStruct(const OBBoxClass &box0,const OBBoxClass & box1) :
		Box0(box0),															
		Box1(box1)
	{
		Vector3::Subtract(box1.Center,box0.Center,&C);	// vector from center of box0 to center of box1

		A[0].Set(box0.Basis[0][0],box0.Basis[1][0],box0.Basis[2][0]);
		A[1].Set(box0.Basis[0][1],box0.Basis[1][1],box0.Basis[2][1]);
		A[2].Set(box0.Basis[0][2],box0.Basis[1][2],box0.Basis[2][2]);

		B[0].Set(box1.Basis[0][0],box1.Basis[1][0],box1.Basis[2][0]);
		B[1].Set(box1.Basis[0][1],box1.Basis[1][1],box1.Basis[2][1]);
		B[2].Set(box1.Basis[0][2],box1.Basis[1][2],box1.Basis[2][2]);
	}

	Vector3					C;						// Vector from the center0 to center1
	Vector3					A[3];					// basis vectors for box0
	Vector3					B[3];					// basis vectors for box1
	float						AB[3][3];			// dot products of the basis vectors

	const OBBoxClass &	Box0;
	const OBBoxClass &	Box1;

private:
	//not implemented
	ObbIntersectionStruct(const ObbIntersectionStruct&);
	ObbIntersectionStruct & operator = (const ObbIntersectionStruct&);
};

static bool obb_intersect_box0_basis
(
	ObbIntersectionStruct &	context,
	int							axis_index
)
{
	// ra = box0 projection onto the axis
	// rb = box1 projection onto the axis
	float ra =	context.Box0.Extent[axis_index];
	float rb =	WWMath::Fabs(context.Box1.Extent[0]*context.AB[axis_index][0]) + 
					WWMath::Fabs(context.Box1.Extent[1]*context.AB[axis_index][1]) + 
					WWMath::Fabs(context.Box1.Extent[2]*context.AB[axis_index][2]);
	float rsum = ra+rb;

	// u = projected distance between the box centers
	float u = Vector3::Dot_Product(context.C,context.A[axis_index]);

	// (gth) the epsilon here was not scaled to the length of the axis so it
	// caused problems when the axis being tested became very small
	return ((u /*+ WWMATH_EPSILON*/ > rsum) || (u /*- WWMATH_EPSILON*/ < -rsum));
}

static bool obb_intersect_box1_basis
(
	ObbIntersectionStruct &	context,
	int							axis_index
)
{
	// ra = box0 projection onto the axis
	// rb = box1 projection onto the axis
	float ra =	WWMath::Fabs(context.Box0.Extent[0]*context.AB[0][axis_index]) + 
					WWMath::Fabs(context.Box0.Extent[1]*context.AB[1][axis_index]) + 
					WWMath::Fabs(context.Box0.Extent[2]*context.AB[2][axis_index]);
	float rb =	context.Box1.Extent[axis_index];
	float rsum = ra+rb;

	// u = projected distance between the box centers
	float u = Vector3::Dot_Product(context.C,context.B[axis_index]);

	// (gth) the epsilon here was not scaled to the length of the axis so it
	// caused problems when the axis being tested became very small
	return ((u /*+ WWMATH_EPSILON*/ > rsum) || (u /*- WWMATH_EPSILON*/ < -rsum));
}

static inline bool obb_intersect_axis
(
	ObbIntersectionStruct &	context,
	const Vector3 &			axis,
	float							ra,
	float							rb
)
{
	float rsum = ra+rb;
	float u = Vector3::Dot_Product(context.C,axis);

	// (gth) the epsilon here was not scaled to the length of the axis so it
	// caused problems when the axis being tested became very small
	return ((u /*+ WWMATH_EPSILON*/ > rsum) || (u /*- WWMATH_EPSILON*/ < -rsum));
}

bool intersect_obb_obb
(
	ObbIntersectionStruct & context
)
{
	Vector3 axis;
	float ra,rb;
	
	/////////////////////////////////////////////////////////////////////////
	// Axis = A0
	/////////////////////////////////////////////////////////////////////////
	context.AB[0][0] = Vector3::Dot_Product(context.A[0],context.B[0]);
	context.AB[0][1] = Vector3::Dot_Product(context.A[0],context.B[1]);
	context.AB[0][2] = Vector3::Dot_Product(context.A[0],context.B[2]);
	if (context.Box0.Extent[0] > 0.0f) {
		if (obb_intersect_box0_basis(context,0)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axsis A1
	/////////////////////////////////////////////////////////////////////////
	context.AB[1][0] = Vector3::Dot_Product(context.A[1],context.B[0]);
	context.AB[1][1] = Vector3::Dot_Product(context.A[1],context.B[1]);
	context.AB[1][2] = Vector3::Dot_Product(context.A[1],context.B[2]);
	if (context.Box0.Extent[1] > 0.0f) {
		if (obb_intersect_box0_basis(context,1)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2
	/////////////////////////////////////////////////////////////////////////
	context.AB[2][0] = Vector3::Dot_Product(context.A[2],context.B[0]);
	context.AB[2][1] = Vector3::Dot_Product(context.A[2],context.B[1]);
	context.AB[2][2] = Vector3::Dot_Product(context.A[2],context.B[2]);
	if (context.Box0.Extent[2] > 0.0f) {
		if (obb_intersect_box0_basis(context,2)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis B0,B1,B2
	/////////////////////////////////////////////////////////////////////////
	if (context.Box1.Extent[0] > 0.0f) {
		if (obb_intersect_box1_basis(context,0)) return false;
	}

	if (context.Box1.Extent[1] > 0.0f) {
		if (obb_intersect_box1_basis(context,1)) return false;
	}

	if (context.Box1.Extent[2] > 0.0f) {
		if (obb_intersect_box1_basis(context,2)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB0
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[0],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][0])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[0][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[0][1]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[1],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][1])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[0][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[0][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}
	
	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[2],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][2])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[0][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[0][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB0
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[0],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][0])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[1][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[1][1]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[1],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][1])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[1][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[1][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[2],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][2])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[1][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[1][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false; 
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB0
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[0],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][0])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[2][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[2][1]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[1],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][1])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[2][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[2][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[2],&axis);
	if (axis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][2])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[2][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[2][0]);
		if (obb_intersect_axis(context,axis,ra,rb)) return false;
	}

	return true;
}

bool CollisionMath::Intersection_Test(const OBBoxClass & box0,const OBBoxClass & box1)
{
	ObbIntersectionStruct context(box0,box1);
	return intersect_obb_obb(context);
}

bool CollisionMath::Intersection_Test(const OBBoxClass & box0,const AABoxClass & box1)
{
	OBBoxClass obbox1(box1.Center,box1.Extent);
	ObbIntersectionStruct context(box0,obbox1);
	return intersect_obb_obb(context);
}

bool CollisionMath::Intersection_Test(const AABoxClass & box0,const OBBoxClass & box1)
{
	OBBoxClass obbox0(box0.Center,box0.Extent);
	ObbIntersectionStruct context(obbox0,box1);
	return intersect_obb_obb(context);
}

struct ObbCollisionStruct
{
	ObbCollisionStruct(const OBBoxClass &box0,const Vector3 &move0,const OBBoxClass & box1,const Vector3 &move1) :
		StartBad(true),													// Startbad is true until one of the axes clears it
		AxisId(INTERSECTION),											// AxisId will be the axis that allowed the longest move
		MaxFrac(0.0f),														// MaxFrac is the longest allowed move so far
		Box0(box0),															
		Move0(move0),
		Box1(box1),
		Move1(move1)
	{
		Vector3::Subtract(box1.Center,box0.Center,&C);			// vector from center of box0 to center of box1
		Vector3::Subtract(move1,move0,&M);							// move vector relative to stationary box0

		A[0].Set(box0.Basis[0][0],box0.Basis[1][0],box0.Basis[2][0]);
		A[1].Set(box0.Basis[0][1],box0.Basis[1][1],box0.Basis[2][1]);
		A[2].Set(box0.Basis[0][2],box0.Basis[1][2],box0.Basis[2][2]);

		B[0].Set(box1.Basis[0][0],box1.Basis[1][0],box1.Basis[2][0]);
		B[1].Set(box1.Basis[0][1],box1.Basis[1][1],box1.Basis[2][1]);
		B[2].Set(box1.Basis[0][2],box1.Basis[1][2],box1.Basis[2][2]);
	}

	bool						StartBad;			// Inital configuration is intersecting?
	float						MaxFrac;				// Longest move allowed so far
	int						AxisId;				// Last separating axis
	int						Side;					// which side of the interval

	int						TestAxisId;			// Axis 'id' we're working on
	Vector3					TestAxis;			// Axis that we're working on

	Vector3					C;						// Vector from the center0 to center1
	Vector3					M;						// Move vector relative to stationary box0
	
	Vector3					A[3];					// basis vectors for box0
	Vector3					B[3];					// basis vectors for box1
	float						AB[3][3];			// dot products of the basis vectors

	const OBBoxClass &	Box0;
	const Vector3 &		Move0;
	const OBBoxClass &	Box1;
	const Vector3 &		Move1;

private:
	//not implemented
	ObbCollisionStruct(const ObbCollisionStruct&);
	ObbCollisionStruct & operator = (const ObbCollisionStruct&);
};

static inline bool obb_separation_test
(
 	ObbCollisionStruct & context,
	float ra,
	float rb,
	float u0,
	float u1
)
{
	float tmp;
	float rsum = ra+rb;

	if ( u0 + WWMATH_EPSILON > rsum ) { 
		context.StartBad = false; 
		if ( u1 > rsum ) { 
			context.MaxFrac = 1.0f; 
			return true;
		} else if (WWMath::Fabs(u1-u0) > 0.0f) {
			tmp = (rsum-u0)/(u1-u0);
			if ( tmp > context.MaxFrac ) {
				context.MaxFrac = tmp; 
				context.AxisId = context.TestAxisId;
				context.Side = +1;
			}
		}
	} else if ( u0 - WWMATH_EPSILON < -rsum ) {
		context.StartBad = false;
		if ( u1 < -rsum ) {
			context.MaxFrac = 1.0f; 
			return true;
		} else if (WWMath::Fabs(u1-u0) > 0.0f) {
			tmp = (-rsum-u0)/(u1-u0);
			if ( tmp > context.MaxFrac ) {
				context.MaxFrac = tmp;
				context.AxisId = context.TestAxisId;
				context.Side = -1;
			} 
		} 
	} 
	return false;
}

static bool obb_check_box0_basis
(
	ObbCollisionStruct &		context,
	int							axis_index
)
{
	// ra = box0 projection onto the axis
	// rb = box1 projection onto the axis
	float ra =	context.Box0.Extent[axis_index];
	float rb =	WWMath::Fabs(context.Box1.Extent[0]*context.AB[axis_index][0]) + 
					WWMath::Fabs(context.Box1.Extent[1]*context.AB[axis_index][1]) + 
					WWMath::Fabs(context.Box1.Extent[2]*context.AB[axis_index][2]);

	// u0 = projected distance between the box centers at t0
	// u1 = projected distance between the box centers at t1
	float u0 = Vector3::Dot_Product(context.C,context.A[axis_index]);
	float u1 = u0 + Vector3::Dot_Product(context.M,context.A[axis_index]);

	return obb_separation_test(context,ra,rb,u0,u1);
}

static bool obb_check_box1_basis
(
	ObbCollisionStruct &		context,
	int							axis_index
)
{
	// ra = box0 projection onto the axis
	// rb = box1 projection onto the axis
	float ra =	WWMath::Fabs(context.Box0.Extent[0]*context.AB[0][axis_index]) + 
					WWMath::Fabs(context.Box0.Extent[1]*context.AB[1][axis_index]) + 
					WWMath::Fabs(context.Box0.Extent[2]*context.AB[2][axis_index]);
	float rb =	context.Box1.Extent[axis_index];

	// u0 = projected distance between the box centers at t0
	// u1 = projected distance between the box centers at t1
	float u0 = Vector3::Dot_Product(context.C,context.B[axis_index]);
	float u1 = u0 + Vector3::Dot_Product(context.M,context.B[axis_index]);
	return obb_separation_test(context,ra,rb,u0,u1);
}

static inline bool obb_check_axis
(
	ObbCollisionStruct &		context,
	float							ra,
	float							rb
)
{
	float u0 = Vector3::Dot_Product(context.C,context.TestAxis);
	float u1 = u0 + Vector3::Dot_Product(context.M,context.TestAxis);
	return obb_separation_test(context,ra,rb,u0,u1);
}

static inline void obb_compute_projections
(
	const ObbCollisionStruct &		context,
	float *								ra,
	float *								rb
)
{
	*ra =	context.Box0.Extent.X * WWMath::Fabs(Vector3::Dot_Product(context.A[0],context.TestAxis)) + 
			context.Box0.Extent.Y * WWMath::Fabs(Vector3::Dot_Product(context.A[1],context.TestAxis)) +
			context.Box0.Extent.Z * WWMath::Fabs(Vector3::Dot_Product(context.A[2],context.TestAxis));

	*rb =	context.Box1.Extent.X * WWMath::Fabs(Vector3::Dot_Product(context.B[0],context.TestAxis)) + 
			context.Box1.Extent.Y * WWMath::Fabs(Vector3::Dot_Product(context.B[1],context.TestAxis)) +
			context.Box1.Extent.Z * WWMath::Fabs(Vector3::Dot_Product(context.B[2],context.TestAxis));
}

static inline void compute_contact_normal(ObbCollisionStruct & context,CastResultStruct * result)
{
	switch(context.AxisId) 
	{
	case INTERSECTION:
#pragma message("Fatal assert disabled for demo, obb-obb collision")
//		WWASSERT(0);
//		break;

	case AXIS_A0:
		result->Normal = context.A[0];
		break;

	case AXIS_A1:
		result->Normal = context.A[1];
		break;

	case AXIS_A2:
		result->Normal = context.A[2];
		break;

	case AXIS_B0:
		result->Normal = context.B[0];
		break;

	case AXIS_B1:
		result->Normal = context.B[1];
		break;

	case AXIS_B2:
		result->Normal = context.B[2];
		break;

	case AXIS_A0B0:
		Vector3::Cross_Product(context.A[0],context.B[0],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A0B1:
		Vector3::Cross_Product(context.A[0],context.B[1],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A0B2:
		Vector3::Cross_Product(context.A[0],context.B[2],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A1B0:
		Vector3::Cross_Product(context.A[1],context.B[0],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A1B1:
		Vector3::Cross_Product(context.A[1],context.B[1],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A1B2:
		Vector3::Cross_Product(context.A[1],context.B[2],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A2B0:
		Vector3::Cross_Product(context.A[2],context.B[0],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A2B1:
		Vector3::Cross_Product(context.A[2],context.B[1],&result->Normal);
		result->Normal.Normalize();
		break;

	case AXIS_A2B2:
		Vector3::Cross_Product(context.A[2],context.B[2],&result->Normal);
		result->Normal.Normalize();
		break;
	}	

	result->Normal *= -context.Side;
}

static inline float eval_side(float ab,float side)
{
	if (ab > 0.0f) {
		return side;
	} else if (ab < 0.0f) {
		return -side;
	} else {
		return 0.0f;
	}
}

static inline void compute_contact_point(ObbCollisionStruct & context,CastResultStruct * result)
{
	int i,j;
	float x[3];		// box0 parameters
	float y[3];		// box1 parameters
	float den;
	Vector3 dcnew(0,0,0);

//again:

	if (context.AxisId >= AXIS_A0B0) {
		Vector3 cnew0;
		Vector3 cnew1;
		Vector3::Add(context.Box0.Center,context.MaxFrac * context.Move0,&cnew0);
		Vector3::Add(context.Box1.Center,context.MaxFrac * context.Move1,&cnew1);
		Vector3::Subtract(cnew1,cnew0,&dcnew);
	}

	//PROBLEMS: 
	//in case of edge-face or face-face or perfectly aligned edge-edge this
	//routine is only computing a single point.  
	switch(context.AxisId) 
	{
	case AXIS_A0:
	case AXIS_A1:
	case AXIS_A2:
		i = context.AxisId - AXIS_A0;
		for (j=0; j<3; j++) {
			y[j] = -eval_side(context.AB[i][j],context.Side);
		}
		context.Box1.Compute_Point(y,&(result->ContactPoint));
		result->ContactPoint += result->Fraction * context.Move1;
		return;

	case AXIS_B0:
	case AXIS_B1:
	case AXIS_B2:
		j = context.AxisId - AXIS_B0;
		for (i=0; i<3; i++) {
			x[i] = eval_side(context.AB[i][j],context.Side);
		}
		context.Box0.Compute_Point(x,&(result->ContactPoint));
		result->ContactPoint += result->Fraction * context.Move0;
		return;

	case AXIS_A0B0:
		x[1] = -eval_side(context.AB[2][0],context.Side) * context.Box0.Extent[1];
		x[2] = eval_side(context.AB[1][0],context.Side) * context.Box0.Extent[2];
		y[1] = -eval_side(context.AB[0][2],context.Side) * context.Box1.Extent[1];
		y[2] = eval_side(context.AB[0][1],context.Side) * context.Box1.Extent[2];
		
		den = (1.0f - context.AB[0][0] * context.AB[0][0]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[0] = Vector3::Dot_Product(context.A[0],dcnew);
			x[0] += context.AB[0][0] * (Vector3::Dot_Product(-context.B[0],dcnew) + context.AB[1][0]*x[1] + context.AB[2][0]*x[2]);
			x[0] += context.AB[0][1] * y[1] + context.AB[0][2] * y[2];
			x[0] /= den;
		} else {
			x[0] = 0.0f;
		}
		break;
	
	case AXIS_A0B1:
		x[1] = -eval_side(context.AB[2][1],context.Side) * context.Box0.Extent[1];
		x[2] = eval_side(context.AB[1][1],context.Side) * context.Box0.Extent[2];
		y[0] = eval_side(context.AB[0][2],context.Side) * context.Box1.Extent[0];
		y[2] = -eval_side(context.AB[0][0],context.Side) * context.Box1.Extent[2];

		den = (1.0f - context.AB[0][1] * context.AB[0][1]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[0] = Vector3::Dot_Product(context.A[0],dcnew);
			x[0] += context.AB[0][1] * (Vector3::Dot_Product(-context.B[1],dcnew) + context.AB[1][1]*x[1] + context.AB[2][1]*x[2]);
			x[0] += context.AB[0][0] * y[0] + context.AB[0][2] * y[2];
			x[0] /= den; 
		} else {
			x[0] = 0.0f;
		}
		break;
	
	case AXIS_A0B2:
		x[1] = -eval_side(context.AB[2][2],context.Side) * context.Box0.Extent[1];
		x[2] = eval_side(context.AB[1][2],context.Side) * context.Box0.Extent[2];
		y[0] = -eval_side(context.AB[0][1],context.Side) * context.Box1.Extent[0];
		y[1] = eval_side(context.AB[0][0],context.Side) * context.Box1.Extent[1];

		den = (1.0f - context.AB[0][2] * context.AB[0][2]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[0] = Vector3::Dot_Product(context.A[0],dcnew);
			x[0] += context.AB[0][2] * (Vector3::Dot_Product(-context.B[2],dcnew) + context.AB[1][2]*x[1] + context.AB[2][2]*x[2]);
			x[0] += context.AB[0][0] * y[0] + context.AB[0][1] * y[1];
			x[0] /= den;
		} else {
			x[0] = 0.0f;
		}
		break;

	case AXIS_A1B0:
		x[0] = eval_side(context.AB[2][0],context.Side) * context.Box0.Extent[0];
		x[2] = -eval_side(context.AB[0][0],context.Side) * context.Box0.Extent[2];
		y[1] = -eval_side(context.AB[1][2],context.Side) * context.Box1.Extent[1];
		y[2] = eval_side(context.AB[1][1],context.Side) * context.Box1.Extent[2];

		den = (1.0f - context.AB[1][0] * context.AB[1][0]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[1] = Vector3::Dot_Product(context.A[1],dcnew);
			x[1] += context.AB[1][0] * (Vector3::Dot_Product(-context.B[0],dcnew) + context.AB[0][0]*x[0] + context.AB[2][0]*x[2]);
			x[1] += context.AB[1][1] * y[1] + context.AB[1][2] * y[2];
			x[1] /= den; 
		} else {
			x[1] = 0.0f;
		}
		break;

	case AXIS_A1B1:
		x[0] = eval_side(context.AB[2][1],context.Side) * context.Box0.Extent[0];
		x[2] = -eval_side(context.AB[0][1],context.Side) * context.Box0.Extent[2];
		y[0] = eval_side(context.AB[1][2],context.Side) * context.Box1.Extent[0];
		y[2] = -eval_side(context.AB[1][0],context.Side) * context.Box1.Extent[2];

		den = 1.0f / (1.0f - context.AB[1][1] * context.AB[1][1]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[1] = Vector3::Dot_Product(context.A[1],dcnew);
			x[1] += context.AB[1][1] * (Vector3::Dot_Product(-context.B[1],dcnew) + context.AB[0][1]*x[0] + context.AB[2][1]*x[2]);
			x[1] += context.AB[1][0] * y[0] + context.AB[1][2] * y[2];
			x[1] /= den; 
		} else {
			x[1] = 0.0f;
		}
		break;

	case AXIS_A1B2:
		x[0] = eval_side(context.AB[2][2],context.Side) * context.Box0.Extent[0];
		x[2] = -eval_side(context.AB[0][2],context.Side) * context.Box0.Extent[2];
		y[0] = -eval_side(context.AB[1][1],context.Side) * context.Box1.Extent[0];
		y[1] = eval_side(context.AB[1][0],context.Side) * context.Box1.Extent[1];

		den = (1.0f - context.AB[1][2] * context.AB[1][2]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[1] = Vector3::Dot_Product(context.A[1],dcnew);
			x[1] += context.AB[1][2] * (Vector3::Dot_Product(-context.B[2],dcnew) + context.AB[0][2]*x[0] + context.AB[2][2]*x[2]);
			x[1] += context.AB[1][0] * y[0] + context.AB[1][1] * y[1];
			x[1] /= den;
		} else {
			x[1] = 0.0f;
		}
		break;

	case AXIS_A2B0:
		x[0] = -eval_side(context.AB[1][0],context.Side) * context.Box0.Extent[0];
		x[1] = eval_side(context.AB[0][0],context.Side) * context.Box0.Extent[1];
		y[1] = -eval_side(context.AB[2][2],context.Side) * context.Box1.Extent[1];
		y[2] = eval_side(context.AB[2][1],context.Side) * context.Box1.Extent[2];

		den = (1.0f - context.AB[2][0] * context.AB[2][0]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[2] = Vector3::Dot_Product(context.A[2],dcnew);
			x[2] += context.AB[2][0] * (Vector3::Dot_Product(-context.B[0],dcnew) + context.AB[0][0]*x[0] + context.AB[1][0]*x[1]);
			x[2] += context.AB[2][1] * y[1] + context.AB[2][2] * y[2];
			x[2] /= den;
		} else {
			x[2] = 0.0f;
		}
		break;
	
	case AXIS_A2B1:
		x[0] = -eval_side(context.AB[1][1],context.Side) * context.Box0.Extent[0];
		x[1] = eval_side(context.AB[0][1],context.Side) * context.Box0.Extent[1];
		y[0] = eval_side(context.AB[2][2],context.Side) * context.Box1.Extent[0];
		y[2] = -eval_side(context.AB[2][0],context.Side) * context.Box1.Extent[2];

		den = (1.0f - context.AB[2][1] * context.AB[2][1]);
		if (WWMath::Fabs(den) > 0.0f) {
			x[2] = Vector3::Dot_Product(context.A[2],dcnew);
			x[2] += context.AB[2][1] * (Vector3::Dot_Product(-context.B[1],dcnew) + context.AB[0][1]*x[0] + context.AB[1][1]*x[1]);
			x[2] += context.AB[2][0] * y[0] + context.AB[2][2] * y[2];
			x[2] /= den;
		} else {
			x[2] = 0.0f;
		}
		break;
	
	case AXIS_A2B2:
		x[0] = -eval_side(context.AB[1][2],context.Side) * context.Box0.Extent[0];
		x[1] = eval_side(context.AB[0][2],context.Side) * context.Box0.Extent[1];
		y[0] = -eval_side(context.AB[2][1],context.Side) * context.Box1.Extent[0];
		y[1] = eval_side(context.AB[2][0],context.Side) * context.Box1.Extent[1];

		den = (1.0f - context.AB[2][2] * context.AB[2][2]); 
		if (WWMath::Fabs(den) > 0.0f) {
			x[2] = Vector3::Dot_Product(context.A[2],dcnew);
			x[2] += context.AB[2][2] * (Vector3::Dot_Product(-context.B[2],dcnew) + context.AB[0][2]*x[0] + context.AB[1][2]*x[1]);
			x[2] += context.AB[2][0] * y[0] + context.AB[2][1] * y[1];
			x[2] /= den;
		} else {
			x[2] = 0.0f;
		}
		break;
	}	

	// all but the first two cases fall through to here
	result->ContactPoint.X =	context.Box0.Center.X + 
										x[0]*context.A[0].X + 
										x[1]*context.A[1].X + 
										x[2]*context.A[2].X;

	result->ContactPoint.Y =	context.Box0.Center.Y + 
										x[0]*context.A[0].Y + 
										x[1]*context.A[1].Y + 
										x[2]*context.A[2].Y;

	result->ContactPoint.Z =	context.Box0.Center.Z + 
										x[0]*context.A[0].Z + 
										x[1]*context.A[1].Z + 
										x[2]*context.A[2].Z;
	
	Vector3::Add(result->ContactPoint,result->Fraction * context.Move0,&(result->ContactPoint));

}

bool collide_obb_obb
(
	ObbCollisionStruct &		context,
	CastResultStruct *		result
)
{
	Vector3 axis;
	float ra,rb;

	/////////////////////////////////////////////////////////////////////////
	// Axis = A0
	// Projecting the two boxes onto Box0's X axis.  If their intervals
	// on this line do not intersect, the boxes are not intersecting!
	// Each of the tests in this function work in a similar way.
	// For this function I compute the AB's that are needed.  The first
	// three tests compute all of these constants.
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_A0;
	context.AB[0][0] = Vector3::Dot_Product(context.A[0],context.B[0]);
	context.AB[0][1] = Vector3::Dot_Product(context.A[0],context.B[1]);
	context.AB[0][2] = Vector3::Dot_Product(context.A[0],context.B[2]);
	if (obb_check_box0_basis(context,0)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axsis A1
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_A1;
	context.AB[1][0] = Vector3::Dot_Product(context.A[1],context.B[0]);
	context.AB[1][1] = Vector3::Dot_Product(context.A[1],context.B[1]);
	context.AB[1][2] = Vector3::Dot_Product(context.A[1],context.B[2]);
	if (obb_check_box0_basis(context,1)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_A2;
	context.AB[2][0] = Vector3::Dot_Product(context.A[2],context.B[0]);
	context.AB[2][1] = Vector3::Dot_Product(context.A[2],context.B[1]);
	context.AB[2][2] = Vector3::Dot_Product(context.A[2],context.B[2]);
	if (obb_check_box0_basis(context,2)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axis = B0
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_B0;
	if (obb_check_box1_basis(context,0)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axis = B1
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_B1;
	if (obb_check_box1_basis(context,1)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axis = B2
	/////////////////////////////////////////////////////////////////////////
	context.TestAxisId = AXIS_B2;
	if (obb_check_box1_basis(context,2)) goto exit;

	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB0
	// The axes defined by the cross product between the boxes' basis
	// vectors are optimized in a similar way to this one:
	//
	// ra   = |ex*A0*(A0xB0)| + |ey*A1*(A0xB0)| + |ez*A2*(A0xB0)|
	//      = |ey*A1*(A0xB0)| + |ez*A2*(A0xB0)|							A0*(A0xB0)=0
	//      = |ey*B0*(A1xA0)| + |ez*B0*(A2xA0)|						   A*(BxC)=B*(CxA)=C*(AxB)
	//      = |-ey*A2*B0| +     |ez*A1*B0|									A0xA1=A2
	//      = |ey*AB[2][0]| +   |ez*AB[1][0]|								already computed these dot products!
	// 
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[0],&context.TestAxis);
	context.TestAxisId = AXIS_A0B0;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][0])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[0][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[0][1]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[1],&context.TestAxis);
	context.TestAxisId = AXIS_A0B1;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][1])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[0][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[0][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}
	
	/////////////////////////////////////////////////////////////////////////
	// Axis = A0xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[0],context.B[2],&context.TestAxis);
	context.TestAxisId = AXIS_A0B2;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[1]*context.AB[2][2])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[1][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[0][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[0][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB0
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[0],&context.TestAxis);
	context.TestAxisId = AXIS_A1B0;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][0])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[1][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[1][1]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[1],&context.TestAxis);
	context.TestAxisId = AXIS_A1B1;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][1])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[1][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[1][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A1xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[1],context.B[2],&context.TestAxis);
	context.TestAxisId = AXIS_A1B2;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[2][2])+WWMath::Fabs(context.Box0.Extent[2]*context.AB[0][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[1][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[1][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB0
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[0],&context.TestAxis);
	context.TestAxisId = AXIS_A2B0;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][0])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][0]);
		rb = WWMath::Fabs(context.Box1.Extent[1]*context.AB[2][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[2][1]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB1
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[1],&context.TestAxis);
	context.TestAxisId = AXIS_A2B1;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][1])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][1]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[2][2])+WWMath::Fabs(context.Box1.Extent[2]*context.AB[2][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	/////////////////////////////////////////////////////////////////////////
	// Axis = A2xB2
	/////////////////////////////////////////////////////////////////////////
	Vector3::Cross_Product(context.A[2],context.B[2],&context.TestAxis);
	context.TestAxisId = AXIS_A2B2;
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		ra = WWMath::Fabs(context.Box0.Extent[0]*context.AB[1][2])+WWMath::Fabs(context.Box0.Extent[1]*context.AB[0][2]);
		rb = WWMath::Fabs(context.Box1.Extent[0]*context.AB[2][1])+WWMath::Fabs(context.Box1.Extent[1]*context.AB[2][0]);
		if (obb_check_axis(context,ra,rb)) goto exit;
	}

	if (!result->StartBad) {
	
		context.TestAxisId = context.AxisId;

		/////////////////////////////////////////////////////////////////////////
		// Final three checks are for eliminating false collisions
		// Axis = A0xMove
		/////////////////////////////////////////////////////////////////////////
		Vector3::Cross_Product(context.A[0],context.Move0,&context.TestAxis);
		if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
			obb_compute_projections(context,&ra,&rb);
			if (obb_check_axis(context,ra,rb)) goto exit;
		}
		
		/////////////////////////////////////////////////////////////////////////
		// Axis = A1xMove
		/////////////////////////////////////////////////////////////////////////
		Vector3::Cross_Product(context.A[1],context.Move0,&context.TestAxis);
		if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
			obb_compute_projections(context,&ra,&rb);
			if (obb_check_axis(context,ra,rb)) goto exit;
		}

		/////////////////////////////////////////////////////////////////////////
		// Axis = A2xMove
		/////////////////////////////////////////////////////////////////////////
		Vector3::Cross_Product(context.A[2],context.Move0,&context.TestAxis);
		if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
			obb_compute_projections(context,&ra,&rb);
			if (obb_check_axis(context,ra,rb)) goto exit;
		}
	}
	
exit:

	if (context.StartBad) {
		result->StartBad = true;
		result->Fraction = 0.0f;
		return true;
	}

	/*
	** If our fraction is smaller, override the previous 
	** values because our collision occured first.
	*/
	if (context.MaxFrac < result->Fraction) {

		result->Fraction = context.MaxFrac;

		compute_contact_normal(context,result);
		if (result->ComputeContactPoint) {
			compute_contact_point(context,result);
		}
		return true;
	}
	return false;
}

bool CollisionMath::Collide
(
	const OBBoxClass &		box0,
	const Vector3 &			move0,
	const OBBoxClass &		box1,
	const Vector3 &			move1,
	CastResultStruct *		result
)
{
	ObbCollisionStruct context(box0,move0,box1,move1);
	return collide_obb_obb(context,result);	
}

bool CollisionMath::Collide
(
	const OBBoxClass &		box0,
	const Vector3 &			move0,
	const AABoxClass &		box1,
	const Vector3 &			move1,
	CastResultStruct *		result
)
{
	OBBoxClass obbox1(box1.Center,box1.Extent);
	ObbCollisionStruct context(box0,move0,obbox1,move1);
	return collide_obb_obb(context,result);	
}

bool CollisionMath::Collide
(
	const AABoxClass &		box0,
	const Vector3 &			move0,
	const OBBoxClass &		box1,
	const Vector3 &			move1,
	CastResultStruct *		result
)
{
	OBBoxClass obbox0(box0.Center,box0.Extent);
	ObbCollisionStruct context(obbox0,move0,box1,move1);
	return collide_obb_obb(context,result);	
}
