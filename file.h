#ifndef FILE_H
#define FILE_H
#include "pattern.h"

Pattern *load_file(char *filename);
void free_pattern(Pattern *pattern);

#endif