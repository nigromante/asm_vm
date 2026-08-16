
#ifndef REGS_H
#define REGS_H

typedef struct
{
  int AX;
  int BX;
  int CX;
  int DX;
  int IP;
  int ZF;
  int BP;
  int SP;

} REG;

#ifdef REGS_C
REG reg;
REG reg_bk;
#else
extern REG reg;

#endif

#endif

void AX_Set (int v);
int AX_Get ();
void BX_Set (int v);
int BX_Get ();
void CX_Set (int v);
int CX_Get ();
void DX_Set (int v);
int DX_Get ();
void IP_Set (int v);
int IP_Get ();
void ZF_Set (int v);
int ZF_Get ();
void BP_Set (int v);
int BP_Get ();
void SP_Set (int v);
int SP_Get ();

int Reg_Get (char *par);
void Reg_Set (char *registro, int value);
void prgm_stmnt_inc (char *par1, char *par2);
void prgm_stmnt_dec (char *par1, char *par2);
void prgm_stmnt_mov (char *par1, char *par2);
void prgm_stmnt_add (char *par1, char *par2);
void prgm_stmnt_sub (char *par1, char *par2);
void prgm_stmnt_cmp (char *par1, char *par2);
void prgm_stmnt_reset ();
void Reg_Backup ();
void regs_dump ();
