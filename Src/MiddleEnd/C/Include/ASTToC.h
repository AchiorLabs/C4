#ifndef ACHIOR_LABS_AST_TO_C_H
#define ACHIOR_LABS_AST_TO_C_H

#include "../../Include/Include.h"


struct ASTToC
{
    struct LinkedList modules;
    char *cFileName;
    char *hFileName;
    FILE *cFileHandle;
    FILE *hFileHandle;
    struct BumpAllocator *bump;
};



bool ASTToCNew(struct ASTToC *self,struct LinkedList modules,char *fileName,struct BumpAllocator *bump);


void ASTToCType(struct ASTToC *self,struct ASTType *type,struct LinkedList *arrayBuffer,bool cFile);

void ASTToCIdentifier(struct ASTToC *self,struct Token *ident,bool cFile);

void ASTToCProgram(struct ASTToC *self,struct ASTProgram *program);

void ASTToCDecl(struct ASTToC *self,struct ASTDeclaration *decl);



void ASTToCUseDecl(struct ASTToC *self,struct ASTUseDecl *decl);

void ASTToCEnumDecl(struct ASTToC *self,struct ASTEnumDecl *decl);

void ASTToCEnumConstant(struct ASTToC *self,struct ASTEnumConstant  *constant);

void ASTToCStructDecl(struct ASTToC *self,struct ASTStructDecl *decl,bool isStruct);

void ASTToCStructProperty(struct ASTToC *self,struct ASTStructProperty *property);

void ASTToCImplDecl(struct ASTToC *self,struct ASTImplDecl *decl);

void ASTToCSumDecl(struct ASTToC *self,struct ASTSumDecl *decl);

void ASTToCSumEnum(struct ASTToC *self,char *ident,struct LinkedList variants);

void ASTToCSumVariants(struct ASTToC *self,struct LinkedList variants);

void ASTToCFunctionDecl(struct ASTToC *self,struct ASTFunctionDecl *function);

void ASTToCFunctionArgument(struct ASTToC *self,struct ASTFunctionArgument *argument);

void ASTToCVariableDecl(struct ASTToC *self,struct ASTVariableDecl *stmt);





void ASTToCBlockStmt(struct ASTToC *self,struct ASTBlockStmt *block,char *tab);

void ASTToCStmt(struct ASTToC *self,struct ASTStatement *stmt,char *tab);

void ASTToCReturnStmt(struct ASTToC *self,struct ASTReturnStmt *stmt,char *tab);

void ASTToCLoopStmt(struct ASTToC *self,struct ASTLoopStmt *stmt,char *tab);

void ASTToCWhileStmt(struct ASTToC *self,struct ASTWhileStmt *stmt,char *tab);

void ASTToCBreakStmt(struct ASTToC *self,struct ASTBreakStmt *stmt,char *tab);

void ASTToCContinueStmt(struct ASTToC *self,struct ASTContinueStmt *stmt,char *tab);

void ASTToCIfStmt(struct ASTToC *self,struct ASTIfStmt *stmt,char *tab);

void ASTToCVariableDeclStmt(struct ASTToC *self,struct ASTVariableDecl *stmt,char *tab);

void ASTToCVariableDeclInit(struct ASTToC *self,struct ASTVariableDeclInit *init,bool cFile);

void ASTToCExpressionStmt(struct ASTToC *self,struct ASTExpression *stmt,char *tab);





void ASTToCExpression(struct ASTToC *self,struct ASTExpression *expr,bool cFile);

void ASTToCPathExpr(struct ASTToC *self,struct ASTPathExpr *expr,bool cFile);

char *ASTToCGetStructIdent(struct ASTToC *self,struct ASTType *type,bool *isPointer);

void ASTToCMethodExpr(struct ASTToC *self,struct ASTMethodExpr *expr,bool cFile);

void ASTToCStructAccessExpr(struct ASTToC *self,struct ASTStructAccessExpr *expr,bool cFile);

void ASTToCStructPointerAccessExpr(struct ASTToC *self,struct ASTStructPointerAccessExpr *expr,bool cFile);

void ASTToCLenExpr(struct ASTToC *self,struct ASTLenExpr *expr,bool cFile);

void ASTToCAsPtrExpr(struct ASTToC *self,struct ASTAsPtrExpr *expr,bool cFile);

void ASTToCSubscriptExpr(struct ASTToC *self,struct ASTSubscriptExpr *expr,bool cFile);

void ASTToCPtrDiffExpr(struct ASTToC *self,struct ASTPtrDiffExpr *expr,bool cFile);

void ASTToCPtrAdvanceExpr(struct ASTToC *self,struct ASTPtrAdvanceExpr *expr,bool cFile);

void ASTToCPtrByteOffsetExpr(struct ASTToC *self,struct ASTPtrByteOffsetExpr *expr,bool cFile);

void ASTToCPtrOffsetExpr(struct ASTToC *self,struct ASTPtrOffsetExpr *expr,bool cFile);

void ASTToCPtrWriteExpr(struct ASTToC *self,struct ASTPtrWriteExpr *expr,bool cFile);

void ASTToCPtrReadExpr(struct ASTToC *self,struct ASTPtrReadExpr *expr,bool cFile);

void ASTToCAddressOfExpr(struct ASTToC *self,struct ASTAddressOfExpr *expr,bool cFile);

void ASTToCFunctionCallExpr(struct ASTToC *self,struct ASTFunctionCallExpr *expr,bool cFile);

void ASTToCCastExpr(struct ASTToC *self,struct ASTCastExpr *expr,bool cFile);

void ASTToCAssignmentExpr(struct ASTToC *self,struct ASTAssignmentExpr *expr,bool cFile);

void ASTToCAssignmentOperator(struct ASTToC *self,enum ASTAssignmentOperator op,bool cFile);

void ASTToCBinaryExpr(struct ASTToC *self,struct ASTBinaryExpr *expr,bool cFile);

void ASTToCBinaryOperator(struct ASTToC *self,enum ASTBinaryOperator op,bool cFile);

void ASTToCUnaryExpr(struct ASTToC *self,struct ASTUnaryExpr *expr,bool cFile);

void ASTToCUnaryOperator(struct ASTToC *self,enum ASTUnaryOperator op,bool cFile);

void ASTToCParenExpr(struct ASTToC *self,struct ASTParenExpr *expr,bool cFile);

void ASTToCVariableExpr(struct ASTToC *self,struct ASTVariableExpr *expr,bool cFile);

void ASTToCLiteralExpr(struct ASTToC *self,struct ASTLiteralExpr *expr,bool cFile);


#endif
