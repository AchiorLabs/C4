#ifndef ACHIOR_LABS_STRING_H
#define ACHIOR_LABS_STRING_H

#include "Types.h"
#include "Utils.h"
#include "BumpAllocator.h"



struct String
{
	u64 size;
	u64 capacity;
	char *data;
	struct BumpAllocator *bump;
};




bool StringNew(struct String *self,u64 capacity,struct BumpAllocator *bump);


bool StringPushBack(struct String *self,const char *data);


bool StringPushBackChar(struct String *self,char data);


bool StringEqual(struct String *self,const struct String *str);


bool StringEqualCstr(struct String *self,const char *str);


bool StringPrint(struct String *self);

bool StringPrintln(struct String *self);

#endif
