#ifndef ACHIOR_LABS_FRONTEND_MODULESYSTEM_H
#define ACHIOR_LABS_FRONTEND_MODULESYSTEM_H


#include "../../../C4COptions/Include/C4COptions.h"
#include "../../Lexer/Include/Lexer.h"
#include "../../Parser/Include/Parser.h"

struct Module
{
    struct String fullPath; // core::ops
    struct ASTProgram *ast;

    struct HashMap imports;
    struct HashMap symbols;
};


bool ModuleNew(struct Module *self,struct String fullPath,struct ASTProgram *ast,struct HashMap imports,struct HashMap symbols);



struct ModuleImport
{
    struct Token alias;
    struct String targetPath; // core::ops

    struct Module *target;
};


bool ModuleImportNew(struct ModuleImport *self,struct Token alias,struct String targetPath,struct Module *target);


struct ModuleRegistry
{
    struct HashMap modules;
};


bool ModuleRegistryNew(struct ModuleRegistry *self,struct HashMap modules);

enum FileTreeNodeType
{
    FILE_TREE_NODE_NONE,
    FILE_TREE_NODE_FILE,
    FILE_TREE_NODE_DIRECTORY
};


struct FileTreeNode
{
    enum FileTreeNodeType type;
    struct String name;

    // full path is useful
    struct String fullPath;
    
    // only used if DIRECTORY
    struct LinkedList children;
};


bool FileTreeNodeNew(struct FileTreeNode *self,enum FileTreeNodeType type,struct String name,struct String fullPath,struct LinkedList children);


struct ModuleSystem
{
    struct C4CFrontEndOptions *options;
    struct ModuleRegistry *registry;
    struct BumpAllocator *bump;
};




bool ModuleNew(struct Module *self,struct String fullPath,struct ASTProgram *ast,struct HashMap imports,struct HashMap symbols);

bool ModuleImportNew(struct ModuleImport *self,struct Token alias,struct String targetPath,struct Module *target);

bool ModuleRegistryNew(struct ModuleRegistry *self,struct HashMap modules);

bool FileTreeNodeNew(struct FileTreeNode *self,enum FileTreeNodeType type,struct String name,struct String fullPath,struct LinkedList children);

bool ModuleSystemNew(struct ModuleSystem *self,struct BumpAllocator *bump,struct C4CFrontEndOptions *options);

struct String StringFromCString(struct ModuleSystem *self, const char *text);

struct String GetBaseName(struct ModuleSystem *self,const char *path);

char *JoinPath(struct ModuleSystem *self,const char *parent, const char *child);

void ModuleSystemDiscoverFiles(struct ModuleSystem *self);

struct FileTreeNode *ModuleSystemDiscoverDirectory(struct ModuleSystem *self,const char *path);

void ModuleSystemFileTreeNodePrint(struct FileTreeNode *node,int depth);

struct String ModuleSystemFilePathToModulePath(struct ModuleSystem *self,const char *filePath);

struct Module *ModuleSystemCreateModule(struct ModuleSystem *self,const char *filePath);


struct ASTProgram *ModuleSystemParseFile(struct ModuleSystem *self,char *filePath);

struct ModuleRegistry *ModuleSystemCreateModuleRegistry(struct ModuleSystem *self,struct FileTreeNode *root);


bool ModuleSystemCollectAllImports(struct ModuleSystem *self,struct FileTreeNode *fileTree);


bool ModuleSystemResolveAllImports(struct ModuleSystem *self);

#endif