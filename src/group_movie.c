#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct {
    int year;
    char title[100];
    char director[100];
    char genre[50];
    char origin[50];
} Movie;

int compareYear(const void *a, const void *b) {
    Movie *movieA = (Movie *)a;
    Movie *movieB = (Movie *)b;
    return (movieA->year - movieB->year);
}

int compareDirector(const void *a, const void *b) {
    Movie *movieA = (Movie *)a;
    Movie *movieB = (Movie *)b;
    return strcasecmp(movieA->director, movieB->director);
}

int compareGenre(const void *a, const void *b) {
    Movie *movieA = (Movie *)a;
    Movie *movieB = (Movie *)b;
    return strcasecmp(movieA->genre, movieB->genre);
}

int compareOrigin(const void *a, const void *b) {
    Movie *movieA = (Movie *)a;
    Movie *movieB = (Movie *)b;
    return strcasecmp(movieA->origin, movieB->origin);
}


void groupMovies(Movie *movies, int count, char flag) {
    if (flag == 'y') {
        qsort(movies, count, sizeof(Movie), compareYear);
        printf("\nGrouped by Release Year (Oldest to Newest):\n");
    } 
    else if (flag == 'd') {
        qsort(movies, count, sizeof(Movie), compareDirector);
        printf("\nGrouped Alphabetically by Director:\n");
    } 
    else if (flag == 'g') {
        qsort(movies, count, sizeof(Movie), compareGenre);
        printf("\nGrouped Alphabetically by Genre:\n");
    } 
    else if (flag == 'o') {
        qsort(movies, count, sizeof(Movie), compareOrigin);
        printf("\nGrouped Alphabetically by Origin:\n");
    } 
    else {
        printf("\nInvalid flag. Use -y, -d, -g, or -o.\n");
        return;
    }

    /*printf("%-6s | %-20s | %-20s | %-15s | %-10s\n", "Year", "Title", "Director", "Genre", "Origin");
    for (int i = 0; i < count; i++) {
        printf("%-6d | %-20.20s | %-20.20s | %-15.15s | %-10.10s\n", 
               movies[i].year, movies[i].title, movies[i].director, movies[i].genre, movies[i].origin);
    }*/
}
