#include "pattern.h"
#include "debugmalloc.h"

void free_pattern(Pattern *pattern)
{
    free(pattern->name);
    free(pattern->pattern[0]);
    free(pattern->pattern);
    free(pattern);
}