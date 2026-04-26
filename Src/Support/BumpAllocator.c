#include "Include/BumpAllocator.h"




bool LayoutNew(struct Layout *self,u64 size,u64 alignment)
{
    if( ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->size = size;
    self->alignment = alignment;
    return true;
}



bool BumpAllocatorNew(struct BumpAllocator *self,u64 capacity)
{
    if( ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->offset = 0;
    self->capacity = capacity;
    self->base = ACHIOR_LABS_MALLOC(capacity);

    if( ACHIOR_LABS_NULL(self->base))
    {
        return false;
    }

    return true;
}


bool BumpAllocatorIsPowerOfTwo(struct BumpAllocator *self,u64 num)
{
    return ACHIOR_LABS_NOT_ZERO(num) && (num & (num - 1)) == 0; 
}

bool BumpAllocatorCheckedAdd(struct BumpAllocator *self,u64 *dst,u64 num1,u64 num2)
{
    if( ACHIOR_LABS_GREATER(num1,SIZE_MAX - num2))
    {
        return true;
    }

    *dst = num1 + num2;
    return false;
}


bool BumpAllocatorAlign(struct BumpAllocator *self,u64 *dst,u64 num,u64 alignment)
{
    if ( !BumpAllocatorIsPowerOfTwo(self,alignment))
    {
        return false;
    }

    u64 mask = alignment - 1;
    u64 added = 0;

    if( BumpAllocatorCheckedAdd(self,&added,num,mask))
    {
        return false;
    }

    *dst = added & ~mask;
    return true;
}

bool BumpAllocatorReset(struct BumpAllocator *self)
{
    self->offset = 0;
}

u64 BumpAllocatorAvailableMemory(struct BumpAllocator *self)
{
    return self->capacity - self->offset;
}

void *BumpAllocatorAlignedAlloc(struct BumpAllocator *self,struct Layout layout)
{
    if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(self->base) || ACHIOR_LABS_ZERO(layout.size) || !BumpAllocatorIsPowerOfTwo(self,layout.alignment))
    {
        return NULL;
    }

    u8 *base_addr = (u8 *)self->base;
    u64 current_offset = 0;

    if( BumpAllocatorCheckedAdd(self,&current_offset,(u64)base_addr,self->offset))
    {
        return NULL;
    }

    u64 aligned_addr = 0;
    if( !BumpAllocatorAlign(self,&aligned_addr,current_offset,layout.alignment))
    {
        return NULL;
    }

    if( ACHIOR_LABS_LESS(aligned_addr,(u64)base_addr))
    {
        return NULL;
    }

    u64 aligned_offset = aligned_addr - (u64)base_addr;

    u64 new_offset = 0;
    if( BumpAllocatorCheckedAdd(self,&new_offset,aligned_offset,layout.size))
    {
        return NULL;
    }

    if( ACHIOR_LABS_GREATER(new_offset,self->capacity))
    {
        return NULL;
    }

    void *mem = self->base + aligned_offset;
    self->offset = new_offset;
    return mem;
}



bool BumpAllocatorFree(struct BumpAllocator *self)
{
    if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(self->base))
    {
        return false;
    }

    ACHIOR_LABS_FREE(self->base);
    self->capacity = self->offset = 0;
    return true;
}


