#ifndef ACHIOR_LABS_OUTPUT_H
#define ACHIOR_LABS_OUTPUT_H

#include "../../Include/Include.h"
#include "../../C4COptions/Include/C4COptions.h"
#include "../../FrontEnd/ModuleSystem/Include/ModuleSystem.h"

struct Output
{
    struct LinkedList modules;
    struct C4COptions options;
    FILE *buildFileHandle;
    struct BumpAllocator *bump;
};


bool OutputNew(struct Output *self,struct LinkedList modules,struct C4COptions options,struct BumpAllocator *bump);

bool OutputModules(struct Output *self);

bool GenerateMakefile(struct Output *self, struct LinkedList modules);


bool GenerateMakefileBaremetal(struct Output *self, struct LinkedList modules);

#endif