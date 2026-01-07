#include "movie.h"
#include <stdlib.h>
#include <string.h>

/* Private definition */
struct Movie {
    int id;
    int release_year;
    char *title;
    char *origin;
    char *genre;
    char *director;
};

static char *copy_string(const char *s) {
    if (!s) return NULL;

    char *copy = malloc(strlen(s) + 1);
    if (copy) {
        strcpy(copy, s);
    }
    return copy;
}

/* Creation / destruction */

Movie *movie_create(
    int id,
    int release_year,
    const char *title,
    const char *origin,
    const char *genre,
    const char *director
) {
    Movie *m = malloc(sizeof *m);
    if (!m) return NULL;

    m->id = id;
    m->release_year = release_year;
    m->title = copy_string(title);
    m->origin = copy_string(origin);
    m->genre = copy_string(genre);
    m->director = copy_string(director);

    return m;
}

void movie_destroy(Movie *movie) {
    if (!movie) return;

    free(movie->title);
    free(movie->origin);
    free(movie->genre);
    free(movie->director);
    free(movie);
}

/* Getters */

int movie_get_id(const Movie *movie) {
    return movie->id;
}

int movie_get_release_year(const Movie *movie) {
    return movie->release_year;
}

const char *movie_get_title(const Movie *movie) {
    return movie->title;
}

const char *movie_get_origin(const Movie *movie) {
    return movie->origin;
}

const char *movie_get_genre(const Movie *movie) {
    return movie->genre;
}

const char *movie_get_director(const Movie *movie) {
    return movie->director;
}

/* Setters */

void movie_set_id(Movie *movie, int id) {
    movie->id = id;
}

void movie_set_release_year(Movie *movie, int release_year) {
    movie->release_year = release_year;
}

void movie_set_title(Movie *movie, const char *title) {
    free(movie->title);
    movie->title = copy_string(title);
}

void movie_set_origin(Movie *movie, const char *origin) {
    free(movie->origin);
    movie->origin = copy_string(origin);
}

void movie_set_genre(Movie *movie, const char *genre) {
    free(movie->genre);
    movie->genre = copy_string(genre);
}

void movie_set_director(Movie *movie, const char *director) {
    free(movie->director);
    movie->director = copy_string(director);
}
