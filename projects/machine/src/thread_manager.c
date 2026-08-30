#include <pthread.h>

int execute (char *filename, int mode, int dump_level);
void qsyscall_run ();

typedef struct
{
  char *filename;
  int mode;
  int dump_level;
} _THREAD_PARAM_;

void *
thread_proc (void *param)
{
  _THREAD_PARAM_ *p = (_THREAD_PARAM_ *)param;

  execute (p->filename, p->mode, p->dump_level);
  return NULL;
}

void *
thread_sys (void *param)
{
  // _THREAD_PARAM_ *p = (_THREAD_PARAM_ *)param;
  qsyscall_run ();
  return NULL;
}

int
thread_ini (char *filename, int mode, int dump_level)
{
  _THREAD_PARAM_ param;
  param.filename = filename;
  param.mode = mode;
  param.dump_level = dump_level;

  pthread_t t_proc, t_sys;

  pthread_create (&t_proc, NULL, thread_proc, &param);
  pthread_create (&t_sys, NULL, thread_sys, &param);

  pthread_join (t_proc, NULL);
  pthread_join (t_sys, NULL);

  return 0;
}
