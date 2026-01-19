#ifndef MOVIE_H
#define MOVIE_H

typedef struct {
    int id;
    int year;
    char title[50];
    char origin[30];
    char genre[30];
    char director[30];
} Movie;

#endif
