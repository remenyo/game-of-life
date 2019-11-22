#include "pattern.h"
#include "debugmalloc.h"

void free_pattern(Pattern *pattern)
{
    free(pattern->name);
    free(pattern->cells[0]);
    free(pattern->cells);
    free(pattern);
}