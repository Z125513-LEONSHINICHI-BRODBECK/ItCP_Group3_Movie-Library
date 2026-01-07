#include <stdio.h>
#include "movie.h"
#include "movie_list.h"


/*
 * THIS FILE IS JUST A PLACEHOLDER FOR THE BEGINNING. IT DEMONSTRATES A BASIC IMPLEMENTATION OF THE MOVIE OBJECT AND THE MOVIE LIST.
 */
int main(void) {
    // creating initial dynamic list
    MovieList *list = movie_list_create();

    // adding movies
    movie_list_add(list, movie_create(1, 1999, "The Matrix", "USA", "Sci-Fi", "Wachowskis"));
    movie_list_add(list, movie_create(2, 2010, "Inception", "USA", "Sci-Fi", "Nolan"));


    // displaying movie title and year of the whole movie list
    for (size_t i = 0; i < movie_list_size(list); i++) {
        Movie *m = movie_list_get(list, i);
        printf("%s (%d)\n",
               movie_get_title(m),
               movie_get_release_year(m));
    }

    // cleanup
    // first destroy movies, then destroy list
    for (size_t i = 0; i < movie_list_size(list); i++) {
        movie_destroy(movie_list_get(list, i));
    }
    movie_list_destroy(list);
    return 0;
}
