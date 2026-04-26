#include "Include/CmdLineArgumentList.h"


bool CmdLineArgumentListNew(struct CmdLineArgumentList *self,u64 capacity,struct BumpAllocator *bump)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->data = ACHIOR_LABS_ARENA_ALLOC(bump,struct CmdLineArgument ,capacity);

	if( ACHIOR_LABS_NULL(self->data))
	{
		return false;
	}

	self->capacity = capacity;
	self->size = 0;
	self->bump = bump;

	return true;
}


bool CmdLineArgumentListPushBack(struct CmdLineArgumentList *self,struct CmdLineArgument data)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	if( ACHIOR_LABS_GREATER_EQUAL(self->size,self->capacity))
	{
		i64 capacity = self->capacity * 2;
		struct CmdLineArgument *str = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct CmdLineArgument,capacity);

		if( ACHIOR_LABS_NULL(str))
		{
			return false;
		}

		ACHIOR_LABS_MEMCPY(str,self->data,self->size * sizeof(struct CmdLineArgument));
		
		self->data = str;
		self->capacity = capacity;
	}
	

	self->data[self->size] = data;
	self->size += 1;

	return true;
	

}


