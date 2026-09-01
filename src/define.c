#include <start.h>

void
callDefine (char *line)
{

  char *cmd, *varname, *varvalue;

  cmd = line;

  varname = strstr (line, " ");
  if (varname)
    *varname = 0x00;
  varname++;

  varvalue = strstr (varname, " ");
  if (varvalue)
    *varvalue = 0x00;
  varvalue++;

  if (strcmp (cmd, "db") == 0)
    {
      mem_declare (varname, 2, strlen (varvalue));
      mem_store_db (varname, varvalue, strlen (varvalue));
    }
  if (strcmp (cmd, "dw") == 0)
    {
      mem_declare (varname, 1, sizeof (int));
      mem_store_dw (varname, varvalue);
    }
}

int
isDefine (char *line)
{
  char sline[100];
  strcpy (sline, line);
  char *p = strstr (sline, " ");
  if (p)
    *p = 0x00;

  if (strcmp (sline, "db") == 0 || strcmp (sline, "dw") == 0)
    {
      return 1;
    }

  return 0;
}
