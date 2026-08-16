#define CPU_C

#include <start.h>

// ------------------------------------------------------------------ Privates
void
exec_callback ()
{
  if (cpu->callback_fn)
    cpu->callback_fn ();
}

void
cpu_ip_set (int n)
{
  IP_Set (n);
}

int
cpu_ip_get ()
{
  return IP_Get ();
}

// ---------------------------------------------------------------- Statements
// *** Call Function
void
cpu_stmnt_call (int jmp_label)
{
  __push (IP_Get () + 1);
  cpu_ip_set (jmp_label);
}

// *** Return
int
cpu_stmnt_ret ()
{
  return __pop ();
}

void
cpu_stmnt_void ()
{
}

void
cpu_stmnt_next ()
{
  cpu_ip_set (1 + cpu_ip_get ());
}

int
cpu_stmnt_exit ()
{
  return -1;
}

void
cpu_stmnt_push (char *registro)
{
  __push (Reg_Get (registro));
}

void
cpu_stmnt_pop (char *registro)
{
  int value = __pop ();
  Reg_Set (registro, value);
}

void
cpu_stmnt_error (int idx, char *cmd, char *par1, char *par2, char *par3)
{
  printf ("\n ERROR  ***  ");
  printf ("\n   Line   : %d  ", idx);
  printf ("\n          : %s %s %s %s", cmd, par1, par2, par3);
  printf ("\n ***  ");
}

int
cpu_stmnt_eval (_CODE_LINE_ *stmnt)
{

  // --------------------------------------------------------------------- Stop
  if (strcmp (stmnt->cmd, "STOP") == 0 || strcmp (stmnt->cmd, "EXIT") == 0)
    return cpu_stmnt_exit ();

  // ----------------------------------------------------------------- Comments
  else if (strlen (stmnt->cmd) == 0 || strcmp (stmnt->cmd, ";") == 0)
    cpu_stmnt_void ();

  // -------------------------------------------------------------------- Jumps
  else if (strcmp (stmnt->cmd, "JMP") == 0)
    {
      cpu_ip_set (stmnt->jmp_label);
      return 0;
    }
  else if (strcmp (stmnt->cmd, "JZ") == 0 || strcmp (stmnt->cmd, "JE") == 0)
    {
      if (reg.ZF == 1)
        {
          cpu_ip_set (stmnt->jmp_label);
          return 0;
        }
    }
  else if (strcmp (stmnt->cmd, "JNZ") == 0 || strcmp (stmnt->cmd, "JNE") == 0)
    {
      if (reg.ZF == 0)
        {
          cpu_ip_set (stmnt->jmp_label);
          return 0;
        }
    }
  // ---------------------------------------------------------------- Functions
  else if (strcmp (stmnt->cmd, "CALL") == 0)
    {
      __push (cpu_ip_get () + 1);
      cpu_ip_set (stmnt->jmp_label);
      return 0;
    }

  else if (strcmp (stmnt->cmd, "RET") == 0)
    {
      cpu_ip_set (__pop ());
      return 0;
    }

  // ----------------------------------------------------------------- Register
  else if (strcmp (stmnt->cmd, "MOV") == 0)
    prgm_stmnt_mov (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "ADD") == 0)
    prgm_stmnt_add (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "SUB") == 0)
    prgm_stmnt_sub (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "INC") == 0)
    prgm_stmnt_inc (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "DEC") == 0)
    prgm_stmnt_dec (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "CMP") == 0)
    prgm_stmnt_cmp (stmnt->par1, stmnt->par2);

  // -------------------------------------------------------------------- Stack
  else if (strcmp (stmnt->cmd, "PUSH") == 0)
    cpu_stmnt_push (stmnt->par1);

  else if (strcmp (stmnt->cmd, "POP") == 0)
    cpu_stmnt_pop (stmnt->par1);

  // ------------------------------------------------------------------- Memory
  else if (strcmp (stmnt->cmd, "INTEGER") == 0)
    prgm_stmnt_declare (stmnt->par1, 1, 0);

  else if (strcmp (stmnt->cmd, "LOAD") == 0)
    prgm_stmnt_load (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "STORE") == 0
           || strcmp (stmnt->cmd, "STO") == 0)
    prgm_stmnt_store (stmnt->par1, stmnt->par2);

  // --------------------------------------------------------------- Interrupts
  else if (strcmp (stmnt->cmd, "INT") == 0)
    prgm_stmnt_int (atoi (stmnt->par1));

  // -------------------------------------------------- Undefined Command Error
  else
    {
      cpu_stmnt_error (cpu_ip_get (), stmnt->cmd, stmnt->par1, stmnt->par2,
                       stmnt->par3);
      return -2;
    }

  cpu_stmnt_next ();
  return 0;
}

// ---------------------------------------------------------- Public functions
int
cpu_run ()
{
  char *global = code->get_global ();

  cpu_ip_set (code->get_row_by_label (global));

  while (1)
    {
      int line = cpu_ip_get ();
      if (line <= 0)
        break;

      _CODE_LINE_ *stmnt = code->get_line (line);
      if (stmnt == NULL)
        break;

      Reg_Backup ();

      if (cpu_stmnt_eval (stmnt) != 0)
        {
          break;
        }

      exec_callback ();
    }

  return 0;
}

void
cpu_set_callback (void (*fn) ())
{
  cpu->callback_fn = fn;
}

// ------------------------------------------------------------------ Instance
void
cpu_init ()
{
  cpu = (_CPU_ *)malloc (sizeof (_CPU_));
  memset (cpu, 0x00, sizeof (_CPU_));

  cpu->run = cpu_run;
  cpu->set_callback = cpu_set_callback;
}

void
cpu_release ()
{
  free (cpu);
  cpu = NULL;
}

// ------------------------------------------------------------------ Cpu Ends
