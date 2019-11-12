#include <stdlib.h>
#include <ncurses.h>
#include "menu.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(0);

    char *menu_items[] = {"Uj eletter", "Eletter megnyitasa", "Lejatszas", "Modositas", "Mentes", "Kilepes"};
    int selection = show_menu(menu_items, 6, 4);

    printw("Selection: %d", selection);

    getch();
    endwin();
}