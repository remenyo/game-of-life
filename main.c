#include <ncurses.h>
#include <stdbool.h>

#include "menu.h"
#include "file.h"
#include "pattern.h"
#include "status.h"
#include "input.h"
#include "play.h"
#include "debugmalloc.h"

int warn_dirty()
{
    print_status(warning, "Your pattern was modified since the last save. Continue?");
    char *no_yes[] = {"No", "Yes"};
    if (1 == show_menu(no_yes, 2, 2))
    {
        return 1;
    }
    return 0;
}

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
            if (pattern->dirty)
            {
                if (warn_dirty())
                {
                    play_pattern(pattern);
                }
            }
            else
            {
                play_pattern(pattern);
            }

            break;
        case 3: // Edit
            if (pattern->dirty)
            {
                if (warn_dirty())
                {
                    // edit_pattern(pattern);
                }
            }
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
                if (pattern->dirty)
                {
                    if (warn_dirty())
                    {
                        free_pattern(pattern);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    free_pattern(pattern);
                }
            }
            endwin();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
}