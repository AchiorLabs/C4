#ifndef ACHIOR_LABS_IDENTIFIER_RESOLUTION_H
#define ACHIOR_LABS_IDENTIFIER_RESOLUTION_H

#include "../../AST/Include/AST.h"

enum IdentifierAggregateKind
{
    IDENTIFIER_AGGREGATE_NONE,
    IDENTIFIER_AGGREGATE_STRUCT,
    IDENTIFIER_AGGREGATE_ENUM,
    IDENTIFIER_AGGREGATE_UNION,
    IDENTIFIER_AGGREGATE_SUM,
    IDENTIFIER_AGGREGATE_TYPE_ALIAS,
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
    char *moduleName;
    char *moduleSource;
    u64 sourceLength;
    struct HashMap functionAttributes;
    struct HashMap structMap;
    struct DiagnosticEngine *engine;
    struct BumpAllocator *bump;
};


bool IdentifierResolutionNew(struct IdentifierResolution *self,char *moduleName,char *moduleSource,struct ASTProgram *program,u64 globalCounter,struct DiagnosticEngine *engine,struct BumpAllocator *bump);

void IdentifierResolutionProgram(struct IdentifierResolution *self,struct ASTProgram *program,struct HashMap *identMap);

void IdentifierResolutionDeclaration(struct IdentifierResolution *self,struct ASTDeclaration *decl,struct HashMap *identMap);

void IdentifierResolutionType(struct IdentifierResolution *self,struct ASTType *type);


void IdentifierResolutionEnumDecl(struct IdentifierResolution *self,struct ASTEnumDecl *decl,struct HashMap *identMap);

void IdentifierResolutionStructDecl(struct IdentifierResolution *self,struct ASTStructDecl *decl,struct HashMap *identMap);
void IdentifierResolutionStructProperty(struct IdentifierResolution *self,struct ASTStructProperty *property,struct HashMap *identMap);


void IdentifierResolutionImplDecl(struct IdentifierResolution *self,struct ASTImplDecl *decl,struct HashMap *identMap);

void IdentifierResolutionSumDecl(struct IdentifierResolution *self,struct ASTSumDecl *decl,struct HashMap *identMap);

void IdentifierResolutionSumEnum(struct IdentifierResolution *self,char *ident,struct LinkedList variants,struct HashMap *identMap);

void IdentifierResolutionSumVariants(struct IdentifierResolution *self,struct LinkedList variants,struct HashMap *identMap);

void IdentifierResolutionFunctionDecl(struct IdentifierResolution *self,struct ASTFunctionDecl *function,struct String structIdent,struct HashMap *identMap);
void IdentifierResolutionFunctionArgument(struct IdentifierResolution *self,struct ASTFunctionArgument *argument,struct HashMap *identMap);

void IdentifierResolutionVariableDecl(struct IdentifierResolution *self,struct ASTVariableDecl *decl,struct HashMap *identMap);

void IdentifierResolutionTypeDecl(struct IdentifierResolution *self,struct ASTTypeDecl *decl,struct HashMap *identMap);

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

void IdentifierResolutionPathExpr(struct IdentifierResolution *self,struct ASTPathExpr *expr,struct HashMap *identMap);

void IdentifierResolutionMethodExpr(struct IdentifierResolution *self,struct ASTMethodExpr *expr,struct HashMap *identMap);

void IdentifierResolutionStructPointerAccessExpr(struct IdentifierResolution *self,struct ASTStructPointerAccessExpr *expr,struct HashMap *identMap);

void IdentifierResolutionStructAccessExpr(struct IdentifierResolution *self,struct ASTStructAccessExpr *expr,struct HashMap *identMap);

void IdentifierResolutionLenExpr(struct IdentifierResolution *self,struct ASTLenExpr *expr,struct HashMap *identMap);

void IdentifierResolutionAsPtrExpr(struct IdentifierResolution *self,struct ASTAsPtrExpr *expr,struct HashMap *identMap);

void IdentifierResolutionSubscriptExpr(struct IdentifierResolution *self,struct ASTSubscriptExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrDiffExpr(struct IdentifierResolution *self,struct ASTPtrDiffExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrAdvanceExpr(struct IdentifierResolution *self,struct ASTPtrAdvanceExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrByteOffsetExpr(struct IdentifierResolution *self,struct ASTPtrByteOffsetExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrOffsetExpr(struct IdentifierResolution *self,struct ASTPtrOffsetExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrWriteExpr(struct IdentifierResolution *self,struct ASTPtrWriteExpr *expr,struct HashMap *identMap);

void IdentifierResolutionPtrReadExpr(struct IdentifierResolution *self,struct ASTPtrReadExpr *expr,struct HashMap *identMap);

void IdentifierResolutionAddressOfExpr(struct IdentifierResolution *self,struct ASTAddressOfExpr *expr,struct HashMap *identMap);

void IdentifierResolutionFunctionCallExpr(struct IdentifierResolution *self,struct ASTFunctionCallExpr *expr,struct HashMap *identMap);

void IdentifierResolutionCastExpr(struct IdentifierResolution *self,struct ASTCastExpr *expr,struct HashMap *identMap);

void IdentifierResolutionAssignmentExpr(struct IdentifierResolution *self,struct ASTAssignmentExpr *expr,struct HashMap *identMap);

void IdentifierResolutionBinaryExpr(struct IdentifierResolution *self,struct ASTBinaryExpr *expr,struct HashMap *identMap);

void IdentifierResolutionUnaryExpr(struct IdentifierResolution *self,struct ASTUnaryExpr *expr,struct HashMap *identMap);

void IdentifierResolutionParenExpr(struct IdentifierResolution *self,struct ASTParenExpr *expr,struct HashMap *identMap);

void IdentifierResolutionVariableExpr(struct IdentifierResolution *self,struct ASTVariableExpr *expr,struct HashMap *identMap);

struct String IdentifierResolutionMakeTmp(struct IdentifierResolution *self);


#endif
