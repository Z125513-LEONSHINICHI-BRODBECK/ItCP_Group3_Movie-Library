#ifndef MOVIE_H
#define MOVIE_H

typedef struct Movie Movie;

Movie *movie_create(
    int id,
    int release_year,
    const char *title,
    const char *origin,
    const char *genre,
    const char *director
);

void movie_destroy(Movie *movie);

int movie_get_id(const Movie *movie);
int movie_get_release_year(const Movie *movie);
const char *movie_get_title(const Movie *movie);
const char *movie_get_origin(const Movie *movie);
const char *movie_get_genre(const Movie *movie);
const char *movie_get_director(const Movie *movie);

void movie_set_id(Movie *movie, int id);
void movie_set_release_year(Movie *movie, int release_year);
void movie_set_title(Movie *movie, const char *title);
void movie_set_origin(Movie *movie, const char *origin);
void movie_set_genre(Movie *movie, const char *genre);
void movie_set_director(Movie *movie, const char *director);

#endif 
