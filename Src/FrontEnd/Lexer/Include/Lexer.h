#ifndef ACHIOR_LABS_LEXER_H
#define ACHIOR_LABS_LEXER_H

#include "Token.h"
#include "../../../DiagnosticEngine/Include/DiagnosticEngine.h" 


struct Lexer
{
	char *fileName;
	char *fileSource;
	i64 fileLength;
	i64 index;
	i64 current;

    u64 start;
    u64 end;
    u64 startLine;
    u64 startColumn;
    u64 endLine;
    u64 endColumn;
	bool hasErrors;
	struct LinkedList tokens;
	struct DiagnosticEngine *engine;
	struct BumpAllocator *bump;
};




void LexerNew(struct Lexer *self,char *fileName,char *fileSource,struct DiagnosticEngine *engine,struct BumpAllocator *bump);

bool LexerAtEnd(struct Lexer *self);

char LexerPeek(struct Lexer *self,i64 lookAhead);

char LexerConsume(struct Lexer *self);

bool LexerIsToken(struct Lexer *self,char token,i64 lookAhead);

bool LexerMatchToken(struct Lexer *self,char token,i64 lookAhead);

bool LexerIsDigit(struct Lexer *self,i64 lookAhead);

void LexerMakeDecimal(struct Lexer *self);

void LexerMakeNumber(struct Lexer *self);

bool LexerIsAlpha(struct Lexer *self);

bool LexerIsAlphanum(struct Lexer *self);

void LexerMakeString(struct Lexer *self);

void LexerMakeIdentifier(struct Lexer *self);

void LexerMakeCharacter(struct Lexer *self);

bool LexerMatchKeyword(struct Lexer *self,struct String str1,char *str2);

void LexerAddKeywords(struct Lexer *self,struct String str);

void LexerAdvanceColumn(struct Lexer *self,u64 amount);

void LexerAdvanceLine(struct Lexer *self,u64 amount);

void LexerAddToken(struct Lexer *self,enum TokenKind kind,struct String str);

void LexerAddTokenSingle(struct Lexer *self,enum TokenKind kind,struct String str);

void LexerAddTokenDouble(struct Lexer *self,enum TokenKind kind,struct String str);


void LexerScanToken(struct Lexer *self);

void LexerScanTokens(struct Lexer *self);


void LexerPrintErrors(struct Lexer *self);

void LexerPrintTokens(struct Lexer *self,char *outputFileName);

#endif

