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
#define NT_INC 0x0303
#define NT_DEC 0x0304
#define NT_CMP 0x0305

#define NT_PUSH 0x0400
#define NT_POP 0x0401

#define NT_INTEGER 0x0500
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

  { "", NT_VOID },           { ";", NT_VOID },

  { "STOP", NT_STOP },       { "EXIT", NT_STOP },

  { "JMP", NT_JMP },         { "JZ", NT_JZ },     { "JNZ", NT_JNZ },
  { "JE", NT_JZ },           { "JNE", NT_JNZ },

  { "CALL", NT_CALL },       { "RET", NT_RET },

  { "MOV", NT_MOV },         { "ADD", NT_ADD },   { "SUB", NT_SUB },
  { "INC", NT_INC },         { "DEC", NT_DEC },   { "CMP", NT_CMP },

  { "PUSH", NT_PUSH },       { "POP", NT_POP },

  { "INTEGER", NT_INTEGER }, { "LOAD", NT_LOAD }, { "STORE", NT_STORE },

  { "INT", NT_INT },
};

#endif

int nt_get_code (char *code);

#endif
