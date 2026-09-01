#ifndef PREPROC_H
#define PREPROC_H

typedef struct
{
  //  unsigned char type;
  char line[100];
} _PREPROC_LINE_;

typedef struct
{
  // Lines
  _PREPROC_LINE_ *lines;
  int lines_cnt;

  // global
  char global_label[100];

  // Labels
  int label_cnt;

  void (*load) ();
  void (*dump) ();
  int (*count_lines) ();
  char *(*get_line) (int row);

  char *(*global) ();
  void (*set_global) (char *label);

} _PREPROC_;

#ifdef PREPROC_C
_PREPROC_ *preproc = NULL;
#else
extern _PREPROC_ *preproc;

#endif

void preproc_init ();
void preproc_release ();

#endif
