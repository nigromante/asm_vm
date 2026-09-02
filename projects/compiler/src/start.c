
#define START_C

#include <start.h>

__attribute__ ((constructor)) void
loader_init ()
{
  source_init ();
  code_init ();
  preproc_init ();
}

__attribute__ ((destructor)) void
loader_end ()
{
  source_release ();
  code_release ();
  preproc_release ();
}
