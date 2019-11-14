#include <stdbool.h>
#include <stdio.h>

static bool file_valid(FILE *file)
{
    rewind(file);
    if (fscanf(file, "!Name: %*[^\n]s") == 1)
    {
    }
}