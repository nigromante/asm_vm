#define INT_C
#include <start.h>

void
syscall_manager (int n)
{
  gotoxy (5 + vout++, vio_offset);
  printf ("CX : %d  ", CX_Get ());
}
