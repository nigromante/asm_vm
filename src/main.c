#include <start.h>
#include <unistd.h>

void
run_pause_getchar ()
{
  getchar ();
}

void
run_pause_sleep ()
{
  sleep (1);
}

void (*pausa) ();

void
run_callback ()
{
  code->dump ();
  regs_dump ();
  stack_dump ();
  pausa ();
}

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

      cpu->set_callback (run_callback);

      pausa = run_pause_getchar;
      if (strcmp (argv[2], "DEMO") == 0)
        pausa = run_pause_sleep;
    }

  cpu->run ();

  gotoxy (50, 1);
  printf ("\n");
  return 0;
}
