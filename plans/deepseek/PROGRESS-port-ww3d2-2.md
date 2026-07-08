# PROGRESS: port-ww3d2-2

## Done (pre-existing on branch)
DONE distlod.cpp
DONE hanim.cpp
DONE hcanim.cpp

## Skipped
SKIP decalsys.cpp — only ambiguous shared MultiList inlines locate; main functions unlocated/absent
SKIP dx8caps.cpp — includes dx8wrapper.h + real windows.h
SKIP dx8fvf.cpp — includes D3dx8core.h
SKIP dx8indexbuffer.cpp — includes dx8wrapper.h
SKIP dx8polygonrenderer.cpp — includes dx8renderer.h (DX8 chain)
SKIP dx8renderer.cpp — heavy DX8 chain
SKIP dx8rendererdebugger.cpp — heavy DX8 chain
SKIP dx8texman.cpp — heavy DX8 chain
SKIP dx8vertexbuffer.cpp — includes dx8wrapper.h + D3dx8core.h
SKIP dx8webbrowser.cpp — includes dx8wrapper.h
SKIP dx8wrapper.cpp — heavy DX8 chain
SKIP dynamesh.cpp — includes dx8wrapper.h
SKIP font3d.cpp — compile wall (missing wwdebug.h + widestring.h issues)
SKIP formconv.cpp — formconv.h includes d3d8.h
SKIP FramGrab.cpp — framgrab.h includes windows.h/windowsx.h/vfw.h
SKIP hanimmgr.cpp — only 1 shared destructor locates; manager methods absent/ambiguous
