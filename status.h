#ifndef STATUS_H
#define STATUS_H

typedef enum Statustype
{
    successful,
    info,
    warning,
    error
} Statustype;

void print_status(Statustype message_type, char *message);
void init_status();

#endif