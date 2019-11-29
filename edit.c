#include <ncurses.h>

#include "pattern.h"
#include "status.h"

static void print_pattern(WINDOW *pattern_win, Pattern *pattern)
{
    for (size_t y = 0; y < pattern->size.y; y++)
    {
        for (size_t x = 0; x < pattern->size.x; x++)
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

void edit_pattern(Pattern *pattern)
{
    size_t screen_size_y, screen_size_x; // = Terminal magassag, szelesseg
    getmaxyx(stdscr, screen_size_y, screen_size_x);
    if (screen_size_y - 2 < pattern->size.y || screen_size_x / 2 < pattern->size.x)
    {
        print_status(warning, "The pattern is bigger than your terminal window.");
        return;
    }
    WINDOW *pattern_win = newwin(pattern->size.y + 2, ((pattern->size.x + 1) * 2), ((screen_size_y - pattern->size.y) - 2) / 2, ((screen_size_x - (pattern->size.x + 1) * 2)) / 2);
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
    size_t mouse_pos_y, mouse_pos_x;
    MEVENT event;
    while ((c = wgetch(stdscr)) != 'x')
    {
        switch (c)
        {
        case KEY_MOUSE:
            if (getmouse(&event) == OK)
            {
                mouse_pos_y = event.y - ((screen_size_y - pattern->size.y) - 2) / 2 - 1;
                mouse_pos_x = (event.x - ((screen_size_x - (pattern->size.x + 1) * 2)) / 2 + 1) / 2 - 1;
            }
            if ((event.bstate & (BUTTON1_PRESSED)) && (mouse_pos_y < pattern->size.y) && (mouse_pos_x < pattern->size.x))
            {
                flip_cell(pattern, mouse_pos_y, mouse_pos_x);
            }
            print_pattern(pattern_win, pattern);
            wrefresh(pattern_win);
            break;
        default:
            break;
        }
    }
}