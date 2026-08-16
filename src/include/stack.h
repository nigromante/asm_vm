
#ifndef STACK_H
#define STACK_H

#ifdef STACK_C
int stack_data[20];
int stack_idx = 0;
#else
extern int stack_data[100];
extern int stack_idx;
#endif

void __push (int value);
int __pop ();
void stack_dump ();
void stack_init ();
#endif
