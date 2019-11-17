#include <ncurses.h>
#include <stdbool.h>

#include "menu.h"
#include "file.h"
#include "pattern.h"
#include "status.h"
#include "input.h"
#include "debugmalloc.h"

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
    Pattern *pattern = NULL;
    while (true)
    {
        int selection = show_menu(menu_items, menu_items_n, 2);
        switch (selection)
        {
        case 0: // New pattern
            /* code */
            break;
        case 1: // Load pattern
            if (pattern != NULL)
            {
                free_pattern(pattern);
                pattern = NULL;
            }
            pattern = load_file();
            if (pattern != NULL)
            {
                print_status(successful, "Pattern loaded successfully!");
            }
            break;
        case 2: // Play
            if (pattern == NULL)
            {
                print_status(info, "No pattern was loaded. Use 'New pattern' or 'Load pattern'");
            }
            break;
        case 3: // Edit
            /* code */
            break;
        case 4: // Save
            if (pattern == NULL)
            {
                print_status(info, "No pattern was loaded. Use 'New pattern' or 'Load pattern'");
            }
            else
            {
                save_pattern(pattern);
            }
            break;
        case 5: // Exit
            if (pattern != NULL)
            {
                free_pattern(pattern);
            }
            endwin();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
}