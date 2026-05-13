#ifndef ACHIOR_LABS_MODULESYSTEM_RESOLVE_SYMBOLS_H
#define ACHIOR_LABS_MODULESYSTEM_RESOLVE_SYMBOLS_H

#include "Module.h"


bool ModuleSystemResolveSymbolIdentifiers(struct ModuleSystem *self,struct Module *module);

bool ModuleSystemResolveSymbolFunctionDecl(struct ModuleSystem *self,struct Module *module,struct ASTFunctionDecl *decl);

bool ModuleSystemResolveSymbolEnumDecl(struct ModuleSystem *self,struct Module *module,struct ASTEnumDecl *decl);

bool ModuleSystemResolveSymbolStructDecl(struct ModuleSystem *self,struct Module *module,struct ASTStructDecl *decl);

bool ModuleSystemResolveSymbolImplDecl(struct ModuleSystem *self,struct Module *module,struct ASTImplDecl *decl);


bool ModuleSystemResolveSymbolFunctionArgument(struct ModuleSystem *self,struct Module *module,struct ASTFunctionArgument *stmt);

bool ModuleSystemResolveSymbolBlockStmt(struct ModuleSystem *self,struct Module *module,struct ASTBlockStmt *block);

bool ModuleSystemResolveSymbolStatement(struct ModuleSystem *self,struct Module *module,struct ASTStatement *stmt);


bool ModuleSystemResolveSymbolIfStmt(struct ModuleSystem *self,struct Module *module,struct ASTIfStmt *stmt);

bool ModuleSystemResolveSymbolWhileStmt(struct ModuleSystem *self,struct Module *module,struct ASTWhileStmt *stmt);

bool ModuleSystemResolveSymbolVariableDeclStmt(struct ModuleSystem *self,struct Module *module,struct ASTVariableDecl *stmt);

bool ModuleSystemResolveSymbolReturnStmt(struct ModuleSystem *self,struct Module *module,struct ASTReturnStmt *stmt);

bool ModuleSystemResolveSymbolExpressionStmt(struct ModuleSystem *self,struct Module *module,struct ASTExpression *stmt);


bool ModuleSystemResolveSymbolExpression(struct ModuleSystem *self,struct Module *module,struct ASTExpression *expr);


bool ModuleSystemResolveSymbolPathExpr(struct ModuleSystem *self,struct Module *module,struct ASTPathExpr *expr);


bool ModuleSystemResolveSymbolStructPointerAccessExpr(struct ModuleSystem *self,struct Module *module,struct ASTStructPointerAccessExpr *expr);

bool ModuleSystemResolveSymbolStructAccessExpr(struct ModuleSystem *self,struct Module *module,struct ASTStructAccessExpr *expr);

bool ModuleSystemResolveSymbolMethodExpr(struct ModuleSystem *self,struct Module *module,struct ASTMethodExpr *expr);

bool ModuleSystemResolveSymbolFunctionCallExpr(struct ModuleSystem *self,struct Module *module,struct ASTFunctionCallExpr *expr);

bool ModuleSystemResolveSymbolAssignmentExpr(struct ModuleSystem *self,struct Module *module,struct ASTAssignmentExpr *expr);

bool ModuleSystemResolveSymbolBinaryExpr(struct ModuleSystem *self,struct Module *module,struct ASTBinaryExpr *expr);

bool ModuleSystemResolveSymbolUnaryExpr(struct ModuleSystem *self,struct Module *module,struct ASTUnaryExpr *expr);

bool ModuleSystemResolveSymbolParenExpr(struct ModuleSystem *self,struct Module *module,struct ASTParenExpr *expr);

bool ModuleSystemResolveSymbolVariableExpr(struct ModuleSystem *self,struct Module *module,struct ASTVariableExpr *expr);

bool ModuleSystemResolveSymbolAllIdentifiers(struct ModuleSystem *self);


bool ModuleSystemTypeCheckAll(struct ModuleSystem *self);


#endif