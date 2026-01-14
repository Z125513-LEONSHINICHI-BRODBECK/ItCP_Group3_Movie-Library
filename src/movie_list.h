#ifndef MOVIE_LIST_H
#define MOVIE_LIST_H

#include <stddef.h>
#include "movie.h"

typedef struct MovieList MovieList;

/* Creation / destruction */
MovieList *movie_list_create(void);
void movie_list_destroy(MovieList *list);

/* Operations */
size_t movie_list_size(const MovieList *list);
const Movie *movie_list_get(const MovieList *list, size_t index); //read-only
Movie *movie_list_get_mut(MovieList *list, size_t index); //mutable
void movie_list_add(MovieList *list, Movie *movie);
void movie_list_print_table(const MovieList *list);

#endif /* MOVIE_LIST_H */
