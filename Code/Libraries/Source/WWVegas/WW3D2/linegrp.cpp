// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4; neutralize the old name in this TU.
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Linegroup.cpp                                                *
 *                                                                                             *
 *                     $Archive::                                                             $*
 *                                                                                             *
 *              Original Author:: Hector Yee                                                   *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 2                                                            $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "sharebuf.h"
#include "linegrp.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8wrapper.h"
#include "wwmath.h"
class CameraClass;
#include "rinfo.h"
#include "camera.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

// Line groups are a rendering primitive similar to point groups
// They are tetrahedra which are aligned with the view plane with their centers
// at StartLineLoc. The apex of the tetrahedron is at EndLineLoc.
// They can be individually colored LineDiffuse
// and the LineUCoord determines the U coordinate of the texture to use
// the V coordinate is always 0 at the flat end of the tetrahedron
// and 1 at the apex
LineGroupClass::LineGroupClass(void) :
	StartLineLoc(NULL),
	EndLineLoc(NULL),
	LineDiffuse(NULL),
	TailDiffuse(NULL),
	ALT(NULL),
	LineSize(NULL),
	LineUCoord(NULL),
	LineCount(0),
	Texture(NULL),
	Flags(0),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	DefaultLineSize(0.0f),
	DefaultLineColor(1.0f, 1.0f, 1.0f),
	DefaultLineAlpha(1.0f),		
	DefaultLineUCoord(0.0f),
	DefaultTailDiffuse(0.0f, 0.0f, 0.0f, 0.0f),
	LineMode(TETRAHEDRON)
{
}

// ?LineGroupClass::~LineGroupClass present-unmatched
LineGroupClass::~LineGroupClass(void)
{
	REF_PTR_RELEASE(StartLineLoc);
	REF_PTR_RELEASE(EndLineLoc);
	REF_PTR_RELEASE(LineDiffuse);
	REF_PTR_RELEASE(TailDiffuse);
	REF_PTR_RELEASE(ALT);
	REF_PTR_RELEASE(LineSize);
	REF_PTR_RELEASE(LineUCoord);
	REF_PTR_RELEASE(Texture);
}

void LineGroupClass::Set_Arrays(
	ShareBufferClass<Vector3> *startlocs,
	ShareBufferClass<Vector3> *endlocs,
	ShareBufferClass<Vector4> *diffuse,		
	ShareBufferClass<Vector4> *taildiffuse,
	ShareBufferClass<unsigned int> *alt,
	ShareBufferClass<float> *sizes,	
	ShareBufferClass<float> *ucoords, 
	int active_line_count
	)
{
	// The Line locations arrays are NOT optional!
	WWASSERT(startlocs);
	WWASSERT(endlocs);

	// Ensure lengths of all arrays are the same:
	WWASSERT(startlocs->Get_Count() == endlocs->Get_Count());
	WWASSERT(!diffuse || startlocs->Get_Count() == diffuse->Get_Count());
	WWASSERT(!alt || startlocs->Get_Count() == alt->Get_Count());
	WWASSERT(!sizes || startlocs->Get_Count() == sizes->Get_Count());	
	WWASSERT(!ucoords || startlocs->Get_Count() == ucoords->Get_Count());
	WWASSERT(!taildiffuse || startlocs->Get_Count() == taildiffuse->Get_Count());

	REF_PTR_SET(StartLineLoc,startlocs);
	REF_PTR_SET(EndLineLoc,endlocs);
	REF_PTR_SET(LineDiffuse,diffuse);
	REF_PTR_SET(TailDiffuse,taildiffuse);
	REF_PTR_SET(ALT,alt);
	REF_PTR_SET(LineSize,sizes);	
	REF_PTR_SET(LineUCoord,ucoords);

	if (ALT) {
		LineCount = active_line_count;
	} else {
		LineCount = (active_line_count >= 0) ? active_line_count : StartLineLoc->Get_Count();
	}

}

// ?LineGroupClass::Set_Line_Size present-unmatched
void LineGroupClass::Set_Line_Size(float size)
{
	DefaultLineSize = size;
}

// ?LineGroupClass::Get_Line_Size present-unmatched
float LineGroupClass::Get_Line_Size(void)
{
	return DefaultLineSize;
}

// ?LineGroupClass::Set_Line_Color present-unmatched
void LineGroupClass::Set_Line_Color(const Vector3 &color)
{
	DefaultLineColor = color;
}

Vector3 LineGroupClass::Get_Line_Color(void)
{
	return DefaultLineColor;
}

void LineGroupClass::Set_Tail_Diffuse(const Vector4 &tdiffuse)
{
	DefaultTailDiffuse = tdiffuse;
}

Vector4 LineGroupClass::Get_Tail_Diffuse(void)
{
	return DefaultTailDiffuse;
}

// ?LineGroupClass::Set_Line_Alpha present-unmatched
void LineGroupClass::Set_Line_Alpha(float alpha)
{
	DefaultLineAlpha = alpha;
}

// ?LineGroupClass::Get_Line_Alpha present-unmatched
float LineGroupClass::Get_Line_Alpha(void)
{
	return DefaultLineAlpha;
}

// ?LineGroupClass::Set_Line_UCoord present-unmatched
void LineGroupClass::Set_Line_UCoord(float ucoord)
{
	DefaultLineUCoord = ucoord;
}

// ?LineGroupClass::Get_Line_UCoord present-unmatched
float LineGroupClass::Get_Line_UCoord(void)
{
	return DefaultLineUCoord;
}

void LineGroupClass::Set_Flag(FlagsType flag, bool on)
{
	if (on) Flags |= 1 << flag; 
	else 
		Flags &= ~(1 << flag);
}

// ?LineGroupClass::Get_Flag present-unmatched
int LineGroupClass::Get_Flag(FlagsType flag)
{
	return (Flags >> flag) & 0x1;
}

// ?LineGroupClass::Set_Texture present-unmatched
void LineGroupClass::Set_Texture(TextureClass* texture)
{
	REF_PTR_SET(Texture,texture);
}

// ?LineGroupClass::Get_Texture present-unmatched
TextureClass * LineGroupClass::Get_Texture(void)
{
	if (Texture) Texture->Add_Ref();
	return Texture;
}

// ?LineGroupClass::Peek_Texture present-unmatched
TextureClass * LineGroupClass::Peek_Texture(void)
{
	return Texture;
}

// ?LineGroupClass::Set_Shader present-unmatched
void LineGroupClass::Set_Shader(const ShaderClass &shader)
{
	Shader = shader;
}

// ?LineGroupClass::Get_Shader present-unmatched
ShaderClass LineGroupClass::Get_Shader(void)
{
	return Shader;
}

// ?LineGroupClass::Set_Line_Mode present-unmatched
void LineGroupClass::Set_Line_Mode(LineModeType linemode)
{
	LineMode = linemode;
}

// ?LineGroupClass::Get_Line_Mode present-unmatched
LineGroupClass::LineModeType LineGroupClass::Get_Line_Mode(void)
{
	return LineMode;
}

// ?LineGroupClass::Render present-unmatched
void	LineGroupClass::Render(RenderInfoClass &rinfo)
{
	// BFME match note: Render is the DX8/Direct3D render path — stubbed so the
	// other LineGroupClass methods compile and locate. Left unmatched.
}

int LineGroupClass::Get_Polygon_Count(void)
{
	switch (LineMode) {
		case TETRAHEDRON:
			return LineCount * 4;
			break;
		case PRISM:
			return LineCount * 8;
			break;
	}
	WWASSERT(0);
	return 0;
}