#include <ncurses.h>

typedef enum Statustype
{
    successful,
    info,
    warning,
    error
} Statustype;

void init_status()
{
    // Színek (Nord):
    init_color(COLOR_BLACK, 180, 204, 251);
    init_color(COLOR_RED, 749, 380, 416);
    init_color(COLOR_GREEN, 639, 745, 549);
    init_color(COLOR_YELLOW, 922, 796, 545);
    init_color(COLOR_BLUE, 369, 506, 675);

    init_pair(0, COLOR_BLACK, COLOR_GREEN);  // successful
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // info
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // warning
    init_pair(3, COLOR_WHITE, COLOR_RED);    // error
}

void print_status(Statustype message_type, char *message)
{
    int rows, cols; // = Terminal magassag, szelesseg
    getmaxyx(stdscr, rows, cols);
    attron(COLOR_PAIR(message_type));
    move(rows - 1, 0);
    for (int i = 0; i < cols; i++) // Előző üzenet törlése
    {
        addch(' ');
    }
    move(rows - 1, 0);
    printw(message);
    refresh();
}