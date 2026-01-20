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

/**
 * Converts a command string to a Command enum value.
 *
 * @param s  input string (e.g. "add", "search")
 * @return   corresponding Command value, or CMD_UNKNOWN
 */
Command to_command(const char *s);

#endif /* COMMAND_H */
