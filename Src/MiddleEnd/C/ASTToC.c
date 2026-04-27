#include "Include/ASTToC.h"




bool ASTToCNew(struct ASTToC *self,struct ASTProgram *program,char *fileName,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->program    = program;
    self->fileHandle = ACHIOR_LABS_FOPEN(fileName,"w");
    self->bump       = bump;

    if(ACHIOR_LABS_NULL(self->fileHandle))
    {
        return false;
    }

    ASTToCProgram(self,program);

    return true;
}


void ASTToCProgram(struct ASTToC *self,struct ASTProgram *program)
{
    if( ACHIOR_LABS_NULL(program))
    {
        return;
    }
    
    ACHIOR_LABS_FPRINTF(self->fileHandle,"#include <AchiorLabs/C4/Types.h>\n\n");
    
    for(u64 i = 0; i < program->decls.len; i++)
    {
		ASTToCDecl(self,LinkedListAt(&program->decls,i));
	}

    ACHIOR_LABS_FCLOSE(self->fileHandle);

}


void ASTToCDecl(struct ASTToC *self,struct ASTDeclaration *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

	switch(decl->type)
	{
		case AST_DECLARATION_STRUCT:
		{
			ASTToCStructDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_UNION:
		{
			ASTToCUnionDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_SUM:
		{
			ASTToCSumDecl(self,decl->decl);
			break;
		}
		case AST_DECLARATION_FUNCTION:
		{
			ASTToCFunctionDecl(self,decl->decl);
			break;
		}
		default:
		{
			break;
		}
	}

}


void ASTToCIdentifier(struct ASTToC *self,struct Token ident)
{
    ACHIOR_LABS_FPRINTF(self->fileHandle,"%s",ident.value.data);
}



void ASTToCStructDecl(struct ASTToC *self,struct ASTStructDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"\nstruct ");
    ASTToCIdentifier(self,decl->ident);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n{");

    for(u64 i = 0; i < decl->properties.len; i++)
    {
        struct ASTStructProperty *property = LinkedListAt(&decl->properties,i);
        ASTToCStructProperty(self,property);
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n};\n");

}





void ASTToCUnionDecl(struct ASTToC *self,struct ASTUnionDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"\nunion ");
    ASTToCIdentifier(self,decl->ident);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n{");

    for(u64 i = 0; i < decl->properties.len; i++)
    {
        struct ASTStructProperty *property = LinkedListAt(&decl->properties,i);
        ASTToCStructProperty(self,property);
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n};\n");

}


void ASTToCStructProperty(struct ASTToC *self,struct ASTStructProperty *property)
{
    if( ACHIOR_LABS_NULL(property))
    {
        return;
    }

    struct LinkedList arrayBuffer;
    LinkedListNew(&arrayBuffer,self->bump);

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\t");
    ASTToCType(self,property->type,&arrayBuffer);
    ASTToCIdentifier(self,property->ident);

    for(u64 i = 0; i < arrayBuffer.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"[");
        struct ASTExpression *size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size);
        ACHIOR_LABS_FPRINTF(self->fileHandle,"]");
    }
    ACHIOR_LABS_FPRINTF(self->fileHandle,";");
}



void ASTToCSumDecl(struct ASTToC *self,struct ASTSumDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }


    ASTToCSumEnum(self,decl->ident.value.data,decl->variants);
    

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\nstruct ");
    ASTToCIdentifier(self,decl->ident);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n{");

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\tenum %sTag tag;\n",decl->ident.value.data);

    ASTToCSumVariants(self,decl->variants);

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n};\n");

}


char *ASTToCCapitalizeString(struct ASTToC *self,char *source)
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


void ASTToCSumEnum(struct ASTToC *self,char *ident,struct LinkedList variants)
{
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\nenum %sTag\n{\n",ident);

    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        ACHIOR_LABS_FPRINTF(self->fileHandle,"\t%s_TAG_%s,\n",ASTToCCapitalizeString(self,ident),ASTToCCapitalizeString(self,variant->ident.value.data));
        break;
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"};\n");
}




void ASTToCSumVariants(struct ASTToC *self,struct LinkedList variants)
{
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\tunion\n\t{");
    for(u64 i = 0; i < variants.len; i++)
    {
        struct ASTSumVariant *variant = LinkedListAt(&variants,i);

        switch(variant->kind)
        {
            case AST_SUM_VARIANT_UNIT:
            {
                struct ASTType *type = LinkedListAt(&variant->fields,0);
                
                struct LinkedList arrayBuffer;
                
                ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\t\t");
                ASTToCType(self,type,&arrayBuffer);
                ACHIOR_LABS_FPRINTF(self->fileHandle," ");
                ASTToCIdentifier(self,variant->ident);
                
                ACHIOR_LABS_FPRINTF(self->fileHandle,";");
                break;
            }
            case AST_SUM_VARIANT_TUPLE:
            {
                ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\n\t\tstruct\n\t\t{");
                for(u64 i = 0; i < variant->fields.len; i++)
                {
                    struct ASTType *type = LinkedListAt(&variant->fields,i);
                    struct LinkedList arrayBuffer;
                
                    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\t\t\t");
                    ASTToCType(self,type,&arrayBuffer);
                    ACHIOR_LABS_FPRINTF(self->fileHandle," field%lu;",i);
                }

                ACHIOR_LABS_FPRINTF(self->fileHandle,"\t\t\n\t\t}%s;",variant->ident.value.data);
                break;
            }
            case AST_SUM_VARIANT_STRUCT:
            {
                break;
            }
        }
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n\t}data;");
}





void ASTToCFunctionDecl(struct ASTToC *self,struct ASTFunctionDecl *decl)
{
    if( ACHIOR_LABS_NULL(decl))
    {
        return;
    }

    
    if(ACHIOR_LABS_TRUE(decl->attributes->is_static))
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"static ");
    }
	
    struct LinkedList arrayBuffer;
    LinkedListNew(&arrayBuffer,self->bump);

    ASTToCType(self,decl->returnType,&arrayBuffer);
    ACHIOR_LABS_FPRINTF(self->fileHandle," ");
    ASTToCIdentifier(self,decl->ident);

    for(u64 i = 0; i < arrayBuffer.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"[");
        struct ASTExpression *size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size);
        ACHIOR_LABS_FPRINTF(self->fileHandle,"]");
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"(");

    for(u64 i = 0; i < decl->arguments.len; i++)
    {
        ASTToCFunctionArgument(self,LinkedListAt(&decl->arguments,i));
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,")");

    ASTToCBlockStmt(self,decl->block,"");
}



void ASTToCFunctionArgument(struct ASTToC *self,struct ASTFunctionArgument *argument)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }

    struct LinkedList arrayBuffer;
    LinkedListNew(&arrayBuffer,self->bump);

    ASTToCType(self,argument->type,&arrayBuffer);
    ASTToCIdentifier(self,argument->ident);

    for(u64 i = 0; i < arrayBuffer.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"[");
        struct ASTExpression *size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size);
        ACHIOR_LABS_FPRINTF(self->fileHandle,"]");
    }
}


void ASTToCGetDataType(struct ASTToC *self,enum ASTDataType type)
{
    
}


void ASTToCType(struct ASTToC *self,struct ASTType *type,struct LinkedList *arrayBuffer)
{
    if( ACHIOR_LABS_NULL(type))
    {
        return;
    }

    switch(type->dataType)
    {
        case AST_DATA_TYPE_I8:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"i8 ");
            break;
        }
        case AST_DATA_TYPE_I16:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"i16 ");
            break;
        }
        case AST_DATA_TYPE_I32:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"i32 ");
            break;
        }
        case AST_DATA_TYPE_I64:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"i64 ");
            break;
        }
        case AST_DATA_TYPE_U8:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"u8 ");
            break;
        }
        case AST_DATA_TYPE_U16:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"u16 ");
            break;
        }
        case AST_DATA_TYPE_U32:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"u32 ");
            break;
        }
        case AST_DATA_TYPE_U64:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"u64 ");
            break;
        }
        case AST_DATA_TYPE_POINTER:
        {
            struct ASTPointerType *ptrType = (struct ASTPointerType *)type->type;
            ASTToCType(self,ptrType->type,arrayBuffer);
            ACHIOR_LABS_FPRINTF(self->fileHandle,"*");
            break;
        }
        case AST_DATA_TYPE_ARRAY:
        {
            struct ASTArrayType *arrayType = (struct ASTArrayType *)type->type;
            LinkedListPushBack(arrayBuffer,arrayType->size);
            ASTToCType(self,arrayType->type,arrayBuffer);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"unknown-type");
        }
    }	
}

void ASTToCBlockStmt(struct ASTToC *self,struct ASTBlockStmt *block,char *tab)
{
    char newTab[ACHIOR_LABS_STRLEN(tab) + 2];
    ACHIOR_LABS_SNPRINTF(newTab,ACHIOR_LABS_STRLEN(tab) + 2,"%s\t",tab);

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n%s{",tab);
    for(u64 i = 0; i < block->stmts.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"\n%s\t",tab);
        ASTToCStmt(self,LinkedListAt(&block->stmts,i),newTab);
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n%s}\n",tab);
}


void ASTToCStmt(struct ASTToC *self,struct ASTStatement *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

	switch(stmt->type)
	{
		case AST_STATEMENT_RETURN:
		{
            ASTToCReturnStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_LOOP:
		{
            ASTToCLoopStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_WHILE:
		{
            ASTToCWhileStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_BREAK:
		{
            ASTToCBreakStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_CONTINUE:
		{
            ASTToCContinueStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_IF:
		{
            ASTToCIfStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_VAR_DECL:
		{
            ASTToCVariableDeclStmt(self,stmt->stmt,tab);
			break;
		}
        case AST_STATEMENT_EXPRESSION:
		{
            ASTToCExpressionStmt(self,stmt->stmt,tab);
			break;
		}
		default:
		{
			break;
		}
	}

}





void ASTToCExpressionStmt(struct ASTToC *self,struct ASTExpression *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ASTToCExpression(self,stmt);
    ACHIOR_LABS_FPRINTF(self->fileHandle,";");
}



void ASTToCVariableDeclStmt(struct ASTToC *self,struct ASTVariableDecl *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    struct LinkedList arrayBuffer;
    LinkedListNew(&arrayBuffer,self->bump);

    ASTToCType(self,stmt->type,&arrayBuffer);
    ASTToCIdentifier(self,stmt->ident);

    for(u64 i = 0; i < arrayBuffer.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"[");
        struct ASTExpression *size = LinkedListAt(&arrayBuffer,i);
        ASTToCExpression(self,size);
        ACHIOR_LABS_FPRINTF(self->fileHandle,"]");
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle," = ");
    ASTToCVariableDeclInit(self,stmt->init);
    ACHIOR_LABS_FPRINTF(self->fileHandle,";");
}



void ASTToCVariableDeclInit(struct ASTToC *self,struct ASTVariableDeclInit *init)
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
            ASTToCExpression(self,singleInit->expr);
            break;
        }
        case AST_VAR_DECL_INIT_ARRAY_INIT:
        {
            struct ASTVariableDeclArrayInit *arrayInit = (struct ASTVariableDeclArrayInit *)init->init;

            ACHIOR_LABS_FPRINTF(self->fileHandle,"{");

            for(u64 i = 0; i < arrayInit->elements.len; i++)
            {
                struct ASTVariableDeclInit *tmpInit = LinkedListAt(&arrayInit->elements,i);
                ASTToCVariableDeclInit(self,tmpInit);

                if(ACHIOR_LABS_LESS(i,arrayInit->elements.len - 1))
                {
                    ACHIOR_LABS_FPRINTF(self->fileHandle,",");
                }
            }

            ACHIOR_LABS_FPRINTF(self->fileHandle,"}");

            break;
        }
    }

}



void ASTToCIfStmt(struct ASTToC *self,struct ASTIfStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"if(");
    ASTToCExpression(self,stmt->expr);
    ACHIOR_LABS_FPRINTF(self->fileHandle,")");
    ASTToCBlockStmt(self,stmt->block,tab);

    for(u64 i = 0; i < stmt->elifs.len; i++)
    {
        struct ASTIfElif *Elif = LinkedListAt(&stmt->elifs,i);
        ACHIOR_LABS_FPRINTF(self->fileHandle,"%selse if(",tab);
        ASTToCExpression(self,Elif->expr);
        ACHIOR_LABS_FPRINTF(self->fileHandle,")");
        ASTToCBlockStmt(self,Elif->block,tab);
    }

    if(ACHIOR_LABS_NOT_NULL(stmt->else_block))
    {
        ACHIOR_LABS_FPRINTF(self->fileHandle,"%selse",tab);
        ASTToCBlockStmt(self,stmt->else_block->block,tab);
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n");
}


void ASTToCContinueStmt(struct ASTToC *self,struct ASTContinueStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"continue;");
}



void ASTToCBreakStmt(struct ASTToC *self,struct ASTBreakStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"break;");
}


void ASTToCWhileStmt(struct ASTToC *self,struct ASTWhileStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"while(");
    ASTToCExpression(self,stmt->expr);
    ACHIOR_LABS_FPRINTF(self->fileHandle,")");
    ASTToCBlockStmt(self,stmt->block,tab);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n");
}



void ASTToCLoopStmt(struct ASTToC *self,struct ASTLoopStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }


    ACHIOR_LABS_FPRINTF(self->fileHandle,"while(true)");
    ASTToCBlockStmt(self,stmt->block,tab);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"\n");
}



void ASTToCReturnStmt(struct ASTToC *self,struct ASTReturnStmt *stmt,char *tab)
{
    if( ACHIOR_LABS_NULL(stmt))
    {
        return;
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,"return ");
    ASTToCExpression(self,stmt->expr);
    ACHIOR_LABS_FPRINTF(self->fileHandle,";");
}



void ASTToCExpression(struct ASTToC *self,struct ASTExpression *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

	switch(expr->type)
    {
        case AST_EXPRESSION_LITERAL:
        {
            ASTToCLiteralExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_VARIABLE:
        {
            ASTToCVariableExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            ASTToCUnaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_BINARY:
        {
            ASTToCBinaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_ASSIGNMENT:
        {
            ASTToCAssignmentExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_CAST:
        {
            ASTToCCastExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_FUNCTION_CALL:
        {
            ASTToCFunctionCallExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_ADDRESS_OF:
        {
            ASTToCAddressOfExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_READ:
        {
            ASTToCPtrReadExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_WRITE:
        {
            ASTToCPtrWriteExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_OFFSET:
        {
            ASTToCPtrOffsetExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_BYTE_OFFSET:
        {
            ASTToCPtrByteOffsetExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_ADVANCE:
        {
            ASTToCPtrAdvanceExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_PTR_DIFF:
        {
            ASTToCPtrDiffExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_SUBSCRIPT:
        {
            ASTToCSubscriptExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_AS_PTR:
        {
            ASTToCAsPtrExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_LEN:
        {
            ASTToCLenExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_STRUCT_ACCESS:
        {
            //ASTToCStructAccessExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_STRUCT_POINTER_ACCESS:
        {
            //ASTToCStructPointerAccessExpr(self,expr->expr);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"unknown expression ");
            break;
        }
    }
}





void ASTToCLenExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTLenExpr *len = (struct ASTLenExpr *)expr;
    ACHIOR_LABS_FPRINTF(self->fileHandle,"%lu",len->dataType->layout.size);
}



void ASTToCAsPtrExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAsPtrExpr *asPtr = (struct ASTAsPtrExpr *)expr;
    ASTToCExpression(self,asPtr->lhs);
}




void ASTToCSubscriptExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTSubscriptExpr *subscript = (struct ASTSubscriptExpr *)expr;

    ASTToCExpression(self,subscript->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"[");
    ASTToCExpression(self,subscript->index);
    ACHIOR_LABS_FPRINTF(self->fileHandle,"]");
}




void ASTToCPtrDiffExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrDiffExpr *ptrDiff = (struct ASTPtrDiffExpr *)expr;

    ASTToCExpression(self,ptrDiff->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle," - ");
    ASTToCExpression(self,ptrDiff->rhs);
}






void ASTToCPtrAdvanceExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrAdvanceExpr *ptrAdvance = (struct ASTPtrAdvanceExpr *)expr;

    ASTToCExpression(self,ptrAdvance->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle," += ");
    ASTToCExpression(self,ptrAdvance->rhs);
}






void ASTToCPtrByteOffsetExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrByteOffsetExpr *ptrByteOffset = (struct ASTPtrByteOffsetExpr *)expr;

    ACHIOR_LABS_FPRINTF(self->fileHandle,"(((i8 *)");
    ASTToCExpression(self,ptrByteOffset->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle,")");
    ACHIOR_LABS_FPRINTF(self->fileHandle," + ");
    ASTToCExpression(self,ptrByteOffset->rhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle,")");
}







void ASTToCPtrOffsetExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrOffsetExpr *ptrOffset = (struct ASTPtrOffsetExpr *)expr;

    ASTToCExpression(self,ptrOffset->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle," + ");
    ASTToCExpression(self,ptrOffset->rhs);
}





void ASTToCPtrWriteExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrWriteExpr *ptrWrite = (struct ASTPtrWriteExpr *)expr;

    ACHIOR_LABS_FPRINTF(self->fileHandle,"*");
    ASTToCExpression(self,ptrWrite->lhs);
    ACHIOR_LABS_FPRINTF(self->fileHandle," = ");
    ASTToCExpression(self,ptrWrite->rhs);
}






void ASTToCPtrReadExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTPtrReadExpr *ptrRead = (struct ASTPtrReadExpr *)expr;

    ACHIOR_LABS_FPRINTF(self->fileHandle,"*");
    ASTToCExpression(self,ptrRead->lhs);
}



void ASTToCAddressOfExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAddressOfExpr *addressOf = (struct ASTAddressOfExpr *)expr;

    ACHIOR_LABS_FPRINTF(self->fileHandle,"&");
    ASTToCExpression(self,addressOf->rhs);
}



void ASTToCFunctionCallExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTFunctionCallExpr *function = (struct ASTFunctionCallExpr *)expr;

    ASTToCExpression(self,function->base);

    ACHIOR_LABS_FPRINTF(self->fileHandle,"(");

    for(u64 i = 0; i < function->arguments.len; i++)
    {
        struct ASTExpression *argument = LinkedListAt(&function->arguments,i);
        ASTToCExpression(self,argument);
    }

    ACHIOR_LABS_FPRINTF(self->fileHandle,")");

}



void ASTToCCastExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTCastExpr *cast = (struct ASTCastExpr *)expr;

    ACHIOR_LABS_FPRINTF(self->fileHandle,"(");
    ASTToCType(self,cast->dataType,NULL);
    ACHIOR_LABS_FPRINTF(self->fileHandle,")");
    ASTToCExpression(self,cast->lhs);
}



void ASTToCAssignmentExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTAssignmentExpr *assign = (struct ASTAssignmentExpr *)expr;
    ASTToCExpression(self,assign->lhs);
    ASTToCAssignmentOperator(self,assign->op);
    ASTToCExpression(self,assign->rhs);
}



void ASTToCAssignmentOperator(struct ASTToC *self,enum ASTAssignmentOperator op)
{
    switch(op)
    {
        case AST_ASSIGNMENT_OPERATOR_ADD:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," += ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_SUB:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," -= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_MUL:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," *= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_DIV:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," /= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR_MOD:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," %%= ");
            break;
        }
        case AST_ASSIGNMENT_OPERATOR:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," = ");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," unknown-assignmet-operator ");
            break;
        }
    }
}


void ASTToCBinaryExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTBinaryExpr *binary = (struct ASTBinaryExpr *)expr;
    ASTToCExpression(self,binary->lhs);
    ASTToCBinaryOperator(self,binary->op);
    ASTToCExpression(self,binary->rhs);
}



void ASTToCBinaryOperator(struct ASTToC *self,enum ASTBinaryOperator op)
{
    switch(op)
    {
        case AST_BINARY_OPERATOR_ADD:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," + ");
            break;
        }
        case AST_BINARY_OPERATOR_SUB:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," - ");
            break;
        }
        case AST_BINARY_OPERATOR_MUL:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," * ");
            break;
        }
        case AST_BINARY_OPERATOR_DIV:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," / ");
            break;
        }
        case AST_BINARY_OPERATOR_MOD:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," %% ");
            break;
        }
        case AST_BINARY_OPERATOR_LESS:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," < ");
            break;
        }
        case AST_BINARY_OPERATOR_LESS_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," <= ");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," > ");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle," >= ");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"unknown binary operator");
            break;
        }
    }
}


void ASTToCUnaryExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTUnaryExpr *unary = (struct ASTUnaryExpr *)expr;
    ASTToCUnaryOperator(self,unary->op);
    ASTToCExpression(self,unary->rhs);
}


void ASTToCUnaryOperator(struct ASTToC *self,enum ASTUnaryOperator op)
{
    switch(op)
    {
        case AST_UNARY_OPERATOR_COMPLEMENT:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"~");
            break;
        }
        case AST_UNARY_OPERATOR_NEGATE:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"-");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"unknown unary operator");
            break;
        }
    }
}



void ASTToCVariableExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }


    struct ASTVariableExpr *variable = (struct ASTVariableExpr *)expr;
    ASTToCIdentifier(self,variable->ident);
}

void ASTToCLiteralExpr(struct ASTToC *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    //ACHIOR_LABS_PRINT("literal");
    struct ASTLiteralExpr *literal = (struct ASTLiteralExpr *)expr;

    switch(literal->type)
    {
        case AST_LITERAL_I32:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"%s",literal->literal.value.data);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->fileHandle,"unknown literal expression");
        }
    }
}
