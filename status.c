#include <ncurses.h>
#include <stdarg.h>

void init_status()
{
    // Színek (Nord):
    init_color(COLOR_WHITE, 925, 937, 957);
    init_color(COLOR_BLACK, 180, 204, 251);
    init_color(COLOR_RED, 749, 380, 416);
    init_color(COLOR_GREEN, 639, 745, 549);
    init_color(COLOR_YELLOW, 922, 796, 545);
    init_color(COLOR_BLUE, 369, 506, 675);

    init_pair(1, COLOR_BLACK, COLOR_GREEN);  // successful
    init_pair(2, COLOR_WHITE, COLOR_BLUE);   // info
    init_pair(3, COLOR_BLACK, COLOR_YELLOW); // warning
    init_pair(4, COLOR_WHITE, COLOR_RED);    // error
}

void print_status(int message_type, char *message, ...)
{
    int screen_size_y, screen_size_x;
    getmaxyx(stdscr, screen_size_y, screen_size_x);
    attron(COLOR_PAIR(message_type));
    move(screen_size_y - 1, 0);
    for (int i = 0; i < screen_size_x; i++) // Előző üzenet törlése
    {
        addch(' ');
    }
    move(screen_size_y - 1, 1);
    va_list args;
    va_start(args, message);
    vw_printw(stdscr, message, args);
    attroff(COLOR_PAIR(message_type));
    refresh();
}