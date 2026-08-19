#ifndef NEMOTECHS_H
#define NEMOTECHS_H

#define NT_STOP 0x0100
#define NT_VOID 0x0101

#define NT_JMP 0x0200
#define NT_JZ 0x0201
#define NT_JNZ 0x0202
#define NT_CALL 0x0203
#define NT_RET 0x0204
#define NT_JMP_END 0x02ff

#define NT_MOV 0x0300

#define NT_ADD 0x0301
#define NT_SUB 0x0302
#define NT_MUL 0x0303
#define NT_DIV 0x0304
#define NT_MOD 0x0305

#define NT_INC 0x0306
#define NT_DEC 0x0307

#define NT_EQU 0x0311
#define NT__GT 0x0312
#define NT__LT 0x0313
#define NT_GTE 0x0314
#define NT_LTE 0x0315
#define NT_LAND 0x0316
#define NT_L_OR 0x0317
#define NT_LNOT 0x0318

#define NT_BXOR 0x0321
#define NT_BAND 0x0322
#define NT_B_OR 0x0323
#define NT_BNOT 0x0324
#define NT_BSHL 0x0325
#define NT_BSHR 0x0326

#define NT_PSH 0x0400
#define NT_POP 0x0401

#define NT_NUM 0x0500
#define NT_LOAD 0x0501
#define NT_STORE 0x0502

#define NT_INT 0x0600

#ifdef NEMOTECHS_C

typedef struct
{
  char name[20];
  int code;
} _NM_DATA_;

_NM_DATA_ nm_data[] = {

  { "", NT_VOID },      { ";", NT_VOID },

  { "STOP", NT_STOP },  { "EXIT", NT_STOP },

  { "JMP", NT_JMP },    { "JZ", NT_JZ },       { "JNZ", NT_JNZ },
  { "JE", NT_JZ },      { "JNE", NT_JNZ },

  { "CALL", NT_CALL },  { "RET", NT_RET },

  { "MOV", NT_MOV },

  { "ADD", NT_ADD },    { "SUB", NT_SUB },     { "MUL", NT_MUL },
  { "DIV", NT_DIV },    { "MOD", NT_MOD },     { "INC", NT_INC },
  { "DEC", NT_DEC },

  { "CMP", NT_EQU },    { "EQU", NT_EQU },

  { "XOR", NT_BXOR },   { "AND", NT_BAND },    { "OR", NT_B_OR },
  { "NOT", NT_BNOT },   { "SHL", NT_BSHL },    { "SHR", NT_BSHR },

  { "PUSH", NT_PSH },   { "POP", NT_POP },

  { "NUMBER", NT_NUM }, { "NUM", NT_NUM },

  { "LOAD", NT_LOAD },  { "STORE", NT_STORE },

  { "INT", NT_INT },
};

#endif

int nt_get_code (char *code);

#endif
