#ifndef ACHIOR_LABS_DIAGNOSTICENGINE_DIAGNOSTIC_H
#define ACHIOR_LABS_DIAGNOSTICENGINE_DIAGNOSTIC_H

#include "../../Support/Include/Types.h"
#include "../../Support/Include/Utils.h"
#include "../../Support/Include/BumpAllocator.h"
#include "../../Support/Include/String.h"
#include "../../Support/Include/List.h"
#include "../../Support/Include/Log.h"
#include "../../FrontEnd/Lexer/Include/Token.h"



enum DiagnosticSeverity
{
    DIAGNOSTIC_ERROR,DIAGNOSTIC_WARNING,DIAGNOSTIC_NOTE,DIAGNOSTIC_HELP
};


struct DiagnosticLabel
{
    struct Span span;
    const char *message;
    bool isPrimary;
    u64 column;
};

bool DiagnosticLabelNew(struct DiagnosticLabel *self,struct Span span,const char *message,bool isPrimary,u64 column);



struct DiagnosticFix
{
    struct Span span;
    const char *replacement;
};

bool DiagnosticFixNew(struct DiagnosticFix *self,struct Span span,const char *replacement);



struct Diagnostic
{
    enum DiagnosticSeverity severity;
    const char *message;

    const char *fileName;
    const char *source;
    u64 sourceLength;

    struct LinkedList labels;
    struct LinkedList fixes;

    char *note;
    char *help;

    u32 code;
};


bool  DiagnosticNew(struct  Diagnostic *self,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code);


struct Diagnostic *C4MakeDiagnostic(struct BumpAllocator *bump,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code);



void DiagnosticAddLabel(struct Diagnostic *self,struct Span span,const char *message,bool primary,struct BumpAllocator *bump);
void DiagnosticAddFix(struct Diagnostic *self,struct Span span,const char *replacement,struct BumpAllocator *bump);

void DiagnosticAddNote(struct Diagnostic *self,const char *note,struct BumpAllocator *bump);
void DiagnosticAddHelp(struct Diagnostic *self,const char *help,struct BumpAllocator *bump);



#endif