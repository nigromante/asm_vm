#ifndef REG_H
#define REG_H

typedef struct
{
  int AX; // Acumulador
  int BX;
  int CX; //  Contador
  int DX;

  int RX; //  Return
  int DI; //  Parametro
  int SI; //  Parametro
  int IP; //  Instrucion Point
  int ZF; //  Zero flag

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

void DI_Set (int v);
int DI_Get ();
void SI_Set (int v);
int SI_Get ();
void RX_Set (int v);
int RX_Get ();
#endif
