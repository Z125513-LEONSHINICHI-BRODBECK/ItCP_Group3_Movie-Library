#ifndef MOVIE_LIST_H
#define MOVIE_LIST_H

#include <stddef.h>
#include "movie.h"

typedef struct MovieList MovieList;

MovieList *movie_list_create(void);
void movie_list_destroy(MovieList *list);

int movie_list_size(const MovieList *list);
const Movie *movie_list_get(const MovieList *list, int index); 
Movie *movie_list_get_mut(MovieList *list, int index); 
void movie_list_add(MovieList *list, Movie *movie);
void movie_list_sort(MovieList *list, int (*compar)(const void *, const void *));
void movie_list_delete_at(MovieList *list, int index);
void movie_list_print_table(const MovieList *list);

#endif 
