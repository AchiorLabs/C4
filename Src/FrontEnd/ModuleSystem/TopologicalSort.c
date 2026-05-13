#include "Include/TopologicalSort.h"






bool ModuleSystemVisitModule(struct ModuleSystem *self,struct Module *module)
{
    if (module == NULL)
    {
        return false;
    }

    if (module->visitState == MODULE_VISIT_VISITING)
    {
        ACHIOR_LABS_PRINTF("Dependency cycle detected at: ");
        StringPrintln(&module->fullPath);
        return false;
    }

    if (module->visitState == MODULE_VISIT_VISITED)
    {
        return true;
    }

    module->visitState = MODULE_VISIT_VISITING;

    for (u64 i = 0; i < module->imports.capacity; i++)
    {
        for (struct HashNode *node = module->imports.buckets[i]; node != NULL; node = node->next)
        {
            struct ModuleImport *import = node->value;

            if(import == NULL || import->target == NULL)
            {
                continue;
            }

            if(!ModuleSystemVisitModule(self,import->target))
            {
                return false;
            }
        }
    }

    module->visitState = MODULE_VISIT_VISITED;

    // post order push to give a topological order

    LinkedListPushBack(&self->order,module);

    return true;
}




bool ModuleSystemBuildTopologicalOrder(struct ModuleSystem *self)
{
    for (u64 i = 0; i < self->registry->modules.capacity; i++)
    {
        for (struct HashNode *node = self->registry->modules.buckets[i]; node != NULL; node = node->next)
        {
            struct Module *module = node->value;

            if (module == NULL)
            {
                continue;
            }

            if (module->visitState == MODULE_VISIT_UNVISITED)
            {
                if (!ModuleSystemVisitModule(self,module))
                {
                    return false;
                }
            }
        }
    }

    return true;
}




bool ModuleSystemPrintModules(struct ModuleSystem *self)
{
    for(u64 i = 0; i < self->order.len; i++)
    {
        struct Module *module = LinkedListAt(&self->order,i);

        ACHIOR_LABS_PRINTF("%s => ",module->fullPath.data);
    }

    ACHIOR_LABS_PRINT("END");
}


