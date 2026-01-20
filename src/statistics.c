#include <stdio.h>
#include <string.h>
#include "statistics.h"
#include "movie.h"
#include "movie_list.h"

void show_stats(const MovieList *list) {
    printf("\e[1;1H\e[2J");

    if (!list || movie_list_size(list) == 0) {
        printf("No movies loaded.\n");
        return;
    }

    size_t total = movie_list_size(list);

    const Movie *m0 = movie_list_get(list, 0);
    int min_year = movie_get_release_year(m0);
    int max_year = movie_get_release_year(m0);

    for (size_t i = 1; i < total; i++) {
        const Movie *m = movie_list_get(list, i);
        int y = movie_get_release_year(m);
        if (y < min_year) min_year = y;
        if (y > max_year) max_year = y;
    }

    const char *genres[256];
    int counts[256];
    int unique = 0;

    for (size_t i = 0; i < total; i++) {
        const Movie *m = movie_list_get(list, i);
        const char *g = movie_get_genre(m);

        int found = -1;
        for (int j = 0; j < unique; j++) {
            if (strcmp(genres[j], g) == 0) {
                found = j;
                break;
            }
        }

        if (found >= 0) {
            counts[found]++;
        } else {
            genres[unique] = g;
            counts[unique] = 1;
            unique++;
        }
    }

    printf("\nMovie Statistics\n");
    printf("----------------\n");
    printf("Total movies: %zu\n", total);
    printf("Oldest release year: %d\n", min_year);
    printf("Newest release year: %d\n\n", max_year);

    printf("Movies by genre:\n");
    for (int i = 0; i < unique; i++) {
        printf("  %-15s : %d\n", genres[i], counts[i]);
    }
    printf("\n");
}
