#define CODE_C

#include <start.h>

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
              strcpy (line->label, linea_buffer);
              *(line->label + strlen (line->label) - 1) = 0x00;

              code->labels_cnt++;
            }
          else
            {
              char cmd[4][20];
              split_command (linea_buffer, cmd);
              strcpy (line->cmd, cmd[0]);
              strcpy (line->par1, cmd[1]);
              strcpy (line->par2, cmd[2]);
              strcpy (line->par3, cmd[3]);
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
      if (strlen (line->label) > 0)
        {
          _CODE_LABEL_ *label
              = (_CODE_LABEL_ *)((char *)code->labels
                                 + cnt * sizeof (_CODE_LABEL_));

          label->reference = row;
          strcpy (label->label, line->label);
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
      if (strcmp ("CALL", line->cmd) == 0 || strcmp ("JMP", line->cmd) == 0
          || strcmp ("JZ", line->cmd) == 0 || strcmp ("JNZ", line->cmd) == 0)
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
  gotoxy (3, 1);
  source->dump (line->reference);
}

void
code_dump ()
{
  int current_line = IP_Get ();
  int src_current_line = 0;
  // printf ("\n global label : [%s]", code->get_global ());
  for (int cnt = 1; cnt <= code->lines_cnt; cnt++)
    {
      _CODE_LINE_ *line = (_CODE_LINE_ *)((char *)code->lines
                                          + (cnt - 1) * sizeof (_CODE_LINE_));
      gotoxy (4 + cnt, 1);
      if (strlen (line->label))
        printf ("%s %3d %s %s",
                (cnt == current_line) ? COLOR_YELLOW : COLOR_RESET, cnt,
                line->label, COLOR_RESET);
      else
        printf ("%s %3d\t%s %s %s %s %s",
                (cnt == current_line) ? COLOR_YELLOW : COLOR_RESET, cnt,
                line->cmd, line->par1, line->par2, line->par3, COLOR_RESET);
      /*
      printf ("%3d [ %3d ] [%-20s] [%s %c %-20s %-20s %-20s %-20s %s] [ %2d ]",
              cnt, line->reference, line->label,
              (cnt == current_line) ? COLOR_YELLOW : COLOR_RESET,
              (cnt == current_line) ? '>' : ' ', line->cmd, line->par1,
              line->par2, line->par3, COLOR_RESET, line->jmp_label);
      */
      if (cnt == current_line)
        src_current_line = line->reference;
    }
  /*
  printf ("\n\n");
  for (int cnt = 1; cnt <= code->labels_cnt; cnt++)
    {
      _CODE_LABEL_ *line
          = (_CODE_LABEL_ *)((char *)code->labels
                             + (cnt - 1) * sizeof (_CODE_LABEL_));
      printf ("\n%3d [ %3d ] [%-20s] ", cnt, line->reference, line->label);
    }
    */
  source->dump (src_current_line);
}

// ------------------------------------------------------------------ Instance
void
code_init ()
{
  code = (_CODE_ *)malloc (sizeof (_CODE_));
  memset (code, 0x00, sizeof (_CODE_));

  code->load = code_load;
  code->dump = code_dump;
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
