#ifndef ACHIOR_LABS_CMD_LINE_ARGUMENT_LIST_H
#define ACHIOR_LABS_CMD_LINE_ARGUMENT_LIST_H

#include "../../Support/Include/Types.h"
#include "../../Support/Include/Utils.h"
#include "../../Support/Include/BumpAllocator.h"
#include "../../Support/Include/String.h"
#include "../../Support/Include/Log.h"



struct CmdLineArgument;

struct CmdLineArgumentList
{
	u64 size;
	u64 capacity;
	struct CmdLineArgument *data;
	struct BumpAllocator *bump;
};



#include "CmdLine.h"


bool CmdLineArgumentListNew(struct CmdLineArgumentList *self,u64 capacity,struct BumpAllocator *bump);

bool CmdLineArgumentListPushBack(struct CmdLineArgumentList *self,struct CmdLineArgument data);




#endif
