// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/seglinerenderer.cpp                    $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "seglinerenderer.h"
#include "ww3d.h"
class CameraClass;
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#include "random.h"
#include "v3_rnd.h"
#include "meshgeometry.h"

#ifndef W3D_ELINE_TILED_TEXTURE_MAP
#define W3D_ELINE_MERGE_INTERSECTIONS 				0x00000001
#define W3D_ELINE_FREEZE_RANDOM						0x00000002
#define W3D_ELINE_DISABLE_SORTING					0x00000004
#define W3D_ELINE_END_CAPS 							0x00000008
#define W3D_ELINE_TEXTURE_MAP_MODE_MASK 			0xFF000000
#define W3D_ELINE_TEXTURE_MAP_MODE_OFFSET 		24
#define W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP		0x00000000
#define W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP 	0x00000001
#define W3D_ELINE_TILED_TEXTURE_MAP					0x00000002
#define W3D_ELINE_DEFAULT_BITS	(W3D_ELINE_MERGE_INTERSECTIONS | (W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP << W3D_ELINE_TEXTURE_MAP_MODE_OFFSET))
struct W3dEmitterLinePropertiesStruct
{
	uint32			Flags;
	uint32			SubdivisionLevel;
	float32			NoiseAmplitude;
	float32			MergeAbortFactor;
	float32			TextureTileFactor;
	float32			UPerSec;
	float32			VPerSec;
	uint32			Reserved[9];
};
#endif


/* We have chunking logic which handles N segments at a time. To simplify the subdivision logic,
** we will ensure that N is a power of two and that N >= 2^MAX_SEGLINE_SUBDIV_LEVELS, so that the
** subdivision logic can be inside the chunking loop.
*/

#if MAX_SEGLINE_SUBDIV_LEVELS > 7
#define SEGLINE_CHUNK_SIZE (1 << MAX_SEGLINE_SUBDIV_LEVELS)
#else
#define SEGLINE_CHUNK_SIZE (128)
#endif

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define MAX_SEGLINE_POINT_BUFFER_SIZE (1 + SEGLINE_CHUNK_SIZE)
// This macro depends on the assumption that each line segment is two polys.
#define MAX_SEGLINE_POLY_BUFFER_SIZE (SEGLINE_CHUNK_SIZE * 2)




SegLineRendererClass::SegLineRendererClass(void) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		_BFME_Unknown_Member(0.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(WW3D::Get_Sync_Time()),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
	// EMPTY
}

SegLineRendererClass::SegLineRendererClass(const SegLineRendererClass & that) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		_BFME_Unknown_Member(0.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(that.LastUsedSyncTime),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
	*this = that;
}

// ?SegLineRendererClass::operator= present-unmatched
SegLineRendererClass & SegLineRendererClass::operator = (const SegLineRendererClass & that)
{
	if (this != &that) {
		REF_PTR_SET(Texture,that.Texture);
		Shader = that.Shader;
		Width = that.Width;
		Color = that.Color;
		Opacity = that.Opacity;
		SubdivisionLevel = that.SubdivisionLevel;
		NoiseAmplitude = that.NoiseAmplitude;
		MergeAbortFactor = that.MergeAbortFactor;
		TextureTileFactor = that.TextureTileFactor;
		LastUsedSyncTime = that.LastUsedSyncTime;
		CurrentUVOffset = that.CurrentUVOffset;
		UVOffsetDeltaPerMS = that.UVOffsetDeltaPerMS;
		Bits = that.Bits;
		// Don't modify m_vertexBufferSize and m_vertexBuffer
	}
	return *this;
}

SegLineRendererClass::~SegLineRendererClass(void)
{
	// BFME reorders these vs GeneralsMD: the vertex buffer is freed before the
	// texture reference (verified against the dtor at 0x960030). The texture
	// release is a bare conditional call (no NULL-out), so it tail-jmps.
	delete [] m_vertexBuffer;
	if (Texture) Texture->Release_Ref();
}

void SegLineRendererClass::Init(const W3dEmitterLinePropertiesStruct & props)
{
	// translate the flags
	Set_Merge_Intersections(props.Flags & W3D_ELINE_MERGE_INTERSECTIONS);
	Set_Freeze_Random(props.Flags & W3D_ELINE_FREEZE_RANDOM);
	Set_Disable_Sorting(props.Flags & W3D_ELINE_DISABLE_SORTING);
	Set_End_Caps(props.Flags & W3D_ELINE_END_CAPS);

	int texture_mode = ((props.Flags & W3D_ELINE_TEXTURE_MAP_MODE_MASK) >> W3D_ELINE_TEXTURE_MAP_MODE_OFFSET);
	switch (texture_mode) 
	{
	case W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_WIDTH_TEXTURE_MAP);
		break;
	case W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_LENGTH_TEXTURE_MAP);		
		break;
	case W3D_ELINE_TILED_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(TILED_TEXTURE_MAP);		
		break;
	};

	// install all other settings
	Set_Current_Subdivision_Level(props.SubdivisionLevel);
	Set_Noise_Amplitude(props.NoiseAmplitude);
	Set_Merge_Abort_Factor(props.MergeAbortFactor);
	Set_Texture_Tile_Factor(props.TextureTileFactor);
	Set_UV_Offset_Rate(Vector2(props.UPerSec,props.VPerSec));
}


// ?SegLineRendererClass::Set_Texture present-unmatched
void SegLineRendererClass::Set_Texture(TextureClass *texture)
{ 
	REF_PTR_SET(Texture,texture); 
}

// ?SegLineRendererClass::Get_Texture present-unmatched
TextureClass * SegLineRendererClass::Get_Texture(void) const
{
	if (Texture != NULL) {
		Texture->Add_Ref();
	}
	return Texture;
}

// ?SegLineRendererClass::Set_Current_UV_Offset present-unmatched
void SegLineRendererClass::Set_Current_UV_Offset(const Vector2 & offset)
{
	CurrentUVOffset = offset;
}

void SegLineRendererClass::Set_Texture_Tile_Factor(float factor)
{
	// Care should be taken to avoid tiling a texture too many times over a single polygon;
	// otherwise performance may be adversely affected.
	///@todo: I raised this number and didn't see much difference on our min-spec. -MW
	const static float MAX_LINE_TILING_FACTOR = 50.0f;
	if (factor > MAX_LINE_TILING_FACTOR) {
		WWDEBUG_SAY(("Texture (%s) Tile Factor (%.2f) too large in SegLineRendererClass!\r\n", Get_Texture()->Get_Texture_Name(), TextureTileFactor));
		factor = MAX_LINE_TILING_FACTOR;
	} else {
		factor = MAX(factor, 0.0f);
	}
	TextureTileFactor = factor;
}

void SegLineRendererClass::Reset_Line(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	CurrentUVOffset.Set(0.0f,0.0f);
}



void SegLineRendererClass::Render
(	
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	const SphereClass & obj_sphere,
	Vector4 * rgbas
)
{
	// BFME match note: Render is the DX8/Direct3D render path (DynamicVBAccess,
	// DX8Wrapper draw calls) — not reproducible with the byte-match toolchain, so
	// its body is stubbed to let the 12 non-DX8 methods in this TU compile and
	// locate. Render itself is intentionally left unmatched.
}


// ?SegLineRendererClass::subdivision_util present-unmatched (addr 0x9602A0, size 1724; scheduling drift at +0x28 near Is_Freeze_Random; Vector3SolidBoxRandomizer callees unresolved)
void SegLineRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
	const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
	float *subdiv_tex_v, Vector4 *base_diffuse, Vector4 *subdiv_diffuse)
{
	// CAUTION: freezing the random offsets will make it more readily apparent that the offsets
	// are in camera space rather than worldspace.
	int freeze_random = Is_Freeze_Random();
	Random3Class randomize;
	const float oo_int_max = 1.0f / (float)INT_MAX;
	Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
	Vector3 randvec(0,0,0);
	unsigned int sub_pidx = 0;

	struct SegLineSubdivision {
		Vector3			StartPos;
		Vector3			EndPos;
		float				StartTexV;	// V texture coordinate of start point
		float				EndTexV;		// V texture coordinate of end point
		Vector4			StartDiffuse;
		Vector4			EndDiffuse;
		float				Rand;
		unsigned int	Level;		// Subdivision level
	};

	SegLineSubdivision stack[2 * MAX_SEGLINE_SUBDIV_LEVELS];	// Maximum number needed
	int tos = 0;

	for (unsigned int pidx = 0; pidx < point_cnt - 1; pidx++) {

		// Subdivide the (pidx, pidx + 1) segment. Produce pidx and all subdivided points up to
		// (not including) pidx + 1.
		tos = 0;
		stack[0].StartPos = xformed_pts[pidx];
		stack[0].EndPos = xformed_pts[pidx + 1];
		stack[0].StartTexV = base_tex_v[pidx];
		stack[0].EndTexV = base_tex_v[pidx + 1];
		
		if (base_diffuse) {
			stack[0].StartDiffuse = base_diffuse[pidx];
			stack[0].EndDiffuse = base_diffuse[pidx+1];
		} else {
			stack[0].StartDiffuse.Set(Color.X, Color.Y, Color.Z, Opacity);
			stack[0].EndDiffuse = stack[0].StartDiffuse;
		}

		stack[0].Rand = NoiseAmplitude;
		stack[0].Level = 0;

		for (; tos >= 0;) {
			if (stack[tos].Level == SubdivisionLevel) {
				// Generate point location and texture V coordinate
				xformed_subdiv_pts[sub_pidx] = stack[tos].StartPos;
				subdiv_tex_v[sub_pidx] = stack[tos].StartTexV;
				subdiv_diffuse[sub_pidx] = stack[tos].StartDiffuse;

				sub_pidx = sub_pidx + 1;

				// Pop
				tos--;
			} else {
				// Recurse down: pop existing entry and push two subdivided ones.
				if (freeze_random) {
					randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
				} else {
					randomizer.Get_Vector(randvec);
				}
				stack[tos + 1].StartPos = stack[tos].StartPos;
				stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
				stack[tos + 1].StartTexV = stack[tos].StartTexV;
				stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
				stack[tos + 1].StartDiffuse = stack[tos].StartDiffuse;
				stack[tos + 1].EndDiffuse = (stack[tos].StartDiffuse + stack[tos].EndDiffuse) * 0.5f;
				stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
				stack[tos + 1].Level = stack[tos].Level + 1;
				stack[tos].StartPos = stack[tos + 1].EndPos;
				// stack[tos].EndPos already has the right value
				stack[tos].StartTexV = stack[tos + 1].EndTexV;
				// stack[tos].EndTexV already has the right value
				stack[tos].Rand = stack[tos + 1].Rand;
				stack[tos].Level = stack[tos + 1].Level;
				tos++;
			}
		}
	}
	// Last point
	xformed_subdiv_pts[sub_pidx] = xformed_pts[point_cnt - 1];
	subdiv_tex_v[sub_pidx] = base_tex_v[point_cnt - 1];
	if (base_diffuse) {
		subdiv_diffuse[sub_pidx] = base_diffuse[point_cnt - 1];
	} else {
		subdiv_diffuse[sub_pidx].Set(Color.X, Color.Y, Color.Z, Opacity);
	}

	sub_pidx = sub_pidx + 1;

	// Output:
	*p_sub_point_cnt = sub_pidx;
}

// ?SegLineRendererClass::Scale present-unmatched
void SegLineRendererClass::Scale(float scale)
{
	Width *= scale;
	NoiseAmplitude *= scale;
}

VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)
{
	// TODO: use a stl vector instead of our own array.
	if (number > m_vertexBufferSize)
	{
		unsigned int numberToAlloc = number + (number >> 1);
		delete [] m_vertexBuffer;
		m_vertexBuffer = W3DNEWARRAY VertexFormatXYZDUV1[numberToAlloc];
		m_vertexBufferSize = numberToAlloc;
	}

	return m_vertexBuffer;
}
