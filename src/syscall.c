#define INT_C
#include <start.h>

typedef struct
{
  int n;
  _REG_ reg;
} _SCALL_BFFR_;

_SCALL_BFFR_ sc_bffr[20];
int sc_bffr_ini = 0;
int sc_bffr_end = 0;

#define _INC_(x)                                                              \
  do                                                                          \
    {                                                                         \
      x = (x + 1) % 20;                                                       \
    }                                                                         \
  while (0)

int
syscall_consume (int *n, _REG_ *_reg)
{
  if (sc_bffr_ini == sc_bffr_end)
    return 0;

  _SCALL_BFFR_ *p = (sc_bffr + sc_bffr_ini);
  *n = p->n;
  memcpy ((_REG_ *)_reg, &(p->reg), sizeof (_REG_));
  _INC_ (sc_bffr_ini);
  return 1;
}

void
syscall_produce (int n, _REG_ *_reg)
{
  printf (" %d %d \n ", n, _reg->CX);
  _SCALL_BFFR_ *p = (sc_bffr + sc_bffr_end);
  p->n = n;
  memcpy (&(p->reg), _reg, sizeof (_REG_));
  _INC_ (sc_bffr_end);
}
