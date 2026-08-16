#define SOURCE_C

#include <start.h>

char *
source_ptr2line (int line)
{
  return (char *)source->lines + (line) * sizeof (_SOURCE_LINE_);
}

int
count_lines (FILE *file)
{
  int cnt = 0;
  char line[100];

  while (fgets (line, sizeof (line), file))
    cnt++;

  rewind (file);
  return cnt;
}

void
read_lines (FILE *file)
{
  int cnt = 0;
  char line[100];

  while (fgets (line, sizeof (line), file))
    {
      char *pline = source_ptr2line (cnt);
      strcpy (pline, line);
      *(pline + strlen (pline) - 1) = 0x00;
      cnt++;
    }
}

void
source_alloc ()
{
  source->lines
      = (_SOURCE_LINE_ *)malloc (source->lines_cnt * sizeof (_SOURCE_LINE_));
  memset (source->lines, 0x00, source->lines_cnt * sizeof (_SOURCE_LINE_));
}

// ----------------------------------------------------------------------- Load
int
source_load (char *filename)
{
  strcpy (source->filename, filename);

  FILE *file = fopen (filename, "r");

  source->lines_cnt = count_lines (file);

  source_alloc ();

  read_lines (file);

  fclose (file);
  return 0;
}

// ----------------------------------------------------------------------- Dump
void
source_dump (int current_line)
{
  for (int cnt = 1; cnt <= source->lines_cnt; cnt++)
    {
      char *pline = source_ptr2line (cnt - 1);
      gotoxy (4 + cnt, 30);
      printf ("%3d [%s %c %-40s %s]", cnt,
              (cnt == current_line) ? COLOR_YELLOW : COLOR_RESET,
              (cnt == current_line) ? '>' : ' ', pline, COLOR_RESET);
    }
}

// -------------------
int
source_count_lines ()
{
  return source->lines_cnt;
}

char *
source_get_line (int row)
{
  return source_ptr2line (row - 1);
}

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
  free (source);
  source = NULL;
}
