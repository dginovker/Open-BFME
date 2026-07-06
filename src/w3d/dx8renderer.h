#pragma once
// BFME shim of WW3D2 dx8renderer.h: only the global mesh renderer's registration
// entry points that MeshModelClass ctor/dtor call. Declarations only (compile to
// external calls, pinned in symbols.csv); the DX8 renderer body is not needed.
#ifndef DX8RENDERER_H_SHIM
#define DX8RENDERER_H_SHIM
class MeshModelClass;
class DX8MeshRendererClass
{
public:
	void Register_Mesh_Type(MeshModelClass* mmc);
	void Unregister_Mesh_Type(MeshModelClass* mmc);
};
extern DX8MeshRendererClass TheDX8MeshRenderer;
#endif
