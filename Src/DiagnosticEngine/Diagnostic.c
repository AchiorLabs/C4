#include "Include/Diagnostic.h"



bool DiagnosticLabelNew(struct DiagnosticLabel *self,struct Span span,const char *message,bool isPrimary,u64 column)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->span      = span;
    self->message   = message;
    self->isPrimary = isPrimary;
    self->column    = column;

    return true;
}


struct DiagnosticLabel *C4MakeDiagnosticLabel(struct BumpAllocator *bump,struct Span span,const char *message,bool isPrimary,u64 column)
{
    struct DiagnosticLabel *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct DiagnosticLabel,1);
    DiagnosticLabelNew(node,span,message,isPrimary,column);

    return node;
}

void DiagnosticAddLabel(struct Diagnostic *self,struct Span span,const char *message,bool isPrimary,struct BumpAllocator *bump)
{
    struct DiagnosticLabel *label = C4MakeDiagnosticLabel(bump,span,message,isPrimary,0);

    LinkedListPushBack(&self->labels,label);
}





bool DiagnosticFixNew(struct DiagnosticFix *self,struct Span span,const char *replacement)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->span        = span;
    self->replacement = replacement;

    return true;
}


struct DiagnosticFix *C4MakeDiagnosticFix(struct BumpAllocator *bump,struct Span span,const char *replacement)
{
    struct DiagnosticFix *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct DiagnosticFix,1);
    DiagnosticFixNew(node,span,replacement);

    return node;
}


void DiagnosticAddFix(struct Diagnostic *self,struct Span span,const char *replacement,struct BumpAllocator *bump)
{
    struct DiagnosticFix *fix = C4MakeDiagnosticFix(bump,span,replacement);
    LinkedListPushBack(&self->fixes,fix);
}


void DiagnosticAddNote(struct Diagnostic *self, const char *note,struct BumpAllocator *bump)
{
    self->note = ACHIOR_LABS_ARENA_ALLOC(bump,char,ACHIOR_LABS_STRLEN(note) + 1);
    ACHIOR_LABS_STRNCPY(self->note,note,ACHIOR_LABS_STRLEN(note));
    self->note[ACHIOR_LABS_STRLEN(note)] = '\0';
}


void DiagnosticAddHelp(struct Diagnostic *self, const char *help,struct BumpAllocator *bump)
{
    self->help = ACHIOR_LABS_ARENA_ALLOC(bump,char,ACHIOR_LABS_STRLEN(help) + 1);
    ACHIOR_LABS_STRNCPY(self->help,help,ACHIOR_LABS_STRLEN(help));
    self->help[ACHIOR_LABS_STRLEN(help)] = '\0';
}





bool  DiagnosticNew(struct  Diagnostic *self,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }

    self->severity     = severity;
    self->message      = message;
    self->fileName     = fileName;
    self->source       = source;
    self->sourceLength = sourceLength;
    self->note         = NULL;
    self->help         = NULL;
    self->code         = code;

    

    return true;
}


struct Diagnostic *C4MakeDiagnostic(struct BumpAllocator *bump,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code)
{
    struct Diagnostic *node = ACHIOR_LABS_ARENA_ALLOC(bump,struct Diagnostic,1);
    DiagnosticNew(node,severity,message,fileName,source,sourceLength,code);

    LinkedListNew(&node->labels,bump);
    LinkedListNew(&node->fixes,bump);

    return node;
}

