#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

#define MAX_STR 128

/* Movie record used only for file I/O */
typedef struct {
    int id;
    int year;
    char title[MAX_STR];
    char origin[MAX_STR];
    char genre[MAX_STR];
    char director[MAX_STR];
} MovieRecord;

/* Load movies from CSV file
   Returns number of movies loaded, or -1 on fatal error */
int load_movies(const char *filename, MovieRecord **movies, int *count);

/* Save movies to CSV file
   Returns 0 on success, -1 on failure */
int save_movies(const char *filename, const MovieRecord *movies, int count);

#endif
