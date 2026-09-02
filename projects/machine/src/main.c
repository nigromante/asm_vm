#include <start.h>
#include <unistd.h>

#include <GL/glut.h>
int thread_ini (char *filename, int mode, int dump_level);

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

  glutInit (&argc, argv);

  clrscr ();

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

  return thread_ini (filename, mode, dump_level);
}

// ----------------------------------------------------------------- Main Ends
