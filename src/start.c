
#define START_C

#include <start.h>

__attribute__ ((constructor)) void
loader_init ()
{
  mem_init ();
  stack_init ();
  source_init ();
  code_init ();
  cpu_init ();
}

__attribute__ ((destructor)) void
loader_end ()
{
  mem_release ();
  source_release ();
  code_release ();
  cpu_release ();
}
