#include "memory_pool.h"

unsigned int MemoryPool::_GetBlockSize(void *block)
{
    if (block == 0) {
        return 0;
    }

    return ((unsigned int *)block)[-1];
}
