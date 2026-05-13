#include "Include/ResolveSymbols.h"
#include "../TypeChecking/Include/TypeChecking.h"





struct String StringReplacePathSeparators(struct String source);

bool ModuleSystemResolveSymbolType(struct ModuleSystem *self,struct Module *module,struct ASTType *type)
{
    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(type))
    {
        return false;
    }

    switch(type->dataType)
    {
        case AST_DATA_TYPE_POINTER:
        {
            struct ASTPointerType *pointer = ASTTYPE_GET_TYPE(*type);

            return ModuleSystemResolveSymbolType(self,module,ASTPOINTERTYPE_GET_TYPE(*pointer));
        }

        case AST_DATA_TYPE_ARRAY:
        {
            struct ASTArrayType *array = ASTTYPE_GET_TYPE(*type);

            ModuleSystemResolveSymbolType(self,module,ASTARRAYTYPE_GET_TYPE(*array));
            ModuleSystemResolveSymbolExpression(self,module,ASTARRAYTYPE_GET_SIZE(*array));

            return true;
        }

        case AST_DATA_TYPE_AGGREGATE:
        {
            struct ASTAggregateType *aggregate = ASTTYPE_GET_TYPE(*type);

            if (ASTAGGREGATETYPE_GET_PATH(*aggregate).len == 0)
            {
                return false;
            }

            // token element: module or local symbol
            struct Token *token = LinkedListAt(&ASTAGGREGATETYPE_GET_PATH(*aggregate),0);

            struct Module *currentModule = module;
            struct ModuleSymbol *symbol  = NULL;

            // check if token is an import alias
            struct ModuleImport *import = HashMapGet(&module->imports,TOKEN_GET_VALUE_DATA(*token),TOKEN_GET_VALUE_SIZE(*token));

            u64 index = 0;

            if (import != NULL && import->target != NULL)
            {
                currentModule = import->target;
                index = 1; // skip alias
            }

            struct String tmpName = StringReplacePathSeparators(currentModule->fullPath);;

            u64 bufSize = 1024;
            char buf[bufSize];
            ACHIOR_LABS_MEMSET(buf,0,bufSize);

            struct Token *tok = LinkedListAt(&ASTAGGREGATETYPE_GET_PATH(*aggregate),1);
            ACHIOR_LABS_SNPRINTF(buf,bufSize,"%s%s",tmpName.data,TOKEN_GET_VALUE_DATA(*tok));

            symbol = HashMapGet(&currentModule->symbols,buf,strlen(buf));


            if (symbol == NULL)
            {
                printf("unknown type '%s' in module : size = > %lu\n",buf,strlen(buf));
                StringPrintln(&currentModule->fullPath);
                return false;
            }

            

            if(ACHIOR_LABS_EQUAL(symbol->kind,MODULE_SYMBOL_STRUCT))
            {
                struct ASTStructType *structType = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructType,1);
                ASTStructTypeNew(structType,symbol->ident,(struct Layout){0});

                ASTSTRUCTTYPE_SET_MODULE(*structType,currentModule);

                ASTTYPE_SET_DATATYPE(*type,AST_DATA_TYPE_STRUCT);
                ASTTYPE_SET_TYPE(*type,structType);
            }
            else if(ACHIOR_LABS_EQUAL(symbol->kind,MODULE_SYMBOL_ENUM))
            {
                struct ASTStructType *structType = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructType,1);
                ASTStructTypeNew(structType,symbol->ident,(struct Layout){0});

                ASTSTRUCTTYPE_SET_MODULE(*structType,currentModule);

                ASTTYPE_SET_DATATYPE(*type,AST_DATA_TYPE_ENUM);
                ASTTYPE_SET_TYPE(*type,structType);
            }

            return true;
        }
        default:
        {
            break;
        }
    }
}



bool ModuleSystemResolveSymbolIdentifiers(struct ModuleSystem *self,struct Module *module)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(module->ast))
    {
        return false;
    }

    for (u64 i = 0; i < module->ast->decls.len; i++)
    {
        struct ASTDeclaration *decl = LinkedListAt(&module->ast->decls,i);

        if (ACHIOR_LABS_NULL(decl))
        {
            continue;
        }

        switch(ASTDECLARATION_GET_KIND(*decl))
        {
            case AST_DECLARATION_FUNCTION:
            {
                ModuleSystemResolveSymbolFunctionDecl(self,module,decl->decl);
                break;
            }
            case AST_DECLARATION_IMPL:
            {
                ModuleSystemResolveSymbolImplDecl(self,module,decl->decl);
                break;
            }
            case AST_DECLARATION_STRUCT:
            {
                ModuleSystemResolveSymbolStructDecl(self,module,decl->decl);
                break;
            }
            case AST_DECLARATION_ENUM:
            {
                ModuleSystemResolveSymbolEnumDecl(self,module,decl->decl);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return true;
}



bool ModuleSystemResolveSymbolEnumDecl(struct ModuleSystem *self,struct Module *module,struct ASTEnumDecl *decl)
{
    ACHIOR_LABS_VAR_INIT(u64,constantLength);
    ACHIOR_LABS_PTR_INIT(struct ASTEnumConstant,constant);

    constantLength = decl->constants.len;

    for(u64 i = 0; i < constantLength; i++)
    {
        constant = LinkedListAt(&decl->constants,i);
        ModuleSystemResolveSymbolExpression(self,module,constant->expr);
    }
}


bool ModuleSystemResolveSymbolStructDecl(struct ModuleSystem *self,struct Module *module,struct ASTStructDecl *decl)
{
    ACHIOR_LABS_VAR_INIT(u64,propertyLength);
    ACHIOR_LABS_PTR_INIT(struct ASTStructProperty,property);

    propertyLength = decl->properties.len;

    for(u64 i = 0; i < propertyLength; i++)
    {
        property = LinkedListAt(&decl->properties,i);
        ModuleSystemResolveSymbolType(self,module,property->type);
    }
}


bool ModuleSystemResolveSymbolImplDecl(struct ModuleSystem *self,struct Module *module,struct ASTImplDecl *decl)
{
    ACHIOR_LABS_VAR_INIT(u64,methodLength);

    methodLength = decl->methods.len;

    for(u64 i = 0; i < methodLength; i++)
    {
        ModuleSystemResolveSymbolFunctionDecl(self,module,LinkedListAt(&decl->methods,i));
    }
}


bool ModuleSystemResolveSymbolFunctionDecl(struct ModuleSystem *self,struct Module *module,struct ASTFunctionDecl *decl)
{
    ModuleSystemResolveSymbolType(self,module,decl->returnType);
    for(u64 i = 0; i < ASTFUNCTIONDECL_GET_ARGUMENTS(*decl).len; i++)
    {
        ModuleSystemResolveSymbolFunctionArgument(self,module,LinkedListAt(&decl->arguments,i));
    }

    if(ACHIOR_LABS_NOT_NULL(decl->block))
    {
        ModuleSystemResolveSymbolBlockStmt(self,module,decl->block);
    }
}




bool ModuleSystemResolveSymbolFunctionArgument(struct ModuleSystem *self,struct Module *module,struct ASTFunctionArgument *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    // 1. resolve the type
    if (!ModuleSystemResolveSymbolType(self,module,ASTVARIABLEDECL_GET_TYPE(*stmt)))
    {
        return false;
    }
}



bool ModuleSystemResolveSymbolBlockStmt(struct ModuleSystem *self,struct Module *module,struct ASTBlockStmt *block)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(block))
    {
        return false;
    }

    for (u64 i = 0; i < ASTBLOCKSTMT_GET_STMTS(*block).len; i++)
    {
        struct ASTStatement *stmt = LinkedListAt(&ASTBLOCKSTMT_GET_STMTS(*block),i);

        if (ACHIOR_LABS_NULL(stmt))
        {
            continue;
        }

        ModuleSystemResolveSymbolStatement(self,module,stmt);
    }
}




bool ModuleSystemResolveSymbolStatement(struct ModuleSystem *self,struct Module *module,struct ASTStatement *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    switch(ASTSTATEMENT_GET_KIND(*stmt))
    {
        case AST_STATEMENT_RETURN:
        {
            ModuleSystemResolveSymbolReturnStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
            break;
        }
        case AST_STATEMENT_EXPRESSION:
        {
            ModuleSystemResolveSymbolExpressionStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
            break;
        }
        case AST_STATEMENT_VAR_DECL:
        {
            ModuleSystemResolveSymbolVariableDeclStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
            break;
        }
        case AST_STATEMENT_WHILE:
        {
            ModuleSystemResolveSymbolWhileStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
            break;
        }
        case AST_STATEMENT_IF:
        {
            ModuleSystemResolveSymbolIfStmt(self,module,ASTSTATEMENT_GET_STMT(*stmt));
            break;
        }
    }
}

bool ModuleSystemResolveSymbolVariableDeclStmt(struct ModuleSystem *self,struct Module *module,struct ASTVariableDecl *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    // 1. resolve the type
    if (!ModuleSystemResolveSymbolType(self,module,ASTVARIABLEDECL_GET_TYPE(*stmt)))
    {
        return false;
    }

    

    // 2. resolve initializer (if exists)

    if (stmt->init != NULL)
    {
        struct ASTVariableDeclInit *init = stmt->init;

        switch (init->kind)
        {
            case AST_VAR_DECL_INIT_SINGLE_INIT:
            {
                struct ASTVariableDeclSingleInit *single =init->init;

                ModuleSystemResolveSymbolExpression(self,module,single->expr);

                break;
            }

            case AST_VAR_DECL_INIT_ARRAY_INIT:
            {
                struct ASTVariableDeclArrayInit *array = init->init;

                for (u64 i = 0; i < array->elements.len; i++)
                {
                    struct ASTVariableDeclInit *elem = LinkedListAt(&array->elements,i);

                    // recursive (arrays can be nested)
                }

                break;
            }
        }
    }


    return true;
}


bool ModuleSystemResolveSymbolExpressionStmt(struct ModuleSystem *self,struct Module *module,struct ASTExpression *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,stmt);
}




bool ModuleSystemResolveSymbolIfStmt(struct ModuleSystem *self,struct Module *module,struct ASTIfStmt *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    ACHIOR_LABS_VAR_INIT(u64,elifLength);
    ACHIOR_LABS_PTR_INIT(struct ASTIfElif,elifBlock);

    ModuleSystemResolveSymbolExpression(self,module,stmt->expr);
    ModuleSystemResolveSymbolBlockStmt(self,module,stmt->block);

    elifLength = stmt->elifs.len;

    for(u64 i = 0; i < elifLength; i++)
    {
        elifBlock = LinkedListAt(&stmt->elifs,i);

        ModuleSystemResolveSymbolExpression(self,module,elifBlock->expr);
        ModuleSystemResolveSymbolBlockStmt(self,module,elifBlock->block);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->elseBlock))
    {
        ModuleSystemResolveSymbolBlockStmt(self,module,stmt->elseBlock->block);
    }
}






bool ModuleSystemResolveSymbolWhileStmt(struct ModuleSystem *self,struct Module *module,struct ASTWhileStmt *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,stmt->expr);
    ModuleSystemResolveSymbolBlockStmt(self,module,stmt->block);
}





bool ModuleSystemResolveSymbolReturnStmt(struct ModuleSystem *self,struct Module *module,struct ASTReturnStmt *stmt)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(stmt))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,stmt->expr);
}





bool ModuleSystemResolveSymbolExpression(struct ModuleSystem *self,struct Module *module,struct ASTExpression *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    switch (ASTEXPRESSION_GET_KIND(*expr))
    {
        case AST_EXPRESSION_VARIABLE:
        {
            ModuleSystemResolveSymbolVariableExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_PAREN:
        {
            ModuleSystemResolveSymbolParenExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            ModuleSystemResolveSymbolUnaryExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            ModuleSystemResolveSymbolBinaryExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            ModuleSystemResolveSymbolAssignmentExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            ModuleSystemResolveSymbolFunctionCallExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_METHOD:
        {
            ModuleSystemResolveSymbolMethodExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            ModuleSystemResolveSymbolStructAccessExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            ModuleSystemResolveSymbolStructPointerAccessExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
        case AST_EXPRESSION_PATH:
        {
            ModuleSystemResolveSymbolPathExpr(self,module,ASTEXPRESSION_GET_EXPR(*expr));
            break;
        }
    }
}

struct String StringGetSubStringFromEnd(struct String src, u64 n)
{
    struct String out;
    StringNew(&out, n, src.bump);

    if (n > src.size)
    {
        n = src.size;
    }

    StringPushBack(&out, src.data + (src.size - n));

    return out;
}

struct String StringReplacePathSeparators(struct String source);

bool ModuleSystemResolveSymbolPathExpr(struct ModuleSystem *self,struct Module *module,struct ASTPathExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }


    if (expr->path.len == 0)
    {
        return false;
    }


    

    struct Token *token = LinkedListAt(&expr->path,0);
    char *name          = TOKEN_GET_VALUE_DATA(*token);
    struct ModuleSymbol *sym = NULL;

    //puts(name);

    struct ModuleImport *import = HashMapGet(&module->imports,name,strlen(name));
    struct Module *current      = module;

    if (import == NULL || import->target == NULL)
    {
        // check for local path i.e it migt be an enum
        struct String identName;
        StringNew(&identName,current->fullPath.capacity,self->bump);
        StringPushBack(&identName,current->fullPath.data);


        for (u64 i = 0; i < expr->path.len - 1; i++)
        {
            token = LinkedListAt(&expr->path,i);
            name  = TOKEN_GET_VALUE_DATA(*token);

            StringPushBack(&identName,name);
        }

        identName = StringReplacePathSeparators(identName);
        name      = identName.data;
        sym       = HashMapGet(&current->symbols,name,strlen(name));


        expr->symbol = sym;

        return true;
    }

    current = import->target;

    if(ACHIOR_LABS_NULL(current))
    {
        puts("null");
    }

    


    
    //StringPrintln(&current->fullPath);

    struct String identName;
    StringNew(&identName,current->fullPath.capacity,self->bump);
    StringPushBack(&identName,current->fullPath.data);


    for (u64 i = 1; i < expr->path.len; i++)
    {
        token = LinkedListAt(&expr->path,i);
        name  = TOKEN_GET_VALUE_DATA(*token);

        StringPushBack(&identName,name);
    }

    identName = StringReplacePathSeparators(identName);
    name      = identName.data;
    sym       = HashMapGet(&current->symbols,name,strlen(name));

   

    if(ACHIOR_LABS_NULL(sym))
    {

        token                    = LinkedListAt(&expr->path,expr->path.len - 1);
        struct String lastString = StringGetSubStringFromEnd(identName,TOKEN_GET_VALUE_SIZE(*token));

        if(ACHIOR_LABS_STRNCMP(TOKEN_GET_VALUE_DATA(*token),lastString.data,lastString.size) == 0)
        {
            identName.size -= lastString.size;

            char buf[100];
            ACHIOR_LABS_MEMSET(buf,0,sizeof(buf));
            ACHIOR_LABS_STRNCPY(buf,identName.data,identName.size);


            sym = HashMapGet(&current->symbols,buf,strlen(buf));
        }
    }
        

    if(ACHIOR_LABS_TRUE(expr->isFunction))
    {
        for(u64 i = 0; i < expr->arguments.len; i++)
        {
            struct ASTExpression *tmpExpr = LinkedListAt(&expr->arguments,i);
            ModuleSystemResolveSymbolExpression(self,module,tmpExpr);
        }
    }

    if (sym == NULL)
    {
        puts("NULL Path Expr");
    }

    //puts(sym->ident->value.data);

    expr->symbol = sym;
}



bool ModuleSystemResolveSymbolStructPointerAccessExpr(struct ModuleSystem *self,struct Module *module,struct ASTStructPointerAccessExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }


    ModuleSystemResolveSymbolExpression(self,module,expr->lhs);

}



bool ModuleSystemResolveSymbolStructAccessExpr(struct ModuleSystem *self,struct Module *module,struct ASTStructAccessExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }


    ModuleSystemResolveSymbolExpression(self,module,expr->lhs);

}




bool ModuleSystemResolveSymbolMethodExpr(struct ModuleSystem *self,struct Module *module,struct ASTMethodExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->lhs);


    for (u64 i = 0; i < expr->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&expr->arguments,i);

        ModuleSystemResolveSymbolExpression(self,module,argument);
    }
}



bool ModuleSystemResolveSymbolFunctionCallExpr(struct ModuleSystem *self,struct Module *module,struct ASTFunctionCallExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->base);

    for (u64 i = 0; i < expr->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&expr->arguments,i);

        ModuleSystemResolveSymbolExpression(self,module,argument);
    }
}


bool ModuleSystemResolveSymbolAssignmentExpr(struct ModuleSystem *self,struct Module *module,struct ASTAssignmentExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->lhs);
    ModuleSystemResolveSymbolExpression(self,module,expr->rhs);
}

bool ModuleSystemResolveSymbolBinaryExpr(struct ModuleSystem *self,struct Module *module,struct ASTBinaryExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->lhs);
    ModuleSystemResolveSymbolExpression(self,module,expr->rhs);
}


bool ModuleSystemResolveSymbolUnaryExpr(struct ModuleSystem *self,struct Module *module,struct ASTUnaryExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->rhs);
}




bool ModuleSystemResolveSymbolParenExpr(struct ModuleSystem *self,struct Module *module,struct ASTParenExpr *expr)
{
    if (ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(expr))
    {
        return false;
    }

    ModuleSystemResolveSymbolExpression(self,module,expr->expr);
}




bool ModuleSystemResolveSymbolVariableExpr(struct ModuleSystem *self,struct Module *module,struct ASTVariableExpr *expr)
{
    struct ModuleSymbol *symbol = HashMapGet(&module->symbols,TOKEN_GET_VALUE_DATA(*(expr->ident)),TOKEN_GET_VALUE_SIZE(*(expr->ident)));

    if (symbol == NULL)
    {
        // try the imports 

        for (u64 i = 0; i < module->imports.capacity; i++)
        {
            for (struct HashNode *node = module->imports.buckets[i]; node != NULL; node = node->next)
            {
                struct ModuleImport *import = node->value;

                if (import == NULL || import->target == NULL)
                {
                    continue;
                }

                symbol = HashMapGet(&import->target->symbols,TOKEN_GET_VALUE_DATA(*(expr->ident)),TOKEN_GET_VALUE_SIZE(*(expr->ident)));

                if (ACHIOR_LABS_NOT_NULL(symbol))
                {
                    break;
                }
            }

            if (ACHIOR_LABS_NOT_NULL(symbol))
            {
                break;
            }
        }
    }

    expr->symbol = symbol;
}



bool ModuleSystemResolveSymbolAllIdentifiers(struct ModuleSystem *self)
{
    if (ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    for (u64 i = 0; i < self->order.len; i++)
    {
        struct Module *module = LinkedListAt(&self->order,i);

        if (ACHIOR_LABS_NULL(module))
        {
            continue;
        }

        if (!ModuleSystemResolveSymbolIdentifiers(self,module))
        {
            return false;
        }
    }

    return true;
}





bool ModuleSystemTypeCheckAll(struct ModuleSystem *self)
{
    if (ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    for (u64 i = 0; i < self->order.len; i++)
    {
        struct Module *module = LinkedListAt(&self->order,i);

        if (ACHIOR_LABS_NULL(module))
        {
            continue;
        }

        struct TypeChecking typeChecker;
        TypeCheckingNew(&typeChecker,module,self->options->global_counter,self->bump);
        self->options->global_counter = typeChecker.globalCounter;
    }

    
    return true;
}
