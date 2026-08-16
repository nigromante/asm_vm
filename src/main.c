#include <start.h>

void
run_callback ()
{
  code->dump ();
  getchar ();
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
  if (argc == 3 && strcmp (argv[2], "DEBUG") == 0)
    cpu->set_callback (run_callback);

  cpu->run ();

  printf ("\n");
  return 0;
}
