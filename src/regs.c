#define REGS_C

#include <start.h>

void
regs_reset ()
{
  memset ((void *)&reg, 0x00, sizeof (reg));
}

int
Reg_Get (char *par)
{
  to_uppercase (par);
  if (strcmp (par, "AX") == 0)
    return AX_Get ();
  else if (strcmp (par, "BX") == 0)
    return BX_Get ();
  else if (strcmp (par, "CX") == 0)
    return CX_Get ();
  else if (strcmp (par, "DX") == 0)
    return DX_Get ();
  else if (strcmp (par, "BP") == 0)
    return BP_Get ();
  else if (strcmp (par, "SP") == 0)
    return SP_Get ();
  else if (strcmp (par, "IP") == 0)
    return IP_Get ();
  return atoi (par);
}

void
Reg_Set (char *registro, int value)
{
  to_uppercase (registro);
  if (strcmp (registro, "AX") == 0)
    AX_Set (value);
  if (strcmp (registro, "BX") == 0)
    BX_Set (value);
  if (strcmp (registro, "CX") == 0)
    CX_Set (value);
  if (strcmp (registro, "DX") == 0)
    DX_Set (value);
  if (strcmp (registro, "BP") == 0)
    BP_Set (value);
  if (strcmp (registro, "SP") == 0)
    SP_Set (value);
}

void
regs_inc (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    AX_Set (AX_Get () + 1);
  if (strcmp (par1, "BX") == 0)
    BX_Set (BX_Get () + 1);
  if (strcmp (par1, "CX") == 0)
    CX_Set (CX_Get () + 1);
  if (strcmp (par1, "DX") == 0)
    DX_Set (DX_Get () + 1);
}

void
regs_dec (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    AX_Set (AX_Get () - 1);
  if (strcmp (par1, "BX") == 0)
    BX_Set (BX_Get () - 1);
  if (strcmp (par1, "CX") == 0)
    CX_Set (CX_Get () - 1);
  if (strcmp (par1, "DX") == 0)
    DX_Set (DX_Get () - 1);
}

void
regs_mov (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    AX_Set (Reg_Get (par2));
  if (strcmp (par1, "BX") == 0)
    BX_Set (Reg_Get (par2));
  if (strcmp (par1, "CX") == 0)
    CX_Set (Reg_Get (par2));
  if (strcmp (par1, "DX") == 0)
    DX_Set (Reg_Get (par2));
  if (strcmp (par1, "BP") == 0)
    BP_Set (Reg_Get (par2));
  if (strcmp (par1, "SP") == 0)
    SP_Set (Reg_Get (par2));
}

void
regs_add (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    AX_Set (AX_Get () + Reg_Get (par2));
  if (strcmp (par1, "BX") == 0)
    BX_Set (BX_Get () + Reg_Get (par2));
  if (strcmp (par1, "CX") == 0)
    CX_Set (CX_Get () + Reg_Get (par2));
  if (strcmp (par1, "DX") == 0)
    DX_Set (DX_Get () + Reg_Get (par2));
  if (strcmp (par1, "SP") == 0)
    DX_Set (SP_Get () + Reg_Get (par2));
}

void
regs_sub (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    {
      AX_Set (AX_Get () - Reg_Get (par2));
      ZF_Set (AX_Get () == 0);
    }
  if (strcmp (par1, "BX") == 0)
    {
      BX_Set (BX_Get () - Reg_Get (par2));
      ZF_Set (BX_Get () == 0);
    }
  if (strcmp (par1, "CX") == 0)
    {
      CX_Set (CX_Get () - Reg_Get (par2));
      ZF_Set (CX_Get () == 0);
    }
  if (strcmp (par1, "DX") == 0)
    {
      DX_Set (DX_Get () - Reg_Get (par2));
      ZF_Set (DX_Get () == 0);
    }
  if (strcmp (par1, "SP") == 0)
    {
      SP_Set (SP_Get () - Reg_Get (par2));
      ZF_Set (SP_Get () == 0);
    }
}

void
regs_cmp (char *par1, char *par2)
{
  to_uppercase (par1);
  if (strcmp (par1, "AX") == 0)
    ZF_Set ((AX_Get () - Reg_Get (par2)) == 0);
  if (strcmp (par1, "BX") == 0)
    ZF_Set ((BX_Get () - Reg_Get (par2)) == 0);
  if (strcmp (par1, "CX") == 0)
    ZF_Set ((CX_Get () - Reg_Get (par2)) == 0);
  if (strcmp (par1, "DX") == 0)
    ZF_Set ((DX_Get () - Reg_Get (par2)) == 0);
  if (strcmp (par1, "SP") == 0)
    ZF_Set ((SP_Get () - Reg_Get (par2)) == 0);
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
  printf (" AX : %4d  BX : %4d  CX : %4d  DX : %4d  IP : %4d  ZF : %4d  BP : "
          "%4d  SP : %4d ",
          reg_bk.AX, reg_bk.BX, reg_bk.CX, reg_bk.DX, reg_bk.IP, reg_bk.ZF,
          reg_bk.BP, reg_bk.SP);
  gotoxy (2, 1);
  printf (" AX : %4d  BX : %4d  CX : %4d  DX : %4d  IP : %4d  ZF : %4d  BP : "
          "%4d  SP : %4d ",
          AX_Get (), BX_Get (), CX_Get (), DX_Get (), IP_Get (), ZF_Get (),
          BP_Get (), SP_Get ());
}
