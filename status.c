#include <ncurses.h>

void init_status()
{
    // Színek (Nord):
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

void print_status(int message_type, char *message)
{
    attron(COLOR_PAIR(message_type));
    move(LINES - 1, 0);
    for (int i = 0; i < COLS; i++) // Előző üzenet törlése
    {
        addch(' ');
    }
    move(LINES - 1, 1);
    printw(message);
    attroff(COLOR_PAIR(message_type));
    refresh();
}