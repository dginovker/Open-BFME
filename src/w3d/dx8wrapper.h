#pragma once
// Guard-only stand-in for WW3D2 dx8wrapper.h. part_buf.cpp and texturefilter.h
// include it but reference no DX8 symbols; the real header pulls the whole
// Direct3D web the match toolchain doesn't have. Anything genuinely needing
// DX8Wrapper statics must declare exactly what it uses (see ww3d.h precedent).
#ifndef DX8WRAPPER_H
#define DX8WRAPPER_H

// Fixed vertex format used by the line renderers (verbatim from WW3D2 dx8fvf.h).
struct VertexFormatXYZDUV1
{
	float x;
	float y;
	float z;
	unsigned diffuse;
	float u1;
	float v1;
};

#endif
