#ifndef MOVIE_DELETE_H
#define MOVIE_DELETE_H

#include "movie.h"

/* Deletes a movie by ID
   Returns 1 if deleted, 0 otherwise */
int deleteMovie(Movie movies[], int *count);

#endif
