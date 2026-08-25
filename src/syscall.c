#define INT_C
#include <start.h>

void
print_ax ()
{
  gotoxy (5 + vout++, vio_offset);
  printf ("AX : %d  ", AX_Get ());
}

void
print_bx ()
{
  gotoxy (5 + vout++, vio_offset);
  printf ("BX : %d  ", BX_Get ());
}

void
print_cx ()
{
  gotoxy (5 + vout++, vio_offset);
  printf ("CX : %d  ", CX_Get ());
}

void
print_dx ()
{
  gotoxy (5 + vout++, vio_offset);
  printf ("DX : %d  ", DX_Get ());
}

void
syscall_manager (int n)
{
  switch (n)
    {
    case 80:
      print_ax ();
      break;
    case 81:
      print_bx ();
      break;
    case 82:
      print_cx ();
      break;
    case 83:
      print_dx ();
      break;
    }
}
