#include <start.h>
#include <termios.h>
#include <unistd.h>

extern int tfinish;

int
getch (void)
{
  struct termios oldt, newt;
  int ch;

  tcgetattr (STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr (STDIN_FILENO, TCSANOW, &newt);
  ch = getchar ();
  tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

void
tinput_run ()
{
  char c;
  while (!tfinish)
    {
      c = getch ();

      if (c == 'q')
        tfinish = 1;

      // printf ("[%c]", c);
    }
}
