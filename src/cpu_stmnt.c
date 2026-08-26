
#include <start.h>

// -------------------------------------------------- Function Call Management
int
cpu_stmnt_call (int jmp_label, char *label)
{
  frame->push (label);
  _push (IP_Get () + 1);
  IP_Set (jmp_label);
  return 0;
}

int
cpu_stmnt_ret ()
{
  frame->pop ();
  IP_Set (_pop ());
  return 0;
}

// ---------------------------------------------------------------------- Jump
int
cpu_stmnt_jmp (int row, char *label)
{
  frame->setCurrent (label);
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
cpu_stmnt_error (int idx, int cmd, char *par1, char *par2)
{
  gotoxy (45, 1);
  printf ("\n ERROR  ***  ");
  printf ("\n   Line   : %d  ", idx);
  printf ("\n          : %d %s %s", cmd, par1, par2);
  printf ("\n ***  ");
}

// ------------------------------------------------------------ Statement Main
int
cpu_stmnt_eval (_CODE_LINE_ *stmnt)
{

  // -------------------------------------------------------------------- Stop
  if (stmnt->code_cmd == NT_END)
    return cpu_stmnt_exit ();

  // ---------------------------------------------------------------- Comments
  else if (stmnt->code_cmd == NT_NOP)
    {
      if (stmnt->type == 0)
        frame->setCurrent (stmnt->par1);
      cpu_stmnt_void ();
    }
  // ------------------------------------------------------------------- Jumps
  else if (stmnt->code_cmd == NT_JMP)
    return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);

  else if (stmnt->code_cmd == NT__JZ)
    {
      if (reg.ZF == 0)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  else if (stmnt->code_cmd == NT_JNZ)
    {
      if (reg.ZF != 0)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  else if (stmnt->code_cmd == NT_JGT)
    {
      if (reg.ZF == 1)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  else if (stmnt->code_cmd == NT_JGE)
    {
      if (reg.ZF == 0 || reg.ZF == 1)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  else if (stmnt->code_cmd == NT_JLT)
    {
      if (reg.ZF == -1)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  else if (stmnt->code_cmd == NT_JLE)
    {
      if (reg.ZF == 0 || reg.ZF == -1)
        return cpu_stmnt_jmp (stmnt->jmp_label, stmnt->par1);
    }

  // --------------------------------------------------------------- Functions
  else if (stmnt->code_cmd == NT_CALL)
    return cpu_stmnt_call (stmnt->jmp_label, stmnt->par1);

  else if (stmnt->code_cmd == NT_RET)
    return cpu_stmnt_ret ();

  // ---------------------------------------------------------------- Register
  else if (stmnt->code_cmd == NT_MOV)
    regs_mov (stmnt->par1, stmnt->par2);

  //                                                               Maths
  else if (stmnt->code_cmd == NT_ADD)
    regs_add (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_SUB)
    regs_sub (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_MUL)
    regs_mul (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_DIV)
    regs_div (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_MOD)
    regs_mod (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_INC)
    regs_inc (stmnt->par1);

  else if (stmnt->code_cmd == NT_DEC)
    regs_dec (stmnt->par1);

  //                                                              Compare
  else if (stmnt->code_cmd == NT_CMP)
    regs_cmp (stmnt->par1, stmnt->par2);

  //                                                              logics
  else if (stmnt->code_cmd == NT_LAND)
    regs_and (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_L_OR)
    regs_or (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_LNOT)
    regs_not (stmnt->par1);

  //                                                                Bits
  else if (stmnt->code_cmd == NT_BXOR)
    regs_bxor (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_BAND)
    regs_band (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_B_OR)
    regs_b_or (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_BNOT)
    regs_bnot (stmnt->par1);

  // ------------------------------------------------------------------- Stack
  else if (stmnt->code_cmd == NT_PSH)
    regs_push (stmnt->par1);

  else if (stmnt->code_cmd == NT_POP)
    regs_pop (stmnt->par1);

  // ------------------------------------------------------------------ Memory
  else if (stmnt->code_cmd == NT_LOAD)
    mem_load (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_STORE)
    mem_store (stmnt->par1, stmnt->par2);

  // ------------------------------------------------------------------- Types
  else if (stmnt->code_cmd == NT_NUM)
    mem_declare (stmnt->par1, 1, sizeof (int));

  // -------------------------------------------------------------- Interrupts
  else if (stmnt->code_cmd == NT_SYSCALL)
    syscall_manager (atoi (stmnt->par1));

  // ------------------------------------------------- Undefined Command Error
  else
    {
      cpu_stmnt_error (IP_Get (), stmnt->code_cmd, stmnt->par1, stmnt->par2);
      return -2;
    }

  cpu_stmnt_next ();
  return 0;
}
