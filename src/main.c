#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

int main(void) {
    MovieRecord *movies = NULL;
    int count = 0;

    int loaded = load_movies("movie.csv", &movies, &count);
    if (loaded < 0) {
        fprintf(stderr, "Failed to load movies\n");
        return 1;
    }

    printf("Loaded %d movies\n", count);

    /* Optional: print loaded movies */
    for (int i = 0; i < count; i++) {
        printf("%d | %d | %s | %s | %s | %s\n",
               movies[i].id,
               movies[i].year,
               movies[i].title,
               movies[i].origin,
               movies[i].genre,
               movies[i].director);
    }

    /* Save back to file on exit */
    if (save_movies("movie.csv", movies, count) == 0) {
        printf("Movies saved successfully.\n");
    }

    free(movies);
    return 0;
}
