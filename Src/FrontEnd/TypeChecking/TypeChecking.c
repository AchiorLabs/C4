#include "Include/TypeChecking.h"



int align(int size,int alignment)
{
    return (size + (alignment - 1)) & ~(alignment - 1);
}



u64 max(u64 num1,u64 num2)
{
    return num1 > num2 ? num1 : num2;
}




bool StructMemberEntryNew(struct StructMemberEntry *self,struct String ident,struct ASTType *type,u64 offset)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ident  = ident;
    self->type   = type;
    self->offset = offset;

    return true;
}



bool StructEntryNew(struct StructEntry *self,struct String ident,struct Layout layout,struct HashMap members)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ident   = ident;
    self->layout  = layout;
    self->members = members;

    return true;
}




bool SymbolNew(struct Symbol *self,enum SymbolKind kind,struct String ident,struct String trueIdent,struct ASTType *type)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }


    self->kind      = kind;
    self->ident     = ident;
    self->trueIdent = trueIdent;
    self->type      = type;

    return true;
}





bool TypeCheckingNew(struct TypeChecking *self,struct ASTProgram *program,u64 globalCounter,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->program       = program;
    self->globalCounter = globalCounter;
    self->bump          = bump;

    HashMapNew(&self->symbols,10,self->bump);

    TypeCheckingProgram(self,program);

    return true;
}




bool TypeCheckingType(struct TypeChecking *self,struct ASTType *type)
{
    if( ACHIOR_LABS_NULL(type))
    {
        return false;
    }

    switch(type->dataType)
    {
        case AST_DATA_TYPE_VOID:
        case AST_DATA_TYPE_I8:
        case AST_DATA_TYPE_I16:
        case AST_DATA_TYPE_I32:
        case AST_DATA_TYPE_I64:
        case AST_DATA_TYPE_U8:
        case AST_DATA_TYPE_U16:
        case AST_DATA_TYPE_U32:
        case AST_DATA_TYPE_U64:
        {
            return true;
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            struct ASTPointerType *ptrType = (struct ASTPointerType *)type->type;
            return TypeCheckingType(self,ptrType->type);
            break;
        }
        case AST_DATA_TYPE_ARRAY:
        {
            struct ASTArrayType *arrayType = (struct ASTArrayType *)type->type;
            return TypeCheckingType(self,arrayType->type);
            break;
        }
        case AST_DATA_TYPE_STRUCT:
        {
            struct ASTStructType *structType = (struct ASTStructType *)type->type;
            return true;
            break;
        }
        default:
        {
            printf("%d [type]\n",type->dataType);
            return false;
            break;
        }
    }	
}



u64 TypeCheckingDecodeSize(struct TypeChecking *self,struct ASTExpression *expr)
{
    switch(expr->type)
    {
        case AST_EXPRESSION_LITERAL:
        {
            struct ASTLiteralExpr *literalExpr = (struct ASTLiteralExpr *)expr->expr;
            return (u64)atol(literalExpr->literal.value.data);
            break;
        }
    }

    return 0;
}




bool TypeCheckingBuildLayout(struct TypeChecking *self,struct ASTType *type)
{
    u64 size      = 0;
    u64 alignment = 0;
    switch(type->dataType)
    {
        case AST_DATA_TYPE_VOID:
        case AST_DATA_TYPE_CHAR:
        case AST_DATA_TYPE_I8:
        case AST_DATA_TYPE_U8:
        {
            size      = 1;
            alignment = 1;
            LayoutNew(&type->layout,size,alignment);
            break;
        }
        case AST_DATA_TYPE_I16:
        case AST_DATA_TYPE_U16:
        {
            size      = 2;
            alignment = 2;
            LayoutNew(&type->layout,size,alignment);
            break;
        }
        case AST_DATA_TYPE_I32:
        case AST_DATA_TYPE_U32:
        {
            size      = 4;
            alignment = 4;
            LayoutNew(&type->layout,size,alignment);
            break;
        }
        case AST_DATA_TYPE_I64:
        case AST_DATA_TYPE_U64:
        {
            size      = 8;
            alignment = 8;
            LayoutNew(&type->layout,size,alignment);
            break;
        }
        case AST_DATA_TYPE_STRING:
        {
            size      = 8;
            alignment = 8;
            LayoutNew(&type->layout,size,alignment);
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            size      = 8;
            alignment = 8;
            LayoutNew(&type->layout,size,alignment);

            struct ASTPointerType *astPtr = (struct ASTPointerType *)type->type;
            TypeCheckingBuildLayout(self,astPtr->type);

            break;
        }
        case AST_DATA_TYPE_ARRAY:
        {
            struct ASTArrayType *astArray = (struct ASTArrayType *)type->type;
            TypeCheckingBuildLayout(self,astArray->type);

            size      = TypeCheckingDecodeSize(self,astArray->size);
            alignment = astArray->type->layout.alignment;

            LayoutNew(&astArray->layout,size,alignment);
            LayoutNew(&type->layout,size,alignment);
            
            break;
        }
        case AST_DATA_TYPE_STRUCT:
        {
            struct ASTStructType *structType = (struct ASTStructType *)type->type;
            struct String structIdent        = structType->ident.value;
            struct Symbol *symbol            = HashMapGet(&self->symbols,structIdent.data,structIdent.size);

            if(ACHIOR_LABS_EQUAL(symbol->kind,SYMBOL_STRUCT))
            {
                LayoutNew(&type->layout,symbol->type->layout.size,symbol->type->layout.alignment);
            }
            else
            {
                exit(9);
            }
            
            break;
        }
        default:
        {
            puts("unknown layout");
            printf("%d [type]\n",type->dataType);
            //exit(2);
            return false;
            break;
        }
    }

    return true;
}




void TypeCheckingProgram(struct TypeChecking *self,struct ASTProgram *program)
{
    if( ACHIOR_LABS_NULL(program))
    {
        return;
    }
 
    
    for(u64 i = 0; i < program->decls.len; i++)
    {
		TypeCheckingDeclaration(self,LinkedListAt(&program->decls,i));
	}

    puts("type checker done");
}


void TypeCheckingDeclaration(struct TypeChecking *self,struct ASTDeclaration *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

	switch(decl->type)
	{
		case AST_DECLARATION_STRUCT:
		{
			TypeCheckingStructDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_UNION:
		{
			TypeCheckingUnionDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_IMPL:
		{
			TypeCheckingImplDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_SUM:
		{
            break;
			//TypeCheckingSumDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_FUNCTION:
		{
			TypeCheckingFunctionDecl(self,decl->decl);
			break;
		}
		default:
		{
			break;
		}
	}
}






void TypeCheckingStructDecl(struct TypeChecking *self,struct ASTStructDecl *decl)
{
    if(ACHIOR_LABS_ZERO(decl->properties.len))
    {
        return;
    }

    struct Layout structLayout;
    LayoutNew(&structLayout,0,1);

    struct HashMap members;
    HashMapNew(&members,10,self->bump);

    for(u64 i = 0; i < decl->properties.len; i++)
    {
        struct ASTStructProperty *property = LinkedListAt(&decl->properties,i);

        if(ACHIOR_LABS_NULL(property))
        {
            continue;
        }

        if(! TypeCheckingType(self,property->type))
        {
            puts(" invalid argument type in struct ");
            //exit(9);
        }

        struct String memberIdent = property->ident.value;


        TypeCheckingBuildLayout(self,property->type);
        struct Layout layout = property->type->layout; 
        u64 memberOffset     = align(structLayout.size,layout.alignment);

        struct StructMemberEntry *member = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct StructMemberEntry,1);
        StructMemberEntryNew(member,property->ident.value,property->type,memberOffset);
        HashMapAdd(&members,memberIdent.data,memberIdent.size,member);

        structLayout.alignment = max(structLayout.alignment,layout.alignment);
        structLayout.size      = memberOffset + layout.size;
    }

    structLayout.size = align(structLayout.size,structLayout.alignment);

    struct StructEntry structEntry;
    StructEntryNew(&structEntry,decl->ident.value,structLayout,members);


    struct String ident     = decl->ident.value;
    struct String trueIdent = ident;


    struct ASTStructType *structType = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTStructType,1);
    ASTStructTypeNew(structType,decl->ident,structLayout);

    struct ASTType *type = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTType,1);
    ASTTypeNew(type,AST_DATA_TYPE_STRUCT,structType);

    struct Symbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Symbol,1);
    SymbolNew(symbol,SYMBOL_STRUCT,ident,trueIdent,type);

    symbol->entry = structEntry;
    
    HashMapAdd(&self->symbols,ident.data,ident.size,symbol);
}






void TypeCheckingUnionDecl(struct TypeChecking *self,struct ASTUnionDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


}



void TypeCheckingImplDecl(struct TypeChecking *self,struct ASTImplDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    for(u64 i = 0; i < decl->methods.len; i++)
    {
        struct ASTFunctionDecl *method = LinkedListAt(&decl->methods,i);
        TypeCheckingFunctionDecl(self,method);
    }
}


void TypeCheckingFunctionDecl(struct TypeChecking *self,struct ASTFunctionDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    bool status = TypeCheckingType(self,decl->returnType);
    
    if(ACHIOR_LABS_FALSE(status))
    {
        puts("invalid function return type");
        //exit(1);
    }


    TypeCheckingBuildLayout(self,decl->returnType);


    for(u64 i = 0; i < decl->arguments.len; i++)
    {
        TypeCheckingFunctionArgument(self,LinkedListAt(&decl->arguments,i));
    }


    struct String ident                  = decl->ident.value;
    struct String trueIdent              = ident;

    struct ASTFunctionType *functionType = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTFunctionType,1);
    ASTFunctionTypeNew(functionType,decl->returnType,decl->arguments);

    struct ASTType *type = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTType,1);
    ASTTypeNew(type,AST_DATA_TYPE_FUNCTION,functionType);

    struct Symbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Symbol,1);
    SymbolNew(symbol,SYMBOL_FUNCTION,ident,trueIdent,type);

    
    HashMapAdd(&self->symbols,ident.data,ident.size,symbol);

    if(ACHIOR_LABS_NOT_NULL(decl->block))
    {
        TypeCheckingBlockStmt(self,decl->block);
    }
}




void TypeCheckingFunctionArgument(struct TypeChecking *self,struct ASTFunctionArgument *argument)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }

    bool status = TypeCheckingType(self,argument->type);
    
    if(ACHIOR_LABS_FALSE(status))
    {
        puts("invalid function argument type");
        //exit(1);
    }


    TypeCheckingBuildLayout(self,argument->type);


    struct String ident     = argument->ident.value;
    struct String trueIdent = ident;

    struct Symbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Symbol,1);
    SymbolNew(symbol,SYMBOL_VARIABLE,ident,trueIdent,argument->type);
    
    HashMapAdd(&self->symbols,ident.data,ident.size,symbol);
}




void TypeCheckingBlockStmt(struct TypeChecking *self,struct ASTBlockStmt *block)
{
    for(u64 i = 0; i < block->stmts.len; i++)
    {
        TypeCheckingStmt(self,LinkedListAt(&block->stmts,i));
    }   
}


void TypeCheckingStmt(struct TypeChecking *self,struct ASTStatement *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(stmt->type)
	{
		case AST_STATEMENT_RETURN:
		{
            TypeCheckingReturnStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            TypeCheckingLoopStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            TypeCheckingWhileStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            TypeCheckingBreakStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            TypeCheckingContinueStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_IF:
		{
            TypeCheckingIfStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            TypeCheckingVariableDeclStmt(self,stmt->stmt);
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            TypeCheckingExpressionStmt(self,stmt->stmt);
			break;
		}
		default:
		{
			break;
		}
	}

}





void TypeCheckingExpressionStmt(struct TypeChecking *self,struct ASTExpression *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    TypeCheckingExpression(self,stmt);
}



void TypeCheckingVariableDeclStmt(struct TypeChecking *self,struct ASTVariableDecl *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    bool status = TypeCheckingType(self,stmt->type);
    
    if(ACHIOR_LABS_FALSE(status))
    {
        puts("invalid variable declaration type");
        //exit(1);
    }


    TypeCheckingBuildLayout(self,stmt->type);


    struct String ident     = stmt->ident.value;
    struct String trueIdent = ident;

    struct Symbol *symbol = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Symbol,1);
    SymbolNew(symbol,SYMBOL_VARIABLE,ident,trueIdent,stmt->type);
    
    HashMapAdd(&self->symbols,ident.data,ident.size,symbol);


    if(ACHIOR_LABS_NOT_NULL(stmt->init))
    {
        TypeCheckingVariableDeclInit(self,stmt->init);
    }
}



void TypeCheckingVariableDeclInit(struct TypeChecking *self,struct ASTVariableDeclInit *init)
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

            TypeCheckingExpression(self,singleInit->expr);
            break;
        }
        case AST_VAR_DECL_INIT_ARRAY_INIT:
        {
            struct ASTVariableDeclArrayInit *arrayInit = (struct ASTVariableDeclArrayInit *)init->init;

            for(u64 i = 0; i < arrayInit->elements.len; i++)
            {
                struct ASTVariableDeclInit *tmpInit = LinkedListAt(&arrayInit->elements,i);

                TypeCheckingVariableDeclInit(self,tmpInit);
            }
            break;
        }
    }

}



void TypeCheckingIfStmt(struct TypeChecking *self,struct ASTIfStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
    
    TypeCheckingExpression(self,stmt->expr);
    TypeCheckingBlockStmt(self,stmt->block);

    for(u64 i = 0; i < stmt->elifs.len; i++)
    {
        struct ASTIfElif *Elif = LinkedListAt(&stmt->elifs,i);

        TypeCheckingExpression(self,Elif->expr);   
        TypeCheckingBlockStmt(self,Elif->block);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->else_block))
    {
        
        TypeCheckingBlockStmt(self,stmt->else_block->block);
    }
}


void TypeCheckingContinueStmt(struct TypeChecking *self,struct ASTContinueStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}



void TypeCheckingBreakStmt(struct TypeChecking *self,struct ASTBreakStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }
}


void TypeCheckingWhileStmt(struct TypeChecking *self,struct ASTWhileStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    TypeCheckingExpression(self,stmt->expr);
    TypeCheckingBlockStmt(self,stmt->block);
}



void TypeCheckingLoopStmt(struct TypeChecking *self,struct ASTLoopStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    TypeCheckingBlockStmt(self,stmt->block);
}



void TypeCheckingReturnStmt(struct TypeChecking *self,struct ASTReturnStmt *stmt)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    TypeCheckingExpression(self,stmt->expr);    
}



void TypeCheckingExpression(struct TypeChecking *self,struct ASTExpression *expr)
{    
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    

	switch(expr->type)
    {
        case AST_EXPRESSION_LITERAL:
        {
            struct ASTLiteralExpr *innerExpr = (struct ASTLiteralExpr *)expr->expr;
            TypeCheckingLiteralExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_VARIABLE:
        {
            struct ASTVariableExpr *innerExpr = (struct ASTVariableExpr *)expr->expr;
            TypeCheckingVariableExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            struct ASTUnaryExpr *innerExpr = (struct ASTUnaryExpr *)expr->expr;
            TypeCheckingUnaryExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            struct ASTBinaryExpr *innerExpr = (struct ASTBinaryExpr *)expr->expr;
            TypeCheckingBinaryExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            struct ASTAssignmentExpr *innerExpr = (struct ASTAssignmentExpr *)expr->expr;
            TypeCheckingAssignmentExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_CAST:
        {
            struct ASTCastExpr *innerExpr = (struct ASTCastExpr *)expr->expr;
            TypeCheckingCastExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            struct ASTFunctionCallExpr *innerExpr = (struct ASTFunctionCallExpr *)expr->expr;
            TypeCheckingFunctionCallExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_ADDRESS_OF:
        {
            struct ASTAddressOfExpr *innerExpr = (struct ASTAddressOfExpr *)expr->expr;
            TypeCheckingAddressOfExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_READ:
        {
            struct ASTPtrReadExpr *innerExpr = (struct ASTPtrReadExpr *)expr->expr;
            TypeCheckingPtrReadExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_WRITE:
        {
            struct ASTPtrWriteExpr *innerExpr = (struct ASTPtrWriteExpr *)expr->expr;
            TypeCheckingPtrWriteExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_OFFSET:
        {
            struct ASTPtrOffsetExpr *innerExpr = (struct ASTPtrOffsetExpr *)expr->expr;
            TypeCheckingPtrOffsetExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_BYTE_OFFSET:
        {
            struct ASTPtrByteOffsetExpr *innerExpr = (struct ASTPtrByteOffsetExpr *)expr->expr;
            TypeCheckingPtrByteOffsetExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_ADVANCE:
        {
            struct ASTPtrAdvanceExpr *innerExpr = (struct ASTPtrAdvanceExpr *)expr->expr;
            TypeCheckingPtrAdvanceExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_PTR_DIFF:
        {
            struct ASTPtrDiffExpr *innerExpr = (struct ASTPtrDiffExpr *)expr->expr;
            TypeCheckingPtrDiffExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_SUBSCRIPT:
        {
            struct ASTSubscriptExpr *innerExpr = (struct ASTSubscriptExpr *)expr->expr;
            TypeCheckingSubscriptExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_AS_PTR:
        {
            struct ASTAsPtrExpr *innerExpr = (struct ASTAsPtrExpr *)expr->expr;
            TypeCheckingAsPtrExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_LEN:
        {
            struct ASTLenExpr *innerExpr = (struct ASTLenExpr *)expr->expr;
            TypeCheckingLenExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            struct ASTStructAccessExpr *innerExpr = (struct ASTStructAccessExpr *)expr->expr;
            //TypeCheckingStructAccessExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            struct ASTStructPointerAccessExpr *innerExpr = (struct ASTStructPointerAccessExpr *)expr->expr;
            //TypeCheckingStructPointerAccessExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        case AST_EXPRESSION_METHOD:
        {
            struct ASTMethodExpr *innerExpr = (struct ASTMethodExpr *)expr->expr;
            TypeCheckingMethodExpr(self,innerExpr);
            expr->dataType = innerExpr->dataType;
            break;
        }
        default:
        {
            
            break;
        }
    }
}





void TypeCheckingMethodExpr(struct TypeChecking *self,struct ASTMethodExpr *expr)
{
    puts("hm");
    TypeCheckingExpression(self,expr->lhs);
    return;

    for(u64 i = 0; i < expr->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&expr->arguments,i);
        TypeCheckingExpression(self,argument);
    }

    /**
    switch(expr->lhs->dataType->dataType)
    {
        case AST_DATA_TYPE_STRUCT:
        {
            switch(expr->lhs->type)
            {
                case AST_EXPRESSION_VARIABLE:
                {
                    struct ASTType *type             = expr->lhs->dataType;
                    struct ASTStructType *structType = type->type;

                    struct String structIdent        = structType->ident.value;

                    struct Symbol *symbol            = HashMapGet(&self->symbols,structIdent.data,structIdent.size);

                    if(ACHIOR_LABS_NULL(symbol))
                    {
                        puts(" struct access on an unknown struct type is illegal ");
                        //exit(2);
                    }

                    if(ACHIOR_LABS_NOT_EQUAL(symbol->kind,SYMBOL_STRUCT))
                    {
                        puts(" struct access on a non-struct type is illegal ");
                        //exit(2);
                    }

                    struct StructEntry structEntry        = symbol->entry;
                    struct String memberIdent             = expr->member.value;
                    struct StructMemberEntry *memberEntry = HashMapGet(&structEntry.members,memberIdent.data,memberIdent.size);

                    if(ACHIOR_LABS_NULL(memberEntry))
                    {
                        puts("trying to access an undeclared member on a struct type is illegal ");
                        //exit(9);
                    }

                    //printf("member.offset : %lu\n",member.offset);

                    expr->dataType  = memberEntry->type;
                    expr->offset    = memberEntry->offset;

                    //printf("member.offset : %lu\n",expr->offset);

                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            puts("attempting to . (struct access) on a non-struct type is invalid ");
            //return NULL;
            break;
        }
    }

    */
    //return expr->dataType;
}








void TypeCheckingStructPointerAccessExpr(struct TypeChecking *self,struct ASTStructPointerAccessExpr *expr)
{
    TypeCheckingExpression(self,expr->lhs);
    switch(expr->lhs->dataType->dataType)
    {
        case AST_DATA_TYPE_STRUCT:
        {
            puts("ai");
            switch(expr->lhs->type)
            {
                case AST_EXPRESSION_VARIABLE:
                {
                    struct ASTType *type             = expr->lhs->dataType;
                    struct ASTStructType *structType = type->type;

                    struct String structIdent        = structType->ident.value;

                    struct Symbol *symbol            = HashMapGet(&self->symbols,structIdent.data,structIdent.size);

                    if(ACHIOR_LABS_NULL(symbol))
                    {
                        puts(" struct access on an unknown struct type is illegal ");
                        //exit(2);
                    }

                    if(ACHIOR_LABS_NOT_EQUAL(symbol->kind,SYMBOL_STRUCT))
                    {
                        puts(" struct access on a non-struct type is illegal ");
                        //exit(2);
                    }

                    struct StructEntry structEntry        = symbol->entry;
                    struct String memberIdent             = expr->member.value;
                    struct StructMemberEntry *memberEntry = HashMapGet(&structEntry.members,memberIdent.data,memberIdent.size);

                    if(ACHIOR_LABS_NULL(memberEntry))
                    {
                        puts("trying to access an undeclared member on a struct type is illegal ");
                        //exit(9);
                    }

                    //printf("member.offset : %lu\n",member.offset);

                    expr->dataType  = memberEntry->type;
                    expr->offset    = memberEntry->offset;

                    //printf("member.offset : %lu\n",expr->offset);

                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            puts("attempting to . (struct access) on a non-struct type is invalid ");
            //return NULL;
            break;
        }
    }

    //return expr->dataType;
}







void TypeCheckingStructAccessExpr(struct TypeChecking *self,struct ASTStructAccessExpr *expr)
{
    TypeCheckingExpression(self,expr->lhs);
    switch(expr->lhs->dataType->dataType)
    {
        case AST_DATA_TYPE_STRUCT:
        {
            puts("ai");
            switch(expr->lhs->type)
            {
                case AST_EXPRESSION_VARIABLE:
                {
                    struct ASTType *type             = expr->lhs->dataType;
                    struct ASTStructType *structType = type->type;

                    struct String structIdent        = structType->ident.value;

                    struct Symbol *symbol            = HashMapGet(&self->symbols,structIdent.data,structIdent.size);

                    if(ACHIOR_LABS_NULL(symbol))
                    {
                        puts(" struct access on an unknown struct type is illegal ");
                        //exit(2);
                    }

                    if(ACHIOR_LABS_NOT_EQUAL(symbol->kind,SYMBOL_STRUCT))
                    {
                        puts(" struct access on a non-struct type is illegal ");
                        //exit(2);
                    }

                    struct StructEntry structEntry        = symbol->entry;
                    struct String memberIdent             = expr->member.value;
                    struct StructMemberEntry *memberEntry = HashMapGet(&structEntry.members,memberIdent.data,memberIdent.size);

                    if(ACHIOR_LABS_NULL(memberEntry))
                    {
                        puts("trying to access an undeclared member on a struct type is illegal ");
                        //exit(9);
                    }

                    //printf("member.offset : %lu\n",member.offset);

                    expr->dataType  = memberEntry->type;
                    expr->offset    = memberEntry->offset;

                    //printf("member.offset : %lu\n",expr->offset);

                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            puts("attempting to . (struct access) on a non-struct type is invalid ");
            //return NULL;
            break;
        }
    }

    //return expr->dataType;
}




void TypeCheckingLenExpr(struct TypeChecking *self,struct ASTLenExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->lhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}



void TypeCheckingAsPtrExpr(struct TypeChecking *self,struct ASTAsPtrExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    TypeCheckingExpression(self,expr->lhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}




void TypeCheckingSubscriptExpr(struct TypeChecking *self,struct ASTSubscriptExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->lhs);    
    TypeCheckingExpression(self,expr->index);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}




void TypeCheckingPtrDiffExpr(struct TypeChecking *self,struct ASTPtrDiffExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}






void TypeCheckingPtrAdvanceExpr(struct TypeChecking *self,struct ASTPtrAdvanceExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}






void TypeCheckingPtrByteOffsetExpr(struct TypeChecking *self,struct ASTPtrByteOffsetExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}







void TypeCheckingPtrOffsetExpr(struct TypeChecking *self,struct ASTPtrOffsetExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}





void TypeCheckingPtrWriteExpr(struct TypeChecking *self,struct ASTPtrWriteExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}






void TypeCheckingPtrReadExpr(struct TypeChecking *self,struct ASTPtrReadExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    TypeCheckingExpression(self,expr->lhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}



void TypeCheckingAddressOfExpr(struct TypeChecking *self,struct ASTAddressOfExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    
    TypeCheckingExpression(self,expr->rhs);
    expr->dataType = expr->rhs->dataType;

    //return expr->dataType;
}



void TypeCheckingFunctionCallExpr(struct TypeChecking *self,struct ASTFunctionCallExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    if(ACHIOR_LABS_NOT_EQUAL(expr->base->type,AST_EXPRESSION_VARIABLE))
    {
        puts("expected an identifier as the function name [error]");
        //exit(3);
    }

    TypeCheckingExpression(self,expr->base);    

    struct ASTVariableExpr *variableExpr = ((struct ASTVariableExpr *)expr->base->expr);
    struct String ident                  = variableExpr->ident.value;
    struct Symbol *symbol                = HashMapGet(&self->symbols,ident.data,ident.size);

    if(ACHIOR_LABS_NULL(symbol))
    {
        puts("unknown function identifier");
        //exit(3);
    }

    if(ACHIOR_LABS_NOT_EQUAL(symbol->kind,SYMBOL_FUNCTION))
    {
        puts("non-function identifier used as a function");
        //exit(3);
    }


    struct ASTFunctionType *functionType = symbol->type->type;

    if(ACHIOR_LABS_NOT_EQUAL(expr->arguments.len,functionType->arguments.len))
    {
        puts(("function called with non-matching[invalid] number of arguments"));
        //exit(3);
    }


    for(u64 i = 0; i < expr->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&expr->arguments,i);
        TypeCheckingExpression(self,argument);
    }

    expr->dataType = functionType->returnType;

    //return expr->dataType;
}



void TypeCheckingCastExpr(struct TypeChecking *self,struct ASTCastExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    

    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingType(self,expr->dataType);

    //return expr->dataType;
}



void TypeCheckingAssignmentExpr(struct TypeChecking *self,struct ASTAssignmentExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}


void TypeCheckingBinaryExpr(struct TypeChecking *self,struct ASTBinaryExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    TypeCheckingExpression(self,expr->lhs);
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->lhs->dataType;

    //return expr->dataType;
}



void TypeCheckingUnaryExpr(struct TypeChecking *self,struct ASTUnaryExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }
    
    TypeCheckingExpression(self,expr->rhs);

    expr->dataType = expr->rhs->dataType;

    //return expr->dataType;
}


void TypeCheckingVariableExpr(struct TypeChecking *self,struct ASTVariableExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    struct String ident   = expr->ident.value;
    struct Symbol *symbol = HashMapGet(&self->symbols,ident.data,ident.size);

    if(ACHIOR_LABS_NULL(symbol))
    {
        puts("illegal use of an undeclared variable identifier : [error]");
        //exit(2);
        return;
    }

    if(ACHIOR_LABS_NOT_EQUAL(symbol->kind,SYMBOL_VARIABLE))
    {
        puts("non-variable identifier used as a variable");
        //exit(3);
    }

    expr->dataType = symbol->type;

    //return expr->dataType;
}







void TypeCheckingLiteralExpr(struct TypeChecking *self,struct ASTLiteralExpr *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    enum ASTLiteralType type = AST_LITERAL_NONE;

    switch(expr->type)
    {
        case AST_LITERAL_CHARACTER:
        {
            type = AST_DATA_TYPE_CHAR;
            break;
        }
        case AST_LITERAL_I32:
        {
            type = AST_DATA_TYPE_I32;
            break;
        }
        case AST_LITERAL_I64:
        {
            type = AST_DATA_TYPE_I64;
            break;
        }
        case AST_LITERAL_STRING:
        {
            type = AST_DATA_TYPE_STRING;
            break;
        }
    }

    expr->dataType = TypeCheckingBuildBuiltIn(self,type);

    //return expr->dataType;
}












struct ASTType *TypeCheckingBuildBuiltIn(struct TypeChecking *self,enum ASTDataType dataType)
{
    struct Layout layout  = TypeCheckingGetBuiltInLayout(self,dataType);
    struct ASTType *type  = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ASTType,1);
    ASTTypeNew(type,dataType,NULL);
    type->layout = layout;

    return type;
}







struct Layout TypeCheckingGetBuiltInLayout(struct TypeChecking *self,enum ASTDataType type)
{
    int size = 0;
    int alignment = 0;

    switch(type)
    {
        case AST_DATA_TYPE_I8:
        case AST_DATA_TYPE_U8:
        {
            size      = 1;
            alignment = 1;
            break;
        }
        case AST_DATA_TYPE_I16:
        case AST_DATA_TYPE_U16:
        {
            size      = 2;
            alignment = 2;
            break;
        }
        case AST_DATA_TYPE_I32:
        case AST_DATA_TYPE_U32:
        {
            size      = 4;
            alignment = 4;
            break;
        }
        case AST_DATA_TYPE_I64:
        case AST_DATA_TYPE_U64:
        {
            size      = 8;
            alignment = 8;
            break;
        }
    }
    
    struct Layout layout;
    LayoutNew(&layout,size,alignment);

    return layout;
}






bool TypeCheckingIsLvalue(struct TypeChecking *self,struct ASTExpression *expr)
{
    switch(expr->type)
    {
        case AST_EXPRESSION_VARIABLE:
        case AST_EXPRESSION_STRUCT_ACCESS:
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






