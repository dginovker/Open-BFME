// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include "gridcull.h"
#include "chunkio.h"
#include "iostruct.h"
#include "colmath.h"
#include "colmathinlines.h"


DEFINE_AUTO_POOL(GridLinkClass,256);


const uint32 GRID_CURRENT_VERSION = 0x00010000;


enum 
{
	GRID_CHUNK_VERSION					= 0x00000001,	// version wrapper, contains 32bit version #
	GRID_CHUNK_PARAMETERS				= 0x00000100,	// parameters for the grid cull system
};


struct IOGridParametersStruct
{
	IOVector3Struct	MinCellSize;	
	IOVector3Struct	Origin;
	IOVector3Struct	CellDim;
	uint32				CellCount[3];
	float32				MaxObjExtent;
};


static inline CullableClass * get_next_object(CullableClass * obj)
{
	return ((GridLinkClass *)obj->Get_Cull_Link())->Next;
}

GridLinkClass::GridLinkClass(GridCullSystemClass * system) :
	CullLinkClass(system),
	GridAddress(-1),
	Prev(NULL),
	Next(NULL)
{
}


GridCullSystemClass::GridCullSystemClass(void) :
	MinCellSize(10,10,10),
	MaxObjExtent(15),
	Origin(-100,-100,-100),
	CellDim(10,10,10),
	Cells(NULL),
	NoGridList(NULL),
	ObjCount(0),
	TerminationCellCount(TERMINATION_CELL_COUNT)
{
	CellCount[0] = CellCount[1] = CellCount[2] = 0;
	Re_Partition(Vector3(-100,-100,-100),Vector3(100,100,100),15);
	Reset_Statistics();
}


GridCullSystemClass::~GridCullSystemClass(void)
{
	if (Cells != NULL) {
		delete Cells;
		Cells = NULL;
	}
}


void GridCullSystemClass::Collect_Objects(const Vector3 & point)
{
	/*
	** Collect the objects in the grid
	*/
	VolumeStruct vol;
	init_volume(point,point,&vol);
	if (!vol.Is_Empty()) {

		int delta_x = vol.Max[0] - vol.Min[0];		
		int i,j,k;
		int address = map_indices_to_address(vol.Min[0],vol.Min[1],vol.Min[2]);
		
		for (k=vol.Min[2]; k<vol.Max[2]; k++) {
			for (j=vol.Min[1]; j<vol.Max[1]; j++) {
				for (i=vol.Min[0]; i<vol.Max[0]; i++) {
					GRIDCULL_NODE_TRIVIALLY_ACCEPTED;
					collect_objects_in_leaf(point,Cells[address]);
					address++;
				}
				address -= delta_x;
				address += CellCount[0];
			}
			address = map_indices_to_address(vol.Min[0],vol.Min[1],k+1);
		}
	}

	/*
	** Collect the objects in the no-grid-list
	*/
	collect_objects_in_leaf(point,NoGridList);
}


void GridCullSystemClass::Collect_Objects(const AABoxClass & box)
{
	/*
	** Collect the objects in the grid
	*/
	VolumeStruct vol;
	init_volume(box,&vol);

	if (!vol.Is_Empty()) {

		int delta_x = vol.Max[0] - vol.Min[0];		
		int i,j,k;
		int address = map_indices_to_address(vol.Min[0],vol.Min[1],vol.Min[2]);
		
		for (k=vol.Min[2]; k<vol.Max[2]; k++) {
			for (j=vol.Min[1]; j<vol.Max[1]; j++) {
				for (i=vol.Min[0]; i<vol.Max[0]; i++) {
					GRIDCULL_NODE_TRIVIALLY_ACCEPTED;
					collect_objects_in_leaf(box,Cells[address]);
					address++;
				}
				address -= delta_x;
				address += CellCount[0];
			}
			address = map_indices_to_address(vol.Min[0],vol.Min[1],k+1);
		}
	}
	
	/*
	** Collect the objects in the no-grid-list
	*/
	collect_objects_in_leaf(box,NoGridList);
}


void GridCullSystemClass::Collect_Objects(const OBBoxClass & box)
{
	/*
	** Collect the objects in the grid
	*/
	VolumeStruct vol;
	init_volume(box,&vol);

	if (!vol.Is_Empty()) {

		int delta_x = vol.Max[0] - vol.Min[0];		
		int i,j,k;
		int address = map_indices_to_address(vol.Min[0],vol.Min[1],vol.Min[2]);

		for (k=vol.Min[2]; k<vol.Max[2]; k++) {
			for (j=vol.Min[1]; j<vol.Max[1]; j++) {
				for (i=vol.Min[0]; i<vol.Max[0]; i++) {
					GRIDCULL_NODE_TRIVIALLY_ACCEPTED;
					collect_objects_in_leaf(box,Cells[address]);
					address++;
				}
				address -= delta_x;
				address += CellCount[0];
			}
			address = map_indices_to_address(vol.Min[0],vol.Min[1],k+1);
		}
	}

	/*
	** Collect the objects in the no-grid-list
	*/
	collect_objects_in_leaf(box,NoGridList);
}


void GridCullSystemClass::Collect_Objects(const FrustumClass & frustum)
{
	/*
	** Collect the objects in the grid
	*/
	VolumeStruct vol;
	init_volume(frustum,&vol);

	if (!vol.Is_Empty()) {

		int delta_x = vol.Max[0] - vol.Min[0];		
		int i,j,k;
		int address = map_indices_to_address(vol.Min[0],vol.Min[1],vol.Min[2]);
		
		for (k=vol.Min[2]; k<vol.Max[2]; k++) {
			for (j=vol.Min[1]; j<vol.Max[1]; j++) {
				for (i=vol.Min[0]; i<vol.Max[0]; i++) {
					GRIDCULL_NODE_TRIVIALLY_ACCEPTED;
					collect_objects_in_leaf(frustum,Cells[address]);
					address++;
				}
				address -= delta_x;
				address += CellCount[0];
			}
			address = map_indices_to_address(vol.Min[0],vol.Min[1],k+1);
		}
	}
	
	/*
	** Collect the objects in the no-grid-list
	*/
	collect_objects_in_leaf(frustum,NoGridList);
}


void GridCullSystemClass::Re_Partition(const Vector3 & input_min,const Vector3 & input_max,float objdim)
{
	/*
	** grab all objects into the collection list and unlink them from the grid
	*/
	Reset_Collection();
	Collect_And_Unlink_All();

	/*
	** Do a sanity check on the input parameters
	*/
	Vector3 min = input_min;
	Vector3 max = input_max;

	if (max.X - min.X < 1.0f) {
		max.X += MinCellSize.X;
		min.X -= MinCellSize.X;
	}
	if (max.Y - min.Y < 1.0f) {
		max.Y += MinCellSize.Y;
		min.Y -= MinCellSize.Y;
	}
	if (max.Z - min.Z < 1.0f) {
		max.Z += MinCellSize.Z;
		min.Z -= MinCellSize.Z;
	}

	/*
	** Compute the grid parameters
	*/
	Origin = min;
	Vector3 world_dim = max - min;
	MaxObjExtent = objdim;

	WWASSERT(world_dim.X > 0.0f);
	WWASSERT(world_dim.Y > 0.0f);
	WWASSERT(world_dim.Z > 0.0f);

	/*
	** how many cells should we use on each dimension?
	*/
	CellCount[0] = CellCount[1] = CellCount[2] = 1;
	CellDim = world_dim;
	bool done = false;

	while (!done) {

		/*
		** find biggest dimension
		*/
		int bigdim = 0;
		if (CellDim[1]/MinCellSize[1] > CellDim[bigdim]/MinCellSize[bigdim]) bigdim = 1;
		if (CellDim[2]/MinCellSize[2] > CellDim[bigdim]/MinCellSize[bigdim]) bigdim = 2;

		/*
		** split dimension in two if possible
		*/
		if (CellDim[bigdim] >= 2.0f * MinCellSize[bigdim]) {
			CellDim[bigdim] /= 2.0f;
			CellCount[bigdim] *= 2;
		}

		/*
		** check termination conditions
		*/
		if (total_cell_count() >= TerminationCellCount) {
			done = true;
		}

		if (	(CellDim[0] < 2.0*MinCellSize[0]) &&
				(CellDim[1] < 2.0*MinCellSize[1]) &&
				(CellDim[2] < 2.0*MinCellSize[2]) ) {
			done = true;
		}
	}

	OOCellDim.X = 1.0f / CellDim.X;
	OOCellDim.Y = 1.0f / CellDim.Y;
	OOCellDim.Z = 1.0f / CellDim.Z;

	if (Cells != NULL) {
		delete[] Cells;
	}
	Cells = W3DNEWARRAY CullableClass * [total_cell_count()];
	memset(&(Cells[0]),0,total_cell_count() * sizeof(CullableClass *));

	/*
	** iterate the collection list and re-insert all objects into the grid
	*/
	CullableClass * obj;
	for (	obj = Get_First_Collected_Object_Internal(); 
			obj != NULL; 
			obj = Get_Next_Collected_Object_Internal(obj)) 
	{
		link_object(obj);
	}
}


void GridCullSystemClass::Collect_And_Unlink_All(void)
{
	Reset_Collection();

	/*
	** pull all objects out of the grid
	*/
	for (int k=0; k<CellCount[2]; k++) {
		for (int j=0; j<CellCount[1]; j++) {
			for (int i=0; i<CellCount[0]; i++) {

				/*
				** collect and unlink all objects in cell(i,j,k)
				*/
				CullableClass * obj = Cells[map_indices_to_address(i,j,k)];
				while (obj) {
					CullableClass * nextobj = get_next_object(obj);
				
					unlink_object(obj);
					Add_To_Collection(obj);

					obj = nextobj;
				}

			}
		}
	}

	/*
	** pull all objects out of the "no-grid" list
	*/
	CullableClass * obj = NoGridList;
	while (obj) {
		CullableClass * nextobj = get_next_object(obj);
	
		unlink_object(obj);
		Add_To_Collection(obj);

		obj = nextobj;
	}
}


void GridCullSystemClass::Update_Culling(CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);
	
	int address;
	GridLinkClass * link = (GridLinkClass *)obj->Get_Cull_Link();
	map_point_to_address(obj->Get_Cull_Box().Center,address);
	
	if (address != link->GridAddress) {
		unlink_object(obj);
		link_object(obj,address);
	}
}


void GridCullSystemClass::Load(ChunkLoadClass & cload)
{
	/*
	** read the version chunk
	*/ 
	uint32 version;
	cload.Open_Chunk();
	WWASSERT(cload.Cur_Chunk_ID() == GRID_CHUNK_VERSION);
	cload.Read(&version,sizeof(version));
	cload.Close_Chunk();

	/*
	** read the parameters chunk
	*/
	IOGridParametersStruct params;
	memset(&params,0,sizeof(params));
	cload.Open_Chunk();
	WWASSERT(cload.Cur_Chunk_ID() == GRID_CHUNK_PARAMETERS);
	cload.Read(&params,sizeof(params));
	cload.Close_Chunk();

	/*
	** unlink all objects
	*/
	Collect_And_Unlink_All();

	/*
	** partition the grid according to the loaded parameters
	*/
	CellCount[0]		= params.CellCount[0];
	CellCount[1]		= params.CellCount[1];
	CellCount[2]		= params.CellCount[2];
	CellDim.X			= params.CellDim.X;
	CellDim.Y			= params.CellDim.Y;
	CellDim.Z			= params.CellDim.Z;
	MaxObjExtent		= params.MaxObjExtent;
	MinCellSize.X		= params.MinCellSize.X;
	MinCellSize.Y		= params.MinCellSize.Y;
	MinCellSize.Z		= params.MinCellSize.Z;
	Origin.X				= params.Origin.X;
	Origin.Y				= params.Origin.Y;
	Origin.Z				= params.Origin.Z;

	OOCellDim.X = 1.0f / CellDim.X;
	OOCellDim.Y = 1.0f / CellDim.Y;
	OOCellDim.Z = 1.0f / CellDim.Z;

	if (Cells != NULL) {
		delete [] Cells;
		Cells = NULL;
	}

	Cells = W3DNEWARRAY CullableClass * [total_cell_count()];
	memset(&(Cells[0]),0,total_cell_count() * sizeof(CullableClass *));

	/*
	** re-link the objects in
	*/
	CullableClass * obj;
	for (	obj = Get_First_Collected_Object_Internal(); 
			obj != NULL; 
			obj = Get_Next_Collected_Object_Internal(obj)) 
	{
		link_object(obj);
	}
}


void GridCullSystemClass::Save(ChunkSaveClass & csave)
{	
	/*
	** write the version chunk
	*/
	uint32 version = GRID_CURRENT_VERSION;
	csave.Begin_Chunk(GRID_CHUNK_VERSION);
	csave.Write(&version,sizeof(version));
	csave.End_Chunk();

	/*
	** write the grid parameters
	*/
	IOGridParametersStruct params;
	memset(&params,0,sizeof(params));
	params.CellCount[0] = CellCount[0];
	params.CellCount[1] = CellCount[1];
	params.CellCount[2] = CellCount[2];
	params.CellDim.X = CellDim.X;
	params.CellDim.Y = CellDim.Y;
	params.CellDim.Z = CellDim.Z;
	params.MaxObjExtent = MaxObjExtent;
	params.MinCellSize.X = MinCellSize.X;
	params.MinCellSize.Y = MinCellSize.Y;
	params.MinCellSize.Z = MinCellSize.Z;
	params.Origin.X = Origin.X;
	params.Origin.Y = Origin.Y;
	params.Origin.Z = Origin.Z;

	csave.Begin_Chunk(GRID_CHUNK_PARAMETERS);
	csave.Write(&params,sizeof(params));
	csave.End_Chunk();
}


void GridCullSystemClass::Reset_Statistics(void)
{
	// number of (virtual) nodes = 2n-1
	Stats.NodeCount = 2 * (CellCount[0] * CellCount[1] * CellCount[2]) - 1;
	Stats.NodesAccepted = 0;
	Stats.NodesTriviallyAccepted = 0;
	Stats.NodesRejected = 0;
}


void GridCullSystemClass::Add_Object_Internal(CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == NULL);

	GridLinkClass * link = new GridLinkClass(this);
	obj->Set_Cull_Link(link);
	link_object(obj);
	
	ObjCount++;
	obj->Add_Ref();
}


void GridCullSystemClass::link_object(CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);

	int address;
	map_point_to_address(obj->Get_Cull_Box().Center,address);

	link_object(obj,address);
}

void GridCullSystemClass::link_object(CullableClass * obj,int address)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);
	GridLinkClass * link = (GridLinkClass *)obj->Get_Cull_Link();
	WWASSERT(link != NULL);

	/*
	** if obj cannot be inserted into the grid, add it to the NoGridList
	** otherwise, insert it into the cell
	*/
	const AABoxClass & box = obj->Get_Cull_Box();
	if (	
			(box.Extent.X > MaxObjExtent) || 
			(box.Extent.Y > MaxObjExtent) || 
			(box.Extent.Z > MaxObjExtent) ||
			(address == UNGRIDDED_ADDRESS)
		) 
	{
		link->GridAddress = UNGRIDDED_ADDRESS;	
		link_object_to_list(&NoGridList,obj);
	} else {
		link->GridAddress = address;
		link_object_to_list(&(Cells[address]),obj);
	}
}

void GridCullSystemClass::unlink_object(CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);
	GridLinkClass * link = (GridLinkClass *)obj->Get_Cull_Link();

	if (link->GridAddress == UNGRIDDED_ADDRESS) {
		unlink_object_from_list(&NoGridList,obj);
	} else {
		unlink_object_from_list(&(Cells[link->GridAddress]),obj);
	}
}


void GridCullSystemClass::link_object_to_list(CullableClass ** head,CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);
	GridLinkClass * link = (GridLinkClass *)obj->Get_Cull_Link();

	/*
	** Insert this object as the new head of the list.
	*/
	link->Next = *head;
	link->Prev = NULL;

	if (link->Next != NULL) {
		GridLinkClass * next_link = (GridLinkClass *)link->Next->Get_Cull_Link();
		WWASSERT(next_link != NULL);
		next_link->Prev = obj;
	}

	*head = obj;
}


void GridCullSystemClass::unlink_object_from_list(CullableClass ** head,CullableClass * obj)
{
	WWASSERT(obj);
	WWASSERT(obj->Get_Culling_System() == this);
	GridLinkClass * link = (GridLinkClass *)obj->Get_Cull_Link();

	/*
	** check to see that the object is actually in this list
	*/
#ifdef WWDEBUG
	CullableClass * tmp = *head;
	bool found = false;
	while (tmp && !found) {
		if (tmp == obj) found = true;
		tmp = ((GridLinkClass *)(tmp->Get_Cull_Link()))->Next;
	}
	WWASSERT(found);
#endif

	/*
	** If we were the head of the list, make the head point to the next object
	*/
	if (obj == *head) {
		*head = link->Next;
	}
	
	/*
	** Link the object previous to us to our next...
	*/
	if (link->Prev) {
		GridLinkClass * prev_link = (GridLinkClass *)link->Prev->Get_Cull_Link();
		prev_link->Next = link->Next;
	}

	/*
	** Link the objects after us to our previous...
	*/
	if (link->Next) {
		GridLinkClass * next_link = (GridLinkClass *)link->Next->Get_Cull_Link();
		next_link->Prev = link->Prev;
	}

	link->Prev = NULL;
	link->Next = NULL;
}


void GridCullSystemClass::collect_objects_in_leaf(const Vector3 & point,CullableClass * head)
{
	if (head != NULL) {
		GridListIterator it(head);
		for (;!it.Is_Done(); it.Next()) {
			CullableClass * obj = it.Peek_Obj();
			if (obj->Get_Cull_Box ().Contains (point) == true) {
				Add_To_Collection(obj);
			}
		}
	}
}

void GridCullSystemClass::collect_objects_in_leaf(const AABoxClass & box,CullableClass * head)
{
	if (head != NULL) {
		GridListIterator it(head);
		for (;!it.Is_Done(); it.Next()) {
			CullableClass * obj = it.Peek_Obj();
			if (CollisionMath::Overlap_Test(box,obj->Get_Cull_Box()) != CollisionMath::OUTSIDE) {
				Add_To_Collection(obj);
			}
		}
	}
}

void GridCullSystemClass::collect_objects_in_leaf(const OBBoxClass & obbox,CullableClass * head)
{
	if (head != NULL) {
		GridListIterator it(head);
		for (;!it.Is_Done(); it.Next()) {
			CullableClass * obj = it.Peek_Obj();
			if (CollisionMath::Overlap_Test(obbox,obj->Get_Cull_Box()) != CollisionMath::OUTSIDE) {
				Add_To_Collection(obj);
			}
		}
	}
}

void GridCullSystemClass::collect_objects_in_leaf(const FrustumClass & frustum,CullableClass * head)
{
	if (head != NULL) {
		GridListIterator it(head);
		for (;!it.Is_Done(); it.Next()) {
			CullableClass * obj = it.Peek_Obj();
			if (CollisionMath::Overlap_Test(frustum,obj->Get_Cull_Box()) != CollisionMath::OUTSIDE) {
				Add_To_Collection(obj);
			}
		}
	}
}
