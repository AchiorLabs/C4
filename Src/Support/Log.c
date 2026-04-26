#include "Include/Log.h"


static struct log_config g_log_config =
{
    true,  /* use_color */
    true,  /* show_level */
    true   /* append_newline */
};

static const char *log_level_to_string(enum log_level level)
{
    switch(level)
    {
        case LOG_LEVEL_TRACE: return "TRACE";
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_FATAL: return "FATAL";
        default:              return "UNKNOWN";
    }
}

static enum log_color log_level_to_color(enum log_level level)
{
    switch(level)
    {
        case LOG_LEVEL_TRACE: return LOG_COLOR_BOLD_WHITE;
        case LOG_LEVEL_DEBUG: return LOG_COLOR_BOLD_CYAN;
        case LOG_LEVEL_INFO:  return LOG_COLOR_BOLD_GREEN;
        case LOG_LEVEL_WARN:  return LOG_COLOR_BOLD_YELLOW;
        case LOG_LEVEL_ERROR: return LOG_COLOR_BOLD_RED;
        case LOG_LEVEL_FATAL: return LOG_COLOR_BOLD_MAGENTA;
        default:              return LOG_COLOR_DEFAULT;
    }
}

static const char *log_color_to_ansi(enum log_color color)
{
    switch(color)
    {
        case LOG_COLOR_BLACK:         return "\x1b[30m";
        case LOG_COLOR_RED:           return "\x1b[31m";
        case LOG_COLOR_GREEN:         return "\x1b[32m";
        case LOG_COLOR_YELLOW:        return "\x1b[33m";
        case LOG_COLOR_BLUE:          return "\x1b[34m";
        case LOG_COLOR_MAGENTA:       return "\x1b[35m";
        case LOG_COLOR_CYAN:          return "\x1b[36m";
        case LOG_COLOR_WHITE:         return "\x1b[37m";

        case LOG_COLOR_BOLD_BLACK:    return "\x1b[1;30m";
        case LOG_COLOR_BOLD_RED:      return "\x1b[1;31m";
        case LOG_COLOR_BOLD_GREEN:    return "\x1b[1;32m";
        case LOG_COLOR_BOLD_YELLOW:   return "\x1b[1;33m";
        case LOG_COLOR_BOLD_BLUE:     return "\x1b[1;34m";
        case LOG_COLOR_BOLD_MAGENTA:  return "\x1b[1;35m";
        case LOG_COLOR_BOLD_CYAN:     return "\x1b[1;36m";
        case LOG_COLOR_BOLD_WHITE:    return "\x1b[1;37m";

        case LOG_COLOR_DEFAULT:
        default:
            return "\x1b[0m";
    }
}

static bool log_str_eq_n(const char *lhs,size_t lhs_len,const char *rhs)
{
    size_t rhs_len = strlen(rhs);
    if(lhs_len != rhs_len)
    {
        return false;
    }

    return strncmp(lhs,rhs,lhs_len) == 0;
}

static enum log_color log_parse_named_color(const char *name,size_t len)
{
    if(log_str_eq_n(name,len,"reset"))         return LOG_COLOR_DEFAULT;
    if(log_str_eq_n(name,len,"default"))       return LOG_COLOR_DEFAULT;

    if(log_str_eq_n(name,len,"black"))         return LOG_COLOR_BLACK;
    if(log_str_eq_n(name,len,"red"))           return LOG_COLOR_RED;
    if(log_str_eq_n(name,len,"green"))         return LOG_COLOR_GREEN;
    if(log_str_eq_n(name,len,"yellow"))        return LOG_COLOR_YELLOW;
    if(log_str_eq_n(name,len,"blue"))          return LOG_COLOR_BLUE;
    if(log_str_eq_n(name,len,"magenta"))       return LOG_COLOR_MAGENTA;
    if(log_str_eq_n(name,len,"cyan"))          return LOG_COLOR_CYAN;
    if(log_str_eq_n(name,len,"white"))         return LOG_COLOR_WHITE;

    if(log_str_eq_n(name,len,"bold_black"))    return LOG_COLOR_BOLD_BLACK;
    if(log_str_eq_n(name,len,"bold_red"))      return LOG_COLOR_BOLD_RED;
    if(log_str_eq_n(name,len,"bold_green"))    return LOG_COLOR_BOLD_GREEN;
    if(log_str_eq_n(name,len,"bold_yellow"))   return LOG_COLOR_BOLD_YELLOW;
    if(log_str_eq_n(name,len,"bold_blue"))     return LOG_COLOR_BOLD_BLUE;
    if(log_str_eq_n(name,len,"bold_magenta"))  return LOG_COLOR_BOLD_MAGENTA;
    if(log_str_eq_n(name,len,"bold_cyan"))     return LOG_COLOR_BOLD_CYAN;
    if(log_str_eq_n(name,len,"bold_white"))    return LOG_COLOR_BOLD_WHITE;

    return LOG_COLOR_DEFAULT;
}

void log_set_config(struct log_config config)
{
    g_log_config = config;
}

struct log_config log_get_config(void)
{
    return g_log_config;
}

void log_put_color(enum log_color color)
{
    if(!g_log_config.use_color)
    {
        return;
    }

    fputs(log_color_to_ansi(color),stdout);
}

void log_reset_color(void)
{
    log_put_color(LOG_COLOR_DEFAULT);
}

static void log_emit_level_prefix(enum log_level level)
{
    if(!g_log_config.show_level)
    {
        return;
    }

    fputc('[',stdout);

    if(g_log_config.use_color)
    {
        log_put_color(log_level_to_color(level));
    }

    fputs(log_level_to_string(level),stdout);

    if(g_log_config.use_color)
    {
        log_reset_color();
    }

    fputs("] ",stdout);
}

static void log_emit_string(const char *s)
{
    if(s == NULL)
    {
        fputs("(null)",stdout);
        return;
    }

    fputs(s,stdout);
}

static void log_emit_unknown_specifier(char ch)
{
    fputc('%',stdout);
    if(ch != '\0')
    {
        fputc(ch,stdout);
    }
}

void log_vwrite(enum log_level level,const char *fmt,va_list args)
{
    const char *p = fmt;

    if(fmt == NULL)
    {
        return;
    }

    log_emit_level_prefix(level);

    while(*p != '\0')
    {
        if(*p != '%')
        {
            fputc(*p,stdout);
            p++;
            continue;
        }

        p++;

        if(*p == '\0')
        {
            fputc('%',stdout);
            break;
        }

        if(*p == '%')
        {
            fputc('%',stdout);
            p++;
            continue;
        }

        if(*p == 's')
        {
            const char *value = va_arg(args,const char *);
            log_emit_string(value);
            p++;
            continue;
        }

        if(*p == 'd')
        {
            int value = va_arg(args,int);
            fprintf(stdout,"%d",value);
            p++;
            continue;
        }

        if(*p == 'u')
        {
            unsigned int value = va_arg(args,unsigned int);
            fprintf(stdout,"%u",value);
            p++;
            continue;
        }

        if(*p == 'l')
        {
            if(*(p + 1) == 'd')
            {
                long value = va_arg(args,long);
                fprintf(stdout,"%ld",value);
                p += 2;
                continue;
            }

            if(*(p + 1) == 'u')
            {
                unsigned long value = va_arg(args,unsigned long);
                fprintf(stdout,"%lu",value);
                p += 2;
                continue;
            }

            log_emit_unknown_specifier(*p);
            p++;
            continue;
        }

        /*
            %c  -> expects enum log_color
        */
        if(*p == 'c')
        {
            int color = va_arg(args,int);
            log_put_color((enum log_color)color);
            p++;
            continue;
        }

        /*
            %C{red}
            %C{bold_yellow}
            %C{reset}
        */
        if(*p == 'C' && *(p + 1) == '{')
        {
            const char *name_start;
            const char *name_end;

            p += 2;
            name_start = p;

            while(*p != '\0' && *p != '}')
            {
                p++;
            }

            if(*p == '}')
            {
                name_end = p;
                log_put_color(log_parse_named_color(name_start,(size_t)(name_end - name_start)));
                p++;
                continue;
            }

            fputs("%C{",stdout);
            fwrite(name_start,1,(size_t)(p - name_start),stdout);
            break;
        }

        log_emit_unknown_specifier(*p);
        p++;
    }

    if(g_log_config.use_color)
    {
        log_reset_color();
    }

    if(g_log_config.append_newline)
    {
        fputc('\n',stdout);
    }

    fflush(stdout);
}

void log_write(enum log_level level,const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(level,fmt,args);
    va_end(args);
}

void log_trace(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_TRACE,fmt,args);
    va_end(args);
}

void log_debug(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_DEBUG,fmt,args);
    va_end(args);
}

void log_info(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_INFO,fmt,args);
    va_end(args);
}

void log_warn(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_WARN,fmt,args);
    va_end(args);
}

void log_error(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_ERROR,fmt,args);
    va_end(args);
}

void log_fatal(const char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    log_vwrite(LOG_LEVEL_FATAL,fmt,args);
    va_end(args);
}
