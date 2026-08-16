#define INT_C
#include <int.h>
#include <regs.h>
#include <stdio.h>
#include <vio.h>

void
prgm_stmnt_int (int n)
{
  gotoxy (5 + vout++, 100);
  printf ("--- ::  Interrupt %d  | CX : %d --- \n", n, CX_Get ());
}
