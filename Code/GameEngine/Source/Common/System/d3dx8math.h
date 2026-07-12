#pragma once
// Minimal D3DX8 math subset (DX8 SDK inline vector/matrix math) — reconstructed to
// the SDK's standard inline forms so byte-matching geometry code compiles.
typedef struct D3DXVECTOR4 {
    float x, y, z, w;
    D3DXVECTOR4() {}
    D3DXVECTOR4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
} D3DXVECTOR4;

typedef struct D3DXMATRIX {
    union {
        struct { float _11,_12,_13,_14, _21,_22,_23,_24, _31,_32,_33,_34, _41,_42,_43,_44; };
        float m[4][4];
    };
    D3DXMATRIX() {}
    D3DXMATRIX(float f11,float f12,float f13,float f14, float f21,float f22,float f23,float f24,
               float f31,float f32,float f33,float f34, float f41,float f42,float f43,float f44)
    { _11=f11;_12=f12;_13=f13;_14=f14; _21=f21;_22=f22;_23=f23;_24=f24;
      _31=f31;_32=f32;_33=f33;_34=f34; _41=f41;_42=f42;_43=f43;_44=f44; }
} D3DXMATRIX;

inline float D3DXVec4Dot(const D3DXVECTOR4* pV1, const D3DXVECTOR4* pV2)
{ return pV1->x*pV2->x + pV1->y*pV2->y + pV1->z*pV2->z + pV1->w*pV2->w; }

inline D3DXVECTOR4* D3DXVec4Transform(D3DXVECTOR4* pOut, const D3DXVECTOR4* pV, const D3DXMATRIX* pM)
{
    float x = pV->x * pM->_11 + pV->y * pM->_21 + pV->z * pM->_31 + pV->w * pM->_41;
    float y = pV->x * pM->_12 + pV->y * pM->_22 + pV->z * pM->_32 + pV->w * pM->_42;
    float z = pV->x * pM->_13 + pV->y * pM->_23 + pV->z * pM->_33 + pV->w * pM->_43;
    float w = pV->x * pM->_14 + pV->y * pM->_24 + pV->z * pM->_34 + pV->w * pM->_44;
    pOut->x = x; pOut->y = y; pOut->z = z; pOut->w = w;
    return pOut;
}
