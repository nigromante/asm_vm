#ifndef VIO_H
#define VIO_H

#define COLOR_YELLOW_HIGH "\033[1;33m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BLUE "\033[34m"
#define COLOR_ORANGE "\033[38;5;208m"
#define COLOR_PURPLE "\033[0;35m"

#define COLOR_RESET "\033[0m"
#ifdef VIO_C
int vio_offset = 0;
#else
extern int vio_offset;
#endif

void gotoxy (int row, int column);
void cursor_hide ();
void cursor_show ();

#endif
