#ifndef CODE_H
#define CODE_H

#define CODE_LBL_GLOBAL "global "
#define CODE_LBL_START "_start"

typedef struct
{
  int reference; // line relative to source
  int type;
  int code_cmd;
  char par1[20]; // label when type == 0
  char par2[20];
  int jmp_label;

} _CODE_LINE_;

typedef struct
{
  int reference;
  char label[20];
} _CODE_LABEL_;

typedef struct
{

  _CODE_LINE_ *lines;
  int lines_cnt;

  _CODE_LABEL_ *labels;
  int labels_cnt;

  // --- global
  char global_label[100];

  // -------------- public methods
  void (*load) ();
  void (*dump) ();

  char *(*global_get) ();
  void (*global_set) (char *label);

  void (*dump_type) (int tipo);

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
