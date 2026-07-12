#pragma once

namespace MemoryPool {

enum AllocType {
    ALLOC_NORMAL = 0,
    ALLOC_PERMANENT
};

void _Exit();
unsigned int _GetBlockSize(void *block);
bool _IsValidBlock(void *block);
void *_Allocate(unsigned int size, AllocType type);
void _Free(void *ptr, AllocType type);
void *_Reallocate(void *ptr, unsigned int size, AllocType type);
void _Init();
void _VerifyIntegrity();

}
