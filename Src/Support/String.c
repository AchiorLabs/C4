#include "Include/String.h"




bool StringNew(struct String *self,u64 capacity,struct BumpAllocator *bump)
{
	if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_EQUAL(capacity,0) || ACHIOR_LABS_NULL(bump))
	{
		return false;
	}

	self->data = ACHIOR_LABS_ARENA_ALLOC(bump,char,capacity);

	if( ACHIOR_LABS_NULL(self->data))
	{
		return false;
	}

	self->capacity = capacity;
	self->size = 0;
	self->data[0] = '\0';
	self->bump = bump;

	return true;
}



bool StringPushBackChar(struct String *self,char data)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	u64 size = 1;

	if( ACHIOR_LABS_GREATER_EQUAL(self->size + size + 1,self->capacity))
	{
		i64 capacity = ACHIOR_LABS_GREATER(self->size + size,self->capacity * 2) ? self->size + size : self->capacity * 2;
		capacity += 1;
		char *str = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,capacity);

		if( ACHIOR_LABS_NULL(str))
		{
			return false;
		}

		ACHIOR_LABS_STRNCPY(str,self->data,self->size);
		str[self->size] = data;
		self->size += size;
		self->capacity = capacity;
		self->data = str;

		self->data[self->size] = '\0';
	}
	else
	{
		self->data[self->size] = data;
		self->size += size;
		self->data[self->size] = '\0';
	}

	return true;
}




bool StringPushBack(struct String *self,const char *data)
{
	if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(data))
	{
		return false;
	}

	u64 size = ACHIOR_LABS_STRLEN(data);

	if( ACHIOR_LABS_GREATER_EQUAL(self->size + size + 1,self->capacity))
	{
		i64 capacity = ACHIOR_LABS_GREATER(self->size + size,self->capacity * 2) ? self->size + size : self->capacity * 2;
		capacity += 1;
		char *str = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,capacity);

		if( ACHIOR_LABS_NULL(str))
		{
			return false;
		}

		ACHIOR_LABS_STRNCPY(str,self->data,self->size);
		ACHIOR_LABS_STRNCPY(str + self->size,data,size);
		
		self->size += size;
		self->capacity = capacity;
		self->data = str;

		self->data[self->size] = '\0';
	}
	else
	{
		ACHIOR_LABS_STRNCPY(self->data + self->size,data,size);
		self->size += size;
		self->data[self->size] = '\0';
	}

	return true;
}




bool StringEqual(struct String *self,const struct String *str)
{
	if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(str) || ACHIOR_LABS_NOT_EQUAL(self->size,str->size))
	{
		return false;
	}

	return ACHIOR_LABS_STRNCMP(self->data,str->data,self->size) == 0;
}






bool StringEqualCstr(struct String *self,const char *str)
{
	if( ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(str) || ACHIOR_LABS_NOT_EQUAL(self->size,ACHIOR_LABS_STRLEN(str)))
	{
		return false;
	}

	return ACHIOR_LABS_STRNCMP(self->data,str,self->size) == 0;
}





bool StringPrint(struct String *self)
{
	printf("%s",self->data);
}

bool StringPrintln(struct String *self)
{
	printf("%s\n",self->data);
}
