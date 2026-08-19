#ifndef CPU_H
#define CPU_H

typedef struct
{
  void (*callback_fn) ();
  void (*set_trace) (void (*fn) ());
  int (*run) ();
  void (*set_start) ();
  int (*ciclos_total) ();
} _CPU_;

#ifdef CPU_C
_CPU_ *cpu = NULL;
int ciclos = 0;
#else
extern _CPU_ *cpu;
#endif

void cpu_init ();
void cpu_release ();

#endif
