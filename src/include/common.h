#ifndef COMMON_H
#define COMMON_H

void to_uppercase (char *str);
char *trim (char *str);
void split_command (char *line, char cmd[4][20]);
void sleep_ms (long milliseconds);
int file_exists (const char *filename);
#endif
