#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void
to_uppercase (char *str)
{
  // char *p = str;
  // printf ("\n [%s]  -  ", str);
  while (*str)
    {
      // printf ("%02x ", *str);
      *str = (char)toupper ((unsigned char)*str);
      str++;
    }
  // printf ("  -  [%s]", p);
}

char *
trim (char *str)
{
  if (str == NULL)
    return str;

  // Trim leading space
  char *start = str;
  while (isspace ((unsigned char)*start))
    {
      start++;
    }

  // If the string is all whitespace
  if (*start == 0)
    {
      *str = '\0';
      return str;
    }

  // Trim trailing space
  char *end = start + strlen (start) - 1;
  while (end > start && isspace ((unsigned char)*end))
    {
      end--;
    }
  *(end + 1) = '\0';

  // Shift trimmed string to the beginning if needed
  if (start != str)
    {
      memmove (str, start, (end - start) + 2);
    }
  return str;
}

void
split_command (char *line, char cmd[4][20])
{
  char *p = line;
  int f = 0, c = 0;
  memset ((char *)cmd, 0x00, 4 * 20);
  while (*p)
    {
      if (*p == ' ')
        {
          c = 0;
          f++;
          p++;
        }
      cmd[f][c++] = *p++;
    }
  to_uppercase (cmd[0]);
}

void
sleep_ms (long milliseconds)
{
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000; // Extract full seconds
  ts.tv_nsec
      = (milliseconds % 1000) * 1000000L; // Convert remainder to nanoseconds
  nanosleep (&ts, NULL);
}

int
file_exists (const char *filename)
{
  struct stat buffer;
  return (stat (filename, &buffer) == 0); // Returns true if file exists
}
