#include "Include/Parser.h"


bool ParserNew(struct Parser *self,char *fileName,char *fileSource,struct LinkedList tokens,struct DiagnosticEngine *engine,struct BumpAllocator *bump)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->fileName   = fileName;
	self->fileSource = fileSource;
	self->fileLength = ACHIOR_LABS_STRLEN(fileSource);
	self->tokens     = tokens;
	self->tokenSize  = tokens.len;
	self->index      = 0;
	self->bump       = bump;
	self->astProgram = NULL;
	self->engine     = engine;
	self->panicMode  = false;
	self->hasErrors  = false;

	ParserParseProgram(self);

	//puts("parsing done");
	return true;
}



enum TokenKind ParserKeywordToToken(struct Parser *self,char *keyword)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return TOKEN_EOF;
	}



	if (!strcmp(keyword,"and"))
	{
		return TOKEN_AND;
	}
	else if (!strcmp(keyword,"as"))
	{
		return TOKEN_KEYWORD_AS;
	}
	else if (!strcmp(keyword,"bool"))
	{
		return TOKEN_KEYWORD_BOOL;
	}
	else if (!strcmp(keyword,"break"))
	{
		return TOKEN_KEYWORD_BREAK;
	}
	else if (!strcmp(keyword,"case"))
	{
		return TOKEN_KEYWORD_CASE;
	}
	else if (!strcmp(keyword,"cast"))
	{
		return TOKEN_KEYWORD_CAST;
	}
	else if (!strcmp(keyword,"char"))
	{
		return TOKEN_KEYWORD_CHAR;
	}
	else if (!strcmp(keyword,"const"))
	{
		return TOKEN_KEYWORD_CONST;
	}
	else if (!strcmp(keyword,"continue"))
	{
		return TOKEN_KEYWORD_CONTINUE;
	}
	else if (!strcmp(keyword,"default"))
	{
		return TOKEN_KEYWORD_DEFAULT;
	}
	else if (!strcmp(keyword,"do"))
	{
		return TOKEN_KEYWORD_DO;
	}
	else if (!strcmp(keyword,"defer"))
	{
		return TOKEN_KEYWORD_DEFER;
	}
	else if (!strcmp(keyword,"else"))
	{
		return TOKEN_KEYWORD_ELSE;
	}
	else if (!strcmp(keyword,"elif"))
	{
		return TOKEN_KEYWORD_ELIF;
	}
	else if (!strcmp(keyword,"enum"))
	{
		return TOKEN_KEYWORD_ENUM;
	}
	else if (!strcmp(keyword,"extern"))
	{
		return TOKEN_KEYWORD_EXTERN;
	}
	else if (!strcmp(keyword,"fn"))
	{
		return TOKEN_KEYWORD_FN;
	}
	else if (!strcmp(keyword,"f32"))
	{
		return TOKEN_KEYWORD_F32;
	}
	else if (!strcmp(keyword,"f64"))
	{
		return TOKEN_KEYWORD_F64;
	}
	else if (!strcmp(keyword,"false"))
	{
		return TOKEN_KEYWORD_FALSE;
	}
	else if (!strcmp(keyword,"for"))
	{
		return TOKEN_KEYWORD_FOR;
	}
	else if (!strcmp(keyword,"foreign"))
	{
		return TOKEN_KEYWORD_FOREIGN;
	}
	else if (!strcmp(keyword,"i8"))
	{
		return TOKEN_KEYWORD_I8;
	}
	else if (!strcmp(keyword,"i16"))
	{
		return TOKEN_KEYWORD_I16;
	}
	else if (!strcmp(keyword,"i32"))
	{
		return TOKEN_KEYWORD_I32;
	}
	else if (!strcmp(keyword,"i64"))
	{
		return TOKEN_KEYWORD_I64;
	}
	else if (!strcmp(keyword,"if"))
	{
		return TOKEN_KEYWORD_IF;
	}
	else if (!strcmp(keyword,"impl"))
	{
		return TOKEN_KEYWORD_IMPL;
	}
	else if (!strcmp(keyword,"isize"))
	{
		return TOKEN_KEYWORD_IMPL;
	}
	else if (!strcmp(keyword,"loop"))
	{
		return TOKEN_KEYWORD_LOOP;
	}
	else if (!strcmp(keyword,"macro"))
	{
		return TOKEN_KEYWORD_MACRO;
	}
	else if (!strcmp(keyword,"match"))
	{
		return TOKEN_KEYWORD_MATCH;
	}
	else if (!strcmp(keyword,"module"))
	{
		return TOKEN_KEYWORD_MODULE;
	}
	else if (!strcmp(keyword,"new"))
	{
		return TOKEN_KEYWORD_NEW;
	}
	else if (!strcmp(keyword,"not"))
	{
		return TOKEN_KEYWORD_NOT;
	}
	else if (!strcmp(keyword,"null"))
	{
		return TOKEN_KEYWORD_NULL;
	}
	else if (!strcmp(keyword,"or"))
	{
		return TOKEN_OR;
	}
	else if (!strcmp(keyword,"pub"))
	{
		return TOKEN_KEYWORD_PUB;
	}
	else if (!strcmp(keyword,"return"))
	{
		return TOKEN_KEYWORD_RETURN;
	}
	else if (!strcmp(keyword,"self"))
	{
		return TOKEN_KEYWORD_SELF;
	}
	else if (!strcmp(keyword,"static"))
	{
		return TOKEN_KEYWORD_STATIC;
	}
	else if (!strcmp(keyword,"str"))
	{
		return TOKEN_KEYWORD_STR;
	}
	else if (!strcmp(keyword,"struct"))
	{
		return TOKEN_KEYWORD_STRUCT;
	}
	else if (!strcmp(keyword,"sum"))
	{
		return TOKEN_KEYWORD_SUM;
	}
	else if (!strcmp(keyword,"switch"))
	{
		return TOKEN_KEYWORD_SWITCH;
	}
	else if (!strcmp(keyword,"true"))
	{
		return TOKEN_KEYWORD_TRUE;
	}
	else if (!strcmp(keyword,"type"))
	{
		return TOKEN_KEYWORD_TYPE;
	}
	else if (!strcmp(keyword,"while"))
	{
		return TOKEN_KEYWORD_WHILE;
	}
	else if (!strcmp(keyword,"u8"))
	{
		return TOKEN_KEYWORD_U8;
	}
	else if (!strcmp(keyword,"u16"))
	{
		return TOKEN_KEYWORD_U16;
	}
	else if (!strcmp(keyword,"u32"))
	{
		return TOKEN_KEYWORD_U32;
	}
	else if (!strcmp(keyword,"u64"))
	{
		return TOKEN_KEYWORD_U64;
	}
	else if (!strcmp(keyword,"use"))
	{
		return TOKEN_KEYWORD_USE;
	}
	else if (!strcmp(keyword,"usize"))
	{
		return TOKEN_KEYWORD_USIZE;
	}
	else if (!strcmp(keyword,"union"))
	{
		return TOKEN_KEYWORD_UNION;
	}
	else if (!strcmp(keyword,"void"))
	{
		return TOKEN_KEYWORD_VOID;
	}
	else
	{
		return TOKEN_EOF;
	}
	
}

enum TokenKind ParserSymbolToToken(struct Parser *self,char *keyword)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return TOKEN_EOF;
	}

	

	if (!strcmp(keyword,"="))
	{
		return TOKEN_ASSIGN;
	}
	else if (!strcmp(keyword,"+="))
	{
		return TOKEN_ASSIGN_ADD;
	}
	else if (!strcmp(keyword,"-="))
	{
		return TOKEN_ASSIGN_SUB;
	}
	else if (!strcmp(keyword,"*="))
	{
		return TOKEN_ASSIGN_MUL;
	}
	else if (!strcmp(keyword,"/="))
	{
		return TOKEN_ASSIGN_DIV;
	}
	else if (!strcmp(keyword,"%%="))
	{
		return TOKEN_ASSIGN_MOD;
	}
	else if (!strcmp(keyword,"-"))
	{
		return TOKEN_SUB;
	}
	else if (!strcmp(keyword,"+"))
	{
		return TOKEN_ADD;
	}
	else if (!strcmp(keyword,"*"))
	{
		return TOKEN_MUL;
	}
	else if (!strcmp(keyword,"/"))
	{
		return TOKEN_DIV;
	}
	else if (!strcmp(keyword,"%%"))
	{
		return TOKEN_MOD;
	}
	else if (!strcmp(keyword,"<"))
	{
		return TOKEN_LESS;
	}
	else if (!strcmp(keyword,"<<"))
	{
		return TOKEN_LEFT_SHIFT;
	}
	else if (!strcmp(keyword,"<="))
	{
		return TOKEN_LESS_EQUAL;
	}
	else if (!strcmp(keyword,">"))
	{
		return TOKEN_GREATER;
	}
	else if (!strcmp(keyword,">>"))
	{
		return TOKEN_RIGHT_SHIFT;
	}
	else if (!strcmp(keyword,">="))
	{
		return TOKEN_GREATER_EQUAL;
	}
	else if (!strcmp(keyword,"=="))
	{
		return TOKEN_EQUAL;
	}
	else if (!strcmp(keyword,"!="))
	{
		return TOKEN_NOT_EQUAL;
	}
	else if (!strcmp(keyword,"&&"))
	{
		return TOKEN_AND;
	}
	else if (!strcmp(keyword,"|"))
	{
		return TOKEN_BITWISE_OR;
	}
	else if (!strcmp(keyword,"&"))
	{
		return TOKEN_BITWISE_AND;
	}
	else if (!strcmp(keyword,"||"))
	{
		return TOKEN_OR;
	}
	else if (!strcmp(keyword,"~"))
	{
		return TOKEN_TILDE;
	}
	else if (!strcmp(keyword,"!"))
	{
		return TOKEN_NOT;
	}
	else if (!strcmp(keyword,"->"))
	{
		return TOKEN_RETPARAM;
	}
	else if (!strcmp(keyword,"("))
	{
		return TOKEN_LBRACE;
	}
	else if (!strcmp(keyword,")"))
	{
		return TOKEN_RBRACE;
	}
	else if (!strcmp(keyword,"["))
	{
		return TOKEN_LBRACKET;
	}
	else if (!strcmp(keyword,"]"))
	{
		return TOKEN_RBRACKET;
	}
	else if (!strcmp(keyword,":"))
	{
		return TOKEN_COLON;
	}
	else if (!strcmp(keyword,"::"))
	{
		return TOKEN_RESOLUTION;
	}
	else if (!strcmp(keyword,","))
	{
		return TOKEN_COMMA;
	}
	else if (!strcmp(keyword,"."))
	{
		return TOKEN_DOT;
	}
	else if (!strcmp(keyword,"..."))
	{
		return TOKEN_ELIPSIS;
	}
	else if (!strcmp(keyword,"@"))
	{
		return TOKEN_AT;
	}
	else
	{
		return TOKEN_EOF;
	}
	
}



enum TokenKind ParserStringToToken(struct Parser *self,char *string)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return TOKEN_EOF;
	}

	return ParserSymbolToToken(self,string);
}


struct Token *ParserPeek(struct Parser *self,i64 lookAhead)
{
	if(ACHIOR_LABS_NULL(self) || ParserAtEnd(self) || ACHIOR_LABS_GREATER_EQUAL(self->index + lookAhead,self->tokenSize))
	{
		return NULL;
	}

	return LinkedListAt(&self->tokens,self->index + lookAhead);
}


struct Token *ParserConsume(struct Parser *self)
{
	if(ACHIOR_LABS_NULL(self) || ParserAtEnd(self) || ACHIOR_LABS_GREATER_EQUAL(self->index,self->tokenSize))
	{
		return NULL;
	}

	return LinkedListAt(&self->tokens,self->index++);
}



bool ParserIsTokenKind(struct Parser *self,enum TokenKind kind,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self) || ParserAtEnd(self))
	{
		return false;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,token);

	token = ParserPeek(self,lookAhead);

	return ACHIOR_LABS_EQUAL(TOKEN_GET_KIND(*token),kind);
}




bool ParserIsToken(struct Parser *self,char *string,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self) || ParserAtEnd(self))
	{
		return false;
	}

	return ParserIsTokenKind(self,ParserSymbolToToken(self,string),lookAhead) || ParserIsTokenKind(self,ParserKeywordToToken(self,string),lookAhead);
}



void ParserFatal(struct Parser *self,struct Token *token,char *message,char *label,char *help,char *fix,char *note)
{
	if( ACHIOR_LABS_NULL(self) || ParserAtEnd(self))
	{
		return;
	}

	ACHIOR_LABS_STRUCT_INIT(struct Span,span);
	ACHIOR_LABS_PTR_INIT(struct Diagnostic,diagnostic);

	self->panicMode  = true;
	self->hasErrors  = true;
	span             = token->span;
	diagnostic       = DiagnosticEngineReport(self->engine,DIAGNOSTIC_ERROR,message,self->fileName,self->fileSource,self->fileLength,1);
	
	
	if(ACHIOR_LABS_NOT_NULL(label))
	{
		DiagnosticAddLabel(diagnostic,span,label,true,self->bump);
	}
	else
	{
		DiagnosticAddLabel(diagnostic,span,"",true,self->bump);
	}

	if(ACHIOR_LABS_NOT_NULL(help))
	{
		DiagnosticAddHelp(diagnostic,help,self->bump);
	}

	if(ACHIOR_LABS_NOT_NULL(fix))
	{
		DiagnosticAddFix(diagnostic,span,fix,self->bump);
	}
	
	if(ACHIOR_LABS_NOT_NULL(note))
	{
		DiagnosticAddNote(diagnostic,note,self->bump);
	}
}




void ParserSynchronizeDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,token);

	while( !ParserAtEnd(self))
	{
		token = ParserPeek(self,0);

		switch(TOKEN_GET_KIND(*token))
		{
			case TOKEN_KEYWORD_PUB:
			case TOKEN_KEYWORD_FN:
			case TOKEN_KEYWORD_FOREIGN:
			{
				return;
				break;
			}
			default:
			{
				if( ParserIsType(self) || ParserIsIdentifier(self))
				{
					return;
				}
			}
		}

		ParserConsume(self);
	}
}




void ParserSynchronizeStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,token);

	while( !ParserAtEnd(self))
	{
		token = ParserPeek(self,0);

		switch(TOKEN_GET_KIND(*token))
		{
			case TOKEN_KEYWORD_IF:
			case TOKEN_KEYWORD_LOOP:
			case TOKEN_KEYWORD_WHILE:
			case TOKEN_KEYWORD_FOR:
			case TOKEN_KEYWORD_CONTINUE:
			case TOKEN_KEYWORD_BREAK:
			case TOKEN_KEYWORD_RETURN:
			{
				return;
				break;
			}
			default:
			{
				if( ParserIsType(self) || ParserIsIdentifier(self))
				{
					return;
				}
			}
		}

		ParserConsume(self);
	}
}


extern const char *tokenTypeNames[];

bool ParserIsType(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,token);

	token = ParserPeek(self,0);

	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_KEYWORD_VOID:
		case TOKEN_KEYWORD_CHAR:
		case TOKEN_KEYWORD_I8:
		case TOKEN_KEYWORD_I16:
		case TOKEN_KEYWORD_I32:
		case TOKEN_KEYWORD_I64:
		case TOKEN_KEYWORD_U8:
		case TOKEN_KEYWORD_U16:
		case TOKEN_KEYWORD_U32:
		case TOKEN_KEYWORD_U64:
		case TOKEN_KEYWORD_STR:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
}




bool ParserIsSymbol(struct Parser *self,char *symbol,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self) || ParserAtEnd(self))
	{
		return false;
	}

	return ParserIsTokenKind(self,ParserSymbolToToken(self,symbol),lookAhead);
}



bool ParserExpectSymbol(struct Parser *self,char *symbol,char *message)
{
	if( ACHIOR_LABS_NULL(self) || ParserAtEnd(self))
	{
		return false;
	}

	ACHIOR_LABS_VAR_INIT(bool,status);

	status = false;
	
	if( ParserIsTokenKind(self,ParserSymbolToToken(self,symbol),0))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),message,"unexpected symbol","remove this symbol",symbol,NULL);
	}

	ParserConsume(self);

	return status;

}



bool ParserIsKeyword(struct Parser *self,char *keyword,i64 lookAhead)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenKind(self,ParserKeywordToToken(self,keyword),lookAhead);
}



bool ParserExpectKeyword(struct Parser *self,char *keyword,char *message)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	ACHIOR_LABS_VAR_INIT(bool,status);

	status = false;

	if( ParserIsTokenKind(self,ParserKeywordToToken(self,keyword),0))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),message,"unexpected keyword","remove this word",keyword,NULL);
	}

	ParserConsume(self);

	return status;
}





bool ParserIsStringLiteral(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenKind(self,TOKEN_LITERAL_STRING,0);
}


bool ParserExpectStringLiteral(struct Parser *self,char *literal,char *message)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	ACHIOR_LABS_VAR_INIT(bool,status);
	ACHIOR_LABS_STRUCT_INIT(struct String,str);

	status = false;
	str    = ParserPeek(self,0)->value;

	if( StringEqualCstr(&str,literal))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),message,"unexpected literal","remove this literal",literal,NULL);
	}

	ParserConsume(self);

	return status;
}



bool ParserIsIdentifier(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenKind(self,TOKEN_IDENT,0);
}




bool ParserAtEnd(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ACHIOR_LABS_GREATER_EQUAL(self->index,self->tokenSize);
}

struct ASTProgram *ParserParseProgram(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTProgram,program);
	ACHIOR_LABS_PTR_INIT(struct ASTDeclaration,decl);

 

	LinkedListNew(&self->decls,self->bump);
	while( !ParserAtEnd(self))
	{
		decl = ParserParseDecl(self);

		if(ACHIOR_LABS_TRUE(self->panicMode))
		{
			ParserSynchronizeDecl(self);
			continue;
		}

		if( ACHIOR_LABS_NULL(decl))
		{
			continue;
		}


		LinkedListPushBack(&self->decls,decl);
	}



	program          = C4MakeASTProgram(self->bump,self->decls);
	self->astProgram = program;

	return program;
}

#define ACHIOR_LABS_SYNCHRONIZE(is_decl) do                                  \
								{                                            \
									if(self->panicMode)                     \
									{                                        \
										return NULL;                         \
									}                                        \
								}while(0);                                   \







struct ASTDeclaration *ParserParseDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTDeclaration,decl);
	ACHIOR_LABS_PTR_INIT(struct Token,token);

	token = ParserPeek(self,0);


	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_KEYWORD_USE:
		{
			return ParserParseUseDecl(self);
			break;
		}
		case TOKEN_KEYWORD_PUB:
		{
			ParserConsume(self);

			if(ParserIsToken(self,"fn",0))
			{
				struct String tmp;
				decl = ParserParseFunctionDecl(self,true,false,false,false,tmp,false,tmp);	
			}
			else
			{
				ParserFatal(self,ParserPeek(self,0),"invalid use of pub modifier",NULL,"use pub with fn",NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(true);
			}

			break;
		}
		case TOKEN_KEYWORD_FN:
		{
			struct String tmp;
			decl = ParserParseFunctionDecl(self,false,true,false,false,tmp,false,tmp);
			break;
		}
		case TOKEN_KEYWORD_FOREIGN:
		{
			ParserParseForeignDecl(self);
			return NULL;
			break;
		}
		case TOKEN_KEYWORD_ENUM:
		{
			struct String tmp;
			decl = ParserParseEnumDecl(self);
			break;
		}
		case TOKEN_KEYWORD_STRUCT:
		{
			decl = ParserParseStructDecl(self);
			break;
		}
		case TOKEN_KEYWORD_UNION:
		{
			decl = ParserParseStructDecl(self);
			break;
		}
		case TOKEN_KEYWORD_IMPL:
		{
			decl = ParserParseImplDecl(self);
			break;
		}
		case TOKEN_KEYWORD_SUM:
		{
			decl = ParserParseSumDecl(self);
			break;
		}
		case TOKEN_KEYWORD_TYPE:
		{
			decl = ParserParseTypeDecl(self);
			break;
		}
		case TOKEN_KEYWORD_CONST:
		{
			decl = ParserParseVariableDecl(self);
			break;
		}
		case TOKEN_EOF:
		{
			//ACHIOR_LABS_PRINT("eof");
			ParserConsume(self);
			break;
		}
		default:
		{
			if( ParserIsType(self) || ParserParseTryVariableDecl(self) )
			{
				decl = ParserParseVariableDecl(self);
			}
			//puts(ParserConsume(self)->value.data);
			break;
		}
	}

	return decl;
}





struct ASTDeclaration *ParserParseUseDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,path);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct Token,alias);
	ACHIOR_LABS_PTR_INIT(struct ASTUseDecl,decl);

	// consume use keyword
	ParserExpectKeyword(self,"use","expected use keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);

    LinkedListNew(&path,self->bump);


	// check if we have an import name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after use",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}


    LinkedListPushBack(&path,TOKEN_GET_VALUE_DATA(*ident));

    while (ParserIsToken(self,"::",0))
    {
		ParserExpectSymbol(self,"::","expected :: ");
		ACHIOR_LABS_SYNCHRONIZE(true);

        ident = ParserConsume(self);
        LinkedListPushBack(&path,TOKEN_GET_VALUE_DATA(*ident));
    }


	// consume as keyword
	ParserExpectKeyword(self,"as","expected as keyword after module paths");
	ACHIOR_LABS_SYNCHRONIZE(true);


	// check if we have an alias name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		alias = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an alias identifier after as keyword",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	decl = C4MakeASTUseDecl(self->bump,path,alias);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_USE,decl,false);
}




struct ASTDeclaration *ParserParseEnumDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,constants);
	ACHIOR_LABS_PTR_INIT(struct ASTEnumConstant,constant);
	ACHIOR_LABS_PTR_INIT(struct ASTEnumDecl,decl);
	
	// consume enum keyword
	ParserExpectKeyword(self,"enum","expected enum keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);


	// check if we have an enum name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after struct",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	LinkedListNew(&constants,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		constant = ParserParseEnumConstant(self);
		if( ACHIOR_LABS_NULL(constant))
		{
			continue;
		}

		LinkedListPushBack(&constants,constant);
		if( ParserIsSymbol(self,":",0))
		{
			break;
		}
	}

	ParserExpectSymbol(self,":","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	decl = C4MakeASTEnumDecl(self->bump,ident,constants);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_ENUM,decl,false);
}


struct ASTEnumConstant *ParserParseEnumConstant(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTEnumConstant,constant);
	ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);

	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier as enum constant",NULL,"Add an enum constant",NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}


	if(ParserIsToken(self,"=",0))
	{
		ParserConsume(self);
		expr = ParserParseExpr(self,0);
	}

	return C4MakeASTEnumConstant(self->bump,ident,expr);
}




struct ASTDeclaration *ParserParseStructDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTStructDecl,decl);
	ACHIOR_LABS_PTR_INIT(struct ASTStructProperty,property);
	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,properties);

	// consume struct keyword
	ParserExpectKeyword(self,"struct","expected struct keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);


	// check if we have a struct name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after struct",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	LinkedListNew(&properties,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		property = ParserParseStructProperty(self);
		if( ACHIOR_LABS_NULL(property))
		{
			continue;
		}

		LinkedListPushBack(&properties,property);
		if( ParserIsSymbol(self,":",0))
		{
			break;
		}
	}

	ParserExpectSymbol(self,":","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	decl = C4MakeASTStructDecl(self->bump,ident,properties);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_STRUCT,decl,false);
}






struct ASTStructProperty *ParserParseStructProperty(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);


	type = ParserParseType(self);
	if( ACHIOR_LABS_NULL(type))
	{
		ACHIOR_LABS_PRINT("null argument type");
	}


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after type in struct property",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	return C4MakeASTStructProperty(self->bump,type,ident);
}






struct ASTDeclaration *ParserParseImplDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionDecl,method);
	ACHIOR_LABS_PTR_INIT(struct ASTImplDecl,decl);
	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,methods);
	ACHIOR_LABS_STRUCT_INIT(struct String,tmp);

	// consume impl keyword
	ParserExpectKeyword(self,"impl","expected impl keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);

	// check if we have a struct name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after impl",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	LinkedListNew(&methods,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		method = ParserParseImplMethod(self,ident,false,true,false,false,tmp,false,tmp);
		if( ACHIOR_LABS_NULL(method))
		{
			continue;
		}

		LinkedListPushBack(&methods,method);
		if( ParserIsSymbol(self,":",0))
		{
			break;
		}
	}

	ParserExpectSymbol(self,":","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	decl = C4MakeASTImplDecl(self->bump,ident,methods);
	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_IMPL,decl,false);
}





struct ASTFunctionDecl *ParserParseImplMethod(struct Parser *self,struct Token *structIdent,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionDecl,decl);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionArgument,argument);
	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct Token,selfIdent);
	ACHIOR_LABS_PTR_INIT(struct ASTPointerType,pointerType);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionAttributes,attributes);

	ACHIOR_LABS_VAR_INIT(bool,hasVariableArguments);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);
	ACHIOR_LABS_STRUCT_INIT(struct String,tmp);

	if(ACHIOR_LABS_TRUE(isPublic) && ACHIOR_LABS_TRUE(isForeign))
	{
		ParserFatal(self,ParserPeek(self,0),"function cannot be both foreign and public",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume fn keyword
	ParserExpectKeyword(self,"fn","expected fn");
	ACHIOR_LABS_SYNCHRONIZE(true);

	// check if we have a function name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after fn",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}


	// consume the open paren
	ParserExpectSymbol(self,"(","expected (");
	ACHIOR_LABS_SYNCHRONIZE(true);

	LinkedListNew(&arguments,self->bump);

	StringNew(&tmp,10,self->bump);
	StringPushBack(&tmp,"self");

	selfIdent   = C4MakeToken(self->bump,TOKEN_IDENT,tmp,(struct Span){});
	type        = C4MakeASTType(self->bump,AST_DATA_TYPE_STRUCT,C4MakeASTStructType(self->bump,structIdent,(struct Layout){0}));
	pointerType = C4MakeASTPointerType(self->bump,type);
	type        = C4MakeASTType(self->bump,AST_DATA_TYPE_POINTER,pointerType);
	argument    = C4MakeASTFunctionArgument(self->bump,type,selfIdent);
	
	LinkedListPushBack(&arguments,argument);

	while( !ParserIsToken(self,")",0))
	{
		if(ParserIsToken(self,"...",0))
		{
			hasVariableArguments = true;
			ParserConsume(self);
			break;
		}

		argument = ParserParseFunctionArgument(self);
		if( ACHIOR_LABS_NULL(argument))
		{
			continue;
		}

		LinkedListPushBack(&arguments,argument);
		if( ParserIsSymbol(self,")",0))
		{
			break;
		}

		ParserExpectSymbol(self,",","expected , in fn argument");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	ParserExpectSymbol(self,")","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	if(ParserIsToken(self,"->",0))
	{
		ParserExpectSymbol(self,"->","expected ->");
		ACHIOR_LABS_SYNCHRONIZE(true);
		type = ParserParseType(self);
	}
	else
	{
		type = C4MakeASTType(self->bump,AST_DATA_TYPE_VOID,NULL);
	}
	

	if(ACHIOR_LABS_FALSE(isForeign))
	{

		if( ParserIsSymbol(self,":",0))
		{
			block = ParserParseBlockStmt(self);
		}
		else
		{
			ParserFatal(self,ParserPeek(self,0),"expected a function block => Function lacks a valid block",NULL,NULL,NULL,NULL);
			ACHIOR_LABS_SYNCHRONIZE(true);
		}
	}


	attributes = C4MakeASTFunctionAttributes(self->bump,isPublic,isStatic,isNaked,isForeign,foreignAbi,hasLinkName,linkName);

	return C4MakeASTFunctionDecl(self->bump,type,ident,arguments,block,attributes,hasVariableArguments);
}








struct ASTDeclaration *ParserParseSumDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTSumDecl,decl);
	ACHIOR_LABS_PTR_INIT(struct ASTSumVariant,variant);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,variants);

	// consume sum keyword
	ParserExpectKeyword(self,"sum","expected sum keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);


	// check if we have a sum name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after sum",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	LinkedListNew(&variants,self->bump);
	

	while( !ParserIsToken(self,":",0))
	{
		variant = ParserParseSumVariant(self);
		if( ACHIOR_LABS_NULL(variant))
		{
			continue;
		}

		LinkedListPushBack(&variants,variant);
		if( ParserIsSymbol(self,":",0))
		{
			break;
		}
	}

	ParserExpectSymbol(self,":","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	decl = C4MakeASTSumDecl(self->bump,ident,variants);
	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_SUM,decl,false);
}





struct ASTSumVariant *ParserParseSumVariant(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_VAR_INIT(enum ASTSumVariantKind,kind);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,fields);


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier in sumtype field",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	kind = AST_SUM_VARIANT_NONE;
	
	LinkedListNew(&fields,self->bump);

	if( ParserIsSymbol(self,"(",0))
	{
		// consume the (	
		ParserExpectSymbol(self,"(","expected (");

		type = ParserParseType(self);

		if( ACHIOR_LABS_NULL(type))
		{
			ACHIOR_LABS_PRINT("null argument type");
		}


		if(ParserIsSymbol(self,")",0))
		{
			LinkedListPushBack(&fields,type);
			kind = AST_SUM_VARIANT_UNIT;
		}
		else
		{
			kind = AST_SUM_VARIANT_TUPLE;
			
			while(true)
			{
				LinkedListPushBack(&fields,type);

				if(ParserIsSymbol(self,")",0))
				{
					break;
				}
				else
				{
					ParserExpectSymbol(self,",","expected a ,after sum tuple field value");
				}

				type = ParserParseType(self);
				if( ACHIOR_LABS_NULL(type))
				{
					ACHIOR_LABS_PRINT("null argument type");
				}
			}
		}

		// consume the )
		ParserExpectSymbol(self,")","expected )");
	}

	return C4MakeASTSumVariant(self->bump,ident,kind,fields);
}



void *ParserParseForeignDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_STRUCT_INIT(struct String,foreignAbi);


	// consume foreign keyword
	ParserExpectKeyword(self,"foreign","expected foreign");
	
	if(ParserIsStringLiteral(self))
	{
		foreignAbi = TOKEN_GET_VALUE(*ParserConsume(self));
	}


	ParserExpectSymbol(self,":","expected a : after foreignAbi ");
	ACHIOR_LABS_SYNCHRONIZE(true);

	while(! ParserIsToken(self,":",0))
	{
		LinkedListPushBack(&self->decls,ParserParseFunctionDecl(self,false,false,false,true,foreignAbi,false,(struct String){}));	
	}

	ParserExpectSymbol(self,":","expected : after foreign");
	ACHIOR_LABS_SYNCHRONIZE(true);

	return NULL;
}




struct ASTDeclaration *ParserParseFunctionDecl(struct Parser *self,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionDecl,decl);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionArgument,argument);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionAttributes,attributes);
	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);

	ACHIOR_LABS_VAR_INIT(bool,hasVariableArguments);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);


	if(ACHIOR_LABS_TRUE(isPublic) && ACHIOR_LABS_TRUE(isForeign))
	{
		ParserFatal(self,ParserPeek(self,0),"function cannot be both foreign and public",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume fn keyword
	ParserExpectKeyword(self,"fn","expected fn");
	ACHIOR_LABS_SYNCHRONIZE(true);

	// check if we have a function name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after fn",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the open paren
	ParserExpectSymbol(self,"(","expected (");
	ACHIOR_LABS_SYNCHRONIZE(true);


	LinkedListNew(&arguments,self->bump);

	while( !ParserIsToken(self,")",0))
	{
		if(ParserIsToken(self,"...",0))
		{
			hasVariableArguments = true;
			ParserConsume(self);
			break;
		}


		argument = ParserParseFunctionArgument(self);
		ACHIOR_LABS_SYNCHRONIZE(true);

		if( ACHIOR_LABS_NULL(argument))
		{
			continue;
		}

		LinkedListPushBack(&arguments,argument);
		if( ParserIsSymbol(self,")",0))
		{
			break;
		}

		ParserExpectSymbol(self,",","expected , in fn argument");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	ParserExpectSymbol(self,")","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);


	if(ParserIsToken(self,"->",0))
	{
		ParserExpectSymbol(self,"->","expected ->");
		ACHIOR_LABS_SYNCHRONIZE(true);

		type = ParserParseType(self);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}
	else
	{
		type = C4MakeASTType(self->bump,AST_DATA_TYPE_VOID,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}
	

	if(ACHIOR_LABS_FALSE(isForeign))
	{
		if( ParserIsSymbol(self,":",0))
		{
			block = ParserParseBlockStmt(self);
			ACHIOR_LABS_SYNCHRONIZE(true);
		}
		else
		{
			ParserFatal(self,ParserPeek(self,0),"function Lacks a valid block => expected a valid block",NULL,NULL,NULL,NULL);
			ACHIOR_LABS_SYNCHRONIZE(true);
		}
	}


	attributes = C4MakeASTFunctionAttributes(self->bump,isPublic,isStatic,isNaked,isForeign,foreignAbi,hasLinkName,linkName);
	decl       = C4MakeASTFunctionDecl(self->bump,type,ident,arguments,block,attributes,hasVariableArguments);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_FUNCTION,decl,false);
}



struct ASTFunctionArgument *ParserParseFunctionArgument(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTFunctionArgument,argument);

	type = ParserParseType(self);

	if( ACHIOR_LABS_NULL(type))
	{
		ACHIOR_LABS_PRINT("null argument type");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after fn",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	argument = C4MakeASTFunctionArgument(self->bump,type,ident);
	return argument;

}






struct ASTDeclaration *ParserParseVariableDecl(struct Parser *self)
{
	ACHIOR_LABS_VAR_INIT(bool,isConstant);
	ACHIOR_LABS_PTR_INIT(struct ASTVariableDecl,decl);

	if(ParserIsToken(self,"const",0))
	{
		ParserExpectKeyword(self,"const","expected const");
		ACHIOR_LABS_SYNCHRONIZE(false);

		isConstant = true;
	}


	decl = ParserParseVariableDeclaration(self,isConstant);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_VARIABLE,decl,false);
}







struct ASTDeclaration *ParserParseTypeDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTTypeDecl,decl);

	ParserExpectKeyword(self,"type","expected type");
	ACHIOR_LABS_SYNCHRONIZE(true);


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after type",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	ParserExpectSymbol(self,"=","expected =");
	ACHIOR_LABS_SYNCHRONIZE(true);

	type = ParserParseType(self);

	if( ACHIOR_LABS_NULL(type))
	{
		ACHIOR_LABS_PRINT("null argument type");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}


	

	decl = C4MakeASTTypeDecl(self->bump,ident,type);

	return C4MakeASTDeclaration(self->bump,AST_DECLARATION_TYPE,decl,false);;

}



enum ASTDataType ParserGetDataType(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return AST_DATA_TYPE_NONE;
	}

	ACHIOR_LABS_VAR_INIT(enum ASTDataType,type);

	if( ParserIsToken(self,"void",0))
	{
		type = AST_DATA_TYPE_VOID;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"char",0))
	{
		type = AST_DATA_TYPE_CHAR;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i8",0))
	{
		type = AST_DATA_TYPE_I8;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i16",0))
	{
		type = AST_DATA_TYPE_I16;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i32",0))
	{
		type = AST_DATA_TYPE_I32;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i64",0))
	{
		type = AST_DATA_TYPE_I64;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"isize",0))
	{
		type = AST_DATA_TYPE_ISIZE;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u8",0))
	{
		type = AST_DATA_TYPE_U8;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u16",0))
	{
		type = AST_DATA_TYPE_U16;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u32",0))
	{
		type = AST_DATA_TYPE_U32;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u64",0))
	{
		type = AST_DATA_TYPE_U64;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"usize",0))
	{
		type = AST_DATA_TYPE_USIZE;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"str",0))
	{
		type = AST_DATA_TYPE_STRING;
		ParserConsume(self);
	}
	else
	{
		type = AST_DATA_TYPE_NONE;
		ParserConsume(self);
	}

	return type;
}




struct ASTType *ParserParsePrimaryType(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_VAR_INIT(enum ASTDataType,dataType);

	ACHIOR_LABS_PTR_INIT(void,typeType);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTType,type);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,path);



	if( ParserIsType(self))
	{
		dataType = ParserGetDataType(self);

		if(ACHIOR_LABS_EQUAL(dataType,AST_DATA_TYPE_NONE))
		{
			self->panicMode = true;
			ACHIOR_LABS_SYNCHRONIZE(false);
		}
	}
	else if(ParserIsIdentifier(self))
	{
		LinkedListNew(&path, self->bump);

		// first identifier
		ident = ParserConsume(self);

		LinkedListPushBack(&path,ident);


		// handle :: chain
		while(ParserIsToken(self, "::", 0))
		{
			ParserConsume(self); // consume ::

			if(!ParserIsIdentifier(self))
			{
				ParserFatal(self,ParserPeek(self,0),"expected an identifier after :: ",NULL,NULL,NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(false);
				break;
			}

			ident = ParserConsume(self);

			LinkedListPushBack(&path,ident);
		}

		typeType = C4MakeASTAggregateType(self->bump,path);
		dataType = AST_DATA_TYPE_AGGREGATE;
	}


	type = C4MakeASTType(self->bump,dataType,typeType);

	while(ParserIsToken(self,"*",0))
	{
		ParserConsume(self);

		typeType = C4MakeASTPointerType(self->bump,type);
		type     = C4MakeASTType(self->bump,AST_DATA_TYPE_POINTER,typeType);
	}


	while(ParserIsToken(self,"[",0))
	{
		ParserConsume(self);

		typeType = C4MakeASTArrayType(self->bump,type,ParserParseExpr(self,0));
		type     = C4MakeASTType(self->bump,AST_DATA_TYPE_ARRAY,typeType);

		ParserExpectSymbol(self,"]","expected ] after array size");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	return type;
}



struct ASTType *ParserParseType(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTType,baseType);
	ACHIOR_LABS_PTR_INIT(struct ASTType,argument);
	ACHIOR_LABS_PTR_INIT(struct ASTGenericType,generic);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);

    baseType = ParserParsePrimaryType(self); 
    // e.g. Box, i32, Foo

    if (ParserIsToken(self,"<",0))
    {
		LinkedListNew(&arguments,self->bump);

        if (! ParserIsToken(self,">",0))
        {
            do
            {
                argument = ParserParseType(self);
                LinkedListPushBack(&arguments,argument);
            }
            while (ParserIsToken(self,",",0));
        }

        ParserExpectSymbol(self,">","expected a > after generic");

		generic = C4MakeASTGenericType(self->bump,baseType,arguments);

        return C4MakeASTType(self->bump,AST_DATA_TYPE_GENERIC,generic);
    }

    return baseType;
}




struct ASTBlockStmt *ParserParseBlockStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,stmts);

	ACHIOR_LABS_PTR_INIT(struct ASTStatement,stmt);

	
	ParserExpectSymbol(self,":","expected a : ");
	ACHIOR_LABS_SYNCHRONIZE(false);

	LinkedListNew(&stmts,self->bump);


	while(true)
	{
		if(ParserAtEnd(self) || ParserIsSymbol(self,":",0))
		{
			break;
		}

		stmt = ParserParseStmt(self);

		if(ACHIOR_LABS_TRUE(self->panicMode))
		{
			ParserSynchronizeStmt(self);
			continue;
		}


		if( ACHIOR_LABS_NULL(stmt))
		{
			ACHIOR_LABS_PRINT("null stmt");
			continue;
			//break;
		}

		LinkedListPushBack(&stmts,stmt);
	}

	ParserExpectSymbol(self,":","expected : after block");
	ACHIOR_LABS_SYNCHRONIZE(false);

	return C4MakeASTBlockStmt(self->bump,stmts);
}


struct ASTStatement *ParserParseStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct Token,token);
	
	token = ParserPeek(self,0);

	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_KEYWORD_RETURN:
		{
			return ParserParseReturnStmt(self);
			break;
		}
		case TOKEN_KEYWORD_IF:
		{
			return ParserParseIfStmt(self);
			break;
		}
		case TOKEN_KEYWORD_WHILE:
		{
			return ParserParseWhileStmt(self);
			break;
		}
		case TOKEN_KEYWORD_LOOP:
		{
			return ParserParseLoopStmt(self);
			break;
		}
		case TOKEN_KEYWORD_CONTINUE:
		{
			return ParserParseContinueStmt(self);
			break;
		}
		case TOKEN_KEYWORD_BREAK:
		{
			return ParserParseBreakStmt(self);
			break;
		}
		case TOKEN_KEYWORD_MATCH:
		{
			//ParserParseMatchStmt(self);
			break;
		}
		case TOKEN_KEYWORD_CONST:
		{
			return ParserParseVariableDeclarationStmt(self);
			break;
		}
		default:
		{
			if( ParserIsType(self) || ParserParseTryVariableDecl(self) )
			{
				return ParserParseVariableDeclarationStmt(self);
			}
			else
			{
				return C4MakeASTStatement(self->bump,AST_STATEMENT_EXPRESSION,ParserParseExpr(self,0));
			}
			break;
		}
	}

	return NULL; // should never be reached!
}




struct ASTMatchStmt *ParserParseMatchStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ParserExpectKeyword(self,"match","expected match ");
	ACHIOR_LABS_SYNCHRONIZE(false);

	struct ASTExpression *expr = ParserParseExpr(self,0);

	ParserExpectSymbol(self,":","expected a : ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct LinkedList stmts;
	LinkedListNew(&stmts,self->bump);


	while(true)
	{
		if( ParserIsSymbol(self,":",0) || ParserAtEnd(self))
		{
			break;
		}

		//LinkedListPushBack(&stmts,stmt);
	}


	//struct ASTMatchStmt *stmt = C4MakeASTMatchStmt(self);
	return NULL;//astStmt;
}




struct ASTStatement *ParserParseContinueStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTContinueStmt,stmt);

	ParserExpectKeyword(self,"continue","expected continue ");
	ACHIOR_LABS_SYNCHRONIZE(false);

	stmt = C4MakeASTContinueStmt(self->bump);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_CONTINUE,stmt);
}





struct ASTStatement *ParserParseBreakStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	ACHIOR_LABS_PTR_INIT(struct ASTBreakStmt,stmt);

	ParserExpectKeyword(self,"break","expected break ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	stmt = C4MakeASTBreakStmt(self->bump);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_BREAK,stmt);
}





struct ASTStatement *ParserParseLoopStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTLoopStmt,stmt);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);

	ParserExpectKeyword(self,"loop","expected loop ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected a block after loop keyword",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	

	stmt = C4MakeASTLoopStmt(self->bump,block);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_LOOP,stmt);
}







struct ASTStatement *ParserParseWhileStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);
	ACHIOR_LABS_PTR_INIT(struct ASTWhileStmt,stmt);

	ParserExpectKeyword(self,"while","expected while ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	expr = ParserParseExpr(self,0);

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected a block after condition in while keyword",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	

	stmt = C4MakeASTWhileStmt(self->bump,expr,block);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_WHILE,stmt);
}






struct ASTIfElse *ParserParseIfElse(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);

	ParserExpectKeyword(self,"else","expected else ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected a block after else",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	return C4MakeASTIfElse(self->bump,block);
}




struct ASTIfElif *ParserParseIfElif(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);

	ParserExpectKeyword(self,"elif","expected elif ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	expr = ParserParseExpr(self,0);

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected a block after elif keyword",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	return C4MakeASTIfElif(self->bump,expr,block);
}


struct ASTStatement *ParserParseIfStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);
	ACHIOR_LABS_PTR_INIT(struct ASTBlockStmt,block);
	ACHIOR_LABS_PTR_INIT(struct ASTIfStmt,stmt);
	ACHIOR_LABS_PTR_INIT(struct ASTIfElif,elifBlock);
	ACHIOR_LABS_PTR_INIT(struct ASTIfElse,elseBlock);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,elifs);

	ParserExpectKeyword(self,"if","expected if ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	expr = ParserParseExpr(self,0);
	ACHIOR_LABS_SYNCHRONIZE(false);

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected a block after if keyword",NULL,NULL,NULL,NULL);puts("10");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	
	LinkedListNew(&elifs,self->bump);

	while(ParserIsToken(self,"elif",0))
	{
		elifBlock = ParserParseIfElif(self);
		LinkedListPushBack(&elifs,elifBlock);
	}

	if(ParserIsToken(self,"else",0))
	{
		elseBlock = ParserParseIfElse(self);
	}


	stmt = C4MakeASTIfStmt(self->bump,expr,block,elifs,elseBlock);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_IF,stmt);
}




struct ASTStatement *ParserParseReturnStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTReturnStmt,stmt);

	ParserExpectKeyword(self,"return","expected return ");
	ACHIOR_LABS_SYNCHRONIZE(false);	

	stmt = C4MakeASTReturnStmt(self->bump,ParserParseExpr(self,0));

	return C4MakeASTStatement(self->bump,AST_STATEMENT_RETURN,stmt);
}


bool ParserParseTryVariableDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	ACHIOR_LABS_VAR_INIT(u64,saved);
	ACHIOR_LABS_VAR_INIT(bool,panicMode);
	ACHIOR_LABS_VAR_INIT(bool,hasErrors);
	ACHIOR_LABS_VAR_INIT(bool,isVarDecl);
	ACHIOR_LABS_PTR_INIT(struct ASTType,type);

	panicMode = self->panicMode;
	hasErrors = self->hasErrors;
	saved     = self->index;
	type      = ParserParseType(self);

	if(ACHIOR_LABS_NULL(type))
	{
		self->panicMode = panicMode;
		self->hasErrors = hasErrors;

		return false;
	}

	isVarDecl       = ParserIsTokenKind(self, TOKEN_IDENT, 0) && !ParserIsToken(self, "(", 1); 
	self->panicMode = panicMode;
	self->hasErrors = hasErrors;
	self->index     = saved;

	return isVarDecl;
}





struct ASTVariableDecl *ParserParseVariableDeclaration(struct Parser *self,bool isConstant)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTType,type);
	ACHIOR_LABS_PTR_INIT(struct Token,ident);
	ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclInit,init);

	type = ParserParseType(self);

	if( ACHIOR_LABS_NULL(type))
	{
		ACHIOR_LABS_PRINT("null argument type");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,ParserPeek(self,0),"expected an identifier after type",NULL,NULL,NULL,NULL);
		ACHIOR_LABS_SYNCHRONIZE(false);
	}


	if(ParserIsToken(self,"=",0))
	{
		ParserExpectSymbol(self,"=","expected =");
		ACHIOR_LABS_SYNCHRONIZE(false);

		init = ParserParseVariableDeclInit(self,type);
	}


	return C4MakeASTVariableDecl(self->bump,isConstant,type,ident,init);
}




struct ASTStatement *ParserParseVariableDeclarationStmt(struct Parser *self)
{
	ACHIOR_LABS_VAR_INIT(bool,isConstant);
	ACHIOR_LABS_PTR_INIT(struct ASTVariableDecl,stmt);

	if(ParserIsToken(self,"const",0))
	{
		ParserExpectKeyword(self,"const","expected const");
		ACHIOR_LABS_SYNCHRONIZE(false);

		isConstant = true;
	}


	stmt = ParserParseVariableDeclaration(self,isConstant);

	return C4MakeASTStatement(self->bump,AST_STATEMENT_VAR_DECL,stmt);
}





struct ASTVariableDeclInit *ParserParseVariableDeclInit(struct Parser *self,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	if(ACHIOR_LABS_EQUAL(type->dataType,AST_DATA_TYPE_ARRAY))
	{
		return ParserParseVariableDeclArrayInit(self,type);
	}
	else
	{
		return ParserParseVariableDeclSingleInit(self,type);
	}
}


struct ASTVariableDeclInit *ParserParseVariableDeclSingleInit(struct Parser *self,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclSingleInit,init);

	init = C4MakeASTVariableDeclSingleInit(self->bump,ParserParseExpr(self,0));

	return C4MakeASTVariableDeclInit(self->bump,AST_VAR_DECL_INIT_SINGLE_INIT,init);
}


struct ASTVariableDeclInit *ParserParseVariableDeclArrayInit(struct Parser *self,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ACHIOR_LABS_PTR_INIT(struct ASTArrayType,arrayType);
	ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclInit,init);
	ACHIOR_LABS_PTR_INIT(struct ASTVariableDeclArrayInit,arrayInit);

	ACHIOR_LABS_STRUCT_INIT(struct LinkedList,elements);

	arrayType = type->type;

	LinkedListNew(&elements,self->bump);
	ParserExpectSymbol(self,"[","expected [ in array initialization");

	while(true)
	{
		init = ParserParseVariableDeclInit(self,arrayType->type);
		LinkedListPushBack(&elements,init);

		if(ParserIsToken(self,"]",0))
		{
			break;
		}

		ParserExpectSymbol(self,",","expected , in array initialization");
	}

	ParserExpectSymbol(self,"]","expected ] after array initialization");


	arrayInit = C4MakeASTVariableDeclArrayInit(self->bump,elements);

	return C4MakeASTVariableDeclInit(self->bump,AST_VAR_DECL_INIT_ARRAY_INIT,arrayInit);
}


enum ASTAssignmentOperator ParserGetAssignmentOperator(struct Parser *self,struct Token *token)
{
	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_ASSIGN:
		{
			return AST_ASSIGNMENT_OPERATOR;
			break;
		}
		case TOKEN_ASSIGN_ADD:
		{
			return AST_ASSIGNMENT_OPERATOR_ADD;
			break;
		}
		case TOKEN_ASSIGN_SUB:
		{
			return AST_ASSIGNMENT_OPERATOR_SUB;
			break;
		}
		case TOKEN_ASSIGN_MUL:
		{
			return AST_ASSIGNMENT_OPERATOR_MUL;
			break;
		}
		case TOKEN_ASSIGN_DIV:
		{
			return AST_ASSIGNMENT_OPERATOR_DIV;
			break;
		}
		case TOKEN_ASSIGN_MOD:
		{
			return AST_ASSIGNMENT_OPERATOR_MOD;
			break;
		}
		default:
		{
			return AST_ASSIGNMENT_OPERATOR_NONE;
			break;
		}
	}
}

bool ParserIs_assignment(struct Parser *self)
{
	return ParserIsToken(self,"=",0)  || 
		   ParserIsToken(self,"+=",0) || 
		   ParserIsToken(self,"-=",0) || 
		   ParserIsToken(self,"*=",0) || 
		   ParserIsToken(self,"/=",0) || 
		   ParserIsToken(self,"%%=",0);
}




bool ParserIsBinary(struct Parser *self)
{
	return ParserIsToken(self,"+",0)  || 
	       ParserIsToken(self,"-",0)  || 
		   ParserIsToken(self,"*",0)  || 
		   ParserIsToken(self,"/",0)  || 
		   ParserIsToken(self,"%%",0) || 
		   ParserIsToken(self,"<<",0)  || 
		   ParserIsToken(self,">>",0)  || 
		   ParserIsToken(self,"<",0)  || 
		   ParserIsToken(self,"<=",0) || 
		   ParserIsToken(self,">",0)  || 
		   ParserIsToken(self,">=",0) || 
		   ParserIsToken(self,"==",0) ||
		   ParserIsToken(self,"!=",0) ||  
		   ParserIsToken(self,"&&",0) || 
		   ParserIsToken(self,"||",0) || 
		   ParserIsToken(self,"&",0) || 
		   ParserIsToken(self,"|",0) || 
		   ParserIs_assignment(self)   || 
		   ParserIsToken(self,"as",0);
}




enum ASTBinaryOperator ParserGetBinaryOperator(struct Parser *self,struct Token *token)
{
	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_ADD:
		{
			return AST_BINARY_OPERATOR_ADD;
			break;
		}
		case TOKEN_SUB:
		{
			return AST_BINARY_OPERATOR_SUB;
			break;
		}
		case TOKEN_MUL:
		{
			return AST_BINARY_OPERATOR_MUL;
			break;
		}
		case TOKEN_DIV:
		{
			return AST_BINARY_OPERATOR_DIV;
			break;
		}
		case TOKEN_MOD:
		{
			return AST_BINARY_OPERATOR_MOD;
			break;
		}
		case TOKEN_LESS:
		{
			return AST_BINARY_OPERATOR_LESS;
			break;
		}
		case TOKEN_LESS_EQUAL:
		{
			return AST_BINARY_OPERATOR_LESS_EQUAL;
			break;
		}
		case TOKEN_GREATER:
		{
			return AST_BINARY_OPERATOR_GREATER;
			break;
		}
		case TOKEN_GREATER_EQUAL:
		{
			return AST_BINARY_OPERATOR_GREATER_EQUAL;
			break;
		}
		case TOKEN_EQUAL:
		{
			return AST_BINARY_OPERATOR_EQUAL;
			break;
		}
		case TOKEN_NOT_EQUAL:
		{
			return AST_BINARY_OPERATOR_NOT_EQUAL;
			break;
		}
		case TOKEN_AND:
		{
			return AST_BINARY_OPERATOR_AND;
			break;
		}
		case TOKEN_OR:
		{
			return AST_BINARY_OPERATOR_OR;
			break;
		}
		case TOKEN_BITWISE_AND:
		{
			return AST_BINARY_OPERATOR_BITWISE_AND;
			break;
		}
		case TOKEN_BITWISE_OR:
		{
			return AST_BINARY_OPERATOR_BITWISE_OR;
			break;
		}
		case TOKEN_LEFT_SHIFT:
		{
			return AST_BINARY_OPERATOR_BITWISE_LEFT_SHIFT;
			break;
		}
		case TOKEN_RIGHT_SHIFT:
		{
			return AST_BINARY_OPERATOR_BITWISE_RIGHT_SHIFT;
			break;
		}
		default:
		{
			return AST_BINARY_OPERATOR_NONE;
			break;
		}
	}
}



u64 ParserGetPrecedence(struct Parser *self)
{
	if(ParserIsToken(self,"as",0))
	{
		return AST_PRECEDENCE_AS;
	}
	else if(ParserIsToken(self,"+",0) || ParserIsToken(self,"-",0))
	{
		return AST_PRECEDENCE_ADD;
	}
	else if(ParserIsToken(self,"*",0) || ParserIsToken(self,"/",0) || ParserIsToken(self,"%%",0))
	{
		return AST_PRECEDENCE_MUL;
	}
	else if(ParserIsToken(self,">>",0) || ParserIsToken(self,"<<",0))
	{
		return AST_PRECEDENCE_SHIFT;
	}
	else if(ParserIsToken(self,"<",0) || ParserIsToken(self,"<=",0) || ParserIsToken(self,">",0) || ParserIsToken(self,">=",0))
	{
		return AST_PRECEDENCE_RELATIONAL;
	}
	else if(ParserIsToken(self,"&&",0))
	{
		return AST_PRECEDENCE_AND_LOGICAL;
	}
	else if(ParserIsToken(self,"||",0))
	{
		return AST_PRECEDENCE_OR_LOGICAL;
	}
	else if(ParserIsToken(self,"=",0))
	{
		return AST_PRECEDENCE_ASSIGN;
	}


	return AST_PRECEDENCE_NONE;
}





bool ParserIsUnary(struct Parser *self)
{
	return ParserIsToken(self,"-",0) || 
	       ParserIsToken(self,"~",0);
}


enum ASTUnaryOperator ParserGetUnaryOperator(struct Parser *self,struct Token *token)
{
	switch(TOKEN_GET_KIND(*token))
	{
		case TOKEN_SUB:
		{
			return AST_UNARY_OPERATOR_NEGATE;
			break;
		}
		case TOKEN_TILDE:
		{
			return AST_UNARY_OPERATOR_COMPLEMENT;
			break;
		}
		default:
		{
			return AST_UNARY_OPERATOR_NONE;
			break;
		}
	}
}

struct ASTExpression *ParserParseExpr(struct Parser *self,u64 min_precedence)
{
	ACHIOR_LABS_PTR_INIT(struct ASTExpression,lhs);
	ACHIOR_LABS_PTR_INIT(struct ASTExpression,rhs);
	ACHIOR_LABS_PTR_INIT(struct Token,token);

	ACHIOR_LABS_VAR_INIT(u64,precedence);
	ACHIOR_LABS_VAR_INIT(enum ASTCastOperator,op);

	lhs = ParserParseUnary(self);

	
	while ( ParserIsBinary(self) && ParserGetPrecedence(self) >= min_precedence)
	{
		precedence = ParserGetPrecedence(self);

		if(ParserIsToken(self,"as",0))
		{
			ACHIOR_LABS_PTR_INIT(struct ASTType,type);
			ACHIOR_LABS_PTR_INIT(struct ASTCastExpr,innerExpr);


			token = ParserConsume(self);
			op    = AST_CAST_OPERATOR_WIDEN;

			if(ParserIsToken(self,"<",0))
			{
				ParserConsume(self);
				token = ParserConsume(self); // add a check for if is identifier

				if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*token),"narrow") == 0)
				{
					op = AST_CAST_OPERATOR_NARROW;
				}
				else
				{
					op = AST_CAST_OPERATOR_NONE;
				}

				ParserExpectSymbol(self,">","expected > after as<modifier ");
				if(self->panicMode)
				{
					break;
				}
			}

			type      = ParserParseType(self);
			innerExpr = C4MakeASTCastExpr(self->bump,lhs,op,type);
			lhs       = C4MakeASTExpression(self->bump,AST_EXPRESSION_CAST,innerExpr);
		}
		else if(ParserIs_assignment(self))
		{
			ACHIOR_LABS_PTR_INIT(struct ASTAssignmentExpr,innerExpr);

			token     = ParserConsume(self);
			rhs       = ParserParseExpr(self,precedence);
			innerExpr = C4MakeASTAssignmentExpr(self->bump,lhs,ParserGetAssignmentOperator(self,token),rhs);
			lhs       = C4MakeASTExpression(self->bump,AST_EXPRESSION_ASSIGNMENT,innerExpr);
		}
		else
		{
			ACHIOR_LABS_PTR_INIT(struct ASTBinaryExpr,innerExpr);

			token     = ParserConsume(self);
			rhs       = ParserParseExpr(self,precedence + 1);
			innerExpr = C4MakeASTBinaryExpr(self->bump,lhs,ParserGetBinaryOperator(self,token),rhs);
			lhs       = C4MakeASTExpression(self->bump,AST_EXPRESSION_BINARY,innerExpr);
		}

	}

	return lhs;
}

struct ASTExpression *ParserParseUnary(struct Parser *self)
{
	if (ParserIsUnary(self))
	{
		ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);
		ACHIOR_LABS_PTR_INIT(struct ASTUnaryExpr,innerExpr);
		ACHIOR_LABS_VAR_INIT(enum ASTUnaryOperator,op);


		op        = ParserGetUnaryOperator(self,ParserConsume(self));
		expr      = ParserParseUnary(self);
		innerExpr = C4MakeASTUnaryExpr(self->bump,op,expr);
		
		return C4MakeASTExpression(self->bump,AST_EXPRESSION_UNARY,innerExpr);
	}

	return ParserParsePostfix(self);
}



struct ASTExpression *ParserParsePostfix(struct Parser *self)
{
	struct ASTExpression *expr = ParserParsePrimary(self);

	while(true)
	{
		if(ParserIsToken(self,"::",0))
		{
			ACHIOR_LABS_PTR_INIT(struct ASTPathExpr,innerExpr);
			ACHIOR_LABS_PTR_INIT(struct ASTVariableExpr,variableExpr);
			ACHIOR_LABS_VAR_INIT(bool,isFunction);
			
			ACHIOR_LABS_STRUCT_INIT(struct LinkedList,path);
			ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);

			variableExpr = expr->expr;
			
			LinkedListNew(&path,self->bump);
			LinkedListPushBack(&path,variableExpr->ident);

			while(ParserIsToken(self,"::",0))
			{
				ParserExpectSymbol(self,"::","expected ::");
				ACHIOR_LABS_SYNCHRONIZE(false);

				if(!ParserIsIdentifier(self))
				{
					break;
				}

				LinkedListPushBack(&path,ParserConsume(self));
			}

			isFunction = false;

			LinkedListNew(&arguments,self->bump);

			if(ParserIsToken(self,"(",0))
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				
				while(!ParserIsToken(self,")",0))
				{
					LinkedListPushBack(&arguments,ParserParseExpr(self,0));
					if(ParserIsToken(self,")",0))
					{
						break;
					}

					ParserExpectSymbol(self,",","expected a , after an argument in function call");
					ACHIOR_LABS_SYNCHRONIZE(false);
				}

				isFunction = true;
				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);	
			}

			innerExpr = C4MakeASTPathExpr(self->bump,path,isFunction,arguments);
			expr      = C4MakeASTExpression(self->bump, AST_EXPRESSION_PATH,innerExpr);
		}
		else if(ParserIsToken(self,"(",0))
		{
			ACHIOR_LABS_PTR_INIT(struct ASTFunctionCallExpr,innerExpr);
			ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);

			ParserExpectSymbol(self,"(","expected (");
			ACHIOR_LABS_SYNCHRONIZE(false);

			LinkedListNew(&arguments,self->bump);

			while(!ParserIsToken(self,")",0))
			{
				LinkedListPushBack(&arguments,ParserParseExpr(self,0));
				if(ParserIsToken(self,")",0))
				{
					break;
				}

				ParserExpectSymbol(self,",","expected a , after an argument in function call");
				ACHIOR_LABS_SYNCHRONIZE(false);
			}

			ParserExpectSymbol(self,")","expected )");
			ACHIOR_LABS_SYNCHRONIZE(false);
			
			innerExpr = C4MakeASTFunctionCallExpr(self->bump,expr,arguments);
			expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_FUNCTION_CALL,innerExpr);
		}
		else if(ParserIsToken(self,".",0))
		{
			ACHIOR_LABS_PTR_INIT(struct Token,member);
			ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);

			ParserExpectSymbol(self,".","expected .");
			ACHIOR_LABS_SYNCHRONIZE(false);

			// check if we have a function name,raise and error if not
			if( ParserIsIdentifier(self))
			{
				member = ParserConsume(self);
			}
			else
			{
				ParserFatal(self,ParserPeek(self,0),"expected an identifier after . ",NULL,NULL,NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(true);
			}

			if(ParserIsToken(self,"(",0))
			{
				ACHIOR_LABS_PTR_INIT(struct ASTMethodExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				LinkedListNew(&arguments,self->bump);

				while(!ParserIsToken(self,")",0))
				{
					LinkedListPushBack(&arguments,ParserParseExpr(self,0));
					if(ParserIsToken(self,")",0))
					{
						break;
					}

					ParserExpectSymbol(self,",","expected a , after an argument in function call");
					ACHIOR_LABS_SYNCHRONIZE(false);
				}

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);
				
				innerExpr = C4MakeASTMethodExpr(self->bump,expr,member,arguments);
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_METHOD,innerExpr);
			}
			else
			{
				ACHIOR_LABS_PTR_INIT(struct ASTStructAccessExpr,innerExpr);

				innerExpr = C4MakeASTStructAccessExpr(self->bump,expr,member); 
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_STRUCT_ACCESS,innerExpr);
			}
		}
		else if(ParserIsToken(self,"->",0))
		{
			ACHIOR_LABS_PTR_INIT(struct Token,member);

			ACHIOR_LABS_STRUCT_INIT(struct LinkedList,arguments);

			ParserExpectSymbol(self,"->","expected ->");
			ACHIOR_LABS_SYNCHRONIZE(false);

			// check if we have a function name,raise and error if not
			if( ParserIsIdentifier(self))
			{
				member = ParserConsume(self);
			}
			else
			{
				ParserFatal(self,ParserPeek(self,0),"expected an identifier after -> ",NULL,NULL,NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(true);
			}

			if(ParserIsToken(self,"(",0))
			{
				ACHIOR_LABS_PTR_INIT(struct ASTMethodExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				LinkedListNew(&arguments,self->bump);

				while(!ParserIsToken(self,")",0))
				{
					LinkedListPushBack(&arguments,ParserParseExpr(self,0));
					if(ParserIsToken(self,")",0))
					{
						break;
					}

					ParserExpectSymbol(self,",","expected a , after an argument in function call");
					ACHIOR_LABS_SYNCHRONIZE(false);
				}

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);
				
				innerExpr = C4MakeASTMethodExpr(self->bump,expr,member,arguments);
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_METHOD,innerExpr);
			}
			else
			{
				ACHIOR_LABS_PTR_INIT(struct ASTStructPointerAccessExpr,innerExpr);

				innerExpr = C4MakeASTStructPointerAccessExpr(self->bump,expr,member); 
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_STRUCT_POINTER_ACCESS,innerExpr);
			}
		}
		else if(ParserIsToken(self,"[",0))
		{
			ACHIOR_LABS_PTR_INIT(struct ASTSubscriptExpr,innerExpr);

			ParserExpectSymbol(self,"[","expected [");
			ACHIOR_LABS_SYNCHRONIZE(false);

			innerExpr = C4MakeASTSubscriptExpr(self->bump,expr,ParserParseExpr(self,0));

			ParserExpectSymbol(self,"]","expected ]");
			ACHIOR_LABS_SYNCHRONIZE(false);

			expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_SUBSCRIPT,innerExpr);
			
		}
		else if(ParserIsToken(self,"@",0))
		{
			ACHIOR_LABS_PTR_INIT(struct Token,ident);

			ParserExpectSymbol(self,"@","expected @");
			ACHIOR_LABS_SYNCHRONIZE(false);

			// check if we have a function name,raise and error if not
			if( ParserIsIdentifier(self))
			{
				ident = ParserConsume(self);
			}
			else
			{
				ParserFatal(self,ParserPeek(self,0),"expected an identifier after @ ",NULL,NULL,NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(true);
			}

			if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"read") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrReadExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrReadExpr(self->bump,expr);
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_READ,innerExpr);

			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"write") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrWriteExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrWriteExpr(self->bump,expr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_WRITE,innerExpr);
			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"offset") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrOffsetExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrOffsetExpr(self->bump,expr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_OFFSET,innerExpr);
			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"byte_offset") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrByteOffsetExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrByteOffsetExpr(self->bump,expr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_BYTE_OFFSET,innerExpr);
			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"advance") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrAdvanceExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrAdvanceExpr(self->bump,expr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_ADVANCE,innerExpr);
			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"diff") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTPtrDiffExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTPtrDiffExpr(self->bump,expr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				expr = C4MakeASTExpression(self->bump,AST_EXPRESSION_PTR_DIFF,innerExpr);
			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"as_ptr") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTAsPtrExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTAsPtrExpr(self->bump,expr);
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_AS_PTR,innerExpr);

			}
			else if(ACHIOR_LABS_STRCMP(TOKEN_GET_VALUE_DATA(*ident),"len") == 0)
			{
				ACHIOR_LABS_PTR_INIT(struct ASTLenExpr,innerExpr);

				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				innerExpr = C4MakeASTLenExpr(self->bump,expr);
				expr      = C4MakeASTExpression(self->bump,AST_EXPRESSION_LEN,innerExpr);
			}
			else
			{
				ParserFatal(self,ParserPeek(self,0),"unknown intrinsic  . ",NULL,NULL,NULL,NULL);
				ACHIOR_LABS_SYNCHRONIZE(false);
			}
		}
		else
		{
			break;
		}
	}

	return expr;
}

struct ASTExpression *ParserParsePrimary(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTExpression,expr);

	if( ParserIsTokenKind(self,TOKEN_LITERAL_INT,0))
	{
		expr = ParserParseLiteralI32(self);
	}
	else if( ParserIsTokenKind(self,TOKEN_LITERAL_CHARACTER,0))
	{
		expr = ParserParseLiteralCharacter(self);
	}
	else if( ParserIsTokenKind(self,TOKEN_LITERAL_STRING,0))
	{
		expr = ParserParseLiteralString(self);
	}
	else if( ParserIsIdentifier(self))
	{
		expr = ParserParseVariableExpr(self);
	}
	else if( ParserIsTokenKind(self,TOKEN_KEYWORD_SELF,0))
	{
		expr = ParserParseSelfExpr(self);
	}
	else if(ParserIsToken(self,"(",0))
	{
		//ParserExpectSymbol(self,"(","expected ( ");
		//expr = ParserParseExpr(self,0);
		expr = ParserParseParenExpr(self);
		ParserExpectSymbol(self,")","expected ) ");
	}
	else if(ParserIsToken(self,"&",0))
	{
		expr = ParserParseAddressOfExpr(self);
	}

	return expr;
}



struct ASTExpression *ParserParseAddressOfExpr(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTAddressOfExpr,expr);

	ParserExpectSymbol(self,"&","expected &");
	ACHIOR_LABS_SYNCHRONIZE(false);

	expr = C4MakeASTAddressOfExpr(self->bump,ParserParsePrimary(self));
	
	return C4MakeASTExpression(self->bump,AST_EXPRESSION_ADDRESS_OF,expr);
}


struct ASTExpression *ParserParseSelfExpr(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTVariableExpr,expr);

	expr = C4MakeASTVariableExpr(self->bump,ParserConsume(self));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_VARIABLE,expr);
}



struct ASTExpression *ParserParseParenExpr(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTParenExpr,expr);

	ParserExpectSymbol(self,"(","expected (");

	expr = C4MakeASTParenExpr(self->bump,ParserParseExpr(self,0));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_PAREN,expr);
}

struct ASTExpression *ParserParseVariableExpr(struct Parser *self)
{
	struct ASTVariableExpr *expr = C4MakeASTVariableExpr(self->bump,ParserConsume(self));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_VARIABLE,expr);
}




struct ASTExpression *ParserParseLiteralString(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTLiteralExpr,expr);

	expr = C4MakeASTLiteralExpr(self->bump,AST_LITERAL_STRING,ParserConsume(self));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_LITERAL,expr);
}



struct ASTExpression *ParserParseLiteralCharacter(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTLiteralExpr,expr);

	expr = C4MakeASTLiteralExpr(self->bump,AST_LITERAL_CHARACTER,ParserConsume(self));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_LITERAL,expr);
}



struct ASTExpression *ParserParseLiteralI32(struct Parser *self)
{
	ACHIOR_LABS_PTR_INIT(struct ASTLiteralExpr,expr);

	expr = C4MakeASTLiteralExpr(self->bump,AST_LITERAL_I32,ParserConsume(self));

	return C4MakeASTExpression(self->bump,AST_EXPRESSION_LITERAL,expr);
}


