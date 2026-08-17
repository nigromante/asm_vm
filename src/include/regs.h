
#ifndef REGS_H
#define REGS_H

int Reg_Get (char *registro);
void Reg_Set (char *registro, int value);
void regs_inc (char *registro);
void regs_dec (char *registro);
void regs_mov (char *reg_dest, char *reg_src);
void regs_add (char *reg_dest, char *reg_src);
void regs_sub (char *reg_dest, char *reg_src);
void regs_cmp (char *reg_dest, char *reg_src);
void regs_reset ();
void Reg_Backup ();
void regs_dump ();

#endif
