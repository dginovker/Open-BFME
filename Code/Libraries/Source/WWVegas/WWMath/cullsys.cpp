// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep


#include "cullsys.h"
#include "wwdebug.h"
#include "wwprofile.h"


/*************************************************************************
**
** CullableClass Implementation
**
*************************************************************************/
CullableClass::CullableClass(void) :
	CullLink(NULL),
	NextCollected(NULL)
{
	CullBox.Init(Vector3(0,0,0),Vector3(1,1,1));
}

CullableClass::~CullableClass(void)
{
	// the cull system that contains us is responsible for any culling link
	// so we better be out of it and it should have cleared our pointer before
	// we are deleted.
	WWASSERT(CullLink == NULL);
}

void CullableClass::Set_Cull_Box(const AABoxClass & box,bool just_loaded)
{
	CullBox = box;

	WWPROFILE("Cullable::Set_Cull_Box");

	// Just_loaded flag allows us to update the box without notifying the
	// culling system.  Use this when you've saved and loaded the linkage
	// so you know you're in the right node of the culling system...
	if (!just_loaded) {
		CullSystemClass * sys = Get_Culling_System();
		if (sys != NULL) {
			sys->Update_Culling(this);
		}
	}
}

void CullableClass::Set_Culling_System(CullSystemClass * sys)
{
	if (CullLink) {
		CullLink->Set_Culling_System(sys);
	}
}

CullSystemClass * CullableClass::Get_Culling_System(void) const
{
	if (CullLink) {
		return CullLink->Get_Culling_System();
	}
	return NULL;
}


/*************************************************************************
**
** CullSystemClass Implementation
**
** The base CullSystemClass mainly contains code for maintaining the
** current collection list and iterating through it.
**
*************************************************************************/
CullSystemClass::CullSystemClass(void) :
	CollectionHead(NULL)
{
}

CullSystemClass::~CullSystemClass(void)
{
}

// NOTE: THE Get_() functions currently are the same as the Peek_() functions (e.g., they do not
// add a Ref). This is wrong and will be fixed.
CullableClass * CullSystemClass::Get_First_Collected_Object_Internal(void)
{
	return CollectionHead;
}

CullableClass * CullSystemClass::Get_Next_Collected_Object_Internal(CullableClass * obj)
{
	if (obj != NULL) {
		return obj->NextCollected;
	}
	return NULL;
}

CullableClass * CullSystemClass::Peek_First_Collected_Object_Internal(void)
{
	return CollectionHead;
}

CullableClass * CullSystemClass::Peek_Next_Collected_Object_Internal(CullableClass * obj)
{
	if (obj != NULL) {
		return obj->NextCollected;
	}
	return NULL;
}

void CullSystemClass::Reset_Collection(void)
{
	CollectionHead = NULL;
}

void CullSystemClass::Add_To_Collection(CullableClass * obj)
{
	WWASSERT(obj != NULL);
	obj->NextCollected = CollectionHead;
	CollectionHead = obj;
}
