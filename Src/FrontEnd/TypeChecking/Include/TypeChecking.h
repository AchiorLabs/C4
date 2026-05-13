#ifndef ACHIOR_LABS_FRONTEND_TYPECHECKING_H
#define ACHIOR_LABS_FRONTEND_TYPECHECKING_H

#include "../../AST/Include/AST.h"
#include "../../ModuleSystem/Include/Module.h"




struct TypeChecking
{
    struct Module *module;
    struct ASTProgram *program;
    u64 globalCounter;
    struct HashMap symbols;
    struct BumpAllocator *bump;
};


bool TypeCheckingNew(struct TypeChecking *self,struct Module *module,u64 globalCounter,struct BumpAllocator *bump);

bool TypeCheckingType(struct TypeChecking *self,struct ASTType *type);

u64 TypeCheckingDecodeSize(struct TypeChecking *self,struct ASTExpression *expr);

bool TypeCheckingBuildLayout(struct TypeChecking *self,struct ASTType *type);

void TypeCheckingProgram(struct TypeChecking *self,struct ASTProgram *program);

void TypeCheckingDeclaration(struct TypeChecking *self,struct ASTDeclaration *decl);

void TypeCheckingStructDecl(struct TypeChecking *self,struct ASTStructDecl *decl);

void TypeCheckingUnionDecl(struct TypeChecking *self,struct ASTUnionDecl *decl);

void TypeCheckingImplDecl(struct TypeChecking *self,struct ASTImplDecl *decl);

void TypeCheckingFunctionDecl(struct TypeChecking *self,struct ASTFunctionDecl *decl);

void TypeCheckingFunctionArgument(struct TypeChecking *self,struct ASTFunctionArgument *argument);

void TypeCheckingBlockStmt(struct TypeChecking *self,struct ASTBlockStmt *block);

void TypeCheckingStmt(struct TypeChecking *self,struct ASTStatement *stmt);

void TypeCheckingExpressionStmt(struct TypeChecking *self,struct ASTExpression *stmt);

void TypeCheckingVariableDeclStmt(struct TypeChecking *self,struct ASTVariableDecl *stmt);

void TypeCheckingVariableDeclInit(struct TypeChecking *self,struct ASTVariableDeclInit *init);

void TypeCheckingIfStmt(struct TypeChecking *self,struct ASTIfStmt *stmt);

void TypeCheckingContinueStmt(struct TypeChecking *self,struct ASTContinueStmt *stmt);

void TypeCheckingBreakStmt(struct TypeChecking *self,struct ASTBreakStmt *stmt);

void TypeCheckingWhileStmt(struct TypeChecking *self,struct ASTWhileStmt *stmt);

void TypeCheckingLoopStmt(struct TypeChecking *self,struct ASTLoopStmt *stmt);

void TypeCheckingReturnStmt(struct TypeChecking *self,struct ASTReturnStmt *stmt);

void TypeCheckingExpression(struct TypeChecking *self,struct ASTExpression *expr);


void TypeCheckingStructPointerAccessExpr(struct TypeChecking *self,struct ASTStructPointerAccessExpr *expr);

void TypeCheckingStructAccessExpr(struct TypeChecking *self,struct ASTStructAccessExpr *expr);

void TypeCheckingMethodExpr(struct TypeChecking *self,struct ASTMethodExpr *expr);

void TypeCheckingLenExpr(struct TypeChecking *self,struct ASTLenExpr *expr);

void TypeCheckingAsPtrExpr(struct TypeChecking *self,struct ASTAsPtrExpr *expr);

void TypeCheckingSubscriptExpr(struct TypeChecking *self,struct ASTSubscriptExpr *expr);

void TypeCheckingPtrDiffExpr(struct TypeChecking *self,struct ASTPtrDiffExpr *expr);

void TypeCheckingPtrAdvanceExpr(struct TypeChecking *self,struct ASTPtrAdvanceExpr *expr);

void TypeCheckingPtrByteOffsetExpr(struct TypeChecking *self,struct ASTPtrByteOffsetExpr *expr);

void TypeCheckingPtrOffsetExpr(struct TypeChecking *self,struct ASTPtrOffsetExpr *expr);

void TypeCheckingPtrWriteExpr(struct TypeChecking *self,struct ASTPtrWriteExpr *expr);

void TypeCheckingPtrReadExpr(struct TypeChecking *self,struct ASTPtrReadExpr *expr);

void TypeCheckingAddressOfExpr(struct TypeChecking *self,struct ASTAddressOfExpr *expr);

void TypeCheckingFunctionCallExpr(struct TypeChecking *self,struct ASTFunctionCallExpr *expr);

void TypeCheckingCastExpr(struct TypeChecking *self,struct ASTCastExpr *expr);

void TypeCheckingAssignmentExpr(struct TypeChecking *self,struct ASTAssignmentExpr *expr);

void TypeCheckingBinaryExpr(struct TypeChecking *self,struct ASTBinaryExpr *expr);

void TypeCheckingUnaryExpr(struct TypeChecking *self,struct ASTUnaryExpr *expr);

void TypeCheckingParenExpr(struct TypeChecking *self,struct ASTParenExpr *expr);

void TypeCheckingVariableExpr(struct TypeChecking *self,struct ASTVariableExpr *expr);

void TypeCheckingLiteralExpr(struct TypeChecking *self,struct ASTLiteralExpr *expr);

struct ASTType *TypeCheckingBuildBuiltIn(struct TypeChecking *self,enum ASTDataType dataType);

struct Layout TypeCheckingGetBuiltInLayout(struct TypeChecking *self,enum ASTDataType type);

bool TypeCheckingIsLvalue(struct TypeChecking *self,struct ASTExpression *expr);
#endif