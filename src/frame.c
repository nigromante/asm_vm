#define FRAME_C

#include <start.h>

void
frame_setcurrent (char *frame_name)
{
  strcpy (frame->stack[frame->stack_idx - 1].current, frame_name);
}

void
frame_push (char *frame_name)
{
  strcpy (frame->stack[frame->stack_idx].frame, frame_name);
  strcpy (frame->stack[frame->stack_idx].current, frame_name);
  frame->stack_idx++;
}

void
frame_pop ()
{
  frame->stack_idx--;
}

char *
frame_current ()
{
  return (char *)frame->stack[frame->stack_idx - 1].current;
}

char *
frame_last ()
{
  return (char *)frame->stack[frame->stack_idx - 1].frame;
}

// ------------------------------------------------------------------ Instance
void
frame_init ()
{
  frame = (_FRAME_ *)malloc (sizeof (_FRAME_));
  memset (frame, 0x00, sizeof (_FRAME_));
  frame->setCurrent = frame_setcurrent;
  frame->push = frame_push;
  frame->pop = frame_pop;
  frame->last = frame_last;
  frame->getCurrent = frame_current;
}

void
frame_release ()
{
  free (frame);
}

// ---------------------------------------------------------------- Frame Ends
