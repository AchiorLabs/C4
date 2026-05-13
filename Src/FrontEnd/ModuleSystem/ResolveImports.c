#include "Include/ResolveImports.h"




struct String ModuleSystemPathFromList(struct BumpAllocator *bump,struct LinkedList list)
{
    struct String path;
    StringNew(&path,10,bump);

    for(u64 i = 0; i < list.len; i++)
    {
        char *name = LinkedListAt(&list,i);
        StringPushBack(&path,name);

        if(ACHIOR_LABS_LESS(i,list.len - 1))
        {
            StringPushBack(&path,"::");
        }
    }

    return path;
}




bool ModuleSystemCollectImports(struct ModuleSystem *self,struct Module *module)
{
    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(module) || ACHIOR_LABS_NULL(module->ast))
    {
        return false;
    }
    

    for(u64 i = 0; i < module->ast->decls.len; i++)
    {
        struct ASTDeclaration *decl = LinkedListAt(&module->ast->decls,i);

        if(ACHIOR_LABS_NOT_EQUAL(ASTDECLARATION_GET_KIND(*decl),AST_DECLARATION_USE))
        {
            continue;
        }


        struct ASTUseDecl *useDecl  = (struct ASTUseDecl *)decl->decl;
        struct ModuleImport *import = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct ModuleImport,1);
        useDecl->import             = import;
        struct String fullPath      = ModuleSystemPathFromList(self->bump,useDecl->path);

        ModuleImportNew(import,useDecl->alias,fullPath,NULL);


        HashMapAdd(&module->imports,TOKEN_GET_VALUE_DATA(*(useDecl->alias)),TOKEN_GET_VALUE_SIZE(*(useDecl->alias)),import);
    }
}




bool ModuleSystemCollectAllImports(struct ModuleSystem *self,struct FileTreeNode *fileTree)
{
    struct FileTreeNode *newFileTree = fileTree;

    for(u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for (struct HashNode *node = self->registry->modules.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct Module *module   = node->value;

            ModuleSystemCollectImports(self,module);
        }
    }
}







bool ModuleSystemResolveImports(struct ModuleSystem *self,struct Module *module)
{

    for(u64 i = 0; i < module->imports.capacity; i++)
    {
        for (struct HashNode *node = module->imports.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct ModuleImport *import = node->value;
            struct Module *target       = HashMapGet(&self->registry->modules,import->targetPath.data,import->targetPath.size);

            if (target == NULL)
            {
                continue;
            }

            import->target = target;
        }
    }
}




bool ModuleSystemResolveAllImports(struct ModuleSystem *self)
{

    for(u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for(struct HashNode *node = self->registry->modules.buckets[i]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
        {
            struct Module *module = (struct Module *)node->value;
            ModuleSystemResolveImports(self,module);
        }
    }
}


