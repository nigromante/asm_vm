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

void
cpu_set_start ()
{
  char *global = code->get_global ();
  IP_Set (code->get_row_by_label (global));
}

// ------------------------------------------------------- CPU Run - Main loop
int
cpu_run ()
{
  while (1)
    {
      int line = IP_Get ();
      if (line <= 0)
        break;

      _CODE_LINE_ *stmnt = code->get_line (line);
      if (stmnt == NULL)
        break;

      if (cpu_stmnt_eval (stmnt) != 0)
        {
          break;
        }

      ram->header->ciclos++;
      Reg_Backup ();
      exec_callback ();
    }
  return 0;
}

int
cpu_ciclos_total ()
{
  return ram->header->ciclos;
}

// ------------------------------------------------------------------ Instance
void
cpu_init ()
{
  cpu = (_CPU_ *)malloc (sizeof (_CPU_));
  memset (cpu, 0x00, sizeof (_CPU_));

  cpu->run = cpu_run;
  cpu->set_trace = cpu_set_trace_callback;
  cpu->set_start = cpu_set_start;
  cpu->ciclos_total = cpu_ciclos_total;
}

void
cpu_release ()
{
  free (cpu);
  cpu = NULL;
}

// ------------------------------------------------------------------ Cpu Ends
