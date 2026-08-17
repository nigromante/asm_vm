#define REG_C

#include <reg.h>

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
