#ifndef ACHIOR_LABS_TREE_WALKER_H
#define ACHIOR_LABS_TREE_WALKER_H

#include "../../AST/Include/AST.h"

enum TreeWalkerValueType
{
    TREE_WALKER_VALUE_NONE,
    TREE_WALKER_VALUE_I32,
};



struct TreeWalkerValue
{
    enum TreeWalkerValueType type;
    void *value;
};



bool TreeWalkerValueNew(struct TreeWalkerValue *self,enum TreeWalkerValueType type,void *value);


struct TreeWalker
{
    struct ASTProgram *ast_program;
    FILE *output_file_handle;
};

bool TreeWalkerNew(struct TreeWalker *self,struct ASTProgram *ast_program,char *output_file_name);

void TreeWalkerProgram(struct TreeWalker *self,struct ASTProgram *ast_program);
void TreeWalkerDecl(struct TreeWalker *self,struct ASTDeclaration *ast_decl);

void TreeWalkerIdentifier(struct TreeWalker *self,struct Token ident);
void TreeWalkerFunctionDecl(struct TreeWalker *self,struct ASTFunctionDecl *ast_fn);
void TreeWalkerFunctionArgument(struct TreeWalker *self,struct ASTFunctionArgument *ast_fn_arg);

void TreeWalkerGetDataType(struct TreeWalker *self,enum ASTDataType ast_type);


void TreeWalkerType(struct TreeWalker *self,struct ASTType *ast_type);

void TreeWalkerBlockStmt(struct TreeWalker *self,struct ASTBlockStmt *ast_block);


void TreeWalkerStmt(struct TreeWalker *self,struct ASTStatement *astStmt);



void TreeWalkerReturnStmt(struct TreeWalker *self,struct ASTReturnStmt *astStmt);



struct TreeWalkerValue TreeWalkerExpr(struct TreeWalker *self,struct ASTExpression *expr);


struct TreeWalkerValue TreeWalkerBinaryExpr(struct TreeWalker *self,void *expr);


struct TreeWalkerValue TreeWalkerBinaryOperator(struct TreeWalker *self,struct TreeWalkerValue lhs,enum ASTBinaryOperator op,struct TreeWalkerValue rhs);

struct TreeWalkerValue TreeWalkerUnaryExpr(struct TreeWalker *self,void *expr);
struct TreeWalkerValue TreeWalkerUnaryOperator(struct TreeWalker *self,enum ASTUnaryOperator op,struct TreeWalkerValue  rhs);


struct TreeWalkerValue TreeWalkerLiteralExpr(struct TreeWalker *self,void *expr);


#endif
