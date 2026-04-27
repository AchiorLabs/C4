#include "Include/AST.h"


bool ASTProgramNew(struct ASTProgram *self,struct LinkedList decls)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->decls = decls;
	return true;
}


bool ASTDeclarationNew(struct ASTDeclaration *self,enum ASTDeclarationType type,void *decl)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type = type;
	self->decl = decl;
	return true;
}



bool ASTStructTypeNew(struct ASTStructType *self,struct Token ident,struct Layout layout)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;

	return true;
}




bool ASTAggregateTypeNew(struct ASTAggregateType *self,struct Token ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;

	return true;
}


bool ASTFunctionTypeNew(struct ASTFunctionType *self,struct ASTType *returnType,struct LinkedList arguments)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->returnType = returnType;
	self->arguments   = arguments;

	return true;
}



bool ASTArrayTypeNew(struct ASTArrayType *self,struct ASTType *type,struct ASTExpression *size)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type = type;
	self->size = size;

	return true;
}




bool ASTPointerTypeNew(struct ASTPointerType *self,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type = type;

	return true;
}


bool ASTTypeNew(struct ASTType *self,enum ASTDataType dataType,void *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->dataType   = dataType;
	self->is_function = false;
	self->type        = type;

	return true;
}




bool ASTStructPropertyNew(struct ASTStructProperty *self,struct ASTType *type,struct Token ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type  = type;
	self->ident = ident;

	return true;
}


bool ASTStructDeclNew(struct ASTStructDecl *self,struct Token ident,struct LinkedList properties)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident      = ident;
	self->properties = properties;

	return true;
}



bool ASTUnionDeclNew(struct ASTUnionDecl *self,struct Token ident,struct LinkedList properties)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident      = ident;
	self->properties = properties;

	return true;
}



bool ASTImplDeclNew(struct ASTImplDecl *self,struct Token ident,struct LinkedList methods)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident   = ident;
	self->methods = methods;

	return true;
}


bool ASTSumNamedFieldNew(struct ASTSumNamedField *self,struct Token ident,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;
	self->type  = type;

	return true;
}



bool ASTSumVariantNew(struct ASTSumVariant *self,struct Token ident,enum ASTSumVariantKind kind,struct LinkedList fields)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident  = ident;
	self->kind   = kind;
	self->fields = fields;

	return true;
}



bool ASTSumDeclNew(struct ASTSumDecl *self,struct Token ident,struct LinkedList variants)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident    = ident;
	self->variants = variants;

	return true;
}



bool ASTFunctionAttributesNew(struct ASTFunctionAttributes *self,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->is_pub         = is_pub;
	self->is_static      = is_static;
	self->is_naked       = is_naked;
	self->is_foreign     = is_foreign;
	self->foreign_abi    = foreign_abi;
	self->has_link_name  = has_link_name;
	self->link_name      = link_name;

	return true;
}




bool ASTFunctionArgumentNew(struct ASTFunctionArgument *self,struct ASTType *type,struct Token ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type  = type;
	self->ident = ident;
	return true;
}
bool ASTFunctionDeclNew(struct ASTFunctionDecl *self,struct ASTType *returnType,struct Token ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->returnType = returnType;
	self->ident       = ident;
	self->arguments   = arguments;
	self->block       = block;
	self->attributes  = attributes;

	return true;
}



bool ASTForeignDeclNew(struct ASTForeignDecl *self,struct LinkedList functions)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->functions = functions;

	return true;
}


bool ASTStatementNew(struct ASTStatement *self,enum ASTStatementType type,void *stmt)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type = type;
	self->stmt = stmt;

	return true;
}


bool ASTBlockStmtNew(struct ASTBlockStmt *self,struct LinkedList stmts)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->stmts = stmts;

	return true;
}



bool ASTBreakStmtNew(struct ASTBreakStmt *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return true;
}



bool ASTContinueStmtNew(struct ASTContinueStmt *self)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	return true;
}



bool ASTLoopStmtNew(struct ASTLoopStmt *self,struct ASTBlockStmt *block)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->block = block;

	return true;
}



bool ASTWhileStmtNew(struct ASTWhileStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr  = expr;
	self->block = block;

	return true;
}



bool ASTIfElseNew(struct ASTIfElse *self,struct ASTBlockStmt *block)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->block = block;

	return true;
}

bool ASTIfElifNew(struct ASTIfElif *self,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr  = expr;
	self->block = block;

	return true;
}

bool ASTIfStmtNew(struct ASTIfStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList  elifs,struct ASTIfElse *else_block)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr       = expr;
	self->block      = block;
	self->elifs      = elifs;
	self->else_block = else_block;

	return true;
}




bool ASTVariableDeclNew(struct ASTVariableDecl *self,struct ASTType *type,struct Token ident,struct ASTVariableDeclInit *init)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type  = type;
	self->ident = ident;
	self->init  = init;

	return true;
}


bool ASTVariableDeclInitNew(struct ASTVariableDeclInit *self,enum ASTVariableDeclInitType initType,void *init)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->initType = initType;
	self->init      = init;

	return true;
}


bool ASTVariableDeclSingleInitNew(struct ASTVariableDeclSingleInit *self,struct ASTExpression *expr)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr = expr;

	return true;
}



bool ASTVariableDeclArrayInitNew(struct ASTVariableDeclArrayInit *self,struct LinkedList elements)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->elements = elements;

	return true;
}



bool ASTReturnStmtNew(struct ASTReturnStmt *self,struct ASTExpression *expr)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr = expr;

	return true;
}




bool ASTPatternNew(struct ASTPattern *self,enum ASTPatternKind kind,struct Token ident,struct LinkedList bindings)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind     = kind;
	self->ident    = ident;
	self->bindings = bindings;

	return true;
}



bool ASTMatchArmNew(struct ASTMatchArm *self,struct ASTPattern *pattern,struct ASTBlockStmt *stmt)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->pattern = pattern;
	self->stmt    = stmt;

	return true;
}


bool ASTMatchStmtNew(struct ASTMatchStmt *self,struct ASTExpression *expr,struct LinkedList arms)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr = expr;
	self->arms = arms;

	return true;
}



bool ASTExpressionNew(struct ASTExpression *self,enum ASTExpressionType type,void *expr)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type = type;
	self->expr = expr;

	return true;
}


bool ASTStructPointerAccessExprNew(struct ASTStructPointerAccessExpr *self,struct ASTExpression *lhs,struct Token member)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->member    = member;

	return true;
}




bool ASTStructAccessExprNew(struct ASTStructAccessExpr *self,struct ASTExpression *lhs,struct Token member)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->member    = member;

	return true;
}


bool ASTLenExprNew(struct ASTLenExpr *self,struct ASTExpression *lhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;

	return true;
}


bool ASTAsPtrExprNew(struct ASTAsPtrExpr *self,struct ASTExpression *lhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;

	return true;
}


bool ASTSubscriptExprNew(struct ASTSubscriptExpr *self,struct ASTExpression *lhs,struct ASTExpression *index)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->index     = index;

	return true;
}




bool ASTAddressOfExprNew(struct ASTAddressOfExpr *self,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->rhs = rhs;

	return true;
}





bool ASTPtrReadExprNew(struct ASTPtrReadExpr *self,struct ASTExpression *lhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;

	return true;
}



bool ASTPtrWriteExprNew(struct ASTPtrWriteExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->rhs = rhs;

	return true;
}




bool ASTPtrOffsetExprNew(struct ASTPtrOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->rhs = rhs;

	return true;
}




bool ASTPtrByteOffsetExprNew(struct ASTPtrByteOffsetExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->rhs = rhs;

	return true;
}





bool ASTPtrAdvanceExprNew(struct ASTPtrAdvanceExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->rhs = rhs;

	return true;
}





bool ASTPtrDiffExprNew(struct ASTPtrDiffExpr *self,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->rhs = rhs;

	return true;
}




bool ASTFunctionCallExprNew(struct ASTFunctionCallExpr *self,struct ASTExpression *base,struct LinkedList arguments)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->base            = base;
	self->arguments       = arguments;
	self->attributes      = NULL;
	self->dataType       = NULL;

	return true;
}



bool ASTCastExprNew(struct ASTCastExpr *self,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *dataType)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->op        = op;
	self->dataType = dataType;

	return true;
}


bool ASTAssignmentExprNew(struct ASTAssignmentExpr *self,struct ASTExpression *lhs,enum ASTAssignmentOperator op,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->op  = op;
	self->rhs = rhs;

	return true;
}

bool ASTBinaryExprNew(struct ASTBinaryExpr *self,struct ASTExpression *lhs,enum ASTBinaryOperator op,struct ASTExpression *rhs)
{

	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs = lhs;
	self->op  = op;
	self->rhs = rhs;

	return true;
}


bool ASTUnaryExprNew(struct ASTUnaryExpr *self,enum ASTUnaryOperator op,struct ASTExpression *rhs)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->op  = op;
	self->rhs = rhs;

	return true;
}



bool ASTVariableExprNew(struct ASTVariableExpr *self,struct Token ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;
	return true;
}


bool ASTLiteralExprNew(struct ASTLiteralExpr *self,enum ASTLiteralType type,struct Token literal)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type    = type;
	self->literal = literal;
	return true;
}
