#ifndef ACHIOR_LABS_LEXER_H
#define ACHIOR_LABS_LEXER_H

#include "Token.h"


struct TokenList
{
	u64 size;
	u64 capacity;
	struct Token *data;
	struct BumpAllocator *bump;
};



bool TokenListNew(struct TokenList *self,u64 capacity,struct BumpAllocator *bump);

bool TokenListPushBack(struct TokenList *self,struct Token data);




struct Lexer
{
	char *file_name;
	char *file_source;
	i64 file_length;
	i64 index;
	i64 current;
	u64 row;
	u64 col;
	u64 start;
	u64 end;
	u64 line;
	bool has_errors;
	struct TokenList tokens;
	struct BumpAllocator *bump;
};




void LexerNew(struct Lexer *self,char *file_name,char *file_source,struct BumpAllocator *bump);

bool LexerAtEnd(struct Lexer *self);

char LexerPeek(struct Lexer *self,i64 lookahead);

char LexerConsume(struct Lexer *self);

bool LexerIsToken(struct Lexer *self,char token,i64 lookahead);

bool LexerMatchToken(struct Lexer *self,char token,i64 lookahead);

bool LexerIsDigit(struct Lexer *self,i64 lookahead);

void LexerMakeDecimal(struct Lexer *self);

void LexerMakeNumber(struct Lexer *self);

bool LexerIsAlpha(struct Lexer *self);

bool LexerIsAlphanum(struct Lexer *self);

void LexerMakeString(struct Lexer *self);

void LexerMakeIdentifier(struct Lexer *self);

void LexerMakeCharacter(struct Lexer *self);

bool LexerMatchKeyword(struct Lexer *self,struct String str1,char *str2);

void LexerAddKeywords(struct Lexer *self,struct String str);

void LexerUpdateCol(struct Lexer *self,i64 col_dx);

void LexerUpdateRow(struct Lexer *self,i64 row_dx);

void LexerAddToken(struct Lexer *self,enum TokenType type,struct String str);

void LexerAddTokenSingle(struct Lexer *self,enum TokenType type,struct String str);

void LexerAddTokenDouble(struct Lexer *self,enum TokenType type,struct String str);


void LexerScanToken(struct Lexer *self);

void LexerScanTokens(struct Lexer *self);


void LexerPrintErrors(struct Lexer *self);

void LexerPrintTokens(struct Lexer *self,char *output_file_name);

#endif

