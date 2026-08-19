
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
  if (stmnt->code_cmd == NT_STOP)
    return cpu_stmnt_exit ();

  // ---------------------------------------------------------------- Comments
  else if (stmnt->code_cmd == NT_VOID)
    cpu_stmnt_void ();

  // ------------------------------------------------------------------- Jumps
  else if (stmnt->code_cmd == NT_JMP)
    return cpu_stmnt_jmp (stmnt->jmp_label);

  else if (stmnt->code_cmd == NT_JZ)
    {
      if (reg.ZF == 1)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  else if (stmnt->code_cmd == NT_JNZ)
    {
      if (reg.ZF == 0)
        return cpu_stmnt_jmp (stmnt->jmp_label);
    }

  // --------------------------------------------------------------- Functions
  else if (stmnt->code_cmd == NT_CALL)
    return cpu_stmnt_call (stmnt->jmp_label);

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

  //                                                              logics
  else if (stmnt->code_cmd == NT_EQU)
    regs_cmp (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT__GT)
    regs_cmp_gt (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_GTE)
    regs_cmp_gte (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT__LT)
    regs_cmp_lt (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_LTE)
    regs_cmp_lte (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_LAND)
    regs_cmp_and (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_L_OR)
    regs_cmp_or (stmnt->par1, stmnt->par2);

  else if (stmnt->code_cmd == NT_LNOT)
    regs_cmp_not (stmnt->par1);

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
    mem_declare (stmnt->par1, 1, 0);

  // -------------------------------------------------------------- Interrupts
  else if (stmnt->code_cmd == NT_INT)
    int_manager (atoi (stmnt->par1));

  // ------------------------------------------------- Undefined Command Error
  else
    {
      cpu_stmnt_error (IP_Get (), stmnt->code_cmd, stmnt->par1, stmnt->par2);
      return -2;
    }

  cpu_stmnt_next ();
  return 0;
}
