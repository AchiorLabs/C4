#include "Include/DiagnosticEngine.h"


bool DiagnosticEngineNew(struct DiagnosticEngine *self,u64 maxErrors,struct BumpAllocator *bump)
{
    if (!LinkedListNew(&self->diagnostics, bump))
        return false;

    self->bump = bump;
    self->hasErrors = false;
    self->errorCount = 0;
    self->maxErrors = maxErrors;

    return true;
}


struct Diagnostic *DiagnosticEngineReport(struct DiagnosticEngine *self,enum DiagnosticSeverity severity,const char *message,const char *fileName,const char *source,u64 sourceLength,u32 code)
{
    if (self->errorCount >= self->maxErrors)
    {
        return NULL;
    }

    ACHIOR_LABS_PTR_INIT(struct Diagnostic,diagnostic);
    ACHIOR_LABS_PTR_INIT(struct Diagnostic,storedDiagnostic);

    diagnostic = C4MakeDiagnostic(self->bump,severity,message,fileName,source,sourceLength,code);
    LinkedListPushBack(&self->diagnostics,diagnostic);

    storedDiagnostic = LinkedListAt(&self->diagnostics,LinkedListLength(&self->diagnostics) - 1);

    if (ACHIOR_LABS_EQUAL(severity,DIAGNOSTIC_ERROR))
    {
        self->hasErrors = true;
        self->errorCount++;
    }

    return storedDiagnostic;
}





void DiagnosticEngineEmit(struct DiagnosticEngine *self)
{
    u64 count = LinkedListLength(&self->diagnostics);

    for (u64 i = 0; i < count; i++)
    {
        struct Diagnostic *d = LinkedListAt(&self->diagnostics, i);

        log_write(LOG_LEVEL_NONE,
            "%C{bold_red}%s%C{reset}: %s",
            (d->severity == DIAGNOSTIC_ERROR) ? "error" : "warning",
            d->message
        );

        DiagnosticRenderLabels(d);

        if (d->note)
        {
            log_write(LOG_LEVEL_NONE,
                "%C{bold_cyan}note%C{reset}:  %s",
                d->note);
        }

        if (d->help)
        {
            log_write(LOG_LEVEL_NONE,
                "%C{bold_green}help%C{reset}:  %s",
                d->help);
        }

        DiagnosticRenderFixes(d);

        printf("\n");
    }
}

