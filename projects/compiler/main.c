#include <start.h>
#include <unistd.h>

int tfinish = 0;

// ------------------------------------------------------------------ Executes
int
execute (char *filename, char *fileoutput)
{
  source->load (filename);
  preproc->load ();
  code->load ();

  code->save (fileoutput);
  return 0;
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
  char *fileoutput = NULL;
  int opt;

  while ((opt = getopt (argc, argv, "RDVf:o:bah")) != -1)
    {
      switch (opt)
        {
        case 'f':
          filename = optarg;
          break;
        case 'o':
          fileoutput = optarg;
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

  if (fileoutput == NULL)
    {
      printf ("ruta a archivo de salida requerido");
      exit (1);
    }

  if (!file_exists (filename))
    {
      printf ("archivo [%s] no existe ", filename);
      exit (1);
    }

  return execute (filename, fileoutput);
}

// ----------------------------------------------------------------- Main Ends
