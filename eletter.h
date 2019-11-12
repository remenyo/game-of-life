#ifndef ELETTER_H
#define ELETTER_H

typedef struct Size
{
    int x;
    int y;
} Size;

typedef struct Eletter_data
{
    /* data */
} Eletter_data;

typedef struct Eletter
{
    char *name; // eletter neve
    Size size;  // eletter merete
    bool dirty; // = modositva lett mentes/betoltes ota.
} Eletter;

#endif