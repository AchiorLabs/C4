#ifndef ACHIOR_LABS_MODULESYSTEM_RESOLVE_IMPORTS_H
#define ACHIOR_LABS_MODULESYSTEM_RESOLVE_IMPORTS_H

#include "Module.h"


struct String ModuleSystemPathFromList(struct BumpAllocator *bump,struct LinkedList list);

bool ModuleSystemCollectImports(struct ModuleSystem *self,struct Module *module);

bool ModuleSystemCollectAllImports(struct ModuleSystem *self,struct FileTreeNode *fileTree);



bool ModuleSystemResolveImports(struct ModuleSystem *self,struct Module *module);


bool ModuleSystemResolveAllImports(struct ModuleSystem *self);;


#endif
