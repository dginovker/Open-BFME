// cl: /DNDEBUG /MD
// Global operator new/delete route through the game's pluggable memory-manager
// function pointers (indirect __cdecl calls). Matching these unlocks new/delete
// for thousands of callers.
#include <stddef.h>
typedef void (__cdecl *GameFreeFn)(void*, int);
typedef void* (__cdecl *GameAllocFn)(size_t, int);
extern "C" GameFreeFn __gameMemFreePtr;    // pin -> 0x0130e9ac
extern "C" GameAllocFn __gameMemAllocPtr;  // pin -> 0x0130e9b4

void __cdecl operator delete(void* p) { if (p) __gameMemFreePtr(p, 1); }
void __cdecl operator delete[](void* p) { if (p) __gameMemFreePtr(p, 2); }
void* __cdecl operator new(size_t s) { return __gameMemAllocPtr(s, 1); }
void* __cdecl operator new[](size_t s) { return __gameMemAllocPtr(s, 2); }
