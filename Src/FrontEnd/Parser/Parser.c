#include "Include/Parser.h"


bool ParserNew(
	struct Parser *self,
	char *file_name,
	struct TokenList tokens,
	struct BumpAllocator *bump
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->fileName   = file_name;
	self->tokens     = tokens;
	self->tokenSize  = tokens.size;
	self->index      = 0;
	self->bump       = bump;
	self->astProgram = NULL;
	self->panicMode  = false;
	self->hasErrors  = false;

	ParserParseProgram(self);

	puts("parsing done");
	return true;
}



enum TokenType ParserKeywordToToken(
	struct Parser *self,
	char *keyword
)
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
	else if (!strcmp(keyword,"union"))
	{
		return TOKEN_KEYWORD_UNION;
	}
	else if (!strcmp(keyword,"variant"))
	{
		return TOKEN_KEYWORD_VARIANT;
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

enum TokenType ParserSymbolToToken(
	struct Parser *self,
	char *keyword
)
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
	else if (!strcmp(keyword,"<="))
	{
		return TOKEN_LESS_EQUAL;
	}
	else if (!strcmp(keyword,">"))
	{
		return TOKEN_GREATER;
	}
	else if (!strcmp(keyword,">="))
	{
		return TOKEN_GREATER_EQUAL;
	}
	else if (!strcmp(keyword,"&&"))
	{
		return TOKEN_AND;
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
	else if (!strcmp(keyword,","))
	{
		return TOKEN_COMMA;
	}
	else if (!strcmp(keyword,"."))
	{
		return TOKEN_DOT;
	}
	else if (!strcmp(keyword,"@"))
	{
		return TOKEN_AT;
	}
	else if (!strcmp(keyword,"&"))
	{
		return TOKEN_BITWISE_AND;
	}
	else
	{
		return TOKEN_EOF;
	}
	
}



enum TokenType ParserStringToToken(
	struct Parser *self,
	char *string
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return TOKEN_EOF;
	}

	return ParserSymbolToToken(self,string);
}


struct Token ParserPeek(
	struct Parser *self,
	i64 lookAhead
)
{
	if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_GREATER_EQUAL(self->index + lookAhead,self->tokenSize))
	{
		return (struct Token){
			.type = TOKEN_EOF,
		};
	}

	return self->tokens.data[self->index + lookAhead];
}


struct Token ParserConsume(
	struct Parser *self
)
{
	if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_GREATER_EQUAL(self->index,self->tokenSize))
	{
		return (struct Token){
			.type = TOKEN_EOF,
		};
	}

	return self->tokens.data[self->index++];
}



bool ParserIsTokenType(
	struct Parser *self,
	enum TokenType type,
	i64 lookAhead
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	struct Token token = ParserPeek(self,lookAhead);
	return ACHIOR_LABS_EQUAL(token.type,type);
}




bool ParserIsToken(
	struct Parser *self,
	char *string,
	i64 lookAhead
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenType(self,ParserSymbolToToken(self,string),lookAhead) || ParserIsTokenType(self,ParserKeywordToToken(self,string),lookAhead);
}



void ParserFatal(
	struct Parser *self,
	char *string
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	self->panicMode  = true;
	self->hasErrors = true;
	ACHIOR_LABS_PRINT(string);
}




void ParserSynchronizeDecl(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

	while( !ParserAtEnd(self))
	{
		struct Token token = ParserPeek(self,0);

		switch(token.type)
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




void ParserSynchronizeStmt(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}


	while( !ParserAtEnd(self))
	{
		struct Token token = ParserPeek(self,0);

		switch(token.type)
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

bool ParserIsType(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	struct Token token = ParserPeek(self,0);

	switch(token.type)
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




bool ParserIsSymbol(
	struct Parser *self,
	char *symbol,
	i64 lookAhead
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenType(self,ParserSymbolToToken(self,symbol),lookAhead);
}



bool ParserExpectSymbol(
	struct Parser *self,
	char *symbol,
	char *error_message
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	bool status = false;
	if( ParserIsTokenType(self,ParserSymbolToToken(self,symbol),0))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,error_message);
	}

	ParserConsume(self);

	return status;

}



bool ParserIsKeyword(
	struct Parser *self,
	char *keyword,
	i64 lookAhead
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenType(self,ParserKeywordToToken(self,keyword),lookAhead);
}



bool ParserExpectKeyword(
	struct Parser *self,
	char *keyword,
	char *error_message
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	bool status = false;
	if( ParserIsTokenType(self,ParserKeywordToToken(self,keyword),0))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,error_message);
	}

	ParserConsume(self);

	return status;
}





bool ParserIsStringLiteral(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenType(self,TOKEN_LITERAL_STRING,0);
}


bool ParserExpectString_literal(
	struct Parser *self,
	char *literal,
	char *error_message
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	bool status = false;
	struct String str = ParserPeek(self,0).value;
	if( StringEqualCstr(&str,literal))
	{
		status = true;
	}
	else
	{
		ParserFatal(self,error_message);
	}

	ParserConsume(self);

	return status;
}



bool ParserIsIdentifier(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ParserIsTokenType(self,TOKEN_IDENT,0);
}




bool ParserAtEnd(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return ACHIOR_LABS_GREATER_EQUAL(self->index,self->tokenSize);
}

struct ASTProgram *ParserParseProgram(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
 

	LinkedListNew(&self->decls,self->bump);
	while( !ParserAtEnd(self))
	{
		struct ASTDeclaration *ast_decl = ParserParseDecl(self);

		if(ACHIOR_LABS_TRUE(self->panicMode))
		{
			ParserSynchronizeDecl(self);
			continue;
		}

		if( ACHIOR_LABS_NULL(ast_decl))
		{
			continue;
		}


		LinkedListPushBack(&self->decls,ast_decl);
	}



	struct ASTProgram *astProgram = ParserMakeProgram(self,self->decls);
	self->astProgram = astProgram;

	return astProgram;
}

#define ACHIOR_LABS_SYNCHRONIZE(is_decl) do                                  \
								{                                            \
									if(self->panicMode)                     \
									{                                        \
										return NULL;                         \
									}                                        \
								}while(0);                                   \







struct ASTDeclaration *ParserParseDecl(
	struct Parser *self
)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	struct Token token                 = ParserPeek(self,0);
	enum ASTDeclarationType ast_type   = AST_DECLARATION_NONE;
	void *ast_decl_val                 = NULL;

	switch(token.type)
	{
		case TOKEN_KEYWORD_PUB:
		{
			ParserConsume(self);
			if(ParserIsToken(self,"fn",0))
			{
				struct String tmp;
				ast_type     = AST_DECLARATION_FUNCTION;
				ast_decl_val = (void *)ParserParseFunctionDecl(self,true,false,false,false,tmp,false,tmp);	
			}
			else
			{
				ParserFatal(self,"invalid use of pub modifier");
				ACHIOR_LABS_SYNCHRONIZE(true);
			}
			break;
		}
		case TOKEN_KEYWORD_FN:
		{
			struct String tmp;
			ast_type     = AST_DECLARATION_FUNCTION;
			ast_decl_val = (void *)ParserParseFunctionDecl(self,false,true,false,false,tmp,false,tmp);
			break;
		}
		case TOKEN_KEYWORD_FOREIGN:
		{
			ParserParseForeignDecl(self);
			return NULL;
			break;
		}
		case TOKEN_KEYWORD_STRUCT:
		{
			struct String tmp;
			ast_type     = AST_DECLARATION_STRUCT;
			ast_decl_val = (void *)ParserParseStructDecl(self);
			break;
		}
		case TOKEN_KEYWORD_UNION:
		{
			struct String tmp;
			ast_type     = AST_DECLARATION_UNION;
			ast_decl_val = (void *)ParserParseStructDecl(self);
			break;
		}
		case TOKEN_KEYWORD_IMPL:
		{
			struct String tmp;
			ast_type     = AST_DECLARATION_IMPL;
			ast_decl_val = (void *)ParserParseImplDecl(self);
			break;
		}
		case TOKEN_KEYWORD_SUM:
		{
			struct String tmp;
			ast_type     = AST_DECLARATION_SUM;
			ast_decl_val = (void *)ParserParseSumDecl(self);
			break;
		}
		case TOKEN_EOF:
		{
			ACHIOR_LABS_PRINT("eof");
			ParserConsume(self);
			break;
		}
		default:
		{
			ParserConsume(self);
			break;
		}
	}

	struct ASTDeclaration *ast_decl = ParserMakeDeclaration(self,ast_type,ast_decl_val);
	return ast_decl;
}





struct ASTStructDecl *ParserParseStructDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	// consume struct keyword
	ParserExpectKeyword(self,"struct","expected struct keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct Token ident;

	// check if we have a struct name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after struct");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct LinkedList properties;
	LinkedListNew(&properties,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		struct ASTStructProperty *ASTStructProperty = ParserParseStructProperty(self);
		if( ACHIOR_LABS_NULL(ASTStructProperty))
		{
			continue;
		}

		LinkedListPushBack(&properties,ASTStructProperty);
		if( ParserIsSymbol(self,":",0))
		{
			break;
		}
	}

	ParserExpectSymbol(self,":","expected )");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct ASTStructDecl *ast_struct_decl = ParserMakeStructDecl(self,ident,properties);
	return ast_struct_decl;
}





struct ASTStructProperty *ParserParseStructProperty(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	struct ASTType *ast_type = ParserParseType(self);
	if( ACHIOR_LABS_NULL(ast_type))
	{
		ACHIOR_LABS_PRINT("null argument type");
	}

	struct Token ident;


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after fn");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	struct ASTStructProperty *ASTStructProperty = ParserMakeStructProperty(self,ast_type,ident);
	return ASTStructProperty;
}






struct ASTImplDecl *ParserParseImplDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	// consume struct keyword
	ParserExpectKeyword(self,"impl","expected impl keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct Token ident;

	// check if we have a struct name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after impl");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct LinkedList methods;
	LinkedListNew(&methods,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		struct String tmp;
		struct ASTFunctionDecl *method = ParserParseImplMethod(self,ident,false,true,false,false,tmp,false,tmp);
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

	struct ASTImplDecl *decl = ParserMakeImplDecl(self,ident,methods);
	return decl;
}





struct ASTFunctionDecl *ParserParseImplMethod(struct Parser *self,struct Token structIdent,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	if(ACHIOR_LABS_TRUE(is_pub) && ACHIOR_LABS_TRUE(is_foreign))
	{
		ParserFatal(self,"function cannot be both foreign and public");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume fn keyword
	ParserExpectKeyword(self,"fn","expected fn");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct Token ident;

	// check if we have a function name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after fn");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	struct String name;
	StringNew(&name,10,self->bump);
	StringPushBack(&name,ident.value.data);
	ident.value.size = 0;
	StringPushBack(&ident.value,"__C4C");
	StringPushBack(&ident.value,structIdent.value.data);
	StringPushBack(&ident.value,name.data);


	// consume the open paren
	ParserExpectSymbol(self,"(","expected (");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct LinkedList arguments;
	LinkedListNew(&arguments,self->bump);

	struct String tmp;
	StringNew(&tmp,10,self->bump);
	StringPushBack(&tmp,"self");
	struct Token selfIdent               = (struct Token){.type = TOKEN_IDENT,.value = tmp};
	struct ASTType *astType              = ParserMakeType(self,AST_DATA_TYPE_AGGREGATE,ParserMakeAggregateType(self,structIdent));
	struct ASTPointerType *pointerType   = ParserMakePointerType(self,astType);
	astType                              = ParserMakeType(self,AST_DATA_TYPE_POINTER,pointerType);
	struct ASTFunctionArgument *argument = ParserMakeFunctionArgument(self,astType,selfIdent);
	LinkedListPushBack(&arguments,argument);

	while( !ParserIsToken(self,")",0))
	{
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

	struct ASTType *return_type;

	if(ParserIsToken(self,"->",0))
	{
		ParserExpectSymbol(self,"->","expected ->");
		ACHIOR_LABS_SYNCHRONIZE(true);
		return_type = ParserParseType(self);
	}
	else
	{
		return_type = ParserMakeType(self,AST_DATA_TYPE_VOID,NULL);
	}
	

	struct ASTBlockStmt *block = NULL;

	if(ACHIOR_LABS_FALSE(is_foreign))
	{

		if( ParserIsSymbol(self,":",0))
		{
			block = ParserParseBlockStmt(self);
		}
		else
		{
			ParserFatal(self,"error : function lacks a valid block");
			ACHIOR_LABS_SYNCHRONIZE(true);
		}
	}


	struct ASTFunctionAttributes *attributes = ParserMakeFunctionAttributes(self,is_pub,is_static,is_naked,is_foreign,foreign_abi,has_link_name,link_name);
	
	struct ASTFunctionDecl *ast_fn = ParserMakeFunctionDecl(self,return_type,ident,arguments,block,attributes);
	return ast_fn;
}








struct ASTSumDecl *ParserParseSumDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	// consume sum keyword
	ParserExpectKeyword(self,"sum","expected sum keyword");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct Token ident;

	// check if we have a sum name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after sum");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the :
	ParserExpectSymbol(self,":","expected :");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct LinkedList variants;
	LinkedListNew(&variants,self->bump);
	

	while( !ParserIsToken(self,":",0))
	{
		struct ASTSumVariant *variant = ParserParseSumVariant(self);
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

	struct ASTSumDecl *decl = ParserMakeSumDecl(self,ident,variants);
	return decl;
}





struct ASTSumVariant *ParserParseSumVariant(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	

	struct Token ident;

	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier in sum type field");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	enum ASTSumVariantKind kind = AST_SUM_VARIANT_NONE;
	struct LinkedList fields;
	LinkedListNew(&fields,self->bump);

	if( ParserIsSymbol(self,"(",0))
	{
		// consume the (
		ParserExpectSymbol(self,"(","expected (");

		

		struct ASTType *type = ParserParseType(self);
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

	struct ASTSumVariant *variant = ParserMakeSumVariant(self,ident,kind,fields);
	return variant;
}



void *ParserParseForeignDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	// consume foreign keyword
	ParserExpectKeyword(self,"foreign","expected foreign");
	
	struct String foreign_abi;
	if(ParserIsStringLiteral(self))
	{
		foreign_abi = ParserConsume(self).value;
	}


	ParserExpectSymbol(self,":","expected a : after foreign_abi ");
	ACHIOR_LABS_SYNCHRONIZE(true);

	while(! ParserIsToken(self,":",0))
	{
		struct ASTFunctionDecl *ast_fn = ParserParseFunctionDecl(self,false,false,false,true,foreign_abi,false,(struct String){});
		struct ASTDeclaration *ast_decl = ParserMakeDeclaration(self,AST_DECLARATION_FUNCTION,ast_fn);
		LinkedListPushBack(&self->decls,ast_decl);
		
	}

	ParserExpectSymbol(self,":","expected : after foreign");
	ACHIOR_LABS_SYNCHRONIZE(true);

	return NULL;
}

struct ASTFunctionDecl *ParserParseFunctionDecl(struct Parser *self,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	if(ACHIOR_LABS_TRUE(is_pub) && ACHIOR_LABS_TRUE(is_foreign))
	{
		ParserFatal(self,"function cannot be both foreign and public");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume fn keyword
	ParserExpectKeyword(self,"fn","expected fn");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct Token ident;

	// check if we have a function name,raise and error if not
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after fn");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	// consume the open paren
	ParserExpectSymbol(self,"(","expected (");
	ACHIOR_LABS_SYNCHRONIZE(true);

	struct LinkedList arguments;
	LinkedListNew(&arguments,self->bump);
	

	while( !ParserIsToken(self,")",0))
	{
		struct ASTFunctionArgument *argument = ParserParseFunctionArgument(self);
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

	struct ASTType *return_type;

	if(ParserIsToken(self,"->",0))
	{
		ParserExpectSymbol(self,"->","expected ->");
		ACHIOR_LABS_SYNCHRONIZE(true);
		return_type = ParserParseType(self);
	}
	else
	{
		return_type = ParserMakeType(self,AST_DATA_TYPE_VOID,NULL);
	}
	

	struct ASTBlockStmt *block = NULL;

	if(ACHIOR_LABS_FALSE(is_foreign))
	{

		if( ParserIsSymbol(self,":",0))
		{
			block = ParserParseBlockStmt(self);
		}
		else
		{
			ParserFatal(self,"error : function lacks a valid block");
			ACHIOR_LABS_SYNCHRONIZE(true);
		}
	}


	struct ASTFunctionAttributes *attributes = ParserMakeFunctionAttributes(self,is_pub,is_static,is_naked,is_foreign,foreign_abi,has_link_name,link_name);
	
	struct ASTFunctionDecl *ast_fn = ParserMakeFunctionDecl(self,return_type,ident,arguments,block,attributes);
	return ast_fn;
}



struct ASTFunctionArgument *ParserParseFunctionArgument(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	struct ASTType *ast_type = ParserParseType(self);
	if( ACHIOR_LABS_NULL(ast_type))
	{
		ACHIOR_LABS_PRINT("null argument type");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	struct Token ident;


	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after fn");
		ACHIOR_LABS_SYNCHRONIZE(true);
	}

	struct ASTFunctionArgument *argument = ParserMakeFunctionArgument(self,ast_type,ident);
	return argument;

}


enum ASTDataType ParserGetDataType(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return AST_DATA_TYPE_NONE;
	}

	enum ASTDataType data_type = AST_DATA_TYPE_NONE;

	if( ParserIsToken(self,"void",0))
	{
		data_type = AST_DATA_TYPE_VOID;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"char",0))
	{
		data_type = AST_DATA_TYPE_CHAR;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i8",0))
	{
		data_type = AST_DATA_TYPE_I8;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i16",0))
	{
		data_type = AST_DATA_TYPE_I16;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i32",0))
	{
		data_type = AST_DATA_TYPE_I32;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"i64",0))
	{
		data_type = AST_DATA_TYPE_I64;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u8",0))
	{
		data_type = AST_DATA_TYPE_U8;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u16",0))
	{
		data_type = AST_DATA_TYPE_U16;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u32",0))
	{
		data_type = AST_DATA_TYPE_U32;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"u64",0))
	{
		data_type = AST_DATA_TYPE_U64;
		ParserConsume(self);
	}
	else if( ParserIsToken(self,"str",0))
	{
		data_type = AST_DATA_TYPE_STRING;
		ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"unsupported data type : get_data_type");
		data_type = AST_DATA_TYPE_NONE;
		ParserConsume(self);
	}

	return data_type;
}

struct ASTType *ParserParseType(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	
	void *ast_type_type       = NULL;

	enum ASTDataType data_type;
	if( ParserIsType(self))
	{
		data_type = ParserGetDataType(self);
		if(ACHIOR_LABS_EQUAL(data_type,AST_DATA_TYPE_NONE))
		{
			self->panicMode = true;
			ACHIOR_LABS_SYNCHRONIZE(false);
		}
	}
	else if(ParserIsIdentifier(self))
	{
		data_type     = AST_DATA_TYPE_AGGREGATE;
		ast_type_type = ParserMakeAggregateType(self,ParserConsume(self));
	}
	else
	{
		ParserFatal(self,"parse-type => unsupported data type");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}


	struct ASTType *astType = ParserMakeType(self,data_type,ast_type_type);

	while(ParserIsToken(self,"*",0))
	{
		ParserConsume(self);

		ast_type_type = ParserMakePointerType(self,astType);
		astType      = ParserMakeType(self,AST_DATA_TYPE_POINTER,ast_type_type);
	}


	while(ParserIsToken(self,"[",0))
	{
		ParserConsume(self);

		ast_type_type = ParserMakeArrayType(self,astType,ParserParseExpr(self,0));
		astType       = ParserMakeType(self,AST_DATA_TYPE_ARRAY,ast_type_type);

		ParserExpectSymbol(self,"]","expected ] after array size");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	return astType;
}








struct ASTBlockStmt *ParserParseBlockStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	
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

		struct ASTStatement *stmt = ParserParseStmt(self);

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


	struct ASTBlockStmt *ast_block = ParserMakeBlockStmt(self,stmts);
	return ast_block;
}


struct ASTStatement *ParserParseStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	
	enum ASTStatementType ast_type = AST_STATEMENT_NONE;
	void *astStmt_val               = NULL;
	struct Token token               = ParserPeek(self,0);

	switch(token.type)
	{
		case TOKEN_KEYWORD_RETURN:
		{
			ast_type     = AST_STATEMENT_RETURN;
			astStmt_val = (void *)ParserParseReturnStmt(self);
			break;
		}
		case TOKEN_KEYWORD_IF:
		{
			ast_type     = AST_STATEMENT_IF;
			astStmt_val = (void *)ParserParseIfStmt(self);
			break;
		}
		case TOKEN_KEYWORD_WHILE:
		{
			ast_type     = AST_STATEMENT_WHILE;
			astStmt_val = (void *)ParserParseWhileStmt(self);
			break;
		}
		case TOKEN_KEYWORD_LOOP:
		{
			ast_type     = AST_STATEMENT_LOOP;
			astStmt_val = (void *)ParserParseLoopStmt(self);
			break;
		}
		case TOKEN_KEYWORD_CONTINUE:
		{
			ast_type     = AST_STATEMENT_CONTINUE;
			astStmt_val = (void *)ParserParseContinueStmt(self);
			break;
		}
		case TOKEN_KEYWORD_BREAK:
		{
			ast_type     = AST_STATEMENT_BREAK;
			astStmt_val = (void *)ParserParseBreakStmt(self);
			break;
		}
		case TOKEN_KEYWORD_MATCH:
		{
			ast_type     = AST_STATEMENT_MATCH;
			astStmt_val = (void *)ParserParseMatchStmt(self);
			break;
		}
		default:
		{
			if( ParserIsType(self) || ParserParseTryVariableDecl(self) )
			{
				ast_type     = AST_STATEMENT_VAR_DECL;
				astStmt_val = (void *)ParserParseVariableDecl(self);
			}
			else
			{
				ast_type     = AST_STATEMENT_EXPRESSION;
				astStmt_val = (void *)ParserParseExpr(self,0);

			}
			break;
		}
	}

	if(ACHIOR_LABS_NULL(astStmt_val))
	{
		ParserFatal(self," unknown statement ");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}


	struct ASTStatement *astStmt = ParserMakeStatement(self,ast_type,astStmt_val);
	return astStmt;
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


	//struct ASTMatchStmt *astStmt = ParserMakeMatchStmt(self);
	return NULL;//astStmt;
}




struct ASTContinueStmt *ParserParseContinueStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ParserExpectKeyword(self,"continue","expected continue ");
	ACHIOR_LABS_SYNCHRONIZE(false);

	struct ASTContinueStmt *astStmt = ParserMakeContinueStmt(self);
	return astStmt;
}





struct ASTBreakStmt *ParserParseBreakStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}
	

	ParserExpectKeyword(self,"break","expected break ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTBreakStmt *astStmt = ParserMakeBreakStmt(self);
	return astStmt;
}





struct ASTLoopStmt *ParserParseLoopStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ParserExpectKeyword(self,"loop","expected loop ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTBlockStmt *block      = NULL;

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,"expected a block ':' after loop");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	

	struct ASTLoopStmt *astStmt = ParserMakeLoopStmt(self,block);
	return astStmt;
}







struct ASTWhileStmt *ParserParseWhileStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ParserExpectKeyword(self,"while","expected while ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTExpression *expr       = ParserParseExpr(self,0);
	struct ASTBlockStmt *block      = NULL;

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,"expected a block ':' after while");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	

	struct ASTWhileStmt *astStmt = ParserMakeWhileStmt(self,expr,block);
	return astStmt;
}






struct ASTIfElse *ParserParseIfElse(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	ParserExpectKeyword(self,"else","expected else ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTBlockStmt *block = NULL;

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,"expected a block ':' after loop");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	struct ASTIfElse *ast_else = ParserMakeIfElse(self,block);
	return ast_else;
}




struct ASTIfElif *ParserParseIfElif(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	ParserExpectKeyword(self,"elif","expected elif ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTExpression *expr  = ParserParseExpr(self,0);
	struct ASTBlockStmt *block = NULL;

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,"expected a block ':' after loop");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	struct ASTIfElif *ast_elif = ParserMakeIfElif(self,expr,block);
	return ast_elif;
}


struct ASTIfStmt *ParserParseIfStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}


	ParserExpectKeyword(self,"if","expected if ");
	ACHIOR_LABS_SYNCHRONIZE(false);


	struct ASTExpression *expr       = ParserParseExpr(self,0);
	struct ASTBlockStmt *block      = NULL;

	if(ParserIsToken(self,":",0))
	{
		block = ParserParseBlockStmt(self);
	}
	else
	{
		ParserFatal(self,"expected a block ':' after loop");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}
	
	struct LinkedList elifList;
	LinkedListNew(&elifList,self->bump);

	while(ParserIsToken(self,"elif",0))
	{
		struct ASTIfElif *ast_elif = ParserParseIfElif(self);
		LinkedListPushBack(&elifList,ast_elif);
	}


	struct ASTIfElse *ast_else = NULL;
	if(ParserIsToken(self,"else",0))
	{
		ast_else = ParserParseIfElse(self);
	}


	struct ASTIfStmt *astStmt = ParserMakeIfStmt(self,expr,block,elifList,ast_else);

	return astStmt;
}




struct ASTReturnStmt *ParserParseReturnStmt(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	ParserExpectKeyword(self,"return","expected return ");
	ACHIOR_LABS_SYNCHRONIZE(false);	

	struct ASTExpression *expr      = ParserParseExpr(self,0);
	struct ASTReturnStmt *astStmt = ParserMakeReturnStmt(self,expr);
	return astStmt;
}


bool ParserParseTryVariableDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	u64 index      = self->index;
	u64 lookAhead = 0;

	if(ParserIsIdentifier(self))
	{
		lookAhead++;
		while(ParserIsToken(self,"*",lookAhead))
		{
			lookAhead++;
		}

		while(ParserIsToken(self,"[",lookAhead))
		{
			lookAhead++;
			while(! ParserIsToken(self,"]",lookAhead) && !ACHIOR_LABS_EQUAL(index,self->index))
			{
				lookAhead++;
			}

			if(ACHIOR_LABS_EQUAL(index,self->index))
			{
				break;
			}
		}

		if(ParserIsTokenType(self,TOKEN_IDENT,lookAhead))
		{
			return true;
		}
	}
	
	
	return false;
}


struct ASTVariableDecl *ParserParseVariableDecl(struct Parser *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	struct ASTType *ast_type = ParserParseType(self);
	if( ACHIOR_LABS_NULL(ast_type))
	{
		ACHIOR_LABS_PRINT("null argument type");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	struct Token ident;
	if( ParserIsIdentifier(self))
	{
		ident = ParserConsume(self);
	}
	else
	{
		ParserFatal(self,"expected an identifier after type");
		ACHIOR_LABS_SYNCHRONIZE(false);
	}

	struct ASTVariableDeclInit *init = NULL;
	if(ParserIsToken(self,"=",0))
	{
		ParserExpectSymbol(self,"=","expected =");
		ACHIOR_LABS_SYNCHRONIZE(false);

		init = ParserParseVariableDeclInit(self,ast_type);
	}


	struct ASTVariableDecl *astStmt = ParserMakeVariableDecl(self,ast_type,ident,init);
	return astStmt;
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

	struct ASTVariableDeclSingleInit *single_init = ParserMakeVariableDeclSingleInit(self,ParserParseExpr(self,0));
	struct ASTVariableDeclInit *init               = ParserMakeVariableDeclInit(self,AST_VAR_DECL_INIT_SINGLE_INIT,single_init);

	return init;
}


struct ASTVariableDeclInit *ParserParseVariableDeclArrayInit(struct Parser *self,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return NULL;
	}

	struct ASTArrayType *astArrayType = (struct ASTArrayType *)type->type;

	struct LinkedList elements;
	LinkedListNew(&elements,self->bump);

	ParserExpectSymbol(self,"[","expected [ in array initialization");

	while(true)
	{
		struct ASTVariableDeclInit *ast_var_init = ParserParseVariableDeclInit(self,astArrayType->type);
		LinkedListPushBack(&elements,ast_var_init);

		if(ParserIsToken(self,"]",0))
		{
			break;
		}

		ParserExpectSymbol(self,",","expected , in array initialization");
	}

	ParserExpectSymbol(self,"]","expected ] after array initialization");


	struct ASTVariableDeclArrayInit *array_init = ParserMakeVariableDeclArrayInit(self,elements);
	struct ASTVariableDeclInit *init             = ParserMakeVariableDeclInit(self,AST_VAR_DECL_INIT_ARRAY_INIT,array_init);

	return init;
}


enum ASTAssignmentOperator ParserGetAssignmentOperator(struct Parser *self,struct Token token)
{
	switch(token.type)
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
		   ParserIsToken(self,"<",0)  || 
		   ParserIsToken(self,"<=",0) || 
		   ParserIsToken(self,">",0)  || 
		   ParserIsToken(self,">=",0) || 
		   ParserIsToken(self,"&&",0) || 
		   ParserIsToken(self,"||",0) || 
		   ParserIs_assignment(self)   || 
		   ParserIsToken(self,"as",0);
}




enum ASTBinaryOperator ParserGetBinaryOperator(struct Parser *self,struct Token token)
{
	switch(token.type)
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


enum ASTUnaryOperator ParserGetUnaryOperator(struct Parser *self,struct Token token)
{
	switch(token.type)
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
	struct ASTExpression *ast_lhs = ParserParseUnary(self);
	

	while ( ParserIsBinary(self) && ParserGetPrecedence(self) >= min_precedence)
	{
		u64 precedence = ParserGetPrecedence(self);
		if(ParserIsToken(self,"as",0))
		{
			struct Token token        = ParserConsume(self);
			enum ASTCastOperator op = AST_CAST_OPERATOR_WIDEN;

			if(ParserIsToken(self,"<",0))
			{
				ParserConsume(self);
				token = ParserConsume(self); // add a check for if is identifier

				if(ACHIOR_LABS_STRCMP(token.value.data,"narrow") == 0)
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

			struct ASTType *ast_type           = ParserParseType(self);
			struct ASTCastExpr *ASTCastExpr = ParserMakeCastExpr(self,ast_lhs,op,ast_type);
			struct ASTExpression *astExpr     = ParserMakeExpression(self,AST_EXPRESSION_CAST,ASTCastExpr);
			ast_lhs                             = astExpr;
		}
		else if(ParserIs_assignment(self))
		{
			struct Token token                              = ParserConsume(self);
			struct ASTExpression *ast_rhs                  = ParserParseExpr(self,precedence);
			struct ASTAssignmentExpr *astAssignmentExpr = ParserMakeAssignmentExpr(self,ast_lhs,ParserGetAssignmentOperator(self,token),ast_rhs);
			struct ASTExpression *astExpr                 = ParserMakeExpression(self,AST_EXPRESSION_ASSIGNMENT,astAssignmentExpr);
			ast_lhs                                         = astExpr;
		}
		else
		{
			struct Token token                      = ParserConsume(self);
			struct ASTExpression *ast_rhs          = ParserParseExpr(self,precedence + 1);
			struct ASTBinaryExpr *ast_binaryExpr = ParserMakeBinaryExpr(self,ast_lhs,ParserGetBinaryOperator(self,token),ast_rhs);
			struct ASTExpression *astExpr         = ParserMakeExpression(self,AST_EXPRESSION_BINARY,ast_binaryExpr);
			ast_lhs                                 = astExpr;
		}

	}

	return ast_lhs;
}

struct ASTExpression *ParserParseUnary(struct Parser *self)
{
	if (ParserIsUnary(self))
	{
		enum ASTUnaryOperator op       = ParserGetUnaryOperator(self,ParserConsume(self));
		struct ASTExpression *expr1     = ParserParseUnary(self);
		struct ASTUnaryExpr *astExpr2 = ParserMakeUnaryExpr(self,op,expr1);
		struct ASTExpression *astExpr  = ParserMakeExpression(self,AST_EXPRESSION_UNARY,astExpr2);

		return astExpr;
	}

	return ParserParsePostfix(self);
}



struct ASTExpression *ParserParsePostfix(struct Parser *self)
{
	struct ASTExpression *astExpr = ParserParsePrimary(self);

	while(true)
	{
		if(ParserIsToken(self,"(",0))
		{
			ParserExpectSymbol(self,"(","expected (");
			ACHIOR_LABS_SYNCHRONIZE(false);

			struct LinkedList LinkedList;
			LinkedListNew(&LinkedList,self->bump);

			while(!ParserIsToken(self,")",0))
			{
				LinkedListPushBack(&LinkedList,ParserParseExpr(self,0));
				if(ParserIsToken(self,")",0))
				{
					break;
				}

				ParserExpectSymbol(self,",","expected a , after an argument in function call");
				ACHIOR_LABS_SYNCHRONIZE(false);
			}

			ParserExpectSymbol(self,")","expected )");
			ACHIOR_LABS_SYNCHRONIZE(false);
			
			struct ASTFunctionCallExpr *ASTFunctionCallExpr = ParserMakeFunctionCallExpr(self,astExpr,LinkedList);
			astExpr                                              = ParserMakeExpression(self,AST_EXPRESSION_FUNCTION_CALL,ASTFunctionCallExpr);

		}
		else if(ParserIsToken(self,".",0))
		{
			ParserExpectSymbol(self,".","expected .");
			ACHIOR_LABS_SYNCHRONIZE(false);

			struct Token member;

			// check if we have a function name,raise and error if not
			if( ParserIsIdentifier(self))
			{
				member = ParserConsume(self);
			}
			else
			{
				ParserFatal(self,"expected an identifier after .");
				ACHIOR_LABS_SYNCHRONIZE(true);
			}


			struct ASTStructAccessExpr *ast_structExpr = ParserMakeStructAccessExpr(self,astExpr,member); 
			astExpr                                       = ParserMakeExpression(self,AST_EXPRESSION_STRUCT_ACCESS,ast_structExpr);
		}
		else if(ParserIsToken(self,"[",0))
		{
			ParserExpectSymbol(self,"[","expected [");
			ACHIOR_LABS_SYNCHRONIZE(false);

			struct ASTSubscriptExpr *ast_subscriptExpr = ParserMakeSubscriptExpr(self,astExpr,ParserParseExpr(self,0));

			ParserExpectSymbol(self,"]","expected ]");
			ACHIOR_LABS_SYNCHRONIZE(false);

			astExpr = ParserMakeExpression(self,AST_EXPRESSION_SUBSCRIPT,ast_subscriptExpr);
			
		}
		else if(ParserIsToken(self,"@",0))
		{
			ParserExpectSymbol(self,"@","expected @");
			ACHIOR_LABS_SYNCHRONIZE(false);

			struct Token ident;

			// check if we have a function name,raise and error if not
			if( ParserIsIdentifier(self))
			{
				ident = ParserConsume(self);
			}
			else
			{
				ParserFatal(self,"expected an identifier after fn");
				ACHIOR_LABS_SYNCHRONIZE(true);
			}

			if(ACHIOR_LABS_STRCMP(ident.value.data,"read") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrReadExpr *ast_ptr_readExpr = ParserMakePtrReadExpr(self,astExpr);
				astExpr                                    = ParserMakeExpression(self,AST_EXPRESSION_PTR_READ,ast_ptr_readExpr);

			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"write") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrWriteExpr *ast_ptr_writeExpr = ParserMakePtrWriteExpr(self,astExpr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				astExpr = ParserMakeExpression(self,AST_EXPRESSION_PTR_WRITE,ast_ptr_writeExpr);
			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"offset") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrOffsetExpr *ast_ptrOffsetExpr = ParserMakePtrOffsetExpr(self,astExpr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				astExpr = ParserMakeExpression(self,AST_EXPRESSION_PTR_OFFSET,ast_ptrOffsetExpr);
			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"byte_offset") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrByteOffsetExpr *ast_ptr_byteOffsetExpr = ParserMakePtrByteOffsetExpr(self,astExpr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				astExpr = ParserMakeExpression(self,AST_EXPRESSION_PTR_BYTE_OFFSET,ast_ptr_byteOffsetExpr);
			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"advance") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrAdvanceExpr *ast_ptr_advanceExpr = ParserMakePtrAdvanceExpr(self,astExpr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				astExpr = ParserMakeExpression(self,AST_EXPRESSION_PTR_ADVANCE,ast_ptr_advanceExpr);
			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"diff") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTPtrDiffExpr *ast_ptr_diffExpr = ParserMakePtrDiffExpr(self,astExpr,ParserParseExpr(self,0));

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				astExpr = ParserMakeExpression(self,AST_EXPRESSION_PTR_DIFF,ast_ptr_diffExpr);
			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"as_ptr") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTAsPtrExpr *astAsPtrExpr = ParserMakeAsPtrExpr(self,astExpr);
				astExpr                                = ParserMakeExpression(self,AST_EXPRESSION_AS_PTR,astAsPtrExpr);

			}
			else if(ACHIOR_LABS_STRCMP(ident.value.data,"len") == 0)
			{
				ParserExpectSymbol(self,"(","expected (");
				ACHIOR_LABS_SYNCHRONIZE(false);

				ParserExpectSymbol(self,")","expected )");
				ACHIOR_LABS_SYNCHRONIZE(false);

				struct ASTLenExpr *ast_lenExpr = ParserMakeLenExpr(self,astExpr);
				astExpr                          = ParserMakeExpression(self,AST_EXPRESSION_LEN,ast_lenExpr);
			}
			else
			{
				ParserFatal(self,"unknown intrinsic ");
				ACHIOR_LABS_SYNCHRONIZE(false);
			}
		}
		else
		{
			break;
		}
	}

	return astExpr;
}

struct ASTExpression *ParserParsePrimary(struct Parser *self)
{
	struct ASTExpression *astExpr = NULL;

	if( ParserIsTokenType(self,TOKEN_LITERAL_INT,0))
	{
		astExpr = ParserParseLiteralI32(self);
	}
	else if( ParserIsTokenType(self,TOKEN_LITERAL_CHARACTER,0))
	{
		astExpr = ParserParseLiteralCharacter(self);
	}
	else if( ParserIsTokenType(self,TOKEN_LITERAL_STRING,0))
	{
		astExpr = ParserParseLiteralString(self);
	}
	else if( ParserIsIdentifier(self))
	{
		astExpr = ParserParseVariableExpr(self);
	}
	else if(ParserIsToken(self,"(",0))
	{
		ParserExpectSymbol(self,"(",0);
		astExpr = ParserParseExpr(self,0);
		ParserExpectSymbol(self,")",0);puts("yyy");
	}
	else if(ParserIsToken(self,"&",0))
	{
		astExpr = ParserParseAddressOfExpr(self);
	}
	else
	{
		extern const char *tokenTypeNames[];
		struct Token token = ParserPeek(self,0);
	}

	return astExpr;
}



struct ASTExpression *ParserParseAddressOfExpr(struct Parser *self)
{
	ParserExpectSymbol(self,"&","expected &");
	ACHIOR_LABS_SYNCHRONIZE(false);

	struct ASTAddressOfExpr *astAddressOf = ParserMakeAddressOfExpr(self,ParserParsePrimary(self));
	struct ASTExpression *astExpr            = ParserMakeExpression(self,AST_EXPRESSION_ADDRESS_OF,astAddressOf);

	return astExpr;
}


struct ASTExpression *ParserParseVariableExpr(struct Parser *self)
{
	struct Token token                     = ParserConsume(self);
	struct ASTVariableExpr *ast_variable = ParserMakeVariableExpr(self,token);
	struct ASTExpression *astExpr        = ParserMakeExpression(self,AST_EXPRESSION_VARIABLE,ast_variable);

	return astExpr;
}




struct ASTExpression *ParserParseLiteralString(struct Parser *self)
{
	struct Token token                   = ParserConsume(self);
	struct ASTLiteralExpr *ast_literal = ParserMakeLiteralExpr(self,AST_LITERAL_STRING,token);
	struct ASTExpression *astExpr      = ParserMakeExpression(self,AST_EXPRESSION_LITERAL,ast_literal);

	return astExpr;
}



struct ASTExpression *ParserParseLiteralCharacter(struct Parser *self)
{
	struct Token token                   = ParserConsume(self);
	struct ASTLiteralExpr *ast_literal = ParserMakeLiteralExpr(self,AST_LITERAL_CHARACTER,token);
	struct ASTExpression *astExpr      = ParserMakeExpression(self,AST_EXPRESSION_LITERAL,ast_literal);

	return astExpr;
}



struct ASTExpression *ParserParseLiteralI32(struct Parser *self)
{
	struct Token token                   = ParserConsume(self);
	struct ASTLiteralExpr *ast_literal = ParserMakeLiteralExpr(self,AST_LITERAL_I32,token);
	struct ASTExpression *astExpr      = ParserMakeExpression(self,AST_EXPRESSION_LITERAL,ast_literal);

	return astExpr;
}




//  Helpers



struct ASTProgram *ParserMakeProgram(struct Parser *self,struct LinkedList decls)
{
    struct ASTProgram *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTProgram,1);

    ASTProgramNew(node,decls);
    return node;
}



struct ASTDeclaration *ParserMakeDeclaration(struct Parser *self,enum ASTDeclarationType type,void *decl)
{
    struct ASTDeclaration *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTDeclaration,1);
    
    ASTDeclarationNew(node,type,decl);
    return node;
}



struct ASTStructDecl *ParserMakeStructDecl(struct Parser *self,struct Token ident,struct LinkedList properties)
{
    struct ASTStructDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructDecl,1);

    ASTStructDeclNew(node,ident,properties);
    return node;
}



struct ASTStructProperty *ParserMakeStructProperty(struct Parser *self,struct ASTType *type,struct Token ident)
{
    struct ASTStructProperty *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructProperty,1);

    ASTStructPropertyNew(node,type,ident);
    return node;
}





struct ASTImplDecl *ParserMakeImplDecl(struct Parser *self,struct Token ident,struct LinkedList methods)
{
    struct ASTImplDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTImplDecl,1);

    ASTImplDeclNew(node,ident,methods);
    return node;
}


struct ASTSumDecl *ParserMakeSumDecl(struct Parser *self,struct Token ident,struct LinkedList variants)
{
    struct ASTSumDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTSumDecl,1);

    ASTSumDeclNew(node,ident,variants);
    return node;
}


struct ASTSumVariant *ParserMakeSumVariant(struct Parser *self,struct Token ident,enum ASTSumVariantKind kind,struct LinkedList fields)
{
	struct ASTSumVariant *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTSumVariant,1);

    ASTSumVariantNew(node,ident,kind,fields);
    return node;
}


struct ASTForeignDecl *ParserMakeForeignDecl(struct Parser *self,struct LinkedList functions)
{
    struct ASTForeignDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTForeignDecl,1);

    ASTForeignDeclNew(node,functions);
    return node;
}




struct ASTFunctionDecl *ParserMakeFunctionDecl(struct Parser *self,struct ASTType *return_type,struct Token ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes)
{
    struct ASTFunctionDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionDecl,1);

    ASTFunctionDeclNew(node,return_type,ident,arguments,block,attributes);
    return node;
}



struct ASTFunctionArgument *ParserMakeFunctionArgument(struct Parser *self,struct ASTType *type,struct Token ident)
{
    struct ASTFunctionArgument *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionArgument,1);

    ASTFunctionArgumentNew(node,type,ident);
    return node;
}



struct ASTFunctionAttributes *ParserMakeFunctionAttributes(struct Parser *self,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name)
{
    struct ASTFunctionAttributes *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionAttributes,1);

    ASTFunctionAttributesNew(node,is_pub,is_static,is_naked,is_foreign,foreign_abi,has_link_name,link_name);

    return node;
}




struct ASTType *ParserMakeType(struct Parser *self,enum ASTDataType data_type,void *type)
{
    struct ASTType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTType,1);

    ASTTypeNew(node,data_type,type);
    return node;
}




struct ASTPointerType *ParserMakePointerType(struct Parser *self,struct ASTType *type)
{
    struct ASTPointerType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPointerType,1);

    ASTPointerTypeNew(node,type);
    return node;
}




struct ASTArrayType *ParserMakeArrayType(struct Parser *self,struct ASTType *type,struct ASTExpression *size)
{
    struct ASTArrayType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTArrayType,1);

    ASTArrayTypeNew(node,type,size);
    return node;
}




struct ASTFunctionType *ParserMakeFunctionType(struct Parser *self,struct ASTType *return_type,struct LinkedList arguments)
{
    struct ASTFunctionType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionType,1);

    ASTFunctionTypeNew(node,return_type,arguments);
    return node;
}




struct ASTStructType *ParserMakeStructType(struct Parser *self,struct Token ident,struct Layout layout)
{
    struct ASTStructType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructType,1);

    ASTStructTypeNew(node,ident,layout);
    return node;
}



struct ASTAggregateType *ParserMakeAggregateType(struct Parser *self,struct Token ident)
{
    struct ASTAggregateType *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTAggregateType,1);

    ASTAggregateTypeNew(node,ident);
    return node;
}






struct ASTStatement *ParserMakeStatement(struct Parser *self,enum ASTStatementType type,void *stmt)
{
    struct ASTStatement *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStatement,1);

    ASTStatementNew(node,type,stmt);
    return node;
}




struct ASTBlockStmt *ParserMakeBlockStmt(struct Parser *self,struct LinkedList stmts)
{
    struct ASTBlockStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTBlockStmt,1);

    ASTBlockStmtNew(node,stmts);
    return node;
}




struct ASTReturnStmt *ParserMakeReturnStmt(struct Parser *self,struct ASTExpression *expr)
{
    struct ASTReturnStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTReturnStmt,1);

    ASTReturnStmtNew(node,expr);
    return node;
}




struct ASTVariableDecl *ParserMakeVariableDecl(struct Parser *self,struct ASTType *type,struct Token ident,struct ASTVariableDeclInit *init)
{
    struct ASTVariableDecl *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTVariableDecl,1);

    ASTVariableDeclNew(node,type,ident,init);
    return node;
}





struct ASTVariableDeclInit *ParserMakeVariableDeclInit(struct Parser *self,enum ASTVariableDeclInitType init_type,void *init)
{
    struct ASTVariableDeclInit *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTVariableDeclInit,1);

    ASTVariableDeclInitNew(node,init_type,init);
    return node;
}





struct ASTVariableDeclSingleInit *ParserMakeVariableDeclSingleInit(struct Parser *self,struct ASTExpression *expr)
{
    struct ASTVariableDeclSingleInit *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTVariableDeclSingleInit,1);

    ASTVariableDeclSingleInitNew(node,expr);
    return node;
}




struct ASTVariableDeclArrayInit *ParserMakeVariableDeclArrayInit(struct Parser *self,struct LinkedList elements)
{
    struct ASTVariableDeclArrayInit *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTVariableDeclArrayInit,1);

    ASTVariableDeclArrayInitNew(node,elements);
    return node;
}




struct ASTBreakStmt *ParserMakeBreakStmt(struct Parser *self)
{
    struct ASTBreakStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTBreakStmt,1);

    ASTBreakStmtNew(node);
    return node;
}






struct ASTContinueStmt *ParserMakeContinueStmt(struct Parser *self)
{
    struct ASTContinueStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTContinueStmt,1);

    ASTContinueStmtNew(node);
    return node;
}




struct ASTLoopStmt *ParserMakeLoopStmt(struct Parser *self,struct ASTBlockStmt *block)
{
    struct ASTLoopStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTLoopStmt,1);

    ASTLoopStmtNew(node,block);
    return node;
}




struct ASTWhileStmt *ParserMakeWhileStmt(struct Parser *self,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
    struct ASTWhileStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTWhileStmt,1);

    ASTWhileStmtNew(node,expr,block);
    return node;
}




struct ASTIfElif *ParserMakeIfElif(struct Parser *self,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
    struct ASTIfElif *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTIfElif,1);

    ASTIfElifNew(node,expr,block);
    return node;
}

struct ASTIfElse *ParserMakeIfElse(struct Parser *self,struct ASTBlockStmt *block)
{
    struct ASTIfElse *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTIfElse,1);

    ASTIfElseNew(node,block);
    return node;
}

struct ASTIfStmt *ParserMakeIfStmt(struct Parser *self,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList elifs,struct ASTIfElse *else_block)
{
    struct ASTIfStmt *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTIfStmt,1);

    ASTIfStmtNew(node,expr,block,elifs,else_block);
    return node;
}




struct ASTExpression *ParserMakeExpression(struct Parser *self,enum ASTExpressionType type,void *expr)
{
    struct ASTExpression *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTExpression,1);

    ASTExpressionNew(node,type,expr);
    return node;
}



struct ASTLiteralExpr *ParserMakeLiteralExpr(struct Parser *self,enum ASTLiteralType type,struct Token literal)
{
    struct ASTLiteralExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTLiteralExpr,1);

    ASTLiteralExprNew(node,type,literal);
    return node;
}




struct ASTVariableExpr *ParserMakeVariableExpr(struct Parser *self,struct Token ident)
{
    struct ASTVariableExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTVariableExpr,1);

    ASTVariableExprNew(node,ident);
    return node;
}



struct ASTUnaryExpr *ParserMakeUnaryExpr(struct Parser *self,enum ASTUnaryOperator op,struct ASTExpression *rhs)
{
    struct ASTUnaryExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTUnaryExpr,1);

    ASTUnaryExprNew(node,op,rhs);
    return node;
}




struct ASTBinaryExpr *ParserMakeBinaryExpr(struct Parser *self,struct ASTExpression *lhs,enum ASTBinaryOperator op,struct ASTExpression *rhs)
{
    struct ASTBinaryExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTBinaryExpr,1);

    ASTBinaryExprNew(node,lhs,op,rhs);
    return node;
}




struct ASTAssignmentExpr *ParserMakeAssignmentExpr(struct Parser *self,struct ASTExpression *lhs,enum ASTAssignmentOperator op,struct ASTExpression *rhs)
{
    struct ASTAssignmentExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTAssignmentExpr,1);

    ASTAssignmentExprNew(node,lhs,op,rhs);
    return node;
}




struct ASTCastExpr *ParserMakeCastExpr(struct Parser *self,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *data_type)
{
    struct ASTCastExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTCastExpr,1);

    ASTCastExprNew(node,lhs,op,data_type);
    return node;
}





struct ASTFunctionCallExpr *ParserMakeFunctionCallExpr(struct Parser *self,struct ASTExpression *base,struct LinkedList arguments)
{
    struct ASTFunctionCallExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionCallExpr,1);

    ASTFunctionCallExprNew(node,base,arguments);
    return node;
}



struct ASTAddressOfExpr *ParserMakeAddressOfExpr(struct Parser *self,struct ASTExpression *rhs)
{
    struct ASTAddressOfExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTAddressOfExpr,1);

    ASTAddressOfExprNew(node,rhs);
    return node;
}




struct ASTPtrReadExpr *ParserMakePtrReadExpr(struct Parser *self,struct ASTExpression *lhs)
{
    struct ASTPtrReadExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrReadExpr,1);

    ASTPtrReadExprNew(node,lhs);
    return node;
}




struct ASTPtrWriteExpr *ParserMakePtrWriteExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrWriteExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrWriteExpr,1);

    ASTPtrWriteExprNew(node,lhs,rhs);
    return node;
}




struct ASTPtrOffsetExpr *ParserMakePtrOffsetExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrOffsetExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrOffsetExpr,1);

    ASTPtrOffsetExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrByteOffsetExpr *ParserMakePtrByteOffsetExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrByteOffsetExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrByteOffsetExpr,1);

    ASTPtrByteOffsetExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrAdvanceExpr *ParserMakePtrAdvanceExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrAdvanceExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrAdvanceExpr,1);

    ASTPtrAdvanceExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrDiffExpr *ParserMakePtrDiffExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrDiffExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTPtrDiffExpr,1);

    ASTPtrDiffExprNew(node,lhs,rhs);
    return node;
}




struct ASTSubscriptExpr *ParserMakeSubscriptExpr(struct Parser *self,struct ASTExpression *lhs,struct ASTExpression *index)
{
    struct ASTSubscriptExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTSubscriptExpr,1);

    ASTSubscriptExprNew(node,lhs,index);
    return node;
}




struct ASTAsPtrExpr *ParserMakeAsPtrExpr(struct Parser *self,struct ASTExpression *lhs)
{
    struct ASTAsPtrExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTAsPtrExpr,1);

    ASTAsPtrExprNew(node,lhs);
    return node;
}

struct ASTLenExpr *ParserMakeLenExpr(struct Parser *self,struct ASTExpression *lhs)
{
    struct ASTLenExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTLenExpr,1);

    ASTLenExprNew(node,lhs);
    return node;
}




struct ASTStructAccessExpr *ParserMakeStructAccessExpr(struct Parser *self,struct ASTExpression *lhs,struct Token member)
{
    struct ASTStructAccessExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructAccessExpr,1);

    ASTStructAccessExprNew(node,lhs,member);
    return node;
}




struct ASTStructPointerAccessExpr *ParserMakeStructPointerAccessExpr(struct Parser *self,struct ASTExpression *lhs,struct Token member)
{
    struct ASTStructPointerAccessExpr *node = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructPointerAccessExpr,   1);

    ASTStructPointerAccessExprNew(node,lhs,member);
    return node;
}



