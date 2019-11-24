#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "status.h"
#include "input.h"
#include "pattern.h"
#include "debugmalloc.h"

static const char namestring[] = "!Name: ";

static bool file_valid(FILE *file)
{
    rewind(file);
    char c;
    for (size_t i = 0; i < strlen(namestring); i++)
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
            print_status(warning, "A not valid character was found in your pattern.");
            return false;
        }
        if (!pattern_exists && (c == '.' || c == 'O'))
        {
            pattern_exists = true; // van pattern!
        }
        c = fgetc(file);
    }
    if (!pattern_exists)
    {
        print_status(warning, "No pattern found in your file.");
        return false;
    }

    return true;
}

struct Pattern *load_file() // Beolvas egy fájlt, és ha helyes a formázás, megépít egy élettér struktúrát, amit visszaad.
{
    char *filename = get_input("Name of file:");
    FILE *file = fopen(filename, "rt");
    free(filename);
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

    for (size_t i = 0; i < strlen(namestring); i++)
    {
        c = fgetc(file);
    }
    fflush(file);
    unsigned long name_start_pos = ftell(file);
    int name_lenght = 0;
    while (c != '\n') // Name string hossza
    {
        name_lenght++;
        c = fgetc(file);
    }
    while (c != '.' && c != 'O')
    {
        c = fgetc(file);
    }

    fflush(file);
    unsigned long pattern_start_pos = ftell(file) - 1;
    pattern->name = (char *)malloc(sizeof(char) * name_lenght);
    fseek(file, name_start_pos, SEEK_SET);
    fgets(pattern->name, name_lenght, file); // Név beolvasása

    // Élettér méreteinek megmérése

    // Oszlopok száma:
    fseek(file, pattern_start_pos, SEEK_SET);
    pattern->size.x = 0;
    pattern->size.y = 0;
    c = fgetc(file);
    while (c != '\n')
    {
        pattern->size.x++;
        c = fgetc(file);
    }

    // Sorok száma:
    fseek(file, pattern_start_pos, SEEK_SET);
    c = fgetc(file);
    while (c != EOF)
    {
        bool line_contains_pattern = false;
        while (c != '\n' && c != EOF)
        {
            if (!line_contains_pattern && (c == '.' || c == 'O')) // ha van a sorban élettér adat
            {
                line_contains_pattern = true;
                pattern->size.y++;
            }
            c = fgetc(file);
        }
        c = fgetc(file);
    }

    pattern->cells = alloc_pattern_cells(pattern->size.y, pattern->size.x);

    if (pattern->cells == NULL)
    {
        print_status(error, "Memory allocation failed.");
        return NULL;
    }

    // Élettér feltöltése

    fseek(file, pattern_start_pos, SEEK_SET);
    int y = 0;
    int x = 0;
    c = fgetc(file);
    while (c != EOF)
    {
        while (c != '\n' && c != EOF)
        {
            pattern->cells[y][x] = (c == '.' ? state_dead : state_alive);
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

void save_pattern(Pattern *pattern)
{
    char *name = get_input("Name of pattern:");
    char *filename = calloc(strlen(name), sizeof(char) + 4); // ==name + ".txt" + \0
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *f = fopen(filename, "wt");
    if (f == NULL)
    {
        print_status(error, "Failed to make file.");
    }
    else
    {
        free(pattern->name);
        pattern->name = (char *)calloc((strlen(name) + 1), sizeof(char));
        strcpy(pattern->name, name);
        fprintf(f, "%s%s\n!", namestring, pattern->name);
        for (int y = 0; y < pattern->size.y; y++)
        {
            fputc('\n', f);
            for (int x = 0; x < pattern->size.x; x++)
            {
                fprintf(f, "%c", pattern->cells[y][x] == state_alive ? 'O' : '.');
            }
        }
        fclose(f);
        print_status(successful, "Pattern saved successfully!");
        pattern->dirty = false;
    }
    free(name);
    free(filename);
}