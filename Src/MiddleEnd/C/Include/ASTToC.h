#ifndef ACHIOR_LABS_AST_TO_C_H
#define ACHIOR_LABS_AST_TO_C_H

#include "../../Include/Include.h"


struct ASTToC
{
    struct ASTProgram *program;
    FILE *fileHandle;
    struct BumpAllocator *bump;
};



bool ASTToCNew(struct ASTToC *self,struct ASTProgram *program,char *fileName,struct BumpAllocator *bump);

void ASTToCProgram(struct ASTToC *self,struct ASTProgram *program);
void ASTToCDecl(struct ASTToC *self,struct ASTDeclaration *decl);

void ASTToCIdentifier(struct ASTToC *self,struct Token ident);



void ASTToCStructDecl(struct ASTToC *self,struct ASTStructDecl *decl);
void ASTToCStructProperty(struct ASTToC *self,struct ASTStructProperty *property);

void ASTToCUnionDecl(struct ASTToC *self,struct ASTUnionDecl *decl);


void ASTToCImplDecl(struct ASTToC *self,struct ASTImplDecl *decl);

void ASTToCSumDecl(struct ASTToC *self,struct ASTSumDecl *decl);

void ASTToCSumEnum(struct ASTToC *self,char *ident,struct LinkedList variants);

void ASTToCSumVariants(struct ASTToC *self,struct LinkedList variants);

void ASTToCFunctionDecl(struct ASTToC *self,struct ASTFunctionDecl *function);
void ASTToCFunctionArgument(struct ASTToC *self,struct ASTFunctionArgument *argument);


void ASTToCType(struct ASTToC *self,struct ASTType *type,struct LinkedList *arrayBuffer);

void ASTToCBlockStmt(struct ASTToC *self,struct ASTBlockStmt *block,char *tab);


void ASTToCStmt(struct ASTToC *self,struct ASTStatement *stmt,char *tab);



void ASTToCReturnStmt(struct ASTToC *self,struct ASTReturnStmt *stmt,char *tab);
void ASTToCLoopStmt(struct ASTToC *self,struct ASTLoopStmt *stmt,char *tab);
void ASTToCWhileStmt(struct ASTToC *self,struct ASTWhileStmt *stmt,char *tab);
void ASTToCBreakStmt(struct ASTToC *self,struct ASTBreakStmt *stmt,char *tab);
void ASTToCContinueStmt(struct ASTToC *self,struct ASTContinueStmt *stmt,char *tab);
void ASTToCIfStmt(struct ASTToC *self,struct ASTIfStmt *stmt,char *tab);void ASTToCVariableDeclStmt(struct ASTToC *self,struct ASTVariableDecl *stmt,char *tab);
void ASTToCVariableDeclInit(struct ASTToC *self,struct ASTVariableDeclInit *init);
void ASTToCExpressionStmt(struct ASTToC *self,struct ASTExpression *stmt,char *tab);



void ASTToCExpression(struct ASTToC *self,struct ASTExpression *expr);



void ASTToCLiteralExpr(struct ASTToC *self,void *expr);


void ASTToCVariableExpr(struct ASTToC *self,void *expr);


void ASTToCUnaryExpr(struct ASTToC *self,void *expr);
void ASTToCUnaryOperator(struct ASTToC *self,enum ASTUnaryOperator op);

void ASTToCBinaryExpr(struct ASTToC *self,void *expr);
void ASTToCBinaryOperator(struct ASTToC *self,enum ASTBinaryOperator op);

void ASTToCAssignmentExpr(struct ASTToC *self,void *expr);

void ASTToCAssignmentOperator(struct ASTToC *self,enum ASTAssignmentOperator op);

void ASTToCFunctionCallExpr(struct ASTToC *self,void *expr);

void ASTToCCastExpr(struct ASTToC *self,void *expr);

void ASTToCAddressOfExpr(struct ASTToC *self,void *expr);

void ASTToCPtrReadExpr(struct ASTToC *self,void *expr);

void ASTToCPtrWriteExpr(struct ASTToC *self,void *expr);

void ASTToCPtrOffsetExpr(struct ASTToC *self,void *expr);

void ASTToCPtrByteOffsetExpr(struct ASTToC *self,void *expr);

void ASTToCPtrAdvanceExpr(struct ASTToC *self,void *expr);

void ASTToCPtrDiffExpr(struct ASTToC *self,void *expr);

void ASTToCSubscriptExpr(struct ASTToC *self,void *expr);

void ASTToCAsPtrExpr(struct ASTToC *self,void *expr);

void ASTToCLenExpr(struct ASTToC *self,void *expr);

#endif
