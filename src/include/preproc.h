#ifndef PREPROC_H
#define PREPROC_H

typedef struct
{
  _SOURCE_LINE_ *lines;
  int lines_cnt;

  char global_label[100];

  void (*load) ();
  void (*dump) ();
  int (*count_lines) ();
  char *(*get_line) (int row);

  char *(*global) ();
  char (*set_global) (char *label);

} _PREPROC_;

#ifdef PREPROC_C
_PREPROC_ *preproc = NULL;
#else
extern _PREPROC_ *preproc;

#endif

void preproc_init ();
void preproc_release ();

#endif
