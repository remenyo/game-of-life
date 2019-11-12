#include <ncurses.h>
#include <string.h>

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

int show_menu(char **menu_items, int items_n, int menu_width, int border_size)
{
    int selection = 0; // = kivalasztott elem
    int rows, cols, c; // = terminal magassag, szelesseg, c a billentyu bemenet tarolasahoz
    getmaxyx(stdscr, rows, cols);
    WINDOW *menu_win = newwin(items_n + border_size, menu_width + border_size * 2, (rows - (items_n + border_size)) / 2, (cols - (menu_width + border_size * 2)) / 2);
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
    wborder(menu_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(menu_win);
    delwin(menu_win);
    return selection;
}