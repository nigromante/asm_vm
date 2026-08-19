
#define STACK_C
#include <start.h>

void
__push (int value)
{
  int idx = SP_Get ();
  if (idx >= STACK_MAX)
    return;

  stack_data[idx++] = value;
  SP_Set (idx);
}

int
__pop ()
{
  int idx = SP_Get ();
  if (idx < 0)
    return -1;

  int value = stack_data[--idx];
  stack_data[idx] = 0;
  SP_Set (idx);
  return value;
}

void
stack_init ()
{
  SP_Set (0);
  memset ((char *)&stack_data, 0x00, sizeof (stack_data));
}

void
stack_dump ()
{
  int idx = SP_Get ();
  for (int i = 0; i < STACK_MAX; i++)
    {
      gotoxy (5 + i, 82);
      if (i > idx)
        {
          printf ("          ");
          break;
        }
      printf ("%c %2d  %4d", idx == i ? '>' : ' ', i, stack_data[i]);
    }
}
