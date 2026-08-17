#include <start.h>
#include <time.h>

void (*pausa) ();

void
run_pause_getchar ()
{
  getchar ();
}

void
sleep_ms (long milliseconds)
{
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000; // Extract full seconds
  ts.tv_nsec
      = (milliseconds % 1000) * 1000000L; // Convert remainder to nanoseconds
  nanosleep (&ts, NULL);
}

void
run_pause_sleep ()
{
  sleep_ms (100);
}

void
trace_callback_full ()
{
  code->dump ();
  regs_dump ();
  stack_dump ();
  pausa ();
}

void
trace_callback_simple ()
{
  code->dump ();
  //  regs_dump ();
  //  stack_dump ();
  pausa ();
}
// ------------------------------------------------------------- Main function
int
main (int argc, char **argv)
{
  if (argc == 1)
    {
      perror ("file not defined");
      return 1;
    }

  char *filename = argv[1];

  source->load (filename);

  code->load ();

  // Set callback if is required
  if (argc == 3
      && (strcmp (argv[2], "DEBUG") == 0 || strcmp (argv[2], "DEMO") == 0))
    {
      vio_offset = 100; // Limite vertical para la salida
                        // reserva 100 columnas para trazas

      cpu->set_trace (trace_callback_full);

      // Define que rutina de pausa usar en rutina trace
      pausa = run_pause_getchar;
      if (strcmp (argv[2], "DEMO") == 0)
        pausa = run_pause_sleep;
    }

  cursor_hide ();

  // Proceso principal
  cpu->run ();

  cursor_show ();

  gotoxy (50, 1);
  return 0;
}
