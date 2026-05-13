#include "Include/Token.h"


// Initializes a Span with source location bounds (byte offsets + line/column info)
// Safe no-op if self is NULL

void SpanNew(struct Span *self,u64 start,u64 end,u64 startLine,u64 startColumn,u64 endLine,u64 endColumn)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->start       = start;
	self->end         = end;
	self->startLine   = startLine;
	self->startColumn = startColumn;
	self->endLine     = endLine;
	self->endColumn   = endColumn;
}


// Constructs a token with its type, literal value, and source span
// Safe no-op if self is NULL

void TokenNew(struct Token *self,enum TokenKind kind,struct String value,struct Span span)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->kind  = kind;
	self->value = value;
	self->span  = span;
}




struct Token *C4MakeToken(struct BumpAllocator *bump,enum TokenKind kind,struct String value,struct Span span)
{
	struct Token *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct Token,1);
	TokenNew(node,kind,value,span);

	return node;
}
