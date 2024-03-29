#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "pattern.h"
#include "status.h"
#include "input.h"
#include "debugmalloc.h"

void free_pattern(Pattern *pattern)
{
    free(pattern->name);
    free(pattern->cells[0]);
    free(pattern->cells);
    free(pattern);
}

bool **alloc_pattern_cells(size_t y, size_t x)
{
    // Az élettérhez szükséges memória lefoglalása (calloc-al, mert lehet,
    //  hogy az első sor hoszabb volt mint a többi, így az az első sor alatt lévő celláknak alapértelmezetten 0-nak, halottnak kell lennie.)
    bool **cells = (bool **)calloc(y, sizeof(bool *));
    if (cells == NULL)
    {
        return NULL;
    }
    cells[0] = (bool *)calloc(y * x, sizeof(bool));
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
    bool **temp_cells = alloc_pattern_cells(pattern->size.y + 2, pattern->size.x + 2);

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
                        neighbor_count += temp_cells[y + y_offset][x + x_offset];
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

void flip_cell(Pattern *pattern, int y, int x)
{
    pattern->cells[y][x] = !pattern->cells[y][x];
    pattern->dirty = true;
}

Pattern *new_empty_pattern()
{
    Pattern *pattern = malloc(sizeof(Pattern));
    Size size;
    pattern->name = get_input("Name of pattern:");
    char *width = get_input("Width of pattern:");
    if ((size.x = strtoul(width, NULL, 0)) == 0)
    {
        print_status(error, "Invalid width. (%s)", width);
        free(width);
        free(pattern->name);
        free(pattern);
        return NULL;
    }
    char *height = get_input("Height of pattern:");
    if ((size.y = strtoul(height, NULL, 0)) == 0)
    {
        print_status(error, "Invalid height. (%s)", height);
        free(width);
        free(height);
        free(pattern->name);
        free(pattern);
        return NULL;
    }
    free(width);
    free(height);

    pattern->size.x = size.x;
    pattern->size.y = size.y;
    pattern->cells = alloc_pattern_cells(size.y, size.x);
    if (pattern->cells == NULL)
    {
        clear(); // Debugmalloc is szól hogy nem sikerült, de köszönöm, inkább kiírom én.
        print_status(error, "Pattern allocation failed");
        free(pattern->name);
        free(pattern);
        return NULL;
    }
    pattern->dirty = false;
    print_status(successful, "Pattern (%s) created succesfully", pattern->name);
    return pattern;
}