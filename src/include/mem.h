#ifndef MEM_H
#define MEM_H

typedef struct
{
  char name[10];
  char *value;
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
void mem_dump ();

void mem_declare (char *variable, int type, int size);
void mem_load (char *registro, char *variable);
void mem_store (char *variable, char *registro);
#endif
