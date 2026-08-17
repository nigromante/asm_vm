#ifndef VIO_H
#define VIO_H

#define COLOR_YELLOW "\033[1;33m"
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
