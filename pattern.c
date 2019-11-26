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
    for (size_t i = 1; i < y; i++)
    {
        cells[i] = cells[0] + i * x;
    }
    return cells;
}

void next_generation(Pattern *pattern)
{
    // következő generáció lefoglalása kerettel, a számoláshoz
    int **temp_cells = alloc_pattern_cells(pattern->size.y + 2, pattern->size.x + 2);

    if (temp_cells != NULL)
    {
        // élettér átmásolása
        for (size_t y = 0; y < pattern->size.y; y++)
        {
            for (size_t x = 0; x < pattern->size.x; x++)
            {
                temp_cells[y + 1][x + 1] = pattern->cells[y][x];
            }
        }

        pattern->dirty = true;
        // számítás
        for (size_t y = 1; y < pattern->size.y + 1; y++)
        {
            for (size_t x = 1; x < pattern->size.x + 1; x++)
            {
                int neighbor_count = 0;
                for (int y_offset = -1; y_offset < 2; y_offset++)
                {
                    for (int x_offset = -1; x_offset < 2; x_offset++)
                    {
                        neighbor_count += temp_cells[y + y_offset][x + x_offset] == state_alive;
                    }
                }
                if (temp_cells[y][x] == state_alive)
                {
                    neighbor_count--; // ugyanis beleszámoltuk önmagunkat a szomszédok közé
                }
                if (neighbor_count == 2 || neighbor_count == 3)
                {
                    if (neighbor_count == 3)
                    {
                        pattern->cells[y - 1][x - 1] = state_alive;
                    }
                }
                else
                {
                    pattern->cells[y - 1][x - 1] = state_dead;
                }
            }
        }
        free(temp_cells[0]);
        free(temp_cells);
    }
}