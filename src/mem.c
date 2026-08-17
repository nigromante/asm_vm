#define MEM_C
#include <start.h>

void
mem_declare (char *variable, int type, int size)
{
  MEM_OBJ *p = (MEM_OBJ *)((char *)mem_list + mem_idx * sizeof (MEM_OBJ));
  strcpy (p->name, variable);
  sprintf (p->value, "%d", 99);
  p->type = type;
  mem_idx++;
}

MEM_OBJ *
GetPtr (char *variable)
{
  for (int i = 0; i < mem_idx; i++)
    {
      MEM_OBJ *p = (MEM_OBJ *)((char *)mem_list + i * sizeof (MEM_OBJ));
      if (strcmp (p->name, variable) == 0)
        {
          return p;
        }
    }
  return 0;
}

void
mem_load (char *registro, char *variable)
{
  MEM_OBJ *addr = GetPtr (variable);
  regs_mov (registro, addr->value);
}

void
mem_store (char *registro, char *variable)
{
  MEM_OBJ *addr = GetPtr (variable);
  int value = Reg_Get (registro);
  sprintf (addr->value, "%d", value);
}

void
mem_init ()
{
  mem_list = (MEM_OBJ *)malloc (100 * sizeof (MEM_OBJ));
}

void
mem_release ()
{
  free (mem_list);
  mem_list = NULL;
}

void
mem_debug ()
{
  for (int i = 0; i < mem_idx; i++)
    {
      MEM_OBJ *p = (MEM_OBJ *)((char *)mem_list + i * sizeof (MEM_OBJ));
      gotoxy (2, 1 + i * 10);
      printf ("[%s] [%s] ", p->name, p->value);
    }
}
