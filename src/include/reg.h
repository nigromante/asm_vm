#ifndef REG_H
#define REG_H

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

} _REG_;

#ifdef REG_C

_REG_ reg;
_REG_ reg_bk;
#else

extern _REG_ reg;
extern _REG_ reg_bk;
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

#endif
