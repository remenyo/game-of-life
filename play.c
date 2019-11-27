#include <ncurses.h>

#include "status.h"
#include "pattern.h"

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

void play_pattern(Pattern *pattern)
{
    if ((size_t)LINES - 2 < pattern->size.y || (size_t)COLS / 2 < pattern->size.x)
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
    int c;                 // Billentyű bemenet
    int delay_amount = 10; // = 10 tized másodperc
    bool continuous_mode = false;
    while ((c = wgetch(pattern_win)) != 'x')
    {
        if (continuous_mode)
            halfdelay(delay_amount);

        switch (c)
        {
        case ' ':
            next_generation(pattern);
            print_pattern(pattern_win, pattern);
            wrefresh(pattern_win);
            print_status(info, "Next generation");
            break;
        case KEY_UP:
            if (delay_amount > 1) // = max fps az ncurses miatt 1 tized mp
                delay_amount--;
            break;
        case KEY_DOWN:
            if (delay_amount < 10) // = min fps = 10/10=1 mp
                delay_amount++;
            break;
        case 'c':
            continuous_mode = !continuous_mode;
            if (continuous_mode)
                halfdelay(delay_amount);
            else
                cbreak();
            print_status(info, "Continous mode");
            break;
        default:
            if (continuous_mode)
            {
                ungetch(' '); // Mintha megnyomtam volna a space-t
            }
            break;
        }
    }
    // Ha folyamatos üzemmódban kilép a felhasználó, a halfdelay üzemmód megmarad.
    cbreak();
    // Nem szükséges, de visszaállítom.
}