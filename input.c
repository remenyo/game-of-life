#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#include "status.h"
#include "debugmalloc.h"

char *get_input(char *message)
{
    int rows, c; // = Terminal magassag a 'c' valtozo a billentyu bemenet tarolasahoz kell.
    rows = getmaxy(stdscr);
    print_status(info, message);
    attron(COLOR_PAIR(info));
    int x_null = strlen(message) + 2; // +2 = space
    int x = x_null;
    int curs_pos;
    char *input = (char *)malloc(1 * sizeof(char));
    input[0] = 0;
    while ((c = getch()) != 10)
    {
        curs_pos = x - x_null;
        switch (c)
        {
        case KEY_BACKSPACE:
        case 127:
            if (curs_pos == 0)
            {
                mvaddch(rows - 1, x_null + curs_pos - 1, ' ');
                input[curs_pos] = 0;
            }
            if (curs_pos > 0)
            {
                x--;
                mvaddch(rows - 1, x_null + curs_pos - 1, ' ');
                input[curs_pos - 1] = 0;
            }
            break;
        default:
            if (isprint(c))
            {
                mvaddch(rows - 1, x_null + curs_pos, c);
                input = realloc(input, sizeof(char) * curs_pos + 2);
                input[curs_pos] = c;
                input[curs_pos + 1] = 0;
                x++;
            }

            break;
        }
        refresh();
    }
    attroff(COLOR_PAIR(info));
    return input;
}