#ifndef SOURCE_H
#define SOURCE_H

typedef struct
{
  char line[100];
} _SOURCE_LINE_;

typedef struct
{
  _SOURCE_LINE_ *lines;
  int lines_cnt;

  // ---------- public methods
  int (*load) (char *filename);
  void (*dump) (int current_line);
  int (*count_lines) ();
  char *(*get_line) (int row);

} _SOURCE_;

#ifdef SOURCE_C
_SOURCE_ *source = NULL;
#else
extern _SOURCE_ *source;
#endif

void source_init ();
void source_release ();

#endif
