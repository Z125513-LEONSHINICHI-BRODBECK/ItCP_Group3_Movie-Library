#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include "movie_list.h"

int load_movies(const char *filename, MovieList *list);

int save_movies(const char *filename, const MovieList *list);

#endif

