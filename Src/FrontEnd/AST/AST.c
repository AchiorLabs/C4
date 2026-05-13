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


bool ASTDeclarationNew(struct ASTDeclaration *self,enum ASTDeclarationKind kind,void *decl,bool isPublic)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind     = kind;
	self->decl     = decl;
	self->isPublic = isPublic;

	return true;
}



bool ASTStructTypeNew(struct ASTStructType *self,struct Token *ident,struct Layout layout)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;

	return true;
}




bool ASTAggregateTypeNew(struct ASTAggregateType *self,struct LinkedList path)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->path = path;

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


bool ASTGenericTypeNew(struct ASTGenericType *self,struct ASTType *base,struct LinkedList args)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->base = base;
	self->args = args;

	return true;
}

bool ASTTypeNew(struct ASTType *self,enum ASTDataType dataType,void *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->dataType   = dataType;
	self->isFunction = false;
	self->type       = type;

	return true;
}



bool ASTUseDeclNew(struct ASTUseDecl *self,struct LinkedList path,struct Token *alias)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->path  = path;
	self->alias = alias;
	
	return true;
}



bool ASTEnumConstantNew(struct ASTEnumConstant *self,struct Token *constant,struct ASTExpression *expr)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->constant = constant;
	self->expr     = expr;

	return true;
}



bool ASTEnumDeclNew(struct ASTEnumDecl *self,struct Token *ident,struct LinkedList constants)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident     = ident;
	self->constants = constants;

	return true;
}




bool ASTStructPropertyNew(struct ASTStructProperty *self,struct ASTType *type,struct Token *ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type  = type;
	self->ident = ident;

	return true;
}


bool ASTStructDeclNew(struct ASTStructDecl *self,struct Token *ident,struct LinkedList properties)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident      = ident;
	self->properties = properties;

	return true;
}



bool ASTUnionDeclNew(struct ASTUnionDecl *self,struct Token *ident,struct LinkedList properties)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident      = ident;
	self->properties = properties;

	return true;
}



bool ASTImplDeclNew(struct ASTImplDecl *self,struct Token *ident,struct LinkedList methods)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident   = ident;
	self->methods = methods;

	return true;
}


bool ASTSumNamedFieldNew(struct ASTSumNamedField *self,struct Token *ident,struct ASTType *type)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;
	self->type  = type;

	return true;
}



bool ASTSumVariantNew(struct ASTSumVariant *self,struct Token *ident,enum ASTSumVariantKind kind,struct LinkedList fields)
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



bool ASTSumDeclNew(struct ASTSumDecl *self,struct Token *ident,struct LinkedList variants)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident    = ident;
	self->variants = variants;

	return true;
}



bool ASTFunctionAttributesNew(struct ASTFunctionAttributes *self,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->isPublic    = isPublic;
	self->isStatic    = isStatic;
	self->isNaked     = isNaked;
	self->isForeign   = isForeign;
	self->foreignAbi  = foreignAbi;
	self->hasLinkName = hasLinkName;
	self->linkName    = linkName;

	return true;
}




bool ASTFunctionArgumentNew(struct ASTFunctionArgument *self,struct ASTType *type,struct Token *ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->type  = type;
	self->ident = ident;
	return true;
}



bool ASTFunctionDeclNew(struct ASTFunctionDecl *self,struct ASTType *returnType,struct Token *ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->returnType = returnType;
	self->ident      = ident;
	self->arguments  = arguments;
	self->block      = block;
	self->attributes = attributes;

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


bool ASTStatementNew(struct ASTStatement *self,enum ASTStatementKind kind,void *stmt)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind = kind;
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

bool ASTIfStmtNew(struct ASTIfStmt *self,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList  elifs,struct ASTIfElse *elseBlock)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr      = expr;
	self->block     = block;
	self->elifs     = elifs;
	self->elseBlock = elseBlock;

	return true;
}




bool ASTVariableDeclNew(struct ASTVariableDecl *self,struct ASTType *type,struct Token *ident,struct ASTVariableDeclInit *init)
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


bool ASTVariableDeclInitNew(struct ASTVariableDeclInit *self,enum ASTVariableDeclInitKind kind,void *init)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind = kind;
	self->init = init;

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




bool ASTPatternNew(struct ASTPattern *self,enum ASTPatternKind kind,struct Token *ident,struct LinkedList bindings)
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



bool ASTExpressionNew(struct ASTExpression *self,enum ASTExpressionKind kind,void *expr)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind = kind;
	self->expr = expr;

	return true;
}


bool ASTPathExprNew(struct ASTPathExpr *self,struct LinkedList path,bool isFunction,struct LinkedList arguments)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->path       = path;
	self->isFunction = isFunction;
	self->arguments  = arguments;

	return true;
}


bool ASTMethodExprNew(struct ASTMethodExpr *self,struct ASTExpression *lhs,struct Token *member,struct LinkedList arguments)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->member    = member;
	self->arguments = arguments;

	return true;
}

bool ASTStructPointerAccessExprNew(struct ASTStructPointerAccessExpr *self,struct ASTExpression *lhs,struct Token *member)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->lhs       = lhs;
	self->member    = member;

	return true;
}




bool ASTStructAccessExprNew(struct ASTStructAccessExpr *self,struct ASTExpression *lhs,struct Token *member)
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


bool ASTParenExprNew(struct ASTParenExpr *self,struct ASTExpression *expr)
{
	if(ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->expr = expr;

	return true;
}


bool ASTVariableExprNew(struct ASTVariableExpr *self,struct Token *ident)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->ident = ident;
	return true;
}


bool ASTLiteralExprNew(struct ASTLiteralExpr *self,enum ASTLiteralKind kind,struct Token *literal)
{
	if( ACHIOR_LABS_NULL(self))
	{
		return false;
	}

	self->kind    = kind;
	self->literal = literal;
	return true;
}









struct ASTProgram *C4MakeASTProgram(struct BumpAllocator *bump,struct LinkedList decls)
{
    struct ASTProgram *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTProgram,1);

    ASTProgramNew(node,decls);
    return node;
}



struct ASTDeclaration *C4MakeASTDeclaration(struct BumpAllocator *bump,enum ASTDeclarationKind kind,void *decl,bool isPublic)
{
    struct ASTDeclaration *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTDeclaration,1);
    
    ASTDeclarationNew(node,kind,decl,isPublic);
    return node;
}



struct ASTUseDecl *C4MakeASTUseDecl(struct BumpAllocator *bump,struct LinkedList path,struct Token *alias)
{
    struct ASTUseDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTUseDecl,1);

    ASTUseDeclNew(node,path,alias);
    return node;
}


struct ASTEnumDecl *C4MakeASTEnumDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList constants)
{
    struct ASTEnumDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTEnumDecl,1);

    ASTEnumDeclNew(node,ident,constants);
    return node;
}


struct ASTEnumConstant *C4MakeASTEnumConstant(struct BumpAllocator *bump,struct Token *constant,struct ASTExpression *expr)
{
	struct ASTEnumConstant *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTEnumConstant,1);
	ASTEnumConstantNew(node,constant,expr);

	return node;
}


struct ASTStructDecl *C4MakeASTStructDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList properties)
{
    struct ASTStructDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStructDecl,1);

    ASTStructDeclNew(node,ident,properties);
    return node;
}


struct ASTStructProperty *C4MakeASTStructProperty(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident)
{
    struct ASTStructProperty *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStructProperty,1);

    ASTStructPropertyNew(node,type,ident);
    return node;
}





struct ASTImplDecl *C4MakeASTImplDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList methods)
{
    struct ASTImplDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTImplDecl,1);

    ASTImplDeclNew(node,ident,methods);
    return node;
}


struct ASTSumDecl *C4MakeASTSumDecl(struct BumpAllocator *bump,struct Token *ident,struct LinkedList variants)
{
    struct ASTSumDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTSumDecl,1);

    ASTSumDeclNew(node,ident,variants);
    return node;
}


struct ASTSumVariant *C4MakeASTSumVariant(struct BumpAllocator *bump,struct Token *ident,enum ASTSumVariantKind kind,struct LinkedList fields)
{
	struct ASTSumVariant *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTSumVariant,1);

    ASTSumVariantNew(node,ident,kind,fields);
    return node;
}


struct ASTForeignDecl *C4MakeASTForeignDecl(struct BumpAllocator *bump,struct LinkedList functions)
{
    struct ASTForeignDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTForeignDecl,1);

    ASTForeignDeclNew(node,functions);
    return node;
}




struct ASTFunctionDecl *C4MakeASTFunctionDecl(struct BumpAllocator *bump,struct ASTType *returnType,struct Token *ident,struct LinkedList arguments,struct ASTBlockStmt *block,struct ASTFunctionAttributes *attributes)
{
    struct ASTFunctionDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTFunctionDecl,1);

    ASTFunctionDeclNew(node,returnType,ident,arguments,block,attributes);
    return node;
}



struct ASTFunctionArgument *C4MakeASTFunctionArgument(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident)
{
    struct ASTFunctionArgument *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTFunctionArgument,1);

    ASTFunctionArgumentNew(node,type,ident);
    return node;
}



struct ASTFunctionAttributes *C4MakeASTFunctionAttributes(struct BumpAllocator *bump,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName)
{
    struct ASTFunctionAttributes *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTFunctionAttributes,1);

    ASTFunctionAttributesNew(node,isPublic,isStatic,isNaked,isForeign,foreignAbi,hasLinkName,linkName);

    return node;
}




struct ASTType *C4MakeASTType(struct BumpAllocator *bump,enum ASTDataType data_type,void *type)
{
    struct ASTType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTType,1);

    ASTTypeNew(node,data_type,type);
    return node;
}




struct ASTPointerType *C4MakeASTPointerType(struct BumpAllocator *bump,struct ASTType *type)
{
    struct ASTPointerType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPointerType,1);

    ASTPointerTypeNew(node,type);
    return node;
}




struct ASTArrayType *C4MakeASTArrayType(struct BumpAllocator *bump,struct ASTType *type,struct ASTExpression *size)
{
    struct ASTArrayType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTArrayType,1);

    ASTArrayTypeNew(node,type,size);
    return node;
}




struct ASTFunctionType *C4MakeASTFunctionType(struct BumpAllocator *bump,struct ASTType *returnType,struct LinkedList arguments)
{
    struct ASTFunctionType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTFunctionType,1);

    ASTFunctionTypeNew(node,returnType,arguments);
    return node;
}




struct ASTStructType *C4MakeASTStructType(struct BumpAllocator *bump,struct Token *ident,struct Layout layout)
{
    struct ASTStructType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStructType,1);

    ASTStructTypeNew(node,ident,layout);
    return node;
}



struct ASTAggregateType *C4MakeASTAggregateType(struct BumpAllocator *bump,struct LinkedList path)
{
    struct ASTAggregateType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTAggregateType,1);

    ASTAggregateTypeNew(node,path);
    return node;
}


struct ASTGenericType *C4MakeASTGenericType(struct BumpAllocator *bump,struct ASTType *base,struct LinkedList args)
{
	struct ASTGenericType *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTGenericType,1);

	ASTGenericTypeNew(node,base,args);
	return node;
}



struct ASTStatement *C4MakeASTStatement(struct BumpAllocator *bump,enum ASTStatementKind kind,void *stmt)
{
    struct ASTStatement *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStatement,1);

    ASTStatementNew(node,kind,stmt);
    return node;
}




struct ASTBlockStmt *C4MakeASTBlockStmt(struct BumpAllocator *bump,struct LinkedList stmts)
{
    struct ASTBlockStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTBlockStmt,1);

    ASTBlockStmtNew(node,stmts);
    return node;
}




struct ASTReturnStmt *C4MakeASTReturnStmt(struct BumpAllocator *bump,struct ASTExpression *expr)
{
    struct ASTReturnStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTReturnStmt,1);

    ASTReturnStmtNew(node,expr);
    return node;
}




struct ASTVariableDecl *C4MakeASTVariableDecl(struct BumpAllocator *bump,struct ASTType *type,struct Token *ident,struct ASTVariableDeclInit *init)
{
    struct ASTVariableDecl *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTVariableDecl,1);

    ASTVariableDeclNew(node,type,ident,init);
    return node;
}





struct ASTVariableDeclInit *C4MakeASTVariableDeclInit(struct BumpAllocator *bump,enum ASTVariableDeclInitKind kind,void *init)
{
    struct ASTVariableDeclInit *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTVariableDeclInit,1);

    ASTVariableDeclInitNew(node,kind,init);
    return node;
}





struct ASTVariableDeclSingleInit *C4MakeASTVariableDeclSingleInit(struct BumpAllocator *bump,struct ASTExpression *expr)
{
    struct ASTVariableDeclSingleInit *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTVariableDeclSingleInit,1);

    ASTVariableDeclSingleInitNew(node,expr);
    return node;
}




struct ASTVariableDeclArrayInit *C4MakeASTVariableDeclArrayInit(struct BumpAllocator *bump,struct LinkedList elements)
{
    struct ASTVariableDeclArrayInit *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTVariableDeclArrayInit,1);

    ASTVariableDeclArrayInitNew(node,elements);
    return node;
}




struct ASTBreakStmt *C4MakeASTBreakStmt(struct BumpAllocator *bump)
{
    struct ASTBreakStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTBreakStmt,1);

    ASTBreakStmtNew(node);
    return node;
}






struct ASTContinueStmt *C4MakeASTContinueStmt(struct BumpAllocator *bump)
{
    struct ASTContinueStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTContinueStmt,1);

    ASTContinueStmtNew(node);
    return node;
}




struct ASTLoopStmt *C4MakeASTLoopStmt(struct BumpAllocator *bump,struct ASTBlockStmt *block)
{
    struct ASTLoopStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTLoopStmt,1);

    ASTLoopStmtNew(node,block);
    return node;
}




struct ASTWhileStmt *C4MakeASTWhileStmt(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
    struct ASTWhileStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTWhileStmt,1);

    ASTWhileStmtNew(node,expr,block);
    return node;
}




struct ASTIfElif *C4MakeASTIfElif(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block)
{
    struct ASTIfElif *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTIfElif,1);

    ASTIfElifNew(node,expr,block);
    return node;
}

struct ASTIfElse *C4MakeASTIfElse(struct BumpAllocator *bump,struct ASTBlockStmt *block)
{
    struct ASTIfElse *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTIfElse,1);

    ASTIfElseNew(node,block);
    return node;
}

struct ASTIfStmt *C4MakeASTIfStmt(struct BumpAllocator *bump,struct ASTExpression *expr,struct ASTBlockStmt *block,struct LinkedList elifs,struct ASTIfElse *elseBlock)
{
    struct ASTIfStmt *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTIfStmt,1);

    ASTIfStmtNew(node,expr,block,elifs,elseBlock);
    return node;
}




struct ASTExpression *C4MakeASTExpression(struct BumpAllocator *bump,enum ASTExpressionKind kind,void *expr)
{
    struct ASTExpression *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTExpression,1);

    ASTExpressionNew(node,kind,expr);

	return node;
}



struct ASTLiteralExpr *C4MakeASTLiteralExpr(struct BumpAllocator *bump,enum ASTLiteralKind kind,struct Token *literal)
{
    struct ASTLiteralExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTLiteralExpr,1);

    ASTLiteralExprNew(node,kind,literal);
    return node;
}




struct ASTVariableExpr *C4MakeASTVariableExpr(struct BumpAllocator *bump,struct Token *ident)
{
    struct ASTVariableExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTVariableExpr,1);

    ASTVariableExprNew(node,ident);
    return node;
}

struct ASTParenExpr *C4MakeASTParenExpr(struct BumpAllocator *bump,struct ASTExpression *expr)
{
	struct ASTParenExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTParenExpr,1);

	ASTParenExprNew(node,expr);

	return node;
}

/*


struct ASTSelfExpr *C4MakeASTSelfExpr(struct BumpAllocator *bump,struct Token *ident)
{
    struct ASTSelfExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTSelfExpr,1);

    ASTVariableExprNew(node,ident);
    return node;
}
*/




struct ASTUnaryExpr *C4MakeASTUnaryExpr(struct BumpAllocator *bump,enum ASTUnaryOperator op,struct ASTExpression *rhs)
{
    struct ASTUnaryExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTUnaryExpr,1);

    ASTUnaryExprNew(node,op,rhs);
    return node;
}




struct ASTBinaryExpr *C4MakeASTBinaryExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTBinaryOperator op,struct ASTExpression *rhs)
{
    struct ASTBinaryExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTBinaryExpr,1);

    ASTBinaryExprNew(node,lhs,op,rhs);
    return node;
}




struct ASTAssignmentExpr *C4MakeASTAssignmentExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTAssignmentOperator op,struct ASTExpression *rhs)
{
    struct ASTAssignmentExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTAssignmentExpr,1);

    ASTAssignmentExprNew(node,lhs,op,rhs);
    return node;
}




struct ASTCastExpr *C4MakeASTCastExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,enum ASTCastOperator op,struct ASTType *data_type)
{
    struct ASTCastExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTCastExpr,1);

    ASTCastExprNew(node,lhs,op,data_type);
    return node;
}





struct ASTFunctionCallExpr *C4MakeASTFunctionCallExpr(struct BumpAllocator *bump,struct ASTExpression *base,struct LinkedList arguments)
{
    struct ASTFunctionCallExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTFunctionCallExpr,1);

    ASTFunctionCallExprNew(node,base,arguments);
    return node;
}



struct ASTAddressOfExpr *C4MakeASTAddressOfExpr(struct BumpAllocator *bump,struct ASTExpression *rhs)
{
    struct ASTAddressOfExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTAddressOfExpr,1);

    ASTAddressOfExprNew(node,rhs);
    return node;
}




struct ASTPtrReadExpr *C4MakeASTPtrReadExpr(struct BumpAllocator *bump,struct ASTExpression *lhs)
{
    struct ASTPtrReadExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrReadExpr,1);

    ASTPtrReadExprNew(node,lhs);
    return node;
}




struct ASTPtrWriteExpr *C4MakeASTPtrWriteExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrWriteExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrWriteExpr,1);

    ASTPtrWriteExprNew(node,lhs,rhs);
    return node;
}




struct ASTPtrOffsetExpr *C4MakeASTPtrOffsetExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrOffsetExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrOffsetExpr,1);

    ASTPtrOffsetExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrByteOffsetExpr *C4MakeASTPtrByteOffsetExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrByteOffsetExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrByteOffsetExpr,1);

    ASTPtrByteOffsetExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrAdvanceExpr *C4MakeASTPtrAdvanceExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrAdvanceExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrAdvanceExpr,1);

    ASTPtrAdvanceExprNew(node,lhs,rhs);
    return node;
}



struct ASTPtrDiffExpr *C4MakeASTPtrDiffExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *rhs)
{
    struct ASTPtrDiffExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPtrDiffExpr,1);

    ASTPtrDiffExprNew(node,lhs,rhs);
    return node;
}




struct ASTSubscriptExpr *C4MakeASTSubscriptExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct ASTExpression *index)
{
    struct ASTSubscriptExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTSubscriptExpr,1);

    ASTSubscriptExprNew(node,lhs,index);
    return node;
}




struct ASTAsPtrExpr *C4MakeASTAsPtrExpr(struct BumpAllocator *bump,struct ASTExpression *lhs)
{
    struct ASTAsPtrExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTAsPtrExpr,1);

    ASTAsPtrExprNew(node,lhs);
    return node;
}

struct ASTLenExpr *C4MakeASTLenExpr(struct BumpAllocator *bump,struct ASTExpression *lhs)
{
    struct ASTLenExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTLenExpr,1);

    ASTLenExprNew(node,lhs);
    return node;
}




struct ASTStructAccessExpr *C4MakeASTStructAccessExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member)
{
    struct ASTStructAccessExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStructAccessExpr,1);

    ASTStructAccessExprNew(node,lhs,member);
    return node;
}




struct ASTStructPointerAccessExpr *C4MakeASTStructPointerAccessExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member)
{
    struct ASTStructPointerAccessExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTStructPointerAccessExpr,   1);

    ASTStructPointerAccessExprNew(node,lhs,member);
    return node;
}





struct ASTMethodExpr *C4MakeASTMethodExpr(struct BumpAllocator *bump,struct ASTExpression *lhs,struct Token *member,struct LinkedList arguments)
{
    struct ASTMethodExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTMethodExpr,1);

    ASTMethodExprNew(node,lhs,member,arguments);
    return node;
}




struct ASTPathExpr *C4MakeASTPathExpr(struct BumpAllocator *bump,struct LinkedList path,bool isFunction,struct LinkedList arguments)
{
    struct ASTPathExpr *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct ASTPathExpr,1);
    ASTPathExprNew(node,path,isFunction,arguments);

    return node;
}

