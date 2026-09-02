#ifndef CODE_FILE_H
#define CODE_FILE_H

void code_save (char *filename);
int code_read (char *filename, void (*callback) (char *));

#endif
