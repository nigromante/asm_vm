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
DI_Set (int v)
{
  reg.DI = v;
}

int
DI_Get ()
{
  return reg.DI;
}

void
SI_Set (int v)
{
  reg.SI = v;
}

int
SI_Get ()
{
  return reg.SI;
}

void
RX_Set (int v)
{
  reg.RX = v;
}

int
RX_Get ()
{
  return reg.RX;
}
