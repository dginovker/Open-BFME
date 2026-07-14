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

#include "dx8rendererdebugger.h"
#include "hashtemplate.h"
#include "mesh.h"
#include "meshmdl.h"

static HashTemplateClass<unsigned, MeshClass*> MeshHash;

bool DX8RendererDebugger::Enabled;

// ?Enable@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable(bool enable)
{
	Enabled=true;
}

// ?Get_String@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Get_String(StringClass& s)
{
	if (!Enabled) {
		s="";
		return;
	}
	s="\n\n\n\n";

	int cnt=0;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		StringClass tmp(0,true);
		MeshClass* mesh=ite.Peek_Value();
		MeshModelClass* mmc=mesh->Peek_Model();
		int polys=0;
		int verts=0;
		if (mmc) {
			polys=mmc->Get_Polygon_Count();
			verts=mmc->Get_Vertex_Count();
		}
		tmp.Format("id: %5.5d mesh: %s %d polys, %d verts",
			ite.Peek_Key(),
			mesh->Get_Name(),
			polys,
			verts);
		s+=tmp;
		if (mesh->Is_Disabled_By_Debugger()) {
			s+=" (disabled)\n";
		}
		else {
			s+="\n";
		}
		cnt++;
		if (cnt>20) break;
	}

}

// ?Update@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Update()
{
	// Release references to all meshes and empty the hash
	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Release_Ref();
	}
	MeshHash.Remove_All();

//	if (!Enabled) return;
}

#ifdef WWDEBUG
// ?Add_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Add_Mesh(MeshClass* mesh)
{
	if (!Enabled) return;

	// Don't insert the same mesh twice
	if (MeshHash.Get(mesh->Get_Debug_Id())) return;

	mesh->Add_Ref();
	MeshHash.Insert(mesh->Get_Debug_Id(),mesh);
}
#endif

// ?Disable_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Disable_Mesh(unsigned id)
{
	if (!Enabled) return;
	MeshClass* mesh=MeshHash.Get(id);
	if (!mesh) return;
	mesh->Set_Debugger_Disable(true);
}

// ?Enable_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable_Mesh(unsigned id)
{
	if (!Enabled) return;
	MeshClass* mesh=MeshHash.Get(id);
	if (!mesh) return;
	mesh->Set_Debugger_Disable(false);
}

// ?Disable_All@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Disable_All()
{
	if (!Enabled) return;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Set_Debugger_Disable(true);
	}
}

// ?Enable_All@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable_All()
{
	if (!Enabled) return;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Set_Debugger_Disable(false);
	}
}

