#ifndef STATUS_H
#define STATUS_H

typedef enum Statustype
{
    successful = 1,
    info,
    warning,
    error
} Statustype;

void print_status(Statustype message_type, char *message, ...);
void init_status();

#endif