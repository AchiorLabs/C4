#include "Include/Driver.h"




struct LinkedList FrontEndDriverRun(struct C4CFrontEndOptions *options,struct DiagnosticEngine *engine,struct BumpAllocator *bump)
{
	struct ModuleSystem moduleSystem;
	ModuleSystemNew(&moduleSystem,engine,bump,options);

	return moduleSystem.order;

}
