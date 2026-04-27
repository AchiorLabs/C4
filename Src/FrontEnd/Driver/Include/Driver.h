#ifndef ACHIOR_LABS_FRONTEND_DRIVER_DRIVER_H
#define ACHIOR_LABS_FRONTEND_DRIVER_DRIVER_H


#include "../../../C4COptions/Include/C4COptions.h"
#include "../../Lexer/Include/Lexer.h"
#include "../../Parser/Include/Parser.h"
#include "../../TreeWalker/Include/TreeWalker.h"
#include "../../IdentifierResolution/Include/IdentifierResolution.h"


struct Parser FrontEndDriverRun(struct C4CFrontEndOptions *options,struct BumpAllocator *bump);



#endif