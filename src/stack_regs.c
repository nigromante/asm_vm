#include <start.h>

void
regs_push (char *registro)
{
  __push (Reg_Get (registro));
}

void
regs_pop (char *registro)
{
  Reg_Set (registro, __pop ());
}
