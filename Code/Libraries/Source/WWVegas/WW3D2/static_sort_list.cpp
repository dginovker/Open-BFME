// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

/*************************************************************************************************** 
 ***                  C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               *** 
 *************************************************************************************************** 
 *                                                                                                 * 
 *                     Project Name : G                                                            * 
 *                                                                                                 * 
 *                         $Archive::                                                             $* 
 *                                                                                                 * 
 *                          Creator::Scott K. Bowen - 7/15/2002                                        *
 *                                                                                                 * 
 *                          $Author::                                                             $* 
 *                                                                                                 * 
 *                         $Modtime::                                                             $* 
 *                                                                                                 * 
 *                        $Revision::                                                             $* 
 *                                                                                                 * 
 *-------------------------------------------------------------------------------------------------* 
 * Functions:                                                                                      * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - -  - - */

////////////////////////////////////////////////////////////////////////////////////////////////////
// Include files ///////////////////////////////////////////////////////////////////////////////////

#include "static_sort_list.h"

#include "rendobj.h"
#include "dx8renderer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization Functions ////////////////////////////////////////////////////////////////////////

DefaultStaticSortListClass::DefaultStaticSortListClass(void) :
	StaticSortListClass(),
	SortLists(),
	MinSort(1),
	MaxSort(MAX_SORT_LEVEL)
{
}

DefaultStaticSortListClass::~DefaultStaticSortListClass(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Virtual functions ///////////////////////////////////////////////////////////////////////////////

// ?Add_To_List@DefaultStaticSortListClass@@UAEXPAVRenderObjClass@@I@Z present-unmatched
void DefaultStaticSortListClass::Add_To_List(RenderObjClass * robj, unsigned int sort_level)
{
	if(sort_level < 1 || sort_level > MAX_SORT_LEVEL) {
		WWASSERT(0);
		return;
	}
	SortLists[sort_level].Add_Tail(robj, false);
}

// ?Render_And_Clear@DefaultStaticSortListClass@@UAEXAAVRenderInfoClass@@@Z present-unmatched
void DefaultStaticSortListClass::Render_And_Clear(RenderInfoClass & rinfo)
{
	// We go from higher sort level to lower, since lower sort level means higher priority (in
	// front), so lower sort level meshes need to be rendered later.
	for(unsigned int sort_level = MaxSort; sort_level >= MinSort; sort_level--) {
		bool render=false;
		for (	RenderObjClass *robj = SortLists[sort_level].Remove_Head(); robj;
				robj->Release_Ref(), robj = SortLists[sort_level].Remove_Head())
		{
			if (robj->Get_Render_Hook()) {
				if (robj->Get_Render_Hook()->Pre_Render(robj, rinfo)) {
					robj->Render(rinfo);
					render = true;
				}
				robj->Get_Render_Hook()->Post_Render(robj, rinfo);
			} else {
				robj->Render(rinfo);
				render = true;
			}
		}
		if (render) TheDX8MeshRenderer.Flush();
	}
}

