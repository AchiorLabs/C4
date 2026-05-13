#include "Include/Module.h"





bool ModuleStructMemberEntryNew(struct ModuleStructMemberEntry *self,struct String ident,struct ASTType *type,u64 offset)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ident  = ident;
    self->type   = type;
    self->offset = offset;

    return true;
}




bool ModuleStructEntryNew(struct ModuleStructEntry *self,struct String ident,struct Layout layout,struct HashMap members)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->ident   = ident;
    self->layout  = layout;
    self->members = members;

    return true;
}



bool ModuleSymbolNew(struct ModuleSymbol *self,enum ModuleSymbolKind kind,struct Token *ident,void *decl,bool isPublic,struct Module *owner)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->kind     = kind;
    self->ident    = ident;
    self->decl     = decl;
    self->isPublic = isPublic;
    self->owner    = owner;

    return true;
}



bool ModuleNew(struct Module *self,struct String fullPath,struct ASTProgram *ast,char *workingDirectory,char *directory,char *fileName,struct HashMap imports,struct HashMap symbols)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->fullPath         = fullPath;
    self->ast              = ast;
    self->workingDirectory = workingDirectory;
    self->directory        = directory;
    self->fileName         = fileName; 
    self->imports          = imports;
    self->symbols          = symbols;

    return true;
}



bool ModuleImportNew(struct ModuleImport *self,struct Token *alias,struct String targetPath,struct Module *target)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->alias      = alias;
    self->targetPath = targetPath;
    self->target     = target;

    return true;
}



bool ModuleRegistryNew(struct ModuleRegistry *self,struct HashMap modules)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->modules = modules;

    return true;
}




bool FileTreeNodeNew(struct FileTreeNode *self,enum FileTreeNodeType type,struct String name,struct String fullPath,struct LinkedList children)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->type     = type;
    self->name     = name;
    self->fullPath = fullPath;
    self->children = children;

    return true;
}


