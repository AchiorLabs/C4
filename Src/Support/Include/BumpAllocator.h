#ifndef ACHIOR_LABS_BUMP_ALLOCATOR_H
#define ACHIOR_LABS_BUMP_ALLOCATOR_H

#include "Types.h"
#include "Utils.h"

struct Layout
{
    u64 size;
    u64 alignment;
};

bool LayoutNew(struct Layout *self,u64 size,u64 alignment);

struct BumpAllocator
{
    u64 capacity;
    u64 offset;
    char *base;
};

bool BumpAllocatorNew(struct BumpAllocator *self,u64 capacity);

bool BumpAllocatorFree(struct BumpAllocator *self);

bool BumpAllocatorIsPowerOfTwo(struct BumpAllocator *self,u64 num);

bool BumpAllocatorCheckedAdd(struct BumpAllocator *self,u64 *dst,u64 num1,u64 num2);

bool BumpAllocatorAlign(struct BumpAllocator *self,u64 *dst,u64 num,u64 alignment);

bool BumpAllocatorReset(struct BumpAllocator *self);

u64 BumpAllocatorAvailableMemory(struct BumpAllocator *self);

void *BumpAllocatorAlignedAlloc(struct BumpAllocator *self,struct Layout layout);



#ifndef ACHIOR_LABS_ARENA_ALLOC
#define ACHIOR_LABS_ARENA_ALLOC(self,type,count) (type *)BumpAllocatorAlignedAlloc((self),(struct Layout){.size = sizeof(type) * (count),.alignment = _Alignof(type)})
#endif


#endif
