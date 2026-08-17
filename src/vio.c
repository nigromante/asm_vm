#define VIO_C
#include <start.h>

void
gotoxy (int row, int column)
{
  // \033 is the ESC character, H sets the cursor position
  printf ("\033[%d;%df", row, column);
}

void
cursor_hide ()
{
  printf ("\e[?25l");
}

void
cursor_show ()
{
  printf ("\e[?25h");
}
