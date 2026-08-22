#ifndef RAM_H
#define RAM_H

// --- Constants
#define RAM_MAX 1 //  KB
#define RAM_ITEM_SIZE 4
#define RAM_SEGMENT 64
#define RAM_SIZE (RAM_SEGMENT * RAM_MAX + sizeof (_RAM_HEADER_))

#define RAM_MAX_VAR 20

// Macros
#define _BP ram->header->stack_ini
#define _SP ram->header->stack_end

// --- Types definition
typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef char *PTR;
typedef struct
{
  char name[10];
  UINT size;
  UINT type;
  PTR ptr;
} _RAM_OBJ_;

typedef struct
{
  INT program_control;
  INT stack_ini;
  INT stack_end;
  INT heap_ini;
  INT heap_end;

  char filler[12];

} _RAM_HEADER_;

typedef struct
{
  PTR ptr;

  _RAM_HEADER_ *header;

  void (*dump) ();
  int (*mem_avail) ();
  PTR (*stack_alloc) (int n);
  PTR (*stack_read) (int n);
  void (*stack_free) (int n);
  void (*stack_bp2sp) ();
  void (*stack_sp2bp) ();
} _RAM_;

// --- Declare Variables
#ifdef RAM_C
_RAM_ *ram = NULL;
#else
extern _RAM_ *ram;
#endif

// --- Public functions
void ram_init ();
void ram_release ();
#endif
