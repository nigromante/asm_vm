
#ifndef REGS_H
#define REGS_H

int Reg_Get (char *par);
void Reg_Set (char *registro, int value);
void regs_inc (char *par1, char *par2);
void regs_dec (char *par1, char *par2);
void regs_mov (char *par1, char *par2);
void regs_add (char *par1, char *par2);
void regs_sub (char *par1, char *par2);
void regs_cmp (char *par1, char *par2);
void regs_reset ();
void Reg_Backup ();
void regs_dump ();

#endif
