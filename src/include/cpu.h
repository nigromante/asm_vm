#ifndef CPU_H
#define CPU_H

typedef struct
{
  void (*callback_fn) ();
  void (*set_trace) (void (*fn) ());
  int (*run) ();
} _CPU_;

#ifdef CPU_C
_CPU_ *cpu = NULL;
#else
extern _CPU_ *cpu;
#endif

void cpu_init ();
void cpu_release ();

#endif
