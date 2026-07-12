// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Vector3 has no out-of-line members of its own (all inline in vector3.h). The
// retail binary keeps standalone COMDAT copies, emitted from use sites. Reference
// their addresses so this TU emits the same COMDATs for verification.
#include "vector3.h"

// free operators / helpers
typedef Vector3 (*V3_binop)(const Vector3 &, const Vector3 &);
typedef Vector3 (*V3_vf)(const Vector3 &, float);
typedef Vector3 (*V3_fv)(float, const Vector3 &);
typedef bool    (*V3_cmp)(const Vector3 &, const Vector3 &);
typedef bool    (*V3_eps)(const Vector3 &, const Vector3 &, float);
typedef void    (*V3_swap)(Vector3 &, Vector3 &);

V3_binop _add  = operator+;
V3_binop _sub  = operator-;
V3_vf    _mulf = operator*;
V3_fv    _fmul = operator*;
V3_vf    _div  = operator/;
V3_cmp   _eq   = operator==;
V3_cmp   _ne   = operator!=;
V3_eps   _eps  = Equal_Within_Epsilon;
V3_swap  _swap = Swap;

// static members
typedef void  (*V3_lerp)(const Vector3 &, const Vector3 &, float, Vector3 *);
typedef float (*V3_dot)(const Vector3 &, const Vector3 &);
typedef void  (*V3_cross)(const Vector3 &, const Vector3 &, Vector3 *);
typedef float (*V3_dist)(const Vector3 &, const Vector3 &);

V3_lerp  _lerp   = &Vector3::Lerp;
V3_dot   _dot    = &Vector3::Dot_Product;
V3_cross _cross  = &Vector3::Cross_Product;
V3_cross _ncross = &Vector3::Normalized_Cross_Product;
V3_cross _addp   = &Vector3::Add;
V3_cross _subp   = &Vector3::Subtract;
V3_dist  _dist   = &Vector3::Distance;
V3_dist  _qdist  = &Vector3::Quick_Distance;
V3_dot   _cx     = &Vector3::Cross_Product_X;
V3_dot   _cy     = &Vector3::Cross_Product_Y;
V3_dot   _cz     = &Vector3::Cross_Product_Z;

// const members
typedef float         (Vector3::*V3m_len)() const;
typedef unsigned long (Vector3::*V3m_argb)() const;
typedef bool          (Vector3::*V3m_valid)() const;
typedef Vector3       (Vector3::*V3m_neg)() const;

V3m_len   _len   = &Vector3::Length;
V3m_len   _qlen  = &Vector3::Quick_Length;
V3m_valid _valid = &Vector3::Is_Valid;
V3m_argb  _abgr  = &Vector3::Convert_To_ABGR;
V3m_argb  _argb  = &Vector3::Convert_To_ARGB;
V3m_neg   _neg   = &Vector3::operator-;

// non-const members
typedef void (Vector3::*V3m_scale)(const Vector3 &);
typedef void (Vector3::*V3m_rot1)(float);
typedef void (Vector3::*V3m_rot2)(float, float);

V3m_scale _scale = &Vector3::Scale;
V3m_scale _umin  = &Vector3::Update_Min;
V3m_scale _umax  = &Vector3::Update_Max;
V3m_scale _cap   = &Vector3::Cap_Absolute_To;
V3m_rot1  _rx1   = &Vector3::Rotate_X;
V3m_rot1  _ry1   = &Vector3::Rotate_Y;
V3m_rot1  _rz1   = &Vector3::Rotate_Z;
V3m_rot2  _rx2   = &Vector3::Rotate_X;
V3m_rot2  _ry2   = &Vector3::Rotate_Y;
V3m_rot2  _rz2   = &Vector3::Rotate_Z;
