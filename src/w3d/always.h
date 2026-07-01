// Minimal stand-in for WWLib always.h. The real header is config/pragma/memory-pool
// machinery; chunkio.cpp uses none of it, only needs the ALWAYS_H guard satisfied so
// chunkio.h's conditional include is a no-op.
#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef ALWAYS_H
#define ALWAYS_H

#endif
