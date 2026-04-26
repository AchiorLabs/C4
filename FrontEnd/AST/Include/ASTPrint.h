#ifndef ACHIOR_LABS_AST_PRINT_H
#define ACHIOR_LABS_AST_PRINT_H

#include "AST.h"


struct ASTPrint
{
    struct ASTProgram *ast_program;
    FILE *output_file_handle;
};

bool ASTPrintNew(struct ASTPrint *self,struct ASTProgram *ast_program,char *output_file_name);

void ASTPrintProgram(struct ASTPrint *self,struct ASTProgram *ast_program);
void ASTPrintDecl(struct ASTPrint *self,struct ASTDeclaration *ast_decl);

void ASTPrintIdentifier(struct ASTPrint *self,struct Token ident);
void ASTPrintFunctionDecl(struct ASTPrint *self,struct ASTFunctionDecl *ast_fn);
void ASTPrintFunctionArgument(struct ASTPrint *self,struct ASTFunctionArgument *ast_fn_arg);

void ASTPrintGetDataType(struct ASTPrint *self,enum ASTDataType ast_type);


void ASTPrintType(struct ASTPrint *self,struct ASTType *ast_type);

void ASTPrintBlockStmt(struct ASTPrint *self,struct ASTBlockStmt *ast_block);


void ASTPrintStmt(struct ASTPrint *self,struct ASTStatement *astStmt);



void ASTPrintReturnStmt(struct ASTPrint *self,struct ASTReturnStmt *astStmt);



void ASTPrintExpr(struct ASTPrint *self,struct ASTExpression *expr);


void ASTPrintBinaryExpr(struct ASTPrint *self,void *expr);


void ASTPrintBinaryOperator(struct ASTPrint *self,enum ASTBinaryOperator op);

void ASTPrintUnaryExpr(struct ASTPrint *self,void *expr);
void ASTPrintUnaryOperator(struct ASTPrint *self,enum ASTUnaryOperator op);


void ASTPrintLiteralExpr(struct ASTPrint *self,void *expr);


#endif
