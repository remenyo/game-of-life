#if defined (__MINGW64__) || (__MINGW32__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

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
    size_t screen_size_y, screen_size_x; // = Terminal magassag, szelesseg
    getmaxyx(stdscr, screen_size_y, screen_size_x);
    if (screen_size_y - 2 < pattern->size.y || (screen_size_x + 2) / 2 < pattern->size.x)
    {
        print_status(warning, "The pattern (%dx%d) is bigger than your terminal window. (%dx%d)", pattern->size.y, pattern->size.x, screen_size_y - 2, (screen_size_x + 2) / 2);
        return;
    }
    WINDOW *pattern_win = newwin(pattern->size.y + 2, ((pattern->size.x + 1) * 2), ((screen_size_y - pattern->size.y) - 2) / 2, ((screen_size_x - (pattern->size.x + 1) * 2)) / 2);
    if (pattern_win == NULL)
    {
        print_status(error, "Pattern window allocation failed. (Make the terminal a little bit bigger.)");
        return;
    }
    clear();
    print_status(info, "Loaded.");
    keypad(pattern_win, TRUE);
    box(pattern_win, ACS_VLINE, ACS_HLINE);
    print_pattern(pattern_win, pattern);
    wrefresh(pattern_win);

    int delay_amount = 10; // = 10 tized másodperc
    bool continuous_mode = false;
    int c;
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
            break;
        case KEY_UP:
            if (delay_amount > 1) // = max fps az ncurses miatt 1 tized mp
                delay_amount--;
            print_status(info, "Step frequency: %d FPS", 11 - delay_amount);
            break;
        case KEY_DOWN:
            if (delay_amount < 10) // = min fps = 10/10=1 mp
                delay_amount++;
            print_status(info, "Step frequency: %d FPS", 11 - delay_amount);
            break;
        case 'c':
            continuous_mode = !continuous_mode;
            if (continuous_mode)
                halfdelay(delay_amount);
            else
                cbreak();
            print_status(info, "Continous mode: %s", continuous_mode ? "ON" : "OFF");
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
    // Nem szükséges, de hatékonyabb, ha visszaállítom.
}