
#define STACK_C
#include <start.h>

void
_push (int value)
{
  PTR p = ram->stack_alloc (4);
  memcpy (p, (char *)&value, 4);
}

int
_pop ()
{
  int value = 0;
  PTR p = ram->stack_read (0);
  memcpy (&value, (char *)p, 4);
  ram->stack_free (4);
  memset (p, 0x00, 4);
  return value;
}

int
_read (int offset)
{
  int value = 0;
  PTR p = ram->stack_read (offset);
  memcpy (&value, (char *)p, 4);
  return value;
}

void
_alloc (int size)
{
  PTR p = ram->stack_alloc (size);
  memset (p, 0x00, size);
}
