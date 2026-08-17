
#define STACK_C
#include <start.h>

void
__push (int value)
{
  if (stack_idx >= STACK_MAX)
    return;

  stack_data[stack_idx++] = value;
  SP_Set (stack_idx);
}

int
__pop ()
{
  if (stack_idx < 0)
    return -1;

  int value = stack_data[--stack_idx];
  stack_data[stack_idx] = 0;
  SP_Set (stack_idx);
  return value;
}

void
stack_init ()
{
  stack_idx = 0;
  memset ((char *)&stack_data, 0x00, sizeof (stack_data));
}

void
stack_dump ()
{
  for (int i = 0; i < STACK_MAX; i++)
    {
      gotoxy (5 + i, 82);
      if (i > stack_idx)
        {
          printf ("          ");
          break;
        }
      printf ("%c %2d  %4d", stack_idx == i ? '>' : ' ', i, stack_data[i]);
    }
}
