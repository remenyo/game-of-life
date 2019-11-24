#include "pattern.h"
#include "debugmalloc.h"

void free_pattern(Pattern *pattern)
{
    free(pattern->name);
    free(pattern->cells[0]);
    free(pattern->cells);
    free(pattern);
}

int **alloc_pattern_cells(size_t y, size_t x)
{
    // Az élettérhez szükséges memória lefoglalása (calloc-al, mert lehet,
    //  hogy az első sor hoszabb volt mint a többi, így az az első sor alatt lévő celláknak alapértelmezetten 0-nak, halottnak kell lennie.)
    int **cells = (int **)calloc(y, sizeof(int *));
    if (cells == NULL)
    {
        return NULL;
    }
    cells[0] = (int *)calloc(y * x, sizeof(int));
    if (cells[0] == NULL)
    {
        return NULL;
    }
    for (int i = 1; i < y; i++)
    {
        cells[i] = cells[0] + i * x;
    }
    return cells;
}