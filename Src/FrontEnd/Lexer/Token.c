#include "Include/Token.h"




void SpanNew(struct Span *self,u64 row,u64 col,u64 start,u64 end,u64 line)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->row   = row;
	self->col   = col;
	self->start = start;
	self->end   = end;
	self->line  = line;
}


void TokenNew(struct Token *self,enum TokenType type,struct String value,struct Span span)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->type  = type;
	self->value = value;
	self->span  = span;
}


