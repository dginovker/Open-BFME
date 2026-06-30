#include "matrix4d.h"

#include <string.h>

Matrix4D::Matrix4D()
{
}

Matrix4D::Matrix4D(const Matrix4D &that)
{
    if (this != &that) {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        values[12] = that.values[12];
        values[13] = that.values[13];
        values[14] = that.values[14];
        values[15] = that.values[15];
    }
}

Matrix4D::Matrix4D(bool identity)
{
    unsigned int zero = 0;

    if (identity) {
        unsigned int one = 0x3f800000;

        ((unsigned int *)values)[0] = one;
        ((unsigned int *)values)[1] = zero;
        ((unsigned int *)values)[2] = zero;
        ((unsigned int *)values)[3] = zero;
        ((unsigned int *)values)[4] = zero;
        ((unsigned int *)values)[5] = one;
        ((unsigned int *)values)[6] = zero;
        ((unsigned int *)values)[7] = zero;
        ((unsigned int *)values)[8] = zero;
        ((unsigned int *)values)[9] = zero;
        ((unsigned int *)values)[10] = one;
        ((unsigned int *)values)[11] = zero;
        ((unsigned int *)values)[12] = zero;
        ((unsigned int *)values)[13] = zero;
        ((unsigned int *)values)[14] = zero;
        ((unsigned int *)values)[15] = one;
    }
}

Matrix4D::Matrix4D(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    values[0] = m00;
    values[1] = m01;
    values[2] = m02;
    values[3] = m03;
    values[4] = m10;
    values[5] = m11;
    values[6] = m12;
    values[7] = m13;
    values[8] = m20;
    values[9] = m21;
    values[10] = m22;
    values[11] = m23;
    values[12] = m30;
    values[13] = m31;
    values[14] = m32;
    values[15] = m33;
}

Matrix4D &Matrix4D::operator=(const Matrix4D &that)
{
    if (this != &that) {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        values[12] = that.values[12];
        values[13] = that.values[13];
        values[14] = that.values[14];
        values[15] = that.values[15];
    }
    return *this;
}

Matrix4D &Matrix4D::operator*=(float scale)
{
    values[0] *= scale;
    values[1] *= scale;
    values[2] *= scale;
    values[3] *= scale;
    values[4] *= scale;
    values[5] *= scale;
    values[6] *= scale;
    values[7] *= scale;
    values[8] *= scale;
    values[9] *= scale;
    values[10] *= scale;
    values[11] *= scale;
    values[12] *= scale;
    values[13] *= scale;
    values[14] *= scale;
    values[15] *= scale;
    return *this;
}

Matrix4D &Matrix4D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    values[0] *= scale;
    values[1] *= scale;
    values[2] *= scale;
    values[3] *= scale;
    values[4] *= scale;
    values[5] *= scale;
    values[6] *= scale;
    values[7] *= scale;
    values[8] *= scale;
    values[9] *= scale;
    values[10] *= scale;
    values[11] *= scale;
    values[12] *= scale;
    values[13] *= scale;
    values[14] *= scale;
    values[15] *= scale;
    return *this;
}

Matrix4D &Matrix4D::operator+=(const Matrix4D &that)
{
    values[0] += that.values[0];
    values[1] += that.values[1];
    values[2] += that.values[2];
    values[3] += that.values[3];
    values[4] += that.values[4];
    values[5] += that.values[5];
    values[6] += that.values[6];
    values[7] += that.values[7];
    values[8] += that.values[8];
    values[9] += that.values[9];
    values[10] += that.values[10];
    values[11] += that.values[11];
    values[12] += that.values[12];
    values[13] += that.values[13];
    values[14] += that.values[14];
    values[15] += that.values[15];
    return *this;
}

Matrix4D &Matrix4D::operator-=(const Matrix4D &that)
{
    values[0] -= that.values[0];
    values[1] -= that.values[1];
    values[2] -= that.values[2];
    values[3] -= that.values[3];
    values[4] -= that.values[4];
    values[5] -= that.values[5];
    values[6] -= that.values[6];
    values[7] -= that.values[7];
    values[8] -= that.values[8];
    values[9] -= that.values[9];
    values[10] -= that.values[10];
    values[11] -= that.values[11];
    values[12] -= that.values[12];
    values[13] -= that.values[13];
    values[14] -= that.values[14];
    values[15] -= that.values[15];
    return *this;
}

Coord3D &Matrix4D::GetXVector(Coord3D &out) const
{
    out.x = values[0];
    out.y = values[4];
    out.z = values[8];
    return out;
}

Coord3D &Matrix4D::GetYVector(Coord3D &out) const
{
    out.x = values[1];
    out.y = values[5];
    out.z = values[9];
    return out;
}

Coord3D &Matrix4D::GetZVector(Coord3D &out) const
{
    out.x = values[2];
    out.y = values[6];
    out.z = values[10];
    return out;
}

Coord3D &Matrix4D::GetTranslationVector(Coord3D &out) const
{
    out.x = values[3];
    out.y = values[7];
    out.z = values[11];
    return out;
}

Coord3D &Matrix4D::RotateCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;

    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

Coord3D &Matrix4D::TransformCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;
    y += values[7];

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;
    z += values[11];

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;
    x += values[3];

    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

Matrix4D &Matrix4D::Set(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    values[0] = m00;
    values[1] = m01;
    values[2] = m02;
    values[3] = m03;
    values[4] = m10;
    values[5] = m11;
    values[6] = m12;
    values[7] = m13;
    values[8] = m20;
    values[9] = m21;
    values[10] = m22;
    values[11] = m23;
    values[12] = m30;
    values[13] = m31;
    values[14] = m32;
    values[15] = m33;
    return *this;
}

Matrix4D &Matrix4D::SetIdentity()
{
    unsigned int zero = 0;
    unsigned int one = 0x3f800000;

    ((unsigned int *)values)[0] = one;
    ((unsigned int *)values)[1] = zero;
    ((unsigned int *)values)[2] = zero;
    ((unsigned int *)values)[3] = zero;
    ((unsigned int *)values)[4] = zero;
    ((unsigned int *)values)[5] = one;
    ((unsigned int *)values)[6] = zero;
    ((unsigned int *)values)[7] = zero;
    ((unsigned int *)values)[8] = zero;
    ((unsigned int *)values)[9] = zero;
    ((unsigned int *)values)[10] = one;
    ((unsigned int *)values)[11] = zero;
    ((unsigned int *)values)[12] = zero;
    ((unsigned int *)values)[13] = zero;
    ((unsigned int *)values)[14] = zero;
    ((unsigned int *)values)[15] = one;
    return *this;
}

__declspec(naked) Matrix4D &Matrix4D::Set(const Coord3D &translation)
{
    __asm {
        mov eax, ecx
        xor ecx, ecx
        mov edx, 0x3f800000
        mov [eax + 0x0c], ecx
        mov [eax + 0x1c], ecx
        mov [eax + 0x2c], ecx
        mov [eax + 0x04], ecx
        mov [eax + 0x08], ecx
        mov [eax + 0x10], ecx
        mov [eax + 0x18], ecx
        mov [eax + 0x20], ecx
        mov [eax + 0x24], ecx
        mov [eax + 0x30], ecx
        mov [eax + 0x34], ecx
        mov [eax + 0x38], ecx
        mov ecx, [esp + 0x04]
        mov [eax], edx
        mov [eax + 0x14], edx
        mov [eax + 0x28], edx
        mov [eax + 0x3c], edx
        mov edx, [ecx]
        mov [eax + 0x0c], edx
        mov edx, [ecx + 0x04]
        mov [eax + 0x1c], edx
        mov ecx, [ecx + 0x08]
        mov [eax + 0x2c], ecx
        ret 4
    }
}

__declspec(naked) bool Matrix4D::IsExactlyEqualTo(const Matrix4D &that)
{
    __asm {
        mov eax, [esp + 4]
        cmp ecx, eax
        jne compare
        mov al, 1
        ret 4
    compare:
        push esi
        push ebx
        xor esi, esi
        push edi
    loop_start:
        mov edi, [ecx]
        mov edx, [eax]
        mov ebx, [ecx + 4]
        xor edx, edi
        mov edi, [eax + 4]
        add eax, 4
        add ecx, 4
        xor edi, ebx
        mov ebx, [ecx + 4]
        or edx, edi
        mov edi, [eax + 4]
        add eax, 4
        add ecx, 4
        xor edi, ebx
        mov ebx, [ecx + 4]
        or edx, edi
        mov edi, [eax + 4]
        add eax, 4
        add ecx, 4
        xor edi, ebx
        or edx, edi
        add eax, 4
        add ecx, 4
        test edx, edx
        jne not_equal
        inc esi
        cmp esi, 4
        jl loop_start
        pop edi
        pop ebx
        mov al, 1
        pop esi
        ret 4
    not_equal:
        pop edi
        pop ebx
        xor al, al
        pop esi
        ret 4
    }
}


// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@@Z

// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z
__declspec(naked) Matrix4D &Matrix4D::Set(const Coord3D &v, float w)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0x64
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x42
        __emit 0x08
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0xd8
        __emit 0xe1
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x40
        __emit 0x3c
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xdd
        __emit 0xd8
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?Transpose@Matrix4D@@QAEAAV1@XZ
__declspec(naked) Matrix4D &Matrix4D::Transpose()
{
    __asm {
        __emit 0x8b
        __emit 0xc1
        __emit 0x8b
        __emit 0x48
        __emit 0x10
        __emit 0x8b
        __emit 0x50
        __emit 0x04
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x50
        __emit 0x04
        __emit 0x8b
        __emit 0xca
        __emit 0x8b
        __emit 0x50
        __emit 0x10
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0xca
        __emit 0x89
        __emit 0x50
        __emit 0x10
        __emit 0x8b
        __emit 0x50
        __emit 0x04
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0x48
        __emit 0x08
        __emit 0x89
        __emit 0x50
        __emit 0x04
        __emit 0x8b
        __emit 0x50
        __emit 0x20
        __emit 0x33
        __emit 0xca
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x50
        __emit 0x20
        __emit 0x89
        __emit 0x48
        __emit 0x08
        __emit 0x8b
        __emit 0xca
        __emit 0x8b
        __emit 0x50
        __emit 0x08
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x50
        __emit 0x08
        __emit 0x8b
        __emit 0x50
        __emit 0x0c
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x50
        __emit 0x0c
        __emit 0x8b
        __emit 0xca
        __emit 0x8b
        __emit 0x50
        __emit 0x30
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0xca
        __emit 0x89
        __emit 0x50
        __emit 0x30
        __emit 0x8b
        __emit 0x50
        __emit 0x0c
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x50
        __emit 0x0c
        __emit 0x8b
        __emit 0x50
        __emit 0x24
        __emit 0x33
        __emit 0xca
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x50
        __emit 0x24
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x8b
        __emit 0xca
        __emit 0x8b
        __emit 0x50
        __emit 0x18
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x50
        __emit 0x18
        __emit 0x8b
        __emit 0x50
        __emit 0x1c
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x50
        __emit 0x1c
        __emit 0x8b
        __emit 0xca
        __emit 0x8b
        __emit 0x50
        __emit 0x34
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0xca
        __emit 0x89
        __emit 0x50
        __emit 0x34
        __emit 0x8b
        __emit 0x50
        __emit 0x1c
        __emit 0x33
        __emit 0xd1
        __emit 0x8b
        __emit 0x48
        __emit 0x38
        __emit 0x89
        __emit 0x50
        __emit 0x1c
        __emit 0x8b
        __emit 0x50
        __emit 0x2c
        __emit 0x33
        __emit 0xca
        __emit 0x33
        __emit 0xd1
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0x89
        __emit 0x50
        __emit 0x2c
        __emit 0x8b
        __emit 0xca
        __emit 0x31
        __emit 0x48
        __emit 0x38
        __emit 0xc3
    }
}

// ?Determinant@Matrix4D@@QBEMXZ
__declspec(naked) float Matrix4D::Determinant() const
{
    __asm {
        __emit 0xd9
        __emit 0x41
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xd9
        __emit 0x41
        __emit 0x38
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x01
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xd9
        __emit 0x41
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x41
        __emit 0x18
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x41
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x3c
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xd9
        __emit 0x41
        __emit 0x30
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x41
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x0c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x38
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x41
        __emit 0x38
        __emit 0xd8
        __emit 0x49
        __emit 0x20
        __emit 0xd9
        __emit 0x41
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x41
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xd9
        __emit 0x41
        __emit 0x30
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xd9
        __emit 0x41
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x0c
        __emit 0xde
        __emit 0xe9
        __emit 0xde
        __emit 0xc9
        __emit 0xde
        __emit 0xc1
        __emit 0xc3
    }
}

// ?Multiply@Matrix4D@@QAEAAV1@ABV1@0@Z
__declspec(naked) Matrix4D &Matrix4D::Multiply(const Matrix4D &left, const Matrix4D &right)
{
    __asm {
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xd9
        __emit 0x06
        __emit 0x8b
        __emit 0xc1
        __emit 0xd8
        __emit 0x0a
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x0c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xd9
        __emit 0x06
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x14
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0x06
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xd9
        __emit 0x46
        __emit 0x0c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x0c
        __emit 0xd8
        __emit 0x0e
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x2c
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x1c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x14
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x1c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x18
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x1c
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x2c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x24
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x2c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x28
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x2c
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x46
        __emit 0x3c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x20
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x30
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x24
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x34
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x34
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x38
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x3c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0x5e
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x3c
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?Inverse@Matrix4D@@QAEMXZ
__declspec(naked) float Matrix4D::Inverse()
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x70
        __emit 0xd9
        __emit 0x01
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x10
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x2c
        __emit 0xd9
        __emit 0x41
        __emit 0x18
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x41
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x28
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x41
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x10
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x20
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x41
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x1c
        __emit 0xd9
        __emit 0x41
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xd9
        __emit 0x41
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xd9
        __emit 0x41
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x14
        __emit 0xd9
        __emit 0x41
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xd9
        __emit 0x41
        __emit 0x30
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0x41
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xd9
        __emit 0x41
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x41
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xd9
        __emit 0x41
        __emit 0x34
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x41
        __emit 0x3c
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x34
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x08
        __emit 0xd9
        __emit 0x41
        __emit 0x3c
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xd9
        __emit 0x41
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x14
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x2c
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x28
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0xc0
        __emit 0xd9
        __emit 0xe1
        __emit 0xd8
        __emit 0x1d
        __emit 0x40
        __emit 0xbf
        __emit 0x09
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x7a
        __emit 0x0c
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x70
        __emit 0xc3
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x10
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xd8
        __emit 0x49
        __emit 0x10
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x49
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x50
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x10
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x60
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x0c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x44
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xd8
        __emit 0x09
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x49
        __emit 0x0c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x54
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x09
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd8
        __emit 0x49
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x49
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x64
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x48
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x58
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x68
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x3c
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xd8
        __emit 0x49
        __emit 0x20
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x4c
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0xd8
        __emit 0x49
        __emit 0x20
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0xe0
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x5c
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0xd8
        __emit 0x49
        __emit 0x20
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x2c
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x6c
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x30
        __emit 0x3b
        __emit 0xc8
        __emit 0xd8
        __emit 0xf5
        __emit 0xd9
        __emit 0x14
        __emit 0x24
        __emit 0xd8
        __emit 0xcc
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x30
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0xca
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x34
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x38
        __emit 0xdd
        __emit 0xd8
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x3c
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x3c
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0xc9
        __emit 0xdd
        __emit 0xda
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x44
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x44
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x48
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x48
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x4c
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x50
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x50
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x54
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x54
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x58
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x58
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x5c
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x5c
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x60
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x60
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x64
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x64
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x68
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x68
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x6c
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x6c
        __emit 0x74
        __emit 0x6f
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x30
        __emit 0xd9
        __emit 0x59
        __emit 0x10
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x34
        __emit 0x89
        __emit 0x11
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x38
        __emit 0x89
        __emit 0x41
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x3c
        __emit 0x89
        __emit 0x51
        __emit 0x08
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x44
        __emit 0x89
        __emit 0x41
        __emit 0x0c
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x48
        __emit 0x89
        __emit 0x51
        __emit 0x14
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x89
        __emit 0x41
        __emit 0x18
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x50
        __emit 0x89
        __emit 0x51
        __emit 0x1c
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x54
        __emit 0x89
        __emit 0x41
        __emit 0x20
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x58
        __emit 0x89
        __emit 0x51
        __emit 0x24
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x5c
        __emit 0x89
        __emit 0x41
        __emit 0x28
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x60
        __emit 0x89
        __emit 0x51
        __emit 0x2c
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x64
        __emit 0x89
        __emit 0x41
        __emit 0x30
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x68
        __emit 0x89
        __emit 0x51
        __emit 0x34
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x6c
        __emit 0x89
        __emit 0x41
        __emit 0x38
        __emit 0x89
        __emit 0x51
        __emit 0x3c
        __emit 0x83
        __emit 0xc4
        __emit 0x70
        __emit 0xc3
        __emit 0xdd
        __emit 0xd8
        __emit 0x83
        __emit 0xc4
        __emit 0x70
        __emit 0xc3
    }
}

// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
__declspec(naked) Matrix4D::Matrix4D(const Coord3D &v, float w)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0x64
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x42
        __emit 0x08
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0xd8
        __emit 0xe1
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x40
        __emit 0x3c
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xdd
        __emit 0xd8
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ??0Matrix4D@@QAE@ABVCoord3D@@@Z
__declspec(naked) Matrix4D::Matrix4D(const Coord3D &v)
{
    __asm {
        __emit 0x8b
        __emit 0xc1
        __emit 0x33
        __emit 0xc9
        __emit 0xba
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0x89
        __emit 0x48
        __emit 0x0c
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0x89
        __emit 0x48
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x08
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x48
        __emit 0x20
        __emit 0x89
        __emit 0x48
        __emit 0x24
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x89
        __emit 0x10
        __emit 0x89
        __emit 0x50
        __emit 0x14
        __emit 0x89
        __emit 0x50
        __emit 0x28
        __emit 0x89
        __emit 0x50
        __emit 0x3c
        __emit 0x8b
        __emit 0x11
        __emit 0x89
        __emit 0x50
        __emit 0x0c
        __emit 0x8b
        __emit 0x51
        __emit 0x04
        __emit 0x89
        __emit 0x50
        __emit 0x1c
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
