#include <start.h>

void
regs_push (char *registro)
{
  _push (Reg_Get (registro));
}

void
regs_pop (char *registro)
{
  Reg_Set (registro, _pop ());
}
