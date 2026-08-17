
#include <start.h>

// -------------------------------------------------- Function Call Management
int
cpu_stmnt_call (int jmp_label)
{
  __push (IP_Get () + 1);
  IP_Set (jmp_label);
  return 0;
}

int
cpu_stmnt_ret ()
{
  IP_Set (__pop ());
  return 0;
}

// ---------------------------------------------------------------------- Jump
int
cpu_stmnt_jmp (int row)
{
  IP_Set (row);
  return 0;
}

// ------------------------------------------------------------ Next Statement
void
cpu_stmnt_next ()
{
  IP_Set (1 + IP_Get ());
}

// ---------------------------------------------------------------------- Void
void
cpu_stmnt_void ()
{
}

// ---------------------------------------------------------------------- Exit
int
cpu_stmnt_exit ()
{
  return -1;
}

// --------------------------------------------------------------------- Error
void
cpu_stmnt_error (int idx, char *cmd, char *par1, char *par2, char *par3)
{
  printf ("\n ERROR  ***  ");
  printf ("\n   Line   : %d  ", idx);
  printf ("\n          : %s %s %s %s", cmd, par1, par2, par3);
  printf ("\n ***  ");
}

// ------------------------------------------------------------ Statement Main
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
    return cpu_stmnt_jmp (stmnt->jmp_label);

  else if (strcmp (stmnt->cmd, "JZ") == 0 || strcmp (stmnt->cmd, "JE") == 0)
    {
      if (reg.ZF == 1)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  else if (strcmp (stmnt->cmd, "JNZ") == 0 || strcmp (stmnt->cmd, "JNE") == 0)
    {
      if (reg.ZF == 0)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  // ---------------------------------------------------------------- Functions
  else if (strcmp (stmnt->cmd, "CALL") == 0)
    return cpu_stmnt_call (stmnt->jmp_label);

  else if (strcmp (stmnt->cmd, "RET") == 0)
    return cpu_stmnt_ret ();

  // ----------------------------------------------------------------- Register
  else if (strcmp (stmnt->cmd, "MOV") == 0)
    regs_mov (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "ADD") == 0)
    regs_add (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "SUB") == 0)
    regs_sub (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "INC") == 0)
    regs_inc (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "DEC") == 0)
    regs_dec (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "CMP") == 0)
    regs_cmp (stmnt->par1, stmnt->par2);

  // -------------------------------------------------------------------- Stack
  else if (strcmp (stmnt->cmd, "PUSH") == 0)
    regs_push (stmnt->par1);

  else if (strcmp (stmnt->cmd, "POP") == 0)
    regs_pop (stmnt->par1);

  // ------------------------------------------------------------------- Memory
  else if (strcmp (stmnt->cmd, "INTEGER") == 0)
    mem_declare (stmnt->par1, 1, 0);

  else if (strcmp (stmnt->cmd, "LOAD") == 0)
    mem_load (stmnt->par1, stmnt->par2);

  else if (strcmp (stmnt->cmd, "STORE") == 0
           || strcmp (stmnt->cmd, "STO") == 0)
    mem_store (stmnt->par1, stmnt->par2);

  // --------------------------------------------------------------- Interrupts
  else if (strcmp (stmnt->cmd, "INT") == 0)
    int_manager (atoi (stmnt->par1));

  // -------------------------------------------------- Undefined Command Error
  else
    {
      cpu_stmnt_error (IP_Get (), stmnt->cmd, stmnt->par1, stmnt->par2,
                       stmnt->par3);
      return -2;
    }

  cpu_stmnt_next ();
  return 0;
}
