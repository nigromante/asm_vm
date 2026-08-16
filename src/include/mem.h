#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

typedef struct
{
  char name[10];
  char value[20];
  int type;
  int len;
} MEM_OBJ;

#ifdef MEM_C
MEM_OBJ *mem_list = NULL;
int mem_idx = 0;
#else
extern MEM_OBJ *mem_list;
extern int men_idx;
#endif

void mem_init ();
void mem_release ();
void mem_debug ();

void prgm_stmnt_declare (char *variable, int type, int size);
void prgm_stmnt_load (char *registro, char *variable);
void prgm_stmnt_store (char *registro, char *variable);
#endif
