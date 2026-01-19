#include <stdio.h>
#include "help.h"

void show_help(void) {
    printf("\nAvailable commands:\n\n");

    printf("  show\n");
    printf("    Show all movies\n\n");

    printf("  search [-t|-i|-y|-o|-g|-d] <value>\n");
    printf("    Search movies by:\n");
    printf("      -t  title\n");
    printf("      -i  id\n");
    printf("      -y  release year\n");
    printf("      -o  origin\n");
    printf("      -g  genre\n");
    printf("      -d  director\n\n");

    printf("  group <field>\n");
    printf("    Group movies by a field\n\n");

    printf("  add\n");
    printf("    Add a new movie\n\n");

    printf("  edit\n");
    printf("    Edit an existing movie\n\n");

    printf("  delete\n");
    printf("    Delete a movie\n\n");

    printf("  stats\n");
    printf("    Show movie library statistics\n\n");

    printf("  help\n");
    printf("    Show this help message\n\n");

    printf("  exit\n");
    printf("    Exit the program\n\n");
}
