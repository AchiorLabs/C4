#ifndef ACHIOR_LABS_FRONTEND_MODULESYSTEM_H
#define ACHIOR_LABS_FRONTEND_MODULESYSTEM_H




#include "Module.h"
#include "Register.h"
#include "ResolveImports.h"
#include "ResolveSymbols.h"
#include "TopologicalSort.h"


struct String StringFromCString(struct ModuleSystem *self, const char *text);

struct String GetBaseName(struct ModuleSystem *self,const char *path);

char *JoinPath(struct ModuleSystem *self,const char *parent, const char *child);

void ModuleSystemDiscoverFiles(struct ModuleSystem *self);

struct FileTreeNode *ModuleSystemDiscoverDirectory(struct ModuleSystem *self,const char *path);

void ModuleSystemFileTreeNodePrint(struct FileTreeNode *node,int depth);

struct String ModuleSystemFilePathToModulePath(struct BumpAllocator *bump,const char *filePath);

struct Module *ModuleSystemCreateModule(struct ModuleSystem *self,const char *filePath);

struct ASTProgram *ModuleSystemParseFile(struct ModuleSystem *self,const char *filePath,char *fullPath,char **fileSource);

struct ModuleRegistry *ModuleSystemCreateModuleRegistry(struct ModuleSystem *self,struct FileTreeNode *root);




#endif