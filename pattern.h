#ifndef ELETTER_H
#define ELETTER_H

enum state
{
    state_dead = 0,
    state_alive = 1
};

typedef struct Size
{
    int x;
    int y;
} Size;

typedef struct Pattern
{
    char *name;    // Az eletter neve
    Size size;     // Az eletter merete
    int **pattern; // Az eletter cellai: 1 = elo, 0 = halott
    bool dirty;    // = modositva lett mentes/betoltes ota az eletter.
} Pattern;

void free_pattern(Pattern *pattern);

#endif