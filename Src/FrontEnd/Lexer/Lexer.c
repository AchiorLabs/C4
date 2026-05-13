#include "Include/Lexer.h"




void LexerNew(struct Lexer *self,char *fileName,char *fileSource,struct DiagnosticEngine *engine,struct BumpAllocator *bump)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->fileName    = fileName;
	self->fileSource  = fileSource;
	self->fileLength  = ACHIOR_LABS_STRLEN(fileSource);
	self->index       = 0;
	self->current     = 0;
	self->start       = 0;
	self->end         = 0;
	self->startLine   = 1;
	self->startColumn = 0;
	self->endLine     = 1;
	self->endColumn   = 0;
	self->hasErrors   = false;
	self->bump        = bump;
	self->engine      = engine;

	LinkedListNew(&self->tokens,bump);
	LexerScanTokens(self);
}



bool LexerAtEnd(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return (ACHIOR_LABS_GREATER_EQUAL(self->index,self->fileLength));
}



char LexerPeek(struct Lexer *self,i64 lookAhead)
{
	if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_GREATER_EQUAL(self->index + lookAhead,self->fileLength))
	{
		return '\0';
	}

	return self->fileSource[self->index + lookAhead];
}



char LexerConsume(struct Lexer *self)
{
	if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_GREATER_EQUAL(self->index,self->fileLength))
	{
		return '\0';
	}

	return self->fileSource[self->index++];
}


bool LexerIsToken(struct Lexer *self,char token,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ACHIOR_LABS_EQUAL(LexerPeek(self,lookAhead),token);
}



bool LexerMatchToken(struct Lexer *self,char token,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return LexerIsToken(self,token,lookAhead);
}



bool LexerIsDigit(struct Lexer *self,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	char token = LexerPeek(self,lookAhead);

	return ACHIOR_LABS_GREATER_EQUAL(token,'0') && ACHIOR_LABS_LESS_EQUAL(token,'9');
}


void LexerMakeInteger(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	struct String str;
	StringNew(&str,10,self->bump);

	while ( LexerIsDigit(self,0))
	{
		StringPushBackChar(&str,LexerConsume(self));
	}

	LexerAddToken(self,TOKEN_LITERAL_INT,str);
}


void LexerMakeNumber(struct Lexer *self)
{

	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	LexerMakeInteger(self);
}

bool LexerIsAlpha(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	char token = LexerPeek(self,0);

	return ( ACHIOR_LABS_GREATER_EQUAL(token,'A') && ACHIOR_LABS_LESS_EQUAL(token,'Z') )  ||  ( ACHIOR_LABS_GREATER_EQUAL(token,'a') && ACHIOR_LABS_LESS_EQUAL(token,'z') ) || ( ACHIOR_LABS_EQUAL(token,'_') );  
}




bool LexerIsAlphanum(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return LexerIsDigit(self,0) || LexerIsAlpha(self);
}



void LexerMakeString(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	bool hasError = false;

	struct String str;
	StringNew(&str,100,self->bump);

	LexerConsume(self);

	u64 increment = 2;
	while( ! LexerMatchToken(self,'\"',0))
	{
		if(LexerMatchToken(self,'\n',0) || LexerAtEnd(self))
		{
			increment = 1;
			hasError  = true;
			break;
		}

		StringPushBackChar(&str,LexerConsume(self));
	}


	
	if (ACHIOR_LABS_TRUE(hasError))
	{
		self->end       = self->index;
		LexerAddToken(self,TOKEN_ERROR_UNTERMINATED_STRING,str);
		self->hasErrors = true;
		return;
	}
	else
	{
		LexerConsume(self);
		LexerAddToken(self,TOKEN_LITERAL_STRING,str);
	}

	LexerAdvanceColumn(self,str.size + increment);
}




void LexerMakeIdentifier(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}


	struct String str;
	StringNew(&str,100,self->bump);

	while( LexerIsAlphanum(self))
	{
		StringPushBackChar(&str,LexerConsume(self));
	}

	LexerAdvanceColumn(self,str.size);
	LexerAddKeywords(self,str);
}




void LexerMakeCharacter(struct Lexer *self)
{
    if (ACHIOR_LABS_NULL(self))
    {
        return;
    }

    bool hasError = false;
    
	struct String str;
    StringNew(&str, 4, self->bump);

    LexerConsume(self); // opening '

    while (!LexerMatchToken(self, '\'', 0))
    {
        if (LexerMatchToken(self, '\n', 0) || LexerAtEnd(self))
        {
            hasError = true;
            break;
        }

        char c = LexerConsume(self);

        if (c == '\\')
        {
            if (LexerAtEnd(self))
            {
                hasError = true;
                break;
            }

            char escape  = LexerConsume(self);

            switch (escape)
            {
                case '0':  StringPushBackChar(&str, '\0'); break;
                case 'n':  StringPushBackChar(&str, '\n'); break;
                case 't':  StringPushBackChar(&str, '\t'); break;
                case 'r':  StringPushBackChar(&str, '\r'); break;
                case '\\': StringPushBackChar(&str, '\\'); break;
                case '\'': StringPushBackChar(&str, '\''); break;
                case '"':  StringPushBackChar(&str, '"'); break;
                default:
                {
                    hasError = true;
                    break;
                }
            }

            if (hasError)
                break;
        }
        else
        {
            StringPushBackChar(&str, c);
        }
    }

    if(hasError)
    {
        self->end       = self->index;
        LexerAddToken(self, TOKEN_ERROR_UNTERMINATED_CHARACTER, str);
        self->hasErrors = true;
        return;
    }

    LexerConsume(self); // closing '

    if (str.size != 1)
    {
        self->end       = self->index;
        LexerAddToken(self, TOKEN_ERROR_UNTERMINATED_CHARACTER, str);
        self->hasErrors = true;
        return;
    }

    LexerAddToken(self, TOKEN_LITERAL_CHARACTER, str);
    LexerAdvanceColumn(self, str.size + 2);
}



bool LexerMatchKeyword(struct Lexer *self,struct String str1,char *str2)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return StringEqualCstr(&str1,str2);
}

void LexerAddKeywords(struct Lexer *self,struct String str)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	if (LexerMatchKeyword(self,str,"and"))
	{
		LexerAddToken(self,TOKEN_AND,str);
	}
	else if (LexerMatchKeyword(self,str,"as"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_AS,str);
	}
	else if (LexerMatchKeyword(self,str,"bool"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_BOOL,str);
	}
	else if (LexerMatchKeyword(self,str,"break"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_BREAK,str);
	}
	else if (LexerMatchKeyword(self,str,"case"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_CASE,str);
	}
	else if (LexerMatchKeyword(self,str,"cast"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_CAST,str);
	}
	else if (LexerMatchKeyword(self,str,"char"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_CHAR,str);
	}
	else if (LexerMatchKeyword(self,str,"const"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_CONST,str);
	}
	else if (LexerMatchKeyword(self,str,"continue"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_CONTINUE,str);
	}
	else if (LexerMatchKeyword(self,str,"default"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_DEFAULT,str);
	}
	else if (LexerMatchKeyword(self,str,"do"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_DO,str);
	}
	else if (LexerMatchKeyword(self,str,"defer"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_DEFER,str);
	}
	else if (LexerMatchKeyword(self,str,"else"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_ELSE,str);
	}
	else if (LexerMatchKeyword(self,str,"elif"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_ELIF,str);
	}
	else if (LexerMatchKeyword(self,str,"enum"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_ENUM,str);
	}
	else if (LexerMatchKeyword(self,str,"extern"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_EXTERN,str);
	}
	else if (LexerMatchKeyword(self,str,"fn"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_FN,str);
	}
	else if (LexerMatchKeyword(self,str,"f32"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_F32,str);
	}
	else if (LexerMatchKeyword(self,str,"f64"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_F64,str);
	}
	else if (LexerMatchKeyword(self,str,"false"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_FALSE,str);
	}
	else if (LexerMatchKeyword(self,str,"for"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_FOR,str);
	}
	else if (LexerMatchKeyword(self,str,"foreign"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_FOREIGN,str);
	}
	else if (LexerMatchKeyword(self,str,"i8"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_I8,str);
	}
	else if (LexerMatchKeyword(self,str,"i16"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_I16,str);
	}
	else if (LexerMatchKeyword(self,str,"i32"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_I32,str);
	}
	else if (LexerMatchKeyword(self,str,"i64"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_I64,str);
	}
	else if (LexerMatchKeyword(self,str,"if"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_IF,str);
	}
	else if (LexerMatchKeyword(self,str,"impl"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_IMPL,str);
	}
	else if (LexerMatchKeyword(self,str,"loop"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_LOOP,str);
	}
	else if (LexerMatchKeyword(self,str,"macro"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_MACRO,str);
	}
	else if (LexerMatchKeyword(self,str,"match"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_MATCH,str);
	}
	else if (LexerMatchKeyword(self,str,"module"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_MODULE,str);
	}
	else if (LexerMatchKeyword(self,str,"new"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_NEW,str);
	}
	else if (LexerMatchKeyword(self,str,"not"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_NOT,str);
	}
	else if (LexerMatchKeyword(self,str,"null"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_NULL,str);
	}
	else if (LexerMatchKeyword(self,str,"or"))
	{
		LexerAddToken(self,TOKEN_OR,str);
	}
	else if (LexerMatchKeyword(self,str,"pub"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_PUB,str);
	}
	else if (LexerMatchKeyword(self,str,"return"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_RETURN,str);
	}
	else if (LexerMatchKeyword(self,str,"self"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_SELF,str);
	}
	else if (LexerMatchKeyword(self,str,"static"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_STATIC,str);
	}
	else if (LexerMatchKeyword(self,str,"str"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_STR,str);
	}
	else if (LexerMatchKeyword(self,str,"struct"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_STRUCT,str);
	}
	else if (LexerMatchKeyword(self,str,"sum"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_SUM,str);
	}
	else if (LexerMatchKeyword(self,str,"switch"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_SWITCH,str);
	}
	else if (LexerMatchKeyword(self,str,"true"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_TRUE,str);
	}
	else if (LexerMatchKeyword(self,str,"while"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_WHILE,str);
	}
	else if (LexerMatchKeyword(self,str,"u8"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_U8,str);
	}
	else if (LexerMatchKeyword(self,str,"u16"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_U16,str);
	}
	else if (LexerMatchKeyword(self,str,"u32"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_U32,str);
	}
	else if (LexerMatchKeyword(self,str,"u64"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_U64,str);
	}
	else if (LexerMatchKeyword(self,str,"use"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_USE,str);
	}
	else if (LexerMatchKeyword(self,str,"union"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_UNION,str);
	}
	else if (LexerMatchKeyword(self,str,"void"))
	{
		LexerAddToken(self,TOKEN_KEYWORD_VOID,str);
	}
	else
	{
		LexerAddToken(self,TOKEN_IDENT,str);
	}
}



void LexerAdvanceColumn(struct Lexer *self,u64 amount)
{
    if (ACHIOR_LABS_NULL(self))
    {
        return;
    }

    self->endColumn += amount;
}



void LexerAdvanceLine(struct Lexer *self,u64 amount)
{
    if (ACHIOR_LABS_NULL(self))
    {
        return;
    }

    self->endLine += amount;
    self->endColumn = 0;
}





void LexerAddToken(struct Lexer *self,enum TokenKind kind,struct String str)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return;
    }

    struct Span span;
	SpanNew(&span,self->start,self->index,self->startLine,self->startColumn,self->endLine,self->endColumn);

    struct Token *token = C4MakeToken(self->bump,kind,str,span);

    LinkedListPushBack(&self->tokens,token);
}




void LexerAddTokenSingle(struct Lexer *self,enum TokenKind kind,struct String str)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	LexerConsume(self);
	LexerAddToken(self,kind,str);
	LexerAdvanceColumn(self,1);
}


void LexerAddTokenDouble(struct Lexer *self,enum TokenKind kind,struct String str)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	LexerConsume(self);
	LexerConsume(self);
	LexerAddToken(self,kind,str);
	LexerAdvanceColumn(self,2);
}

void LexerScanToken(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	struct String str;
	StringNew(&str,100,self->bump);
	char token = LexerPeek(self,0);
	
	switch (token)
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		{
			 LexerMakeIdentifier(self);
			 break;
		}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			LexerMakeNumber(self);
			break;
		}
		case '\"':
		{
			LexerMakeString(self);
			break;
		}
		case '\'':
		{
			LexerMakeCharacter(self);
			break;
		}
		case ':':
		{
			if ( LexerMatchToken(self,':',1))
			{
				StringPushBack(&str,"::");
				LexerAddTokenDouble(self,TOKEN_RESOLUTION,str);
			}
			else
			{
				StringPushBack(&str,":");
				LexerAddTokenSingle(self,TOKEN_COLON,str);
			}
			break;
		}
		case '~':
		{
			StringPushBack(&str,"~");
			LexerAddTokenSingle(self,TOKEN_TILDE,str);
			break;
		}
		case '@':
		{
			StringPushBack(&str,"@");
			LexerAddTokenSingle(self,TOKEN_AT,str);
			break;
		}
		case ';':
		{
			StringPushBack(&str,";");
			LexerAddTokenSingle(self,TOKEN_SEMI_COLON,str);
			break;
		}
		case '(':
		{
			StringPushBack(&str,"(");
			LexerAddTokenSingle(self,TOKEN_LBRACE,str);
			break;
		}
		case ')':
		{
			StringPushBack(&str,")");
			LexerAddTokenSingle(self,TOKEN_RBRACE,str);
			break;
		}
		case '[':
		{
			StringPushBack(&str,"[");
			LexerAddTokenSingle(self,TOKEN_LBRACKET,str);
			break;
		}
		case ']':
		{
			StringPushBack(&str,"]");
			LexerAddTokenSingle(self,TOKEN_RBRACKET,str);
			break;
		}
		case ',':
		{
			StringPushBack(&str,",");
			LexerAddTokenSingle(self,TOKEN_COMMA,str);
			break;
		}
		case '.':
		{
			StringPushBack(&str,".");
			LexerAddTokenSingle(self,TOKEN_DOT,str);
			break;
		}
		case '\t':
		{
			LexerAdvanceColumn(self,4);
			LexerConsume(self);
			break;
		}
		case ' ':
		{
			LexerAdvanceColumn(self,1);
			LexerConsume(self);
			break;
		}
		case '\r':
		{
			LexerAdvanceColumn(self,1);
			LexerConsume(self);
			break;
		}
		case '\n':
		{
			LexerConsume(self);
			LexerAdvanceLine(self,1);
			break;
		}
		case '*':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"*=");
				LexerAddTokenDouble(self,TOKEN_ASSIGN_MUL,str);
			}
			else
			{
				StringPushBack(&str,"*");
				LexerAddTokenSingle(self,TOKEN_MUL,str);
			}
			break;
		}
		case '/':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"/=");
				LexerAddTokenDouble(self,TOKEN_ASSIGN_DIV,str);
			}
			else if( LexerMatchToken(self,'/',1))
			{
				while(! LexerMatchToken(self,'\n',0))
				{
					LexerConsume(self);
				}
			}
			else
			{
				StringPushBack(&str,"/");
				LexerAddTokenSingle(self,TOKEN_DIV,str);
			}
			break;
		}
		case '%':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"%%=");
				LexerAddTokenDouble(self,TOKEN_ASSIGN_MOD,str);
			}
			else
			{
				StringPushBack(&str,"%%");
				LexerAddTokenSingle(self,TOKEN_MOD,str);
			}
			break;
		}
		case '+':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"+=");
				LexerAddTokenDouble(self,TOKEN_ASSIGN_ADD,str);
			}
			else
			{
				StringPushBack(&str,"+");
				LexerAddTokenSingle(self,TOKEN_ADD,str);
			}
			break;
		}
		case '-':
		{
			if ( LexerMatchToken(self,'>',1))
			{
				StringPushBack(&str,"->");
				LexerAddTokenDouble(self,TOKEN_RETPARAM,str);
			}
			else if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"-=");
				LexerAddTokenDouble(self,TOKEN_ASSIGN_SUB,str);
			}
			else
			{
				StringPushBack(&str,"-");
				LexerAddTokenSingle(self,TOKEN_SUB,str);
			}
			break;
		}
		case '>':
		{
			if ( LexerMatchToken(self,'>',1))
			{
				StringPushBack(&str,">>");
				LexerAddTokenDouble(self,TOKEN_RIGHT_SHIFT,str);
			}
			else if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,">=");
				LexerAddTokenDouble(self,TOKEN_GREATER_EQUAL,str);
			}
			else
			{
				StringPushBack(&str,":");
				LexerAddTokenSingle(self,TOKEN_GREATER,str);
			}
			break;
		}
		case '<':
		{
			if ( LexerMatchToken(self,'<',1))
			{
				StringPushBack(&str,"<<");
				LexerAddTokenDouble(self,TOKEN_LEFT_SHIFT,str);
			}
			else if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"<=");
				LexerAddTokenDouble(self,TOKEN_LESS_EQUAL,str);
			}
			else
			{
				StringPushBack(&str,"<");
				LexerAddTokenSingle(self,TOKEN_LESS,str);
			}
			break;
		}
		case '=':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"==");
				LexerAddTokenDouble(self,TOKEN_EQUAL,str);
			}
			else
			{
				StringPushBack(&str,"=");
				LexerAddTokenSingle(self,TOKEN_ASSIGN,str);
			}
			break;
		}
		case '!':
		{
			if ( LexerMatchToken(self,'=',1))
			{
				StringPushBack(&str,"!=");
				LexerAddTokenDouble(self,TOKEN_NOT_EQUAL,str);
			}
			else
			{
				StringPushBack(&str,"!");
				LexerAddTokenSingle(self,TOKEN_NOT,str);
			}
			break;
		}
		case '&':
		{
			if ( LexerMatchToken(self,'&',1))
			{
				StringPushBack(&str,"&&");
				LexerAddTokenDouble(self,TOKEN_AND,str);
			}
			else
			{
				StringPushBack(&str,"&");
				LexerAddTokenSingle(self,TOKEN_BITWISE_AND,str);
			}
			break;
		}
		case '|':
		{
			if ( LexerMatchToken(self,'|',1))
			{
				StringPushBack(&str,"||");
				LexerAddTokenDouble(self,TOKEN_OR,str);
			}
			else
			{
				StringPushBack(&str,"|");
				LexerAddTokenSingle(self,TOKEN_BITWISE_OR,str);
			}
			break;
		}
		default:
		{
			LexerConsume(self);
			self->hasErrors = true;
			self->end        = self->index;
			
			struct Span span;
			SpanNew(&span,self->start,self->index,self->startLine,self->startColumn,self->endLine,self->endColumn);
		
			struct Diagnostic *diagnostic = DiagnosticEngineReport(self->engine,DIAGNOSTIC_ERROR,"invalid character",self->fileName,self->fileSource,self->fileLength,1);
			DiagnosticAddLabel(diagnostic,span,"unexpected character",true,self->bump);
			DiagnosticAddHelp(diagnostic,"remove this character",self->bump);
			//DiagnosticAddFix(diagnostic,span,"==",self->bump);
			//DiagnosticAddNote(diagnostic,"conditions usually use comparison",self->bump);
		}
	}
}

void LexerScanTokens(struct Lexer *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	while (! LexerAtEnd(self))
	{
		self->start       = self->index;
		self->startLine   = self->endLine;
		self->startColumn = self->endColumn;

		LexerScanToken(self);
	}

	//puts("Lexing done");

	return;
}


char *tokenKindNames[] =
{
    "TOKEN_EXP","TOKEN_MUL","TOKEN_DIV","TOKEN_MOD","TOKEN_ADD","TOKEN_SUB",

    "TOKEN_GREATER","TOKEN_LESS","TOKEN_GREATER_EQUAL","TOKEN_LESS_EQUAL",

    "TOKEN_EQUAL","TOKEN_NOT_EQUAL",

    "TOKEN_BITWISE_AND","TOKEN_BITWISE_OR","TOKEN_BITWISE_XOR","TOKEN_BITWISE_NOT","TOKEN_LEFT_SHIFT","TOKEN_RIGHT_SHIFT",

    "TOKEN_AND","TOKEN_OR","TOKEN_NOT",

    "TOKEN_TERNARY",

    "TOKEN_PLUS_PLUS","TOKEN_SUB_SUB",

    "TOKEN_ASSIGN","TOKEN_ASSIGN_ADD","TOKEN_ASSIGN_SUB","TOKEN_ASSIGN_MUL","TOKEN_ASSIGN_DIV","TOKEN_ASSIGN_MOD","TOKEN_ASSIGN_EXP","TOKEN_ASSIGN_BITWISE_AND","TOKEN_ASSIGN_BITWISE_OR","TOKEN_ASSIGN_BITWISE_XOR","TOKEN_ASSIGN_LEFT_SHIFT","TOKEN_ASSIGN_RIGHT_SHIFT",

    "TOKEN_COLON","TOKEN_TILDE","TOKEN_RESOLUTION","TOKEN_SEMI_COLON","TOKEN_LBRACE","TOKEN_RBRACE","TOKEN_LBRACKET","TOKEN_RBRACKET","TOKEN_UNDERSCORE","TOKEN_RETPARAM","TOKEN_COMMA","TOKEN_DOT","TOKEN_AT","TOKEN_MULTI_COMMENT","TOKEN_SINGLE_COMMENT",

    "TOKEN_IDENT",

    "TOKEN_LITERAL_INT","TOKEN_LITERAL_FLOAT","TOKEN_LITERAL_STRING","TOKEN_LITERAL_CHARACTER",

    "TOKEN_KEYWORD_AND","TOKEN_KEYWORD_AS","TOKEN_KEYWORD_BREAK","TOKEN_KEYWORD_BOOL","TOKEN_KEYWORD_CASE","TOKEN_KEYWORD_CAST","TOKEN_KEYWORD_CHAR","TOKEN_KEYWORD_CONST","TOKEN_KEYWORD_CONTINUE","TOKEN_KEYWORD_DEFAULT","TOKEN_KEYWORD_DO","TOKEN_KEYWORD_DEFER","TOKEN_KEYWORD_ELIF","TOKEN_KEYWORD_ELSE","TOKEN_KEYWORD_ENUM","TOKEN_KEYWORD_EXTERN","TOKEN_KEYWORD_F32","TOKEN_KEYWORD_F64","TOKEN_KEYWORD_FALSE","TOKEN_KEYWORD_FN","TOKEN_KEYWORD_FOR","TOKEN_KEYWORD_FOREIGN","TOKEN_KEYWORD_I8","TOKEN_KEYWORD_I16","TOKEN_KEYWORD_I32","TOKEN_KEYWORD_I64","TOKEN_KEYWORD_IF","TOKEN_KEYWORD_IMPL","TOKEN_KEYWORD_LOOP","TOKEN_KEYWORD_MACRO","TOKEN_KEYWORD_MATCH","TOKEN_KEYWORD_MODULE","TOKEN_KEYWORD_NEW","TOKEN_KEYWORD_NOT_NEW","TOKEN_KEYWORD_NOT","TOKEN_KEYWORD_NULL","TOKEN_KEYWORD_OR","TOKEN_KEYWORD_PUB","TOKEN_KEYWORD_RETURN","TOKEN_KEYWORD_SELF","TOKEN_KEYWORD_STATIC","TOKEN_KEYWORD_STR","TOKEN_KEYWORD_STRUCT","TOKEN_KEYWORD_SUM","TOKEN_KEYWORD_SWITCH","TOKEN_KEYWORD_TRUE","TOKEN_KEYWORD_U8","TOKEN_KEYWORD_U16","TOKEN_KEYWORD_U32","TOKEN_KEYWORD_U64","TOKEN_KEYWORD_USE","TOKEN_KEYWORD_UNION","TOKEN_KEYWORD_VOID","TOKEN_KEYWORD_WHILE","TOKEN_KEYWORD_WITH",

    "TOKEN_ERROR_INVALID_CHARACTER","TOKEN_ERROR_MALFORMED_NUMBER","TOKEN_ERROR_UNTERMINATED_STRING","TOKEN_ERROR_UNTERMINATED_CHARACTER","TOKEN_ERROR_INVALID_ESCAPE_CHARACTER","TOKEN_ERROR_UNTERMINATED_COMMENT","TOKEN_EOF",
};

void LexerPrintTokens(struct Lexer *self,char *outputfileName)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	FILE *fout = ACHIOR_LABS_FOPEN(outputfileName,"w");
	if(ACHIOR_LABS_NULL(fout))
	{
		return;
	}
	


	u32 maxTypeLen = 0;
	u64 size       = self->tokens.len;

	for (u64 i = 0; i < size; i++) 
	{
		struct Token *token = LinkedListAt(&self->tokens,i);
		u32 len             = ACHIOR_LABS_STRLEN(tokenKindNames[TOKEN_GET_KIND(*token)]);
		
		if (ACHIOR_LABS_GREATER(len,maxTypeLen))
		{
			maxTypeLen = len;
		}
	}

    for (u64 i = 0; i < size; i++) 
	{
		struct Token *token = LinkedListAt(&self->tokens,i);
        ACHIOR_LABS_FPRINTF(fout,"Type: %-*s  Lexeme: %s\n",maxTypeLen,tokenKindNames[TOKEN_GET_KIND(*token)],TOKEN_GET_VALUE_DATA(*token) ? TOKEN_GET_VALUE_DATA(*token) : "(null)");
    }


	ACHIOR_LABS_FCLOSE(fout);
}


