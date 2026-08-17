
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
  gotoxy (45, 1);
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
  if (stmnt->cmd_code == NT_STOP)
    return cpu_stmnt_exit ();

  // ----------------------------------------------------------------- Comments
  else if (stmnt->cmd_code == NT_VOID)
    cpu_stmnt_void ();

  // -------------------------------------------------------------------- Jumps
  else if (stmnt->cmd_code == NT_JMP)
    return cpu_stmnt_jmp (stmnt->jmp_label);

  else if (stmnt->cmd_code == NT_JZ)
    {
      if (reg.ZF == 1)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  else if (stmnt->cmd_code == NT_JNZ)
    {
      if (reg.ZF == 0)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  // ---------------------------------------------------------------- Functions
  else if (stmnt->cmd_code == NT_CALL)
    return cpu_stmnt_call (stmnt->jmp_label);

  else if (stmnt->cmd_code == NT_RET)
    return cpu_stmnt_ret ();

  // ----------------------------------------------------------------- Register
  else if (stmnt->cmd_code == NT_MOV)
    regs_mov (stmnt->par1, stmnt->par2);

  else if (stmnt->cmd_code == NT_ADD)
    regs_add (stmnt->par1, stmnt->par2);

  else if (stmnt->cmd_code == NT_SUB)
    regs_sub (stmnt->par1, stmnt->par2);

  else if (stmnt->cmd_code == NT_INC)
    regs_inc (stmnt->par1);

  else if (stmnt->cmd_code == NT_DEC)
    regs_dec (stmnt->par1);

  else if (stmnt->cmd_code == NT_CMP)
    regs_cmp (stmnt->par1, stmnt->par2);

  // -------------------------------------------------------------------- Stack
  else if (stmnt->cmd_code == NT_PUSH)
    regs_push (stmnt->par1);

  else if (stmnt->cmd_code == NT_POP)
    regs_pop (stmnt->par1);

  // ------------------------------------------------------------------- Memory
  else if (stmnt->cmd_code == NT_INTEGER)
    mem_declare (stmnt->par1, 1, 0);

  else if (stmnt->cmd_code == NT_LOAD)
    mem_load (stmnt->par1, stmnt->par2);

  else if (stmnt->cmd_code == NT_STORE)
    mem_store (stmnt->par1, stmnt->par2);

  // --------------------------------------------------------------- Interrupts
  else if (stmnt->cmd_code == NT_INT)
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
