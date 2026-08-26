#define VIO_C
#include <start.h>
#include <stdarg.h>

void
clrscr ()
{
  printf (CLRSCR);
}

void
gotoxy (int row, int column)
{
  printf (GOTOXY, row, column);
}

void
cursor_hide ()
{
  printf (CURSOR_HIDE);
}

void
cursor_show ()
{
  printf (CURSOR_SHOW);
}

void
print_at (int row, int col, char *fmt, ...)
{
  char buffer[100];

  va_list va;
  va_start (va, fmt);
  vsprintf (buffer, fmt, va);
  va_end (va);

  gotoxy (row, col);

  printf ("%s", buffer);
}
