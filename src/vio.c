#define VIO_C
#include <start.h>

void
gotoxy (int row, int column)
{
  // \033 is the ESC character, H sets the cursor position
  printf ("\033[%d;%df", row, column);
}
