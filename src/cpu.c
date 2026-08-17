#define CPU_C

#include <start.h>

// ------------------------------------------------------------------ Callback
void
exec_callback ()
{
  if (cpu->callback_fn)
    cpu->callback_fn ();
}

void
cpu_set_trace_callback (void (*fn) ())
{
  cpu->callback_fn = fn;
}

// ------------------------------------------------------- CPU Run - Main loop
int
cpu_run ()
{
  char *global = code->get_global ();

  IP_Set (code->get_row_by_label (global));

  while (1)
    {
      int line = IP_Get ();
      if (line <= 0)
        break;

      _CODE_LINE_ *stmnt = code->get_line (line);
      if (stmnt == NULL)
        break;

      Reg_Backup ();

      if (cpu_stmnt_eval (stmnt) != 0)
        {
          break;
        }

      exec_callback ();
    }

  return 0;
}

// ------------------------------------------------------------------ Instance
void
cpu_init ()
{
  cpu = (_CPU_ *)malloc (sizeof (_CPU_));
  memset (cpu, 0x00, sizeof (_CPU_));

  cpu->run = cpu_run;
  cpu->set_trace = cpu_set_trace_callback;
}

void
cpu_release ()
{
  free (cpu);
  cpu = NULL;
}

// ------------------------------------------------------------------ Cpu Ends
