
#ifndef STACK_H
#define STACK_H

#define STACK_MAX 20

#ifdef STACK_C
int stack_data[STACK_MAX];
#else
extern int stack_data[STACK_MAX];
#endif

void __push (int value);
int __pop ();
void stack_dump ();
void stack_init ();
#endif
