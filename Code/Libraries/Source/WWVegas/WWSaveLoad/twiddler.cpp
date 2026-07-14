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
 *                 Project Name : WWSaveLoad                                                   *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwsaveload/twiddler.cpp                      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 12/10/01 12:40p                                             $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "twiddler.h"
#include "random.h"
#include "saveloadids.h"
#include "simpledefinitionfactory.h"
#include "persistfactory.h"
#include "win.h"
#include "wwhack.h"
#include "systimer.h"


DECLARE_FORCE_LINK( Twiddler )

//////////////////////////////////////////////////////////////////////////////////
//	Constants
//////////////////////////////////////////////////////////////////////////////////
enum
{
	CHUNKID_VARIABLES			= 0x00000100,
	CHUNKID_BASE_CLASS		= 0x00000200,
};

enum
{
	VARID_DEFINTION_ID		= 0x01,
	VARID_INDIRECT_CLASSID,
};


//////////////////////////////////////////////////////////////////////////////////
//
//	Static factories
//
//////////////////////////////////////////////////////////////////////////////////
DECLARE_DEFINITION_FACTORY(TwiddlerClass, CLASSID_TWIDDLERS, "Twiddler")	_TwiddlerFactory;
SimplePersistFactoryClass<TwiddlerClass, CHUNKID_TWIDDLER>						_TwiddlerPersistFactory;


//////////////////////////////////////////////////////////////////////////////////
//
//	TwiddlerClass
//
//////////////////////////////////////////////////////////////////////////////////
// ??0TwiddlerClass@@ present-unmatched
TwiddlerClass::TwiddlerClass (void)
	:	m_IndirectClassID (0)

{
	CLASSID_DEFIDLIST_PARAM (TwiddlerClass, m_DefinitionList, 0, m_IndirectClassID, "Preset List");
	return ;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	~TwiddlerClass
//
//////////////////////////////////////////////////////////////////////////////////
// ??1TwiddlerClass@@ present-unmatched
TwiddlerClass::~TwiddlerClass (void)
{
	return ;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Twiddle
//
//////////////////////////////////////////////////////////////////////////////////
DefinitionClass *
// ?Twiddle@TwiddlerClass@@ present-unmatched
TwiddlerClass::Twiddle (void) const
{
	DefinitionClass *definition = NULL;

	if (m_DefinitionList.Count () > 0) {

		//
		//	Get a random index into our definition list
		//
		RandomClass randomizer (TIMEGETTIME ());
		int index = randomizer (0, m_DefinitionList.Count () - 1);

		//
		//	Lookup the definition this entry represents
		//
		int def_id = m_DefinitionList[index];
		definition = DefinitionMgrClass::Find_Definition (def_id);
	}

	return definition;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Create
//
//////////////////////////////////////////////////////////////////////////////////
PersistClass *
// ?Create@TwiddlerClass@@ present-unmatched
TwiddlerClass::Create (void) const
{
	PersistClass *retval = NULL;

	//
	//	Pick a random definition
	//
	DefinitionClass *definition = Twiddle ();
	if (definition != NULL) {

		//
		//	Indirect the creation to the definition we randomly selected
		//
		retval = definition->Create ();

	}

	return retval;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Get_Factory
//
//////////////////////////////////////////////////////////////////////////////////
const PersistFactoryClass &
// ?Get_Factory@TwiddlerClass@@ present-unmatched
TwiddlerClass::Get_Factory (void) const
{
	return _TwiddlerPersistFactory;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Save
//
//////////////////////////////////////////////////////////////////////////////////
bool
// ?Save@TwiddlerClass@@ present-unmatched
TwiddlerClass::Save (ChunkSaveClass &csave)
{
	bool retval = true;

	csave.Begin_Chunk (CHUNKID_VARIABLES);
		retval &= Save_Variables (csave);
	csave.End_Chunk ();

	csave.Begin_Chunk (CHUNKID_BASE_CLASS);
		retval &= DefinitionClass::Save (csave);
	csave.End_Chunk ();

	return retval;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Load
//
//////////////////////////////////////////////////////////////////////////////////
bool
// ?Load@TwiddlerClass@@ present-unmatched
TwiddlerClass::Load (ChunkLoadClass &cload)
{
	bool retval = true;

	while (cload.Open_Chunk ()) {
		switch (cload.Cur_Chunk_ID ()) {

			case CHUNKID_VARIABLES:
				retval &= Load_Variables (cload);
				break;

			case CHUNKID_BASE_CLASS:
				retval &= DefinitionClass::Load (cload);
				break;
		}

		cload.Close_Chunk ();
	}

	return retval;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Save_Variables
//
//////////////////////////////////////////////////////////////////////////////////
bool
// ?Save_Variables@TwiddlerClass@@ present-unmatched
TwiddlerClass::Save_Variables (ChunkSaveClass &csave)
{
	WRITE_MICRO_CHUNK (csave, VARID_INDIRECT_CLASSID, m_IndirectClassID)

	for (int index = 0; index < m_DefinitionList.Count (); index ++) {

		//
		//	Save this definition ID to the chunk
		//
		int def_id = m_DefinitionList[index];
		WRITE_MICRO_CHUNK (csave, VARID_DEFINTION_ID, def_id)
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Load_Variables
//
//////////////////////////////////////////////////////////////////////////////////
bool
// ?Load_Variables@TwiddlerClass@@ present-unmatched
TwiddlerClass::Load_Variables (ChunkLoadClass &cload)
{
	//
	//	Start fresh
	//
	m_DefinitionList.Delete_All ();

	//
	//	Loop through all the microchunks that define the variables
	//
	while (cload.Open_Micro_Chunk ()) {
		switch (cload.Cur_Micro_Chunk_ID ()) {

			READ_MICRO_CHUNK (cload, VARID_INDIRECT_CLASSID, m_IndirectClassID)

			case VARID_DEFINTION_ID:
			{
				//
				//	Read the definition ID from the chunk and add it
				// to our list
				//
				int def_id = 0;
				cload.Read (&def_id, sizeof (def_id));
				m_DefinitionList.Add (def_id);
			}
			break;
		}

		cload.Close_Micro_Chunk ();
	}

	return true;
}