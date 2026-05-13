#include "Include/DiagnosticRenderer.h"


static const char *get_line_start(const char *src, u64 len, u64 target)
{
    u64 line = 1;
    u64 i = 0;

    while (i < len && line < target)
    {
        if (src[i] == '\n') line++;
        i++;
    }

    return &src[i];
}

static bool spans_overlap(struct Span a, struct Span b)
{
    return !(a.endColumn < b.startColumn || b.endColumn < a.startColumn);
}

/* ===== COLUMN LAYOUT ===== */

static void assign_columns(struct Diagnostic *d)
{
    u64 count = LinkedListLength(&d->labels);

    for (u64 i = 0; i < count; i++)
    {
        struct DiagnosticLabel *a =
            LinkedListAt(&d->labels, i);

        a->column = 0;

        for (u64 j = 0; j < i; j++)
        {
            struct DiagnosticLabel *b =
                LinkedListAt(&d->labels, j);

            if (spans_overlap(a->span, b->span))
            {
                if (b->column >= a->column)
                    a->column = b->column + 1;
            }
        }
    }
}




void DiagnosticRenderLabels(struct Diagnostic *d)
{
    assign_columns(d);

    u64 count = LinkedListLength(&d->labels);

    for (u64 i = 0; i < count; i++)
    {
        struct DiagnosticLabel *lbl =
            LinkedListAt(&d->labels, i);

        const char *line =
            get_line_start(d->source, d->sourceLength, lbl->span.startLine);

        u64 len = 0;
        while (line[len] && line[len] != '\n') len++;

        log_write(LOG_LEVEL_NONE,
            "%lu | %.*s",
            lbl->span.startLine,
            (int)len,
            line
        );

        printf("  | ");

        for (u64 j = 0; j < lbl->span.startColumn; j++)
            fputc(' ', stdout);

        for (u64 c = 0; c < lbl->column; c++)
            printf("| ");

        log_put_color(LOG_COLOR_BOLD_RED);

        u64 width = lbl->span.endColumn - lbl->span.startColumn;
        if (width == 0) width = 1;

        for (u64 j = 0; j < width; j++)
            fputc('^', stdout);

        log_reset_color();

        printf("\n");

        if (lbl->message)
        {
            printf("  | ");

            for (u64 j = 1; j < lbl->span.startColumn; j++)
                fputc(' ', stdout);

            for (u64 c = 0; c < lbl->column; c++)
                printf("| ");

            printf("%s\n", lbl->message);
        }

        puts("");
    }
}









void DiagnosticRenderFixes(struct Diagnostic *d)
{
    u64 count = LinkedListLength(&d->fixes);

    for (u64 i = 0; i < count; i++)
    {
        struct DiagnosticFix *fix =
            LinkedListAt(&d->fixes, i);

        log_write(LOG_LEVEL_NONE,
            "%C{bold_green}help%C{reset}:  replace with");

        printf("  |\n");

        const char *line =
            get_line_start(d->source, d->sourceLength, fix->span.startLine);

        printf("%lu | ", fix->span.startLine);

        fwrite(line, 1, fix->span.startColumn - 1, stdout);

        log_put_color(LOG_COLOR_BOLD_GREEN);
        printf("%s", fix->replacement);
        log_reset_color();

        const char *after = line + fix->span.endColumn;

        while (*after && *after != '\n')
        {
            fputc(*after, stdout);
            after++;
        }

        printf("\n\n");
    }
}






