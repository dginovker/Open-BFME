// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
class CameraClass;
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
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/meshmdl.cpp                            $*
 *                                                                                             *
 *                    Org Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 48                                                          $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "meshmdl.h"
#include "matinfo.h"
#include "aabtree.h"
#include "htree.h"
#include "vp.h"
#include "visrasterizer.h"
#include "dx8polygonrenderer.h"
#include "bwrender.h"
#include "camera.h"
#include "dx8renderer.h"
#include "hashtemplate.h"


/*
** Temporary Buffers
** These buffers are used by the skin code for temporary storage of the deformed vertices and 
** vertex normals.  
*/
static DynamicVectorClass<Vector3>	_TempVertexBuffer;
static DynamicVectorClass<Vector3>	_TempNormalBuffer;
static DynamicVectorClass<Vector4>	_TempTransformedVertexBuffer;
static DynamicVectorClass<unsigned long> _TempClipFlagBuffer;


/*
**
** MeshModelClass Implementation
**
*/


// ?MeshModelClass::MeshModelClass present-unmatched
MeshModelClass::MeshModelClass(void) :
	DefMatDesc(NULL),
	AlternateMatDesc(NULL),
	CurMatDesc(NULL),
	MatInfo(NULL),
	GapFiller(NULL)
{
	Set_Flag(DIRTY_BOUNDS,true);

	DefMatDesc = W3DNEW MeshMatDescClass;
	CurMatDesc = DefMatDesc;
	
	MatInfo = NEW_REF( MaterialInfoClass, () );
	
	return ;
}

// ?MeshModelClass::MeshModelClass present-unmatched
MeshModelClass::MeshModelClass(const MeshModelClass & that) :
	MeshGeometryClass(that),
	DefMatDesc(NULL),
	AlternateMatDesc(NULL),
	CurMatDesc(NULL),
	MatInfo(NULL),
	GapFiller(NULL),
	HasBeenInUse(false)
{
	DefMatDesc = W3DNEW MeshMatDescClass(*(that.DefMatDesc));
	if (that.AlternateMatDesc != NULL) {
		AlternateMatDesc = W3DNEW MeshMatDescClass(*(that.AlternateMatDesc));
	}
	CurMatDesc = DefMatDesc;

	clone_materials(that);
	return ;
}

// ?MeshModelClass::~MeshModelClass present-unmatched
MeshModelClass::~MeshModelClass(void)
{
//	WWDEBUG_SAY(("Note: Mesh %s was never used\n",Get_Name()));
	TheDX8MeshRenderer.Unregister_Mesh_Type(this);

	Reset(0,0,0);
	REF_PTR_RELEASE(MatInfo);

	if (DefMatDesc != NULL) {
		delete DefMatDesc;
	}
	if (AlternateMatDesc != NULL) {
		delete AlternateMatDesc;
	}
	return ;
}

// ?MeshModelClass::operator= present-unmatched
MeshModelClass & MeshModelClass::operator = (const MeshModelClass & that)
{
	if (this != &that) {
		// Remove all polygon renderers, this will remove the mesh from the rendering system.
		// The mesh will be initialized to rendering system the next time it is rendered.
		TheDX8MeshRenderer.Unregister_Mesh_Type(this);

		MeshGeometryClass::operator = (that);

		*DefMatDesc = *(that.DefMatDesc);
		CurMatDesc = DefMatDesc;

		if (AlternateMatDesc != NULL) {
			delete AlternateMatDesc;
			AlternateMatDesc = NULL;
		}

		if (that.AlternateMatDesc != NULL) {
			AlternateMatDesc = W3DNEW MeshMatDescClass(*(that.AlternateMatDesc));
		}

		clone_materials(that);

		if (GapFiller) {
			// DMS - using approriate deallocation method
			delete GapFiller;
			GapFiller=NULL;
		}
		if (that.GapFiller) GapFiller=W3DNEW GapFillerClass(*that.GapFiller);
	}
	return * this;
}

// ?MeshModelClass::Reset present-unmatched
void MeshModelClass::Reset(int polycount,int vertcount,int passcount)
{
	//DMS - We must delete the gapfiller object BEFORE the geometry is reset.  Otherwise,
	// the number of stages and passes gets reset and the gapfiller cannot deallocate properly.
	delete GapFiller;
	GapFiller=NULL;

	Reset_Geometry(polycount,vertcount);

	// Release everything we have and reset to initial state

	TheDX8MeshRenderer.Unregister_Mesh_Type(this);

	MatInfo->Reset();
	DefMatDesc->Reset(polycount,vertcount,passcount);
	if (AlternateMatDesc != NULL) {
		delete AlternateMatDesc;
		AlternateMatDesc = NULL;
	}
	CurMatDesc = DefMatDesc;

	return ;
}

// ?MeshModelClass::Register_For_Rendering present-unmatched
void MeshModelClass::Register_For_Rendering()
{
	HasBeenInUse=true;
//WW3D::Set_NPatches_Level(1);
	if (WW3D::Get_NPatches_Level()>1) {
		if (WW3D::Get_NPatches_Gap_Filling_Mode()!=WW3D::NPATCHES_GAP_FILLING_DISABLED) {
			Init_For_NPatch_Rendering();
		}
		else if (GapFiller) {
			delete GapFiller;
			GapFiller=NULL;
		}
	}
	else {
		if (WW3D::Get_NPatches_Gap_Filling_Mode()==WW3D::NPATCHES_GAP_FILLING_FORCE) {
			Init_For_NPatch_Rendering();
		}
		else if (GapFiller) {
			delete GapFiller;
			GapFiller=NULL;
		}
	}

	TheDX8MeshRenderer.Register_Mesh_Type(this);
}

// ?MeshModelClass::Replace_Texture present-unmatched
void MeshModelClass::Replace_Texture(TextureClass* texture,TextureClass* new_texture)
{
	// BFME: DX8 FVF-category path stubbed.
}

// ?MeshModelClass::Replace_VertexMaterial present-unmatched
void MeshModelClass::Replace_VertexMaterial(VertexMaterialClass* vmat,VertexMaterialClass* new_vmat)
{
	// BFME: DX8 FVF-category path stubbed.
}

// ?MeshModelClass::Peek_FVF_Category_Container present-unmatched
DX8FVFCategoryContainer* MeshModelClass::Peek_FVF_Category_Container()
{
	// BFME: DX8 FVF-category path stubbed.
	return 0;
}

// ?MeshModelClass::Shadow_Render present-unmatched
void MeshModelClass::Shadow_Render(SpecialRenderInfoClass & rinfo,const Matrix3D & tm,const HTreeClass * htree)
{
	if (rinfo.BWRenderer != NULL) {
		if (_TempTransformedVertexBuffer.Length() < VertexCount) _TempTransformedVertexBuffer.Resize(VertexCount);
		Vector4* transf_ptr=&(_TempTransformedVertexBuffer[0]);
		get_deformed_screenspace_vertices(transf_ptr,rinfo,tm,htree);

		Vector2* tptr = reinterpret_cast<Vector2 *>(transf_ptr);
		Vector4* optr = transf_ptr;
		for (int a=0;a<VertexCount;++a,++optr) *tptr++=Vector2((*optr)[0],-(*optr)[1]);

		rinfo.BWRenderer->Set_Vertex_Locations(reinterpret_cast<Vector2*>(transf_ptr),VertexCount);
		rinfo.BWRenderer->Render_Triangles(reinterpret_cast<const unsigned long*>(Poly->Get_Array()),PolyCount*3);
		return;
	}
}

// ?MeshModelClass::Make_Geometry_Unique present-unmatched
void MeshModelClass::Make_Geometry_Unique()
{
	WWASSERT(Vertex);

	ShareBufferClass<Vector3> * unique_verts = NEW_REF(ShareBufferClass<Vector3>,(*Vertex));
	REF_PTR_SET(Vertex,unique_verts);
	REF_PTR_RELEASE(unique_verts);
	
	ShareBufferClass<Vector3> * norms = NEW_REF(ShareBufferClass<Vector3>,(*VertexNorm));
	REF_PTR_SET(VertexNorm,norms);
	REF_PTR_RELEASE(norms);

#if (!OPTIMIZE_PLANEEQ_RAM)
	ShareBufferClass<Vector4> * peq = NEW_REF(ShareBufferClass<Vector4>,(*PlaneEq, "MeshModelClass::PlaneEq"));	
	REF_PTR_SET(PlaneEq,peq);
	REF_PTR_RELEASE(peq);
#endif
}

// ?MeshModelClass::Make_UV_Array_Unique present-unmatched
void MeshModelClass::Make_UV_Array_Unique(int pass,int stage)
{
	CurMatDesc->Make_UV_Array_Unique(pass,stage);
}

// ?MeshModelClass::Make_Color_Array_Unique present-unmatched
void MeshModelClass::Make_Color_Array_Unique(int array_index)
{
	CurMatDesc->Make_Color_Array_Unique(array_index);
}

// ?MeshModelClass::Enable_Alternate_Material_Description present-unmatched
void MeshModelClass::Enable_Alternate_Material_Description(bool onoff)
{
	// BFME: DX8 path stubbed.
}

// ?MeshModelClass::Is_Alternate_Material_Description_Enabled present-unmatched
bool MeshModelClass::Is_Alternate_Material_Description_Enabled(void)
{
	return CurMatDesc == AlternateMatDesc;
}
/*
// ?MeshModelClass::Process_Texture_Reduction present-unmatched
void MeshModelClass::Process_Texture_Reduction(void)
{
	MatInfo->Process_Texture_Reduction();
}
*/
// ?MeshModelClass::Needs_Vertex_Normals present-unmatched
bool MeshModelClass::Needs_Vertex_Normals(void)
{
	if (Get_Flag(MeshModelClass::PRELIT_MASK) == 0) {
		return true;
	}
	return CurMatDesc->Do_Mappers_Need_Normals();
}

struct TriangleSide
{
	Vector3 loc1;
	Vector3 loc2;
	TriangleSide(const Vector3& l1,const Vector3& l2)
	{
		int i1=*(int*)&l1[0];
		i1=37*i1+*(int*)&l1[1];
		i1=37*i1+*(int*)&l1[2];
		int i2=*(int*)&l2[0];
		i2=37*i2+*(int*)&l2[1];
		i2=37*i2+*(int*)&l2[2];
		if (i1<i2) {
			loc1=l1;
			loc2=l2;
		}
		else {
			loc2=l1;
			loc1=l2;
		}
	}
	TriangleSide() {}

	bool operator== (const TriangleSide& s) 
	{
		unsigned i=*(unsigned*)&loc1[0]^*(unsigned*)&s.loc1[0];
		i|=*(unsigned*)&loc1[1]^*(unsigned*)&s.loc1[1];
		i|=*(unsigned*)&loc1[2]^*(unsigned*)&s.loc1[2];
		i|=*(unsigned*)&loc2[0]^*(unsigned*)&s.loc2[0];
		i|=*(unsigned*)&loc2[1]^*(unsigned*)&s.loc2[1];
		i|=*(unsigned*)&loc2[2]^*(unsigned*)&s.loc2[2];
		return !i;
	}
};

// Get_Hash_Value specialization for Vector3.

template <> inline unsigned int HashTemplateKeyClass<Vector3>::Get_Hash_Value(const Vector3& location)
{
	const unsigned char* buffer=(const unsigned char*)&location;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(Vector3);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

// Get_Hash_Value specialization for TriangleSide.

template <> inline unsigned int HashTemplateKeyClass<TriangleSide>::Get_Hash_Value(const TriangleSide& side)
{
	const unsigned char* buffer=(const unsigned char*)&side;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(TriangleSide);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

struct SideIndexInfo
{
	unsigned short vidx1;
	unsigned short vidx2;
	unsigned polygon_index;
	SideIndexInfo() {}
	SideIndexInfo(int i) { WWASSERT(0); }
};


HashTemplateClass<Vector3, unsigned> LocationHash;
HashTemplateClass<Vector3, unsigned> DuplicateLocationHash;
HashTemplateClass<TriangleSide,SideIndexInfo> SideHash;

// ----------------------------------------------------------------------------
//
// Allocate a gap-filler object. The constructor allocates memory for the
// maximum possible amount of gap polygons, which is quite much. After all
// the gap polygons have been added to the arrays, Shrink_Arrays() should
// be called to free up all unneeded memory.
//
// ----------------------------------------------------------------------------

// ?GapFillerClass::GapFillerClass present-unmatched
GapFillerClass::GapFillerClass(MeshModelClass* mmc_) : mmc(NULL), PolygonCount(0)
{
	//DMS - We cannot take a reference to the mesh model here!  This is because the mesh model
	// class OWNS the GapFiller class (allocated via NEW).  If we take a reference here, there
	// will be an extra reference on the parent object, which will result in the parent object
	// not being destroyed.
	//
//	REF_PTR_SET(mmc,mmc_);
	mmc = mmc_;

	ArraySize=mmc->Get_Polygon_Count()*6;	// Each side of each triangle can have 2 polygons added, in the worst case
	PolygonArray=W3DNEWARRAY TriIndex[ArraySize];
	for (int pass=0;pass<mmc->Get_Pass_Count();++pass) {
		for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
			if (mmc->Has_Texture_Array(pass,stage)) {
				TextureArray[pass][stage]=W3DNEWARRAY TextureClass*[ArraySize];
			}
			else TextureArray[pass][stage]=NULL;
		}

		if (mmc->Has_Material_Array(pass)) {
			MaterialArray[pass]=W3DNEWARRAY VertexMaterialClass*[ArraySize];
		}
		else MaterialArray[pass]=NULL;

		if (mmc->Has_Shader_Array(pass)) {
			ShaderArray[pass]=W3DNEWARRAY ShaderClass[ArraySize];
		}
		else ShaderArray[pass]=NULL;
	}
}

// ?GapFillerClass::GapFillerClass present-unmatched
GapFillerClass::GapFillerClass(const GapFillerClass& that) : mmc(NULL), PolygonCount(that.PolygonCount)
{
	//DMS - We cannot take a reference to the mesh model here!  This is because the mesh model
	// class OWNS the GapFiller class (allocated via NEW).  If we take a reference here, there
	// will be an extra reference on the parent object, which will result in the parent object
	// not being destroyed.
	//
//	REF_PTR_SET(mmc,that.mmc);
	mmc = that.mmc;

	ArraySize=that.ArraySize;
	PolygonArray=W3DNEWARRAY TriIndex[ArraySize];
	for (int pass=0;pass<mmc->Get_Pass_Count();++pass) {
		for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
			if (that.TextureArray[pass][stage]) {
				TextureArray[pass][stage]=W3DNEWARRAY TextureClass*[ArraySize];
				for (unsigned i=0;i<PolygonCount;++i) {
					TextureArray[pass][stage][i]=that.TextureArray[pass][stage][i];
					TextureArray[pass][stage][i]->Add_Ref();
				}
			}
			else TextureArray[pass][stage]=NULL;
		}

		if (that.MaterialArray[pass]) {
			MaterialArray[pass]=W3DNEWARRAY VertexMaterialClass*[ArraySize];
			for (unsigned i=0;i<PolygonCount;++i) {
				MaterialArray[pass][i]=that.MaterialArray[pass][i];
				MaterialArray[pass][i]->Add_Ref();
			}
		}
		else MaterialArray[pass]=NULL;

		if (that.ShaderArray[pass]) {
			ShaderArray[pass]=W3DNEWARRAY ShaderClass[ArraySize];
			for (unsigned i=0;i<PolygonCount;++i) {
				ShaderArray[pass][i]=that.ShaderArray[pass][i];
			}
		}
		else ShaderArray[pass]=NULL;
	}
}

// ----------------------------------------------------------------------------
//
// Destruct gap-filler object. Release references to all textures and release
// the arrays.
//
// ----------------------------------------------------------------------------

// ?GapFillerClass::~GapFillerClass present-unmatched
GapFillerClass::~GapFillerClass()
{
	delete[] PolygonArray;

	for (int pass=0;pass<mmc->Get_Pass_Count();++pass) {
		for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
			if (TextureArray[pass][stage]) {

				for (unsigned i=0;i<PolygonCount;++i) {
					REF_PTR_RELEASE(TextureArray[pass][stage][i]);
				}
				delete[] TextureArray[pass][stage];
			}
		}

		if (MaterialArray[pass]) {
			for (unsigned i=0;i<PolygonCount;++i) {
				REF_PTR_RELEASE(MaterialArray[pass][i]);
			}
			delete[] MaterialArray[pass];
		}

		delete[] ShaderArray[pass];
	}

	// DMS - Removed - See constructor for details.
//	REF_PTR_RELEASE(mmc);
}

// ----------------------------------------------------------------------------
//
// Add polygon to gap filler.
//
// ----------------------------------------------------------------------------

// ?GapFillerClass::Add_Polygon present-unmatched
void GapFillerClass::Add_Polygon(unsigned polygon_index,unsigned vidx1,unsigned vidx2, unsigned vidx3)
{
	WWASSERT(PolygonCount<ArraySize);
	WWASSERT(vidx1!=vidx2 && vidx1!=vidx3 && vidx2!=vidx3);
Vector3 loc1=mmc->Get_Vertex_Array()[vidx1];
Vector3 loc2=mmc->Get_Vertex_Array()[vidx2];
Vector3 loc3=mmc->Get_Vertex_Array()[vidx3];
WWASSERT(loc1==loc2 || loc1==loc3 || loc2==loc3);
//sdflksdjflsdkf
//vidx1=mmc->Get_Polygon_Array()[polygon_index][0];
//vidx2=mmc->Get_Polygon_Array()[polygon_index][1];
//vidx3=mmc->Get_Polygon_Array()[polygon_index][2];

	PolygonArray[PolygonCount]=TriIndex(vidx1,vidx2,vidx3);
	for (int pass=0;pass<mmc->Get_Pass_Count();++pass) {
		if (mmc->Has_Shader_Array(pass)) {
			ShaderArray[pass][PolygonCount]=mmc->Get_Shader(polygon_index,pass);
		}
		if (mmc->Has_Material_Array(pass)) {
//			MaterialArray[pass][PolygonCount]=mmc->Get_Material(polygon_index,pass);
			MaterialArray[pass][PolygonCount]=mmc->Get_Material(mmc->Get_Polygon_Array()[polygon_index][0],pass);
		}
		for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
			if (mmc->Has_Texture_Array(pass,stage)) {
				TextureArray[pass][stage][PolygonCount]=mmc->Get_Texture(polygon_index,pass,stage);
			}
		}
	}
	PolygonCount++;
}

// ----------------------------------------------------------------------------
//
// Resize buffers to match the polygon count exatly. After this call no more
// polygons can be added to the buffers.
//
// ----------------------------------------------------------------------------

// ?GapFillerClass::Shrink_Buffers present-unmatched
void GapFillerClass::Shrink_Buffers()
{
	if (PolygonCount==ArraySize) return;

	// Shrink the polygon array
	TriIndex* new_polygon_array=W3DNEWARRAY TriIndex[PolygonCount];
	memcpy(new_polygon_array,PolygonArray,PolygonCount*sizeof(TriIndex));
	delete[] PolygonArray;
	PolygonArray=new_polygon_array;

	for (int pass=0;pass<mmc->Get_Pass_Count();++pass) {
		for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
			if (TextureArray[pass][stage]) {
				// Shrink the texture array
				TextureClass** new_texture_array=W3DNEWARRAY TextureClass*[PolygonCount];
				memcpy(new_texture_array,TextureArray[pass][stage],PolygonCount*sizeof(TextureClass*));
				delete[] TextureArray[pass][stage];
				TextureArray[pass][stage]=new_texture_array;
			}
		}

		if (MaterialArray[pass]) {
			// Shrink the material array
			VertexMaterialClass** new_material_array=W3DNEWARRAY VertexMaterialClass*[PolygonCount];
			memcpy(new_material_array,MaterialArray[pass],PolygonCount*sizeof(VertexMaterialClass*));
			delete[] MaterialArray[pass];
			MaterialArray[pass]=new_material_array;
		}

		if (ShaderArray[pass]) {
			// Shrink the shader array
			ShaderClass* new_shader_array=W3DNEWARRAY ShaderClass[PolygonCount];
			memcpy(new_shader_array,ShaderArray[pass],PolygonCount*sizeof(ShaderClass));
			delete[] ShaderArray[pass];
			ShaderArray[pass]=new_shader_array;
		}
	}
	ArraySize=PolygonCount;
}

// ----------------------------------------------------------------------------
//
// Hard edges cause gaps to n-patches meshes. This code searches for hard edges
// and adds gaps filler polygons, using existing vertices.
//
// ----------------------------------------------------------------------------

// ?MeshModelClass::Init_For_NPatch_Rendering present-unmatched
void MeshModelClass::Init_For_NPatch_Rendering()
{
	// BFME: DX8 path stubbed.
}
