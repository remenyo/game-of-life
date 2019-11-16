#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "menu.h"
#include "file.h"
#include "pattern.h"
#include "status.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_status();

    int menu_items_n = 6;
    char *menu_items[] = {"New pattern", "Load pattern", "Play", "Edit", "Save", "Exit"};
    while (true)
    {
        int selection = show_menu(menu_items, menu_items_n, 2);
        switch (selection)
        {
        case 0: // New pattern
            /* code */
            break;
        case 1: // Load pattern
            /* code */
            break;
        case 2: // Play
            /* code */
            break;
        case 3: // Edit
            /* code */
            break;
        case 4: // Save
            /* code */
            break;
        case 5: // Exit
            endwin();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
}