/*
**  WWMath/Matrix3D.h shim — delegates to the real matrix3d.h
**  The real header is on the WWMath include path for most TUs.
**  For sweep TUs that lack WWMath on the path, we include it via relative path.
*/

#pragma once

#ifndef _MATRIX3D_H
#define _MATRIX3D_H

#include "../../../../../CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h"
#include "../../../../../CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/matrix3d.h"

#endif // _MATRIX3D_H
