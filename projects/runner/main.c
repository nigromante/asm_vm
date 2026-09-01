#include <start.h>
#include <unistd.h>

int tfinish = 0;

int
execute (char *filename)
{

  code_read (filename);

  cursor_hide ();
  int ret = cpu->run ();
  cursor_show ();

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
  int opt;

  while ((opt = getopt (argc, argv, "f:h")) != -1)
    {
      switch (opt)
        {
        case 'f':
          filename = optarg;
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

  if (!file_exists (filename))
    {
      printf ("archivo [%s] mo existe ", filename);
      exit (1);
    }

  return execute (filename);
}

// ----------------------------------------------------------------- Main Ends
