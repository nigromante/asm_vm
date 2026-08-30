#include <start.h>

extern int tfinish;
int vrow = 0;

void
print_ax ()
{
  print_at (5 + vrow++, vio_offset, "%-16s :: %-16s [ AX | %d ]",
            frame->last (), frame->getCurrent (), AX_Get ());
}

void
print_bx ()
{
  print_at (5 + vrow++, vio_offset, "%-16s :: %-16s [ BX | %d ]",
            frame->last (), frame->getCurrent (), BX_Get ());
}

void
print_cx ()
{
  print_at (5 + vrow++, vio_offset, "%-16s :: %-16s [ CX | %d ]",
            frame->last (), frame->getCurrent (), CX_Get ());
}

void
print_dx ()
{
  print_at (5 + vrow++, vio_offset, "%-16s :: %-16s [ DX | %d ]",
            frame->last (), frame->getCurrent (), DX_Get ());
}

void
qsyscall_run ()
{
  int n;
  _REG_ _reg;

  while (!tfinish)
    {
      if (!syscall_consume (&n, &_reg))
        {
          sleep_ms (100);
          continue;
        }

      switch (n)
        {
        case 80:
          print_ax ();
          break;
        case 81:
          print_bx ();
          break;
        case 82:
          print_cx ();
          break;
        case 83:
          print_dx ();
          break;
        }
    }
}
