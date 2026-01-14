#include <string.h>
#include "command.h"

Command to_command(const char *s) {
    if (strcmp(s, "group") == 0)  return CMD_GROUP;
    if (strcmp(s, "search") == 0)  return CMD_SEARCH;
    if (strcmp(s, "add") == 0)  return CMD_ADD;
    if (strcmp(s, "edit") == 0)  return CMD_EDIT;
    if (strcmp(s, "delete") == 0)  return CMD_DELETE;
    if (strcmp(s, "stats") == 0)  return CMD_STATS;
    if (strcmp(s, "help") == 0)  return CMD_HELP;
    if (strcmp(s, "exit") == 0) return CMD_EXIT;
    if (strcmp(s, "") == 0) return CMD_SHOW_ALL;
    return CMD_UNKNOWN;
}
