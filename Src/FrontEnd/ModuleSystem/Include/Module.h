#ifndef ACHIOR_LABS_FRONTEND_MODULE_H
#define ACHIOR_LABS_FRONTEND_MODULE_H


#include "../../../C4COptions/Include/C4COptions.h"
#include "../../Lexer/Include/Lexer.h"
#include "../../Parser/Include/Parser.h"


enum ModuleSymbolKind
{
    MODULE_SYMBOL_FUNCTION = 1,
    MODULE_SYMBOL_STRUCT,
    MODULE_SYMBOL_ENUM,
    MODULE_SYMBOL_VARIABLE,
    MODULE_SYMBOL_CONST,
    MODULE_SYMBOL_GLOBAL,
    MODULE_SYMBOL_TYPE_ALIAS,
};


struct ModuleStructMemberEntry
{
    struct String ident;
    struct ASTType *type;
    u64 offset;
};


bool ModuleStructMemberEntryNew(struct ModuleStructMemberEntry *self,struct String ident,struct ASTType *type,u64 offset);



struct ModuleStructEntry
{
    struct String ident;
    struct Layout layout;
    struct HashMap members;
};


bool ModuleStructEntryNew(struct ModuleStructEntry *self,struct String ident,struct Layout layout,struct HashMap members);



struct ModuleSymbol
{
    enum ModuleSymbolKind kind;
    struct Token *ident;
    void *decl;
    bool isPublic;
    struct Module *owner;
    struct ModuleStructEntry entry;
    struct ASTType *type;
};


bool ModuleSymbolNew(struct ModuleSymbol *self,enum ModuleSymbolKind kind,struct Token *ident,void *decl,bool isPublic,struct Module *owner);


enum ModuleVisitState
{
    MODULE_VISIT_UNVISITED,
    MODULE_VISIT_VISITING,
    MODULE_VISIT_VISITED
};

struct Module
{
    struct String fullPath; // core::ops
    struct ASTProgram *ast;

    char *workingDirectory;
    char *directory;
    char *fileName;


    char *moduleName;
    char *moduleSource;
    u64 sourceLength;

    enum ModuleVisitState visitState;

    struct HashMap imports;
    struct HashMap symbols;
};


bool ModuleNew(struct Module *self,struct String fullPath,struct ASTProgram *ast,char *workingDirectory,char *directory,char *fileName,struct HashMap imports,struct HashMap symbols);



struct ModuleImport
{
    struct Token *alias;
    struct String targetPath; // core::ops

    struct Module *target;
};


bool ModuleImportNew(struct ModuleImport *self,struct Token *alias,struct String targetPath,struct Module *target);


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
    struct LinkedList order;
    char *moduleName;
    char *moduleSource;
    u64 sourceLength;
    struct DiagnosticEngine *engine;
    struct BumpAllocator *bump;
};



bool ModuleSystemNew(struct ModuleSystem *self,struct DiagnosticEngine *engine,struct BumpAllocator *bump,struct C4CFrontEndOptions *options);


#endif


