#ifndef ACHIOR_LABS_MIDDLE_END_DRIVER_DRIVER_H
#define ACHIOR_LABS_MIDDLE_END_DRIVER_DRIVER_H


#include "../../Include/Include.h"
#include "../../C/Include/ASTToC.h"


void MiddleEndDriverRun(struct C4CMiddleEndOptions *options,struct ASTProgram *program,struct BumpAllocator *bump);



#endif