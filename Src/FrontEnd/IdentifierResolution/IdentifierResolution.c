#include "Include/IdentifierResolution.h"



bool IdentifierEntryNew(struct IdentifierEntry *self,bool hasLinkage,bool isCurrent,enum IdentifierAggregateKind aggregateKind,struct String ident)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->hasLinkage    = hasLinkage;
    self->isCurrent     = isCurrent;
    self->aggregateKind = aggregateKind;
    self->ident         = ident;

    return true;
}


bool IdentifierResolutionNew(struct IdentifierResolution *self,struct ASTProgram *program,char *fileName,u64 globalCounter,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->program       = program;
    self->globalCounter = globalCounter;
    self->bump          = bump;

    

    struct HashMap identMap;
    HashMapNew(&identMap,10,self->bump);
    HashMapNew(&self->structMap,10,self->bump);
    HashMapNew(&self->functionAttributes,10,self->bump);

    
    IdentifierResolutionProgram(self,program,&identMap);

    puts("Identifier Resolution done");

    return true;
}


void IdentifierResolutionProgram(struct IdentifierResolution *self,struct ASTProgram *program,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(program))
    {
        return;
    }
 
    
    for(u64 i = 0; i < program->decls.len; i++)
    {
		IdentifierResolutionDeclaration(self,LinkedListAt(&program->decls,i),identMap);
	}
}


void IdentifierResolutionDeclaration(struct IdentifierResolution *self,struct ASTDeclaration *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

	switch(decl->type)
	{
		case AST_DECLARATION_STRUCT:
		{
			IdentifierResolutionStructDecl(self,decl->decl,identMap);
			break;
		}
		case AST_DECLARATION_UNION:
		{
			IdentifierResolutionUnionDecl(self,decl->decl,identMap);
			break;
		}
		case AST_DECLARATION_IMPL:
		{
			IdentifierResolutionImplDecl(self,decl->decl,identMap);
			break;
		}
		case AST_DECLARATION_SUM:
		{
            break;
			//IdentifierResolutionSumDecl(self,decl->decl,identMap);
			break;
		}
		case AST_DECLARATION_FUNCTION:
		{
			IdentifierResolutionFunctionDecl(self,decl->decl,identMap);
			break;
		}
		default:
		{
			break;
		}
	}
}





void IdentifierResolutionStructDecl(struct IdentifierResolution *self,struct ASTStructDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    char *structIdent             = decl->ident.value.data;
    u64 structIdentLength         = ACHIOR_LABS_STRLEN(structIdent);
    struct IdentifierEntry *entry = HashMapGet(&self->structMap,structIdent,structIdentLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        puts("struct redeclared : [error]");
        return;
    }

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_STRUCT,decl->ident.value);
    
    HashMapGet(&self->structMap,structIdent,structIdentLength);
}





void IdentifierResolutionUnionDecl(struct IdentifierResolution *self,struct ASTUnionDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    char *structIdent             = decl->ident.value.data;
    u64 structIdentLength         = ACHIOR_LABS_STRLEN(structIdent);
    struct IdentifierEntry *entry = HashMapGet(&self->structMap,structIdent,structIdentLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        puts("union redeclared : [error]");
        return;
    }

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_UNION,decl->ident.value);
    
    HashMapAdd(&self->structMap,structIdent,structIdentLength,entry);
}


/*


void IdentifierResolutionSumDecl(struct IdentifierResolution *self,struct ASTSumDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    IdentifierResolutionSumEnum(self,decl->ident.value.data,decl->variants);
    

    
    IdentifierResolutionIdentifier(self,decl->ident);

    

    IdentifierResolutionSumVariants(self,decl->variants);

    

}


char *IdentifierResolutionCapitalizeString(struct IdentifierResolution *self,char *source)
{
    u64 length        = ACHIOR_LABS_STRLEN(source);
    char *destination = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,length + 1); 

    for(u64 i = 0; i < length; i++)
    {
        destination[i] = ACHIOR_LABS_TOUPPER(source[i]);
    }

    destination[length] = '\0';
    return destination;
}


void IdentifierResolutionSumEnum(struct IdentifierResolution *self,char *ident,struct LinkedList variants)
{
    
    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        
        break;
    }

    
}




void IdentifierResolutionSumVariants(struct IdentifierResolution *self,struct LinkedList va8/riants)
{
    
    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        switch(variant->kind)
        {
            case AST_SUM_VARIANT_UNIT:
            {
                struct ASTType *type = LinkedListAt(&variant->fields,0);
                
                struct LinkedList arrayBuffer;
                
                
                //IdentifierResolutionType(self,type,&arrayBuffer,identMap);
                
                IdentifierResolutionIdentifier(self,variant->ident);
                
                
                break;
            }
            case AST_SUM_VARIANT_TUPLE:
            {
                for(u64 i = 0; i < variant->fields.len; i++)
                {
                    struct ASTType *type = LinkedListAt(&variant->fields,i);
                    struct LinkedList arrayBuffer;
                    //IdentifierResolutionType(self,type,&arrayBuffer,identMap);
                }

                
                break;
            }
            case AST_SUM_VARIANT_STRUCT:
            {
                break;
            }
        }
    }
    
}


*/



void IdentifierResolutionImplDecl(struct IdentifierResolution *self,struct ASTImplDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    for(u64 i = 0; i < decl->methods.len; i++)
    {
        struct ASTFunctionDecl *method = LinkedListAt(&decl->methods,i);
        IdentifierResolutionFunctionDecl(self,method,identMap);
    }
}


void IdentifierResolutionFunctionDecl(struct IdentifierResolution *self,struct ASTFunctionDecl *decl,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    if(ACHIOR_LABS_EQUAL(decl->returnType->dataType,AST_DATA_TYPE_AGGREGATE))
    {
        struct ASTAggregateType *type = (struct ASTAggregateType *)decl->returnType->type;
        char *ident                   = type->ident.value.data;
        u64 identLength               = ACHIOR_LABS_STRLEN(ident);
        struct IdentifierEntry *entry = HashMapGet(&self->structMap,ident,identLength);

        if(ACHIOR_LABS_NULL(entry))
        {
            puts("unknown aggregate type encountered");
        }

        if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            decl->returnType->dataType = AST_DATA_TYPE_STRUCT;
        }
        else if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            decl->returnType->dataType = AST_DATA_TYPE_UNION;
        }
    }


    char *ident                   = decl->ident.value.data;
    u64 identLength               = ACHIOR_LABS_STRLEN(ident);
    struct IdentifierEntry *entry = HashMapGet(&self->structMap,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            puts("union redeclared : [error]");
            return;
        }
        
    }

    HashMapAdd(&self->functionAttributes,ident,identLength,decl->attributes);

    entry = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,decl->ident.value);
    
    HashMapAdd(&self->structMap,ident,identLength,entry);

    struct HashMap *newIdentMap = identMap;

    for(u64 i = 0; i < decl->arguments.len; i++)
    {
        IdentifierResolutionFunctionArgument(self,LinkedListAt(&decl->arguments,i),newIdentMap);
    }

    if(ACHIOR_LABS_NULL(decl->block))
    {
        IdentifierResolutionBlockStmt(self,decl->block,newIdentMap);
    }
}



void IdentifierResolutionFunctionArgument(struct IdentifierResolution *self,struct ASTFunctionArgument *argument,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }

    if(ACHIOR_LABS_EQUAL(argument->type->dataType,AST_DATA_TYPE_AGGREGATE))
    {
        struct ASTAggregateType *type = (struct ASTAggregateType *)argument->type->type;
        char *ident                   = type->ident.value.data;
        u64 identLength               = ACHIOR_LABS_STRLEN(ident);
        struct IdentifierEntry *entry = HashMapGet(&self->structMap,ident,identLength);

        if(ACHIOR_LABS_NULL(entry))
        {
            puts("unknown aggregate type encountered");
        }

        if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            argument->type->dataType = AST_DATA_TYPE_STRUCT;
        }
        else if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            argument->type->dataType = AST_DATA_TYPE_UNION;
        }
    }


    char *ident                   = argument->ident.value.data;
    u64 identLength               = ACHIOR_LABS_STRLEN(ident);
    struct IdentifierEntry *entry = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            puts("function argument redeclared : [error]");
            return;
        }
        
    }

    struct String tmp = IdentifierResolutionMakeTmp(self);
    entry             = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,tmp);
    
    HashMapAdd(identMap,ident,identLength,entry);
    argument->ident.value = tmp;
}




void IdentifierResolutionBlockStmt(struct IdentifierResolution *self,struct ASTBlockStmt *block,struct HashMap *identMap)
{
    
    struct HashMap *newIdentMap = identMap;
    for(u64 i = 0; i < block->stmts.len; i++)
    {
        IdentifierResolutionStmt(self,LinkedListAt(&block->stmts,i),newIdentMap);
    }   
}


void IdentifierResolutionStmt(struct IdentifierResolution *self,struct ASTStatement *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(stmt->type)
	{
		case AST_STATEMENT_RETURN:
		{
            IdentifierResolutionReturnStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            IdentifierResolutionLoopStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            IdentifierResolutionWhileStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            IdentifierResolutionBreakStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            IdentifierResolutionContinueStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_IF:
		{
            IdentifierResolutionIfStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            IdentifierResolutionVariableDeclStmt(self,stmt->stmt,identMap);
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            IdentifierResolutionExpressionStmt(self,stmt->stmt,identMap);
			break;
		}
		default:
		{
			break;
		}
	}

}





void IdentifierResolutionExpressionStmt(struct IdentifierResolution *self,struct ASTExpression *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt,identMap);
}



void IdentifierResolutionVariableDeclStmt(struct IdentifierResolution *self,struct ASTVariableDecl *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    if(ACHIOR_LABS_EQUAL(stmt->type->dataType,AST_DATA_TYPE_AGGREGATE))
    {
        struct ASTAggregateType *type = (struct ASTAggregateType *)stmt->type->type;
        char *ident                   = type->ident.value.data;
        u64 identLength               = ACHIOR_LABS_STRLEN(ident);
        struct IdentifierEntry *entry = HashMapGet(&self->structMap,ident,identLength);

        if(ACHIOR_LABS_NULL(entry))
        {
            puts("unknown aggregate type encountered");
        }

        if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            stmt->type->dataType = AST_DATA_TYPE_STRUCT;
        }
        else if(ACHIOR_LABS_EQUAL(entry->aggregateKind,IDENTIFIER_AGGREGATE_STRUCT))
        {
            stmt->type->dataType = AST_DATA_TYPE_UNION;
        }
    }


    char *ident                   = stmt->ident.value.data;
    u64 identLength               = ACHIOR_LABS_STRLEN(ident);
    struct IdentifierEntry *entry = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(entry))
    {
        if(ACHIOR_LABS_TRUE(entry->isCurrent))
        {
            puts("variable identifier redeclared : [error]");
            return;
        }
        
    }

    struct String tmp = IdentifierResolutionMakeTmp(self);
    entry             = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct IdentifierEntry,1);
    IdentifierEntryNew(entry,true,true,IDENTIFIER_AGGREGATE_NONE,tmp);
    
    HashMapAdd(identMap,ident,identLength,entry);
    stmt->ident.value = tmp;

    if(ACHIOR_LABS_NOT_NULL(stmt->init))
    {
        IdentifierResolutionVariableDeclInit(self,stmt->init,identMap);
    }
}



void IdentifierResolutionVariableDeclInit(struct IdentifierResolution *self,struct ASTVariableDeclInit *init,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(init))
    {
        return;
    }

    switch(init->initType)
    {
        case AST_VAR_DECL_INIT_SINGLE_INIT:
        {
            struct ASTVariableDeclSingleInit *singleInit = (struct ASTVariableDeclSingleInit *)init->init;

            IdentifierResolutionExpression(self,singleInit->expr,identMap);
            break;
        }
        case AST_VAR_DECL_INIT_ARRAY_INIT:
        {
            struct ASTVariableDeclArrayInit *arrayInit = (struct ASTVariableDeclArrayInit *)init->init;

            for(u64 i = 0; i < arrayInit->elements.len; i++)
            {
                struct ASTVariableDeclInit *tmpInit = LinkedListAt(&arrayInit->elements,i);

                IdentifierResolutionVariableDeclInit(self,tmpInit,identMap);
            }
            break;
        }
    }

}



void IdentifierResolutionIfStmt(struct IdentifierResolution *self,struct ASTIfStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
    
    IdentifierResolutionExpression(self,stmt->expr,identMap);
    IdentifierResolutionBlockStmt(self,stmt->block,identMap);

    for(u64 i = 0; i < stmt->elifs.len; i++)
    {
        struct ASTIfElif *Elif = LinkedListAt(&stmt->elifs,i);

        IdentifierResolutionExpression(self,Elif->expr,identMap);   
        IdentifierResolutionBlockStmt(self,Elif->block,identMap);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->else_block))
    {
        
        IdentifierResolutionBlockStmt(self,stmt->else_block->block,identMap);
    }
}


void IdentifierResolutionContinueStmt(struct IdentifierResolution *self,struct ASTContinueStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}



void IdentifierResolutionBreakStmt(struct IdentifierResolution *self,struct ASTBreakStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}


void IdentifierResolutionWhileStmt(struct IdentifierResolution *self,struct ASTWhileStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt->expr,identMap);
    IdentifierResolutionBlockStmt(self,stmt->block,identMap);
}



void IdentifierResolutionLoopStmt(struct IdentifierResolution *self,struct ASTLoopStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionBlockStmt(self,stmt->block,identMap);
}



void IdentifierResolutionReturnStmt(struct IdentifierResolution *self,struct ASTReturnStmt *stmt,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    IdentifierResolutionExpression(self,stmt->expr,identMap);    
}



void IdentifierResolutionExpression(struct IdentifierResolution *self,struct ASTExpression *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

	switch(expr->type)
    {
        case AST_EXPRESSION_LITERAL:
        {
            break;
        }
        case AST_EXPRESSION_VARIABLE:
        {
            IdentifierResolutionVariableExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            IdentifierResolutionUnaryExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            IdentifierResolutionBinaryExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            IdentifierResolutionAssignmentExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_CAST:
        {
            IdentifierResolutionCastExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            IdentifierResolutionFunctionCallExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_ADDRESS_OF:
        {
            IdentifierResolutionAddressOfExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_READ:
        {
            IdentifierResolutionPtrReadExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_WRITE:
        {
            IdentifierResolutionPtrWriteExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_OFFSET:
        {
            IdentifierResolutionPtrOffsetExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_BYTE_OFFSET:
        {
            IdentifierResolutionPtrByteOffsetExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_ADVANCE:
        {
            IdentifierResolutionPtrAdvanceExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_PTR_DIFF:
        {
            IdentifierResolutionPtrDiffExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_SUBSCRIPT:
        {
            IdentifierResolutionSubscriptExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_AS_PTR:
        {
            IdentifierResolutionAsPtrExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_LEN:
        {
            IdentifierResolutionLenExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            //IdentifierResolutionStructAccessExpr(self,expr->expr,identMap);
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            //IdentifierResolutionStructPointerAccessExpr(self,expr->expr,identMap);
            break;
        }
        default:
        {
            
            break;
        }
    }
}





void IdentifierResolutionLenExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTLenExpr *len = (struct ASTLenExpr *)expr;
    
}



void IdentifierResolutionAsPtrExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAsPtrExpr *asPtr = (struct ASTAsPtrExpr *)expr;
    IdentifierResolutionExpression(self,asPtr->lhs,identMap);
}




void IdentifierResolutionSubscriptExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTSubscriptExpr *subscript = (struct ASTSubscriptExpr *)expr;

    IdentifierResolutionExpression(self,subscript->lhs,identMap);    
    IdentifierResolutionExpression(self,subscript->index,identMap);
}




void IdentifierResolutionPtrDiffExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrDiffExpr *ptrDiff = (struct ASTPtrDiffExpr *)expr;

    IdentifierResolutionExpression(self,ptrDiff->lhs,identMap);
    IdentifierResolutionExpression(self,ptrDiff->rhs,identMap);
}






void IdentifierResolutionPtrAdvanceExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrAdvanceExpr *ptrAdvance = (struct ASTPtrAdvanceExpr *)expr;

    IdentifierResolutionExpression(self,ptrAdvance->lhs,identMap);
    IdentifierResolutionExpression(self,ptrAdvance->rhs,identMap);
}






void IdentifierResolutionPtrByteOffsetExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrByteOffsetExpr *ptrByteOffset = (struct ASTPtrByteOffsetExpr *)expr;

    
    IdentifierResolutionExpression(self,ptrByteOffset->lhs,identMap);
    IdentifierResolutionExpression(self,ptrByteOffset->rhs,identMap);
}







void IdentifierResolutionPtrOffsetExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrOffsetExpr *ptrOffset = (struct ASTPtrOffsetExpr *)expr;

    IdentifierResolutionExpression(self,ptrOffset->lhs,identMap);
    IdentifierResolutionExpression(self,ptrOffset->rhs,identMap);
}





void IdentifierResolutionPtrWriteExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrWriteExpr *ptrWrite = (struct ASTPtrWriteExpr *)expr;

    
    IdentifierResolutionExpression(self,ptrWrite->lhs,identMap);
    IdentifierResolutionExpression(self,ptrWrite->rhs,identMap);
}






void IdentifierResolutionPtrReadExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrReadExpr *ptrRead = (struct ASTPtrReadExpr *)expr;

    IdentifierResolutionExpression(self,ptrRead->lhs,identMap);
}



void IdentifierResolutionAddressOfExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAddressOfExpr *addressOf = (struct ASTAddressOfExpr *)expr;
    
    IdentifierResolutionExpression(self,addressOf->rhs,identMap);
}



void IdentifierResolutionFunctionCallExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTFunctionCallExpr *function = (struct ASTFunctionCallExpr *)expr;

    IdentifierResolutionExpression(self,function->base,identMap);    

    for(u64 i = 0; i < function->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&function->arguments,i);
        IdentifierResolutionExpression(self,argument,identMap);
    }

    struct ASTVariableExpr *variableExpr     = ((struct ASTVariableExpr *)function->base->expr);
    char *ident                              = variableExpr->ident.value.data;
    u64 identLength                          = ACHIOR_LABS_STRLEN(ident);
    struct ASTFunctionAttributes *attributes = HashMapGet(&self->functionAttributes,ident,identLength);

    if(ACHIOR_LABS_NOT_NULL(attributes))
    {
        function->attributes = attributes;
    }
    else
    {
        exit(11);
    }
}



void IdentifierResolutionCastExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTCastExpr *cast = (struct ASTCastExpr *)expr;
    
    IdentifierResolutionExpression(self,cast->lhs,identMap);
}



void IdentifierResolutionAssignmentExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAssignmentExpr *assign = (struct ASTAssignmentExpr *)expr;
    
    IdentifierResolutionExpression(self,assign->lhs,identMap);
    IdentifierResolutionExpression(self,assign->rhs,identMap);
}


void IdentifierResolutionBinaryExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTBinaryExpr *binary = (struct ASTBinaryExpr *)expr;

    IdentifierResolutionExpression(self,binary->lhs,identMap);
    IdentifierResolutionExpression(self,binary->rhs,identMap);
}



void IdentifierResolutionUnaryExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTUnaryExpr *unary = (struct ASTUnaryExpr *)expr;
    
    IdentifierResolutionExpression(self,unary->rhs,identMap);
}


void IdentifierResolutionVariableExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    struct ASTVariableExpr *variable = (struct ASTVariableExpr *)expr;

    char *ident                      = variable->ident.value.data;
    u64 identLength                  = ACHIOR_LABS_STRLEN(ident);
    struct IdentifierEntry *entry    = HashMapGet(identMap,ident,identLength);

    if(ACHIOR_LABS_NULL(entry))
    {
        puts("illegal use of an undeclared variable identifier : [error]");
        return;
    }

    variable->ident.value = entry->ident;
}



struct String IdentifierResolutionMakeTmp(struct IdentifierResolution *self)
{
    struct String tmp;
    StringNew(&tmp,50,self->bump);

    char counter = self->globalCounter++;

    char buf[10] = {0};
    ACHIOR_LABS_SNPRINTF(buf,sizeof(buf),"%lu",self->globalCounter);
    
    StringPushBack(&tmp,"__C4C");
    StringPushBack(&tmp,buf);

    return tmp;
}
