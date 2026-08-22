#define REGS_C

#include <start.h>

#define COMP(a, b) (((a) - (b)) == 0 ? 0 : ((a) > (b) ? 1 : -1))

#define AND(a, b) ((a) && (b))
#define OR(a, b) ((a) || (b))
#define NOT(a) (!(a))

#define BXOR(a, b) ((a) ^ (b))
#define BAND(a, b) ((a) & (b))
#define BOR(a, b) ((a) | (b))
#define BNOT(a) (~(a))

void
regs_reset ()
{
  memset ((void *)&reg, 0x00, sizeof (reg));
}

int
Reg_Get (char *registro)
{
  if (strcmp (registro, "AX") == 0)
    return AX_Get ();
  else if (strcmp (registro, "BX") == 0)
    return BX_Get ();
  else if (strcmp (registro, "CX") == 0)
    return CX_Get ();
  else if (strcmp (registro, "DX") == 0)
    return DX_Get ();
  else if (strcmp (registro, "BP") == 0)
    return BP_Get ();
  else if (strcmp (registro, "SP") == 0)
    return SP_Get ();
  else if (strcmp (registro, "IP") == 0)
    return IP_Get ();
  else if (strcmp (registro, "DI") == 0)
    return DI_Get ();
  else if (strcmp (registro, "SI") == 0)
    return SI_Get ();
  else if (strcmp (registro, "RX") == 0)
    return RX_Get ();
  return atoi (registro);
}

void
Reg_Set (char *registro, int value)
{
  if (strcmp (registro, "AX") == 0)
    AX_Set (value);
  if (strcmp (registro, "BX") == 0)
    BX_Set (value);
  if (strcmp (registro, "CX") == 0)
    CX_Set (value);
  if (strcmp (registro, "DX") == 0)
    DX_Set (value);
  if (strcmp (registro, "DI") == 0)
    DI_Set (value);
  if (strcmp (registro, "SI") == 0)
    SI_Set (value);
  if (strcmp (registro, "RX") == 0)
    RX_Set (value);
  if (strcmp (registro, "BP") == 0)
    ram->header->stack_ini = value;
}

void
regs_inc (char *registro)
{
  if (strcmp (registro, "AX") == 0)
    AX_Set (AX_Get () + 1);
  if (strcmp (registro, "BX") == 0)
    BX_Set (BX_Get () + 1);
  if (strcmp (registro, "CX") == 0)
    CX_Set (CX_Get () + 1);
  if (strcmp (registro, "DX") == 0)
    DX_Set (DX_Get () + 1);
}

void
regs_dec (char *registro)
{
  if (strcmp (registro, "AX") == 0)
    AX_Set (AX_Get () - 1);
  if (strcmp (registro, "BX") == 0)
    BX_Set (BX_Get () - 1);
  if (strcmp (registro, "CX") == 0)
    CX_Set (CX_Get () - 1);
  if (strcmp (registro, "DX") == 0)
    DX_Set (DX_Get () - 1);
}

void
regs_mov (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "DI") == 0)
    DI_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "SI") == 0)
    SI_Set (Reg_Get (reg_src));
  if (strcmp (reg_dest, "RX") == 0)
    RX_Set (Reg_Get (reg_src));
  if ((strcmp (reg_dest, "BP") == 0) && (strcmp (reg_src, "SP") == 0))
    ram->stack_sp2bp ();
  if ((strcmp (reg_dest, "SP") == 0) && (strcmp (reg_src, "BP") == 0))
    ram->stack_bp2sp ();
}

void
regs_add (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (AX_Get () + Reg_Get (reg_src));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BX_Get () + Reg_Get (reg_src));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (CX_Get () + Reg_Get (reg_src));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (DX_Get () + Reg_Get (reg_src));
}

void
regs_mul (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (AX_Get () * Reg_Get (reg_src));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BX_Get () * Reg_Get (reg_src));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (CX_Get () * Reg_Get (reg_src));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (DX_Get () * Reg_Get (reg_src));
}

void
regs_div (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (AX_Get () / Reg_Get (reg_src));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BX_Get () / Reg_Get (reg_src));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (CX_Get () / Reg_Get (reg_src));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (DX_Get () / Reg_Get (reg_src));
}

void
regs_mod (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (AX_Get () % Reg_Get (reg_src));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BX_Get () % Reg_Get (reg_src));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (CX_Get () % Reg_Get (reg_src));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (DX_Get () % Reg_Get (reg_src));
}

void
regs_sub (char *reg_dest, char *reg_src)
{
  ZF_Set (0);
  if (strcmp (reg_dest, "AX") == 0)
    {
      AX_Set (AX_Get () - Reg_Get (reg_src));
      ZF_Set (COMP (AX_Get (), Reg_Get (reg_src)));
    }
  if (strcmp (reg_dest, "BX") == 0)
    {
      BX_Set (BX_Get () - Reg_Get (reg_src));
      ZF_Set (COMP (BX_Get (), Reg_Get (reg_src)));
    }
  if (strcmp (reg_dest, "CX") == 0)
    {
      CX_Set (CX_Get () - Reg_Get (reg_src));
      ZF_Set (COMP (CX_Get (), Reg_Get (reg_src)));
    }
  if (strcmp (reg_dest, "DX") == 0)
    {
      DX_Set (DX_Get () - Reg_Get (reg_src));
      ZF_Set (COMP (DX_Get (), Reg_Get (reg_src)));
    }
  if (strcmp (reg_dest, "SP") == 0)
    {
      ram->stack_alloc (atoi (reg_src));
    }
}
// ------------------------------------------------------------------- Compare
void
regs_cmp (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    ZF_Set (COMP (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    ZF_Set (COMP (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    ZF_Set (COMP (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    ZF_Set (COMP (DX_Get (), Reg_Get (reg_src)));
}

// -------------------------------------------------------------- Logical Inst
void
regs_and (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (AND (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (AND (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (AND (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    CX_Set (AND (CX_Get (), Reg_Get (reg_src)));
}

void
regs_or (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (OR (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (OR (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (OR (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    CX_Set (OR (CX_Get (), Reg_Get (reg_src)));
}

void
regs_not (char *reg_dest)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (NOT (AX_Get ()));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (NOT (BX_Get ()));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (NOT (CX_Get ()));
  if (strcmp (reg_dest, "DX") == 0)
    CX_Set (NOT (CX_Get ()));
}

//                                                                 Bitwise
void
regs_bxor (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (BXOR (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BXOR (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (BXOR (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (BXOR (DX_Get (), Reg_Get (reg_src)));
}

void
regs_band (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (BAND (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BAND (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (BAND (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (BAND (DX_Get (), Reg_Get (reg_src)));
}

void
regs_b_or (char *reg_dest, char *reg_src)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (BOR (AX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BOR (BX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (BOR (CX_Get (), Reg_Get (reg_src)));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (BOR (DX_Get (), Reg_Get (reg_src)));
}

void
regs_bnot (char *reg_dest)
{
  if (strcmp (reg_dest, "AX") == 0)
    AX_Set (BNOT (AX_Get ()));
  if (strcmp (reg_dest, "BX") == 0)
    BX_Set (BNOT (BX_Get ()));
  if (strcmp (reg_dest, "CX") == 0)
    CX_Set (BNOT (CX_Get ()));
  if (strcmp (reg_dest, "DX") == 0)
    DX_Set (BNOT (DX_Get ()));
}

void
Reg_Backup ()
{
  memcpy (&reg_bk, &reg, sizeof (_REG_));
}

void
regs_dump ()
{
  gotoxy (1, 1);
  printf (" AX : %4d  BX : %4d  CX : %4d  DX : %4d  ZF : %4d  DI : "
          "%4d  SI : %4d  RX : %4d",
          reg_bk.AX, reg_bk.BX, reg_bk.CX, reg_bk.DX, reg_bk.ZF, reg_bk.DI,
          reg_bk.SI, reg_bk.RX);

  gotoxy (2, 1);
  printf (" AX : %4d  BX : %4d  CX : %4d  DX : %4d  ZF : %4d  DI : "
          "%4d  SI : %4d  RX : %4d",
          AX_Get (), BX_Get (), CX_Get (), DX_Get (), ZF_Get (), DI_Get (),
          SI_Get (), RX_Get ());
}
