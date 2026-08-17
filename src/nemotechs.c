#define NEMOTECHS_C

#include <start.h>

int
nt_get_code (char *code)
{
  int n = sizeof (nm_data) / sizeof (_NM_DATA_);
  for (int i = 0; i < n; i++)
    {
      if (strcmp (code, nm_data[i].name) == 0)
        {
          return nm_data[i].code;
        }
    }
  return 0;
}
