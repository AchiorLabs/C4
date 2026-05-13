#ifndef ACHIOR_LABS_MODULESYSTEM_TOPOLOGICALSORT_H
#define ACHIOR_LABS_MODULESYSTEM_TOPOLOGICALSORT_H

#include "Module.h"





bool ModuleSystemBuildTopologicalOrder(struct ModuleSystem *self);

bool ModuleSystemPrintModules(struct ModuleSystem *self);

bool ModuleSystemVisitModule(struct ModuleSystem *self,struct Module *module);







#endif