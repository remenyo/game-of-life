#if defined (__MINGW64__) || (__MINGW32__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <string.h>

static size_t longest_menu_item_lenght(char **menu_items, int items_n)
{
    size_t max_len = 0;
    for (int i = 0; i < items_n; i++)
    {
        if (strlen(menu_items[i]) > max_len)
            max_len = strlen(menu_items[i]);
    }
    return max_len;
}

static void print_menu_items(WINDOW *menu_win, char **menu_items, int items_n, int selection, int border_size)
{
    for (int i = 0; i < items_n; i++)
    {
        if (i == selection)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, i + border_size / 2, border_size, menu_items[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, i + border_size / 2, border_size, menu_items[i]);
        }
    }
}

int show_menu(char **menu_items, int items_n, int border_size)
{
    int selection = 0;                   // = Kivalasztott elem
    int screen_size_y, screen_size_x, c; // = Terminal magassag, szelesseg, a 'c' valtozo a billentyu bemenet tarolasahoz kell
    getmaxyx(stdscr, screen_size_y, screen_size_x);
    WINDOW *menu_win = newwin(items_n + border_size, longest_menu_item_lenght(menu_items, items_n) + border_size * 2, (screen_size_y - (items_n + border_size)) / 2, (screen_size_x - (longest_menu_item_lenght(menu_items, items_n) + border_size * 2)) / 2);
    keypad(menu_win, TRUE);
    box(menu_win, ACS_VLINE, ACS_HLINE);
    print_menu_items(menu_win, menu_items, items_n, selection, border_size);
    wrefresh(menu_win);
    while ((c = wgetch(menu_win)) != 10)
    {
        switch (c)
        {
        case KEY_UP:
            selection == 0 ? selection = items_n - 1 : selection--;
            break;
        case KEY_DOWN:
            selection == items_n - 1 ? selection = 0 : selection++;
            break;
        default:
            break;
        }
        print_menu_items(menu_win, menu_items, items_n, selection, border_size);
        wrefresh(menu_win);
    }
    wclear(menu_win);
    delwin(menu_win);
    return selection;
}