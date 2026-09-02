#include <start.h>

#include <sys/stat.h>

typedef struct
{
  char global[20];
  int row_start;
  int rows;
} CODE_FILE_HEADER;

void
eval_define_fn (char *line, void *handler)
{
  fwrite (line, 1, strlen (line), (FILE *)handler);
}

// ---------------------------------------------------------------------- Save
void
code_save (char *filename)
{
  CODE_FILE_HEADER hdr;

  memset (&hdr, 0x00, sizeof (CODE_FILE_HEADER));

  strcpy (hdr.global, preproc->global ());
  hdr.row_start = code->get_row_by_label (hdr.global);
  hdr.rows = code->lines_cnt;

  FILE *fp = fopen (filename, "wb");
  fwrite (&hdr, 1, sizeof (CODE_FILE_HEADER), fp);
  fwrite (code->lines, 1, code->lines_cnt * sizeof (_CODE_LINE_), fp);

  preproc->eval_defines (eval_define_fn, fp);

  fclose (fp);
}

// ---------------------------------------------------------------------- Read
int
code_read (char *filename, void (*callback) (char *))
{
  CODE_FILE_HEADER hdr;
  struct stat st;
  stat (filename, &st);

  FILE *fp = fopen (filename, "rb");
  fread (&hdr, 1, sizeof (CODE_FILE_HEADER), fp);
  code->global_set (hdr.global);
  code->lines_cnt = hdr.rows;

  code->lines = (_CODE_LINE_ *)malloc (code->lines_cnt * sizeof (_CODE_LINE_));
  memset (code->lines, 0x00, code->lines_cnt * sizeof (_CODE_LINE_));

  fread (code->lines, 1, code->lines_cnt * sizeof (_CODE_LINE_), fp);

  if (callback)
    {
      char line[100];
      while (NULL != fgets (line, sizeof (line), fp))
        {
          callback (line);
        }
    }

  fclose (fp);
  return (hdr.row_start);
}

// ------------------------------------------------------------ Code File Ends
