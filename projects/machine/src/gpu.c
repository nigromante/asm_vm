#include <start.h>

extern int tfinish;

void
gpu_instance ()
{
}

void
gpu_release ()
{
}

void
gpu_proc ()
{
}

void
gpu_run ()
{
  int n;
  _REG_ _reg;

  gpu_instance ();

  while (!tfinish)
    {
      if (!syscall_consume (&n, &_reg))
        {
          sleep_ms (100);
          continue;
        }

      gpu_proc ();
    }

  gpu_release ();
}
