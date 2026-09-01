#include <start.h>

#include <sys/stat.h>

// ---------------------------------------------------------------------- Save
void
code_save (char *filename)
{
  struct header
  {
    char global[20];
    int row;
    char fill[76];
  } hdr;

  memset (&hdr, 0x00, sizeof (struct header));

  strcpy (hdr.global, code->global_get ());
  hdr.row = code->get_row_by_label (hdr.global);

  FILE *fp = fopen (filename, "wb");
  fwrite (&hdr, 1, sizeof (struct header), fp);
  fwrite (code->lines, 1, code->lines_cnt * sizeof (_CODE_LINE_), fp);
  fclose (fp);
}

// ---------------------------------------------------------------------- Read
void
code_read (char *filename)
{
  struct stat st;
  struct header
  {
    char global[20];
    int row;
    char fill[76];
  } hdr;
  stat (filename, &st);

  code->lines_cnt = (st.st_size - sizeof (hdr)) / sizeof (_CODE_LINE_);

  code->lines = (_CODE_LINE_ *)malloc (code->lines_cnt * sizeof (_CODE_LINE_));
  memset (code->lines, 0x00, code->lines_cnt * sizeof (_CODE_LINE_));

  FILE *fp = fopen (filename, "rb");
  fread (&hdr, 1, sizeof (struct header), fp);
  code->global_set (hdr.global);
  IP_Set (hdr.row);
  fread (code->lines, 1, code->lines_cnt * sizeof (_CODE_LINE_), fp);
  fclose (fp);
}

// ------------------------------------------------------------ Code File Ends
