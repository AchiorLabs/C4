#ifndef ACHIOR_LABS_DIAGNOSTICENGINE_DIAGNOSTICENGINE_H
#define ACHIOR_LABS_DIAGNOSTICENGINE_DIAGNOSTICENGINE_H

#include "Diagnostic.h"
#include "DiagnosticRenderer.h"



struct DiagnosticEngine
{
    struct LinkedList diagnostics;
    struct BumpAllocator *bump;

    bool hasErrors;
    u64 errorCount;
    u64 maxErrors;
};

bool DiagnosticEngineNew(struct DiagnosticEngine *self,u64 maxErrors,struct BumpAllocator *bump);



struct Diagnostic *DiagnosticEngineReport(struct DiagnosticEngine *self,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code);


void DiagnosticEngineEmit(struct DiagnosticEngine *self);


#endif