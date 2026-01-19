#include <stdio.h>
#include "movie.h"

#define FILE_NAME "movies.csv"

void saveMovies(Movie movies[], int count) {
    FILE *fp = fopen("movies.tmp", "w");
    if (!fp) {
        perror("File save error");
        return;
    }

    fprintf(fp, "ID,Year,Title,Origin,Genre,Director\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
                movies[i].id,
                movies[i].year,
                movies[i].title,
                movies[i].origin,
                movies[i].genre,
                movies[i].director);
    }

    fclose(fp);

    /* Atomic replace */
    rename("movies.tmp", FILE_NAME);
}
