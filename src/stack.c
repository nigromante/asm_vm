
#define STACK_C
#include <regs.h>
#include <stack.h>
#include <stdio.h>
#include <string.h>
#include <vio.h>

void
__push (int value)
{
  if (stack_idx >= 100)
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
  stack_data[stack_idx] = -1;
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
  for (int i = 0; i < 20; i++)
    {
      gotoxy (4 + i, 60);
      printf ("%2d   %c  %d", i, stack_idx == i ? '>' : ' ', stack_data[i]);
    }
}
