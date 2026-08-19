#define INT_C
#include <start.h>

void
syscall_manager (int n)
{
  gotoxy (5 + vout++, vio_offset);
  printf ("--- ::  Interrupt %d  | CX : %d --- \n", n, CX_Get ());
}
