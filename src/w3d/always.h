// Minimal always.h for the WWMath port. The real Generals always.h pulls in
// visualc.h, debug-memory catchers, and STL warning pragmas that don't affect
// codegen here; this keeps only what the WWMath headers actually reference:
// WWINLINE, NULL, ARRAY_SIZE, size_of, and the W3DMPO memory-pool glue that
// matrix3d.h's DynamicMatrix3D derives from.
#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef ALWAYS_H
#define ALWAYS_H

#include <assert.h>

#if defined(_MSC_VER)
#define WWINLINE __forceinline
#else
#define WWINLINE inline
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)		int(sizeof(x)/sizeof(x[0]))
#endif

#ifndef size_of
#define size_of(typ,id) sizeof(((typ*)0)->id)
#endif

// ----------------------------------------------------------------------------
extern void* createW3DMemPool(const char *poolName, int allocationSize);
extern void* allocateFromW3DMemPool(void* p, int allocationSize);
extern void* allocateFromW3DMemPool(void* p, int allocationSize, const char* msg, int unused);
extern void freeFromW3DMemPool(void* pool, void* p);

// ----------------------------------------------------------------------------
#define W3DMPO_GLUE(ARGCLASS) \
private: \
	static void* getClassMemoryPool() \
	{ \
		static void* The##ARGCLASS##Pool = createW3DMemPool(#ARGCLASS, sizeof(ARGCLASS)); \
		return The##ARGCLASS##Pool; \
	} \
protected: \
	virtual int glueEnforcer() const { return sizeof(this); } \
public: \
	inline void* operator new(size_t s) { return allocateFromW3DMemPool(getClassMemoryPool(), s); } \
	inline void operator delete(void *p) { freeFromW3DMemPool(getClassMemoryPool(), p); } \
	inline void* operator new(size_t s, const char* msg, int unused) { return allocateFromW3DMemPool(getClassMemoryPool(), s, msg, unused); } \
	inline void operator delete(void *p, const char* msg, int unused) { freeFromW3DMemPool(getClassMemoryPool(), p); } \

// ----------------------------------------------------------------------------
class W3DMPO
{
private:
	static void* getClassMemoryPool()
	{
		assert(0);	// must replace this via W3DMPO_GLUE
		return 0;
	}
protected:
	// we never call this; it is present to cause compile errors in descendent classes
	virtual int glueEnforcer() const = 0;
public:
	virtual ~W3DMPO() { /* nothing */ }
};

#endif
