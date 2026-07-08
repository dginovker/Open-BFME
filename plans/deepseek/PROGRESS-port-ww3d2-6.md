# PROGRESS: port-ww3d2-6

## Done (pre-existing on branch)
DONE visrasterizer.cpp
DONE w3d_util.cpp

## Skipped
SKIP stripoptimizer.cpp — includes wwdebug.h (WWDebug header wall)
SKIP surfaceclass.cpp — includes dx8wrapper.h / d3dx8.h
SKIP texfcach.cpp — external sr* headers + wwdebug.h
SKIP texproject.cpp — includes dx8wrapper.h
SKIP textdraw.cpp — textdraw.h includes dynamesh.h (DX8 chain)
SKIP texture.cpp — heavy DX8/D3D chain
SKIP texturefile.cpp — external sr* headers + texfcach.h
SKIP texturefilter.cpp — includes dx8wrapper.h
SKIP textureloader.cpp — heavy DX8/D3D chain
SKIP texturethumbnail.cpp — includes windows.h + textureloader chain
SKIP txt.cpp — 0 located after fixing compile; text texture functions absent
SKIP txt2d.cpp — requires external srTextureMap.hpp
SKIP vertmaterial.cpp — includes dx8wrapper.h / wwdebug.h
SKIP w3d_dep.cpp — operator new/delete conflict in always.h
SKIP w3dexclusionlist.cpp — 0 located; functions absent from binary
SKIP ww3d.cpp — heavy DX8 chain
SKIP ww3dformat.cpp — includes dx8wrapper.h / dx8caps.h / d3d8.h
