#include <gpu.h>
#include <start.h>

extern int tfinish;

void
gpu_instance ()
{
  gpu_main ();
}

void
gpu_release ()
{
  glutLeaveMainLoop ();
  glutDestroyWindow (glutGetWindow ());
}

void
gpu_proc ()
{
  glutMainLoopEvent ();
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
          gpu_proc ();
          //    sleep_ms (1);
          continue;
        }
    }

  gpu_release ();
}
