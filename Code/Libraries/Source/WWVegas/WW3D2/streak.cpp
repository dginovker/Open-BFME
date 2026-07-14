// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : G                                                            *
 *                                                                                             *
 *                     $Archive:: /VSS_Sync/ww3d2/segline.cpp                                 $*
 *                                                                                             *
 *                      $Author:: Vss_sync                                                    $*
 *                                                                                             *
 *                     $Modtime:: 8/29/01 7:29p                                               $*
 *                                                                                             *
 *                    $Revision:: 23                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "streak.h"
#include "ww3d.h"
#include "rinfo.h"
#include "predlod.h"
#include "v3_rnd.h"
#include "texture.h"
#include "coltest.h"
#include "w3d_file.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vp.h"
#include "vector3i.h"
#include "sortingrenderer.h"

static SegLineRendererClass _LineRenderer;


/*
** StreakLineClass implementation:
*/

// ??0StreakLineClass@@ present-unmatched
StreakLineClass::StreakLineClass(void) :
		MaxSubdivisionLevels(0),
		NormalizedScreenArea(0.0f)
{
		Personalities = NULL;

}

// ??0StreakLineClass@@ present-unmatched
StreakLineClass::StreakLineClass(const StreakLineClass & src) :
		MaxSubdivisionLevels(src.MaxSubdivisionLevels),
		NormalizedScreenArea(src.NormalizedScreenArea),
		PointLocations(src.PointLocations),
		PointColors(src.PointColors),
		PointWidths(src.PointWidths),
		LineRenderer(src.LineRenderer),
		StreakRenderer(src.StreakRenderer),
		Personalities(src.Personalities)
{
}

// ??4StreakLineClass@@ present-unmatched
StreakLineClass & StreakLineClass::operator = (const StreakLineClass &that)
{
	RenderObjClass::operator = (that);

	if (this != &that) {

		MaxSubdivisionLevels = that.MaxSubdivisionLevels;
		NormalizedScreenArea = that.NormalizedScreenArea;
		PointLocations = that.PointLocations;
		PointColors = that.PointColors;
		PointWidths = that.PointWidths;
		LineRenderer = that.LineRenderer;
		StreakRenderer = that.StreakRenderer;
		Personalities = that.Personalities;
	}

	return * this;
}

//StreakLineClass::~StreakLineClass(void)
//{
//}





// ?Reset_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Reset_Line(void)
{
	LineRenderer.Reset_Line();
	StreakRenderer.Reset_Line();
}





////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// These are segment points, and include the start and end point of the
// entire line. Therefore there must be at least two.
// ?Set_Locs@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Locs( unsigned int num_points, Vector3 *locs )
{
	if (num_points < 2 || !locs) {
		WWASSERT(0);
		return;
	}

	PointLocations.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		PointLocations.Add(locs[i],num_points);
	}

	Invalidate_Cached_Bounding_Volumes();
}

// ?Set_Widths@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Widths( unsigned int num_points, float *widths )
{
	if (num_points < 2 || !widths) {
		WWASSERT(0);
		return;
	}

	PointWidths.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		PointWidths.Add(widths[i],num_points);
	}

}

// ?Set_Colors@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Colors( unsigned int num_points, Vector4 *colors )
{
	if (num_points < 2 || !colors) {
		WWASSERT(0);
		return;
	}

	PointColors.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		PointColors.Add(colors[i],num_points);
	}

}

// ?Set_LocsWidthsColors@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_LocsWidthsColors( unsigned int num_points, 
																					 Vector3 *locs, 
																					 float *widths, 
																					 Vector4 *colors,
																					 unsigned int *personalities)
{

	Personalities = personalities;

	Set_Locs( num_points, locs );

	if (widths)
	{
		Set_Widths( num_points, widths );

		//sanity check
		int locCount = PointLocations.Count();
		int widCount = PointWidths.Count();
		WWASSERT(locCount == widCount);

	}

	if (colors)
	{
		Set_Colors( num_points, colors );

		//sanity check
		int locCount = PointLocations.Count();
		int colCount = PointColors.Count();
		WWASSERT(locCount == colCount);

	}


	Invalidate_Cached_Bounding_Volumes();
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////







// These are segment points, and include the start and end point of the
// entire line. Therefore there must be at least two.
// ?Get_Num_Points@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_Num_Points(void)
{
	int locCount = PointLocations.Count();
	return locCount;
}

// Set object-space location for a given point.
// NOTE: If given position beyond end of point list, do nothing.
// ?Set_Point_Location@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Point_Location(unsigned int point_idx, const Vector3 &location)
{
	if (point_idx < (unsigned int)PointLocations.Count()) {
		PointLocations[point_idx] = location;
	}
	Invalidate_Cached_Bounding_Volumes();
}

// Get object-space location of a given point (if position beyond end of
// point list, will return 0,0,0).
// ?Get_Point_Location@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Point_Location(unsigned int point_idx, Vector3 &loc)
{
	if (point_idx < (unsigned int)PointLocations.Count()) {
		loc.Set(PointLocations[point_idx]);
	} else {
		loc.Set(0, 0, 0);
	}
}

// ?Add_Point@StreakLineClass@@ present-unmatched
void StreakLineClass::Add_Point(const Vector3 & location)
{
	PointLocations.Add(location);
}

// ?Delete_Point@StreakLineClass@@ present-unmatched
void StreakLineClass::Delete_Point(unsigned int point_idx)
{
	if (point_idx < (unsigned int)PointLocations.Count()) {
		PointLocations.Delete(point_idx);
	}
}


// ?Get_Texture@StreakLineClass@@ present-unmatched
TextureClass * StreakLineClass::Get_Texture(void)
{
	return LineRenderer.Get_Texture();
}

// ?Get_Shader@StreakLineClass@@ present-unmatched
ShaderClass StreakLineClass::Get_Shader(void)
{
	return LineRenderer.Get_Shader();
}

// ?Get_Color@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Color(Vector3 &color)
{
	color.Set(LineRenderer.Get_Color());
}

// ?Get_Opacity@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Opacity(void)
{
	return LineRenderer.Get_Opacity();
}

// ?Get_Noise_Amplitude@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Noise_Amplitude(void)
{
	return LineRenderer.Get_Noise_Amplitude();
}

// ?Get_Merge_Abort_Factor@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Merge_Abort_Factor(void)
{
	return LineRenderer.Get_Merge_Abort_Factor();
}

// ?Get_Subdivision_Levels@StreakLineClass@@ present-unmatched
unsigned int StreakLineClass::Get_Subdivision_Levels(void)
{
	return MaxSubdivisionLevels;
}

// ?Get_Texture_Mapping_Mode@StreakLineClass@@ present-unmatched
SegLineRendererClass::TextureMapMode StreakLineClass::Get_Texture_Mapping_Mode(void)
{
	return LineRenderer.Get_Texture_Mapping_Mode(); 
}

// ?Get_Texture_Tile_Factor@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Texture_Tile_Factor(void)
{
	return LineRenderer.Get_Texture_Tile_Factor();
}

// ?Get_UV_Offset_Rate@StreakLineClass@@ present-unmatched
Vector2 StreakLineClass::Get_UV_Offset_Rate(void)
{
	return LineRenderer.Get_UV_Offset_Rate();
}

// ?Is_Merge_Intersections@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Merge_Intersections(void)
{
	return LineRenderer.Is_Merge_Intersections();
}

// ?Is_Freeze_Random@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Freeze_Random(void)
{
	return LineRenderer.Is_Freeze_Random();
}

// ?Is_Sorting_Disabled@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Sorting_Disabled(void)
{
	return LineRenderer.Is_Sorting_Disabled();
}

// ?Are_End_Caps_Enabled@StreakLineClass@@ present-unmatched
int StreakLineClass::Are_End_Caps_Enabled(void)
{
	return LineRenderer.Are_End_Caps_Enabled();
}

// ?Set_Texture@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture(TextureClass *texture)
{
	LineRenderer.Set_Texture(texture);
	StreakRenderer.Set_Texture(texture);
}

// ?Set_Shader@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Shader(ShaderClass shader)
{
	LineRenderer.Set_Shader(shader);
	StreakRenderer.Set_Shader(shader);
}

// ?Get_Width@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Width(void)
{
	return LineRenderer.Get_Width();
}

// ?Set_Width@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Width(float width)
{
	// Widths need to be clamped because they are not automatically clamped later (like colors and
	// alphas are).
	LineRenderer.Set_Width(MAX(width, 0.0f));
	StreakRenderer.Set_Width(MAX(width, 0.0f));

	Invalidate_Cached_Bounding_Volumes();
}

// ?Set_Color@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Color(const Vector3 &color)
{
	LineRenderer.Set_Color(color);
	StreakRenderer.Set_Color(color);
}

// ?Set_Opacity@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Opacity(float opacity)
{
	LineRenderer.Set_Opacity(opacity);
	StreakRenderer.Set_Opacity(opacity);
}

// ?Set_Noise_Amplitude@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Noise_Amplitude(float amplitude)
{
	LineRenderer.Set_Noise_Amplitude(WWMath::Fabs(amplitude));

	Invalidate_Cached_Bounding_Volumes();
}

void StreakLineClass::Set_Merge_Abort_Factor(float factor)
{
	LineRenderer.Set_Merge_Abort_Factor(factor);
}

// ?Set_Subdivision_Levels@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Subdivision_Levels(unsigned int levels)
{
	MaxSubdivisionLevels = MIN(levels, MAX_SEGLINE_SUBDIV_LEVELS);

	Invalidate_Cached_Bounding_Volumes();
}

// ?Set_Texture_Mapping_Mode@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode)
{
	LineRenderer.Set_Texture_Mapping_Mode(mode);
}

// ?Set_Texture_Tile_Factor@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture_Tile_Factor(float factor)
{
	LineRenderer.Set_Texture_Tile_Factor(factor);
}

// ?Set_UV_Offset_Rate@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_UV_Offset_Rate(const Vector2 &rate)
{
	LineRenderer.Set_UV_Offset_Rate(rate);
}

// ?Set_Merge_Intersections@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Merge_Intersections(int onoff)
{
	LineRenderer.Set_Merge_Intersections(onoff);
}

// ?Set_Freeze_Random@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Freeze_Random(int onoff)
{
	LineRenderer.Set_Freeze_Random(onoff);
}


// ?Set_Disable_Sorting@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Disable_Sorting(int onoff)
{
	LineRenderer.Set_Disable_Sorting(onoff);
}

// ?Set_End_Caps@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_End_Caps(int onoff)
{
	LineRenderer.Set_End_Caps(onoff);
}

/*
** RenderObjClass interface:
*/

// ?Clone@StreakLineClass@@ present-unmatched
RenderObjClass * StreakLineClass::Clone(void) const
{
	return NEW_REF( StreakLineClass, (*this)); 
}

// ?Get_Num_Polys@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_Num_Polys(void) const
{
	int subdivision_factor = 1 << LineRenderer.Get_Current_Subdivision_Level();
	return 2 * (PointLocations.Count() - 1) * subdivision_factor;
}

// ?Render@StreakLineClass@@ present-unmatched
void StreakLineClass::Render(RenderInfoClass & rinfo)
{
	if (Is_Not_Hidden_At_All() == false) {
		return ;
	}

	// Process texture reductions:
//	if (LineRenderer.Peek_Texture()) LineRenderer.Peek_Texture()->Process_Reduction();

	unsigned int sort_level = SORT_LEVEL_NONE;

	if (!WW3D::Is_Sorting_Enabled())	
		sort_level=Get_Shader().Guess_Sort_Level();	

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level!=SORT_LEVEL_NONE) {		
		
		WW3D::Add_To_Static_Sort_List(this, sort_level);

	} 
	else
	{
		if ( !PointColors.Count() || !PointWidths.Count() )
		{
			Render_Seg_Line(rinfo);
		}
		else
		{
			Render_Streak_Line(rinfo);
		}
	}
}

// ?Get_Obj_Space_Bounding_Sphere@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	// Get object-space bounding box and create bounding sphere from it
	AABoxClass box;
	Get_Obj_Space_Bounding_Box(box);

	// Create object-space bounding sphere from the bounding box:
	sphere.Center = box.Center;
	sphere.Radius = box.Extent.Length();
}

// ?Get_Obj_Space_Bounding_Box@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	unsigned int num_points = PointLocations.Count();
	
	// Line must have at least two points to be valid
	
	if (num_points >= 2) {

		// Find object-space axis-aligned bounding box
		Vector3 max_coords;
		Vector3 min_coords;
		unsigned int i;

		// We create two bounding boxes; one from the points, and if we have random noise
		// subdivision we create another one from the midpoints and factor the noise amplitude
		// into the second box, and then combine the two.

		// First bounding box:
		max_coords = PointLocations[0];
		min_coords = PointLocations[0];
		for (i = 1; i < num_points; i++) {
			max_coords.Update_Max(PointLocations[i]);
			min_coords.Update_Min(PointLocations[i]);
		}
		// Enlarge bounding box by half the width
		float enlarge_factor = LineRenderer.Get_Width() * 0.5f;
		Vector3 enlarge_offset;
		enlarge_offset.Set(enlarge_factor, enlarge_factor, enlarge_factor);
		max_coords += enlarge_offset;
		min_coords -= enlarge_offset;

		if (MaxSubdivisionLevels > 0) {
			// Second bounding box:
			Vector3 max_coords2;
			Vector3 min_coords2;
			Vector3 midpoint = (PointLocations[0] + PointLocations[1]) * 0.5f;
			max_coords2 = midpoint;
			min_coords2 = midpoint;
			for (i = 1; i < num_points - 1; i++) {
				midpoint = (PointLocations[i] + PointLocations[i + 1]) * 0.5f;
				max_coords2.Update_Max(midpoint);
				min_coords2.Update_Min(midpoint);
			}

			// We ignore the actual number of subdivision levels: we multiply the random noise
			// amplitude by 2, which is the limit as the number of subdivision levels goes to
			// infinity.
			enlarge_factor += (2 * LineRenderer.Get_Noise_Amplitude());
			enlarge_offset.Set(enlarge_factor, enlarge_factor, enlarge_factor);
			max_coords2 += enlarge_offset;
			min_coords2 -= enlarge_offset;

			// Combine the two:
			max_coords.Update_Max(max_coords2);
			min_coords.Update_Min(min_coords2);
		}

		box.Init_Min_Max(min_coords, max_coords);

	} else {
		// Invalid line - return something
		box.Init(Vector3(0,0,0),Vector3(1,1,1));
	}
}

// ?Prepare_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Prepare_LOD(CameraClass &camera)
{
	// Find the maximum screen dimension of the object in pixels
	NormalizedScreenArea = Get_Screen_Size(camera);

//	// Find and set texture reduction factor
//   Set_Texture_Reduction_Factor(Calculate_Texture_Reduction_Factor(NormalizedScreenArea));

	// Ensure subdivision level is legal
	unsigned int lvl = LineRenderer.Get_Current_Subdivision_Level();
	lvl = MIN(lvl, MaxSubdivisionLevels);
	LineRenderer.Set_Current_Subdivision_Level(lvl);

	// Prepare LOD processing if the line has subdivision enabled:
	if (MaxSubdivisionLevels > 0) {
		// Add myself to the LOD optimizer:
		PredictiveLODOptimizerClass::Add_Object(this);
	} else {
		// Not added to optimizer, need to add cost
		PredictiveLODOptimizerClass::Add_Cost(Get_Cost());
	}
}

// ?Increment_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Increment_LOD(void)
{
	unsigned int lvl = LineRenderer.Get_Current_Subdivision_Level();
	
	lvl = MIN(lvl+1,MaxSubdivisionLevels);
	
	LineRenderer.Set_Current_Subdivision_Level(lvl);
}

// ?Decrement_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Decrement_LOD(void)
{
	int lvl = LineRenderer.Get_Current_Subdivision_Level();
	if (lvl == 0) return;
	LineRenderer.Set_Current_Subdivision_Level(lvl-1);
}

// ?Get_Cost@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Cost(void) const
{
	return Get_Num_Polys();
}

// ?Get_Value@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Value(void) const
{
	// If we are at the minimum LOD, we must return AT_MIN_LOD.
	if (LineRenderer.Get_Current_Subdivision_Level() == 0) {
		return AT_MIN_LOD;
	} else {
		float polycount = (float)Get_Num_Polys();
		float benefit_factor = 1.0f - (0.5f / (polycount * polycount));
		return (benefit_factor * NormalizedScreenArea) / Get_Cost();
	}
}

// ?Get_Post_Increment_Value@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Post_Increment_Value(void) const
{
	// If we are at the maximum LOD, we must return AT_MIN_LOD.
	if (LineRenderer.Get_Current_Subdivision_Level() == MaxSubdivisionLevels) {
		return AT_MAX_LOD;
	} else {
		// Assumption: each subdivision level doubles polycount
		float polycount = 2.0f * (float)Get_Num_Polys();
		float benefit_factor = 1.0f - (0.5f / (polycount * polycount));
		// Assumption: Cost() == polycount
		return (benefit_factor * NormalizedScreenArea) / polycount;
	}
}

// ?Set_LOD_Level@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_LOD_Level(int lod)
{
	lod = MAX(0, lod);
	lod = MIN(lod, (int)MaxSubdivisionLevels);

	LineRenderer.Set_Current_Subdivision_Level((unsigned int)lod);
}

// ?Get_LOD_Level@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_LOD_Level(void) const
{
	return (int) LineRenderer.Get_Current_Subdivision_Level();
}

// ?Get_LOD_Count@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_LOD_Count(void) const
{
	return (int)MaxSubdivisionLevels;
}
/*
// ?Set_Texture_Reduction_Factor@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture_Reduction_Factor(float trf)
{
	if (LineRenderer.Peek_Texture()) LineRenderer.Peek_Texture()->Set_Reduction_Factor(trf);
}*/

 

// ?Render_Seg_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Render_Seg_Line(RenderInfoClass & rinfo)
{
	// Line must have at least two points to be valid
	if (PointLocations.Count() < 2) return;

	SphereClass bounding_sphere;
	Get_Obj_Space_Bounding_Sphere(bounding_sphere);			
 
//	LineRenderer.Set_Width(rand()%3);

	LineRenderer.Render(
		rinfo,
		Transform,
		PointLocations.Count(),
		&(PointLocations[0]),
		bounding_sphere
		);
}


// ?Render_Streak_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Render_Streak_Line(RenderInfoClass & rinfo)
{

	WWASSERT(PointLocations.Count() == PointColors.Count());
	WWASSERT(PointLocations.Count() == PointWidths.Count());

	// Line must have at least two points to be valid
	if (PointLocations.Count() < 2) return;
	if (PointColors.Count() < 2) return;
	if (PointWidths.Count() < 2) return;

	if(PointLocations.Count() != PointColors.Count()) return;
	if(PointLocations.Count() != PointWidths.Count()) return;

	SphereClass bounding_sphere;
	Get_Obj_Space_Bounding_Sphere(bounding_sphere);			


//	StreakRenderer.Render(
//		rinfo,
//		Transform,
//		PointLocations.Count(),
//		&(PointLocations[0]),
//		bounding_sphere
//		);
	StreakRenderer.RenderStreak(
		rinfo,
		Transform,
		PointLocations.Count(),
		&(PointLocations[0]),
		&(PointColors[0]),
		&(PointWidths[0]),
		bounding_sphere,
		Personalities
		);
}


// ?Cast_Ray@StreakLineClass@@ present-unmatched
bool StreakLineClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;

	bool retval = false;

	//
	//	Check each line segment against the ray
	//
	float fraction = 1.0F;
	for (uint32 index = 1; index < (unsigned int)PointLocations.Count(); index ++) 
	{
#ifdef ALLOW_TEMPORARIES
		Vector3 curr_start	= Transform * PointLocations[index-1];
		Vector3 curr_end		= Transform * PointLocations[index];
		LineSegClass line_seg (curr_start, curr_end);
#else
		Vector3 curr[2];
		Transform.mulVector3Array(&PointLocations[index-1], curr, 2);
		LineSegClass line_seg(curr[0], curr[1]);
#endif
		
		Vector3 p0;
		Vector3 p1;
		if (raytest.Ray.Find_Intersection (line_seg, &p0, &fraction, &p1, NULL)) {
			
			//
			//	Determine if the ray was close enough to this line to be
			// considered intersecting
			//
			float dist = (p0 - p1).Length ();
			if (dist <= LineRenderer.Get_Width() && fraction >= 0 && fraction < raytest.Result->Fraction) {
			//if (dist <= Width && fraction < raytest.Result->Fraction) {
				retval = true;
				break;
			}
		}			
	}

	//
	//	Fill in the raytest structure if we were successfull
	//
	if (retval) {
		raytest.Result->Fraction		= fraction;
		raytest.Result->SurfaceType	= SURFACE_TYPE_DEFAULT;
		raytest.CollidedRenderObj		= this;
	}

	return retval;
}


