#define SOURCE_C

#include <start.h>

#define SOURCE_GET_LINE(n)                                                    \
  (char *)source->lines + ((n) - 1) * sizeof (_SOURCE_LINE_)

// ---------------------------------------------------------------------- Load
int
source_load_countlines (FILE *file)
{
  int cnt = 0;
  char line[100];

  while (fgets (line, sizeof (line), file))
    cnt++;

  rewind (file);
  return cnt;
}

void
source_load_readlines (FILE *file)
{
  int cnt = 1;
  char line[100];

  while (fgets (line, sizeof (line), file))
    {
      char *pline = SOURCE_GET_LINE (cnt++);
      strcpy (pline, line);
      *(pline + strlen (pline) - 1) = 0x00;
    }
}

void
source_load_alloc ()
{
  int n_size = source->lines_cnt * sizeof (_SOURCE_LINE_);
  source->lines = (_SOURCE_LINE_ *)malloc (n_size);
  memset (source->lines, 0x00, n_size);
}

int
source_load (char *filename)
{
  FILE *file = fopen (filename, "r");
  {
    source->lines_cnt = source_load_countlines (file);
    source_load_alloc ();
    source_load_readlines (file);
  }
  fclose (file);
  return 0;
}

// --------------------------------------------------------------- Data Access
int
source_count_lines ()
{
  return source->lines_cnt;
}

char *
source_get_line (int line)
{
  return SOURCE_GET_LINE (line);
}

// ----------------------------------------------------------------------- Dump
void
source_dump (int current_line)
{
  for (int cnt = 1; cnt <= source->lines_cnt; cnt++)
    {
      char *pline = source_get_line (cnt);
      gotoxy (4 + cnt, 30);
      printf ("%s %03d %-40s %s",
              (cnt == current_line) ? COLOR_YELLOW : COLOR_RESET, cnt, pline,
              COLOR_RESET);
    }
}

// ------------------------------------------------------------------ Instance
void
source_init ()
{
  source = (_SOURCE_ *)malloc (sizeof (_SOURCE_));
  memset (source, 0x00, sizeof (_SOURCE_));

  source->load = source_load;
  source->dump = source_dump;
  source->count_lines = source_count_lines;
  source->get_line = source_get_line;
}

void
source_release ()
{
  free (source->lines);
  source->lines = NULL;

  free (source);
  source = NULL;
}

// --------------------------------------------------------------- Source Ends
