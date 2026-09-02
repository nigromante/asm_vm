#include <start.h>

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
