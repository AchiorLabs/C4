#ifndef ACHIOR_LABS_PARSER_H
#define ACHIOR_LABS_PARSER_H

#include "../../AST/Include/AST.h"
#include "../../AST/Include/ASTPrint.h"

struct Parser
{
	char *fileName;	
	struct TokenList tokens;	
	u64 tokenSize;	
	u64 index;	
	struct BumpAllocator *bump;	
	bool panicMode;	
	bool hasErrors;	
	struct ASTProgram *astProgram;	
	struct LinkedList decls;
};



bool ParserNew(
	struct Parser *self,
	char *file_name,struct TokenList tokens,
	struct BumpAllocator *bump
);


enum TokenType ParserKeywordToToken(
	struct Parser *self,
	char *keyword
);




enum TokenType ParserSymbolToToken(
	struct Parser *self,
	char *symbol
);



enum TokenType ParserStringToToken(
	struct Parser *self,
	char *string
);




struct Token ParserPeek(
	struct Parser *self,
	i64 lookAhead
);




struct Token ParserConsume(
	struct Parser *self
);




bool ParserIsTokenType(
	struct Parser *self,
	enum TokenType type,
	i64 lookAhead
);




bool ParserIsToken(
	struct Parser *self,
	char *string,
	i64 lookAhead
);



void ParserFatal(
	struct Parser *self,
	char *string
);



void ParserSynchronizeDecl(
	struct Parser *self
);



void ParserSynchronizeStmt(
	struct Parser *self
);



bool ParserIsType(
	struct Parser *self
);



bool ParserIsSymbol(
	struct Parser *self,
	char *symbol,
	i64 lookAhead
);



bool ParserExpectSymbol(
	struct Parser *self,
	char *symbol,
	char *errorMessage
);



bool ParserIsKeyword(
	struct Parser *self,
	char *keyword,
	i64 lookAhead
);



bool ParserExpectKeyword(
	struct Parser *self,
	char *keyword,
	char *errorMessage
);




bool ParserExpectString_literal(
	struct Parser *self,
	char *literal,
	char *errorMessage
);



bool ParserIsIdentifier(
	struct Parser *self
);



bool ParserExpectIdentifier(
	struct Parser *self,
	char *errorMessage
);



bool ParserAtEnd(
	struct Parser *self
);




struct ASTProgram *ParserParseProgram(
	struct Parser *self
);




struct ASTDeclaration *ParserParseDecl(
	struct Parser *self
);




struct ASTStructDecl *ParserParseStructDecl(
	struct Parser *self
);



struct ASTStructProperty *ParserParseStructProperty(
	struct Parser *self
);



struct ASTSumDecl *ParserParseSumDecl(struct Parser *self);


struct ASTSumVariant *ParserParseSumVariant(struct Parser *self);


void *ParserParseForeignDecl(
	struct Parser *self
);



struct ASTFunctionDecl *ParserParseFunctionDecl(
	struct Parser *self,
	bool isPublic,
	bool isStatic,
	bool isNaked,
	bool isForeign,
	struct String foreignAbi,
	bool hasLinkName,
	struct String linkName
);




struct ASTFunctionArgument *ParserParseFunctionArgument(
	struct Parser *self
);



enum ASTDataType ParserGetDataType(
	struct Parser *self
);



struct ASTType *ParserParseType(
	struct Parser *self
);



struct ASTBlockStmt *ParserParseBlockStmt(
	struct Parser *self
);



struct ASTStatement *ParserParseStmt(
	struct Parser *self
);



struct ASTReturnStmt *ParserParseReturnStmt(
	struct Parser *self
);


bool ParserParseTryVariableDecl(
	struct Parser *self
);



struct ASTVariableDecl *ParserParseVariableDecl(
	struct Parser *self
);



struct ASTVariableDeclInit *ParserParseVariableDeclInit(
	struct Parser *self,
	struct ASTType *type
);



struct ASTVariableDeclInit *ParserParseVariableDeclSingleInit(
	struct Parser *self,
	struct ASTType *type
);




struct ASTVariableDeclInit *ParserParseVariableDeclArrayInit(
	struct Parser *self,
	struct ASTType *type
);



struct ASTIfElse *ParserParseIfElse(
	struct Parser *self
);



struct ASTIfElif *ParserParseIfElif(
	struct Parser *self
);


struct ASTIfStmt *ParserParseIfStmt(
	struct Parser *self
);



struct ASTWhileStmt *ParserParseWhileStmt(
	struct Parser *self
);


struct ASTLoopStmt *ParserParseLoopStmt(
	struct Parser *self
);



struct ASTContinueStmt *ParserParseContinueStmt(
	struct Parser *self
);



struct ASTBreakStmt *ParserParseBreakStmt(
	struct Parser *self
);



enum ASTAssignmentOperator ParserGetAssignmentOperator(
	struct Parser *self,
	struct Token token
);



bool ParserIsBinary(
	struct Parser *self
);

enum ASTBinaryOperator ParserGetBinaryOperator(
	struct Parser *self,
	struct Token token
);



bool ParserIsUnary(
	struct Parser *self
);



enum ASTUnaryOperator ParserGetUnaryOperator(
	struct Parser *self,
	struct Token token
);



u64 ParserGetPrecedence(
	struct Parser *self
);



struct ASTExpression *ParserParseExpr(
	struct Parser *self,
	u64 minPrecedence
);



struct ASTExpression *ParserParseUnary(
	struct Parser *self
);



struct ASTExpression *ParserParsePostfix(
	struct Parser *self
);



struct ASTExpression *ParserParsePrimary(
	struct Parser *self
);


struct ASTExpression *ParserParseAddressOfExpr(
	struct Parser *self
);



struct ASTExpression *ParserParseVariableExpr(
	struct Parser *self
);



struct ASTExpression *ParserParseLiteralString(
	struct Parser *self
);



struct ASTExpression *ParserParseLiteralCharacter(
	struct Parser *self
);



struct ASTExpression *ParserParseLiteralI32(
	struct Parser *self
);











struct ASTProgram *ParserMakeProgram(
	struct Parser *self,
	struct LinkedList decls
);


struct ASTDeclaration *ParserMakeDeclaration(
	struct Parser *self,
	enum ASTDeclarationType type,
	void *decl
);

struct ASTStructDecl *ParserMakeStructDecl(
	struct Parser *self,
	struct Token ident,
	struct LinkedList properties
);



struct ASTStructProperty *ParserMakeStructProperty(
	struct Parser *self,
	struct ASTType *type,
	struct Token ident
);




struct ASTStructProperty *ParserMakeStructProperty(struct Parser *self,struct ASTType *type,struct Token ident);

struct ASTSumDecl *ParserMakeSumDecl(struct Parser *self,struct Token ident,struct LinkedList variants);


struct ASTSumVariant *ParserMakeSumVariant(struct Parser *self,struct Token ident,enum ASTSumVariantKind kind,struct LinkedList fields);

struct ASTForeignDecl *ParserMakeForeignDecl(
	struct Parser *self,
	struct LinkedList functions
);




struct ASTFunctionDecl *ParserMakeFunctionDecl(
	struct Parser *self,
	struct ASTType *returnType,
	struct Token ident,
	struct LinkedList arguments,
	struct ASTBlockStmt *block,
	struct ASTFunctionAttributes *attributes
);




struct ASTFunctionArgument *ParserMakeFunctionArgument(
	struct Parser *self,
	struct ASTType *type,
	struct Token ident
);



struct ASTFunctionAttributes *ParserMakeFunctionAttributes(
	struct Parser *self,
	bool isPublic,
	bool isStatic,
	bool isNaked,
	bool isForeign,
	struct String foreignAbi,
	bool hasLinkName,
	struct String linkName
);




struct ASTType *ParserMakeType(
	struct Parser *self,
	enum ASTDataType dataType,
	void *type
);



struct ASTPointerType *ParserMakePointerType(
	struct Parser *self,
	struct ASTType *type
);



struct ASTArrayType *ParserMakeArrayType(
	struct Parser *self,
	struct ASTType *type,
	struct ASTExpression *size
);



struct ASTFunctionType *ParserMakeFunctionType(
	struct Parser *self,
	struct ASTType *returnType,
	struct LinkedList arguments
);



struct ASTStructType *ParserMakeStructType(
	struct Parser *self,
	struct Token ident,
	struct Layout layout
);



struct ASTAggregateType *ParserMakeAggregateType(
	struct Parser *self,
	struct Token ident
);



struct ASTStatement *ParserMakeStatement(
	struct Parser *self,
	enum ASTStatementType type,
	void *stmt
);



struct ASTBlockStmt *ParserMakeBlockStmt(
	struct Parser *self,
	struct LinkedList stmts
);



struct ASTReturnStmt *ParserMakeReturnStmt(
	struct Parser *self,
	struct ASTExpression *expr
);



struct ASTVariableDecl *ParserMakeVariableDecl(
	struct Parser *self,
	struct ASTType *type,
	struct Token ident,
	struct ASTVariableDeclInit *init
);



struct ASTVariableDeclInit *ParserMakeVariableDeclInit(
	struct Parser *self,
	enum ASTVariableDeclInitType initType,
	void *init
);



struct ASTVariableDeclSingleInit *ParserMakeVariableDeclSingleInit(
	struct Parser *self,
	struct ASTExpression *expr
);



struct ASTVariableDeclArrayInit *ParserMakeVariableDeclArrayInit(
	struct Parser *self,
	struct LinkedList elements
);



struct ASTBreakStmt *ParserMakeBreakStmt(
	struct Parser *self
);




struct ASTContinueStmt *ParserMakeContinueStmt(
	struct Parser *self
);



struct ASTLoopStmt *ParserMakeLoopStmt(
	struct Parser *self,
	struct ASTBlockStmt *block
);



struct ASTWhileStmt *ParserMakeWhileStmt(
	struct Parser *self,
	struct ASTExpression *expr,
	struct ASTBlockStmt *block
);



struct ASTIfStmt *ParserMakeIfStmt(
	struct Parser *self,
	struct ASTExpression *expr,
	struct ASTBlockStmt *block,
	struct LinkedList elifs,
	struct ASTIfElse *elseBlock
);




struct ASTIfElif *ParserMakeIfElif(
	struct Parser *self,
	struct ASTExpression *expr,
	struct ASTBlockStmt *block
);



struct ASTIfElse *ParserMakeIfElse(
	struct Parser *self,
	struct ASTBlockStmt *block
);




struct ASTExpression *ParserMakeExpression(
	struct Parser *self,
	enum ASTExpressionType type,
	void *expr
);



struct ASTLiteralExpr *ParserMakeLiteralExpr(
	struct Parser *self,
	enum ASTLiteralType type,
	struct Token literal
);



struct ASTVariableExpr *ParserMakeVariableExpr(
	struct Parser *self,
	struct Token ident
);



struct ASTUnaryExpr *ParserMakeUnaryExpr(
	struct Parser *self,
	enum ASTUnaryOperator op,
	struct ASTExpression *rhs
);



struct ASTBinaryExpr *ParserMakeBinaryExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	enum ASTBinaryOperator op,
	struct ASTExpression *rhs
);



struct ASTAssignmentExpr *ParserMakeAssignmentExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	enum ASTAssignmentOperator op,
	struct ASTExpression *rhs
);



struct ASTCastExpr *ParserMakeCastExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	enum ASTCastOperator op,
	struct ASTType *dataType
);



struct ASTFunctionCallExpr *ParserMakeFunctionCallExpr(
	struct Parser *self,
	struct ASTExpression *base,
	struct LinkedList arguments
);



struct ASTAddressOfExpr *ParserMakeAddressOfExpr(
	struct Parser *self,
	struct ASTExpression *rhs
);



struct ASTPtrReadExpr *ParserMakePtrReadExpr(
	struct Parser *self,
	struct ASTExpression *lhs
);



struct ASTPtrWriteExpr *ParserMakePtrWriteExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *rhs
);



struct ASTPtrOffsetExpr *ParserMakePtrOffsetExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *rhs
);



struct ASTPtrByteOffsetExpr *ParserMakePtrByteOffsetExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *rhs
);

struct ASTPtrAdvanceExpr *ParserMakePtrAdvanceExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *rhs
);

struct ASTPtrDiffExpr *ParserMakePtrDiffExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *rhs
);



struct ASTSubscriptExpr *ParserMakeSubscriptExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct ASTExpression *index
);



struct ASTAsPtrExpr *ParserMakeAsPtrExpr(
	struct Parser *self,
	struct ASTExpression *lhs
);



struct ASTLenExpr *ParserMakeLenExpr(
	struct Parser *self,
	struct ASTExpression *lhs
);



struct ASTStructAccessExpr *ParserMakeStructAccessExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct Token member
);



struct ASTStructPointerAccessExpr *ParserMakeStructPointerAccessExpr(
	struct Parser *self,
	struct ASTExpression *lhs,
	struct Token member
);





#endif

