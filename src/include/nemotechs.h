#ifndef NEMOTECHS_H
#define NEMOTECHS_H

#define NT_END 0x0100
#define NT_NOP 0x0101

#define NT_JMP 0x0200
#define NT__JZ 0x0201
#define NT_JNZ 0x0202
#define NT_JGT 0x0203
#define NT_JLT 0x0204
#define NT_JGE 0x0205
#define NT_JLE 0x0206
#define NT_CALL 0x0211
#define NT_RET 0x0212
#define NT_JXX 0x02ff

#define NT_MOV 0x0300

#define NT_ADD 0x0301
#define NT_SUB 0x0302
#define NT_MUL 0x0303
#define NT_DIV 0x0304
#define NT_MOD 0x0305

#define NT_INC 0x0306
#define NT_DEC 0x0307

#define NT_CMP 0x0311
#define NT_LAND 0x0312
#define NT_L_OR 0x0313
#define NT_LNOT 0x0314

#define NT_BXOR 0x0321
#define NT_BAND 0x0322
#define NT_B_OR 0x0323
#define NT_BNOT 0x0324
#define NT_BSHL 0x0325
#define NT_BSHR 0x0326

#define NT_PSH 0x0400
#define NT_POP 0x0401

#define NT_LOAD 0x0501
#define NT_STORE 0x0502

#define NT_SYSCALL 0x0600

#define NT_NUM 0x0700
#ifdef NEMOTECHS_C

typedef struct
{
  char name[20];
  int code;
} _NM_DATA_;

_NM_DATA_ nm_data[] = {

  { "", NT_NOP },
  { ";", NT_NOP },
  { "NOP", NT_NOP },

  { "STOP", NT_END },
  { "EXIT", NT_END },
  { "END", NT_END },

  { "JMP", NT_JMP },
  { "JZ", NT__JZ },
  { "JE", NT__JZ },
  { "JNZ", NT_JNZ },
  { "JNE", NT_JNZ },

  { "JGT", NT_JGT },
  { "JGE", NT_JGE },
  { "JLT", NT_JLT },
  { "JLE", NT_JLE },

  { "CALL", NT_CALL },
  { "RET", NT_RET },

  { "MOV", NT_MOV },

  { "ADD", NT_ADD },
  { "SUB", NT_SUB },
  { "MUL", NT_MUL },
  { "DIV", NT_DIV },
  { "MOD", NT_MOD },
  { "INC", NT_INC },
  { "DEC", NT_DEC },

  { "CMP", NT_CMP },

  { "XOR", NT_BXOR },
  { "AND", NT_BAND },
  { "OR", NT_B_OR },
  { "NOT", NT_BNOT },
  { "SHL", NT_BSHL },
  { "SHR", NT_BSHR },

  { "PUSH", NT_PSH },
  { "POP", NT_POP },

  { "NUMBER", NT_NUM },
  { "NUM", NT_NUM },

  { "LOAD", NT_LOAD },
  { "STORE", NT_STORE },

  { "SYSCALL", NT_SYSCALL },
  { "INT", NT_SYSCALL },
};

#endif

int nt_get_code (char *code);

#endif
