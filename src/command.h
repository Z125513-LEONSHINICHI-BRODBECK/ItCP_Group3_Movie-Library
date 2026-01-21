#ifndef COMMAND_H
#define COMMAND_H

typedef enum {
    CMD_SORT,
    CMD_SEARCH,
    CMD_ADD,
    CMD_EDIT,
    CMD_DELETE,
    CMD_STATS,
    CMD_HELP,
    CMD_EXIT,
    CMD_SHOW_ALL,
    CMD_UNKNOWN
} Command;


Command to_command(const char *s);

#endif 
