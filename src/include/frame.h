#ifndef FRAME_H
#define FRAME_H

typedef struct
{
  char frame[20];
  char current[20];
} FRAME_ITEM;

typedef struct
{
  FRAME_ITEM stack[10];
  int stack_idx;

  void (*push) (char *current);
  void (*pop) ();
  char *(*last) ();
  char *(*getCurrent) ();
  void (*setCurrent) (char *current);
} _FRAME_;

#ifdef FRAME_C
_FRAME_ *frame = NULL;
#else
extern _FRAME_ *frame;
#endif

void frame_init ();
void frame_release ();

#endif
