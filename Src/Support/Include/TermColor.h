#ifndef ACHIOR_LABS_TERMCOLOR_H
#define ACHIOR_LABS_TERMCOLOR_H

#define ANSI_RESET_ALL          "\x1b[0m%s"

#define ANSI_COLOR_BLACK        "\x1b[30m%s"
#define ANSI_COLOR_RED          "\x1b[31m%s"
#define ANSI_COLOR_GREEN        "\x1b[32m%s"
#define ANSI_COLOR_YELLOW       "\x1b[33m%s"
#define ANSI_COLOR_BLUE         "\x1b[34m%s"
#define ANSI_COLOR_MAGENTA      "\x1b[35m%s"
#define ANSI_COLOR_CYAN         "\x1b[36m%s"
#define ANSI_COLOR_WHITE        "\x1b[37m%s"

#define ANSI_COLOR_BOLD_BLACK        "\x1b[1;30m%s"
#define ANSI_COLOR_BOLD_RED          "\x1b[1;31m%s"
#define ANSI_COLOR_BOLD_GREEN        "\x1b[1;32m%s"
#define ANSI_COLOR_BOLD_YELLOW       "\x1b[1;33m%s"
#define ANSI_COLOR_BOLD_BLUE         "\x1b[1;34m%s"
#define ANSI_COLOR_BOLD_MAGENTA      "\x1b[1;35m%s"
#define ANSI_COLOR_BOLD_CYAN         "\x1b[1;36m%s"
#define ANSI_COLOR_BOLD_WHITE        "\x1b[1;37m%s"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m%s"
#define ANSI_BACKGROUND_RED     "\x1b[41m%s"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m%s"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m%s"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m%s"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m%s"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m%s"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m%s"

#define ANSI_BACKGROUND_BOLD_BLACK   "\x1b[1;40m%s"
#define ANSI_BACKGROUND_BOLD_RED     "\x1b[1;41m%s"
#define ANSI_BACKGROUND_BOLD_GREEN   "\x1b[1;42m%s"
#define ANSI_BACKGROUND_BOLD_YELLOW  "\x1b[1;43m%s"
#define ANSI_BACKGROUND_BOLD_BLUE    "\x1b[1;44m%s"
#define ANSI_BACKGROUND_BOLD_MAGENTA "\x1b[1;45m%s"
#define ANSI_BACKGROUND_BOLD_CYAN    "\x1b[1;46m%s"
#define ANSI_BACKGROUND_BOLD_WHITE   "\x1b[1;47m%s"

#define ANSI_COLOR_ITALIC_BLACK        "\x1b[3;30m%s"
#define ANSI_COLOR_ITALIC_RED          "\x1b[3;31m%s"
#define ANSI_COLOR_ITALIC_GREEN        "\x1b[3;32m%s"
#define ANSI_COLOR_ITALIC_YELLOW       "\x1b[3;33m%s"
#define ANSI_COLOR_ITALIC_BLUE         "\x1b[3;34m%s"
#define ANSI_COLOR_ITALIC_MAGENTA      "\x1b[3;35m%s"
#define ANSI_COLOR_ITALIC_CYAN         "\x1b[3;36m%s"
#define ANSI_COLOR_ITALIC_WHITE        "\x1b[3;37m%s"

#define ANSI_COLOR_UNDERLINE_BLACK        "\x1b[4;30m%s"
#define ANSI_COLOR_UNDERLINE_RED          "\x1b[4;31m%s"
#define ANSI_COLOR_UNDERLINE_GREEN        "\x1b[4;32m%s"
#define ANSI_COLOR_UNDERLINE_YELLOW       "\x1b[4;33m%s"
#define ANSI_COLOR_UNDERLINE_BLUE         "\x1b[4;34m%s"
#define ANSI_COLOR_UNDERLINE_MAGENTA      "\x1b[4;35m%s"
#define ANSI_COLOR_UNDERLINE_CYAN         "\x1b[4;36m%s"
#define ANSI_COLOR_UNDERLINE_WHITE        "\x1b[4;37m%s"

#define ANSI_STYLE_BOLD         "\x1b[1m%s"
#define ANSI_STYLE_ITALIC       "\x1b[3m%s"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m%s"


void print_reset();


void print_black(const char *str);
void print_red(const char *str);
void print_green(const char *str);
void print_yellow(const char *str);
void print_blue(const char *str);
void print_magenta(const char *str);
void print_cyan(const char *str);
void print_white(const char *str);


void print_bold_black(const char *str);
void print_bold_red(const char *str);
void print_bold_green(const char *str);
void print_bold_yellow(const char *str);
void print_bold_blue(const char *str);
void print_bold_magenta(const char *str);
void print_bold_cyan(const char *str);
void print_bold_white(const char *str);


void print_italic_black(const char *str);
void print_italic_red(const char *str);
void print_italic_green(const char *str);
void print_italic_yellow(const char *str);
void print_italic_blue(const char *str);
void print_italic_magenta(const char *str);
void print_italic_cyan(const char *str);
void print_italic_white(const char *str);


void print_underline_black(const char *str);
void print_underline_red(const char *str);
void print_underline_green(const char *str);
void print_underline_yellow(const char *str);
void print_underline_blue(const char *str);
void print_underline_magenta(const char *str);
void print_underline_cyan(const char *str);
void print_underline_white(const char *str);


void print_background_black(const char *str);
void print_background_red(const char *str);
void print_background_green(const char *str);
void print_background_yellow(const char *str);
void print_background_blue(const char *str);
void print_background_magenta(const char *str);
void print_background_cyan(const char *str);
void print_background_white(const char *str);


void print_background_bold_black(const char *str);
void print_background_bold_red(const char *str);
void print_background_bold_green(const char *str);
void print_background_bold_yellow(const char *str);
void print_background_bold_blue(const char *str);
void print_background_bold_magenta(const char *str);
void print_background_bold_cyan(const char *str);
void print_background_bold_white(const char *str);


void print_bold(const char *str);
void print_italic(const char *str);
void print_underline(const char *str);


enum TermColor
{
    TERM_COLOR_BLACK,
    TERM_COLOR_RED,
    TERM_COLOR_GREEN,
    TERM_COLOR_YELLOW,
    TERM_COLOR_BLUE,
    TERM_COLOR_MAGENTA,
    TERM_COLOR_CYAN,
    TERM_COLOR_WHITE
};


#endif

