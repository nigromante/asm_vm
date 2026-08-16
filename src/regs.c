#define REGS_C

#include <regs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vio.h>

void to_uppercase (char *str);

void
AX_Set (int v)
{
  reg.AX = v;
}

int
AX_Get ()
{
  return reg.AX;
}

void
BX_Set (int v)
{
  reg.BX = v;
}

int
BX_Get ()
{
  return reg.BX;
}

void
CX_Set (int v)
{
  reg.CX = v;
}

int
CX_Get ()
{
  return reg.CX;
}

void
DX_Set (int v)
{
  reg.DX = v;
}

int
DX_Get ()
{
  return reg.DX;
}

void
IP_Set (int v)
{
  reg.IP = v;
}

int
IP_Get ()
{
  return reg.IP;
}

void
ZF_Set (int v)
{
  reg.ZF = v;
}

int
ZF_Get ()
{
  return reg.ZF;
}

void
BP_Set (int v)
{
  reg.BP = v;
}

int
BP_Get ()
{
  return reg.BP;
}

void
SP_Set (int v)
{
  reg.SP = v;
}

int
SP_Get ()
{
  return reg.SP;
}

void
prgm_stmnt_reset ()
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
prgm_stmnt_inc (char *par1, char *par2)
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
prgm_stmnt_dec (char *par1, char *par2)
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
prgm_stmnt_mov (char *par1, char *par2)
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
prgm_stmnt_add (char *par1, char *par2)
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
prgm_stmnt_sub (char *par1, char *par2)
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
prgm_stmnt_cmp (char *par1, char *par2)
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
  memcpy (&reg_bk, &reg, sizeof (REG));
}

void
regs_dump ()
{
  gotoxy (1, 1);
  printf (" AX : %4d  BX : %4d  CX : %4d  DX : %4d  IP : %4d  ZF : %4d  BP : "
          "%4d  SP : %4d ",
          AX_Get (), BX_Get (), CX_Get (), DX_Get (), IP_Get (), ZF_Get (),
          BP_Get (), SP_Get ());
}
