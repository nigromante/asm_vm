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
  sleep_ms (100);
}

void
trace_callback_full ()
{
  code->dump ();
  regs_dump ();
  ram->dump ();
  mem_dump ();
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

  gotoxy (50, 1);
  printf ("\n total de ciclos : %d \n", ram->header->ciclos);
  return ret;
}

// -------------------------------------------------------- Usage Instructions
void
usage ()
{
  printf ("usage ... ");
}

// ---------------------------------------------------------------------- Main
int
main (int argc, char **argv)
{
  char *filename = NULL;
  int R_flag = 0, D_flag = 0, V_flag = 0, mode = 1;
  int b_flag = 0, a_flag = 0, dump_level = 1;
  int opt;

  while ((opt = getopt (argc, argv, "RDVf:bah")) != -1)
    {
      switch (opt)
        {
        case 'f':
          filename = optarg;
          break;
        case 'R':
          mode = 1;
          R_flag = 1;
          break;
        case 'D':
          mode = 2;
          D_flag = 1;
          break;
        case 'V':
          mode = 3;
          V_flag = 1;
          break;
        case 'b':
          dump_level = 1;
          b_flag = 1;
          break;
        case 'a':
          dump_level = 2;
          a_flag = 1;
          break;
        case 'h':
          usage ();
          exit (0);
          break;
        case '?':
          exit (1);
          break;
        }
    }
  if (filename == NULL)
    {
      printf ("ruta a archivo requerido");
      exit (1);
    }

  if (R_flag + D_flag + V_flag > 1)
    {
      printf ("Puede usar solo una opcion: -R -D -V ");
      exit (1);
    }
  if (b_flag + a_flag > 1)
    {
      printf ("Puede usar solo una opcion: -b -a ");
      exit (1);
    }

  if (!file_exists (filename))
    {
      printf ("archivo [%s] mo existe ", filename);
      exit (1);
    }

  return execute (filename, mode, dump_level);
}

// ----------------------------------------------------------------- Main Ends
