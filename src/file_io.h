#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include "movie_list.h"

/* Load movies from CSV file into an existing MovieList.
   Returns number of movies loaded, or -1 on fatal error. */
int load_movies(const char *filename, MovieList *list);

/* Save movies from a MovieList to CSV file.
   Returns 0 on success, -1 on failure. */
int save_movies(const char *filename, const MovieList *list);

#endif /* FILE_IO_H */
