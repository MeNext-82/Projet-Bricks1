#ifndef GUI_FILES_H_
#define GUI_FILES_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_lines_tab(char **lines, int size);
char **read_lines(const char *filename, int *size);

void free_lines_tab(char **lines, int size);

bool write_lines(char **lines, int size, const char *filename);
#endif // GUI_FILES_H_
