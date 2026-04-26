#include "Include/ASTPrint.h"




bool ASTPrintNew(struct ASTPrint *self,struct ASTProgram *ast_program,char *output_file_name)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ast_program        = ast_program;
    self->output_file_handle = ACHIOR_LABS_FOPEN(output_file_name,"w");
    return ACHIOR_LABS_NULL(self->output_file_handle) ? false : true;
}


void ASTPrintProgram(struct ASTPrint *self,struct ASTProgram *ast_program)
{
    if( ACHIOR_LABS_NULL(ast_program))
    {
        return;
    }
    
    
    for(u64 i = 0; i < ast_program->decls.len; i++)
    {
		ASTPrintDecl(self,LinkedListAt(&ast_program->decls,i));
	}

    ACHIOR_LABS_FCLOSE(self->output_file_handle);

}


void ASTPrintDecl(struct ASTPrint *self,struct ASTDeclaration *ast_decl)
{
    if( ACHIOR_LABS_NULL(ast_decl))
    {
        return;
    }

	switch(ast_decl->type)
	{
		case AST_DECLARATION_FUNCTION:
		{
			ASTPrintFunctionDecl(self,ast_decl->decl);
			break;
		}
		default:
		{
			break;
		}
	}

}


void ASTPrintIdentifier(struct ASTPrint *self,struct Token ident)
{
    ACHIOR_LABS_FPRINTF(self->output_file_handle,"%s",ident.value.data);
}



void ASTPrintFunctionDecl(struct ASTPrint *self,struct ASTFunctionDecl *function)
{
    if( ACHIOR_LABS_NULL(function))
    {
        return;
    }

	
    ACHIOR_LABS_FPRINTF(self->output_file_handle,"print fn : \n\treturn type =>  ");
    ASTPrintType(self,function->returnType);
    ACHIOR_LABS_FPRINTF(self->output_file_handle,"  ,  fn ident  => ");
    ASTPrintIdentifier(self,function->ident);

    for(u64 i = 0; i < function->arguments.len; i++)
    {
        ASTPrintFunctionArgument(self,LinkedListAt(&function->arguments,i));
    }

    ASTPrintBlockStmt(self,function->block);
    
}

void ASTPrintFunctionArgument(struct ASTPrint *self,struct ASTFunctionArgument *argument)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }


    ACHIOR_LABS_PRINT("print fn");
    ASTPrintType(self,argument->type);
    ASTPrintIdentifier(self,argument->ident);
}


void ASTPrintGetDataType(struct ASTPrint *self,enum ASTDataType ast_type)
{
    switch(ast_type)
    {
        case AST_DATA_TYPE_I32:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"i32");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown-type");
        }
    }	
}



void ASTPrintType(struct ASTPrint *self,struct ASTType *ast_type)
{
    if( ACHIOR_LABS_NULL(ast_type))
    {
        return;
    }

	ASTPrintGetDataType(self,ast_type->dataType);
}

void ASTPrintBlockStmt(struct ASTPrint *self,struct ASTBlockStmt *ast_block)
{
    for(u64 i = 0; i < ast_block->stmts.len; i++)
    {
        ACHIOR_LABS_FPRINTF(self->output_file_handle,"\n\t\t");
        ASTPrintStmt(self,LinkedListAt(&ast_block->stmts,i));
    }
}


void ASTPrintStmt(struct ASTPrint *self,struct ASTStatement *ast_stmt)
{
    if( ACHIOR_LABS_NULL(ast_stmt))
    {
        return;
    }

	switch(ast_stmt->type)
	{
		case AST_STATEMENT_RETURN:
		{
            ASTPrintReturnStmt(self,ast_stmt->stmt);
			break;
		}
		default:
		{
			break;
		}
	}

}



void ASTPrintReturnStmt(struct ASTPrint *self,struct ASTReturnStmt *ast_stmt)
{
    if( ACHIOR_LABS_NULL(ast_stmt))
    {
        return;
    }

    ACHIOR_LABS_FPRINTF(self->output_file_handle,"return [EXPR] =>  ");
    ASTPrintExpr(self,ast_stmt->expr);
    ACHIOR_LABS_FPRINTF(self->output_file_handle,"\n\n");
}



void ASTPrintExpr(struct ASTPrint *self,struct ASTExpression *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

	switch(expr->type)
    {
        case AST_EXPRESSION_BINARY:
        {
            ASTPrintBinaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            ASTPrintUnaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_LITERAL:
        {
            ASTPrintLiteralExpr(self,expr->expr);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown expression ");
            break;
        }
    }
}


void ASTPrintBinaryExpr(struct ASTPrint *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTBinaryExpr *binary = (struct ASTBinaryExpr *)expr;
    ASTPrintExpr(self,binary->lhs);
    ASTPrintBinaryOperator(self,binary->op);
    ASTPrintExpr(self,binary->rhs);
}



void ASTPrintBinaryOperator(struct ASTPrint *self,enum ASTBinaryOperator op)
{
    switch(op)
    {
        case AST_BINARY_OPERATOR_ADD:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"+");
            break;
        }
        case AST_BINARY_OPERATOR_SUB:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"-");
            break;
        }
        case AST_BINARY_OPERATOR_MUL:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"*");
            break;
        }
        case AST_BINARY_OPERATOR_DIV:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"/");
            break;
        }
        case AST_BINARY_OPERATOR_MOD:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"%%");
            break;
        }
        case AST_BINARY_OPERATOR_LESS:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"<");
            break;
        }
        case AST_BINARY_OPERATOR_LESS_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"<=");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,">");
            break;
        }
        case AST_BINARY_OPERATOR_GREATER_EQUAL:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,">=");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown binary operator");
            break;
        }
    }
}


void ASTPrintUnaryExpr(struct ASTPrint *self,void *expr)
{
    if( ACHIOR_LABS_NULL(expr))
    {
        return;
    }

    struct ASTUnaryExpr *unary = (struct ASTUnaryExpr *)expr;
    ASTPrintUnaryOperator(self,unary->op);
    ASTPrintExpr(self,unary->rhs);
}


void ASTPrintUnaryOperator(struct ASTPrint *self,enum ASTUnaryOperator op)
{
    switch(op)
    {
        case AST_UNARY_OPERATOR_COMPLEMENT:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"~");
            break;
        }
        case AST_UNARY_OPERATOR_NEGATE:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"-");
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown unary operator");
            break;
        }
    }
}


void ASTPrintLiteralExpr(struct ASTPrint *self,void *expr)
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
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"[i32]");
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"%s",literal->literal.value.data);
            break;
        }
        default:
        {
            ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown literal expression");
        }
    }
}
