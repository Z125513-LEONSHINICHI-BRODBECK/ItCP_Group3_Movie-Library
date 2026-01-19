#include <stdio.h>
#include <stdlib.h>
#include "movie.h"
#include "movie_delete.h"
#include "movie_save.h"

#define MAX_MOVIES 1000

int main() {
    Movie movies[MAX_MOVIES];
    int count = 0;   /* Assume movies already loaded */
    int choice;

    printf("=== Movie Database ===\n");

    while (1) {
        printf("\n1. Delete movie\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (deleteMovie(movies, &count)) {
                    saveMovies(movies, count);
                    printf("Database saved.\n");
                }
                break;

            case 0:
                printf("Exiting.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
}
