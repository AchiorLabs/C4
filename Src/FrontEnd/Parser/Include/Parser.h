#ifndef ACHIOR_LABS_PARSER_H
#define ACHIOR_LABS_PARSER_H

#include "../../AST/Include/AST.h"
#include "../../AST/Include/ASTPrint.h"

struct Parser
{
	char *fileName;
	u64 fileLength;
	char *fileSource;
	struct LinkedList tokens;	
	u64 tokenSize;	
	u64 index;
	struct DiagnosticEngine *engine;
	struct BumpAllocator *bump;	
	bool panicMode;	
	bool hasErrors;	
	struct ASTProgram *astProgram;	
	struct LinkedList decls;
};



bool ParserNew(struct Parser *self,char *fileName,char *fileSource,struct LinkedList tokens,struct DiagnosticEngine *engine,struct BumpAllocator *bump);


enum TokenKind ParserKeywordToToken(struct Parser *self,char *keyword);



enum TokenKind ParserSymbolToToken(struct Parser *self,char *symbol);



enum TokenKind ParserStringToToken(struct Parser *self,char *string);




struct Token *ParserPeek(struct Parser *self,i64 lookAhead);




struct Token *ParserConsume(struct Parser *self);




bool ParserIsTokenKind(struct Parser *self,enum TokenKind kind,i64 lookAhead);




bool ParserIsToken(struct Parser *self,char *string,i64 lookAhead);



void ParserFatal(struct Parser *self,struct Token *token,char *message,char *label,char *help,char *fix,char *note);



void ParserSynchronizeDecl(struct Parser *self);



void ParserSynchronizeStmt(struct Parser *self);



bool ParserIsType(struct Parser *self);



bool ParserIsSymbol(struct Parser *self,char *symbol,i64 lookAhead);



bool ParserExpectSymbol(struct Parser *self,char *symbol,char *errorMessage);



bool ParserIsKeyword(struct Parser *self,char *keyword,i64 lookAhead);



bool ParserExpectKeyword(struct Parser *self,char *keyword,char *errorMessage);




bool ParserExpectString_literal(struct Parser *self,char *literal,char *errorMessage);



bool ParserIsIdentifier(struct Parser *self);



bool ParserExpectIdentifier(struct Parser *self,char *errorMessage);



bool ParserAtEnd(struct Parser *self);




struct ASTProgram *ParserParseProgram(struct Parser *self);




struct ASTDeclaration *ParserParseDecl(struct Parser *self);



struct ASTDeclaration *ParserParseUseDecl(struct Parser *self);


struct ASTDeclaration *ParserParseEnumDecl(struct Parser *self);

struct ASTEnumConstant *ParserParseEnumConstant(struct Parser *self);


struct ASTDeclaration *ParserParseStructDecl(struct Parser *self);



struct ASTStructProperty *ParserParseStructProperty(struct Parser *self);



struct ASTDeclaration *ParserParseImplDecl(struct Parser *self);


struct ASTFunctionDecl *ParserParseImplMethod(struct Parser *self,struct Token *structIdent,bool is_pub,bool is_static,bool is_naked,bool is_foreign,struct String foreign_abi,bool has_link_name,struct String link_name);

struct ASTDeclaration *ParserParseSumDecl(struct Parser *self);


struct ASTSumVariant *ParserParseSumVariant(struct Parser *self);


void *ParserParseForeignDecl(struct Parser *self);



struct ASTDeclaration *ParserParseFunctionDecl(struct Parser *self,bool isPublic,bool isStatic,bool isNaked,bool isForeign,struct String foreignAbi,bool hasLinkName,struct String linkName);




struct ASTFunctionArgument *ParserParseFunctionArgument(struct Parser *self);


struct ASTDeclaration *ParserParseVariableDecl(struct Parser *self);

struct ASTDeclaration *ParserParseTypeDecl(struct Parser *self);

enum ASTDataType ParserGetDataType(struct Parser *self);



struct ASTType *ParserParseType(struct Parser *self);



struct ASTBlockStmt *ParserParseBlockStmt(struct Parser *self);



struct ASTStatement *ParserParseStmt(struct Parser *self);



struct ASTStatement *ParserParseReturnStmt(struct Parser *self);


bool ParserParseTryVariableDecl(struct Parser *self);



struct ASTStatement *ParserParseVariableDeclarationStmt(struct Parser *self);


struct ASTVariableDecl *ParserParseVariableDeclaration(struct Parser *self,bool isConstant);



struct ASTVariableDeclInit *ParserParseVariableDeclInit(struct Parser *self,struct ASTType *type);



struct ASTVariableDeclInit *ParserParseVariableDeclSingleInit(struct Parser *self,struct ASTType *type);




struct ASTVariableDeclInit *ParserParseVariableDeclArrayInit(struct Parser *self,struct ASTType *type);



struct ASTIfElse *ParserParseIfElse(struct Parser *self);



struct ASTIfElif *ParserParseIfElif(struct Parser *self);


struct ASTStatement *ParserParseIfStmt(struct Parser *self);



struct ASTStatement *ParserParseWhileStmt(struct Parser *self);


struct ASTStatement *ParserParseLoopStmt(struct Parser *self);



struct ASTStatement *ParserParseContinueStmt(struct Parser *self);



struct ASTStatement *ParserParseBreakStmt(struct Parser *self);



struct ASTMatchStmt *ParserParseMatchStmt(struct Parser *self);


enum ASTAssignmentOperator ParserGetAssignmentOperator(struct Parser *self,struct Token *token);



bool ParserIsBinary(struct Parser *self);

enum ASTBinaryOperator ParserGetBinaryOperator(struct Parser *self,struct Token *token);



bool ParserIsUnary(struct Parser *self);



enum ASTUnaryOperator ParserGetUnaryOperator(struct Parser *self,struct Token *token);



u64 ParserGetPrecedence(struct Parser *self);



struct ASTExpression *ParserParseExpr(struct Parser *self,u64 minPrecedence);



struct ASTExpression *ParserParseUnary(struct Parser *self);



struct ASTExpression *ParserParsePostfix(struct Parser *self);



struct ASTExpression *ParserParsePrimary(struct Parser *self);


struct ASTExpression *ParserParseAddressOfExpr(struct Parser *self);


struct ASTExpression *ParserParseSelfExpr(struct Parser *self);


struct ASTExpression *ParserParseParenExpr(struct Parser *self);

struct ASTExpression *ParserParseVariableExpr(struct Parser *self);



struct ASTExpression *ParserParseLiteralString(struct Parser *self);



struct ASTExpression *ParserParseLiteralCharacter(struct Parser *self);



struct ASTExpression *ParserParseLiteralI32(struct Parser *self);







#endif

