#ifndef FILE_H
#define FILE_H
#include "pattern.h"

Pattern *load_file();
void free_pattern(Pattern *pattern);
void save_pattern(Pattern *pattern);

#endif