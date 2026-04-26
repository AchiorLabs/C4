#include "Include/TreeWalker.h"




bool TreeWalkerValueNew(struct TreeWalkerValue *self,enum TreeWalkerValueType type,void *value)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->type  = type;
    self->value = value;
}



bool TreeWalkerNew(struct TreeWalker *self,struct ASTProgram *ast_program,char *output_file_name)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ast_program        = ast_program;
    //self->output_file_handle = ACHIOR_LABS_FOPEN(output_file_name,"w");
    return ACHIOR_LABS_NULL(self->output_file_handle) ? false : true;
}


void TreeWalkerProgram(struct TreeWalker *self,struct ASTProgram *ast_program)
{
    if( ACHIOR_LABS_NULL(ast_program))
    {
        return;
    }
    
    
    for(u64 i = 0; i < ast_program->decls.len; i++)
    {
		TreeWalkerDecl(self,LinkedListAt(&ast_program->decls,i));
	}

    //ACHIOR_LABS_FCLOSE(self->output_file_handle);
}


void TreeWalkerDecl(struct TreeWalker *self,struct ASTDeclaration *ast_decl)
{
    if( ACHIOR_LABS_NULL(ast_decl))
    {
        return;
    }

	switch(ast_decl->type)
	{
		case AST_DECLARATION_FUNCTION:
		{
			TreeWalkerFunctionDecl(self,ast_decl->decl);
			break;
		}
		default:
		{
			break;
		}
	}

}


void TreeWalkerIdentifier(struct TreeWalker *self,struct Token ident)
{
    //ACHIOR_LABS_FPRINTF(self->output_file_handle,"%s",ident.value.data);
}



void TreeWalkerFunctionDecl(struct TreeWalker *self,struct ASTFunctionDecl *function)
{
    if( ACHIOR_LABS_NULL(function))
    {
        return;
    }

	
    //ACHIOR_LABS_FPRINTF(self->output_file_handle,"print fn : \n\treturn type =>  ");
    ////TreeWalkerType(self,function->returnType);
    //ACHIOR_LABS_FPRINTF(self->output_file_handle,"  ,  fn ident  => ");
    //TreeWalkerIdentifier(self,function->ident);

    for(u64 i = 0; i < function->arguments.len; i++)
    {
        //TreeWalkerFunctionArgument(self,LinkedListAt(&function->arguments,i));
    }

    TreeWalkerBlockStmt(self,function->block);
    
}

void TreeWalkerFunctionArgument(struct TreeWalker *self,struct ASTFunctionArgument *argument)
{
    if( ACHIOR_LABS_NULL(argument))
    {
        return;
    }


    ACHIOR_LABS_PRINT("print fn");
    //TreeWalkerType(self,argument->type);
    //TreeWalkerIdentifier(self,argument->ident);
}


void TreeWalkerGetDataType(struct TreeWalker *self,enum ASTDataType ast_type)
{
    switch(ast_type)
    {
        case AST_DATA_TYPE_I32:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"i32");
            break;
        }
        default:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown-type");
        }
    }	
}



void TreeWalkerType(struct TreeWalker *self,struct ASTType *ast_type)
{
    if( ACHIOR_LABS_NULL(ast_type))
    {
        return;
    }

	TreeWalkerGetDataType(self,ast_type->dataType);
}

void TreeWalkerBlockStmt(struct TreeWalker *self,struct ASTBlockStmt *ast_block)
{
    for(u64 i = 0; i < ast_block->stmts.len; i++)
    {
        //ACHIOR_LABS_FPRINTF(self->output_file_handle,"\n\t\t");
        TreeWalkerStmt(self,LinkedListAt(&ast_block->stmts,i));
    }
}


void TreeWalkerStmt(struct TreeWalker *self,struct ASTStatement *ast_stmt)
{
    if( ACHIOR_LABS_NULL(ast_stmt))
    {
        return;
    }

	switch(ast_stmt->type)
	{
		case AST_STATEMENT_RETURN:
		{
            TreeWalkerReturnStmt(self,ast_stmt->stmt);
			break;
		}
		default:
		{
			break;
		}
	}

}



void TreeWalkerReturnStmt(struct TreeWalker *self,struct ASTReturnStmt *ast_stmt)
{
    if( ACHIOR_LABS_NULL(ast_stmt))
    {
        return;
    }

    //ACHIOR_LABS_FPRINTF(self->output_file_handle,"return [EXPR] =>  ");
    struct TreeWalkerValue value = TreeWalkerExpr(self,ast_stmt->expr);
    //ACHIOR_LABS_FPRINTF(self->output_file_handle,"\n\n");

    switch(value.type)
    {
        case TREE_WALKER_VALUE_I32:
        {
            ACHIOR_LABS_PRINTF("return value => %s\n",(char *)value.value);
            break;
        }
        default:
        {
            ACHIOR_LABS_PUTS("unsported treewalkervalue\n");
        }
    }
}



struct TreeWalkerValue TreeWalkerExpr(struct TreeWalker *self,struct ASTExpression *expr)
{
    struct TreeWalkerValue value;

    if( ACHIOR_LABS_NULL(expr))
    {
        return value;
    }


    
	switch(expr->type)
    {
        case AST_EXPRESSION_BINARY:
        {
            value = TreeWalkerBinaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_UNARY:
        {
            value = TreeWalkerUnaryExpr(self,expr->expr);
            break;
        }
        case AST_EXPRESSION_LITERAL:
        {
            value = TreeWalkerLiteralExpr(self,expr->expr);
            break;
        }
        default:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown expression ");
            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_NONE,NULL);
            break;
        }
    }

    return value;
}


struct TreeWalkerValue TreeWalkerBinaryExpr(struct TreeWalker *self,void *expr)
{
    struct TreeWalkerValue value;

    if( ACHIOR_LABS_NULL(expr))
    {
        return value;
    }

    struct TreeWalkerValue value1;
    struct TreeWalkerValue value2;

    struct ASTBinaryExpr *binary = (struct ASTBinaryExpr *)expr;
    value1 = TreeWalkerExpr(self,binary->lhs);
    value2 = TreeWalkerExpr(self,binary->rhs);
    return TreeWalkerBinaryOperator(self,value1,binary->op,value2);
}



struct TreeWalkerValue TreeWalkerBinaryOperator(struct TreeWalker *self,struct TreeWalkerValue  lhs,enum ASTBinaryOperator op,struct TreeWalkerValue rhs)
{
    struct TreeWalkerValue value;
    switch(op)
    {
        case AST_BINARY_OPERATOR_ADD:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"+");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 + num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_SUB:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"-");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 - num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_MUL:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"*");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 * num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_DIV:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"/");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 / num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_MOD:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"%%");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 % num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_LESS:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"<");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 < num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_LESS_EQUAL:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"<=");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 <= num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_GREATER:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,">");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 > num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_BINARY_OPERATOR_GREATER_EQUAL:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,">=");
            i32 num1 = atoi(lhs.value);
            i32 num2 = atoi(rhs.value);

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num1 >= num2);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        default:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown binary operator");
            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_NONE,NULL);
            break;
        }
    }

    return value;
}


struct TreeWalkerValue TreeWalkerUnaryExpr(struct TreeWalker *self,void *expr)
{
    struct TreeWalkerValue value;

    if( ACHIOR_LABS_NULL(expr))
    {
        return value;
    }


    struct ASTUnaryExpr *unary = (struct ASTUnaryExpr *)expr;
    value = TreeWalkerExpr(self,unary->rhs);
    return TreeWalkerUnaryOperator(self,unary->op,value);
}



struct TreeWalkerValue TreeWalkerUnaryOperator(struct TreeWalker *self,enum ASTUnaryOperator op,struct TreeWalkerValue rhs)
{
    struct TreeWalkerValue value;
    switch(op)
    {
        case AST_UNARY_OPERATOR_COMPLEMENT:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"~");
            i32 num = atoi(rhs.value);
            num     = ~num;

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        case AST_UNARY_OPERATOR_NEGATE:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"-");
            i32 num = atoi(rhs.value);
            num     = -num;

            char *buf = ACHIOR_LABS_MALLOC(20);
            ACHIOR_LABS_SNPRINTF(buf,20,"%d",num);

            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,buf);
            break;
        }
        default:
        {
            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_NONE,NULL);
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown unary operator");
            break;
        }
    }

    return value;
}


struct TreeWalkerValue TreeWalkerLiteralExpr(struct TreeWalker *self,void *expr)
{
    struct TreeWalkerValue value;

    if( ACHIOR_LABS_NULL(expr))
    {
        return value;
    }

    //ACHIOR_LABS_PRINT("literal");
    struct ASTLiteralExpr *literal = (struct ASTLiteralExpr *)expr;

    switch(literal->type)
    {
        case AST_LITERAL_I32:
        {
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"[i32]");
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"%s",literal->literal.value.data);
            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_I32,literal->literal.value.data);
            break;
        }
        default:
        {
            TreeWalkerValueNew(&value,TREE_WALKER_VALUE_NONE,NULL);
            //ACHIOR_LABS_FPRINTF(self->output_file_handle,"unknown literal expression");
        }
    }

    return value;
}
