#define PREPROC_C

#include <start.h>

#define PREPROC_GET_LINE(n)                                                   \
  (char *)preproc->lines + ((n) - 1) * sizeof (_SOURCE_LINE_)

void
preproc_load ()
{

  preproc->lines_cnt = source->lines_cnt;

  preproc->lines = (_PREPROC_LINE_ *)malloc (preproc->lines_cnt
                                             * sizeof (_PREPROC_LINE_));
  memset (preproc->lines, 0x00, preproc->lines_cnt * sizeof (_PREPROC_LINE_));

  memcpy (preproc->lines, source->lines,
          preproc->lines_cnt * sizeof (_SOURCE_LINE_));

  for (int row = 1; row <= preproc->lines_cnt; row++)
    {
      _PREPROC_LINE_ *pline = &(preproc->lines[row - 1]);
      char *line = pline->line;
      trim (line);
      if (*line == ';')
        *line = 0x00;

      if (*line != 0x00)
        {

          // Cortar Comentarios
          char *p = strstr (line, ";");
          if (p)
            {
              *p = 0x00;
              trim (line);
            }

          // Encuentra Global Label
          p = strstr (line, CODE_LBL_GLOBAL);
          if (p && !*(preproc->global_label))
            {
              p = p + strlen (CODE_LBL_GLOBAL);
              strcpy (preproc->global_label, p);
              trim (preproc->global_label);
            }

          if (isDefine (line))
            {
              callDefine (line);
            }

          // Labels count
          if (*(line + strlen (line) - 1) == ':')
            {
              preproc->label_cnt++;
            }
        }
    }
}

void
preproc_dump ()
{

  for (int row = 1; row <= preproc->lines_cnt; row++)
    {
      char *line = (char *)&(preproc->lines[row - 1]);
      printf (":: [%s]\n", line);
    }
}

int
preproc_count_lines ()
{
  return preproc->lines_cnt;
}

char *
precod_get_line (int line)
{
  return PREPROC_GET_LINE (line);
}

char *
preproc_global ()
{
  return preproc->global_label;
}

void
preproc_set_global (char *label)
{
  strcpy (preproc->global_label, label);
}

// ------------------------------------------------------------------ Instance
void
preproc_init ()
{
  preproc = (_PREPROC_ *)malloc (sizeof (_PREPROC_));
  memset (preproc, 0x00, sizeof (_PREPROC_));

  preproc->load = preproc_load;
  preproc->dump = preproc_dump;
  preproc->count_lines = preproc_count_lines;
  preproc->get_line = precod_get_line;

  preproc->global = preproc_global;
  preproc->set_global = preproc_set_global;
}

void
preproc_release ()
{
  free (preproc->lines);
  free (preproc);
  preproc = NULL;
}

// -------------------------------------------------------------- Preproc Ends
