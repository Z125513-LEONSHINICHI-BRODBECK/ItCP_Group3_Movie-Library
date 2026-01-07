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
void movie_list_add(MovieList *list, Movie *movie);
Movie *movie_list_get(const MovieList *list, size_t index);

#endif /* MOVIE_LIST_H */
