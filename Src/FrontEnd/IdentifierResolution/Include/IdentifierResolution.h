#ifndef ACHIOR_LABS_IDENTIFIER_RESOLUTION_H
#define ACHIOR_LABS_IDENTIFIER_RESOLUTION_H

#include "../../AST/Include/AST.h"

enum IdentifierAggregateKind
{
    IDENTIFIER_AGGREGATE_NONE,
    IDENTIFIER_AGGREGATE_STRUCT,
    IDENTIFIER_AGGREGATE_UNION,
    IDENTIFIER_AGGREGATE_SUM,
};

struct IdentifierEntry
{
    bool hasLinkage;
    bool isCurrent;
    enum IdentifierAggregateKind aggregateKind;
    struct String ident;
};

bool IdentifierEntryNew(struct IdentifierEntry *self,bool hasLinkage,bool isCurrent,enum IdentifierAggregateKind aggregateKind,struct String ident);

struct IdentifierResolution
{
    struct ASTProgram *program;
    u64 globalCounter;
    struct HashMap functionAttributes;
    struct HashMap structMap;
    struct BumpAllocator *bump;
};



bool IdentifierResolutionNew(struct IdentifierResolution *self,struct ASTProgram *program,char *fileName,u64 globalCounter,struct BumpAllocator *bump);

void IdentifierResolutionProgram(struct IdentifierResolution *self,struct ASTProgram *program,struct HashMap *identMap);

void IdentifierResolutionDeclaration(struct IdentifierResolution *self,struct ASTDeclaration *decl,struct HashMap *identMap);


void IdentifierResolutionStructDecl(struct IdentifierResolution *self,struct ASTStructDecl *decl,struct HashMap *identMap);
void IdentifierResolutionStructProperty(struct IdentifierResolution *self,struct ASTStructProperty *property,struct HashMap *identMap);

void IdentifierResolutionUnionDecl(struct IdentifierResolution *self,struct ASTUnionDecl *decl,struct HashMap *identMap);


void IdentifierResolutionImplDecl(struct IdentifierResolution *self,struct ASTImplDecl *decl,struct HashMap *identMap);

void IdentifierResolutionSumDecl(struct IdentifierResolution *self,struct ASTSumDecl *decl,struct HashMap *identMap);

void IdentifierResolutionSumEnum(struct IdentifierResolution *self,char *ident,struct LinkedList variants,struct HashMap *identMap);

void IdentifierResolutionSumVariants(struct IdentifierResolution *self,struct LinkedList variants,struct HashMap *identMap);

void IdentifierResolutionFunctionDecl(struct IdentifierResolution *self,struct ASTFunctionDecl *function,struct HashMap *identMap);
void IdentifierResolutionFunctionArgument(struct IdentifierResolution *self,struct ASTFunctionArgument *argument,struct HashMap *identMap);


void IdentifierResolutionBlockStmt(struct IdentifierResolution *self,struct ASTBlockStmt *block,struct HashMap *identMap);


void IdentifierResolutionStmt(struct IdentifierResolution *self,struct ASTStatement *stmt,struct HashMap *identMap);



void IdentifierResolutionReturnStmt(struct IdentifierResolution *self,struct ASTReturnStmt *stmt,struct HashMap *identMap);
void IdentifierResolutionLoopStmt(struct IdentifierResolution *self,struct ASTLoopStmt *stmt,struct HashMap *identMap);
void IdentifierResolutionWhileStmt(struct IdentifierResolution *self,struct ASTWhileStmt *stmt,struct HashMap *identMap);
void IdentifierResolutionBreakStmt(struct IdentifierResolution *self,struct ASTBreakStmt *stmt,struct HashMap *identMap);
void IdentifierResolutionContinueStmt(struct IdentifierResolution *self,struct ASTContinueStmt *stmt,struct HashMap *identMap);
void IdentifierResolutionIfStmt(struct IdentifierResolution *self,struct ASTIfStmt *stmt,struct HashMap *identMap);void IdentifierResolutionVariableDeclStmt(struct IdentifierResolution *self,struct ASTVariableDecl *stmt,struct HashMap *identMap);
void IdentifierResolutionVariableDeclInit(struct IdentifierResolution *self,struct ASTVariableDeclInit *init,struct HashMap *identMap);
void IdentifierResolutionExpressionStmt(struct IdentifierResolution *self,struct ASTExpression *stmt,struct HashMap *identMap);



void IdentifierResolutionExpression(struct IdentifierResolution *self,struct ASTExpression *expr,struct HashMap *identMap);



void IdentifierResolutionLiteralExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);


void IdentifierResolutionVariableExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);


void IdentifierResolutionUnaryExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);
void IdentifierResolutionUnaryOperator(struct IdentifierResolution *self,enum ASTUnaryOperator op,struct HashMap *identMap);

void IdentifierResolutionBinaryExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);
void IdentifierResolutionBinaryOperator(struct IdentifierResolution *self,enum ASTBinaryOperator op,struct HashMap *identMap);

void IdentifierResolutionAssignmentExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionAssignmentOperator(struct IdentifierResolution *self,enum ASTAssignmentOperator op,struct HashMap *identMap);

void IdentifierResolutionFunctionCallExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionCastExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionAddressOfExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrReadExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrWriteExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrOffsetExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrByteOffsetExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrAdvanceExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionPtrDiffExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionSubscriptExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionAsPtrExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);

void IdentifierResolutionLenExpr(struct IdentifierResolution *self,void *expr,struct HashMap *identMap);


struct String IdentifierResolutionMakeTmp(struct IdentifierResolution *self);

#endif
