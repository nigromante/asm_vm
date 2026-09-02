#include <start.h>
#include <unistd.h>

int tfinish = 0;

void
eval_define_callback (char *line)
{
  callDefine (line);
}

int
execute (char *filename)
{
  cursor_hide ();

  int start_IP = code_read (filename, eval_define_callback);
  IP_Set (start_IP);
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
