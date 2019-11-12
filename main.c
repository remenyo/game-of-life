#include <locale.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include "menu.h"

int main()
{
    setlocale(LC_ALL, "hu_HU.utf8");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(0);

    int menu_items_n = 6;
    char *menu_items[] = {"Új élettér", "Élettér megnyitása", "Lejátszás", "Módosítás", "Mentés", "Kilépés"};
    while (true)
    {
        int selection = show_menu(menu_items, menu_items_n, 18, 2);
        switch (selection)
        {
        case 0: // Uj eletter
            /* code */
            break;
        case 1: // Eletter megnyitasa
            /* code */
            break;
        case 2: // Lejatszas
            /* code */
            break;
        case 3: // Modositas
            /* code */
            break;
        case 4: // Mentes
            /* code */
            break;
        case 5: // Kilepes
            endwin();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
}