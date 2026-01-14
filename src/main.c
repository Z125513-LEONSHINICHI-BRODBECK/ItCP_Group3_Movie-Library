#include <stdio.h>
#include <string.h>
#include "movie.h"
#include "movie_list.h"
#include "command.h"

int isRunning = 1;

int main(void) {
    /* create initial movie list */
    MovieList *list = movie_list_create();


    // for developing purposes. will be deleted later when read csv file reader is implemented
    movie_list_add(list, movie_create(1, 1999, "The Matrix", "USA", "Sci-Fi", "Wachowskis"));
    movie_list_add(list, movie_create(2, 2010, "Inception", "USA", "Sci-Fi", "Christopher Nolan"));
    movie_list_add(list, movie_create(123, 1985, "Back to the Future", "USA", "Adventure/Comedy", "Robert Zemeckis"));



    // TODO: read csv file
    movie_list_print_table(list);

    while (isRunning) {
        char input[256];
        fgets(input, sizeof(input), stdin);

        char *command = strtok(input, " \n");

        switch (to_command(command)) {
            case (CMD_GROUP):
                // TODO: group movies
                break;
            case (CMD_SEARCH):
                // TODO: search movies
                break;
            case (CMD_ADD):
                // TODO: add movie
                break;
            case (CMD_EDIT):
                // TODO: edit movie
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
            default:
                // TODO: show help
                printf("Unknown command\n");
        }
    }

    /* Cleanup */
    for (size_t i = 0; i < movie_list_size(list); ++i) {
        movie_destroy(movie_list_get(list, i));
    }
    movie_list_destroy(list);
    return 0;
}
