#include "Include/Register.h"




void ModuleSystemFatal(struct ModuleSystem *self,struct Token *token,char *message,char *label,char *help,char *fix,char *note)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return;
	}

    

	ACHIOR_LABS_STRUCT_INIT(struct Span,span);
	
    ACHIOR_LABS_PTR_INIT(struct Diagnostic,diagnostic);



	span             = token->span;
	diagnostic       = DiagnosticEngineReport(self->engine,DIAGNOSTIC_ERROR,message,self->moduleName,self->moduleSource,self->sourceLength,1);
	
	
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



bool ModuleSystemRegisterSymbols(struct ModuleSystem *self,struct Module *module)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(module->ast))
    {
        return false;
    }

    for (u64 i = 0; i < module->ast->decls.len; i++)
    {
        struct ASTDeclaration *decl = LinkedListAt(&module->ast->decls, i);

        if (ACHIOR_LABS_NULL(decl))
        {
            continue;
        }

        switch (ASTDECLARATION_GET_KIND(*decl))
        {
            case AST_DECLARATION_FUNCTION:
            {
                ModuleSystemRegisterFunctionDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
            case AST_DECLARATION_ENUM:
            {
                ModuleSystemRegisterEnumDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
            case AST_DECLARATION_STRUCT:
            {
                ModuleSystemRegisterStructDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
            case AST_DECLARATION_IMPL:
            {
                ModuleSystemRegisterImplDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
            case AST_DECLARATION_VARIABLE:
            {
                ModuleSystemRegisterVariableDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
            case AST_DECLARATION_TYPE:
            {
                ModuleSystemRegisterTypeDecl(self,module,ASTDECLARATION_GET_DECL(*decl));
                break;
            }
        }

    }

        

    return true;
}




void ModuleSystemRegisterTypeDecl(struct ModuleSystem *self,struct Module *module,struct ASTTypeDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_TYPE_ALIAS;
    name = decl->ident;

    /*
    duplicate definition check
    */

    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));

    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,decl->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);

    bool isPublic = false;

    ModuleSymbolNew(symbol,kind,name,decl,isPublic,module);
    symbol->type = decl->type;


    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);
}




void ModuleSystemRegisterVariableDecl(struct ModuleSystem *self,struct Module *module,struct ASTVariableDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_VARIABLE;
    name = decl->ident;

    /*
    duplicate definition check
    */
    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));

    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate  symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,decl->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);

    bool isPublic = false;

    ModuleSymbolNew(symbol,kind,name,decl,isPublic,module);


    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);
}




bool ModuleSystemRegisterImplDecl(struct ModuleSystem *self,struct Module *module,struct ASTImplDecl *decl)
{
    for(u64 i = 0; i < decl->methods.len; i++)
    {
        struct ASTFunctionDecl *function = LinkedListAt(&decl->methods,i);
        ModuleSystemRegisterFunctionDecl(self,module,function);
    }
}


bool ModuleSystemRegisterStructDecl(struct ModuleSystem *self,struct Module *module,struct ASTStructDecl *decl)
{
    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_STRUCT;
    name = decl->ident;

    
    // check for duplicate definition

    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));
    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,decl->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);
    bool isPublic               = false;

    ModuleSymbolNew(symbol,kind,name,decl,isPublic,module);
    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);
}



bool ModuleSystemRegisterEnumDecl(struct ModuleSystem *self,struct Module *module,struct ASTEnumDecl *decl)
{
    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_ENUM;
    name = decl->ident;

    char *identName = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,name->value.size + 1);
    u64 identLength = name->value.size;

    ACHIOR_LABS_MEMSET(identName,0,identLength);
    ACHIOR_LABS_STRNCPY(identName,name->value.data,identLength);
    
    // check for duplicate definition

    struct ModuleSymbol *existing = HashMapGet(&module->symbols,identName,identLength);
    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,decl->ident,buf,NULL,NULL,NULL,NULL);
    }



    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);
    bool isPublic               = false;

    ModuleSymbolNew(symbol,kind,name,decl,isPublic,module);
    HashMapAdd(&module->symbols,identName,identLength,symbol);
}



bool ModuleSystemRegisterFunctionDecl(struct ModuleSystem *self,struct Module *module,struct ASTFunctionDecl *decl)
{
    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_FUNCTION;
    name = decl->ident;

    // cehck for duplicate definition

    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));

    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,decl->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);

    bool isPublic = false;

    ModuleSymbolNew(symbol,kind,name,decl,isPublic,module);
    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);

    for(u64 i = 0; i < decl->arguments.len; i++)
    {
        ModuleSystemRegisterFunctionArgument(self,module,LinkedListAt(&decl->arguments,i));
    }

    
    if(ACHIOR_LABS_NOT_NULL(decl->block))
    {
        ModuleSystemRegisterBlockStmt(self,module,decl->block);
    }
    
}




void ModuleSystemRegisterFunctionArgument(struct ModuleSystem *self,struct Module *module,struct ASTFunctionArgument *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_VARIABLE;
    name = stmt->ident;

    /*
    duplicate definition check
    */
    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));

    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate  symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,stmt->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);

    bool isPublic = false;

    ModuleSymbolNew(symbol,kind,name,stmt,isPublic,module);


    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);
}




void ModuleSystemRegisterBlockStmt(struct ModuleSystem *self,struct Module *module,struct ASTBlockStmt *block)
{
    for(u64 i = 0; i < block->stmts.len; i++)
    {
        ModuleSystemRegisterStmt(self,module,LinkedListAt(&block->stmts,i));
    }   
}


void ModuleSystemRegisterStmt(struct ModuleSystem *self,struct Module *module,struct ASTStatement *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(ASTSTATEMENT_GET_KIND(*stmt))
	{
		case AST_STATEMENT_RETURN:
		{
            ModuleSystemRegisterReturnStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            ModuleSystemRegisterLoopStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            ModuleSystemRegisterWhileStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            ModuleSystemRegisterBreakStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            ModuleSystemRegisterContinueStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_IF:
		{
            ModuleSystemRegisterIfStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            ModuleSystemRegisterVariableDeclStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            ModuleSystemRegisterExpressionStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
			break;
		}
		default:
		{
			break;
		}
	}

}



void ModuleSystemRegisterExpressionStmt(struct ModuleSystem *self,struct Module *module,struct ASTExpression *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

}



void ModuleSystemRegisterVariableDeclStmt(struct ModuleSystem *self,struct Module *module,struct ASTVariableDecl *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    enum ModuleSymbolKind kind;
    struct Token *name;

    kind = MODULE_SYMBOL_VARIABLE;
    name = stmt->ident;

    /*
    duplicate definition check
    */
    struct ModuleSymbol *existing = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name));

    if (ACHIOR_LABS_NOT_NULL(existing))
    {
        ACHIOR_LABS_PTR_INIT(char,buf);
        buf = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,1024);

        ACHIOR_LABS_SNPRINTF(buf,1024,"duplicate  symbol in module %s ",module->moduleName);

        ModuleSystemFatal(self,stmt->ident,buf,NULL,NULL,NULL,NULL);
    }

    struct ModuleSymbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleSymbol,1);

    bool isPublic = false;

    ModuleSymbolNew(symbol,kind,name,stmt,isPublic,module);


    HashMapAdd(&module->symbols,TOKEN_GET_VALUE_DATA(*name),TOKEN_GET_VALUE_SIZE(*name),symbol);
}



void ModuleSystemRegisterIfStmt(struct ModuleSystem *self,struct Module *module,struct ASTIfStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
    
    ModuleSystemRegisterBlockStmt(self,module,stmt->block);

    for(u64 i = 0; i < stmt->elifs.len; i++)
    {
        struct ASTIfElif *Elif = LinkedListAt(&stmt->elifs,i);
   
        ModuleSystemRegisterBlockStmt(self,module,Elif->block);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->elseBlock))
    {
        ModuleSystemRegisterBlockStmt(self,module,stmt->elseBlock->block);
    }
}


void ModuleSystemRegisterContinueStmt(struct ModuleSystem *self,struct Module *module,struct ASTContinueStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}



void ModuleSystemRegisterBreakStmt(struct ModuleSystem *self,struct Module *module,struct ASTBreakStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}


void ModuleSystemRegisterWhileStmt(struct ModuleSystem *self,struct Module *module,struct ASTWhileStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ModuleSystemRegisterBlockStmt(self,module,stmt->block);
}



void ModuleSystemRegisterLoopStmt(struct ModuleSystem *self,struct Module *module,struct ASTLoopStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ModuleSystemRegisterBlockStmt(self,module,stmt->block);
}



void ModuleSystemRegisterReturnStmt(struct ModuleSystem *self,struct Module *module,struct ASTReturnStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
    
}







bool ModuleSystemRegisterAllSymbols(struct ModuleSystem *self)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(self->registry))
    {
        return false;
    }

    for (u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for (struct HashNode *node = self->registry->modules.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct Module *module = (struct Module *)node->value;

            if (ACHIOR_LABS_NULL(module))
            {
                continue;
            }

            self->moduleName   = module->moduleName;
            self->moduleSource = module->moduleSource;
            self->sourceLength = module->sourceLength;
            
            ModuleSystemRegisterSymbols(self,module);
        }
    }

    return true;
}












