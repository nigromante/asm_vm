#ifndef VIO_H
#define VIO_H

#define COLOR_BOLD_YELLOW "\033[1;33m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BLUE "\033[34m"
#define COLOR_ORANGE "\033[38;5;208m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_RESET "\033[0m"

#define CURSOR_HIDE "\e[?25l"
#define CURSOR_SHOW "\e[?25h"
#define GOTOXY "\033[%d;%df"
#define CLRSCR "\e[1;1H\e[2J"

#ifdef VIO_C
int vio_offset = 0;
#else
extern int vio_offset;
#endif

void clrscr ();
void gotoxy (int row, int column);
void cursor_hide ();
void cursor_show ();
void print_at (int row, int col, char *fmt, ...);

#endif
