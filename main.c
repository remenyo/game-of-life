#include <ncurses.h>
#include <stdbool.h>

#include "menu.h"
#include "file.h"
#include "pattern.h"
#include "status.h"
#include "input.h"
#include "play.h"
#include "edit.h"
#include "debugmalloc.h"

bool warn_dirty();
void event_loop();

int screen_size_x, screen_size_y;
int menu_items_n = 7;
char *menu_items[] = {"New pattern", "Load pattern", "Play", "Edit", "Save", "Refresh menu", "Exit"};
Pattern *pattern = NULL;

int main()
{
    initscr();
    cbreak();
    noecho();
    mouseinterval(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(0);
    start_color();
    init_status();

    while (true)
    {
        event_loop();
    }
}

bool warn_dirty()
{
    clear();
    print_status(warning, "Your pattern was modified since the last save. Continue?");
    char *choices[] = {"Go back", "Continue"};
    if (1 == show_menu(choices, 2, 2))
    {
        return true;
    }
    return false;
}

void event_loop()
{
    int selection = show_menu(menu_items, menu_items_n, 2);
    switch (selection)
    {
    case 0: // New pattern
        if (pattern != NULL)
        {
            if (pattern->dirty)
            {
                if (warn_dirty())
                {
                    free_pattern(pattern);
                    pattern = new_empty_pattern();
                }
            }
            else
            {
                free_pattern(pattern);
                pattern = new_empty_pattern();
            }
        }
        else
            pattern = new_empty_pattern();
        break;
    case 1: // Load pattern
        if (pattern != NULL)
        {
            if (pattern->dirty)
            {
                if (warn_dirty())
                {
                    free_pattern(pattern);
                    pattern = NULL;
                    pattern = load_file();
                }
            }
            else
            {
                free_pattern(pattern);
                pattern = NULL;
                pattern = load_file();
            }
        }
        else
        {
            pattern = load_file();
        }
        if (pattern != NULL)
        {
            print_status(successful, "Pattern (%s) loaded successfully!", pattern->name);
        }
        break;
    case 2: // Play
        if (pattern == NULL)
        {
            print_status(info, "No pattern loaded. Use 'New pattern' or 'Load pattern'");
        }

        else
        {
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
        }
        break;
    case 3: // Edit
        if (pattern != NULL)
        {
            if (pattern->dirty)
            {
                if (warn_dirty())
                {
                    edit_pattern(pattern);
                }
            }
            else
            {
                edit_pattern(pattern);
            }
        }
        else
        {
            print_status(info, "No pattern loaded. Use 'New pattern' or 'Load pattern'");
        }

        break;
    case 4: // Save
        if (pattern == NULL)
        {
            print_status(info, "No pattern loaded. Use 'New pattern' or 'Load pattern'");
        }
        else
        {
            save_pattern(pattern);
        }
        break;
    case 5: //
        getmaxyx(stdscr, screen_size_y, screen_size_x);
        wresize(stdscr, screen_size_y, screen_size_x);
        clear();
        // resizeterm(screen_size_y, screen_size_x);
        refresh();
        break;
    case 6: // Exit
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
