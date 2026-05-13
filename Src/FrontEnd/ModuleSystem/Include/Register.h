#ifndef ACHIOR_LABS_MODULESYSTEM_REGISTER_H
#define ACHIOR_LABS_MODULESYSTEM_REGISTER_H

#include "Module.h"




bool ModuleSystemRegisterImplDecl(struct ModuleSystem *self,struct Module *module,struct ASTImplDecl *decl);

bool ModuleSystemRegisterStructDecl(struct ModuleSystem *self,struct Module *module,struct ASTStructDecl *decl);

bool ModuleSystemRegisterEnumDecl(struct ModuleSystem *self,struct Module *module,struct ASTEnumDecl *decl);

bool ModuleSystemRegisterFunctionDecl(struct ModuleSystem *self,struct Module *module,struct ASTFunctionDecl *decl);

void ModuleSystemRegisterFunctionArgument(struct ModuleSystem *self,struct Module *module,struct ASTFunctionArgument *stmt);


void ModuleSystemRegisterBlockStmt(struct ModuleSystem *self,struct Module *module,struct ASTBlockStmt *block);

void ModuleSystemRegisterStmt(struct ModuleSystem *self,struct Module *module,struct ASTStatement *stmt);

void ModuleSystemRegisterExpressionStmt(struct ModuleSystem *self,struct Module *module,struct ASTExpression *stmt);

void ModuleSystemRegisterVariableDeclStmt(struct ModuleSystem *self,struct Module *module,struct ASTVariableDecl *stmt);

void ModuleSystemRegisterIfStmt(struct ModuleSystem *self,struct Module *module,struct ASTIfStmt *stmt);

void ModuleSystemRegisterContinueStmt(struct ModuleSystem *self,struct Module *module,struct ASTContinueStmt *stmt);

void ModuleSystemRegisterBreakStmt(struct ModuleSystem *self,struct Module *module,struct ASTBreakStmt *stmt);

void ModuleSystemRegisterWhileStmt(struct ModuleSystem *self,struct Module *module,struct ASTWhileStmt *stmt);

void ModuleSystemRegisterLoopStmt(struct ModuleSystem *self,struct Module *module,struct ASTLoopStmt *stmt);

void ModuleSystemRegisterReturnStmt(struct ModuleSystem *self,struct Module *module,struct ASTReturnStmt *stmt);



bool ModuleSystemRegisterAllSymbols(struct ModuleSystem *self);


#endif