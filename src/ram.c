#define RAM_C

#include <start.h>

// ----------------------------------------------------------------- Funciones
int
ram_mem_avail ()
{
  return (_SP - ram->header->heap_end);
}

// --------------------------------------------------------------------- Stack

PTR
ram_stack_alloc (int n)
{
  if (n > ram_mem_avail ())
    {
      perror ("memory not available");
      return NULL;
    }
  _SP = _SP - n;

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
}

void
ram_stack_bp2sp ()
{
  _SP = _BP;
}

void
ram_stack_sp2bp ()
{
  _BP = _SP;
}

// ---------------------------------------------------------------------- Heap
PTR
ram_heap_alloc (int n)
{
  PTR p = ram->ptr + ram->header->heap_end;
  ram->header->heap_end += n;
  memset (p, 0x00, n);
  return p;
}

// --------------------------------------------------------------------- Dumps
void
ram_dump ()
{
  int l = 1;
  PTR p = ram->ptr;

  for (int i = 0; i < RAM_SIZE; i += RAM_ITEM_SIZE)
    {
      int *value = (int *)p;
      unsigned char c0 = *(p + 0);
      unsigned char c1 = *(p + 1);
      unsigned char c2 = *(p + 2);
      unsigned char c3 = *(p + 3);

      gotoxy (4 + l++, 72);
      {

        if (i >= 0 && i < sizeof (_RAM_HEADER_))
          printf (COLOR_CYAN);
        if (i >= sizeof (_RAM_HEADER_) && i < ram->header->heap_end)
          printf (COLOR_ORANGE);
        if (i >= _SP && i <= _BP)
          printf (COLOR_BOLD_YELLOW);
        if (i > _BP && i < RAM_DATA_SIZE + RAM_HEADER_SIZE)
          printf (COLOR_YELLOW);
        if (i >= RAM_DATA_SIZE + RAM_HEADER_SIZE)
          printf (COLOR_PURPLE);

        printf ("%3d %02x%02x%02x%02x %4d", i, c0, c1, c2, c3, *value);
      }
      printf (COLOR_RESET);
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

  ram->heap_alloc = ram_heap_alloc;

  ram->ptr = (PTR)malloc (RAM_SIZE);
  memset (ram->ptr, 0x00, RAM_SIZE);

  ram->header = (_RAM_HEADER_ *)ram->ptr;

  ram->header->heap_ini = sizeof (_RAM_HEADER_);
  ram->header->heap_end = ram->header->heap_ini;

  ram->header->stack_ini = RAM_DATA_SIZE + RAM_HEADER_SIZE;
  ram->header->stack_end = ram->header->stack_ini;
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
