#ifndef INT_H
#define INT_H

#ifdef INT_C
int vout = 0;
#else

#endif

void syscall_produce (int n, _REG_ *_reg);
int syscall_consume (int *n, _REG_ *_reg);

#endif
