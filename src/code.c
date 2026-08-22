#define CODE_C

#include <start.h>
#include <sys/stat.h>

// -------------------------------------------------------------------- Global
void
code_global_load ()
{
  strcpy (code->global_label, CODE_LBL_START);
  int row_count = source->count_lines ();

  for (int row = 1; row <= row_count; row++)
    {

      char *line = source->get_line (row);
      char *p = strstr (line, CODE_LBL_GLOBAL);
      if (p)
        {
          p = p + strlen (CODE_LBL_GLOBAL);
          strcpy (code->global_label, p);
          trim (code->global_label);
          break;
        }
    }
}

char *
code_global_get ()
{
  return code->global_label;
}

// --------------------------------------------------------------------- Lines
int
code_line_check (char *line)
{
  char sline[100];
  memset (sline, 0x00, sizeof (sline));
  strcpy (sline, line);
  trim (sline);
  if (strlen (sline) == 0)
    return 0;
  if (*sline == ';')
    return 0;
  if (strncmp (sline, CODE_LBL_GLOBAL, strlen (CODE_LBL_GLOBAL)) == 0)
    return 0;
  return 1;
}

int
code_line_count ()
{
  int cnt = 0;
  int row_count = source->count_lines ();
  for (int row = 1; row <= row_count; row++)
    if (code_line_check (source->get_line (row)))
      cnt++;

  return cnt;
}

void
code_line_param (char *dest, char *src)
{
  if (*src != '_') // exclude labels
    to_uppercase (src);
  strcpy (dest, src);
}

void
code_line_read ()
{
  int cnt = 0;
  int row_count = source->count_lines ();
  for (int row = 1; row <= row_count; row++)
    {
      char *linea = source->get_line (row);
      if (code_line_check (linea))
        {
          _CODE_LINE_ *line = (_CODE_LINE_ *)((char *)code->lines
                                              + cnt * sizeof (_CODE_LINE_));

          char linea_buffer[100];
          strcpy (linea_buffer, linea);

          char *p = strstr (linea_buffer, ";");
          if (p)
            *p = 0x00;

          trim (linea_buffer);

          line->reference = row;

          if (*(linea_buffer + strlen (linea_buffer) - 1) == ':')
            {
              strcpy (line->par1, linea_buffer);
              *(line->par1 + strlen (line->par1) - 1) = 0x00;
              line->type = 0;
              line->code_cmd = NT_NOP;
              code->labels_cnt++;
            }
          else
            {
              char cmd[4][20];
              split_command (linea_buffer, cmd);
              line->code_cmd = nt_get_code (cmd[0]);
              code_line_param (line->par1, cmd[1]);
              code_line_param (line->par2, cmd[2]);
              line->type = 1;
            }
          cnt++;
        }
    }
}

void
code_line_load ()
{
  code->lines_cnt = code_line_count ();

  code->lines = (_CODE_LINE_ *)malloc (code->lines_cnt * sizeof (_CODE_LINE_));
  memset (code->lines, 0x00, code->lines_cnt * sizeof (_CODE_LINE_));

  code_line_read ();
}

_CODE_LINE_ *
code_line_get (int row_number)
{
  if (row_number < 1 || row_number > code->lines_cnt)
    {
      printf ("\nNro de linea fuera de rango");
      return NULL;
    }
  return (_CODE_LINE_ *)((char *)code->lines
                         + (row_number - 1) * sizeof (_CODE_LINE_));
}

// -------------------------------------------------------------------- Labels

void
code_label_read ()
{
  int cnt = 0;
  int row_count = code_line_count ();
  for (int row = 1; row <= row_count; row++)
    {
      _CODE_LINE_ *line = (_CODE_LINE_ *)((char *)code->lines
                                          + (row - 1) * sizeof (_CODE_LINE_));
      if (line->type == 0)
        {
          _CODE_LABEL_ *label
              = (_CODE_LABEL_ *)((char *)code->labels
                                 + cnt * sizeof (_CODE_LABEL_));

          label->reference = row;
          strcpy (label->label, line->par1);
          cnt++;
        }
    }
}

void
code_label_load ()
{

  code->labels
      = (_CODE_LABEL_ *)malloc (code->labels_cnt * sizeof (_CODE_LABEL_));
  memset (code->labels, 0x00, code->labels_cnt * sizeof (_CODE_LABEL_));

  code_label_read ();
}

int
code_label_get (char *labelname)
{
  for (int row = 1; row <= code->labels_cnt; row++)
    {
      _CODE_LABEL_ *label
          = (_CODE_LABEL_ *)((char *)code->labels
                             + (row - 1) * sizeof (_CODE_LABEL_));
      if (strcmp (labelname, label->label) == 0)
        {
          return label->reference;
        }
    }
  return -1;
}

// ----------------------------------------------------------------- Post Load
void
code_post_load ()
{
  int row_count = code_line_count ();
  for (int row = 1; row <= row_count; row++)
    {
      _CODE_LINE_ *line = (_CODE_LINE_ *)((char *)code->lines
                                          + (row - 1) * sizeof (_CODE_LINE_));
      if (line->code_cmd >= 0x0200 && line->code_cmd < 0x0300)
        {
          line->jmp_label = code_label_get (line->par1);
        }
    }
}

// --------------------------------------------------------------------- Loads
void
code_load ()
{
  code_global_load ();
  code_line_load ();
  code_label_load ();

  code_post_load ();
}

// --------------------------------------------------------------------- Dumps
void
code_dump_source ()
{
  _CODE_LINE_ *line
      = (_CODE_LINE_ *)((char *)code->lines
                        + (IP_Get () - 1) * sizeof (_CODE_LINE_));
  gotoxy (3, 40);
  source->dump (line->reference);
}

void
code_dump_full ()
{
  int current_line = IP_Get ();
  int src_current_line = 0;
  int _alto = 30, _start = 1, _end = code->lines_cnt;
  int _medio = _alto / 2;
  char buffer[100];

  if (_end > _alto)
    {
      if (current_line + _medio > _end)
        {
          _start = _end - _alto;
        }
      else
        {
          if (current_line > _medio)
            {
              _start = current_line - _medio;
            }
          _end = _start + _alto;
        }
    }

  for (int cnt = _start; cnt <= _end; cnt++)
    {
      _CODE_LINE_ *line = (_CODE_LINE_ *)((char *)code->lines
                                          + (cnt - 1) * sizeof (_CODE_LINE_));
      gotoxy (5 + cnt - _start, 42);

      printf ("%s", (cnt == current_line) ? COLOR_YELLOW_HIGH : COLOR_RESET);

      if (line->type == 0)
        sprintf (buffer, "%03d %s", cnt, line->par1);
      else
        {
          if (line->code_cmd >= NT_JMP && line->code_cmd < NT_JXX)
            {
              if (line->code_cmd == NT_RET)
                {
                  sprintf (buffer, "%03d   %04x ", cnt, line->code_cmd);
                }
              else if (line->jmp_label > 0)
                {
                  sprintf (buffer, "%03d   %04x %03d %s", cnt, line->code_cmd,
                           line->jmp_label, COLOR_RESET);
                }
            }
          else
            {
              sprintf (buffer, "%03d   %04x %s %s", cnt, line->code_cmd,
                       line->par1, line->par2);
            }
        }
      printf ("%-30s", buffer);
      if (cnt == current_line)
        src_current_line = line->reference;
    }
  source->dump (src_current_line);
}

void (*code_dump_fn) ();

void
code_dump ()
{
  code_dump_fn ();
}

void
code_dump_type (int type)
{
  if (type == 0)
    code_dump_fn = code_dump_source;
  else
    code_dump_fn = code_dump_full;
}

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

  strcpy (hdr.global, code->global_label);
  hdr.row = code->get_row_by_label (code->get_global ());

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
  strcpy (code->global_label, hdr.global);
  IP_Set (hdr.row);
  fread (code->lines, 1, code->lines_cnt * sizeof (_CODE_LINE_), fp);
  fclose (fp);
}

// ------------------------------------------------------------------ Instance
void
code_init ()
{
  code = (_CODE_ *)malloc (sizeof (_CODE_));
  memset (code, 0x00, sizeof (_CODE_));

  code->load = code_load;
  code->dump = code_dump;
  code->dump_type = code_dump_type;
  code->save = code_save;
  code->read = code_read;
  code->get_global = code_global_get;
  code->get_line = code_line_get;
  code->get_row_by_label = code_label_get;
}

void
code_release ()
{
  free (code->lines);
  free (code->labels);
  free (code);
  code = NULL;
}

// ----------------------------------------------------------------- Code Ends
