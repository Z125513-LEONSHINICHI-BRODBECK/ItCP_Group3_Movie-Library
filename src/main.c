#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "movie.h"
#include "file_io.h"
#include "movie_list.h"
#include "command.h"
#include "./commands/movie_search.h"
#include "./commands/movie_add_edit.h"

int isRunning = 1;

int main(void) {
    int count = 0;
    MovieList *list = movie_list_create();
    if (!list) {
        fprintf(stderr, "Failed to create movie list\n");
        return 1;
    }

    /* load_movies now fills the provided MovieList and returns number loaded */
    count = load_movies("movie.csv", list);
    if (count < 0) {
        fprintf(stderr, "Failed to load movies from movie.csv\n");
    } else {
        /* optional: print how many loaded */
        printf("Loaded %d movies\n", count);
    }

    movie_list_print_table(list);

    while (isRunning) {
        char input[256];
        char command[32] = {0}, flag[32] = {0}, arg[256] = {0};

        if (fgets(input, sizeof input, stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        int n = sscanf(input, "%31s %31s %255[^\n]", command, flag, arg);

        switch (to_command(command)) {
            case (CMD_GROUP):
                // TODO: group movies
                break;
            case (CMD_SEARCH):
                if (n < 3) { printf("Usage: search [-t|-i|-y|-o|-g|-d] <value>\n> "); break; }
                if (flag[0] != '-') { printf("Expected flag after search\n> "); break; }

                switch (flag[1]) {
                    case 't': movie_list_search_by_title(list, arg); break;
                    case 'i': {
                        char *end; long id = strtol(arg, &end, 10);
                        if (end == arg) printf("Invalid id: %s\n> ", arg);
                        else movie_list_search_by_id(list, (int)id);
                        break;
                    }
                    case 'y': {
                        char *end; long y = strtol(arg, &end, 10);
                        if (end == arg) printf("Invalid year: %s\n> ", arg);
                        else movie_list_search_by_year(list, (int)y);
                        break;
                    }
                    case 'o': movie_list_search_by_origin(list, arg); break;
                    case 'g': movie_list_search_by_genre(list, arg); break;
                    case 'd': movie_list_search_by_director(list, arg); break;
                    default:
                        printf("Unknown search flag: %s\n> ", flag);
                }
                break;

            case (CMD_ADD):
                add_movie_manually(list);
                break;
            case (CMD_EDIT):
                if (n < 3) {
                    printf("Usage: edit -i <id>\n> ");
                    break;
                }
                if (flag[0] != '-' || flag[1] != 'i') {
                    printf("Expected -i flag for edit\n> ");
                    break;
                }

                {
                    char *end;
                    long id = strtol(arg, &end, 10);
                    if (end == arg || *end != '\0' || id <= 0) {
                        printf("Invalid id: %s\n", arg);
                    } else {
                        edit_movie_manually(list, (int)id);
                    }
                }
                break;
            case (CMD_DELETE):
                // TODO: delete movie
                break;
            case (CMD_STATS):
                // TODO: show stats
                break;
            case (CMD_HELP):
                // TODO: show help
                break;
            case (CMD_EXIT):
                isRunning = 0;
                printf("Bye.\n");
                break;
            case (CMD_SHOW_ALL):
                movie_list_print_table(list);
                break;
            default:
                // TODO: show help
                printf("Unknown command\n> ");
        }
    }

    /* Cleanup */
    for (size_t i = 0; i < movie_list_size(list); ++i) {
        movie_destroy(movie_list_get_mut(list, i));
    }
    movie_list_destroy(list);
    return 0;
}
