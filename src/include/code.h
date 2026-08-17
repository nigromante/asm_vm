#ifndef CODE_H
#define CODE_H

#define CODE_LBL_GLOBAL "global "
#define CODE_LBL_START "_start"

typedef struct
{
  int reference; // line relative to source
  char label[20];
  char cmd[20];
  char par1[20];
  char par2[20];
  char par3[20];
  int jmp_label;

} _CODE_LINE_;

typedef struct
{
  int reference;
  char label[20];

} _CODE_LABEL_;

typedef struct
{

  char global_label[100];

  _CODE_LINE_ *lines;
  int lines_cnt;

  _CODE_LABEL_ *labels;
  int labels_cnt;

  // -------------- public methods
  void (*load) ();
  void (*dump) ();

  void (*dump_type) (int tipo);
  char *(*get_global) ();

  _CODE_LINE_ *(*get_line) (int row_number);
  int (*get_row_by_label) (char *labelname);
} _CODE_;

#ifdef CODE_C
_CODE_ *code = NULL;
#else
extern _CODE_ *code;
#endif

void code_init ();
void code_release ();

#endif
