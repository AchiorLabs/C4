#ifndef ACHIOR_LABS_LOG_H
#define ACHIOR_LABS_LOG_H

#include "Types.h"
#include "Utils.h"

enum log_color
{
    LOG_COLOR_DEFAULT = 0,

    LOG_COLOR_BLACK,
    LOG_COLOR_RED,
    LOG_COLOR_GREEN,
    LOG_COLOR_YELLOW,
    LOG_COLOR_BLUE,
    LOG_COLOR_MAGENTA,
    LOG_COLOR_CYAN,
    LOG_COLOR_WHITE,

    LOG_COLOR_BOLD_BLACK,
    LOG_COLOR_BOLD_RED,
    LOG_COLOR_BOLD_GREEN,
    LOG_COLOR_BOLD_YELLOW,
    LOG_COLOR_BOLD_BLUE,
    LOG_COLOR_BOLD_MAGENTA,
    LOG_COLOR_BOLD_CYAN,
    LOG_COLOR_BOLD_WHITE
};

enum log_level
{
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

struct log_config
{
    bool use_color;
    bool show_level;
    bool append_newline;
};

void log_set_config(struct log_config config);
struct log_config log_get_config(void);

void log_write(enum log_level level,const char *fmt,...);
void log_vwrite(enum log_level level,const char *fmt,va_list args);

void log_trace(const char *fmt,...);
void log_debug(const char *fmt,...);
void log_info(const char *fmt,...);
void log_warn(const char *fmt,...);
void log_error(const char *fmt,...);
void log_fatal(const char *fmt,...);

void log_put_color(enum log_color color);
void log_reset_color(void);

#endif