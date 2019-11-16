#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "status.h"
#include "pattern.h"
#include "debugmalloc.h"

static const char namestring[] = "!Name: ";

static bool file_valid(FILE *file)
{
    rewind(file);
    char c;
    for (int i = 0; i < (int)strlen(namestring); i++)
    {
        c = fgetc(file);
        if (c != namestring[i])
        {
            //Ha nem egyezik meg karakterre pontosan a beolvasott szöveg a namestring-gel, hibás a formátum.
            print_status(error, "Error in the name field of your file.");
            return 0;
        }
    }
    while (c != '\n') // Átugorjuk az első sor maradék részét
    {
        c = fgetc(file);
    }
    c = fgetc(file);
    while (c == '!') // Átugorjuk az összes olyan sort, ami '!' jellel kezdődik
    {
        while (c != '\n')
        {
            c = fgetc(file);
        }
        c = fgetc(file);
    }
    bool pattern_exists = false; // Lehet, nincs is pattern...
    while (c != EOF)             // pattern ellenőrzése (a felkiátó jeles sorok után előfordulhat üres sor, nem okoz hibát.)
    {
        if ((c != '.') && (c != 'O') && (c != '\n'))
        {
            if (c == '.' || c == 'O')
            {
                pattern_exists = true; // van pattern!
            }
            print_status(error, "A not valid character was found in your pattern.");
            return false;
        }
        c = fgetc(file);
    }
    if (!pattern_exists)
    {
        print_status(error, "No pattern found in your file");
        return false;
    }

    return true;
}

Pattern *load_file(char *filename) // Beolvas egy fájlt, és ha helyes a formázás, megépít egy élettér struktúrát, amit visszaad.
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        print_status(error, "Failed to open file.");
        return NULL;
    }
    if (!file_valid(file))
    {
        // A státuszokat részletesebben kezeli a file_valid függvény
        return NULL;
    }
    rewind(file); // Mert a file_valid nem rewind-ol, miután végzett.
    char c;

    // Élettér struktúra létrehozása
    Pattern *pattern = (Pattern *)malloc(sizeof(Pattern));

    for (int i = 0; i < strlen(namestring); i++)
    {
        c = fgetc(file);
    }
    fflush(file);
    unsigned long name_start_pos = ftell(file);
    int name_lenght = 1; // Azért nem 0, mert a végén a \n karakter is kell a name mértetéhez.
    while (c != '\n')    // Name string hossza
    {
        name_lenght++;
        c = fgetc(file);
    }

    fflush(file);
    unsigned long pattern_start_pos = ftell(file);
    pattern->name = (char *)malloc(sizeof(char) * name_lenght);
    fseek(file, name_start_pos, SEEK_SET);
    fgets(pattern->name, name_lenght, file); // Név beolvasása

    // Élettér méreteinek megmérése

    // Oszlopok száma:
    fseek(file, pattern_start_pos, SEEK_SET);
    pattern->size.x = 0;
    pattern->size.y = 0;
    while (c != '\n')
    {
        pattern->size.x++;
        c = fgetc(file);
    }

    // Sorok száma:
    fseek(file, pattern_start_pos, SEEK_SET);
    while (c != EOF)
    {
        bool line_contains_pattern = false;
        while (c != '\n')
        {
            if (!line_contains_pattern && (c == '.' || c == 'O')) // ha van a sorban élettér adat
            {
                line_contains_pattern = true;
                pattern->size.y++;
            }
            c = fgetc(file);
        }
    }

    // Az élettérhez szükséges memória lefoglalása (calloc-al, mert lehet,
    //  hogy az első sor hoszabb volt mint a többi, így az az első sor alatt lévő celláknak alapértelmezetten 0-nak, halottnak kell lennie.)
    pattern->pattern = (int **)calloc(pattern->size.y, sizeof(int *));
    pattern->pattern[0] = (int *)calloc(pattern->size.y * pattern->size.x, sizeof(int));
    for (int i = 1; i < pattern->size.y; i++)
    {
        pattern->pattern[i] = pattern->pattern[0] + i * pattern->size.x;
    }

    // Élettér feltöltése

    fseek(file, pattern_start_pos, SEEK_SET);
    int y = 0;
    int x = 0;
    c = fgetc(file);
    while (c != EOF)
    {
        while (c != '\n')
        {
            pattern->pattern[y][x] = (c == '.' ? state_dead : state_alive);
            x++;
            c = fgetc(file);
        }
        x = 0;
        y++;
        c = fgetc(file);
    }
    pattern->dirty = false; // Mivel egy mentett file-t olvastunk be, az aktuális állapot mentve van.

    fclose(file);
    return pattern;
}