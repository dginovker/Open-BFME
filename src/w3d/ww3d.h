// Minimal shim of WW3D2/ww3d.h — only the timing accessor the texture mappers need.
// WW3D::Get_Sync_Time() is inline (reads the static SyncTime); the DIR32 reference to
// SyncTime is relocation-masked by the byte matcher, so no definition is required here.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WW3D_H
#define WW3D_H

class WW3D
{
public:
	enum NPatchesGapFillingModeEnum {
		NPATCHES_GAP_FILLING_DISABLED,
		NPATCHES_GAP_FILLING_ENABLED,
		NPATCHES_GAP_FILLING_FORCE
	};
private:
	static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
	static unsigned int NPatchesLevel;
	static unsigned int SyncTime;
	static int FrameCount;
	static float DefaultNativeScreenSize;
	static unsigned int FrameTime;
	static bool IsSortingEnabled;
	static bool AreStaticSortListsEnabled;
public:
	static unsigned int Get_Sync_Time(void) { return SyncTime; }
	static unsigned int Get_Frame_Count(void) { return FrameCount; }
	static float Get_Default_Native_Screen_Size(void) { return DefaultNativeScreenSize; }
	static unsigned int Get_Frame_Time(void) { return FrameTime; }
	static NPatchesGapFillingModeEnum Get_NPatches_Gap_Filling_Mode() { return NPatchesGapFillingMode; }
	static unsigned int Get_NPatches_Level() { return NPatchesLevel; }
	static bool Is_Sorting_Enabled(void) { return IsSortingEnabled; }
	static bool Are_Static_Sort_Lists_Enabled(void) { return AreStaticSortListsEnabled; }
	static void Add_To_Static_Sort_List(class RenderObjClass *robj, unsigned int sort_level);
};

#endif
