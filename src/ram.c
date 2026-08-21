#define RAM_C

#include <start.h>
#define _BP ram->header->stack_ini
#define _SP ram->header->stack_end

// ----------------------------------------------------------------- Funciones

int
ram_mem_avail ()
{
  return (_SP - ram->header->heap_end);
}

// --------------------------------------------------------------------- Stack

void
ram_stack_upd_regs ()
{
  reg.BP = _BP;
  reg.SP = _SP;
}

PTR
ram_stack_alloc (int n)
{
  if (n > ram_mem_avail ())
    {
      perror ("memory not available");
      return NULL;
    }
  _SP = _SP - n;
  ram_stack_upd_regs ();

  return ram->ptr + _SP;
}

PTR
ram_stack_read (int n)
{
  return ram->ptr + _SP + n;
}

void
ram_stack_free (int n)
{
  _SP = _SP + n;
  ram_stack_upd_regs ();
}

void
ram_stack_bp2sp ()
{
  _SP = _BP;
  ram_stack_upd_regs ();
}

void
ram_stack_sp2bp ()
{
  _BP = _SP;
  ram_stack_upd_regs ();
}

// ---------------------------------------------------------------------- Heap

// --------------------------------------------------------------------- Dumps
void
ram_dump ()
{
  int l = 1;
  PTR p = ram->ptr;

  gotoxy (5, 70);
  printf ("SP : %4d ", _SP);

  gotoxy (6, 70);
  printf ("BP : %4d ", _BP);

  for (int i = 0; i < RAM_SIZE; i += RAM_ITEM_SIZE)
    {
      int *value = (int *)p;
      char c0 = *(p + 0);
      char c1 = *(p + 1);
      char c2 = *(p + 2);
      char c3 = *(p + 3);
      gotoxy (8 + l++, 70);
      printf ("%s %4d - %hhx%hhx%hhx%hhx %4d %s",
              (i >= _SP && i <= _BP) ? COLOR_YELLOW : COLOR_RESET, i, (INT)c0,
              (INT)c1, (INT)c2, (INT)c3, *value, COLOR_RESET);
      p += RAM_ITEM_SIZE;
    }
}

// ------------------------------------------------------------------ Instance
void
ram_init ()
{
  ram = (_RAM_ *)malloc (sizeof (_RAM_));
  memset (ram, 0x00, sizeof (_RAM_));

  ram->dump = ram_dump;
  ram->mem_avail = ram_mem_avail;

  ram->stack_alloc = ram_stack_alloc;
  ram->stack_free = ram_stack_free;
  ram->stack_read = ram_stack_read;
  ram->stack_bp2sp = ram_stack_bp2sp;
  ram->stack_sp2bp = ram_stack_sp2bp;
  ram->stack_upd_regs = ram_stack_upd_regs;

  ram->ptr = (PTR)malloc (RAM_SIZE);
  memset (ram->ptr, 0x00, RAM_SIZE);

  ram->header = (_RAM_HEADER *)ram->ptr;

  ram->header->heap_ini = 0;
  ram->header->heap_end = ram->header->heap_ini;

  ram->header->stack_ini = RAM_SIZE;
  ram->header->stack_end = ram->header->stack_ini;

  ram_stack_upd_regs ();
}

void
ram_release ()
{
  free (ram->ptr);
  ram->ptr = NULL;

  free (ram);
  ram = NULL;
}

// ------------------------------------------------------------------ Ram Ends
