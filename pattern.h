#ifndef ELETTER_H
#define ELETTER_H

#include <stdbool.h>
#include <stddef.h>

enum state
{
    state_dead = 0,
    state_alive = 1
};

typedef struct Size
{
    size_t x;
    size_t y;
} Size;

typedef struct Pattern
{
    char *name;  // Az eletter neve
    Size size;   // Az eletter merete
    int **cells; // Az eletter cellai: 1 = elo, 0 = halott
    bool dirty;  // = modositva lett mentes/betoltes ota az eletter.
} Pattern;

void free_pattern(Pattern *pattern);
int **alloc_pattern_cells(size_t y, size_t x);
void next_generation(Pattern *pattern);

#endif