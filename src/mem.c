#define MEM_C
#include <start.h>

// --------------------------------------------------------- Puntero a Memoria
MEM_OBJ *
mem_getptr (char *variable)
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

// ---------------------------------------------------------- Declare Variable
void
mem_declare (char *variable, int type, int size)
{
  MEM_OBJ *p = (MEM_OBJ *)((char *)mem_list + mem_idx * sizeof (MEM_OBJ));
  strcpy (p->name, variable);
  p->value = ram->heap_alloc (size);
  p->type = type;
  mem_idx++;
}

// -------------------------------------------------- Mover Memoria a registro
void
mem_load (char *registro, char *variable)
{
  MEM_OBJ *addr = mem_getptr (variable);
  regs_mov_int (registro, *(int *)addr->value);
}

// -------------------------------------------------- Mover Registro a Memoria
void
mem_store (char *variable, char *registro)
{
  MEM_OBJ *addr = mem_getptr (variable);
  int value = Reg_Get (registro);
  memcpy (addr->value, &value, sizeof (value));
}

void
mem_store_db (char *variable, char *data, int len)
{
  MEM_OBJ *addr = mem_getptr (variable);
  memcpy (addr->value, data, len);
}

void
mem_store_dw (char *variable, char *data)
{
  int value = atoi (data);
  MEM_OBJ *addr = mem_getptr (variable);
  memcpy (addr->value, &value, sizeof (int));
}

// --------------------------------------------------------------------- Debug
void
mem_dump ()
{
  for (int i = 0; i < mem_idx; i++)
    {
      MEM_OBJ *p = (MEM_OBJ *)((char *)mem_list + i * sizeof (MEM_OBJ));
      gotoxy (3, 1 + i * 10);
      printf ("[%s] [%d] ", p->name, *(int *)p->value);
    }
}

// ------------------------------------------------------------------ Instance
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

// ------------------------------------------------------------------ Mem Ends
