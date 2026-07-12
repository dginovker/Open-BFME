// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4; neutralize the old name in this TU
// so mapper.h (forward-decls class Matrix4x4) and camera.h agree. No matched
// function mangles Matrix4x4 (verified), so this is a pure rename.
#define Matrix4x4 Matrix4
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

/*************************************************************************** 
 ***    C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S     *** 
 *************************************************************************** 
 *                                                                         * 
 *                 Project Name : G                                        * 
 *                                                                         * 
 *                     $Archive:: /VSS_Sync/ww3d2/pointgr.cpp             $* 
 *                                                                         * 
 *                    Org Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 38                                      $* 
 *                                                                         * 
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 *   PointGroupClass::PointGroupClass -- PointGroupClass CTor.             * 
 *   PointGroupClass::~PointGroupClass -- PointGroupClass DTor.            * 
 *   PointGroupClass::operator = -- PointGroupClass assignment operator.   * 
 *   PointGroupClass::Set_Arrays -- Set point location/color/enable arrays.* 
 *   PointGroupClass::Set_Point_Size -- Set default point size.            * 
 *   PointGroupClass::Get_Point_Size -- Get default point size.            * 
 *   PointGroupClass::Set_Point_Color -- Set default point color.          * 
 *   PointGroupClass::Get_Point_Color -- Get default point color.          * 
 *   PointGroupClass::Set_Point_Alpha -- Set default point alpha.          * 
 *   PointGroupClass::Get_Point_Alpha -- Get default point alpha.          * 
 *   PointGroupClass::Set_Point_Orientation -- Set default point orientatio* 
 *   PointGroupClass::Get_Point_Orientation -- Get default point orientatio* 
 *   PointGroupClass::Set_Point_Frame -- Set default point frame.          * 
 *   PointGroupClass::Get_Point_Frame -- Get default point frame.          * 
 *   PointGroupClass::Set_Point_Mode -- Set point rendering method.        * 
 *   PointGroupClass::Get_Point_Mode -- Get point rendering method.        * 
 *   PointGroupClass::Set_Flag -- Set given flag to on or off.             * 
 *   PointGroupClass::Get_Flag -- Get current value (on/off) of given flag.* 
 *   PointGroupClass::Set_Texture -- Set texture used.                     * 
 *   PointGroupClass::Get_Texture -- Get texture used.                     * 
 *   PointGroupClass::Set_Shader -- Set shader used.                       * 
 *   PointGroupClass::Get_Shader -- Get shader used.                       * 
 *   PointGroupClass::Set_Billboard -- Set whether to billboard.           *
 *   PointGroupClass::Get_Billboard -- Get whether to billboard.           *
 *   PointGroupClass::Get_Discrete_Orientation_Count_Log2 -- what it says  * 
 *   PointGroupClass::Set_Discrete_Orientation_Count_Log2 -- what it says. * 
 *   PointGroupClass::Get_Frame_Row_Column_Count_Log2 -- what it says      * 
 *   PointGroupClass::Set_Frame_Row_Column_Count_Log2 -- what it says.     * 
 *   PointGroupClass::Get_Polygon_Count -- Get estimated polygon count.    * 
 *   PointGroupClass::Render -- draw point group.                          * 
 *   PointGroupClass::vInstance -- Create instance of class.               * 
 *   PointGroupClass::sGetClassName -- Get name of class.                  * 
 *   PointGroupClass::Update_Arrays -- Update all arrays used in rendering *
 *   PointGroupClass::Peek_Texture -- Peeks texture                        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include "pointgr.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "aabox.h"
#include "statistics.h"
#include "simplevec.h"
#include "texture.h"
#include "vector.h"
#include "vp.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
class CameraClass;
#include "rinfo.h"
#include "camera.h"
#include "dx8fvf.h"
#include "D3dx8math.h"
#include "sortingrenderer.h"

// Upgraded to DX8 2/2/01 HY

// static data members
Vector3 PointGroupClass::_TriVertexLocationOrientationTable[256][3];
Vector3 PointGroupClass::_QuadVertexLocationOrientationTable[256][4];
Vector2 *PointGroupClass::_TriVertexUVFrameTable[5] = { NULL, NULL, NULL, NULL, NULL};
Vector2 *PointGroupClass::_QuadVertexUVFrameTable[5] = { NULL, NULL, NULL, NULL, NULL};
VertexMaterialClass *PointGroupClass::PointMaterial=NULL;

// Static arrays for intermediate calcs (never resized down, just up):
VectorClass<Vector3>		PointGroupClass::compressed_loc;		// point locations 'compressed' by APT
VectorClass<Vector4>		PointGroupClass::compressed_diffuse;	// point colors 'compressed' by APT
VectorClass<float>			PointGroupClass::compressed_size;		// point sizes 'compressed' by APT
VectorClass<unsigned char>	PointGroupClass::compressed_orient;	// point orientations 'compressed' by APT
VectorClass<unsigned char>	PointGroupClass::compressed_frame;		// point frames 'compressed' by APT
VectorClass<Vector3>		PointGroupClass::transformed_loc;		// transformed point locations

// This array has vertex locations for screenspace mode - calculated to cover exactly 1x1 and 2x2 pixels.
Vector3 PointGroupClass::_ScreenspaceVertexLocationSizeTable[2][3] =
{
	Vector3(0.5f, 0.0f, -1.0f), 
	Vector3(1.0f, 1.0f, -1.0f),
	Vector3(0.0f, 1.0f, -1.0f), 
	Vector3(1.0f, -0.5f, -1.0f),
	Vector3(2.7f, 2.0f, -1.0f), 
	Vector3(-0.7f, 2.0f, -1.0f)
};

// useful for particles that aren't aligned with the screen.
static Vector3 GroundMultiplierX(1.0f, 0.0f, 0.0f);
static Vector3 GroundMultiplierY(0.0f, 1.0f, 0.0f);

// Some internal variables
VectorClass<Vector3>			VertexLoc;		// camera-space vertex locations
VectorClass<Vector4>			VertexDiffuse;	// vertex diffuse/alpha colors
VectorClass<Vector2>			VertexUV;		// vertex texture coords

// Some DX 8 variables
#define MAX_VB_SIZE			2048
#define MAX_TRI_POINTS		MAX_VB_SIZE/3
#define MAX_TRI_IB_SIZE		3*MAX_TRI_POINTS
#define MAX_QUAD_POINTS		MAX_VB_SIZE/4
#define MAX_QUAD_IB_SIZE	6*MAX_QUAD_POINTS

DX8IndexBufferClass			*Tris, *Quads;						// Index buffers.
SortingIndexBufferClass		*SortingTris, *SortingQuads;	// Sorting index buffers.

/************************************************************************** 
 * PointGroupClass::PointGroupClass -- PointGroupClass CTor.              * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
PointGroupClass::PointGroupClass(void) :
	PointLoc(NULL),
	PointDiffuse(NULL),	
	APT(NULL),
	PointSize(NULL),
	PointOrientation(NULL),
	PointFrame(NULL),
	PointCount(0),
	FrameRowColumnCountLog2(0),
	Texture(NULL),
	Flags(0),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	PointMode(TRIS),
	DefaultPointSize(0.0f),
	DefaultPointColor(1.0f, 1.0f, 1.0f),
	DefaultPointAlpha(1.0f),	
	DefaultPointOrientation(0),
	DefaultPointFrame(0),
	VPXMin(0.0f),
	VPYMin(0.0f),
	VPXMax(0.0f),
	VPYMax(0.0f)
{
}

/************************************************************************** 
 * PointGroupClass::~PointGroupClass -- PointGroupClass DTor.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::~PointGroupClass present-unmatched
PointGroupClass::~PointGroupClass(void)
{
	if (PointLoc) {
		PointLoc->Release_Ref();
		PointLoc = NULL;
	}
	if (PointDiffuse) {
		PointDiffuse->Release_Ref();
		PointDiffuse=NULL;
	}
	if (APT) {
		APT->Release_Ref();
		APT = NULL;
	}
	if (PointSize) {
		PointSize->Release_Ref();
		PointSize = NULL;
	}
	if (PointOrientation) {
		PointOrientation->Release_Ref();
		PointOrientation = NULL;
	}
	if (PointFrame) {
		PointFrame->Release_Ref();
		PointFrame = NULL;
	}
	if (Texture) {
		REF_PTR_RELEASE(Texture);		
		Texture = NULL;
	}
}

/************************************************************************** 
 * PointGroupClass::operator = -- PointGroupClass assignment operator.    * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::operator= present-unmatched
PointGroupClass & PointGroupClass::operator = (const PointGroupClass & that)
{
	if (this != &that) {
		WWASSERT(0);	// If you hit this assert implement the function!
	}
	return *this;
}


/************************************************************************** 
 * PointGroupClass::Set_Arrays -- Set point location/color/enable arrays. * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * NOTES:	colors, alphas, APT, sizes, orientations and frames are       *
 *          optional. active_point_count can also be used with a NULL apt.*
 *          In this case active_point_count is ignored if it is -1        *
 *          (default value) and otherwise it indicates the first N active *
 *          points in the arrays.                                         * 
 *          The view plane rectangle may optionally be passed as well -   * 
 *				this is only used in SCREENSPACE mode.                        * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *   08/25/1999 NH  : Alphas added.                                       * 
 *   06/28/2000 NH  : Orientations and frames added.                      * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
void PointGroupClass::Set_Arrays(
	ShareBufferClass<Vector3> *locs,
	ShareBufferClass<Vector4> *diffuse,		
	ShareBufferClass<unsigned int> *apt,
	ShareBufferClass<float> *sizes,
	ShareBufferClass<unsigned char> *orientations,
	ShareBufferClass<unsigned char> *frames, 
	int active_point_count,
	float vpxmin, 
	float vpymin, 
	float vpxmax, 
	float vpymax)
{
	// The point locations array is NOT optional!
	WWASSERT(locs);

	// Ensure lengths of all arrays are the same:
	WWASSERT(!diffuse || locs->Get_Count() == diffuse->Get_Count());
	WWASSERT(!apt || locs->Get_Count() == apt->Get_Count());
	WWASSERT(!sizes || locs->Get_Count() == sizes->Get_Count());
	WWASSERT(!orientations || locs->Get_Count() == orientations->Get_Count());
	WWASSERT(!frames || locs->Get_Count() == frames->Get_Count());

	REF_PTR_SET(PointLoc,locs);
	REF_PTR_SET(PointDiffuse,diffuse);
	REF_PTR_SET(APT,apt);
	REF_PTR_SET(PointSize,sizes);
	REF_PTR_SET(PointOrientation,orientations);
	REF_PTR_SET(PointFrame,frames);

	if (APT) {
		PointCount = active_point_count;
	} else {
		PointCount = (active_point_count >= 0) ? active_point_count : PointLoc->Get_Count();
	}

	// Store view plane rectangle (only used in SCREENSPACE mode)
	VPXMin = vpxmin;
	VPYMin = vpymin;
	VPXMax = vpxmax;
	VPYMax = vpymax;
}

/************************************************************************** 
 * PointGroupClass::Set_Point_Size -- Set default point size.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This size is ignored if a size array is present.             * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Size present-unmatched
void PointGroupClass::Set_Point_Size(float size)
{
	DefaultPointSize = size;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Size -- Get default point size.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This size is ignored if a size array is present.             * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Size present-unmatched
float PointGroupClass::Get_Point_Size(void)
{
	return DefaultPointSize;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Color -- Set default point color.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This color is ignored if a color array is present.           * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/20/1999 NH  : Created.                                            * 
 *========================================================================*/
void PointGroupClass::Set_Point_Color(Vector3 color)
{
	DefaultPointColor = color;
}

/************************************************************************** 
 * PointGroupClass::Get_Point_Color -- Get default point color.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This color is ignored if a color array is present.           * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/20/1999 NH  : Created.                                            * 
 *========================================================================*/
Vector3 PointGroupClass::Get_Point_Color(void)
{
	return DefaultPointColor;
}

/************************************************************************** 
 * PointGroupClass::Set_Point_Alpha -- Set default point alpha.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This alpha is ignored if an alpha array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   08/25/1999 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Alpha present-unmatched
void PointGroupClass::Set_Point_Alpha(float alpha)
{
	DefaultPointAlpha = alpha;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Alpha -- Get default point alpha.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This alpha is ignored if an alpha array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   08/25/1999 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Alpha present-unmatched
float PointGroupClass::Get_Point_Alpha(void)
{
	return DefaultPointAlpha;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Orientation -- Set default point orientation* 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This is ignored if an orientation array is present.          * 
 *                                                                        * 
 * NOTE: No need to ensure value in valid range - it will be masked later.*
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Orientation present-unmatched
void PointGroupClass::Set_Point_Orientation(unsigned char orientation)
{
	DefaultPointOrientation = orientation;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Orientation -- Get default point orientation* 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This is ignored if an orientation array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Orientation present-unmatched
unsigned char PointGroupClass::Get_Point_Orientation(void)
{
	return DefaultPointOrientation;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Frame -- Set default point frame.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This frame is ignored if an frame array is present.          * 
 *                                                                        * 
 * NOTE: No need to ensure value in valid range - it will be masked later.*
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Frame present-unmatched
void PointGroupClass::Set_Point_Frame(unsigned char frame)
{
	DefaultPointFrame = frame;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Frame -- Get default point frame.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This frame is ignored if an frame array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Frame present-unmatched
unsigned char PointGroupClass::Get_Point_Frame(void)
{
	return DefaultPointFrame;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Mode -- Set point rendering method.         * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Mode present-unmatched
void PointGroupClass::Set_Point_Mode(PointModeEnum mode)
{
	PointMode = mode;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Mode -- Get point rendering method.         * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Mode present-unmatched
PointGroupClass::PointModeEnum PointGroupClass::Get_Point_Mode(void)
{
	return PointMode;
}


/************************************************************************** 
 * Set_Flag -- PointGroupClass::Set given flag to on or off.              * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
void PointGroupClass::Set_Flag(FlagsType flag, bool onoff)
{
	if (onoff) Flags|=1<<flag; 
	else 
		Flags&=~(1<<flag);
}

/************************************************************************** 
 * PointGroupClass::Get_Flag -- Get current value (on/off) of given flag. *
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Flag present-unmatched
int PointGroupClass::Get_Flag(FlagsType flag)
{
	return (Flags>>flag) & 0x1;
}

/************************************************************************** 
 * PointGroupClass::Set_Texture -- Set texture used.                      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Texture present-unmatched
void PointGroupClass::Set_Texture(TextureClass* texture)
{
	REF_PTR_SET(Texture,texture);
}

/************************************************************************** 
 * PointGroupClass::Get_Texture -- Get texture used.                      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Get_Texture present-unmatched
TextureClass * PointGroupClass::Get_Texture(void)
{
	if (Texture) Texture->Add_Ref();
	return Texture;
}


/***********************************************************************************************
 * PointGroupClass::Peek_Texture -- Peeks texture                                              *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/12/2001  hy : Created.                                                                  *
 *=============================================================================================*/
// ?PointGroupClass::Peek_Texture present-unmatched
TextureClass * PointGroupClass::Peek_Texture(void)
{
	return Texture;
}

/************************************************************************** 
 * PointGroupClass::Set_Shader -- Set shader used.                        * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:	the primary gradient will be set to MODULATE/DISABLE in    *
 * 				the shader depending on whether a color or alpha array was *
 * 				passed in Set_Point_Arrays. also, texturing will be        *
 * 				enabled or disabled dependent on whether a non-NULL        *
 * 				texture was set.                                           *
 *					these will override the primary gradient/texturing         *
 *					settings in the given shader.                              *
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Shader present-unmatched
void PointGroupClass::Set_Shader(ShaderClass shader)
{
	Shader = shader;
}


/************************************************************************** 
 * PointGroupClass::Get_Shader -- Get shader used.                        * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Get_Shader present-unmatched
ShaderClass PointGroupClass::Get_Shader(void)
{
	return Shader;
}

/************************************************************************** 
 * PointGroupClass::Set_Billboard -- Set whether to Billboard.            * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/25/2002 JM  : Created.                                            *
 *========================================================================*/
// BFME drift: PointGroupClass has no Billboard member (a BILLBOARD flag replaced
// it — see the ctor's Set_Flag usage), so Set_Billboard/Get_Billboard are absent.

/************************************************************************** 
 * PointGroupClass::Get_Billboard -- Get whether to Billboard.            * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/25/2002 JM  : Created.                                            *
 *========================================================================*/


/************************************************************************** 
 * PointGroupClass::Get_Frame_Row_Column_Count_Log2 -- what it says       * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     * 
 *========================================================================*/
// ?PointGroupClass::Get_Frame_Row_Column_Count_Log2 present-unmatched
unsigned char PointGroupClass::Get_Frame_Row_Column_Count_Log2(void)
{
	return FrameRowColumnCountLog2;
}


/************************************************************************** 
 * PointGroupClass::Set_Frame_Row_Column_Count_Log2 -- what it says.      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Frame_Row_Column_Count_Log2 present-unmatched
void PointGroupClass::Set_Frame_Row_Column_Count_Log2(unsigned char frccl2)
{
	FrameRowColumnCountLog2 = MIN(frccl2, 4);
}

/************************************************************************** 
 * PointGroupClass::Get_Polygon_Count -- Get estimated polygon count.     * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/18/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
int PointGroupClass::Get_Polygon_Count(void)
{
	switch (PointMode) {
		case TRIS:
		case SCREENSPACE:
			return PointCount;
			break;
		case QUADS:
			return PointCount * 2;
			break;
	}
	WWASSERT(0);
	return 0;
}

/************************************************************************** 
 * PointGroupClass::Render -- draw point group.                           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   12/10/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
static SimpleVecClass<unsigned long> remap;
// ?PointGroupClass::Render present-unmatched
void PointGroupClass::Render(RenderInfoClass &rinfo, int unknown)
{
	// BFME match note: Render is the DX8/Direct3D render path — not reproducible
	// with the byte-match toolchain, so its body is stubbed to let the other
	// PointGroupClass methods compile and locate.
}






/************************************************************************** 
 * PointGroupClass::RenderVolumeParticles -- draw a point group.sandwich  * 
 *                                                                        * 
 *	This is a specialized renderer. It will draw the particle repeatedly  * 
 *  while attenuating opacity appropriately, and bumping the z-position.  *
 *  This is actually done by cloning the particle over and over at        * 
 *  successively closer positions to the camera. Very Slow!               *
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:      USE SPARINGLY, IT IS EXPENSIVE!!!!!                     * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   12/03/2002	Mark Lorenzen		Created.                                  * 
 *																		                                    *
 *========================================================================*/
#define MAX_VOLUME_PARTICLE_DEPTH ( 16 )
// ?PointGroupClass::RenderVolumeParticle present-unmatched
void PointGroupClass::RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth )
{
	// BFME match note: RenderVolumeParticle is the DX8/Direct3D render path — not reproducible
	// with the byte-match toolchain, so its body is stubbed to let the other
	// PointGroupClass methods compile and locate.
}
