#include <start.h>
#include <unistd.h>

void (*pausa) ();

void
run_pause_getchar ()
{
  getchar ();
}

void
run_pause_sleep ()
{
  sleep_ms (10);
}

void
trace_callback_full ()
{
  code->dump ();
  regs_dump ();
  ram->dump ();
  // mem_dump ();
  pausa ();
}

void
trace_callback_simple ()
{
  code->dump ();
  pausa ();
}

// ------------------------------------------------------------------ Executes
//  char * filename
//  int modo :   RUN -  VIEW DEMO  -  DEBUG
//  int dump_level : BASIC - FULL
int
execute (char *filename, int mode, int dump_level)
{
  clrscr ();

  if (mode == 2 || mode == 3)
    {
      vio_offset = 100; // Limite vertical para la salida
                        // reserva 100 columnas para trazas

      if (dump_level == 1)
        {
          code->dump_type (0);
          cpu->set_trace (trace_callback_simple);
        }
      else
        {
          code->dump_type (1);
          cpu->set_trace (trace_callback_full);
        }

      // Define que rutina de pausa usar en rutina trace
      pausa = run_pause_getchar;
      if (mode == 3)
        pausa = run_pause_sleep;
    }

  source->load (filename);
  code->load ();

  cursor_hide ();
  cpu->set_start ();
  int ret = cpu->run ();
  cursor_show ();

  //  gotoxy (50, 1);
  //  printf ("\n total de ciclos : %d \n", ram->header->ciclos);
  return ret;
}
