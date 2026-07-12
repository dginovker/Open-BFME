#pragma once
// Minimal stand-in for the GameEngine PreRTS.h precompiled header. The real one
// pulls the whole engine (and atlbase.h); a bring-up only needs the basic scalar
// typedefs and CRT math that a given TU actually uses.
#ifndef PRERTS_SHIM_H
#define PRERTS_SHIM_H
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#define PI 3.14159265358979323846f
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#define NEW new
#define MSGNEW new
#define NEW_MEMSET new
// Game debug macros — retail-empty under /DNDEBUG.
#define DEBUG_CRASH(x)
#define DEBUG_ASSERTCRASH(c,x)
#define DEBUG_LOG(x)
#define DEBUG_ASSERTLOG(c,x)
#define RELEASE_CRASH(x)
#define DEBUG_LOG_LEVEL(l,x)
typedef char Char;
template <typename NUM>
inline NUM sqr(NUM x)
{
	return x*x;
}

template <typename NUM>
inline NUM clamp(NUM lo, NUM val, NUM hi) { if (val < lo) return lo; else if (val > hi) return hi; else return val; }

template <typename NUM>
inline int sign(NUM x) { if (x > 0) return 1; else if (x < 0) return -1; else return 0; }

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef short Short;
typedef unsigned short UnsignedShort;
typedef char Byte;
typedef unsigned char UnsignedByte;
typedef unsigned char XferVersion;
typedef bool Bool;

// Fast float helpers + REAL_TO_INT — verbatim from Lib/BaseType.h (inline, header-
// only; the __asm blocks are what the callers inline, so needed for byte matching).

// note, this function depends on the cpu rounding mode, which we set to CHOP every frame, 
// but apparently tends to be left in unpredictable modes by various system bits of
// code, so use this function with caution -- it might not round in the way you want.
__forceinline long fast_float2long_round(float f)
{
	long i;

	__asm {
		fld [f]
		fistp [i]
	}

	return i;
}

// super fast float trunc routine, works always (independent of any FPU modes)
// code courtesy of Martin Hoffesommer (grin)
__forceinline float fast_float_trunc(float f)
{
  _asm
  {
    mov ecx,[f]
    shr ecx,23
    mov eax,0xff800000
    xor ebx,ebx
    sub cl,127
    cmovc eax,ebx
    sar eax,cl
    and [f],eax
  }
  return f;
}

// same here, fast floor function
__forceinline float fast_float_floor(float f)
{
  static unsigned almost1=(126<<23)|0x7fffff;
  if (*(unsigned *)&f &0x80000000)
    f-=*(float *)&almost1;
  return fast_float_trunc(f);
}

// same here, fast ceil function
__forceinline float fast_float_ceil(float f)
{
  static unsigned almost1=(126<<23)|0x7fffff;
  if ( (*(unsigned *)&f &0x80000000)==0)
    f+=*(float *)&almost1;
  return fast_float_trunc(f);
}

//-------------------------------------------------------------------------------------------------
#define REAL_TO_INT(x)						((Int)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_UNSIGNEDINT(x)		((UnsignedInt)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_SHORT(x)					((Short)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_UNSIGNEDSHORT(x)	((UnsignedShort)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_BYTE(x)						((Byte)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_UNSIGNEDBYTE(x)		((UnsignedByte)(fast_float2long_round(fast_float_trunc(x))))
#define REAL_TO_CHAR(x)						((Char)(fast_float2long_round(fast_float_trunc(x))))
#define DOUBLE_TO_REAL(x)					((Real) (x))
#define DOUBLE_TO_INT(x)					((Int) (fast_float2long_round(fast_float_trunc(x))))
#define INT_TO_REAL(x)						((Real) (x))

// once we've ceiled/floored, trunc and round are identical, and currently, round is faster... (srj)
#define REAL_TO_INT_CEIL(x)				(fast_float2long_round(fast_float_ceil(x)))
#define REAL_TO_INT_FLOOR(x)			(fast_float2long_round(fast_float_floor(x)))


#endif
