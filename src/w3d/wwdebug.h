// Minimal wwdebug.h for the WWMath port. matrix3.h is the only WWMath header
// that references WWASSERT; the shipping build compiles these to nothing (the
// release variant), so the stubs are empty to match the binary's codegen.
#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef WWDEBUG_H
#define WWDEBUG_H

#define WWDEBUG_SAY(x)
#define WWASSERT(expr)
#define WWASSERT_PRINT(expr, string)

#endif
