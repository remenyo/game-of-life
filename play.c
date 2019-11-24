#include <ncurses.h>

#include "status.h"
#include "pattern.h"

static void print_pattern(WINDOW *pattern_win, Pattern *pattern)
{
    for (int y = 0; y < pattern->size.y; y++)
    {
        for (int x = 0; x < pattern->size.x; x++)
        {
            if (pattern->cells[y][x] == state_alive)
            {
                wattron(pattern_win, A_STANDOUT);
            }
            mvwprintw(pattern_win, y + 1, x * 2 + 1, "  ");
            wattroff(pattern_win, A_STANDOUT);
        }
        waddch(pattern_win, ACS_VLINE);
    }
    wrefresh(pattern_win);
}

void play_pattern(Pattern *pattern)
{
    if (LINES - 2 < pattern->size.y || COLS / 2 < pattern->size.x)
    {
        print_status(warning, "The pattern is bigger than your terminal window.");
        return;
    }
    WINDOW *pattern_win = newwin(pattern->size.y + 2, ((pattern->size.x + 1) * 2), ((LINES - pattern->size.y) - 2) / 2, ((COLS - (pattern->size.x + 1) * 2)) / 2);
    if (pattern_win == NULL)
    {
        print_status(error, "Pattern window allocation failed.");
        return;
    }
    clear();
    print_status(info, "Loaded.");
    keypad(pattern_win, TRUE);
    box(pattern_win, ACS_VLINE, ACS_HLINE);
    print_pattern(pattern_win, pattern);
    wrefresh(pattern_win);
    int c;
    while ((c = wgetch(pattern_win)) != 'x')
    {
        switch (c)
        {
        case ' ':
            print_status(info, "Space pressed -> next generation");
            break;
        default:
            break;
        }
    }
}